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
#include <stdlib.h>

#ifndef NULL
#define NULL 0
#endif

struct Listable
{
public:
	struct Listable *next;
	struct Listable *prev;

	void *operator new(size_t size);
	void operator delete(void *p);

	Listable();
	virtual ~Listable();

	static void Add(Listable *item, Listable **itemHead);
	static void AddFront(Listable *item, Listable **itemHead);
	static void AddBefore(Listable *item, Listable *spot, Listable **itemHead);
	static void AddAfter(Listable *item, Listable *spot, Listable **itemHead);
	static void Remove(Listable *item, Listable **itemHead);
	static void RemoveAll(Listable **itemHead);
	static void RemoveNoFree(Listable *item, Listable **itemHead);
	static size_t GetCount(const Listable *itemHead);
	static Listable *GetByIndex(Listable *itemHead, unsigned int index);
	static Listable *GetLast(Listable *itemHead);
	static bool Contains(Listable *item, Listable *itemHead);
	static void Reverse(Listable **itemHead);
};

template <class T>
struct GenericListable : Listable
{
	T value;

	static bool ContainsItem(T item, GenericListable<T> *itemHead)
	{
		GenericListable<T> *node;
		for (node = itemHead; node; node = (GenericListable<T>*)node->next)
		{
			if (node->value == item)
				return true;
		}

		return false;
	}

	GenericListable(T value) : Listable()
	{
		this->value = value;
	}
};
