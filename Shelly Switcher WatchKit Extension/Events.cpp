/*
 Copyright 2020 Spaddlewit Inc. www.spaddlewit.com

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
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
