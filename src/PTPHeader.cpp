#include <PTPHeader.h>

PTPHeader::PTPHeader(uint8_t* src) {
    memcpy(&data, src, sizeof(header_t));

    data.msgLength = (data.msgLength << 8) | (data.msgLength >> 8);
    data.seqId = (data.seqId << 8) | (data.seqId >> 8);
}

PTPHeader& PTPHeader::operator=(const PTPHeader &src) {
    memcpy(&data, &src.data, sizeof(header_t));

    return *this;
}

bool PTPHeader::operator==(const PTPHeader &ro) {
    return memcmp(&data, &ro.data, sizeof(header_t)) == 0;
}

std::ostream& operator<<(std::ostream &os, const PTPHeader &header) {
    os << "Precision Time Protocol"
       << "\n\tmessageId: " << (int)header.data.msgType
       << "\n\tversionPTP: " << (int)header.data.verPTP
       << "\n\tmessageLength: " << (int)header.data.msgLength
       << "\n\tsubdomainNumber: " << (int)header.data.domainNum
       << "\n\tflags: "
       << "\n\t\tPTP_SECURITY: " << (header.data.flags.security? "True": "False")
       << "\n\t\tPTP profile Specific 2: " << (header.data.flags.profSpec2? "True": "False")
       << "\n\t\tPTP profile Specific 1: " << (header.data.flags.profSpec1? "True": "False")
       << "\n\t\tPTP_UNICAST: " << (header.data.flags.unicast? "True": "False")
       << "\n\t\tPTP_TWO_STEP: " << (header.data.flags.twoStep? "True": "False")
       << "\n\t\tPTP_ALTERNATE_MASTER: " << (header.data.flags.alternateMaster? "True": "False")
       << "\n\t\tFREQUENCY_TRACEABLE: " << (header.data.flags.freqTraceable? "True": "False")
       << "\n\t\tTIME_TRACEABLE: " << (header.data.flags.timeTraceable? "True": "False")
       << "\n\t\tPTP_TIMESCALE: " << (header.data.flags.timescale? "True": "False")
       << "\n\t\tPTP_UTC_REASONABLE: " << (header.data.flags.utc? "True": "False")
       << "\n\t\tPTP_LI_59: " << (header.data.flags.li59? "True": "False")
       << "\n\t\tPTP_LI_61: " << (header.data.flags.li61? "True": "False")
       << "\n\tcorrection: " << header.data.correctionField
       << "\n\tsequenceId: " << header.data.seqId
       << std::endl;

    return os;
}
