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
#include "rapidjson/rapidjson.h"

template <class T>
struct TableHelper
{

public:

	static void SerializeList(rapidjson::Writer<rapidjson::StringBuffer> &writer, T *list, bool changesOnly = false)
	{
		writer.StartArray();
		T *node;
		for (node = list; node; node = (T*)node->next)
		{
			if (!changesOnly || Listable::GetCount(node->changedProperties) > 0)
				node->Serialize(writer);
		}
		writer.EndArray();
	}

	static T *DeserializeList(const rapidjson::Value& v)
	{
		T *list = NULL;

		rapidjson::SizeType i;
		for (i = 0; i < v.Size(); i++)
		{
			T *item = new T(v[i]);
			Listable::Add(item, (Listable**)&list);
		}

		return list;
	}

	static T *DeserializeList(const char *json)
	{
		rapidjson::Document doc;
		doc.Parse(json);

		return DeserializeList(doc);
	}
};
