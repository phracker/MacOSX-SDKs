/*
     File:       HIToolbox/HIObject.h
 
     Contains:   Base object for HIToolbox
 
     Version:    HIToolbox-227.3~63
 
     Copyright:  © 2001-2006 by Apple Computer, Inc., all rights reserved.
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __HIOBJECT__
#define __HIOBJECT__

#ifndef __CORESERVICES__
#include <CoreServices/CoreServices.h>
#endif

#ifndef __COREFOUNDATION__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifndef __CARBONEVENTSCORE__
#include <HIToolbox/CarbonEventsCore.h>
#endif



#include <AvailabilityMacros.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*
 *  HIObject
 *  
 *  Discussion:
 *    HIObject is the HIToolbox's base class for various objects. Over
 *    time, all of our common objects (controls, windows, menus, etc.)
 *    will be derived from HIObject. Code which is external to
 *    HIToolbox can also create its own subclasses of our objects using
 *    the routines contained in this file. There are also polymorphic
 *    functions one can use on any HIObject for getting the class ID,
 *    etc. 
 *    
 *    HIObjects are actually CF types under the hood. This means that
 *    they can be put into CF collections and retain/release can be
 *    called on them. 
 *    
 *    An HIObject is essentially a very basic building-block object
 *    which contains an event target. You can create these objects to
 *    use as your own Carbon Event receptors in your application, or
 *    you can subclass existing Toolbox object to suit your needs.
 *    
 *    
 *    You register your subclasses with HIObjectRegisterSubclass,
 *    passing your class ID, the parent class, and an event handler.
 *    You also pass a list of events the handler is interested in.
 *    
 *    
 *    To create an object of your subclass, you call HIObjectCreate,
 *    passing the class ref you registered, as well as an
 *    initialization event. 
 *    
 *    Construction is two-phase: first the basic construction of the
 *    object is done, then initialization is performed. The toolbox
 *    sends construction events bottom-up, as you would expect in C++
 *    or the like. Here is the list of what goes on to create an
 *    object: 
 *    
 *    1)  The Toolbox creates the base HIObject 
 *    
 *    2)  It then installs the event handler you specified when you
 *    registered your subclass. Your handler must listen for
 *    kEventHIObjectConstruct and kEventHIObjectDestruct events. If it
 *    does not, the class cannot be registered (you will get a
 *    paramErr). 
 *    
 *    3)  Next, the Toolbox _directly_ calls your handler with an
 *    kEventHIObjectConstruct event. When called like this, you are not
 *    really being called in the context of a handler stack, so you
 *    cannot do things like CallNextEventHandler. The userData
 *    parameter is what you specified when you registered the class.
 *    Typically, during construction you will allocate memory yourself
 *    to store your own instance data; this allocation might be as
 *    simple as calling malloc or NewPtr, or it might involve creating
 *    your own C++ object. In the construct event, you are passed the
 *    base HIObjectRef of the object being created. Typically you would
 *    store this HIObjectRef in your own instance data for later use.
 *    When handling this construct event, you should be sure to use
 *    SetEventParameter to set the kEventParamHIObjectInstance
 *    parameter in the construction event with your own instance data.
 *    You must use typeVoidPtr as the type. 
 *    
 *    4)  The Toolbox looks for your instance of typeVoidPtr after you
 *    handle the construct event. It then takes that data and stores it
 *    off with the object and also sets the user data of the event
 *    handler it installed to be this instance data. This means that
 *    following the construct event, all calls to your event handler
 *    will have the instance data you returned to us. 
 *    
 *    5)  Once construction has completed successfully, we will send
 *    your object the initialize event passed into HIObjectCreate. At
 *    this point, all events are now sent to your object using standard
 *    Carbon Events mechanisms (it is only the construct event which is
 *    special). When we send the initialization event to your subclass,
 *    you should pass the event to your superclass before proceeding.
 *    You do this with CallNextEventHandler. Once back from that call,
 *    you should verify that the result is noErr, indicating that the
 *    superclass did in fact initialize properly. If it did not, your
 *    should return the error that CallNextEventHandler returned from
 *    your handler as well. The object will be destroyed by the
 *    Toolbox. Your object should be able to be destroyed in a
 *    partially initialized state such as this. This stage is optional,
 *    i.e. an object does not need to respond to the initialize event
 *    unless it is expecting certain parameters to be passed to it at
 *    creation time. This is where those parameters can be fetched.
 *    
 *    
 *    6)  Once initialization is successful, the HIObjectRef is
 *    returned to the caller of HIObjectCreate. From there, you can
 *    have all sorts of cool fun. 
 *    
 *    When someone has called CFRelease enough such that the refcount
 *    of the object drops to zero, the object is destroyed. The Toolbox
 *    will send a kEventHIObjectDestruct event to your object. DO NOT
 *    CALL CALLNEXTEVENTHANDLER. You will be setting yourself up for
 *    some hurt. Just clean up and return from your handler.
 */
