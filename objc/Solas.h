//
//  Solas.h
//
//  MIT License
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

#import <AppKit/AppKit.h>

FOUNDATION_EXPORT double SolasVersionNumber;
FOUNDATION_EXPORT const unsigned char SolasVersionString[];

#import "SLSAnimationSource.h"
#import "SLSApplicationMain.h"
#import "SLSDefines.h"
#import "SLSDisplayDelegate.h"
#import "SLSDisplayLink.h"
#import "SLSDisplaySource.h"
#import "SLSEventDelegate.h"
#import "SLSEvents.h"
#import "SLSEventSource.h"
#import "SLSNSBundle+Bundle.h"

#import "SLSNSApplicationDelegate.h"
#import "SLSNSEventSourceView.h"
#import "SLSNSOpenGL3View.h"
#import "SLSNSOpenGL4View.h"
#import "SLSNSOpenGLLayer.h"
#import "SLSNSOpenGLView.h"
#import "SLSNSQuartzView.h"
#import "SLSNSView.h"
#import "SLSNSViewController.h"
#import "SLSNSWindowController.h"

#import "SLSUIApplicationDelegate.h"
#import "SLSUIEventSourceView.h"
#import "SLSUIOpenGLES2View.h"
#import "SLSUIOpenGLES3View.h"
#import "SLSUIOpenGLESView.h"
#import "SLSUIQuartzView.h"
#import "SLSUIView.h"
#import "SLSUIViewController.h"
