/*	CFNotificationCenter.h
	Copyright 1998-2002, Apple, Inc. All rights reserved.
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
        // The server will not queue any notifications with this name and object while the process/app is in the background.
    CFNotificationSuspensionBehaviorCoalesce = 2,
        // The server will only queue the last notification of the specified name and object; earlier notifications are dropped. 
    CFNotificationSuspensionBehaviorHold = 3,
        // The server will hold all matching notifications until the queue has been filled (queue size determined by the server) at which point the server may flush queued notifications.
    CFNotificationSuspensionBehaviorDeliverImmediately = 4
        // The server will deliver notifications matching this registration whether or not the process is in the background.  When a notification with this suspension behavior is matched, it has the effect of first flushing any queued notifications.
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

