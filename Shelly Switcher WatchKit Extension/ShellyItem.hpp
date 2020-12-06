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