typedef struct OpaqueHIObjectClassRef*  HIObjectClassRef;
typedef struct OpaqueHIObjectRef*       HIObjectRef;

/*
 *  Discussion:
 *    HIObject errors
 */
enum {

  /*
   * You are trying to register a class ID that already exists.
   */
  hiObjectClassExistsErr        = -22080,

  /*
   * You are trying to unregister a class which has instances which
   * still exist. You must destroy them first, before they destroy you!
   */
  hiObjectClassHasInstancesErr  = -22081,
  hiObjectClassHasSubclassesErr = -22082,

  /*
   * You are trying to create an HIObject class that is defined as
   * being abstract. You must subclass it instead. Oh yes. Don't make
   * us say it twice!
   */
  hiObjectClassIsAbstractErr    = -22083
};


/*
 */
enum {

  /*
   * The event class for HIObject events.
   */
  kEventClassHIObject           = 'hiob'
};

enum {
  kEventParamHIObjectInstance   = 'hioi',
  kEventParamHIArchive          = 'hiac', /* typeCFTypeRef */
  typeHIObjectRef               = 'hiob'
};

/*
    kEventClassHIObject quick reference:
    
    These are the events for base class functionality of HIObjects. You should only need to be
    aware of these if you are implementing a subclass of HIObject.
    
    kEventHIObjectConstruct         = 1,
    kEventHIObjectInitialize        = 2,
    kEventHIObjectDestruct          = 3,
    kEventHIObjectIsEqual           = 4,
    kEventHIObjectPrintDebugInfo    = 5,
    kEventHIObjectEncode            = 6
*/
/*
 *  kEventClassHIObject / kEventHIObjectConstruct
 *  
 *  Summary:
 *    Your object is being constructed. You should allocate instance
 *    data for your object.
 *  
 *  Discussion:
 *    When your event handler is called with this event, it is being
 *    called directly and not through the normal event dispatching
 *    mechanism. This means that the EventHandlerCallRef passed to your
 *    handler will be NULL and CallNextEventHandler will not work. You
 *    are passed the actual HIObjectRef of your base class for you to
 *    record in your instance data.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    <-> kEventParamHIObjectInstance (in/out, typeHIObjectRef)
 *          On entry, this parameter is typeHIObjectRef, and is the
 *          HIObjectRef of your instanceÕs base class. Typically you
 *          will read this parameter from the event and store it in
 *          your instance data so that when your instance needs to call
 *          HIObject APIs, it can use this HIObjectRef.
 *          
 *          On exit, this parameter is typeVoidPtr, and should be a
 *          pointer to your instance data that you have written into
 *          the event with SetEventParameter. After your event handler
 *          returns, the toolbox reads your instance data pointer from
 *          the event, installs the event handlers that were passed to
 *          HIObjectRegisterSubclass on the new object, and uses the
 *          instance data pointer as the refcon for those event
 *          handlers. This allows your event handlers to retrieve your
 *          instance data pointer from the refcon.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectConstruct       = 1
};

/*
 *  kEventClassHIObject / kEventHIObjectInitialize
 *  
 *  Summary:
 *    Your object is being initialized. You should read initialization
 *    data from the event and store it into your instance data.
 *  
 *  Discussion:
 *    Your handler should pass this event on to the superclass first
 *    before handling this event. This is done by calling
 *    CallNextEventHandler with the event. When that function returns,
 *    you should make sure the result is noErr. If not, you should NOT
 *    continue to initialize your class.
 *    
 *    Assuming that CallNextEventHandler returned noErr, you may then
 *    proceed to read initialization data from the event parameters, if
 *    any. For example, you might be create an object that includes a
 *    string as part of its instance data. The caller of HIObjectCreate
 *    would create an EventRef and add a string to the event using a
 *    parameter name and type defined by your object. In your objectÕs
 *    kEventHIObjectInitialize event handler, you would read the string
 *    from the event parameter and store it into your instance
 *    data.
 *    
 *    The parameters of this event, therefore, contain the union of all
 *    parameters needed by all base classes of this object to properly
 *    construct themselves.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamHIArchive (in, typeCFTypeRef)
 *          The HIArchive reference from which the HIObject should be
 *          decoded. This parameter will only exist when the HIObject
 *          is requested to initialize itself from a decoded archive. 
 *          Otherwise, the HIObject should initialize itself normally.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectInitialize      = 2
};

/*
 *  kEventClassHIObject / kEventHIObjectDestruct
 *  
 *  Summary:
 *    Your object is being destroyed. This is your chance to dispose of
 *    anything you might have allocated for your objectÕs instance data.
 *  
 *  Discussion:
 *    Do NOT call through with CallNextEventHandler, as you will
 *    disrupt the fabric of space-time. An HIObject is destroyed in
 *    most-derived to least-derived order, and if you call through,
 *    your base class can be destroyed before you destroy your own
 *    data, which can cause undefined results.
 *    
 *    Note that the refcon of your event handler for this event will be
 *    the instance data pointer allocated and returned by your
 *    kEventHIObjectConstruct handler in the
 *    kEventParamHIObjectInstance parameter.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectDestruct        = 3
};

/*
 *  kEventClassHIObject / kEventHIObjectIsEqual
 *  
 *  Summary:
 *    HIObjectIsEqual has been called, and you are being asked to
 *    determine if your object is equivalent to the one being passed to
 *    your handler.
 *  
 *  Discussion:
 *    The base HIObject class handles this event by comparing the
 *    HIObjectRef values for pointer equality. Your subclass may choose
 *    to also compare the contents of the HIObject instance data.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamDirectObject (in, typeHIObjectRef)
 *          The object to which your object should be compared.
 *    
 *    <-- kEventParamResult (out, typeBoolean)
 *          If your object is equivalent to the direct object, you
 *          should return true in this parameter; otherwise, return
 *          false.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectIsEqual         = 4
};

/*
 *  kEventClassHIObject / kEventHIObjectPrintDebugInfo
 *  
 *  Summary:
 *    HIObjectPrintDebugInfo has been called, and you are being asked
 *    to print your information to stdout.
 *  
 *  Discussion:
 *    This event is sent to all handlers registered for it. You should
 *    NOT call CallNextEventHandler.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectPrintDebugInfo  = 5
};

/*
 *  kEventClassHIObject / kEventHIObjectEncode
 *  
 *  Summary:
 *    Your object is being requested to encode itself into an archive.
 *  
 *  Discussion:
 *    Your handler should pass this event on to the superclass first
 *    before handling this event. This is done by calling
 *    CallNextEventHandler with the event. When that function returns,
 *    you should make sure the result is noErr. If not, you should NOT
 *    continue to initialize your class.
 *    
 *    HIArchiveEncodeHIObject has been called on your HIObject. At this
 *    point all relevant long term data should be encoded to the
 *    HIArchive provided.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    --> kEventParamHIArchive (in, typeCFTypeRef)
 *          The HIArchive reference into which the HIObject should be
 *          compiled.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 */
