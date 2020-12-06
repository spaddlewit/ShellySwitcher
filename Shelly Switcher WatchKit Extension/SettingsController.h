//
//  SettingsController.h
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 11/30/20.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SettingsController : WKInterfaceController

@property (weak, nonatomic) IBOutlet WKInterfaceTable* tblDevices;
@property (weak, nonatomic) IBOutlet WKInterfaceButton* btnAdd;

@end

NS_ASSUME_NONNULL_END
