//
//  SLSNSOpenGLLayer.mm
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

#import "SLSNSOpenGLLayer.h"

#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#import <QuartzCore/QuartzCore.h>

#include "solas/app_event.h"
#include "solas/framebuffer.h"
#include "takram/math.h"

@interface SLSNSOpenGLLayer () {
 @private
  solas::Framebuffer _framebuffer;
}

@property (nonatomic, assign) NSOpenGLPixelFormatAttribute API;

@end

@implementation SLSNSOpenGLLayer

- (instancetype)init {
  return [self initWithAPI:NSOpenGLProfileVersionLegacy];
}

- (instancetype)initWithAPI:(NSOpenGLPixelFormatAttribute)API {
  self = [super init];
  if (self) {
    self.needsDisplayOnBoundsChange = NO;
    self.asynchronous = NO;
    self.API = API;
  }
  return self;
}

- (NSOpenGLPixelFormat *)openGLPixelFormatForDisplayMask:(uint32_t)mask {
  NSOpenGLPixelFormatAttribute values[] = {
    NSOpenGLPFADoubleBuffer,
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
  // Enable multithreading
  CGLEnable(context.CGLContextObj, kCGLCEMPEngine);
  return context;
}

- (BOOL)canDrawInOpenGLContext:(NSOpenGLContext *)context
                   pixelFormat:(NSOpenGLPixelFormat *)pixelFormat
                  forLayerTime:(CFTimeInterval)layerTime
                   displayTime:(const CVTimeStamp *)displayTime {
  const CGRect bounds = self.bounds;
  const takram::Size2d size(bounds.size.width, bounds.size.height);
  const solas::AppEvent event(solas::AppEvent::Type::UPDATE,
                              context, size, self.contentsScale);
  if ([_displayDelegate respondsToSelector:
          @selector(displayDelegate:update:)]) {
    [_displayDelegate displayDelegate:self update:SLSAppEventMake(&event)];
  }
  return YES;
}

- (void)drawInOpenGLContext:(NSOpenGLContext *)context
                pixelFormat:(NSOpenGLPixelFormat *)pixelFormat
               forLayerTime:(CFTimeInterval)timeInterval
                displayTime:(const CVTimeStamp *)timeStamp {
  const CGRect bounds = self.bounds;
  const double scale = self.contentsScale;
  GLint framebuffer;
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &framebuffer);
  _framebuffer.update(bounds.size.width, bounds.size.height, scale);
  _framebuffer.bind();
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  const takram::Size2d size(bounds.size.width, bounds.size.height);
  const solas::AppEvent event(solas::AppEvent::Type::DRAW,
                              context, size, scale);
  if ([_displayDelegate respondsToSelector:@selector(displayDelegate:draw:)]) {
    [_displayDelegate displayDelegate:self draw:SLSAppEventMake(&event)];
  }
  _framebuffer.transfer(framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
  [super drawInOpenGLContext:context
                 pixelFormat:pixelFormat
                forLayerTime:timeInterval
                 displayTime:timeStamp];
}

- (void)setBounds:(CGRect)bounds {
  BOOL changed = !CGSizeEqualToSize(bounds.size, self.bounds.size);
  [super setBounds:bounds];
  if (changed) {
    [self display];
    [CATransaction flush];
  }
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  if ([NSThread isMainThread]) {
    [self setNeedsDisplay];
  } else {
    // Don't wait until done here because CVDisplayLinkStop call on
    // CVDisplayLink's deallocation on the main thread will result in deadlock.
    [self performSelectorOnMainThread:@selector(setNeedsDisplay)
                           withObject:nil
                        waitUntilDone:NO];
  }
}

@end
