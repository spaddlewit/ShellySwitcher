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

#include "DataFileManager.hpp"
#import <Foundation/Foundation.h>
#include "TableHelper.h"

ShellyItem *shellyList = NULL;
ShellyItem *currentShelly = NULL;

using namespace rapidjson;

void LoadSettings()
{
    Listable::RemoveAll((Listable**)&shellyList);
    NSString *nsShellyListJSON = [NSUserDefaults.standardUserDefaults objectForKey:@"DeviceData"];
    
    if (nsShellyListJSON != nil)
    {
        const char *json = [nsShellyListJSON UTF8String];
        Document doc;
        doc.Parse(json);
        
        if (doc.IsObject())
        {
            for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
            {
                const char *name = itr->name.GetString();
                
                if (!strcmp(name, "Devices"))
                    shellyList = TableHelper<ShellyItem>::DeserializeList(itr->value);
            }
        }
    }
}

void SaveSettings()
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    
    writer.StartObject();
    writer.Key("Devices");
    TableHelper<ShellyItem>::SerializeList(writer, shellyList);
    
    writer.EndObject();
    
    NSString *writeString = [NSString stringWithUTF8String:buffer.GetString()];
    [NSUserDefaults.standardUserDefaults setObject:writeString forKey:@"DeviceData"];
}
