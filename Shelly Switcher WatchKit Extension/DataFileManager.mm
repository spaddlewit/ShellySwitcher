//
//  DataFileManager.cpp
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/4/20.
//

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
