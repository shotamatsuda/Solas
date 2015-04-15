//
//  SLSUIGLView.mm
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

#import "SLSUIGLView.h"

#import <GLKit/GLKit.h>

@interface SLSUIGLView () <GLKViewDelegate>

#pragma mark Initialization

@property (nonatomic, strong) GLKView *view;

- (void)setUpSLSUIGLView;

@end

@implementation SLSUIGLView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    [self setUpSLSUIGLView];
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
  self = [super initWithCoder:decoder];
  if (self) {
    [self setUpSLSUIGLView];
  }
  return self;
}

#pragma mark Initialization

- (void)setUpSLSUIGLView {
  _view = [[GLKView alloc] initWithFrame:self.bounds];
  _view.enableSetNeedsDisplay = YES;
  _view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
  _view.drawableColorFormat = GLKViewDrawableColorFormatRGBA8888;
  _view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
  _view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
  _view.drawableMultisample = GLKViewDrawableMultisample4X;
  _view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
  _view.delegate = self;
  self.internalContentsScaleFactor = _view.contentScaleFactor;
  [self addSubview:_view];
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [_view performSelectorOnMainThread:@selector(setNeedsDisplay)
                          withObject:nil
                       waitUntilDone:NO];
}

#pragma mark GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
  CGFloat scale = self.internalContentsScaleFactor;
  const solas::app::AppEvent event(_view.context, solas::math::Size2d(
      self.bounds.size.width * scale, self.bounds.size.height * scale));
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
}

@end
