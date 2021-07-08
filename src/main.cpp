#include <iostream>
#include <vector>
#include <ctime>
#include <Packet.h>
#include <PayloadLayer.h>
#include <PcapFileDevice.h>
#include <PTPHeader.h>
#include <PTPSync.h>

using namespace std;
using namespace pcpp;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " file\n";

        return 1;
    }

	PcapFileReaderDevice reader(argv[1]);

	if (!reader.open()) {
		cerr << "Error opening file" << endl;

		return 1;
	}

	RawPacket rawPacket;
    uint8_t* payload;
    vector<PTPSync> vect;

	while (reader.getNextPacket(rawPacket)) {
        Packet parsedPacket(&rawPacket);

        if (parsedPacket.isPacketOfType(IPv4)) {
            payload = parsedPacket.getLayerOfType<PayloadLayer>()->getPayload();
            PTPHeader header(payload);

            if (header.getType() == 0x00 || header.getType() == 0x08) {
                PTPSync sync(header, payload);
                vect.push_back(sync);
            }
	    }
    }

	reader.close();

    vect.resize(distance(vect.begin(), unique(vect.begin(), vect.end())));

    time_t res = time(nullptr);
    int id = 0;

    for (int i = 0; i < vect.size(); i++) {
        if (vect[i].getHeader().getType() == 0x00) {
            if (vect[i].getHeader().getId() < id) {
                cerr << "Error: Wrong packet order\n";
                continue;
            }

            id = vect[i].getHeader().getId();

            if (vect[i].getHeader().isTwoStep() && vect.size() - 1 > i) {
                if (vect[i].getHeader().getId() == vect[++i].getHeader().getId()) {
                    cout << vect[i - 1] << endl << res - vect[i].getSeconds() << " SEC AGO\n\n\n";
                } else {
                    cerr << "Error: FollowUp Id is not equal to Sync Id\n";
                }
            } else {
                cout << vect[i] << endl << res - vect[i].getSeconds() << " SEC AGO\n\n\n";
            }
        } else {
            cerr << "Error: FollowUp Packet before Sync\n";
        }
    }

	return 0;
}

