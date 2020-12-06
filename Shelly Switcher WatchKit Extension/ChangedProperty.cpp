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
