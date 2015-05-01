//
//  SLSUIOpenGLESView.mm
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

#import "SLSUIOpenGLESView.h"

#import <GLKit/GLKit.h>

@interface SLSUIOpenGLESView () <GLKViewDelegate, GLKViewControllerDelegate>

#pragma mark Initialization

@property (nonatomic, strong) GLKView *view;
@property (nonatomic, strong) GLKViewController *viewController;

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
  _view.autoresizingMask =
      UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
  _view.delegate = self;
  [self addSubview:_view];
  _viewController = [[GLKViewController alloc] init];
  _viewController.preferredFramesPerSecond = 60;
  _viewController.view = _view;
  _viewController.delegate = self;
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [_view performSelectorOnMainThread:@selector(setNeedsDisplay)
                          withObject:nil
                       waitUntilDone:YES];
}

#pragma mark GLKViewDelegate

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {
  const solas::app::AppEvent event(_view.context, solas::math::Size2d(
      self.bounds.size.width, self.bounds.size.height));
  if ([_displayDelegate respondsToSelector:@selector(sender:draw:)]) {
    [_displayDelegate sender:self draw:SLSAppEventMake(&event)];
  }
}

#pragma mark GLKViewControllerDelegate

- (void)glkViewControllerUpdate:(GLKViewController *)controller {
  const solas::app::AppEvent event(_view.context, solas::math::Size2d(
      self.bounds.size.width, self.bounds.size.height));
  if ([_displayDelegate respondsToSelector:@selector(sender:update:)]) {
    [_displayDelegate sender:self update:SLSAppEventMake(&event)];
  }
}

@end
