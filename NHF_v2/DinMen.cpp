#include "DinMem.h"

#include <iostream>

DinMen::DinMen(int requestedSize)
{
	if (requestedSize < 1)
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Request size cannot be zero or less!\n\n***********************************************");
	
	totalSize = requestedSize;
	remainingSize = requestedSize;
	start = new DM_List();
	finish = NULL;
	start->next = finish;
}

void DinMen::operator+=(Request* request)
{
	if (request->getSize() > remainingSize)
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Requested entity's size is greater than DinMen total size!\n\n***********************************************");
	
	DM_List* movingPtr = start;
	DM_List* newEntity = new DM_List(request);

	while (movingPtr->next != finish) { movingPtr = movingPtr->next; }

	movingPtr->next = newEntity;
	newEntity->next = finish;

	remainingSize -= newEntity->req->getSize();
}

void DinMen::operator-=(Request* request)
{
	bool match = false;

	for (DM_List* movingPtr = start; movingPtr != finish; movingPtr = movingPtr->next)
	{
		if (movingPtr->req == request)
			match = true;
	}
	if (match)
	{
		DM_List* movingPtr = start;
		DM_List* oneStepBehind = start;

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
	std::cout << "============================================\n";
	std::cout << "DinMen STATUS:" << std::endl << std::endl;
	
	std::cout << "Total size: " << totalSize << std::endl;
	std::cout << "Remaining size: " << remainingSize << std::endl;


	for (DinMen::iterator it = DinMen::begin(); it != DinMen::end(); ++it)
	{
		std::cout << std::endl;
		std::cout << it->req;
	}

	std::cout << "\n\n============================================\n\n";
}

DinMen::~DinMen()
{
	while (start->next != finish)
	{
		DM_List* tmp = start->next;
		delete start;
		start = tmp;
	}
	delete start;
}

DinMen::iterator& DinMen::iterator::operator++()
{
	if (p != NULL)
		p = p->next;
	return *this;
}

bool DinMen::iterator::operator!=(const iterator& i) const
{
	return (p != i.p);
}

DinMen::DM_List& DinMen::iterator::operator*()
{
	if (p != NULL)
		return *p;
	throw std::runtime_error("Hibas indirekcio (*)");
}

DinMen::DM_List* DinMen::iterator::operator->()
{
	if (p != NULL)
		return p;
	throw std::runtime_error("Hibas indirekcio (->)");
}