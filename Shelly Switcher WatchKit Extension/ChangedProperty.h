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
