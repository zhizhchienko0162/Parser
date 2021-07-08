#include <PTPSync.h>

PTPSync::PTPSync(const PTPSync &src){
    header = src.header;

    memcpy(&originTimestamp, &src.originTimestamp, 10);
}

PTPSync::PTPSync(PTPHeader &header, uint8_t* data) {
    this->header = header;

    memcpy(&originTimestamp, data + 34, 10);

    for (int i = 0; i < 5; i++) {
        std::swap(((uint8_t*)(&originTimestamp))[i], ((uint8_t*)(&originTimestamp))[9 - i]);
    }
}

PTPSync& PTPSync::operator=(const PTPSync &src) {
    header = src.header;

    memcpy(&originTimestamp, &src.originTimestamp, 10);

    return *this;
}

bool PTPSync::operator==(const PTPSync &ro) {
    return header == ro.header && memcmp(&originTimestamp, &ro.originTimestamp, sizeof(sync_t)) == 0;
}

std::ostream& operator<<(std::ostream &os, const PTPSync &packet) {
    os << packet.header
       << "originTimestamp (seconds): " << packet.originTimestamp.seconds << std::endl
       << "originTimestamp (nanoseconds): " << packet.originTimestamp.nanoseconds << std::endl;

	return os;
}

