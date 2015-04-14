//
//  SLSOpenGLLayer.mm
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

#import "SLSOpenGLLayer.h"

#import <OpenGL/gl.h>

#import "SLSDisplayLink.h"
#import "SLSEvents.h"

#include <cstdint>

#include "solas/app/app_event.h"
#include "solas/math/size.h"

@interface SLSOpenGLLayer ()

@property (nonatomic, strong) SLSDisplayLink *displayLink;

- (void)setNeedsDisplayOnMainThread;

@end

@implementation SLSOpenGLLayer

- (instancetype)init {
  self = [super init];
  if (self) {
    self.needsDisplayOnBoundsChange = YES;
    self.drawsAsynchronously = YES;
    [self startLoop];
  }
  return self;
}

- (CGLPixelFormatObj)copyCGLPixelFormatForDisplayMask:(std::uint32_t)mask {
  CGLPixelFormatAttribute attributes[] = {
    kCGLPFADoubleBuffer,
    kCGLPFAColorSize,
    (CGLPixelFormatAttribute)24,
    kCGLPFAAlphaSize,
    (CGLPixelFormatAttribute)8,
    kCGLPFADepthSize,
    (CGLPixelFormatAttribute)24,
    kCGLPFASampleBuffers,
    (CGLPixelFormatAttribute)1,
    kCGLPFASamples,
    (CGLPixelFormatAttribute)8,
    kCGLPFAMultisample,
    kCGLPFAAccelerated,
    (CGLPixelFormatAttribute)0
  };
  CGLPixelFormatObj pixelFormat = NULL;
  GLint pixelFormatCount;
  CGLChoosePixelFormat(attributes, &pixelFormat, &pixelFormatCount);
  return pixelFormat;
}

- (CGLContextObj)copyCGLContextForPixelFormat:(CGLPixelFormatObj)pixelFormat {
  CGLContextObj context = [super copyCGLContextForPixelFormat:pixelFormat];

  // Synchronize buffer swaps with vertical refresh rate
  CGLSetParameter(context, kCGLCPSwapInterval, (GLint[]) {1});

  // Default viewport
  CGSize size = self.bounds.size;
  glViewport(0.0, 0.0, size.width, size.height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, size.width, size.height, 0.0, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Enable alpha blending by default
  glEnable(GL_BLEND);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                      GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  return context;
}

#pragma mark Controlling Loop

- (void)startLoop {
  if (!_displayLink) {
    _displayLink = [SLSDisplayLink
        displayLinkWithTarget:self
                     selector:@selector(setNeedsDisplayOnMainThread)];
  }
  [_displayLink start];
}

- (void)stopLoop {
  if (_displayLink) {
    [_displayLink stop];
  }
}

- (void)setNeedsDisplayOnMainThread {
  [super performSelectorOnMainThread:@selector(setNeedsDisplay)
                          withObject:self
                       waitUntilDone:YES];
}

-(void)drawInCGLContext:(CGLContextObj)context
            pixelFormat:(CGLPixelFormatObj)pixelFormat
           forLayerTime:(CFTimeInterval)layerTime
            displayTime:(const CVTimeStamp *)displayTime {
  CGLSetCurrentContext(context);
  const solas::app::AppEvent event(context, solas::math::Size2d(
      self.bounds.size.width, self.bounds.size.height));
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
  [super drawInCGLContext:context
              pixelFormat:pixelFormat
             forLayerTime:layerTime
              displayTime:displayTime];
}

@end
