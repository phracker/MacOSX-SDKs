/*
	Copyright:	(c) 2003-2008 by Apple, Inc., all rights reserved.
*/

#import <QuartzComposer/QCComposition.h>

/* HIGH-LEVEL NOTES:
- The Quartz Composer composition repository is a system-wide centralized repository of Quartz compositions.
- The composition repository has a set of built-in compositions but also scans "/Library/Compositions" and "~/Library/Compositions" for Quartz composition files (subdirectories are ignored).
- Compositions in the repository are returned as "QCComposition" opaque objects, which can be queried for information, and also passed to other Quartz Composer APIs like QCRenderer, QCCompositionLayer or QCView.
- Compositions in the repository typically conform to one or more protocols.
- Each composition in the repository has a unique "identifier" (expressed as a NSString) which is persistent.
- The composition identifier can therefore by used to uniquely identify a composition in the repository accross application launches, systems restarts or machines.
- The composition repository posts a QCCompositionRepositoryDidUpdateNotification whenever its list of compositions has been updated.
- The QCCompositionRepository class cannot be subclassed.
*/

#if defined(MAC_OS_X_VERSION_10_5) && (MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5)

/* Notification names */
extern NSString* const QCCompositionRepositoryDidUpdateNotification;

/* Extensions to QCComposition */
@interface QCComposition (QCCompositionRepository)

/*
Returns a unique and persistent identifier for the composition if its comes from the composition repository or nil otherwise.
*/
- (NSString*) identifier;

@end

/* System-wide composition repository */
@interface QCCompositionRepository : NSObject
{
@private
    dispatch_queue_t			cq;	
}

/*
Returns the shared instance of the QCCompositionRepository.
*/
+ (QCCompositionRepository*) sharedCompositionRepository;

/*
Returns the composition corresponding to a given persistent identifier or nil if there is no composition with that identifier in the repository.
*/
- (QCComposition*) compositionWithIdentifier:(NSString*)identifier;

/*
Returns an array of QCComposition objects matching a set of criteria.
Pass one or more protocol names in "protocols" to require only compositions that conform to all these protocols, or pass nil to not do any filering on protocols.
Pass one or more attributes and their values to require only compositions that have these attributes set to those values, or pass nil to not do any filtering on attributes.
*/
- (NSArray*) compositionsWithProtocols:(NSArray*)protocols andAttributes:(NSDictionary*)attributes;

/*
Returns an array of QCComposition objects for all the compositions currently in the repository.
*/
- (NSArray*) allCompositions;

@end

#endif
