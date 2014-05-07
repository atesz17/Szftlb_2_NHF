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
		unsigned int startPos;

		DM_List(Request* newReq = NULL, unsigned int start = 0) : req(newReq), next(NULL)
		{
			startPos = start;
		}
	};

public:

	class iterator;

	DinMen(int);
	void		operator+=(Request*);
	void		operator-=(Request*);
	void		status();
	~DinMen();

	iterator begin() {
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
		iterator(DinMen& d) : p(d.start->next) {}

		iterator& operator++();
		bool operator!=(const iterator& i) const;
		DM_List& operator*();
		DM_List* operator->();
	};
};

#endif