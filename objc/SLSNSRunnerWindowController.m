//
//  SLSNSRunnerWindowController.m
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

#import "SLSNSRunnerWindowController.h"

#import "SLSEventSource.h"
#import "SLSDisplaySource.h"
#import "SLSNSBundle+Bundle.h"
#import "SLSRunner.h"

@interface SLSNSRunnerWindowController ()

@property (nonatomic, strong) IBOutlet NSView *contentView;

@end

@implementation SLSNSRunnerWindowController

- (instancetype)init {
  return [self initWithRunner:nil];
}

- (instancetype)initWithRunner:(SLSRunner *)runner {
  NSBundle *bundle = [NSBundle solasBundle];
  NSString *path = [bundle pathForResource:@"SLSNSRunnerWindowController"
                                    ofType:@"nib"];
  self = [super initWithWindowNibPath:path owner:self];
  if (self) {
    _runner = runner;
  }
  return self;
}

- (void)windowDidLoad {
  [super windowDidLoad];
  self.window.backgroundColor = [NSColor whiteColor];
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
    _runner = runner;
    _eventSource.eventDelegate = _runner;
    _displaySource.displayDelegate = _runner;
  }
}

@end
