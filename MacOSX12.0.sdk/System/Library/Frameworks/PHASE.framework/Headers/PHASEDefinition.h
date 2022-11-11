//
//  PHASEDefinition.h
//  PHASE
//
//  Copyright © 2021 Apple Inc. All rights reserved.
//

#ifndef PHASEDefinition_h
#define PHASEDefinition_h

#import <PHASE/PHASETypes.h>

NS_ASSUME_NONNULL_BEGIN

/****************************************************************************************************/
/*!
    @interface PHASEDefinition
    @abstract The base class for a definition.
    @discussion
        Contains an identifer that uniquely represents this definition.
 */
OS_EXPORT API_AVAILABLE(macos(12.0), ios(15.0)) API_UNAVAILABLE(tvos) API_UNAVAILABLE(watchos)
@interface PHASEDefinition : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/*!
    @property identifier
    @abstract The identifier that uniquely represents this definition.
*/
@property(readonly, nonatomic) NSString* identifier;

@end

NS_ASSUME_NONNULL_END

#endif /* PHASEDefinition_h */
