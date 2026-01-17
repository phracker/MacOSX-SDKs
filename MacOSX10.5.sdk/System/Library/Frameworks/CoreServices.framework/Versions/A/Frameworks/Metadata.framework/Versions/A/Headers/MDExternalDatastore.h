/*
 *  MDExternalDatastore.h
 *  MDDatastoreHarness
 *
 *  Created by Jonah Petri on 1/6/06.
 *  Copyright 2006 Apple. All rights reserved.
 *
 */

#include <CoreFoundation/CoreFoundation.h>

#define kMDExternalDatastoreTypeID      CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,0x49,0x68,0x94,0xB1,0x00,0x30,0x47,0xE0,0x96,0x11,0xF2,0x48,0xFB,0xE0,0xB8,0xCA)
#define kMDExternalDatastoreStoreInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,0xDA,0x62,0x12,0x99,0xED,0xBE,0x4A,0x63,0x92,0x39,0xCB,0x24,0x13,0x73,0xE2,0x07)

/* some opaque types */
typedef void * MDExternalDatastoreQueryRef;
typedef void * MDExternalDatastoreRef;
typedef void * MDResponseChannelRef;

/* an enumeration of oids, for space efficiency */
typedef void * MDOIDEnumerationRef;
uint64_t MDOIDEnumerationNextOID(MDOIDEnumerationRef oidEnum);
bool  MDOIDEnumerationHasMoreOIDs(MDOIDEnumerationRef oidEnum);

/* send an object in response to a query.  Returns true if the query should keep going, false if it has been cancelled, and should stop. */
bool MDResponseChannelSendObject(MDResponseChannelRef channel, CFTypeRef *obj);

/* send an OID in response to a URL=>OID conversion.  Use MDResponseChannelSendOID, it will return true if the store should keep processing the URLs, false otherwise  */
bool MDResponseChannelSendOID(MDResponseChannelRef channel, uint64_t oid);


#if defined(__COREFOUNDATION_CFPLUGINCOM__)
typedef struct {
    IUNKNOWN_C_GUTS;
    
    /* Initialize a store structure for a token, and return it.  In the static store case, token will be NULL.*/
    MDExternalDatastoreRef  (*MDExternalDatastoreCreate)(CFTypeRef token);
    
    /* Dealloc a given store */
    void                    (*MDExternalDatastoreDealloc)(MDExternalDatastoreRef store);
    
    /* execute the query, and send the attribute dicitonaries of each URL through the channel 
        - query will be explained more later, but will include the query tree, and maybe grouping and sorting params, maybe original text? 
        - channel expects CFDictionaries, with at a minimum a kMDItemURL set.  
        - If the store wants to talk in terms of OIDs, it should send along an OID in the dictionary too.
        */    
    bool                    (*MDExternalDatastoreExecuteQuery)(MDExternalDatastoreRef store, MDResponseChannelRef channel, MDExternalDatastoreQueryRef query);
    
    /* send the attribute dictionaries of each URL through the channel
        - urls is a CFArrayRef of CFURLRefs
        - attributes is a CFArrayRef of CFStringRefs 
        */    
    bool                    (*MDExternalDatastoreFetchAttributesForURLs)(MDExternalDatastoreRef store, MDResponseChannelRef channel, CFArrayRef attributes, CFArrayRef URLs);
    
    /* OID<=>URL converters.  If the external datastore has reasonably persistant object IDs, it should provide them as part of the query answers.  It will then be expected to implement the following functions concerning OIDs.  
        
        Implementing these functions can result in substantial gains in performance for your plugin. */
    
    /*  send an OID in response to a URL=>OID conversion.  Use MDResponseChannelSendOID, it will return true if the store should keep processing the URLs, false otherwise  */
    bool                    (*MDExternalDatastoreFetchOIDsForURLs)(MDExternalDatastoreRef store, MDResponseChannelRef channel, CFArrayRef URLs);
    
    /* send attribute dictionaries for the given OIDs.  Use MDResponseChannelSendObject on each dictionary, it will return true if the store should keep processing the OIDs, false otherwise  */
    bool                    (*MDExternalDatastoreFetchAttributesForOIDs)(MDExternalDatastoreRef store, MDResponseChannelRef channel, CFArrayRef attributes, MDOIDEnumerationRef OIDs);
    
    /* send URLs in response to OID=>URL conversions.  Use MDResponseChannelSendObject, it will return true if the store should keep processing the OIDs, false otherwise  */
    bool                    (*MDExternalDatastoreFetchURLsForOIDs)(MDExternalDatastoreRef store, MDResponseChannelRef channel, MDOIDEnumerationRef OIDs);
    
} MDExternalDatastoreStoreInterfaceStruct;
#endif