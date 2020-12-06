//
//  ShellyItem.cpp
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/4/20.
//

#include "ShellyItem.hpp"

const char *ShellyItem::GetAddress() const
{
    return _address;
}

void ShellyItem::SetAddress(const char *value)
{
    CHANGEDPROPERTYSTRING(_address, value, "Address");
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

