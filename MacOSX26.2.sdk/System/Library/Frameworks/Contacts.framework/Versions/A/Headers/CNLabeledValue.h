//
//  CNLabeledValue.h
//  Contacts
//
//  Copyright (c) 2015–2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Contacts/ContactsDefines.h>

NS_ASSUME_NONNULL_BEGIN


/*!
 * @abstract A contact property that has a value and label.
 */
NS_CLASS_AVAILABLE(10_11, 9_0)
@interface CNLabeledValue<ValueType : id <NSCopying, NSSecureCoding>> : NSObject <NSCopying, NSSecureCoding>

/*! The identifier is unique among contacts on the device. It can be saved and used for finding labeled values next application launch. */
@property (readonly, copy, NS_NONATOMIC_IOSONLY) NSString *identifier;

@property (readonly, nullable, copy, NS_NONATOMIC_IOSONLY) NSString *label;
@property (readonly, copy, NS_NONATOMIC_IOSONLY) ValueType value;

/*! Returns a new CNLabeledValue with a new identifier. */
+ (instancetype)labeledValueWithLabel:(nullable NSString *)label value:(ValueType)value;

/*! Initializes the CNLabeledValue with a new identifier. */
- (instancetype)initWithLabel:(nullable NSString *)label value:(ValueType)value;

/*! Returns a new CNLabeledValue with the existing value and identifier. */
- (instancetype)labeledValueBySettingLabel:(nullable NSString *)label;

/*! Returns a new CNLabeledValue with the existing label and identifier. */
- (instancetype)labeledValueBySettingValue:(ValueType)value;

/*! Returns a new CNLabeledValue with the existing identifier. */
- (instancetype)labeledValueBySettingLabel:(nullable NSString *)label value:(ValueType)value;

/*!
 * @abstract Get a localized label.
 *
 * @discussion Some labels are special keys representing generic labels. Use this to obtain a localized string for a label to display to a user.
 *
 * @param label to localize.
 * @return The localized string if a Contacts framework defined label, otherwise just returns the label.
 */
+ (NSString *)localizedStringForLabel:(NSString *)label;

@end


// Generic labels
CONTACTS_EXTERN NSString * const CNLabelHome                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelWork                             NS_AVAILABLE(10_11, 9_0);
CONTACTS_EXTERN NSString * const CNLabelSchool                           NS_AVAILABLE(10_15, 13_0);
CONTACTS_EXTERN NSString * const CNLabelOther                            NS_AVAILABLE(10_11, 9_0);

// Additional email labels
CONTACTS_EXTERN NSString * const CNLabelEmailiCloud                      NS_AVAILABLE(10_11, 9_0);

// URL address labels
CONTACTS_EXTERN NSString * const CNLabelURLAddressHomePage               NS_AVAILABLE(10_11, 9_0);

// Date labels
CONTACTS_EXTERN NSString * const CNLabelDateAnniversary                  NS_AVAILABLE(10_11, 9_0);

NS_ASSUME_NONNULL_END
