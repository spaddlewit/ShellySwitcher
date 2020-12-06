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

#import "ComplicationController.h"

@implementation ComplicationController

#pragma mark - Complication Configuration

- (void)getComplicationDescriptorsWithHandler:(void (^)(NSArray<CLKComplicationDescriptor *> * _Nonnull))handler {
    NSArray<CLKComplicationDescriptor *> *descriptors = @[
        [[CLKComplicationDescriptor alloc] initWithIdentifier:@"complication"
                                                  displayName:@"Shelly Switcher"
                                            supportedFamilies:CLKAllComplicationFamilies()]
        // Multiple complication support can be added here with more descriptors
    ];
    
    // Call the handler with the currently supported complication descriptors
    handler(descriptors);
}

- (void)handleSharedComplicationDescriptors:(NSArray<CLKComplicationDescriptor *> *)complicationDescriptors {
    // Do any necessary work to support these newly shared complication descriptors
}

#pragma mark - Timeline Configuration

- (void)getTimelineEndDateForComplication:(CLKComplication *)complication withHandler:(void(^)(NSDate * __nullable date))handler {
    // Call the handler with the last entry date you can currently provide or nil if you can't support future timelines
    handler(nil);
}

- (void)getPrivacyBehaviorForComplication:(CLKComplication *)complication withHandler:(void(^)(CLKComplicationPrivacyBehavior privacyBehavior))handler {
    // Call the handler with your desired behavior when the device is locked
    handler(CLKComplicationPrivacyBehaviorShowOnLockScreen);
}

#pragma mark - Timeline Population

- (void)getCurrentTimelineEntryForComplication:(CLKComplication *)complication withHandler:(void(^)(CLKComplicationTimelineEntry * __nullable))handler {
    // Call the handler with the current timeline entry
    if (complication.family == CLKComplicationFamilyModularSmall)
    {
        UIImage *iconImage = [UIImage imageNamed:@"SwitchOn"];
        CLKComplicationTemplateModularSmallSimpleImage *clkSI = [[CLKComplicationTemplateModularSmallSimpleImage alloc] initWithImageProvider:[[CLKImageProvider alloc] initWithOnePieceImage:iconImage]];

        CLKComplicationTimelineEntry *entry = [CLKComplicationTimelineEntry entryWithDate:[NSDate date] complicationTemplate:clkSI];
        handler(entry);
    }
    else if (complication.family == CLKComplicationFamilyGraphicCircular)
    {
        UIImage *iconImage = [UIImage imageNamed:@"SwitchOn"];
        CLKComplicationTemplateGraphicCircularImage *clkSI = [[CLKComplicationTemplateGraphicCircularImage alloc] initWithImageProvider:[[CLKFullColorImageProvider alloc] initWithFullColorImage: iconImage]];
                                                              
        CLKComplicationTimelineEntry *entry = [CLKComplicationTimelineEntry entryWithDate:[NSDate date] complicationTemplate:clkSI];
        handler(entry);
    }
    else
        handler(nil);
}
/*
- (void)getTimelineEntriesForComplication:(CLKComplication *)complication afterDate:(NSDate *)date limit:(NSUInteger)limit withHandler:(void(^)(NSArray<CLKComplicationTimelineEntry *> * __nullable entries))handler {
    // Call the handler with the timeline entries after the given date
    handler(nil);
}
*/
#pragma mark - Sample Templates

- (void)getLocalizableSampleTemplateForComplication:(CLKComplication *)complication withHandler:(void(^)(CLKComplicationTemplate * __nullable complicationTemplate))handler {
    // This method will be called once per supported complication, and the results will be cached
    
    if (complication.family == CLKComplicationFamilyModularSmall)
    {
        UIImage *iconImage = [UIImage imageNamed:@"SwitchOn"];
        CLKComplicationTemplateModularSmallSimpleImage *clkSI = [[CLKComplicationTemplateModularSmallSimpleImage alloc] initWithImageProvider:[[CLKImageProvider alloc] initWithOnePieceImage:iconImage]];
        handler(clkSI);
    }
    else if (complication.family == CLKComplicationFamilyGraphicCircular)
    {
        UIImage *iconImage = [UIImage imageNamed:@"SwitchOn"];
        CLKComplicationTemplateGraphicCircularImage *clkSI = [[CLKComplicationTemplateGraphicCircularImage alloc] initWithImageProvider:[[CLKFullColorImageProvider alloc] initWithFullColorImage: iconImage]];
        handler(clkSI);
    }
    else
        handler(nil);
}

@end
