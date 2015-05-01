//
//  SLSDisplayLink.h
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

#import <Foundation/Foundation.h>

@interface SLSDisplayLink : NSObject

- (instancetype)initWithTarget:(id)target selector:(SEL)selector;
+ (SLSDisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)selector;

#pragma mark Controlling the Display Link

- (void)start;
- (void)stop;

@end