enum {
  kEventHIObjectEncode          = 6
};

/*
 *  HIObjectRegisterSubclass()
 *  
 *  Discussion:
 *    Registers a class with the Toolbox for creation later.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inClassID:
 *      The class ID of your class. It should be unique. We recommend
 *      using Java-style com.company.foo naming conventions to avoid
 *      collisions.
 *    
 *    inBaseClassID:
 *      The class ID of the class you derive from. Passing NULL
 *      indicates you wish to subclass HIObject (the base class)
 *      directly.
 *    
 *    inOptions:
 *      Any special options for your class. Currently you must pass 0
 *      for this parameter.
 *    
 *    inConstructProc:
 *      The construction proc for this subclass. You pass the address
 *      of an event handler into this parameter. This handler is called
 *      directly, rather than through the normal event dispatching
 *      mechanism. This means that the EventHandlerCallRef passed in
 *      will be NULL, and you cannot use it for calls like
 *      CallNextEventHandler. Other than that, you should return a
 *      result as usual. After your object is constructed, this proc
 *      will be installed as the event handler for the remaining events
 *      specified in the inEventList parameter. On Mac OS X 10.4 and
 *      later, you may pass NULL to create an "abstract class" that
 *      cannot be instantiated, but can still be used as a base class
 *      for subclasses; if you pass NULL, HIObjectCreate on the class
 *      ID will return hiObjectClassIsAbstractErr.
 *    
 *    inNumEvents:
 *      The number of events you are installing.
 *    
 *    inEventList:
 *      The events your handler wishes to receive. If you are not
 *      creating an abstract class, then you must handle the
 *      kEventHIObjectConstruct and kEventHIObjectDestruct event. If
 *      these events are not specified, an error is returned. An
 *      abstract class may pass 0 for the inNumEvents parameter and
 *      NULL for the inEventList parameter.
 *    
 *    inConstructData:
 *      Pass any info you want passed into your event handler here. For
 *      a C++ hierarchy based on HIObjects, you might actually pass a
 *      static method to construct your object here, and the base class
 *      event handler to do construction as your event handler.
 *    
 *    outClassRef:
 *      The newly created class reference. Pass NULL if you don't care.
 *  
 *  Result:
 *    An operating system result code.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectRegisterSubclass(
  CFStringRef            inClassID,
  CFStringRef            inBaseClassID,
  OptionBits             inOptions,
  EventHandlerUPP        inConstructProc,       /* can be NULL */
  UInt32                 inNumEvents,
  const EventTypeSpec *  inEventList,
  void *                 inConstructData,
  HIObjectClassRef *     outClassRef)           /* can be NULL */ AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectUnregisterClass()
 *  
 *  Discussion:
 *    Unregisters a previously registered subclass of HIObject. You
 *    will receive an error if there are subclasses of your class or
 *    instances of it which still exist. All instances and subclasses
 *    must be disposed of and unregistered first.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inClassRef:
 *      The class ref of the class of object you wish to unregister.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectUnregisterClass(HIObjectClassRef inClassRef)          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectCreate()
 *  
 *  Discussion:
 *    Creates an object derived from HIObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inClassID:
 *      The class ID of the class of object you wish to instantiate.
 *    
 *    inConstructData:
 *      If your class (or any class you derive from) accepts creation
 *      parameters, you need to pass an event into this parameter. The
 *      class must be kEventClassHIObject, and the kind should be
 *      kEventHIObjectInitialize. Any other parameters should be added
 *      as necessary. Specific subclasses of HIObject which require
 *      initialization parameters will specify those parameters in the
 *      appropriate headers.
 *    
 *    outObject:
 *      The instance of the object you create.
 *  
 *  Result:
 *    An operating system result code. A return value of
 *    hiObjectClassIsAbstractErr indicates that the inConstructProc
 *    parameter to HIObjectRegisterSubclass was NULL; instances of such
 *    a class may not be created, only subclassed.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectCreate(
  CFStringRef    inClassID,
  EventRef       inConstructData,
  HIObjectRef *  outObject)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectGetEventTarget()
 *  
 *  Discussion:
 *    Returns the event target of an HIObjectRef.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose target you want.
 *  
 *  Result:
 *    An EventTargetRef.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern EventTargetRef 
