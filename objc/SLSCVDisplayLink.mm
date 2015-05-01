//
//  SLSCVDisplayLink.mm
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
@property (nonatomic, assign) CVDisplayLinkRef link;

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
  [_target release];
  [super dealloc];
}

- (void)start {
  CVDisplayLinkStart(_link);
}

- (void)stop {
  CVDisplayLinkStop(_link);
}

@end
