//
//  InterfaceController.h
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 11/30/20.
//

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>

@interface InterfaceController : WKInterfaceController

@property (weak, nonatomic) IBOutlet WKInterfaceTable* tblDevices;
@property (weak, nonatomic) IBOutlet WKInterfaceImage* imgSettings;
@property (weak, nonatomic) IBOutlet WKInterfaceImage* imgAbout;
@property (weak, nonatomic) IBOutlet WKInterfaceLabel *lblNoDevices;

-(void)refreshList;

@end
