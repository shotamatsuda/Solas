//
//  SLSUIViewController.m
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

#pragma mark Managing the Runner

- (void)setRunner:(SLSRunner *)runner {
  if (runner != _runner) {
    [self stopAnimation];
    _runner = runner;
    [self setUpContentView];
    [self startAnimation];
  }
}

#pragma mark Controlling Animation

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

@end