HIObjectGetEventTarget(HIObjectRef inObject)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectPrintDebugInfo()
 *  
 *  Discussion:
 *    Prints the internal information of an HIObject for debugging
 *    purposes. It outputs the info to stdout.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object to inspect.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern void 
HIObjectPrintDebugInfo(HIObjectRef inObject)                  AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectCopyClassID()
 *  
 *  Discussion:
 *    Returns the class ID of a given HIObject.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose class ID you are interested in.
 *  
 *  Result:
 *    A CFStringRef containing the object's class ID.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern CFStringRef 
HIObjectCopyClassID(HIObjectRef inObject)                     AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectIsOfClass()
 *  
 *  Discussion:
 *    Returns whether or not an object is of a certain class. You can
 *    us this to see whether or not an object you have derives from an
 *    expected superclass.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose class ID you wish to check.
 *    
 *    inObjectClassID:
 *      The class ID in question.
 *  
 *  Result:
 *    A Boolean result indicating whether or not the object is of the
 *    class specified.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIObjectIsOfClass(
  HIObjectRef   inObject,
  CFStringRef   inObjectClassID)                              AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectDynamicCast()
 *  
 *  Discussion:
 *    Returns the instance data for a specific class of an HIObject.
 *    The instance data returned is the same instance data the class's
 *    construction event handler returns in the instance data
 *    parameter. This is stored off with the class reference so that it
 *    can be fetched later for use by this function. It allows your
 *    subclass to easily get at the data it created, if your subclass
 *    needs that data outside of an event handler. (Inside an event
 *    handler, your subclass can get at its instance data via the
 *    userData parameter to the event handler.)
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose class ID you wish to check.
 *    
 *    inClassID:
 *      The class ID to get the instance data for.
 *  
 *  Result:
 *    A void * result which contains the instance data for the object,
 *    or NULL if the object is not an instance of the class.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern void * 
