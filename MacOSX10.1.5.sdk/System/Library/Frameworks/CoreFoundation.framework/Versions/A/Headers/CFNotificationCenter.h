/*	CFNotificationCenter.h
	Copyright 1998-2001, Apple, Inc. All rights reserved.
*/

#if !defined(__COREFOUNDATION_CFNOTIFICATIONCENTER__)
#define __COREFOUNDATION_CFNOTIFICATIONCENTER__ 1

#include <CoreFoundation/CFBase.h>
#include <CoreFoundation/CFDictionary.h>

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct __CFNotificationCenter * CFNotificationCenterRef;

typedef void (*CFNotificationCallback)(CFNotificationCenterRef center, void *observer, CFStringRef name, const void *object, CFDictionaryRef userInfo);

typedef enum {
    CFNotificationSuspensionBehaviorDrop = 1,
        // The server will not queue any notifications with this name and object until CFNotificationCenterSetSuspended(false) is called.
    CFNotificationSuspensionBehaviorCoalesce = 2,
        // The server will only queue the last notification of the specified name and object; earlier notifications are dropped.  In cover methods for which suspension behavior is not an explicit argument, NSNotificationSuspensionBehaviorCoalesce is the default.
    CFNotificationSuspensionBehaviorHold = 3,
        // The server will hold all matching notifications until the queue has been filled (queue size determined by the server) at which point the server may flush queued notifications.
    CFNotificationSuspensionBehaviorDeliverImmediately = 4
        // The server will deliver notifications matching this registration irrespective of whether CFNotificationCenterSetSuspended(false) has been called.  When a notification with this suspension behavior is matched, it has the effect of first flushing any queued notifications.  The effect is somewhat as if CFNotificationCenterSetSuspended(false) were first called if the app is suspended, followed by the notification in question being delivered, followed by a transition back to the previous suspended or unsuspended state.
} CFNotificationSuspensionBehavior;

CF_EXPORT CFTypeID CFNotificationCenterGetTypeID(void);

// Getting an instance
CF_EXPORT CFNotificationCenterRef CFNotificationCenterGetDistributedCenter(void);

// Adding/removing observers
CF_EXPORT void CFNotificationCenterAddObserver(CFNotificationCenterRef center, const void *observer, CFNotificationCallback callBack, CFStringRef name, const void *object, CFNotificationSuspensionBehavior suspensionBehavior);

CF_EXPORT void CFNotificationCenterRemoveObserver(CFNotificationCenterRef center, const void *observer, CFStringRef name, const void *object);
CF_EXPORT void CFNotificationCenterRemoveEveryObserver(CFNotificationCenterRef center, const void *observer);

// Posting
CF_EXPORT void CFNotificationCenterPostNotification(CFNotificationCenterRef center, CFStringRef name, const void *object, CFDictionaryRef userInfo, Boolean deliverImmediately);

#if defined(__cplusplus)
}
#endif

#endif /* ! __COREFOUNDATION_CFNOTIFICATIONCENTER__ */

