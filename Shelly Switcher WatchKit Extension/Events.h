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
#pragma once
#include "Listable.h"

// Warning! Any class that derives from this MUST NOT
// implement virtual functions!
struct EventArgs
{
	void *tag;

	void *operator new(size_t size)
	{
		return calloc(1, size);
	}

	void operator delete(void *p)
	{
		free(p);
	}

	EventArgs()
	{
	}
};

template <class T>
struct GenEventArgs : EventArgs
{
	T result;

	GenEventArgs(T result) : EventArgs()
	{
		this->result = result;
	}
};

struct CancelEventArgs : EventArgs
{
	bool cancel;

	CancelEventArgs() : EventArgs()
	{
		cancel = false;
	}
};

struct TextChangedEventArgs : EventArgs
{
	const char *prevText;

	TextChangedEventArgs(char *prevText) : EventArgs()
	{
		this->prevText = prevText;
	}
};

struct EventFunc : Listable
{
	void(*func)(void*, EventArgs*);
	void *tag;

	static void RemoveEvent(EventFunc **eventList, void *func);
	static void RemoveEventWithTag(EventFunc **eventList, void *func, void *tag);
	static void DisposeEvents(EventFunc **eventList);
	static void FireEvents(EventFunc *eventList, void *sender, EventArgs *e);
};

template <class T>
struct GenEventFunc : EventFunc
{
	void(*func)(void*, GenEventArgs<T>*);
};
