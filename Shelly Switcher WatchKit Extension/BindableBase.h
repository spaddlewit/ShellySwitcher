#pragma once
#include "Listable.h"
#include "ChangedProperty.h"
#include "Events.h"
#include "u_string.h"

#define CHANGEDPROPERTY(x, y, z) { if (x != y) { x = y; OnPropertyChanged(z); } }
#define CHANGEDPROPERTYSTRING(x, y, z) { if (x != y) { if (x) free(x); x = ((!y) ? NULL : strdup(y)); OnPropertyChanged(z); } }
#define CHANGEDPROPERTYMEM(x, y, z, a) { if (x) free(x); x = ((!y) ? NULL : (decltype(x))memdup(y, a)); OnPropertyChanged(z); }

struct PropertyChangedEventArgs : EventArgs
{
	char propertyName[256];

	PropertyChangedEventArgs(const char *propertyName) : EventArgs()
	{
		utf8cpy(this->propertyName, propertyName, 256);
	}
};

struct BindableBase : Listable
{
protected:
	EventFunc *propertyChanged;

public:
	EventFunc *disposing;
	ChangedProperty *changedProperties;

	bool trackChanges;

	void AddPropertyChangedEvent(void(*func)(void*, PropertyChangedEventArgs*), void *tag = NULL);
	void RemovePropertyChangedEvent(void(*func)(void*, PropertyChangedEventArgs*), void *tag = NULL);

	virtual void OnDisposing();
	virtual void OnPropertyChanged(const char *propertyName);

	void AddDisposingEvent(void(*func)(void*, EventArgs*), void *tag = NULL);
	void RemoveDisposingEvent(void(*func)(void*, EventArgs*), void *tag = NULL);

	bool ContainsChangedProperty(const char *name);
	void ClearChangedProperties();

	void SerializeProperties(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
	void DeserializeProperty(const char *propertyName, rapidjson::Value::ConstMemberIterator itr);

	virtual void SetProperty(const char *propertyName, const char *value) = 0;
	virtual char *ToString(const char *propertyName) const
	{
		return strdup("");
	}

	BindableBase();
	virtual ~BindableBase();
};
