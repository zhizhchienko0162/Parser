#ifndef PTP_HEADER_H
#define PTP_HEADER_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

class PTPHeader {
private:
    typedef struct {
        uint8_t alternateMaster: 1;
        uint8_t twoStep: 1;
        uint8_t unicast: 1;
        uint8_t reserved2: 2;
        uint8_t profSpec1: 1;
        uint8_t profSpec2: 1;
        uint8_t security: 1;
		uint8_t li61: 1;
        uint8_t li59: 1;
        uint8_t utc: 1;
        uint8_t timescale: 1;
        uint8_t timeTraceable: 1;
        uint8_t freqTraceable: 1;
        uint8_t reserved: 2;
    } flag_t;

	typedef struct {
        uint8_t msgType: 4;
        uint8_t transportSpec: 4;
        uint8_t verPTP: 4;
        uint8_t reserved: 4;
        uint16_t msgLength;
        uint8_t domainNum;
        uint8_t reserved2;
        flag_t flags;
        double correctionField;
        uint8_t reserved3[4];
        uint8_t srcPort[10];
        uint16_t seqId;
        uint8_t ctrlField;
        uint8_t logMsgInt;
	} header_t;

    header_t data;

public:
    PTPHeader() {}
    PTPHeader(uint8_t*);

    int getType() {
        return data.msgType;
    }

    uint16_t getLength() {
        return data.msgLength;
    }

    uint16_t getId() {
        return data.seqId;
    }

    bool isTwoStep() {
        return data.flags.twoStep;
    }

    PTPHeader& operator=(const PTPHeader&);
    bool operator==(const PTPHeader&);

    friend std::ostream& operator<<(std::ostream&, const PTPHeader&);
};

#endif

