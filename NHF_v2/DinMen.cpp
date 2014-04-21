#include "DinMem.h"

#include <iostream>

DinMen::DinMen(int requestedSize)
{
	if (requestedSize < 1)
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Request size cannot be zero or less!\n\n***********************************************");
	
	totalSize = requestedSize;
	remainingSize = requestedSize;
	begin = new DM_List();
	end = NULL;
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

	remainingSize -= newEntity->req->getSize();
}

void DinMen::operator-=(Request* request)
{
	bool match = false;

	for (DM_List* movingPtr = begin; movingPtr != NULL; movingPtr = movingPtr->next)
	{
		if (movingPtr->req == request)
			match = true;
	}
	if (match)
	{
		DM_List* movingPtr = begin;
		DM_List* oneStepBehind = begin;

		while (movingPtr->req != request)
		{
			movingPtr = movingPtr->next;
		}
		while (oneStepBehind->next != movingPtr)
		{
			oneStepBehind = oneStepBehind->next;
		}
		
		oneStepBehind->next = movingPtr->next;
		
		remainingSize += movingPtr->req->getSize();
		delete movingPtr;


	}
	else
	{
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Request is not in DinMen!\n\n***********************************************");
	}
}

void DinMen::status()
{
	std::cout << std::endl << std::endl;
	std::cout << "============================================\n\n";
	std::cout << "DinMen STATUS:" << std::endl << std::endl;
	
	std::cout << "Total size: " << totalSize << std::endl;
	std::cout << "Remaining size: " << remainingSize << std::endl;

	std::cout << "\n============================================\n\n";
}

DinMen::~DinMen()
{
	while (begin->next != NULL)
	{
		DM_List* tmp = begin->next;
		delete begin;
		begin = tmp;
	}
	delete begin;
}