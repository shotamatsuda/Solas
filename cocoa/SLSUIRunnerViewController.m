//
//  SLSUIRunnerViewController.m
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

#import "SLSUIRunnerViewController.h"

#import "SLSNSBundle+Bundle.h"
#import "SLSRunner.h"
#import "SLSUIRunnerView.h"

@interface SLSUIRunnerViewController ()

@property (nonatomic, strong) IBOutlet SLSUIRunnerView *runnerView;

@end

@implementation SLSUIRunnerViewController

- (instancetype)init {
  return [self initWithRunner:nil];
}

- (instancetype)initWithRunner:(SLSRunner *)runner {
  NSBundle *bundle = [NSBundle solasBundle];
  self = [super initWithNibName:@"SLSUIRunnerViewController" bundle:bundle];
  if (self) {
    _runner = runner;
  }
  return self;
}

- (void)viewDidLoad {
  [super viewDidLoad];
  _runnerView.eventDelegate = _runner;
  _runnerView.runnerLayer.displayDelegate = _runner;
}

#pragma mark Managing the Runner

- (void)setRunner:(SLSRunner *)runner {
  if (runner != _runner) {
    _runner = runner;
    _runnerView.eventDelegate = _runner;
    _runnerView.runnerLayer.displayDelegate = _runner;
  }
}

@end
