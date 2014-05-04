#include "Request.h"
#include "DinMem.h"

#include <iostream>
#include <vld.h>

#define REQUEST_BASIC 0
#define REQUEST_EXCEPTION 0
#define DINMEN_BASIC 0
#define DINMEN_OBJ 1

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

		//Requestek
		Request* r1 = new Request(3);
		std::cout << r1 << std::endl;
		Request* r2 = new Request(3);
		std::cout << r2 << std::endl;
		Request* r3 = new Request(2);
		std::cout << r3 << std::endl;

		Request a(2);
		std::cout << &a;

		d1 += &a;

		d1 += r1;
		d1.status();
		d1 -= r1;
		d1.status();
		d1 += r1;
		d1 += r2;
		d1 += r3;
		d1.status();

		//Requestek felszabaditasa
		delete r1;
		delete r2;
		delete r3;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif DINMEN_OBJ
	try
	{
		DinMen d(15);
		Request r1(3);
		Request* ptr = &r1;

		d += &r1;
		d.status();
		d -= &r1;
		d.status();
		d += &r1;
		d.status();
		d += &r1;
		d.status();
		d += ptr;
		d.status();
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#endif
}