//
//  SLSNSViewController.m
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

#import "SLSNSViewController.h"

#import <CoreGraphics/CoreGraphics.h>

#import "SLSEventSource.h"
#import "SLSDisplayLink.h"
#import "SLSDisplaySource.h"
#import "SLSNSOpenGLView.h"
#import "SLSNSOpenGL3View.h"
#import "SLSNSOpenGL4View.h"
#import "SLSNSQuartzView.h"
#import "SLSRunner.h"

@interface SLSNSViewController ()

#pragma mark Initialization

@property (nonatomic, strong) NSView *contentView;

- (void)setUpContentView;

#pragma mark Controlling Animation

@property (nonatomic, strong) SLSDisplayLink *displayLink;

@end

@implementation SLSNSViewController

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

- (instancetype)initWithCoder:(NSCoder *)coder {
  return [self initWithRunner:nil];
}

- (void)loadView {
  self.view = [[NSView alloc] init];
}

- (void)setUpContentView {
  Class viewClass = nil;
  if (_runner.backend & kSLSRunnerBackendOpenGL2) {
    viewClass = [SLSNSOpenGLView class];
  } else if (_runner.backend & kSLSRunnerBackendOpenGL3) {
    viewClass = [SLSNSOpenGL3View class];
  } else if (_runner.backend & kSLSRunnerBackendOpenGL4) {
    viewClass = [SLSNSOpenGL4View class];
  } else if (_runner.backend & kSLSRunnerBackendCoreGraphics) {
    viewClass = [SLSNSQuartzView class];
  }
  _contentView = [[viewClass alloc] initWithFrame:self.view.bounds];
  _contentView.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;
  if ([_contentView respondsToSelector:@selector(setMouseDownCanMoveWindow:)]) {
    [(id)_contentView setMouseDownCanMoveWindow:_runner.movesWindow];
  }
  [self.view addSubview:_contentView];
  self.view.nextResponder = self;

  // Configure event and display sources
  NSAssert([_contentView conformsToProtocol:@protocol(SLSEventSource)], @"");
  NSAssert([_contentView conformsToProtocol:@protocol(SLSDisplaySource)], @"");
  _eventSource = (id<SLSEventSource>)_contentView;
  _displaySource = (id<SLSDisplaySource>)_contentView;
  _eventSource.eventDelegate = _runner;
  _displaySource.displayDelegate = _runner;
}

- (void)mouseDown:(NSEvent *)event {}
- (void)rightMouseDown:(NSEvent *)event {}
- (void)otherMouseDown:(NSEvent *)event {}
- (void)mouseUp:(NSEvent *)event {}
- (void)rightMouseUp:(NSEvent *)event {}
- (void)otherMouseUp:(NSEvent *)event {}
- (void)mouseDragged:(NSEvent *)event {}
- (void)rightMouseDragged:(NSEvent *)event {}
- (void)otherMouseDragged:(NSEvent *)event {}
- (void)mouseMoved:(NSEvent *)event {}
- (void)mouseEntered:(NSEvent *)event {}
- (void)mouseExited:(NSEvent *)event {}
- (void)scrollWheel:(NSEvent *)event {}
- (void)keyDown:(NSEvent *)event {}
- (void)keyUp:(NSEvent *)event {}
- (void)touchesBeganWithEvent:(NSEvent *)event {}
- (void)touchesMovedWithEvent:(NSEvent *)event {}
- (void)touchesCancelledWithEvent:(NSEvent *)event {}
- (void)touchesEndedWithEvent:(NSEvent *)event {}

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

- (void)runner:(nonnull SLSRunner *)runner resize:(CGSize)size {
  NSWindow *window = self.view.window;
  CGRect contentRect = [window contentRectForFrameRect:window.frame];
  contentRect.origin.x += (contentRect.size.width - size.width) / 2.0;
  contentRect.origin.y += (contentRect.size.height - size.height) / 2.0;
  contentRect.size = size;
  [window setFrame:[window frameRectForContentRect:contentRect] display:YES];
}

- (void)runner:(nonnull SLSRunner *)runner fullScreen:(BOOL)flag {
  BOOL actual = self.view.window.styleMask & NSFullScreenWindowMask;
  if ((flag && !actual) || (!flag && actual)) {
    [self.view.window toggleFullScreen:self];
  }
}

@end