HIObjectDynamicCast(
  HIObjectRef   inObject,
  CFStringRef   inClassID)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectCreateFromBundle()
 *  
 *  Discussion:
 *    Returns the HIObject for the given bundle. A bundle can be
 *    designed to communicate with an app through an HIObject. The
 *    bundle must be designed to create an HIObject and have a defined
 *    suite of CarbonEvents that clients can use to communicate with
 *    the bundle's HIObject. Given a CFBundleRef, this API will tell
 *    the bundle to create the HIObject and return it to the caller.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inBundle:
 *      The bundle that you wish to communicate with.
 *    
 *    outObject:
 *      The HIObject associated with the bundle.
 *  
 *  Result:
 *    An operating system result code. If the bundle's HIObject
 *    creation function cannot be found, cfragNoSymbolErr will be
 *    returned.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectCreateFromBundle(
  CFBundleRef    inBundle,
  HIObjectRef *  outObject)                                   AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectIsAccessibilityIgnored()
 *  
 *  Discussion:
 *    Reports whether or not the given HIObject is marked as ignored
 *    for accessibility. 
 *    
 *    See the discussion of HIObjectSetAccessibilityIgnored for details
 *    on what it means to be accessibility ignored.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose accessibility ignored state you wish to query.
 *  
 *  Result:
 *    A Boolean value indicating whether or not the HIObject is ignored
 *    for accessibility.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIObjectIsAccessibilityIgnored(HIObjectRef inObject)          AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectSetAccessibilityIgnored()
 *  
 *  Discussion:
 *    Marks an HIObject as ignored (or not) for the purposes of the
 *    accessibility APIs. 
 *    
 *    An HIObject that is ignored for accessibility will never be shown
 *    to an assistive application that uses the accessibility APIs to
 *    examine an interface. Your application's accessibility
 *    implementation can (and should) still report an ignored HIObject
 *    as usual. Carbon's accessibility engine will automatically prune
 *    any ignored HIObjects out of the data that is shown to an
 *    assistive application. 
 *    <BR>By default, an HIObject is *not* accessibility ignored.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose accessibility ignored state you wish to change.
 *    
 *    inIgnored:
 *      A Boolean value indicating whether or not to ignore the object.
 *  
 *  Result:
 *    An OSStatus signifying success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.2 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.2 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectSetAccessibilityIgnored(
  HIObjectRef   inObject,
  Boolean       inIgnored)                                    AVAILABLE_MAC_OS_X_VERSION_10_2_AND_LATER;


