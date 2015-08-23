//
//  SLSCVDisplayLink.mm
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
@property (nonatomic, assign) CVDisplayLinkRef link;

@end

@implementation SLSDisplayLink

static CVReturn DisplayLinkCallback(
    CVDisplayLinkRef displayLinkRef,
    const CVTimeStamp *now,
    const CVTimeStamp *outputTime,
    CVOptionFlags flagsIn,
    CVOptionFlags *flagsOut,
    void *userInfo);

- (instancetype)initWithTarget:(id)target selector:(SEL)selector {
  self = [super init];
  if (self) {
    _target = target;
    _selector = selector;
    CVDisplayLinkCreateWithActiveCGDisplays(&_link);
    CVDisplayLinkSetOutputCallback(
        _link, &DisplayLinkCallback, (__bridge void *)self);
  }
  return self;
}

+ (SLSDisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)selector {
  return [[self alloc] initWithTarget:target selector:selector];
}

- (void)dealloc {
  if (_link) {
    if (CVDisplayLinkIsRunning(_link)) {
      CVDisplayLinkStop(_link);
    }
    CVDisplayLinkRelease(_link);
    _link = NULL;
  }
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
  CVDisplayLinkStart(_link);
}

- (void)stop {
  CVDisplayLinkStop(_link);
}

CVReturn DisplayLinkCallback(
    CVDisplayLinkRef displayLinkRef,
    const CVTimeStamp *now,
    const CVTimeStamp *outputTime,
    CVOptionFlags flagsIn,
    CVOptionFlags *flagsOut,
    void *userInfo) {
  @autoreleasepool {
    SLSDisplayLink *self = (__bridge SLSDisplayLink *)userInfo;
    if (self->_interval == std::chrono::microseconds::zero()) {
      [self.target performSelector:self.selector
                          onThread:[NSThread currentThread]
                        withObject:nil
                     waitUntilDone:YES];
    } else {
      const auto elapsed =
          std::chrono::duration_cast<std::chrono::microseconds>(
              std::chrono::system_clock::now() - self->_accumulator);
      if (elapsed > self->_interval) {
        [self.target performSelector:self.selector
                            onThread:[NSThread currentThread]
                          withObject:nil
                       waitUntilDone:YES];
        self->_accumulator += self->_interval * (elapsed / self->_interval);
      }
    }
  }
  return kCVReturnSuccess;
}

@end
