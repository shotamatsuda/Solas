//
//  SLSCADisplayLink.mm
//
//  The MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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

#include <chrono>

@interface SLSDisplayLink () {
 @private
  std::chrono::system_clock::time_point _accumulator;
  std::chrono::microseconds _interval;
}

@property (nonatomic, retain) id target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, strong) CADisplayLink *link;

- (void)callback:(CADisplayLink *)sender;

@end

@implementation SLSDisplayLink

- (instancetype)initWithTarget:(id)target selector:(SEL)selector {
  self = [super init];
  if (self) {
    _target = target;
    _selector = selector;
    _link = [CADisplayLink displayLinkWithTarget:self
                                        selector:@selector(callback:)];
  }
  return self;
}

+ (SLSDisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)selector {
  return [[self alloc] initWithTarget:target selector:selector];
}

- (void)dealloc {
  [self stop];
}

#pragma mark Controlling the Display Link

- (void)setFrameRate:(double)frameRate {
  if (frameRate != _frameRate) {
    _frameRate = frameRate;
    _interval = std::chrono::microseconds(
        static_cast<std::chrono::microseconds::rep>(
            std::chrono::microseconds::period::den / frameRate));
  }
}

- (void)start {
  _accumulator = std::chrono::system_clock::now();
  [_link addToRunLoop:[NSRunLoop mainRunLoop]
              forMode:NSRunLoopCommonModes];
}

- (void)stop {
  [_link removeFromRunLoop:[NSRunLoop mainRunLoop]
                   forMode:NSRunLoopCommonModes];
}

- (void)callback:(CADisplayLink *)sender {
  if (_interval == std::chrono::microseconds::zero()) {
    [self.target performSelector:self.selector
                        onThread:[NSThread currentThread]
                      withObject:nil
                   waitUntilDone:YES];
  } else {
    const auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now() - _accumulator);
    if (elapsed > _interval) {
      [self.target performSelector:self.selector
                          onThread:[NSThread currentThread]
                        withObject:nil
                     waitUntilDone:YES];
      _accumulator += _interval * (elapsed / _interval);
    }
  }
}

@end
