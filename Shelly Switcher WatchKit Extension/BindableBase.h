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
