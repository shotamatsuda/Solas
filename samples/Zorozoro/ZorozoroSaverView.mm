//
//  ZorozoroSaverView.m
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

#import "ZorozoroSaverView.h"

#include <memory>
#include <utility>

#include "solas/app.h"
#include "zorozoro.h"

#include "Solas.h"

@interface NSUserDefaults (ZorozoroSaverView)

- (void)setColor:(NSColor *)color forKey:(NSString *)key;
- (NSColor *)colorForKey:(NSString *)key;

@end

@implementation NSUserDefaults (ZorozoroSaverView)

- (void)setColor:(NSColor *)color forKey:(NSString *)key {
  [self setObject:[NSKeyedArchiver archivedDataWithRootObject:color]
           forKey:key];
}

- (NSColor *)colorForKey:(NSString *)key {
  NSData *data = [self dataForKey:key];
  if (data) {
    return (NSColor *)[NSKeyedUnarchiver unarchiveObjectWithData:data];
  }
  return nil;
}

@end

@interface ZorozoroSaverView () {
 @private
  zorozoro::Zorozoro *_zorozoro;
}

#pragma mark Initialization

@property (nonatomic, strong) IBOutlet NSWindow *configureSheet;
@property (nonatomic, strong) IBOutlet NSColorWell *foregroundColorWell;
@property (nonatomic, strong) IBOutlet NSColorWell *backgroundColorWell;
@property (nonatomic, strong) IBOutlet NSSlider *densitySlider;
@property (nonatomic, strong) SLSRunner *runner;
@property (nonatomic, strong) CALayer<SLSDisplaySource> *displaySource;
@property (nonatomic, readonly) ScreenSaverDefaults *defaults;

@end

@implementation ZorozoroSaverView

- (instancetype)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview {
  self = [super initWithFrame:frame isPreview:isPreview];
  if (self) {
    self.wantsLayer = YES;
    self.animationTimeInterval = 1.0 / 30.0;
    auto zorozoro = std::make_unique<zorozoro::Zorozoro>();
    [self.defaults registerDefaults:@{
      @"Foreground" : [NSKeyedArchiver archivedDataWithRootObject:
          [NSColor colorWithWhite:0.0 alpha:1.0]],
      @"Background" : [NSKeyedArchiver archivedDataWithRootObject:
          [NSColor colorWithWhite:1.0 alpha:1.0]],
      @"Density" : @200
    }];
    NSColor *foreground = [[self.defaults colorForKey:@"Foreground"]
        colorUsingColorSpace:[NSColorSpace genericRGBColorSpace]];
    NSColor *background = [[self.defaults colorForKey:@"Background"]
        colorUsingColorSpace:[NSColorSpace genericRGBColorSpace]];
    NSInteger density = [self.defaults integerForKey:@"Density"];
    _zorozoro = zorozoro.get();
    _zorozoro->foreground.r = [foreground redComponent];
    _zorozoro->foreground.g = [foreground greenComponent];
    _zorozoro->foreground.b = [foreground blueComponent];
    _zorozoro->foreground.a = [foreground alphaComponent];
    _zorozoro->background.r = [background redComponent];
    _zorozoro->background.g = [background greenComponent];
    _zorozoro->background.b = [background blueComponent];
    _zorozoro->background.a = [background alphaComponent];
    _zorozoro->density = density;
    _runner = [[SLSRunner alloc] initWithRunnable:
        std::make_unique<solas::app::Runner>(std::move(zorozoro))];
    NSAssert([self.layer conformsToProtocol:@protocol(SLSDisplaySource)], @"");
    _displaySource = (CALayer<SLSDisplaySource> *)self.layer;
    _displaySource.displayDelegate = _runner;
  }
  return self;
}

- (BOOL)isOpaque {
  return NO;
}

- (CALayer *)makeBackingLayer {
  return [SLSNSGLLayer layer];
}

- (void)drawRect:(NSRect)rect {
  // Do nothing
}

- (void)animateOneFrame {
  [_displaySource setDisplaySourceNeedsDisplay];
}

- (BOOL)hasConfigureSheet {
  return YES;
}

- (NSWindow *)configureSheet {
  if (!_configureSheet) {
    [[NSBundle bundleForClass:[ZorozoroSaverView class]]
           loadNibNamed:@"ZorozoroSaver"
                  owner:self
        topLevelObjects:nil];
  }
  _foregroundColorWell.color = [self.defaults colorForKey:@"Foreground"];
  _backgroundColorWell.color = [self.defaults colorForKey:@"Background"];
  _densitySlider.integerValue = [self.defaults integerForKey:@"Density"];
  return _configureSheet;
}

- (ScreenSaverDefaults *)defaults {
  return [ScreenSaverDefaults defaultsForModuleWithName:@"Zorozoro"];
}

- (IBAction)ok:(id)sender {
  NSColor *foreground = [_foregroundColorWell.color
      colorUsingColorSpace:[NSColorSpace genericRGBColorSpace]];
  NSColor *background = [_backgroundColorWell.color
      colorUsingColorSpace:[NSColorSpace genericRGBColorSpace]];
  NSInteger density = _densitySlider.integerValue;
  [self.defaults setColor:foreground forKey:@"Foreground"];
  [self.defaults setColor:background forKey:@"Background"];
  [self.defaults setInteger:density forKey:@"Density"];
  _zorozoro->foreground.r = [foreground redComponent];
  _zorozoro->foreground.g = [foreground greenComponent];
  _zorozoro->foreground.b = [foreground blueComponent];
  _zorozoro->foreground.a = [foreground alphaComponent];
  _zorozoro->background.r = [background redComponent];
  _zorozoro->background.g = [background greenComponent];
  _zorozoro->background.b = [background blueComponent];
  _zorozoro->background.a = [background alphaComponent];
  _zorozoro->density = density;
  [self.defaults synchronize];
  [[NSApplication sharedApplication] endSheet:_configureSheet];
}

- (IBAction)cancel:(id)sender {
  [[NSApplication sharedApplication] endSheet:_configureSheet];
}

@end
