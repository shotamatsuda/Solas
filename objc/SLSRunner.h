//
//  SLSRunner.h
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

#import <Foundation/Foundation.h>

#import "SLSDisplayDelegate.h"
#import "SLSEventDelegate.h"

#ifdef __cplusplus

#include <memory>

#include "solas/app/runner.h"

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

@interface SLSRunner : NSObject <SLSDisplayDelegate, SLSEventDelegate>

#ifdef __cplusplus

- (instancetype)initWithRunnable:(std::unique_ptr<solas::app::Runner>&&)runner
    NS_DESIGNATED_INITIALIZER;

#endif  // __cplusplus

@property (nonatomic, readonly) SLSRunnerBackend backend;

@end
