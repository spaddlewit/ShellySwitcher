#include "BindableBase.h"

BindableBase::BindableBase() : Listable()
{
	trackChanges = true;
}

BindableBase::~BindableBase()
{
	OnDisposing();

	EventFunc::RemoveEvent(&disposing, NULL);

	if (changedProperties)
		Listable::RemoveAll((Listable**)&changedProperties);

	EventFunc::RemoveEvent(&propertyChanged, NULL);
}

void BindableBase::OnDisposing()
{
	EventArgs evInfo;
	EventFunc::FireEvents(disposing, this, &evInfo);
}

void BindableBase::AddDisposingEvent(void(*func)(void*, EventArgs*), void *tag)
{
	EventFunc *ef = new EventFunc();
	ef->func = (void(*)(void*, EventArgs*))func;
	ef->tag = tag;
	Listable::Add(ef, (Listable**)&disposing);
}

void BindableBase::RemoveDisposingEvent(void(*func)(void*, EventArgs*), void *tag)
{
	EventFunc *node;
	EventFunc *next;
	for (node = disposing; node; node = next)
	{
		next = (EventFunc*)node->next;

		if (node->func == func && node->tag == tag)
			Listable::Remove(node, (Listable**)&disposing);
	}
}

void BindableBase::AddPropertyChangedEvent(void(*func)(void*, PropertyChangedEventArgs*), void *tag)
{
	EventFunc *ef = new EventFunc();
	ef->func = (void(*)(void*, EventArgs*))func;
	ef->tag = tag;
	Listable::Add(ef, (Listable**)&propertyChanged);
}

//
// RemovePropertyChangedEvent
//
void BindableBase::RemovePropertyChangedEvent(void(*func)(void*, PropertyChangedEventArgs*), void *tag)
{
	if (tag)
		EventFunc::RemoveEventWithTag(&propertyChanged, (void*)func, tag);
	else
		EventFunc::RemoveEvent(&propertyChanged, (void*)func);
}

bool BindableBase::ContainsChangedProperty(const char *name)
{
	ChangedProperty *node;
	for (node = changedProperties; node; node = (ChangedProperty*)node->next)
	{
		if (!strcmp(node->GetName(), name))
			return true;
	}

	return false;
}

void BindableBase::OnPropertyChanged(const char *propertyName)
{
	PropertyChangedEventArgs evInfo(propertyName);
	EventFunc::FireEvents(propertyChanged, this, &evInfo);

	if (!trackChanges || ContainsChangedProperty(propertyName))
		return;

	// Doesn't exist already.
	ChangedProperty *cp = new ChangedProperty(propertyName);
	Listable::Add(cp, (Listable**)&changedProperties);
}

void BindableBase::ClearChangedProperties()
{
	Listable::RemoveAll((Listable**)&changedProperties);
}

void BindableBase::SerializeProperties(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.Key("ChangedProperties");
	writer.StartArray();
	ChangedProperty *node;
	for (node = changedProperties; node; node = (ChangedProperty*)node->next)
		node->Serialize(writer);
	writer.EndArray();
}

void BindableBase::DeserializeProperty(const char *propertyName, rapidjson::Value::ConstMemberIterator itr)
{
	if (!strcmp(propertyName, "ChangedProperties"))
	{
		size_t i;
		for (i = 0; i < itr->value.Size(); i++)
		{
			ChangedProperty *item = new ChangedProperty(itr->value[i]);
			Listable::Add(item, (Listable**)&changedProperties);
		}
	}
}
