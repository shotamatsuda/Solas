//
//  SLSUIOpenGLESView.mm
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

#import "SLSUIOpenGLESView.h"

#import <GLKit/GLKit.h>

#include "solas/app_event.h"
#include "takram/math.h"

@interface SLSUIOpenGLESView () <GLKViewDelegate>

#pragma mark Initialization

@property (nonatomic, strong) GLKView *view;

- (void)setUpSLSUIOpenGLESView;

@end

@implementation SLSUIOpenGLESView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    [self setUpSLSUIOpenGLESView];
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
  self = [super initWithCoder:decoder];
  if (self) {
    [self setUpSLSUIOpenGLESView];
  }
  return self;
}

- (EAGLRenderingAPI)API {
  return kEAGLRenderingAPIOpenGLES1;
}

#pragma mark Initialization

- (void)setUpSLSUIOpenGLESView {
  _view = [[GLKView alloc] initWithFrame:self.bounds];
  _view.context = [[EAGLContext alloc] initWithAPI:self.API];
  _view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
  _view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
  _view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
  _view.drawableMultisample = GLKViewDrawableMultisample4X;
  _view.enableSetNeedsDisplay = YES;
  _view.autoresizingMask = (UIViewAutoresizingFlexibleWidth |
                            UIViewAutoresizingFlexibleHeight);
  _view.delegate = self;
  [self addSubview:_view];
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  if ([NSThread isMainThread]) {
    [_view setNeedsDisplay];
  } else {
    // Don't wait until done here because CVDisplayLinkStop call on
    // CVDisplayLink's deallocation on the main thread will result in deadlock.
    [_view performSelectorOnMainThread:@selector(setNeedsDisplay)
                            withObject:nil
                         waitUntilDone:NO];
  }
  CGRect bounds = self.bounds;
  const takram::Size2d size(bounds.size.width, bounds.size.height);
  const solas::AppEvent event(solas::AppEvent::Type::UPDATE,
                              _view.context, size, [UIScreen mainScreen].scale);
  if ([_displayDelegate respondsToSelector:
          @selector(displayDelegate:update:)]) {
    [_displayDelegate displayDelegate:self update:SLSAppEventMake(&event)];
  }
  [_view setNeedsDisplay];
}

#pragma mark GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  CGRect bounds = self.bounds;
  const takram::Size2d size(bounds.size.width, bounds.size.height);
  const solas::AppEvent event(solas::AppEvent::Type::DRAW,
                              _view.context, size, [UIScreen mainScreen].scale);
  if ([_displayDelegate respondsToSelector:@selector(displayDelegate:draw:)]) {
    [_displayDelegate displayDelegate:self draw:SLSAppEventMake(&event)];
  }
}

@end
