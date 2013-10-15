/*	CFNotificationCenter.h
	Copyright (c) 1998-2013, Apple Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNOTIFICATIONCENTER__)
#define __COREFOUNDATION_CFNOTIFICATIONCENTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDictionary.h>

CF_EXTERN_C_BEGIN

typedef struct __CFNotificationCenter * CFNotificationCenterRef;

typedef void (*CFNotificationCallback)(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo);

typedef CF_ENUM(CFIndex, CFNotificationSuspensionBehavior) {
    CFNotificationSuspensionBehaviorDrop = 1,
        // The server will not queue any notifications with this name and object while the process/app is in the background.
    CFNotificationSuspensionBehaviorCoalesce = 2,
        // The server will only queue the last notification of the specified name and object; earlier notifications are dropped. 
    CFNotificationSuspensionBehaviorHold = 3,
        // The server will hold all matching notifications until the queue has been filled (queue size determined by the server) at which point the server may flush queued notifications.
    CFNotificationSuspensionBehaviorDeliverImmediately = 4
        // The server will deliver notifications matching this registration whether or not the process is in the background.  When a notification with this suspension behavior is matched, it has the effect of first flushing any queued notifications.
};

CF_EXPORT CFTypeID CFNotificationCenterGetTypeID(void);

CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetLocalCenter(void);

#if (TARGET_OS_MAC && !(TARGET_OS_EMBEDDED || TARGET_OS_IPHONE)) || TARGET_OS_WIN32
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDistributedCenter(void);
#endif

CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDarwinNotifyCenter(void);
// The Darwin Notify Center is based on the <notify.h> API.
// For this center, there are limitations in the API. There are no notification "objects",
// "userInfo" cannot be passed in the notification, and there are no suspension behaviors
// (always "deliver immediately"). Other limitations in the <notify.h> API as described in
// that header will also apply.
// - In the CFNotificationCallback, the 'object' and 'userInfo' parameters must be ignored.
// - CFNotificationCenterAddObserver(): the 'object' and 'suspensionBehavior' arguments are ignored.
// - CFNotificationCenterAddObserver(): the 'name' argument may not be NULL (for this center).
// - CFNotificationCenterRemoveObserver(): the 'object' argument is ignored.
// - CFNotificationCenterPostNotification(): the 'object', 'userInfo', and 'deliverImmediately' arguments are ignored.
// - CFNotificationCenterPostNotificationWithOptions(): the 'object', 'userInfo', and 'options' arguments are ignored.
// The Darwin Notify Center has no notion of per-user sessions, all notifications are system-wide.
// As with distributed notifications, the main thread's run loop must be running in one of the
// common modes (usually kCFRunLoopDefaultMode) for Darwin-style notifications to be delivered.
// NOTE: NULL or 0 should be passed for all ignored arguments to ensure future compatibility.


CF_EXPORT void CFNotificationCenterAddObserver(CFNotificationCenterRef center, const void *observer, CFNotificationCallback callBack, CFStringRef name, const void *object, CFNotificationSuspensionBehavior suspensionBehavior);

CF_EXPORT void CFNotificationCenterRemoveObserver(CFNotificationCenterRef center, const void *observer, CFStringRef name, const void *object);
CF_EXPORT void CFNotificationCenterRemoveEveryObserver(CFNotificationCenterRef center, const void *observer);

CF_EXPORT void CFNotificationCenterPostNotification(CFNotificationCenterRef center, CFStringRef name, const void *object, CFDictionaryRef userInfo, Boolean deliverImmediately);

enum {
    kCFNotificationDeliverImmediately = (1UL << 0),
    kCFNotificationPostToAllSessions = (1UL << 1)
};

CF_EXPORT void CFNotificationCenterPostNotificationWithOptions(CFNotificationCenterRef center, CFStringRef name, const void *object, CFDictionaryRef userInfo, CFOptionFlags options);


CF_EXTERN_C_END

#endif /* ! __COREFOUNDATION_CFNOTIFICATIONCENTER__ */

