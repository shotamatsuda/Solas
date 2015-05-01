//
//  SLSUIView.m
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

#import "SLSUIView.h"

#import <QuartzCore/QuartzCore.h>

#import "SLSDisplayDelegate.h"
#import "SLSDisplaySource.h"
#import "SLSQuartzLayer.h"

@interface SLSUIView ()

#pragma mark Initialization

@property (nonatomic, strong) CALayer<SLSDisplaySource> *displaySource;

#pragma mark Window Notifications

@end

@implementation SLSUIView

- (instancetype)initWithFrame:(CGRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
  }
  return self;
}

- (BOOL)isOpaque {
  return NO;
}

+ (Class)layerClass {
  NSAssert(NO, @"Subclass must implement layerClass");
  return nil;  // Implement in subviews
}

#pragma mark Invalidating the Display Source

- (void)setDisplaySourceNeedsDisplay {
  [_displaySource setDisplaySourceNeedsDisplay];
}

#pragma mark Managing the Delegate

- (id<SLSDisplayDelegate>)displayDelegate {
  return _displaySource.displayDelegate;
}

- (void)setDisplayDelegate:(id<SLSDisplayDelegate>)displayDelegate {
  _displaySource.displayDelegate = displayDelegate;
}

@end
