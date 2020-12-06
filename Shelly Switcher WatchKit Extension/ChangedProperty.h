/*
'Wizard2' engine by Spaddlewit Inc. ( http://www.spaddlewit.com )
An experimental work-in-progress.

This source code is NOT freeware.
It should be distributed to authorized users only.

Your use of this code is governed by your licensing agreement.

*/
#pragma once
#include "Listable.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

struct ChangedProperty : Listable
{
private:
	char *name;

public:
	const char *GetName() const;
	void SetName(const char *propertyName);

	char *Serialize() const;
	void Serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
	void Deserialize(const char *json);
	void Deserialize(const rapidjson::Value& v);

	ChangedProperty(const char *propertyName);
	ChangedProperty(const rapidjson::Value& v);
	virtual ~ChangedProperty();
};
