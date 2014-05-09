#include "Request.h"
#include "DinMem.h"

#include <iostream>

#define REQUEST_BASIC 0
#define REQUEST_EXCEPTION 0
#define DINMEN_BASIC 0
#define DINMEN_EXCEPTION_SIZE 0
#define DINMEN_EXCEPTION_OPERATOR_PLUS 0
#define DINMEN_EXCEPTION_OPERATOR_MINUS 0
#define ORAI_PELDA 1

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
#elif DINMEN_EXCEPTION_SIZE
	try
	{
		DinMen d(0);
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif DINMEN_EXCEPTION_OPERATOR_PLUS
	try
	{
		DinMen d(1);
		Request rNAGY(2);
		std::cout << rNAGY;
		d += &rNAGY;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif DINMEN_EXCEPTION_OPERATOR_MINUS
	try
	{
		DinMen d(1);
		Request r(2);
		std::cout << r;
		d -= &r;
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#elif ORAI_PELDA
	try
	{
		/*
		DinMen d(5);
		Request r1(1);
		Request r2(2);
		Request r3(1);
		Request r4(1);

		d += &r1;
		d += &r2;
		d += &r3;
		d += &r4;

		d -= &r1;
		d -= &r3;

		Request rhiba(2);
		//Nem kene bemennie
		d += &rhiba;
		*/

		/*
		DinMen d(3);
		Request r1(1);
		Request r2(1);
		Request r3(1);
		d.status();

		d += &r1;
		d += &r2;
		d += &r3;

		d -= &r1;
		d -= &r3;
		Request rhiba(2);
		d += &rhiba;
		*/

		/*
		DinMen d(7);
		d.status();
		Request r1(1);
		Request r2(3);
		Request r3(2);
		d += &r1;
		d += &r2;
		d += &r3;

		d -= &r2;
		Request r4(4);
		d += &r4;
		*/

		DinMen d(10);
		d.status();
		Request r1(2);
		d += &r1;
		Request r2(1);
		d += &r2;
		Request r3(4);
		d += &r3;
		d -= &r2;
		Request r4(3);
		d += &r4;
		d -= &r3;
		Request r5(2);
		d += &r5;
		d -= &r1;
		Request r6(1);
		d += &r6; 
		Request r7(2);
		d += &r7;
		Request r8(1);
		d += &r8;
		Request r9(1);
		d += &r9;
		d -= &r4;
		d -= &r5;
		d -= &r6;
		d += &r2;
		d += &r1;
		d -= &r7;
		d -= &r8;
		d -= &r9;
		d -= &r2;
		d -= &r1;
		
	}
	catch (const std::out_of_range& e)
	{
		std::cout << std::endl << e.what() << std::endl << std::endl;
	}
#endif
}