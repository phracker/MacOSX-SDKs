/*
    File:       CMIOHardwareObject.h

    Contains:   API for communicating with CoreMediaIO hardware

    Copyright:  © 2005-2012 by Apple Inc., all rights reserved.
*/

#if !defined(__CMIOHardwareObject_h__)
#define __CMIOHardwareObject_h__

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Overview
/*!
    @header CMIOHardwareObject
    CMIOObjects all have a set of properties that describe and manipulate their state. A property is accessed via an ordered triple. The first ordinate is the selector which describes the
    property. The other two ordinates are the scope and element that identify the particular part of the object in which to look for the selector. The CMIOObjectPropertyAddress structure
    encapsulates the property address. The value of a property is an untyped block of data whose content depends on the specifics of the selector. Some selectors also require the use of a
    qualifier when querying. The qualifier allows for additional information to be provided to be used in the manipulation of the property. Changing the value of a property is always
    considered asynchronous.

    Applications use the routines CMIOObjectHasProperty(), CMIOObjectIsPropertySettable() and CMIOObjectGetPropertyDataSize() to find useful meta-information about the property. Applications
    use CMIOObjectGetPropertyData() and CMIOObjectSetPropertyData() to manipulate the value of the property. Applications use CMIOObjectAddPropertyListener() and
    CMIOObjectRemovePropertyListener() to register/unregister a function that is to be called when a given property's value changes.

    The base class for all CMIOObjects is the class CMIOObject. As such, each CMIOObject will provide basic properties such as it's class, it's human readable name, and the other
    CMIOObjects it contains.
*/

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Includes

#include <CoreFoundation/CFBase.h>
#include <dispatch/dispatch.h>

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    
#pragma pack(push, 4)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Property Support Types

/*!
    @typedef        CMIOObjectPropertySelector
    @abstract       A CMIOObjectPropertySelector is a four char code that identifies, along with the CMIOObjectPropertyScope and CMIOObjectPropertyElement, a specific piece of
                    information about a CMIOObject.
    @discussion     The property selector specifies the general classification of the property such as volume, streamID format, latency, etc. Note that each class has a different set of
                    selectors. A subclass inherits it's super class's set of selectors, although it may not implement them all.
*/
typedef UInt32 CMIOObjectPropertySelector;

/*!
    @typedef        CMIOObjectPropertyScope
    @abstract       A CMIOObjectPropertyScope is a four char code that identifies, along with the CMIOObjectPropertySelector and CMIOObjectPropertyElement, a specific piece of
                    information about a CMIOObject.
    @discussion     The scope specifies the section of the object in which to look for the property, such as input, output, global, etc. Note that each class has a different set of scopes. A
                    subclass inherits it's superclass's set of scopes.
*/
typedef UInt32 CMIOObjectPropertyScope;

/*!
    @typedef        CMIOObjectPropertyElement
    @abstract       A CMIOObjectPropertyElement is an integer that identifies, along with the CMIOObjectPropertySelector and CMIOObjectPropertyScope, a specific piece of information
                    about a CMIOObject.
    @discussion     The element selects one of possibly many items in the section of the object in which to look for the property. Elements are numbered sequentially where 0 represents the
                    master element. Elements are particular to an instance of a class, meaning that two instances can have different numbers of elements in the same scope. There is no
                    inheritance of elements.
*/
typedef UInt32 CMIOObjectPropertyElement;

/*!
    @struct         CMIOObjectPropertyAddress
    @abstract       A CMIOObjectPropertyAddress collects the three parts that identify a specific property together in a struct for easy transmission.
    @field          mSelector
                        The CMIOObjectPropertySelector for the property.
    @field          mScope
                        The CMIOObjectPropertyScope for the property.
    @field          mElement
                        The CMIOObjectPropertyElement for the property.
*/
struct CMIOObjectPropertyAddress
{
    CMIOObjectPropertySelector  mSelector;
    CMIOObjectPropertyScope     mScope;
    CMIOObjectPropertyElement   mElement;
};
typedef struct CMIOObjectPropertyAddress CMIOObjectPropertyAddress;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark Property Support Constants

