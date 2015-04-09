//
//  SLSDisplayLink.mm
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

#if __has_feature(objc_arc)
#error This file must be compiled without ARC. Use -fno-objc-arc flag.
#endif

#import "SLSDisplayLink.h"

#import <QuartzCore/QuartzCore.h>

#include <cstdint>
#include <vector>

@interface SLSDisplayLink ()

@property (nonatomic, retain) id target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, assign) CVDisplayLinkRef displayLink;

@end

@implementation SLSDisplayLink

namespace {

static CVReturn DisplayLinkCallback(
    CVDisplayLinkRef displayLinkRef,
    const CVTimeStamp *now,
    const CVTimeStamp *outputTime,
    CVOptionFlags flagsIn,
    CVOptionFlags *flagsOut,
    void *userInfo) {
  @autoreleasepool {
    SLSDisplayLink *self = (__bridge SLSDisplayLink *)userInfo;
    [self.target performSelector:self.selector];
  }
  return kCVReturnSuccess;
}

}  // namespace

- (instancetype)initWithTarget:(id)target selector:(SEL)selector {
  self = [super init];
  if (self) {
    _target = [target retain];
    _selector = selector;
    CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);
    CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback,
                                   (__bridge void *)self);
  }
  return self;
}

+ (SLSDisplayLink *)displayLinkWithTarget:(id)target selector:(SEL)selector {
  return [[self alloc] initWithTarget:target selector:selector];
}

- (void)dealloc {
  if (_displayLink) {
    if (CVDisplayLinkIsRunning(_displayLink)) {
      CVDisplayLinkStop(_displayLink);
    }
    CVDisplayLinkRelease(_displayLink);
    _displayLink = NULL;
  }
  [_target release];
  [super dealloc];
}

- (void)start {
  CVDisplayLinkStart(_displayLink);
}

- (void)stop {
  CVDisplayLinkStop(_displayLink);
}

@end
