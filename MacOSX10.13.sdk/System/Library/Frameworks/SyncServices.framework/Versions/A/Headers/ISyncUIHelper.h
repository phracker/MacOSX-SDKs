/*
 * SyncServices -- ISyncUIHelper.h
 * Copyright (c) 2004, Apple Computer, Inc.  All rights reserved.
 */

/* Schema authors who wish to have more control over the display of their changed records (in the DCA), 
   and their conflicts (in Conflict Resolver.app), than just changing the names of attributes, etc.
   will need to implement their own custom UI code, which will be loaded into the syncuid.app (for the DCA),
   or Conflict Resolver.app (for Conflicts) at runtime and asked various questions about how to format
   records best for display.
 
   .syncschema files need to have a "UIHelperClass" key at the top level of their
   Schema.plist file specifying which class in the .syncschema bundle to load for
   information about how to display records.
 
   The class specified with the key "UIHelperClass" should implement at least part
   of the "SyncUIHelperInformalProtocol".  Since this is an informal protocol, classes
   can implement as few or as many of the methods described therin as they see fit.
 
   For each of these methods, there are three possible return values.
   An NSAttributedString with length > 0 will be displayed as is
   An NSAttributedString with length == 0 will be displayed as the localized version of <empty>
   A nil return value means that the default implementation should be used 
*/

#import <Foundation/Foundation.h>

@interface NSObject (SyncUIHelperInformalProtocol)

/* This is implemented by clients wishing to override the default display
   for various value types.  (example strings as URLs, colors, bitfields, images, etc.)
   Clients are passed in the record being displayed,
   and are expected to pass back a corresponding string for the given property name.
 
   The base case is for propertyNames to contain 1 item.  For properties that are specified 
   in a schema as dependent properties, each dependent property will be in propertyNames.
   If a ui helper returns a non-nil value when called with multiple property names,
   the returned value will be considered sufficient to represent all the dependent properties.
   Thus, only one value will be dispayed for those properties, next to the localized
   display name of the first property name.
   If a ui helper returns nil when propertyNames contains more than one property,
   the ui helper will be called again with a separate call for each dependent property.
 
   comparisonRecords is an array of records next to which the current record will be shown.
   For the Data Change Alert case, comparisonRecords will have the "new" or "old" record.
   For the Conflict Resolver case, comparisonRecords will have each record involved in the conflict

   defaultAttributes is a dictionary containing attributes that should be applied to the
   returned NSAttributedString.  The UI helper may alter these attributes as it sees fit.
   
   The suggested formatting is System Font 12pt, and the suggested color for modified values
   is (red: 47, green: 20, blue: 232)
 */

- (NSAttributedString *)attributedStringForPropertiesWithNames:(NSArray *)propertyNames inRecord:(NSDictionary *)record comparisonRecords:(NSArray *)comparisonRecords defaultAttributes:(NSDictionary *)defaultAttributes NS_DEPRECATED_MAC(10_4, 10_7);

/* This allows schemas to return a custom identity string
   including for example a picture (using NSTextAttachment) or specially colored text
   this is displayed at the top of the Record cell
 
   comparisonRecords is an array of records next to which the current record will be shown.
   For the Data Change Alert case, comparisonRecords will have the "new" or "old" record.
   For the Conflict Resolver case, comparisonRecords will have each record involved in the conflict
 
   NOTE: it is recommended that identity strings returned from this
   method be two lines long.  The first line of the returned string should contain the attributes
   in firstLineAttributes.  The second line of the returned string should contain the attributes
   in secondLineAttributes.  The UI helper may alter these attributes as it sees fit.
   
   The suggested formatting is System Font 14 pt Bold for the first line, and System Font 12pt
   for any following lines.
 */
- (NSAttributedString *)attributedStringForIdentityPropertiesWithNames:(NSArray *)propertyNames inRecord:(NSDictionary *)record comparisonRecords:(NSArray *)comparisonRecords firstLineAttributes:(NSDictionary *)firstLineAttributes secondLineAttributes:(NSDictionary *)secondLineAttributes NS_DEPRECATED_MAC(10_4, 10_7);


@end


