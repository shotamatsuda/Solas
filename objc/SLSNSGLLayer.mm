//
//  SLSNSGLLayer.mm
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

#import "SLSNSGLLayer.h"

#include "solas/app/app_event.h"
#include "solas/math/size.h"

@interface SLSNSGLLayer ()

@property (nonatomic, assign) NSOpenGLPixelFormatAttribute API;

@end

@implementation SLSNSGLLayer

- (instancetype)init {
  return [self initWithAPI:NSOpenGLProfileVersionLegacy];
}

- (instancetype)initWithAPI:(NSOpenGLPixelFormatAttribute)API {
  self = [super init];
  if (self) {
    self.needsDisplayOnBoundsChange = YES;
    self.asynchronous = NO;
    self.API = API;
  }
  return self;
}

- (NSOpenGLPixelFormat *)openGLPixelFormatForDisplayMask:(uint32_t)mask {
  NSOpenGLPixelFormatAttribute values[] = {
    NSOpenGLPFADoubleBuffer,
    NSOpenGLPFAColorSize,
    (NSOpenGLPixelFormatAttribute)24,
    NSOpenGLPFAAlphaSize,
    (NSOpenGLPixelFormatAttribute)8,
    NSOpenGLPFADepthSize,
    (NSOpenGLPixelFormatAttribute)24,
    NSOpenGLPFASampleBuffers,
    (NSOpenGLPixelFormatAttribute)1,
    NSOpenGLPFASamples,
    (NSOpenGLPixelFormatAttribute)8,
    NSOpenGLPFAMultisample,
    NSOpenGLPFAAccelerated,
    NSOpenGLPFAOpenGLProfile,
    self.API,
    (NSOpenGLPixelFormatAttribute)0
  };
  return [[NSOpenGLPixelFormat alloc] initWithAttributes:values];
}

- (NSOpenGLContext *)openGLContextForPixelFormat:
    (NSOpenGLPixelFormat *)pixelFormat {
  NSOpenGLContext *context = [super openGLContextForPixelFormat:pixelFormat];
  NSAssert(context, @"Failed to create OpenGL context");
  [context makeCurrentContext];
  // Synchronize buffer swaps with the vertical refresh rate
  [context setValues:(GLint[]) {1} forParameter:NSOpenGLCPSwapInterval];
  return context;
}

- (void)drawInOpenGLContext:(NSOpenGLContext *)context
                pixelFormat:(NSOpenGLPixelFormat *)pixelFormat
               forLayerTime:(CFTimeInterval)timeInterval
                displayTime:(const CVTimeStamp *)timeStamp {
  const solas::app::AppEvent event(context, solas::math::Size2d(
      self.bounds.size.width, self.bounds.size.height));
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
  [super drawInOpenGLContext:context
                 pixelFormat:pixelFormat
                forLayerTime:timeInterval
                 displayTime:timeStamp];
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [self performSelectorOnMainThread:@selector(setNeedsDisplay)
                         withObject:nil
                      waitUntilDone:YES];
}

@end
