/*
'Wizard2' engine by Spaddlewit Inc. ( http://www.spaddlewit.com )
An experimental work-in-progress.

This source code is NOT freeware.
It should be distributed to authorized users only.

Your use of this code is governed by your licensing agreement.

*/
#include "Events.h"

void EventFunc::FireEvents(EventFunc *eventList, void *sender, EventArgs *e)
{
	EventFunc *node;
	EventFunc *next;
	for (node = eventList; node; node = next)
	{
		next = (EventFunc*)node->next;
		e->tag = node->tag;
		node->func(sender, e);
	}
}

//
// RemoveEvent
//
// Generic event remover to cut down on repeat code.
// Passing NULL for func will remove all events from this list
//
void EventFunc::RemoveEvent(EventFunc **eventList, void *func)
{
	EventFunc *node;
	EventFunc *next;
	for (node = *eventList; node; node = next)
	{
		next = (EventFunc*)node->next;
		if (node->func == func || !func)
			Listable::Remove(node, (Listable**)eventList);
	}
}

void EventFunc::RemoveEventWithTag(EventFunc **eventList, void *func, void *tag)
{
	EventFunc *node;
	EventFunc *next;
	for (node = *eventList; node; node = next)
	{
		next = (EventFunc*)node->next;
		if (node->func == func && node->tag == tag)
			Listable::Remove(node, (Listable**)eventList);
	}
}

void EventFunc::DisposeEvents(EventFunc **eventList)
{
	RemoveEvent(eventList, NULL);
}