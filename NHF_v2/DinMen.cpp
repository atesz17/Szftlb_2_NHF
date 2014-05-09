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
	struct match
	{
		unsigned int startPos;
		DM_List* prevElement;
	};

	match Match;
	Match.prevElement = NULL;

	DM_List* ptr = start;

	if (request->getSize() > remainingSize)
	{
		throw std::out_of_range("***********************************************\n\nERROR_DinMen: Requested entity's size is greater than DinMen total size!\n\n***********************************************");
	}
	else
	{
		while (ptr->next != finish)
		{
			// Ha a startnal vagyunk
			if (ptr->req == NULL)
			{
				if ((ptr->next->startPos) >= (request->getSize()))
				{
					Match.startPos = (ptr->next->startPos - request->getSize());
					Match.prevElement = ptr;
				}
			}

			// Ha egy sima elemnel vagyunk
			else
			{
				if ((ptr->next->startPos - ptr->startPos - ptr->req->getSize()) >= (request->getSize()))
				{
					//Match.startPos = (ptr->next->startPos - ptr->startPos - ptr->req->getSize());
					Match.startPos = ptr->next->startPos - request->getSize();
					Match.prevElement = ptr;
				}
			}
			ptr = ptr->next;
		}
		// Ha ures a lista
		if (ptr->req == NULL)
		{
			Match.startPos = totalSize - request->getSize();
			Match.prevElement = start;
		}

		// Ha van hely az utolso elem es az utolso memoria terulet kozott
		else
		{
			if (totalSize - ptr->startPos - ptr->req->getSize() >= request->getSize())
			{
				Match.startPos = totalSize - request->getSize();
				Match.prevElement = ptr;
			}
		}

		// Ha nem talaltunk helyet az elemnek (mert lyukak vannak)
		if (Match.prevElement == NULL)
		{
			throw std::out_of_range("***********************************************\n\nERROR_DinMen: Requested entity's size cannot fit in the memory stacks of DinMen!\n\n***********************************************");
		}
		else
		{
			ptr = start;

			while (ptr != Match.prevElement)
			{
				ptr = ptr->next;
			}

			DM_List* newEntity = new DM_List(request, Match.startPos);
			newEntity->next = ptr->next;
			ptr->next = newEntity;
			remainingSize -= newEntity->req->getSize();
		}
	}

	std::cout << "\nAdding new element to DinMen... address: " << request << " size: " << request->getSize() << std::endl;

	status();
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

	std::cout << "\nRemoving element from DinMen... address: " << request << " size: " << request->getSize() << std::endl;
	
	status();
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
		std::cout << it->req << " (" << it->req->getSize() << ")";
	}

	///////////////////////
	/// Innentol opcionalis
	///////////////////////

	std::cout << std::endl << std::endl;

	DM_List* ptr = start;
	while (ptr->next != finish)
	{
		if (ptr == start)
		{
			for (unsigned int i = 0; i < ptr->next->startPos; i++)
				std::cout << '0';
		}
		else
		{
			for (unsigned int z = 0; z < ptr->req->getSize(); z++)
				std::cout << 'X';
			for (unsigned int i = ptr->startPos + ptr->req->getSize(); i < ptr->next->startPos; i++)
				std::cout << '0';
		}
		ptr = ptr->next;
	}
	
	// Ha ures a lista
	if (ptr == start)
	{
		for (unsigned int i = 0; i < totalSize; i++)
			std::cout << '0';
	}

	// Ha az utolso elemnel vagyunk
	else
	{
		for (unsigned int i = 0; i < ptr->req->getSize(); i++)
			std::cout << 'X';

		// Ha nem a memoria vegeig van lefoglalva az utolso elem terulete
		if (totalSize - ptr->req->getSize() - ptr->startPos != 0)
		{
			for (unsigned int z = 0; z < totalSize - ptr->req->getSize() - ptr->startPos; z++)
				std::cout << '0';
		}
	}

	///////////////////////
	/// Itt a vege
	///////////////////////

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