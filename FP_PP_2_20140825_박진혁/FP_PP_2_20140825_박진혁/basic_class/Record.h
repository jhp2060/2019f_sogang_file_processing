#ifndef __RECORD_H__
#define __RECORD_H__

#include "../usingIOBuffer.h"

class Record abstract {
public:
	virtual bool Pack(IOBuffer& Buffer) const = 0;
	virtual bool Unpack(IOBuffer &Buffer) = 0;
};

#endif