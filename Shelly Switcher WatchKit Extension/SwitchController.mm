//
//  SwitchController.m
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 11/30/20.
//

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
            
            if (doc.IsObject())
            {
                for (Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
                {
                    const char *name = itr->name.GetString();

                    if (!strcmp(name, "ison"))
                    {
                        if (itr->value.GetBool())
                        {
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
    
    //http://192.168.xxx.xxx/relay/0?turn=on
    NSString *address = @"http://";
    address = [address stringByAppendingString:[NSString stringWithUTF8String:currentShelly->GetAddress()]];
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
