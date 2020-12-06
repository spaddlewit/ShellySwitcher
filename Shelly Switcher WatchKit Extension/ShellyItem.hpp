#pragma once
#include "BindableBase.h"
#include "rapidjson/rapidjson.h"

struct ShellyItem : BindableBase
{
    // Start Properties
    char *_address;
    char *_name;
    char *_type;
    // End Properties

    const char *GetAddress() const;
    void SetAddress(const char *value);
    const char *GetName() const;
    void SetName(const char *value);
    const char *GetType() const;
    void SetType(const char *value);

    void SetProperty(const char *propertyName, const char *value);
    virtual char *ToString(const char *propertyName) const;

    char *Serialize() const;
    void Serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
    void Deserialize(const char *json);
    void Deserialize(const rapidjson::Value& v);

    ShellyItem();
    ShellyItem(const char *json);
    ShellyItem(const rapidjson::Value& v);
    virtual ~ShellyItem();
};