/*
 *  HIObjectSetAuxiliaryAccessibilityAttribute()
 *  
 *  Summary:
 *    Associates an additional accessibility attribute with a UIElement
 *    that is used to represent a given HIObject or a part thereof.
 *  
 *  Discussion:
 *    This routine lets your application provide the name of and data
 *    for an accessibility attribute that you want to add to the
 *    UIElement used to represent a given HIObject-identifier pair.
 *    Normally, accessibility attributes can only be supplied
 *    dynamically via Carbon Events, but this routine allows you to
 *    supply them statically. 
 *    
 *    When an accessibility attribute Carbon Event is handled by the
 *    HIObject with a given identifier, the toolbox automatically
 *    supplies the names and/or values of any auxiliary attributes
 *    associated with that HIObject- identifier pair. 
 *    
 *    This routine is particularly useful for supplying values for the
 *    kAXDescriptionAttribute, kAXTitleUIElementAttribute,
 *    kAXServesAsTitleUIElementAttribute, kAXLinkedUIElementsAttribute
 *    and other attributes whose value is specific to the layout and
 *    usage of your application. 
 *    
 *    This routine only allows you to associate attributes whose values
 *    never change. If you need to supply attributes whose values are
 *    determined dynamically or whose values are settable, you must
 *    install the normal accessibility Carbon Event handlers. 
 *    
 *    The auxiliary attribute store is consulted during the HIObject's
 *    default handling of the accessibility attribute Carbon Events.
 *    This means that any programmatic handling of a given
 *    accessibility attribute will have a chance to override or block
 *    the consultation of the store. The general rule is that if the
 *    toolbox or a Carbon Event handler can provide the attribute value
 *    some other way, the store will not be consulted.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inHIObject:
 *      The HIObjectRef part of the object-identifier pair to which the
 *      attribute data is associated.
 *    
 *    inIdentifier:
 *      The 64-bit identifier part of the object-identifier pair to
 *      which the attribute data is associated. When you want to
 *      associate the attribute data to the HIObject as a whole -- such
 *      as when you want to give a description attribute to a push
 *      button -- you should pass zero in this parameter.
 *    
 *    inAttributeName:
 *      A CFStringRef of the name of the attribute you wish to
 *      associate with the object-identifier pair. This string will be
 *      retained before adding it to the auxiliary attribute store.
 *    
 *    inAttributeData:
 *      A CFTypeRef with the data to be supplied as the attribute's
 *      value. This data will be retained before adding it to the
 *      auxiliary attribute store; you may release inAttributeData
 *      after you have called this routine. The inAttributeData
 *      parameter may also be NULL, which indicates that the named
 *      auxiliary attribute should no longer be associated with the
 *      object-identifier pair; any named attribute data previously
 *      associated with the object-identifier pair will be released.
 *  
 *  Result:
 *    An OSStatus result code. The function will return noErr if it was
 *    able to associate the attribute data with the HIObjectRef. If the
 *    HIObjectRef is invalid, paramErr will be returned. Other results
 *    may be returned in other situations.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectSetAuxiliaryAccessibilityAttribute(
  HIObjectRef   inHIObject,
  UInt64        inIdentifier,
  CFStringRef   inAttributeName,
  CFTypeRef     inAttributeData)       /* can be NULL */      AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIObjectOverrideAccessibilityContainment()
 *  
 *  Summary:
 *    Allows you to override the AXUIElementRefs that an HIObject would
 *    normally supply as the values of its AXParent, AXWindow, and
 *    AXTopLevelUIElement attributes.
 *  
 *  Discussion:
 *    This routine allows you to change the parent that an HIObject
 *    would normally supply in the accessibility hierarchy. For
 *    instance, a popup control could call this routine on its menu so
 *    that the menu returned the popup control as the menu's parent;
 *    normally the menu would return the application as its parent.
 *    Optionally, this routine also allows you to change the window and
 *    top-level element that an HIObject would normally supply. 
 *     
 *    If the input HIObject is a standard toolbox construct like an
 *    HIView or a Menu, the input HIObject will not be added as an
 *    accessibility child of its normal parent. In all other cases, it
 *    is the client's responsibility to ensure that the input HIObject
 *    is not added as an accessibility child of its normal parent. 
 *     
 *    If the desired AXUIElementRef parent represents an HIView, a
 *    Menu, or a Window, the input HIObject will be automatically added
 *    as an accessibility child of the specified parent. In all other
 *    cases, it is the client's responsibility to manually add the
 *    input HIObject as a child of the specified parent. To represent
 *    an HIView, a Menu, or a Window, an AXUIElementRef must contain
 *    the appropriate HIObjectRef as well as an identifier value of
 *    zero. 
 *    
 *    Similar rules don't have to apply for the handling of the window
 *    and top-level element attributes because those attributes don't
 *    represent two-way relationships. 
 *    
 *    A containment override is not necessarily supported by every type
 *    of HIObject. Currently, it is supported by HIViews, Menus, and
 *    Windows.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inHIObject:
 *      The HIObjectRef whose parent attribute you want to override.
 *    
 *    inDesiredParent:
 *      The AXUIElementRef that you wish the HIObject to return as the
 *      value of its AXParent attribute. This routine makes a copy of
 *      the AXUIElementRef; you must release inDesiredParent after you
 *      have called this routine. Passing NULL indicates that you want
 *      the HIObject to revert to its normal, un-overridden behavior.
 *    
 *    inDesiredWindow:
 *      The AXUIElementRef that you wish the HIObject to return as the
 *      value of its AXWindow attribute. This routine makes a copy of
 *      the AXUIElementRef; you must release inDesiredWindow after you
 *      have called this routine. Passing NULL indicates that you want
 *      the HIObject to report its normal window, if any.
 *    
 *    inDesiredTopLevelUIElement:
 *      The AXUIElementRef that you wish the HIObject to return as the
 *      value of its AXTopLevelUIElement attribute. This routine makes
 *      a copy of the AXUIElementRef; you must release
 *      inDesiredTopLevelUIElement after you have called this routine.
 *      Passing NULL indicates that you want the HIObject to report its
 *      normal top-level element, if any.
 *  
 *  Result:
 *    An OSStatus result code. If the HIObjectRef is invalid, this
 *    routine will return paramErr.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectOverrideAccessibilityContainment(
  HIObjectRef      inHIObject,
  AXUIElementRef   inDesiredParent,
  AXUIElementRef   inDesiredWindow,
  AXUIElementRef   inDesiredTopLevelUIElement)                AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIObjectIsArchivingIgnored()
 *  
 *  Discussion:
 *    Reports whether or not the given HIObject is marked as ignored
 *    for archiving.
 *    See the discussion of HIObjectSetArchivingIgnored for details on
 *    what it means to be archiving ignored.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose archiving ignored state you wish to query.
 *  
 *  Result:
 *    A Boolean value indicating whether or not the HIObject is ignored
 *    for archiving.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern Boolean 
