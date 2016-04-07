//
//  SLSScreenSaverView.m
//
//  The MIT License
//
//  Copyright (C) 2015-2016 Shota Matsuda
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

#import "SLSScreenSaverView.h"

#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>

#import "SLSDisplaySource.h"
#import "SLSNSOpenGLLayer.h"
#import "SLSRunner.h"

@implementation SLSScreenSaverView

- (instancetype)initWithFrame:(CGRect)frame isPreview:(BOOL)isPreview {
  return [self initWithRunner:nil frame:frame isPreview:isPreview];
}

- (instancetype)initWithRunner:(SLSRunner *)runner
                         frame:(CGRect)frame
                     isPreview:(BOOL)isPreview {
  if (!runner) {
    return nil;
  }
  self = [super initWithFrame:frame isPreview:isPreview];
  if (self) {
    _runner = runner;
    _runner.delegate = self;
    if (_runner.backend & kSLSRunnerBackendOpenGL2) {
      _API = NSOpenGLProfileVersionLegacy;
    } else if (_runner.backend & kSLSRunnerBackendOpenGL3) {
      _API = NSOpenGLProfileVersion3_2Core;
    } else if (_runner.backend & kSLSRunnerBackendOpenGL4) {
      _API = NSOpenGLProfileVersion4_1Core;
    }
    self.wantsBestResolutionOpenGLSurface = YES;
    self.wantsLayer = YES;
    self.animationTimeInterval = 1.0 / 60.0;
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
    _displaySource.displayDelegate = _runner;
  }
  return self;
}

- (BOOL)isOpaque {
  return YES;
}

- (CALayer *)makeBackingLayer {
  return [[SLSNSOpenGLLayer alloc] initWithAPI:self.API];
}

- (void)drawRect:(NSRect)rect {
  // Do nothing
}

- (void)animateOneFrame {
  [_displaySource setDisplaySourceNeedsDisplay];
}

#pragma mark SLSRunnerDelegate

- (void)runner:(nonnull SLSRunner *)runner frameRate:(double)frameRate {
  self.animationTimeInterval = 1.0 / frameRate;
}

@end
