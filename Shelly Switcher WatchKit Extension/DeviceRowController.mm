//
//  DeviceRowController.m
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/1/20.
//

#import "DeviceRowController.h"

@implementation DeviceRowController

- (void)configureWithItem:(const ShellyItem*)item atIndex:(NSUInteger)index
{
    [self.lblName setText:[NSString stringWithUTF8String:item->GetName()]];
}

@end