HIObjectIsArchivingIgnored(HIObjectRef inObject)              AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIObjectSetArchivingIgnored()
 *  
 *  Discussion:
 *    Marks an HIObject as ignored (or not) for the purposes of the
 *    archiving APIs.
 *    An HIObject that is ignored for archiving will never be requested
 *    to encode itself into an archive. This is a statement that the
 *    HIObject does not handle the archiving protocol.
 *    By default, an HIObject *is* archiving ignored.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose archiving ignored state you wish to change.
 *    
 *    inIgnored:
 *      A Boolean value indicating whether or not to ignore the object.
 *  
 *  Result:
 *    An OSStatus signifying success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectSetArchivingIgnored(
  HIObjectRef   inObject,
  Boolean       inIgnored)                                    AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;



/*
   Standard custom archive data dictionary keys describing custom initialize event parameters.
   Each keyed value is an array of OSTypes represented by CFStrings. Use UTCreateStringForOSType
   and UTGetOSTypeFromString in UTType.h for CFStringRef <-> OSType conversion.
*/
/*
 *  kHIObjectCustomDataParameterNamesKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataParameterNamesKey        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kHIObjectCustomDataParameterTypesKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataParameterTypesKey        AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kHIObjectCustomDataParameterValuesKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataParameterValuesKey       AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
   Standard custom archive data dictionary keys defining a class and superclass for clients who do
   not implement the object's true class. Each keyed value is a CFStringRef based HIObject class ID.
*/
/*
 *  kHIObjectCustomDataClassIDKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataClassIDKey               AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;
/*
 *  kHIObjectCustomDataSuperClassIDKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataSuperClassIDKey          AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
   Standard custom archive data dictionary key for ProcPointer based CDEFs.  The key value is a
   CFString based SInt16. Use CFStringGetIntValue in CFString.h for CFStringRef <-> SInt16 conversion.
*/
/*
 *  kHIObjectCustomDataCDEFProcIDKey
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available
 *    Non-Carbon CFM:   not available
 */
