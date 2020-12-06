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
