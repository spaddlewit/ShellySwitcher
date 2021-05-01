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

#import <Foundation/Foundation.h>
#import <WatchKit/WatchKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface AddDeviceController : WKInterfaceController
@property (weak, nonatomic) IBOutlet WKInterfaceTextField *txtIPAddress;
@property (weak, nonatomic) IBOutlet
    WKInterfaceTextField *txtPort;
@property (weak, nonatomic) IBOutlet WKInterfaceTextField *txtDisplayName;
@property (weak, nonatomic) IBOutlet WKInterfacePicker *pkrDeviceType;
@property (weak, nonatomic) IBOutlet WKInterfaceButton *btnAddDevice;

@end

NS_ASSUME_NONNULL_END