extern const CFStringRef kHIObjectCustomDataCDEFProcIDKey            AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;

/*
 *  HIObjectCopyCustomArchiveData()
 *  
 *  Discussion:
 *    Copies the custom archive data associated with an HIObject that
 *    has been read from or will be written to an archive. Useful for
 *    an archive editor that has read a custom object from an archive
 *    and would like to edit its custom data.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose custom archive data you wish to retrieve.
 *    
 *    outCustomData:
 *      On return, a CFDictionaryRef containing the custom data. The
 *      client is responsible for releasing the dictionary. NULL will
 *      be returned if there is no custom archive data available.
 *  
 *  Result:
 *    An OSStatus signifying success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectCopyCustomArchiveData(
  HIObjectRef        inObject,
  CFDictionaryRef *  outCustomData)                           AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;


/*
 *  HIObjectSetCustomArchiveData()
 *  
 *  Discussion:
 *    Retrieves the custom archive data associated with an HIObject
 *    that has been read from or will be written to an archive. Useful
 *    for an archive editor that has edited a custom object's custom
 *    data and would like it to be written to an archive with the
 *    object.
 *  
 *  Mac OS X threading:
 *    Not thread safe
 *  
 *  Parameters:
 *    
 *    inObject:
 *      The object whose custom archive data you wish to change.
 *    
 *    inCustomData:
 *      A CFDictionaryRef containing the custom archive data you would
 *      like to associate with the object. Setting custom data will
 *      replace any existing custom data. Passing NULL will clear the
 *      custom archive data. The dictionary's keys and values must use
 *      CFType callbacks for archiving purposes.
 *  
 *  Result:
 *    An OSStatus signifying success or failure.
 *  
 *  Availability:
 *    Mac OS X:         in version 10.4 and later in Carbon.framework
 *    CarbonLib:        not available in CarbonLib 1.x, is available on Mac OS X version 10.4 and later
 *    Non-Carbon CFM:   not available
 */
extern OSStatus 
HIObjectSetCustomArchiveData(
  HIObjectRef       inObject,
  CFDictionaryRef   inCustomData)       /* can be NULL */     AVAILABLE_MAC_OS_X_VERSION_10_4_AND_LATER;




#ifdef __cplusplus
}
#endif

#endif /* __HIOBJECT__ */

