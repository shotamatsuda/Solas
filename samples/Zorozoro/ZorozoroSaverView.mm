//
//  ZorozoroSaverView.m
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

#import "ZorozoroSaverView.h"

#include <memory>

#include "solas/app.h"
#include "zorozoro.h"

#include "Solas/Solas.h"

@interface ZorozoroSaverView ()

#pragma mark Initialization

@property (nonatomic, strong) SLSRunner *runner;
@property (nonatomic, strong) CALayer<SLSDisplaySource> *displaySource;

@end

@implementation ZorozoroSaverView

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview {
  self = [super initWithFrame:frame isPreview:isPreview];
  if (self) {
    self.wantsLayer = YES;
    self.animationTimeInterval = 1.0 / 30.0;
    _runner = [[SLSRunner alloc] initWithRunnable:
        std::make_unique<solas::app::Runner>(
            std::make_unique<zorozoro::Zorozoro>())];
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
    _displaySource.displayDelegate = _runner;
  }
  return self;
}

- (CALayer *)makeBackingLayer {
  return [SLSNSGLLayer layer];
}

- (void)startAnimation {
  [super startAnimation];
}

- (void)stopAnimation {
  [super stopAnimation];
}

- (void)drawRect:(NSRect)rect {
  [super drawRect:rect];
}

- (void)animateOneFrame {
  [_displaySource setDisplaySourceNeedsDisplay];
}

- (BOOL)hasConfigureSheet {
  return NO;
}

- (NSWindow*)configureSheet {
  return nil;
}

@end
