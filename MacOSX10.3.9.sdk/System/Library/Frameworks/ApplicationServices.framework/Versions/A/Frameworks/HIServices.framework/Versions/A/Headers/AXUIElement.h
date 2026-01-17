/*
 *  AXUIElement.h
 *
 *  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 */

#ifndef __AXUIELEMENT__
#define __AXUIELEMENT__

#ifdef __cplusplus
extern "C" {
#endif

#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>

extern Boolean AXAPIEnabled ();

typedef const struct __AXUIElement *AXUIElementRef;

extern CFTypeID	AXUIElementGetTypeID (void);

extern AXError 	AXUIElementCopyAttributeNames (AXUIElementRef element, CFArrayRef *names);
extern AXError	AXUIElementCopyAttributeValue (AXUIElementRef element, CFStringRef attribute, CFTypeRef *value);
extern AXError  AXUIElementGetAttributeValueCount (AXUIElementRef element, CFStringRef attribute, CFIndex *count);
extern AXError  AXUIElementCopyAttributeValues (AXUIElementRef element, CFStringRef attribute, CFIndex index, CFIndex maxValues, CFArrayRef *values);
extern AXError 	AXUIElementIsAttributeSettable (AXUIElementRef element, CFStringRef attribute, Boolean *settable);
extern AXError 	AXUIElementSetAttributeValue (AXUIElementRef element, CFStringRef attribute, CFTypeRef value);

extern AXError	AXUIElementCopyParameterizedAttributeNames (AXUIElementRef element, CFArrayRef *names);
extern AXError	AXUIElementCopyParameterizedAttributeValue (AXUIElementRef element, CFStringRef parameterizedAttribute, CFTypeRef parameter, CFTypeRef *result);

extern AXError 	AXUIElementCopyActionNames (AXUIElementRef element, CFArrayRef *names);
extern AXError	AXUIElementCopyActionDescription (AXUIElementRef element, CFStringRef action, CFStringRef *description);
extern AXError 	AXUIElementPerformAction (AXUIElementRef element, CFStringRef action);

extern AXError	AXUIElementCopyElementAtPosition (AXUIElementRef application, float x,float y, AXUIElementRef *element);

extern AXUIElementRef  AXUIElementCreateApplication (pid_t pid);
extern AXUIElementRef  AXUIElementCreateSystemWide (void);

extern AXError  AXUIElementGetPid (AXUIElementRef element, pid_t *pid);

// see CGRemoteOperation.h for documentation of parameters
// you can only pass the root or application uielement
extern AXError AXUIElementPostKeyboardEvent (AXUIElementRef application, CGCharCode keyChar, CGKeyCode virtualKey, Boolean keyDown);


// Notification APIs
typedef struct __AXObserver *AXObserverRef;

typedef void (*AXObserverCallback)(AXObserverRef observer, AXUIElementRef element, CFStringRef notification, void *refcon);

CFTypeID AXObserverGetTypeID (void);

extern AXError AXObserverCreate (pid_t application, AXObserverCallback callback, AXObserverRef *outObserver);

extern AXError AXObserverAddNotification (AXObserverRef observer, AXUIElementRef element, CFStringRef notification, void *refcon);
extern AXError AXObserverRemoveNotification (AXObserverRef observer, AXUIElementRef element, CFStringRef notification);

extern CFRunLoopSourceRef AXObserverGetRunLoopSource (AXObserverRef observer);

#ifdef __cplusplus
}
#endif

#endif // __AXUIELEMENT__
