//
//  EPErrors.h
//  ExecutionPolicy
//
#import <Foundation/Foundation.h>

extern NSErrorDomain const EPErrorDomain API_AVAILABLE(macos(10.15));

typedef NS_ERROR_ENUM(EPErrorDomain, EPError) {
    EPErrorGeneric = 1,
    EPErrorNotADeveloperTool,
} API_AVAILABLE(macos(10.15));
