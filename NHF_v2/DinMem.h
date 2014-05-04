#ifndef DINMEN_H
#define DINMEN_H

#include "Request.h"

class DinMen
{
	friend class iterator;
	struct DM_List;

	size_t		totalSize;
	size_t		remainingSize;
	DM_List*	start;
	DM_List*	finish;

	struct DM_List
	{
		Request*	req;
		DM_List*	next;

		DM_List(Request* newReq = NULL) : req(newReq), next(NULL) {}
	};

public:

	class iterator;

	DinMen(int);
	void		operator+=(Request*);
	void		operator-=(Request*);
	void		status();
	~DinMen();

	iterator begin()	{
		return iterator(*this);
	}

	iterator end()	{
		return iterator();
	}

	class iterator
	{
		DM_List* p;
	public:
		iterator() : p(NULL) {}
		iterator(DinMen& d) : p(d.start) {}

		iterator& operator++();
		bool operator!=(const iterator& i);
		DM_List& operator*();
		DM_List* operator->();
	};
};

#endif