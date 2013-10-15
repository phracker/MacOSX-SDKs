// EOSchemaSynchronizationData.h
// Copyright (c) 1999 Apple Computer, Inc. All rights reserved.

#import <EOModeler/EOModeler.h>

EOMODELER_EXTERN NSString *EONameInObjectStoreKey;

@interface EOAttribute (EOSchemaSynchronizationData)

- (NSString *)_nameInObjectStore;
- (NSString *)_recordedNameInObjectStore;
- (void)_setNameInObjectStore:(NSString *)nameInObjectStore;

@end

@interface EOEntity (EOSchemaSynchronizationData)

- (void)_clearSchemaSynchronizationData;
- (NSString *)_nameInObjectStore;
- (NSString *)_recordedNameInObjectStore;
- (void)_setNameInObjectStore:(NSString *)nameInObjectStore;

@end

@interface EOModel (EOSchemaSynchronizationData)

- (void)_addDeletedEntityNameInObjectStore:(NSString *)nameInObjectStore;
- (void)_clearSchemaSynchronizationData;
- (NSArray *)_deletedEntityNamesInObjectStore;
- (NSDictionary *)_schemaSynchronizationOptions;
- (void)_setSchemaSynchronizationOptions:(NSDictionary *)options;
    
@end

@interface EORelationship (EOSchemaSynchronizationData)

- (NSString *)_nameInObjectStore;
- (NSString *)_recordedNameInObjectStore;
- (void)_setNameInObjectStore:(NSString *)nameInObjectStore;

@end
