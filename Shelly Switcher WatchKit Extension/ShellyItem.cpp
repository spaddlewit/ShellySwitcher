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

#include "ShellyItem.hpp"
#include "u_string.h"

const char *ShellyItem::GetAddress() const
{
    return _address;
}

void ShellyItem::SetAddress(const char *value)
{
    CHANGEDPROPERTYSTRING(_address, value, "Address");
}

int ShellyItem::GetPort() const
{
    return _port;
}

void ShellyItem::SetPort(int value)
{
    CHANGEDPROPERTY(_port, value, "Port");
}

const char *ShellyItem::GetName() const
{
    return _name;
}

void ShellyItem::SetName(const char *value)
{
    CHANGEDPROPERTYSTRING(_name, value, "Name");
}

const char *ShellyItem::GetType() const
{
    return _type;
}

void ShellyItem::SetType(const char *value)
{
    CHANGEDPROPERTYSTRING(_type, value, "Type");
}

void ShellyItem::SetProperty(const char *propertyName, const char *value)
{
    if (!strcmp(propertyName, "Address"))
    {
        SetAddress(value);
    }
    else if (!strcmp(propertyName, "Name"))
    {
        SetName(value);
    }
    else if (!strcmp(propertyName, "Type"))
    {
        SetType(value);
    }
}

char *ShellyItem::ToString(const char *propertyName) const
{
    if (!strcmp(propertyName, "Address"))
        return strdup(GetAddress());
    else if (!strcmp(propertyName, "Port"))
    {
        char *ret = (char*)malloc(sizeof(char) * 16);
        sprintf(ret, "%d", GetPort());
        return ret;
    }
    else if (!strcmp(propertyName, "Name"))
        return strdup(GetName());
    else if (!strcmp(propertyName, "Type"))
        return strdup(GetType());

    return BindableBase::ToString(propertyName);
}

using namespace rapidjson;
static void WriteString(Writer<StringBuffer>& writer, const char *value)
{
    if (!value)
        writer.Null();
    else
        writer.String(value);
}

void ShellyItem::Serialize(Writer<StringBuffer>& writer) const
{
    writer.StartObject();

    writer.Key("Address");
    WriteString(writer, GetAddress());
    writer.Key("Port");
    writer.Int(GetPort());
    writer.Key("Name");
    WriteString(writer, GetName());
    writer.Key("Type");
    WriteString(writer, GetType());

    writer.EndObject();
}

char *ShellyItem::Serialize() const
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);

    Serialize(writer);

    return strdup(buffer.GetString());
}

void ShellyItem::Deserialize(const rapidjson::Value& v)
{
    if (!v.IsObject())
        return;

    trackChanges = false;

    for (Value::ConstMemberIterator itr = v.MemberBegin(); itr != v.MemberEnd(); itr++)
    {
        const char *name = itr->name.GetString();

        if (!strcmp(name, "Address"))
            SetAddress(itr->value.GetString());
        else if (!strcmp(name, "Port"))
            SetPort(itr->value.GetInt());
        else if (!strcmp(name, "Name"))
            SetName(itr->value.GetString());
        else if (!strcmp(name, "Type"))
            SetType(itr->value.GetString());

        else
            BindableBase::DeserializeProperty(name, itr);
    }

    trackChanges = true;
}

void ShellyItem::Deserialize(const char *json)
{
    Document doc;
    doc.Parse(json);

    Deserialize(doc);
}

ShellyItem::ShellyItem() : BindableBase()
{
}

ShellyItem::ShellyItem(const char *json) : BindableBase()
{
    Deserialize(json);
}

ShellyItem::ShellyItem(const rapidjson::Value& v) : BindableBase()
{
    Deserialize(v);
}

ShellyItem::~ShellyItem()
{
    if (_address)
        free(_address);

    if (_name)
        free(_name);

    if (_type)
        free(_type);
}

