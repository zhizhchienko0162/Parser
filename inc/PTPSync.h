#ifndef PTP_SYNC_H
#define PTP_SYNC_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <PTPHeader.h>

class PTPSync {
private:
	typedef struct {
        uint32_t nanoseconds;
        uint32_t seconds;
        uint16_t reserved;
    } sync_t;

	PTPHeader header;
    sync_t originTimestamp;

public:
    PTPSync() {}
    PTPSync(const PTPSync&);
    PTPSync(PTPHeader&, uint8_t*);

    PTPSync& operator=(const PTPSync&);
    bool operator==(const PTPSync&);

    PTPHeader getHeader() {
        return header;
    }

    uint32_t getSeconds() {
        return originTimestamp.seconds;
    }

	friend std::ostream& operator<<(std::ostream&, const PTPSync&);
};

#endif

