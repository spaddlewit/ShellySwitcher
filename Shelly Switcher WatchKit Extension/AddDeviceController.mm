//
//  AboutController.m
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/1/20.
//

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
NSString *displayName;
NSInteger deviceTypeIndex = -1;

- (IBAction)ipAddressEntered:(NSString *)value {
    ipAddress = value;
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
    item->SetName([displayName UTF8String]);
    
    WKPickerItem *deviceType = [deviceTypeItems objectAtIndex:deviceTypeIndex];
    
    item->SetType([deviceType.title UTF8String]);
    Listable::Add(item, (Listable**)&shellyList);
    
    SaveSettings();
    
    [self dismissController];
}

@end
