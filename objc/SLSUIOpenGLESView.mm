//
//  SLSUIOpenGLESView.m
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

#import "SLSUIOpenGLESView.h"

#import <GLKit/GLKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <QuartzCore/QuartzCore.h>

#import "SLSCoreGraphicsLayer.h"
#import "SLSDisplayLink.h"
#import "SLSEvents.h"

#include "solas/app/app_event.h"
#include "solas/math/size.h"

@interface SLSUIOpenGLESView ()

@property (nonatomic, strong) GLKView *GLView;
@property (nonatomic, strong) SLSDisplayLink *displayLink;

@end

@implementation SLSUIOpenGLESView

- (id)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    _GLView = [[GLKView alloc] initWithFrame:self.bounds];
    _GLView.autoresizingMask =
        (UIViewAutoresizingFlexibleWidth |
         UIViewAutoresizingFlexibleHeight);
    _GLView.context = [[EAGLContext alloc]
        initWithAPI:kEAGLRenderingAPIOpenGLES2];
    _GLView.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
    _GLView.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    _GLView.drawableStencilFormat = GLKViewDrawableStencilFormat8;
    _GLView.drawableMultisample = GLKViewDrawableMultisample4X;
    [self addSubview:_GLView];
  }
  return self;
}

- (id)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    _GLView = [[GLKView alloc] initWithFrame:self.bounds];
    _GLView.autoresizingMask =
    (UIViewAutoresizingFlexibleWidth |
     UIViewAutoresizingFlexibleHeight);
    [self addSubview:_GLView];
    _GLView.context = [[EAGLContext alloc]
        initWithAPI:kEAGLRenderingAPIOpenGLES2];
    [self startLoop];
  }
  return self;
}

//- (void)dealloc {
//  if ([EAGLContext currentContext] == _context) {
//    [EAGLContext setCurrentContext:nil];
//  }
//}

//+ (Class)layerClass {
//  return [CAEAGLLayer class];
//}
//
//- (NSDictionary *)drawableProperties {
//  return @{
//    kEAGLDrawablePropertyRetainedBacking : @NO,
//    kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8
//  };
//}
//
//- (void)layoutSubviews {
//  [EAGLContext setCurrentContext:_context];
//  const solas::app::AppEvent event(_context, solas::math::Size2d(
//      self.bounds.size.width, self.bounds.size.height));
//  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
//    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
//  }
//  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
//    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
//  }
//}

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

@end
