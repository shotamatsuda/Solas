//
//  SLSCADisplayLink.m
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
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
