//
//  SLSNSOpenGLView.m
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

#import "SLSNSOpenGLView.h"

#import "SLSNSOpenGLLayer.h"

@implementation SLSNSOpenGLView

- (instancetype)initWithFrame:(NSRect)frame {
  self = [super initWithFrame:frame];
  if (self) {
    self.wantsBestResolutionOpenGLSurface = YES;
  }
  return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
  self = [super initWithCoder:coder];
  if (self) {
    self.wantsBestResolutionOpenGLSurface = YES;
  }
  return self;
}

- (CALayer *)makeBackingLayer {
  return [[SLSNSOpenGLLayer alloc] initWithAPI:self.API];
}

- (NSOpenGLPixelFormatAttribute)API {
  return NSOpenGLProfileVersionLegacy;
}

@end
