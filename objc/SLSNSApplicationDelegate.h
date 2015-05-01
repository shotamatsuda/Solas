//
//  SLSNSApplicationDelegate.h
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//
//  All information contained herein is, and remains the property of takram
//  design engineering and its suppliers, if any. The intellectual and
//  technical concepts contained herein are proprietary to takram design
//  engineering and its suppliers and may be covered by U.S. and Foreign
//  Patents, patents in process, and are protected by trade secret or copyright
//  law. Dissemination of this information or reproduction of this material is
//  strictly forbidden unless prior written permission is obtained from takram
//  design engineering.
//

#import <AppKit/AppKit.h>

@interface SLSNSApplicationDelegate : NSObject <
    NSApplicationDelegate, NSUserInterfaceValidations>

#pragma mark Window Controllers

@property (nonatomic, strong, readonly) NSArray *windowControllers;

#pragma mark Received Actions

- (IBAction)newWindow:(id)sender;

@end
