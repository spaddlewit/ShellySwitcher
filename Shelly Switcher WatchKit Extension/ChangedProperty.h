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
