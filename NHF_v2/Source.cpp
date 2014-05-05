#include "Request.h"
#include "DinMem.h"

#include <iostream>

#define REQUEST_BASIC 0
#define REQUEST_EXCEPTION 0
#define DINMEN_BASIC 1
#define DINMEN_OBJ 0
#define ITERATOR 0

std::ostream& operator<<(std::ostream& os, const Request& r)
{
	os << "Ptr: " << &r << " merete: " << r.getSize() << std::endl;
	return os;
}

int main(int argc, char** argv)
{
#if REQUEST_BASIC
		Request r1(1);
		Request r2(2);
		Request r3(9);
		std::cout << r1 << r2 << r3;

		// Ellenorzes
		std::cout << "\nEllenorzes pointerrel:\n\n";
		Request* ptr = &r1;
		std::cout << ptr << std::endl;
		ptr = &r2;
		std::cout << ptr << std::endl;
		ptr = &r3;
		std::cout << ptr << std::endl << std::endl;
		
		// CPORTA
		/*
		std::cout << "CPORTA parameter:" << std::endl << std::endl;
		int cporta = atoi(argv[1]);
		std::cout << "Elso parameter: " << cporta << std::endl;
		Request rCPORTA(cporta);
		std::cout << rCPORTA;
		std::cout << std::endl;
		*/
#elif REQUEST_EXCEPTION
	try
	{
		Request rException(0);
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif DINMEN_BASIC
		DinMen d(5);
		Request r1(1);
		Request r2(1);
		Request r3(2);
		Request r4(1);
		std::cout << r1 << r2 << r3 << r4;

		d += &r1;
		d += &r2;
		d += &r3;
		d += &r4;
		d.status();
		d -= &r3;
		d.status();
		d -= &r1;
		d -= &r2;
		d -= &r4;
		d.status();
#endif
}