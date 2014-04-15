#ifndef DINMEN_H
#define DINMEN_H

#include "Request.h"

class DinMen
{
	struct DM_List;

	size_t		totalSize;
	size_t		remainingSize;
	DM_List*	begin;
	DM_List*	end;

	struct DM_List
	{
		Request*	req;
		DM_List*	next;

		DM_List(Request* newReq = NULL) : req(newReq), next(NULL) {}
	};

public:
	DinMen(int);
	void		operator+=(Request*);
	void		operator-=(Request*);
	void		status();
	//DESTRUKTOR NINCS MEG KESZ
	~DinMen();
};

#endif