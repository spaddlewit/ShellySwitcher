/*
'Wizard2' engine by Spaddlewit Inc. ( http://www.spaddlewit.com )
An experimental work-in-progress.

This source code is NOT freeware.
It should be distributed to authorized users only.

Your use of this code is governed by your licensing agreement.

*/
#include "ChangedProperty.h"

const char *ChangedProperty::GetName() const
{
	return name;
}

void ChangedProperty::SetName(const char *propertyName)
{
	if (name)
		free(name);

	name = strdup(propertyName);
}

ChangedProperty::ChangedProperty(const char *propertyName) : Listable()
{
	SetName(propertyName);
}

ChangedProperty::ChangedProperty(const rapidjson::Value & v)
{
	Deserialize(v);
}

ChangedProperty::~ChangedProperty()
{
	if (name)
		free(name);
}

using namespace rapidjson;
static void WriteString(Writer<StringBuffer>& writer, const char *value)
{
	if (!value)
		writer.Null();
	else
		writer.String(value);
}

void ChangedProperty::Serialize(Writer<StringBuffer>& writer) const
{
/*	writer.StartObject();

	writer.Key("Name");*/
	WriteString(writer, GetName());

/*	writer.EndObject();*/
}

char *ChangedProperty::Serialize() const
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);

	Serialize(writer);

	return strdup(buffer.GetString());
}

void ChangedProperty::Deserialize(const rapidjson::Value& v)
{
	SetName(v.GetString());
}

void ChangedProperty::Deserialize(const char *json)
{
	Document doc;
	doc.Parse(json);

	Deserialize(doc);
}