/*!
    @enum           Property Wildcard Constants
    @abstract       Constants that are used as wildcards in a CMIOObjectPropertyAddress.
    @discussion     Wildcards match any and all values for there associated type. They are especially useful for registering listener procs to receive notifications and for querying an
                    CMIOObject's list of CMIOControls.
    @constant       kCMIOObjectPropertySelectorWildcard
                        The wildcard value for CMIOObjectPropertySelectors.
    @constant       kCMIOObjectPropertyScopeWildcard
                        The wildcard value for CMIOObjectPropertyScopes.
    @constant       kCMIOObjectPropertyElementWildcard
                        The wildcard value for CMIOObjectPropertyElements.
*/
enum
{
    kCMIOObjectPropertySelectorWildcard = '****',
    kCMIOObjectPropertyScopeWildcard    = '****',
    kCMIOObjectPropertyElementWildcard  = 0xFFFFFFFFUL
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOObject Types

/*!
    @typedef        CMIOClassID
    @abstract       CMIOClassIDs are used to identify the class of a CMIOObject.
*/
typedef UInt32 CMIOClassID;

/*!
    @typedef        CMIOObjectID
    @abstract       CMIOObject is the base class for all the objects in the DAL.
    @discussion     CMIOObjects have properties and can contain other CMIOObjects.
*/
typedef UInt32 CMIOObjectID;


/*!
    @typedef        CMIOObjectPropertyListenerProc
    @abstract       Clients register a CMIOObjectPropertyListenerProc with a CMIOObject in order to receive notifications when the properties of the object change.
    @discussion     Listeners will be called when possibly many properties have changed. Consequently, the implementation of a listener must go through the array of addresses to see what
                    exactly has changed. Note that the array of addresses will always have at least one address in it for which the listener is signed up to receive notifications about but
                    may contain addresses for properties for which the listener is not signed up to receive notifications.
    @param          objectID
                        The CMIOObject whose properties have changed.
    @param          numberAddresses
                        The number of elements in the addresses array.
    @param          addresses
                        An array of CMIOObjectPropertyAddresses indicating which properties changed.
    @param          clientData
                        A pointer to client data established when the listener proc was registered with the CMIOObject.
    @result         The return value is currently unused and should always be 0.
*/
typedef OSStatus
(*CMIOObjectPropertyListenerProc)(  CMIOObjectID                    objectID,
                                    UInt32                          numberAddresses,
                                    const CMIOObjectPropertyAddress addresses[],
                                    void*                           clientData);


/*!
    @typedef        CMIOObjectPropertyListenerBlock
    @abstract       Clients register an CMIOObjectPropertyListenerBlock with an CMIOObject in order to receive notifications when the properties of the object change.
    @discussion     Listeners will be called when possibly many properties have changed. Consequently, the implementation of a listener must go through the array of addresses to see what
                    exactly has changed. Note that the array of addresses will always have at least one address in it for which the listener is signed up to receive notifications about but
                    may contain addresses for properties for which the listener is not signed up to receive notifications.
    @param          numberAddresses
                        The number of elements in the addresses array.
    @param          addresses
                        An array of CMIOObjectPropertyAddresses indicating which properties changed.
*/
typedef void
(^CMIOObjectPropertyListenerBlock)( UInt32                          numberAddresses,
                                    const CMIOObjectPropertyAddress addresses[]);

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOObject Constants

/*!
    @enum           CMIOObject Class Constants
    @abstract       Various constants related to CMIOObjects.
    @discussion     
    @constant       kCMIOObjectPropertyScopeGlobal
                        The CMIOObjectPropertyScope for properties that apply to the object as a whole. All CMIOObjects have a global scope and for some it is their only scope.
    @constant       kCMIOObjectPropertyElementMaster
                        The CMIOObjectPropertyElement value for properties that apply to the master element or to the entire scope.
    @constant       kCMIOObjectClassID
                        The CMIOClassID that identifies the CMIOObject class.
    @constant       kCMIOObjectClassIDWildcard
                        The wildcard value for CMIOClassIDs.
    @constant       kCMIOObjectUnknown
                        The CMIOObjectID for a non-existant CMIOObject.
*/
enum
{
    kCMIOObjectPropertyScopeGlobal      = 'glob',
    kCMIOObjectPropertyElementMaster    = 0UL,
    kCMIOObjectClassID                  = 'aobj',
    kCMIOObjectClassIDWildcard          = '****',
    kCMIOObjectUnknown                  = 0UL
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOObject Properties

/*!
    @enum           CMIOObject Property Selectors
    @abstract       CMIOObjectPropertySelector values that apply to all CMIOObjects.
    @discussion     
    @constant       kCMIOObjectPropertyClass
                        A CMIOClassID that identifies the class of the CMIOObject.
    @constant       kCMIOObjectPropertyOwner
                        A CMIOObjectID that identifies the the CMIOObject that owns the given CMIOObject. Note that all CMIOObjects are owned by some other CMIOObject. The only exception is
                        the CMIOSystemObject, for which the value of this property is kCMIOObjectUnknown.
    @constant       kCMIOObjectPropertyCreator
                        A CFString that contains the bundle ID of the plug-in that instantiated the object. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIOObjectPropertyName
                        A CFString that contains the human readable name of the object. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIOObjectPropertyManufacturer
                        A CFString that contains the human readable name of the manufacturer of the hardware the CMIOObject is a part of. The caller is responsible for releasing the
                        returned CFObject.
    @constant       kCMIOObjectPropertyElementName
                        A CFString that contains a human readable name for the given element in the given scope. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIOObjectPropertyElementCategoryName
                        A CFString that contains a human readable name for the category of the given element in the given scope. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIOObjectPropertyElementNumberName
                        A CFString that contains a human readable name for the number of the given element in the given scope. The caller is responsible for releasing the returned CFObject.
    @constant       kCMIOObjectPropertyOwnedObjects
                        An array of CMIOObjectIDs that represent all the CMIOObjects owned by the given object. The qualifier is an array of CMIOClassIDs. If it is non-empty, the
                        returned array of CMIOObjectIDs will only refer to objects whose class is in the qualifier array or whose is a subclass of one in the qualifier array.
    @constant       kCMIOObjectPropertyListenerAdded
                        A CMIOObjectPropertyAddress indicating the address to which a new listener was added. Note that this property is not for applications to use. Rather, this property
                        is for the DAL shell to notify CMIOObjects implemented by a CMIOPlugIn when a listener is added.
    @constant       kCMIOObjectPropertyListenerRemoved
                        A CMIOObjectPropertyAddress indicating the address to which a listener was removed. Note that this property is not for applications to use. Rather, this property
                        is for the DAL shell to notify CMIOObjects implemented by a CMIOPlugIn when a listener is removed.
*/
enum
{
    kCMIOObjectPropertyClass                = 'clas',
    kCMIOObjectPropertyOwner                = 'stdv',
    kCMIOObjectPropertyCreator              = 'oplg',
    kCMIOObjectPropertyName                 = 'lnam',
    kCMIOObjectPropertyManufacturer         = 'lmak',
    kCMIOObjectPropertyElementName          = 'lchn',
    kCMIOObjectPropertyElementCategoryName  = 'lccn',
    kCMIOObjectPropertyElementNumberName    = 'lcnn',
    kCMIOObjectPropertyOwnedObjects         = 'ownd',
    kCMIOObjectPropertyListenerAdded        = 'lisa',
    kCMIOObjectPropertyListenerRemoved      = 'lisr'
};

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma mark CMIOObject Functions

/*!
    @functiongroup  CMIOObject
*/

/*!
    @function       CMIOObjectShow
    @abstract       Prints to standard out a textural description of the CMIOObject.
    @param          objectID
                        The CMIOObject to show.
*/
extern void
CMIOObjectShow(CMIOObjectID objectID)                                                                                           AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectHasProperty
    @abstract       Queries a CMIOObject about whether or not it has the given property.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        A CMIOObjectPropertyAddress indicating which property is being queried.
    @result         A Boolean indicating whether or not the CMIOObject has the given property.
*/
extern Boolean
CMIOObjectHasProperty(  CMIOObjectID                        objectID,
                        const CMIOObjectPropertyAddress*    address)                                                            AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectIsPropertySettable
    @abstract       Queries a CMIOObject about whether or not the given property can be set using CMIOObjectSetPropertyData.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        A CMIOObjectPropertyAddress indicating which property is being queried.
    @param          isSettable
                        A Boolean indicating whether or not the property can be set.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectIsPropertySettable(   CMIOObjectID                        objectID,
                                const CMIOObjectPropertyAddress*    address,
                                Boolean*                            isSettable)                                                 AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectGetPropertyDataSize
    @abstract       Queries a CMIOObject to find the size of the data for the given property.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        A CMIOObjectPropertyAddress indicating which property is being queried.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by qualifierData. Note that not all properties require qualification, in which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property being queried. Note that not all properties require qualification, in which case this value will be
                        NULL.
    @param          dataSize
                        A UInt32 indicating how many bytes the data for the given property occupies.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectGetPropertyDataSize(  CMIOObjectID                        objectID,
                                const CMIOObjectPropertyAddress*    address,
                                UInt32                              qualifierDataSize,
                                const void*                         qualifierData,
                                UInt32*                             dataSize)                                                   AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectGetPropertyData
    @abstract       Queries a CMIOObject to get the data of the given property and places it in the provided buffer.
    @param          objectID
                        The CMIOObject to query.
    @param          address
                        A CMIOObjectPropertyAddress indicating which property is being queried.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by qualifierData. Note that not all properties require qualification, in which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property being queried. Note that not all properties require qualification, in which case this value will be
                        NULL.
    @param          dataSize
                        A UInt32 which indicates the size (in bytes) of the buffer pointed to by data.
    @param          dataUsed
                        A UInt32 which indicates how much (in bytes) of the buffer was used.
    @param          data
                        The buffer into which the CMIOObject will put the data for the given property.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectGetPropertyData(  CMIOObjectID                        objectID,
                            const CMIOObjectPropertyAddress*    address,
                            UInt32                              qualifierDataSize,
                            const void*                         qualifierData,
                            UInt32                              dataSize,
                            UInt32*                             dataUsed,
                            void*                               data)                                                           AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectSetPropertyData
    @abstract       Tells a CMIOObject to change the value of the given property using the provided data.
    @discussion     Note that the value of the property should not be considered changed until the DAL has called the listeners as many properties values are changed asynchronously.
    @param          objectID
                        The CMIOObject to change.
    @param          address
                        A CMIOObjectPropertyAddress indicating which property is being changed.
    @param          qualifierDataSize
                        A UInt32 indicating the size of the buffer pointed to by qualifierData. Note that not all properties require qualification, in which case this value will be 0.
    @param          qualifierData
                        A buffer of data to be used in determining the data of the property being queried. Note that not all properties require qualification, in which case this value will be
                        NULL.
    @param          dataSize
                        A UInt32 indicating the size of the buffer pointed to by data.
    @param          data
                        The buffer containing the data to be used to change the property's value.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectSetPropertyData(  CMIOObjectID                        objectID,
                            const CMIOObjectPropertyAddress*    address,
                            UInt32                              qualifierDataSize,
                            const void*                         qualifierData,
                            UInt32                              dataSize,
                            const void*                         data)                                                           AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectAddPropertyListener
    @abstract       Registers the given CMIOObjectPropertyListenerProc to receive notifications when the given properties change.
    @param          objectID
                        The CMIOObject to register the listener with.
    @param          address
                        The CMIOObjectPropertyAddresses indicating which property the listener should be notified about.
    @param          listener
                        The CMIOObjectPropertyListenerProc to call.
    @param          clientData
                        A pointer to client data that is passed to the listener when it is called.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectAddPropertyListener(  CMIOObjectID                        objectID,
                                const CMIOObjectPropertyAddress*    address,
                                CMIOObjectPropertyListenerProc      listener,
                                void*                               clientData)                                                 AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectRemovePropertyListener
    @abstract       Unregisters the given CMIOObjectPropertyListenerProc from receiving notifications when the given properties change.
    @param          objectID
                        The CMIOObject to unregister the listener from.
    @param          address
                        The CMIOObjectPropertyAddress indicating which property the listener should be removed from.
    @param          listener
                        The CMIOObjectPropertyListenerProc being removed.
    @param          clientData
                        A pointer to client data that is passed to the listener when it is called.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectRemovePropertyListener(   CMIOObjectID                        objectID,
                                    const CMIOObjectPropertyAddress*    address,
                                    CMIOObjectPropertyListenerProc      listener,
                                    void*                               clientData)                                             AVAILABLE_MAC_OS_X_VERSION_10_7_AND_LATER;

/*!
    @function       CMIOObjectAddPropertyListenerBlock
    @abstract       Registers the given CMIOObjectPropertyListenerBlock to receive notifications when the given properties change.
    @param          objectID
                        The CMIOObject to register the listener with.
    @param          address
                        The CMIOObjectPropertyAddresses indicating which property the listener should be notified about.
    @param          dispatchQueue
                        The dispatch queue on which the listener block will be dispatched. All listener blocks will be dispatched asynchronously save for those dispatched from the IO context
                        (of which kCMIODevicePropertyDeviceIsRunning and kCMIODeviceProcessorOverload are the only examples) which will be dispatched synchronously. Note that this dispatch
                        queue will be retained until a matching call to CMIOObjectRemovePropertyListenerBlock is made. If this value is NULL, then the block will be directly invoked.
    @param          listener
                        The CMIOObjectPropertyListenerBlock to call. Note that this block will be Block_copy'd and the reference maintained until a matching call to
                        CMIOObjectRemovePropertyListenerBlock is made.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectAddPropertyListenerBlock( CMIOObjectID                        objectID,
                                    const CMIOObjectPropertyAddress*    address,
                                    dispatch_queue_t                    dispatchQueue,
                                    CMIOObjectPropertyListenerBlock     listener)                                           AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;

/*!
    @function       CMIOObjectRemovePropertyListenerBlock
    @abstract       Unregisters the given CMIOObjectPropertyListenerBlock from receiving notifications when the given properties change.
    @param          objectID
                        The CMIOObject to unregister the listener from.
    @param          numberAddresses
                        The number of elements in the addresses array.
    @param          addresses
                        The CMIOObjectPropertyAddress indicating which property the listener should be removed from.
    @param          dispatchQueue
                        The dispatch queue on which the listener block was being dispatched to. 
    @param          listener
                        The CMIOObjectPropertyListenerBlock being removed.
    @result         An OSStatus indicating success or failure.
*/
extern OSStatus
CMIOObjectRemovePropertyListenerBlock(  CMIOObjectID                        objectID,
                                        const CMIOObjectPropertyAddress*    address,
                                        dispatch_queue_t                    dispatchQueue,
                                        CMIOObjectPropertyListenerBlock     listener)                                       AVAILABLE_MAC_OS_X_VERSION_10_8_AND_LATER;



#pragma pack(pop)
    
#if defined(__cplusplus)
}
#endif

#endif
