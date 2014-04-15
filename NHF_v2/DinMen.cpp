#include "DinMem.h"

#include <iostream>

DinMen::DinMen(int requestedSize)
{
	if (requestedSize < 1)
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Request size cannot be zero or less!\n\n***********************************************");
	
	totalSize = requestedSize;
	remainingSize = requestedSize;
	begin = new DM_List();
	end = new DM_List();
	begin->next = end;
}

void DinMen::operator+=(Request* request)
{
	if (request->getSize() > remainingSize)
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Requested entity's size is greater than DinMen total size!\n\n***********************************************");
	
	DM_List* movingPtr = begin;
	DM_List* newEntity = new DM_List(request);

	while (movingPtr->next != NULL) { movingPtr = movingPtr->next; }

	movingPtr->next = newEntity;
	newEntity->next = end;
}

void DinMen::status()
{
	std::cout << std::endl << std::endl;
	std::cout << "============================================\n\n";
	std::cout << "DinMen STATUS:" << std::endl;
	
	std::cout << "Tolal size: " << totalSize << std::endl;
	std::cout << "Remaining size: " << remainingSize << std::endl;

	std::cout << "\n============================================\n\n";
}

DinMen::~DinMen()
{

}