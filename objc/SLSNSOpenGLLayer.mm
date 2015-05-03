//
//  SLSNSOpenGLLayer.mm
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

#import "SLSNSOpenGLLayer.h"

#include "solas/app/app_event.h"
#include "solas/math/size.h"

@interface SLSNSOpenGLLayer ()

@property (nonatomic, assign) NSOpenGLPixelFormatAttribute API;

@end

@implementation SLSNSOpenGLLayer

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
    (NSOpenGLPixelFormatAttribute)32,
    NSOpenGLPFAStencilSize,
    (NSOpenGLPixelFormatAttribute)8,
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

- (BOOL)canDrawInOpenGLContext:(NSOpenGLContext *)context
                   pixelFormat:(NSOpenGLPixelFormat *)pixelFormat
                  forLayerTime:(CFTimeInterval)layerTime
                   displayTime:(const CVTimeStamp *)displayTime {
  CGRect bounds = self.bounds;
  const solas::math::Size2d size(bounds.size.width, bounds.size.height);
  const solas::app::AppEvent event(context, size, self.contentsScale);
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  return YES;
}

- (void)drawInOpenGLContext:(NSOpenGLContext *)context
                pixelFormat:(NSOpenGLPixelFormat *)pixelFormat
               forLayerTime:(CFTimeInterval)timeInterval
                displayTime:(const CVTimeStamp *)timeStamp {
  CGRect bounds = self.bounds;
  const solas::math::Size2d size(bounds.size.width, bounds.size.height);
  const solas::app::AppEvent event(context, size, self.contentsScale);
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
