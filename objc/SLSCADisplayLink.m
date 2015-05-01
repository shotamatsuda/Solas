//
//  SLSCADisplayLink.m
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

#import "SLSDisplayLink.h"

#import <QuartzCore/QuartzCore.h>

@interface SLSDisplayLink ()

@property (nonatomic, retain) id target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, strong) CADisplayLink *link;

@end

@implementation SLSDisplayLink

- (instancetype)initWithTarget:(id)target selector:(SEL)selector {
  self = [super init];
  if (self) {
    _target = target;
    _selector = selector;
    _link = [CADisplayLink displayLinkWithTarget:target selector:selector];
    _link.frameInterval = 1;
  }
  return self;
}

+ (SLSDisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)selector {
  return [[self alloc] initWithTarget:target selector:selector];
}

- (void)dealloc {
  [self stop];
}

- (void)start {
  [_link addToRunLoop:[NSRunLoop mainRunLoop]
              forMode:NSRunLoopCommonModes];
}

- (void)stop {
  [_link removeFromRunLoop:[NSRunLoop mainRunLoop]
                   forMode:NSRunLoopCommonModes];
}

@end
