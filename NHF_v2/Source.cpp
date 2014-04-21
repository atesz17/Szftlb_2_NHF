#include "Request.h"
#include "DinMem.h"

#include <iostream>

#define REQUEST_BASIC 0
#define REQUEST_EXCEPTION 0
#define DINMEN_BASIC 1

int main()
{
#if REQUEST_BASIC
	try
	{
		Request r1(2);
		Request* rPtr = &r1;
		std::cout << r1.getSize() << std::endl;
		std::cout << rPtr->getSize() << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << e.what();
	}
#elif REQUEST_EXCEPTION
	try
	{
		Request r1(0);
		Request *rPtr = &r1;
		std::cout << r1.getSize() << std::endl;
		std::cout << rPtr->getSize() << std::endl;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif DINMEN_BASIC
	try
	{
		DinMen d1(10);
		d1.status();
		Request* r1 = new Request(3);
		std::cout << r1;
		d1 += r1;
		d1.status();
		d1 -= r1;
		d1.status();
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#endif
}