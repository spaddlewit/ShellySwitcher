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

#import "AddDeviceController.h"
#import "DataFileManager.hpp"

@implementation AddDeviceController

NSMutableArray *deviceTypeItems;

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];

    // Configure interface objects here.
    deviceTypeItems = [[NSMutableArray alloc] init];
    
    WKPickerItem *item = [[WKPickerItem alloc] init];
    item.title = @"Shelly 1";
    [deviceTypeItems addObject: item];
    item = [[WKPickerItem alloc] init];
    item.title = @"Shelly 1PM";
    [deviceTypeItems addObject: item];
    item = [[WKPickerItem alloc] init];
    item.title = @"Shelly 2.5 Sw1";
    [deviceTypeItems addObject: item];
    item = [[WKPickerItem alloc] init];
    item.title = @"Shelly 2.5 Sw2";
    [deviceTypeItems addObject: item];
    
    [self.pkrDeviceType setItems:deviceTypeItems];
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

NSString *ipAddress;
int port;
NSString *displayName;
NSInteger deviceTypeIndex = 0;

- (IBAction)ipAddressEntered:(NSString *)value {
    ipAddress = value;
}
- (IBAction)portEntered:(NSString *)value {
    port = [value intValue];
}
- (IBAction)displayNameEntered:(NSString *)value {
    displayName = value;
}
- (IBAction)deviceTypeEntered:(NSInteger)value {
    deviceTypeIndex = value;
}

- (IBAction)addDevice {
    if (ipAddress == nil || displayName == nil || deviceTypeIndex < 0)
    {
        [self presentAlertControllerWithTitle:nil message:@"All fields must be completed." preferredStyle:WKAlertControllerStyleAlert actions:@[
            [WKAlertAction actionWithTitle: @"OK"
                           style: WKAlertActionStyleDefault
                           handler: ^{
                              //something after clicking OK
                           }
         ]]];
        return;
    }
        
    ShellyItem *item = new ShellyItem();
    item->SetAddress([ipAddress UTF8String]);
    item->SetPort(port);
    item->SetName([displayName UTF8String]);
    
    WKPickerItem *deviceType = [deviceTypeItems objectAtIndex:deviceTypeIndex];
    
    item->SetType([deviceType.title UTF8String]);
    Listable::Add(item, (Listable**)&shellyList);
    
    SaveSettings();
    
    [self dismissController];
}

@end
