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
