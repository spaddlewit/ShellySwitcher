//
//  AboutController.h
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/1/20.
//

#import <Foundation/Foundation.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface AddDeviceController : WKInterfaceController
@property (weak, nonatomic) IBOutlet WKInterfaceTextField *txtIPAddress;
@property (weak, nonatomic) IBOutlet WKInterfaceTextField *txtDisplayName;
@property (weak, nonatomic) IBOutlet WKInterfacePicker *pkrDeviceType;
@property (weak, nonatomic) IBOutlet WKInterfaceButton *btnAddDevice;

@end

NS_ASSUME_NONNULL_END
