//
//  EPDeveloperTool.h
//  ExecutionPolicy
//
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, EPDeveloperToolStatus) {
    EPDeveloperToolStatusNotDetermined = 0,
    EPDeveloperToolStatusRestricted,
    EPDeveloperToolStatusDenied,
    EPDeveloperToolStatusAuthorized,
} API_AVAILABLE(macos(10.15));


NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(macos(10.15), macCatalyst(13.0))
@interface EPDeveloperTool : NSObject

/// Initializes the object to manage the lifetime of the XPC connection.
///
/// The XPC connection remains for the lifecycle of the object and deallocation is
/// required to trigger the teardown of the XPC connection.
- (instancetype)init;

/// The current authorization status of the current process.
/// - Returns: An EPDeveloperToolStatus indicating whether the current process has developer tool privileges.
@property (readonly) EPDeveloperToolStatus authorizationStatus;

///
///  Checks whether developer tool privileges are already available and if not
///  populates an entry in Settings for user approval.
///
///  This method does not show any UI to the user or guide them towards Settings for approval, if necessary.
///
/// - Parameter handler: A block called asynchronously with whether the privilege is available.
///
/// > New info
/// > Concurrency Note: You can call this method from synchronous code using a completion handler,
/// > as shown on this page, or you can call it as an asynchronous method that has the
/// > following declaration:
/// >
/// > ```swift
/// > func requestAccess() async -> Bool
/// > ```
/// >
/// > For information about concurrency and asynchronous code in Swift, see <doc://com.apple.documentation/documentation/swift/calling-objective-c-apis-asynchronously>.
- (void)requestDeveloperToolAccessWithCompletionHandler:(void (^)(BOOL granted))handler;

@end

NS_ASSUME_NONNULL_END
