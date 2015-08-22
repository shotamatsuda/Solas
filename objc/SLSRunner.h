//
//  SLSRunner.h
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

#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#import "SLSDisplayDelegate.h"
#import "SLSEventDelegate.h"

#ifdef __cplusplus

#include <memory>

#include "solas/runner.h"

#endif  // __cplusplus

typedef NS_ENUM(NSInteger, SLSRunnerBackend) {
  kSLSRunnerBackendUndefined = 0,
  kSLSRunnerBackendOpenGL2 = 1 << 0,
  kSLSRunnerBackendOpenGL3 = 1 << 1,
  kSLSRunnerBackendOpenGL4 = 1 << 2,
  kSLSRunnerBackendOpenGLES1 = 1 << 3,
  kSLSRunnerBackendOpenGLES2 = 1 << 4,
  kSLSRunnerBackendOpenGLES3 = 1 << 5,
  kSLSRunnerBackendCoreGraphics = 1 << 6
};

@protocol SLSRunnerDelegate;

@interface SLSRunner : NSObject <SLSDisplayDelegate, SLSEventDelegate>

#ifdef __cplusplus

- (nullable instancetype)init;
- (nullable instancetype)initWithRunnable:
    (std::unique_ptr<solas::Runner>&&)runner
    NS_DESIGNATED_INITIALIZER;

#endif  // __cplusplus

@property (nonatomic, readonly) SLSRunnerBackend backend;
@property (nonatomic, readonly) BOOL translatesTouches;
@property (nonatomic, readonly) BOOL movesWindow;
@property (nonatomic, weak, nullable) id<SLSRunnerDelegate> delegate;

- (void)resize:(CGSize)size;
- (void)fullscreen:(BOOL)flag;

@end

@protocol SLSRunnerDelegate <NSObject>

@optional
- (void)runner:(nonnull SLSRunner *)runner resize:(CGSize)size;
- (void)runner:(nonnull SLSRunner *)runner fullscreen:(BOOL)flag;

@end
