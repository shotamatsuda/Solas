//
//  SLSNSViewController.h
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

#import "SLSAnimationSource.h"
#import "SLSDisplaySource.h"
#import "SLSEventSource.h"
#import "SLSRunner.h"

@interface SLSNSViewController : NSViewController <SLSAnimationSource>

- (instancetype)initWithRunner:(SLSRunner *)runner NS_DESIGNATED_INITIALIZER;

#pragma mark Accessing Views

@property (nonatomic, weak) id<SLSEventSource> eventSource;
@property (nonatomic, weak) id<SLSDisplaySource> displaySource;

#pragma mark Managing the Runner

@property (nonatomic, strong) SLSRunner *runner;

@end
