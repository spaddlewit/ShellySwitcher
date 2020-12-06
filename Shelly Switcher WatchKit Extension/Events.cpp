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
