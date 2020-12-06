//
//  InterfaceController.m
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 11/30/20.
//

#import "InterfaceController.h"
#import "DeviceRowController.h"
#import "DataFileManager.hpp"


@interface InterfaceController ()

@end


@implementation InterfaceController

- (void)awakeWithContext:(id)context {
    // Configure interface objects here.
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [self refreshList];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
}
- (IBAction)tapSettings:(id)sender {
    [self presentControllerWithName:@"icSettingsController" context:nil];
}
- (IBAction)tapAbout:(id)sender {
    [self presentControllerWithName:@"icAboutController" context:nil];
}

/*
 NSError *error;
 NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictionaryOrArrayToOutput
                                                    options:NSJSONWritingPrettyPrinted // Pass 0 if you don't care about the readability of the generated string
                                                      error:&error];

 if (! jsonData) {
     NSLog(@"Got an error: %@", error);
 } else {
     NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
 }
 */

/*
 [NSJSONSerialization JSONObjectWithData:options:error:]
 */

- (void)refreshList {
    
    unsigned long rowCount = Listable::GetCount(shellyList);
    [self.tblDevices setNumberOfRows:rowCount withRowType:@"deviceRowType1"];

    rowCount = (unsigned int)self.tblDevices.numberOfRows;
        
    // Iterate over the rows and set the label and image for each one.
    for (int i = 0; i < rowCount; i++) {
        // Set the values for the row controller
        DeviceRowController *row = (DeviceRowController*)[self.tblDevices rowControllerAtIndex:i];
        
        const ShellyItem *item = (ShellyItem*)Listable::GetByIndex(shellyList, i);
        if (item)
        {
            [row configureWithItem:item atIndex:i];
        }
    }
    
    if (rowCount == 0)
        [self.lblNoDevices setHidden:NO];
    else
        [self.lblNoDevices setHidden:YES];
}

- (void)table:(WKInterfaceTable *)table didSelectRowAtIndex:(NSInteger)rowIndex {
    
    ShellyItem *item = (ShellyItem*)Listable::GetByIndex(shellyList, (unsigned int)rowIndex);
    
    if (item == NULL)
        return;
    
    currentShelly = item;
    
    [self presentControllerWithName:@"icSwitchController" context:nil];
}

@end



