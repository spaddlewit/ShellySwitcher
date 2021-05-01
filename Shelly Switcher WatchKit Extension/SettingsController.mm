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

#import "SettingsController.h"
#import "DeviceRowController.h"
#import "DataFileManager.hpp"

@implementation SettingsController

- (void)awakeWithContext:(id)context {
    [super awakeWithContext:context];

    // Configure interface objects here.
    
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    [super willActivate];
    [self refreshList];
}

- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}

- (void)refreshList {
    
    unsigned long rowCount = Listable::GetCount(shellyList);
    [self.tblDevices setNumberOfRows:rowCount withRowType:@"deviceRowType2"];

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
}

- (void)table:(WKInterfaceTable *)table didSelectRowAtIndex:(NSInteger)rowIndex {
    
    ShellyItem *item = (ShellyItem*)Listable::GetByIndex(shellyList, (unsigned int)rowIndex);
    
    if (item == NULL)
        return;
    
    currentShelly = item;
    
    // Ask 'Do you wish to remove GetName()?
    NSString *prompt = [NSString stringWithFormat:@"Do you wish to remove %s?", item->GetName()];
    [self presentAlertControllerWithTitle:nil message:prompt preferredStyle:WKAlertControllerStyleAlert actions:@[
        [WKAlertAction actionWithTitle: @"Yes"
                       style: WKAlertActionStyleDefault
                       handler: ^{
            //something after clicking OK
            Listable::Remove(item, (Listable**)&shellyList);
            currentShelly = NULL;
            SaveSettings();
            [self refreshList];
                       }
     ],
     [WKAlertAction actionWithTitle: @"No"
                    style: WKAlertActionStyleDefault
                    handler: ^{
         //something after clicking OK
                    }
      ]]
     ];
}

@end
