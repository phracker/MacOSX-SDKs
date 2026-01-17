//
//  FPUIBase.h
//  FileProviderUI
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <os/availability.h>
#import <TargetConditionals.h>

#define FPUI_EXPORT __attribute__((visibility("default")))
#define FPUI_AVAILABLE(...) FPUI_EXPORT API_AVAILABLE(__VA_ARGS__)
