//
//  Copyright (c) 2012 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ABPersonPicker;
@class ABPerson;

OBJC_GC_UNAVAILABLE
API_AVAILABLE(macos(10.9))
API_UNAVAILABLE(macCatalyst)
@protocol ABPersonPickerDelegate <NSObject>

/*!
 * @abstract Provides the ABPerson, property, and ABMultiValue identifier (if any) as chosen by the user.
 * @param picker The picker used to choose the person.
 * @param person The chosen person.
 * @param property The ABPerson property corresponding to the chosen value, e.g. kABEmailProperty.
 * @param identifier The ABMultiValue identifier. Will be nil if a non-ABMultiValue property was chosen, e.g. kABMaidenNameProperty.
 * @discussion If the person picker was used to select a person instead of a person's value, the property and identifier will be nil.
 */
- (void)personPicker:(ABPersonPicker *)picker didChoosePerson:(ABPerson *)person property:(NSString *)property identifier:(NSString *)identifier;

@optional

/*!
 * @abstract Notifies the delegate when the contact picker has closed.
 */
- (void)personPickerDidClose:(ABPersonPicker *)picker;

@end
