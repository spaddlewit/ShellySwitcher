//
//  DeviceRowController.h
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/1/20.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WatchKit.h>
#import "ShellyItem.hpp"

NS_ASSUME_NONNULL_BEGIN

@interface DeviceRowController : NSObject

@property (weak, nonatomic) IBOutlet WKInterfaceLabel* lblName;

- (void)configureWithItem:(const ShellyItem*)item atIndex:(NSUInteger)index;

@end

NS_ASSUME_NONNULL_END
