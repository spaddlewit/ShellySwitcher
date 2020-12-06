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
