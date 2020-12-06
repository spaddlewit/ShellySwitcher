#include "Listable.h"

void *Listable::operator new(size_t size)
{
	return calloc(1, size);
}

void Listable::operator delete(void *p)
{
	free(p);
}

Listable::Listable()
{
	next = prev = NULL;
}

Listable::~Listable()
{
}

//
// Add
//
// Adds an item to the list
//
void Listable::Add(Listable *item, Listable **itemHead)
{
	if (*itemHead == NULL)
	{
		*itemHead = item;
		(*itemHead)->prev = (*itemHead)->next = NULL;
	}
	else
	{
		Listable *tail;
		tail = *itemHead;

		while (tail->next != NULL)
			tail = tail->next;

		tail->next = item;

		tail->next->prev = tail;

		item->next = NULL;
	}
}

//
// AddFront
//
// Adds an item to the front of the list
// (This is much faster)
//
void Listable::AddFront(Listable *item, Listable **itemHead)
{
	if (*itemHead == NULL)
	{
		*itemHead = item;
		(*itemHead)->prev = (*itemHead)->next = NULL;
	}
	else
	{
		(*itemHead)->prev = item;
		item->next = (*itemHead);
		item->prev = NULL;
		*itemHead = item;
	}
}

//
// AddBefore
//
// Adds an item before the item specified in the list
//
void Listable::AddBefore(Listable *item, Listable *spot, Listable **itemHead)
{
	Listable *prev = spot->prev;

	if (!prev)
		AddFront(item, itemHead);
	else
	{
		item->next = spot;
		spot->prev = item;
		item->prev = prev;
		prev->next = item;
	}
}

//
// AddAfter
//
// Adds an item after the item specified in the list
//
void Listable::AddAfter(Listable *item, Listable *spot, Listable **itemHead)
{
	Listable *next = spot->next;

	if (!next)
		Add(item, itemHead);
	else
	{
		item->prev = spot;
		spot->next = item;
		item->next = next;
		next->prev = item;
	}
}

//
// Remove
//
// Take an item out of the list and free its memory.
//
void Listable::Remove(Listable *item, Listable **itemHead)
{
	if (item == *itemHead) // Start of list
	{
		*itemHead = item->next;

		if (*itemHead)
			(*itemHead)->prev = NULL;
	}
	else if (item->next == NULL) // end of list
	{
		item->prev->next = NULL;
	}
	else // Somewhere in between
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}

	delete item;
}

//
// RemoveAll
//
// Removes all items from the list, freeing their memory.
//
void Listable::RemoveAll(Listable **itemHead)
{
	Listable *item;
	Listable *next;
	for (item = *itemHead; item; item = next)
	{
		next = item->next;
		Remove(item, itemHead);
	}
}

//
// RemoveNoFree
//
// Take an item out of the list, but don't free its memory.
//
void Listable::RemoveNoFree(Listable *item, Listable **itemHead)
{
	if (item == *itemHead) // Start of list
	{
		*itemHead = item->next;

		if (*itemHead)
			(*itemHead)->prev = NULL;
	}
	else if (item->next == NULL) // end of list
	{
		item->prev->next = NULL;
	}
	else // Somewhere in between
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}
}

//
// GetCount
//
// Counts the # of items in a list
// Should not be used in performance-minded code
//
size_t Listable::GetCount(const Listable *itemHead)
{
	const Listable *item = itemHead;

	size_t count = 0;
	for (; item; item = item->next)
		count++;

	return count;
}

//
// GetByIndex
//
// Gets an item in the list by its index
// Should not be used in performance-minded code
//
Listable *Listable::GetByIndex(Listable *itemHead, unsigned int index)
{
	Listable *head = itemHead;
	unsigned int count = 0;
	Listable *node;
	for (node = head; node; node = node->next)
	{
		if (count == index)
			return node;

		count++;
	}

	return NULL;
}

Listable *Listable::GetLast(Listable *itemHead)
{
	Listable *node;
	for (node = itemHead; node; node = node->next)
	{
		if (!node->next)
			return node;
	}

	return NULL;
}

bool Listable::Contains(Listable *item, Listable *itemHead)
{
	Listable *node;
	for (node = itemHead; node; node = node->next)
	{
		if (node == item)
			return true;
	}

	return false;
}

void Listable::Reverse(Listable **itemHead)
{
	Listable *curr = *itemHead;
	Listable *temp = NULL;

	while (curr != NULL)
	{
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;
		curr = curr->prev;
	}

	if (temp != NULL)
		*itemHead = temp->prev;
}
