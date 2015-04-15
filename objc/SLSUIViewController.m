//
//  SLSUIViewController.m
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

#import "SLSUIViewController.h"

#import "SLSEventSource.h"
#import "SLSDisplayLink.h"
#import "SLSDisplaySource.h"
#import "SLSRunner.h"

@interface SLSUIViewController ()

#pragma mark Controlling Animation

@property (nonatomic, strong) SLSDisplayLink *displayLink;

@end

@implementation SLSUIViewController

- (instancetype)initWithRunner:(SLSRunner *)runner {
  self = [super init];
  if (self) {
    _runner = runner;
    [self loadView];
    // Configure event and display sources
    NSAssert([self.view conformsToProtocol:@protocol(SLSEventSource)], @"");
    NSAssert([self.view conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _eventSource = (id<SLSEventSource>)self.view;
    _displaySource = (id<SLSDisplaySource>)self.view;
    _eventSource.eventDelegate = _runner;
    _displaySource.displayDelegate = _runner;
    [self startAnimation];
  }
  return self;
}

- (void)loadView {
  NSAssert(NO, @"Subclass must implement loadView");
}

#pragma mark Managing the Runner

- (void)setRunner:(SLSRunner *)runner {
  if (runner != _runner) {
    _runner = runner;
    _eventSource.eventDelegate = _runner;
    _displaySource.displayDelegate = _runner;
  }
}

#pragma mark Controlling Animation

- (void)startAnimation {
  if (!_displayLink) {
    _displayLink = [SLSDisplayLink
        displayLinkWithTarget:_displaySource
                     selector:@selector(displayImmediately)];
  }
  [_displayLink start];
}

- (void)stopAnimation {
  if (_displayLink) {
    [_displayLink stop];
  }
}

@end
