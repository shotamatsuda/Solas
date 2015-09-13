//
//  SLSUIViewController.m
//
//  The MIT License
//
//  Copyright (C) 2015 Shota Matsuda
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

#import "SLSUIViewController.h"

#import "SLSEventSource.h"
#import "SLSDisplayLink.h"
#import "SLSDisplaySource.h"
#import "SLSRunner.h"
#import "SLSUIOpenGLESView.h"
#import "SLSUIOpenGLES2View.h"
#import "SLSUIOpenGLES3View.h"
#import "SLSUIQuartzView.h"

@interface SLSUIViewController ()

#pragma mark Initialization

@property (nonatomic, strong) UIView *contentView;

- (void)setUpContentView;

#pragma mark Controlling Animation

@property (nonatomic, strong) SLSDisplayLink *displayLink;

@end

@implementation SLSUIViewController

- (instancetype)initWithRunner:(SLSRunner *)runner {
  self = [super initWithNibName:nil bundle:nil];
  if (self) {
    [self setRunner:runner];
  }
  return self;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil
                         bundle:(NSBundle *)nibBundleOrNil {
  return [self initWithRunner:nil];
}

- (instancetype)initWithCoder:(NSCoder *)decoder {
  return [self initWithRunner:nil];
}

- (void)loadView {
  self.view = [[UIView alloc] init];
}

- (void)setUpContentView {
  Class viewClass = nil;
  if (_runner.backend & kSLSRunnerBackendOpenGLES1) {
    viewClass = [SLSUIOpenGLESView class];
  } else if (_runner.backend & kSLSRunnerBackendOpenGLES2) {
    viewClass = [SLSUIOpenGLES2View class];
  } else if (_runner.backend & kSLSRunnerBackendOpenGLES3) {
    viewClass = [SLSUIOpenGLES3View class];
  } else if (_runner.backend & kSLSRunnerBackendCoreGraphics) {
    viewClass = [SLSUIQuartzView class];
  }
  _contentView = [[viewClass alloc] initWithFrame:self.view.bounds];
  _contentView.autoresizingMask =
      UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
  [self.view addSubview:_contentView];

  // Configure event and display sources
  NSAssert([_contentView conformsToProtocol:@protocol(SLSEventSource)], @"");
  NSAssert([_contentView conformsToProtocol:@protocol(SLSDisplaySource)], @"");
  _eventSource = (id<SLSEventSource>)_contentView;
  _displaySource = (id<SLSDisplaySource>)_contentView;
  _eventSource.eventDelegate = _runner;
  _displaySource.displayDelegate = _runner;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {}
- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event {}
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event {}
- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event {}

#pragma mark Managing the Runner

- (void)setRunner:(SLSRunner *)runner {
  if (runner != _runner) {
    [self stopAnimation];
    _runner.delegate = nil;
    _runner = runner;
    _runner.delegate = self;
    [self setUpContentView];
    [self startAnimation];
  }
}

#pragma mark Controlling Animation

- (double)frameRate {
  return _displayLink.frameRate;
}

- (void)setFrameRate:(double)frameRate {
  _displayLink.frameRate = frameRate;
}

- (void)startAnimation {
  if (!_displayLink) {
    _displayLink = [SLSDisplayLink
        displayLinkWithTarget:_displaySource
                     selector:@selector(setDisplaySourceNeedsDisplay)];
  }
  [_displayLink start];
}

- (void)stopAnimation {
  if (_displayLink) {
    [_displayLink stop];
  }
}

#pragma mark SLSRunnerDelegate

- (void)runner:(nonnull SLSRunner *)runner frameRate:(double)frameRate {
  self.frameRate = frameRate;
}

@end
