//
//  SwitchController.h
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 11/30/20.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SwitchController : WKInterfaceController

@property (weak, nonatomic) IBOutlet WKInterfaceButton* btnSwitch;

@end

NS_ASSUME_NONNULL_END
