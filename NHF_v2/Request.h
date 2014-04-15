#ifndef REQUEST_H
#define REQUEST_H

#include <stdexcept>

class Request
{
	size_t size;
public:
	Request(int s)
	{
		if (s < 1)
			throw std::out_of_range("***********************************************\n\nERROR_Request: Request size cannot be zero or less!\n\n***********************************************");
		size = s;
	}
	int getSize() { return size; }
};

#endif