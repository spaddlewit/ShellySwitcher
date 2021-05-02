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

#import "SwitchController.h"
#import "DataFileManager.hpp"

@implementation SwitchController

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];

    // Configure interface objects here.
    
}

static void runOnMainThread(void (^block)(void))
{
    if (!block) return;

    if ( [[NSThread currentThread] isMainThread] ) {
        block();
    } else {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}

using namespace rapidjson;

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
    
    NSString *address = @"http://";
    address = [address stringByAppendingString:[NSString stringWithUTF8String:currentShelly->GetAddress()]];
    if (currentShelly->GetPort() > 0 && currentShelly->GetPort() != 80)
        address = [address stringByAppendingString:[NSString stringWithFormat:@":%d", currentShelly->GetPort()]];
    
    if (!strcmp(currentShelly->GetType(), "Shelly 2.5 Sw2"))
        address = [address stringByAppendingString:@"/relay/1"];
    else
        address = [address stringByAppendingString:@"/relay/0"];
    
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:address]];
    [req setHTTPMethod:@"GET"];
    
    [req addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
            
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask *task = [session dataTaskWithRequest:req completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error)
    {
        // Call is complete and data has been received
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse*)response;
        if (httpResponse.statusCode == 200)
        {
            NSString* nsJson = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            const char *json = [nsJson cStringUsingEncoding:NSUTF8StringEncoding];
            rapidjson::Document doc;
            doc.Parse(json);
            
            // TODO: Create a response object to deserialize into.
            if (doc.IsObject())
            {
                for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
                {
                    const char *name = itr->name.GetString();

                    if (!strcmp(name, "ison"))
                    {
                        if (itr->value.GetBool())
                        {
                            // TODO: If Shelly1 PM, display wattage in use
                            runOnMainThread(^{
                                [self.btnSwitch setBackgroundImageNamed:@"SwitchOn"];
                            });
                        }
                        else
                        {
                            runOnMainThread(^{
                                [self.btnSwitch setBackgroundImageNamed:@"SwitchOff"];
                            });
                        }
                    }
                }
            }
        }
        else
        {
            
        }
    }];
    
    [task resume];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

- (IBAction)toggleSwitch {
    
    //http://192.168.xxx.xxx:80/relay/0?turn=on
    NSString *address = @"http://";
    address = [address stringByAppendingString:[NSString stringWithUTF8String:currentShelly->GetAddress()]];
    if (currentShelly->GetPort() > 0 && currentShelly->GetPort() != 80)
        address = [address stringByAppendingString:[NSString stringWithFormat:@":%d", currentShelly->GetPort()]];
    
    if (!strcmp(currentShelly->GetType(), "Shelly 2.5 Sw2"))
        address = [address stringByAppendingString:@"/relay/1?turn=toggle"];
    else
        address = [address stringByAppendingString:@"/relay/0?turn=toggle"];
    
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:address]];
    [req setHTTPMethod:@"GET"];
    
    [req addValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
            
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask *task = [session dataTaskWithRequest:req completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error)
    {
        // Call is complete and data has been received
        NSHTTPURLResponse *httpResponse = (NSHTTPURLResponse*)response;
        if (httpResponse.statusCode == 200)
        {
            NSString* nsJson = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
            const char *json = [nsJson cStringUsingEncoding:NSUTF8StringEncoding];
            rapidjson::Document doc;
            doc.Parse(json);
            
            if (doc.IsObject())
            {
                for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
                {
                    const char *name = itr->name.GetString();

                    if (!strcmp(name, "ison"))
                    {
                        if (itr->value.GetBool())
                        {
                            // TODO: If Shelly1 PM, display wattage in use
                            runOnMainThread(^{
                                [self.btnSwitch setBackgroundImageNamed:@"SwitchOn"];
                            });
                        }
                        else
                        {
                            runOnMainThread(^{
                                [self.btnSwitch setBackgroundImageNamed:@"SwitchOff"];
                            });
                        }
                    }
                }
            }
        }
        else
        {
            
        }
    }];
    
    [task resume];
}

@end
