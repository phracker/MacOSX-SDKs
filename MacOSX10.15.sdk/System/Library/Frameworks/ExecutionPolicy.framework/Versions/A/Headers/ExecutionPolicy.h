//
//  ExecutionPolicy.h
//  ExecutionPolicy
//
#import <Foundation/Foundation.h>

#import "EPDeveloperTool.h"
#import "EPErrors.h"

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.15))
@interface EPExecutionPolicy : NSObject

/*!
 @method init
 Initialization sets up the IPC resources required, allowing the caller to manage the initialization overhead.
 */
- (instancetype)init;

/*!
 @method addPolicyExceptionForURL
 Creates a system-wide exception to bypass execution policy for the bundle or executable at
 the given location.

 @param url Location of the bundle or executable that requires an exception
 @param error Upon failure, will contain an autoreleasing NSError indicating additional failure information

 @return A BOOL indicating the policy exception was created successfully, with
 any failures reported in the error output.
 */
- (BOOL)addPolicyExceptionForURL:(NSURL*)url error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
