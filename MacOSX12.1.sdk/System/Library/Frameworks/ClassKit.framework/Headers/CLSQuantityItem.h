//
//  CLSQuantityItem.h
//  ClassKit
//
//  Copyright © 2018-2020 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ClassKit/CLSActivityItem.h>

NS_ASSUME_NONNULL_BEGIN

/*!
 @abstract      CLSQuantityItem represents user generated quantity information.
 */

API_AVAILABLE(ios(11.3), macos(11.0), macCatalyst(14.0)) API_UNAVAILABLE(watchos, tvos)
@interface CLSQuantityItem : CLSActivityItem

/*!
 @abstract      Quantity awarded.
 */
@property (nonatomic, assign) double quantity;

/*!
 @abstract      Create a quantity item with an identifier and title.
 @param         identifier      An identifier that is unique within activity.
 @param         title           Title of the quantity. Ex @em Hints
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                             title:(NSString *)title NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
