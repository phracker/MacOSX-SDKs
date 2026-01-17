/*
 *  ABMultiValue.h
 *  AddressBook
 *
 *  Copyright (c) 2010-2015 Apple Inc. All rights reserved.
 *
 *  MultiValues are ordered, homogeneous collections of values. Each
 *  value has a unique persistent identifier which can be use to
 *  identify the value across changes to the MultiValue (ie. when
 *  the value's index may have changed). Each value may also have a
 *  non-unique string label.
 *
 */

#ifndef __ABMultiValue__
#define __ABMultiValue__

#include <CoreFoundation/CoreFoundation.h>
#include <AddressBook/AddressBookDefines.h>
#include <AddressBook/ABRecord.h>

typedef CFTypeRef ABMultiValueRef AB_DEPRECATED("use NSArray of CNLabeledValue");

typedef int32_t ABMultiValueIdentifier AB_DEPRECATED("use CNLabeledValue.identifier");
#define kABMultiValueInvalidIdentifier -1

// Type of the contained values
AB_EXTERN ABPropertyType ABMultiValueGetPropertyType(ABMultiValueRef multiValue) AB_DEPRECATED("");

AB_EXTERN CFIndex ABMultiValueGetCount(ABMultiValueRef multiValue) AB_DEPRECATED("use NSArray.count with the labeled value property");

AB_EXTERN CFTypeRef ABMultiValueCopyValueAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] value] with the labeled value property");
AB_EXTERN CFArrayRef ABMultiValueCopyArrayOfAllValues(ABMultiValueRef multiValue) AB_DEPRECATED("use [NSArray enumerateObjectsUsingBlock:] with the labeled value property and collect the values");

AB_EXTERN CFStringRef ABMultiValueCopyLabelAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] label] with the labeled value property");
    
AB_EXTERN CFIndex ABMultiValueGetIndexForIdentifier(ABMultiValueRef multiValue, ABMultiValueIdentifier identifier) AB_DEPRECATED("use [NSArray indexOfObjectPassingTest:] with the labeled value property and find the identifier");
AB_EXTERN ABMultiValueIdentifier ABMultiValueGetIdentifierAtIndex(ABMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [[NSArray objectAtIndex:] identifier] with the labeled value property");
    
AB_EXTERN CFIndex ABMultiValueGetFirstIndexOfValue(ABMultiValueRef multiValue, CFTypeRef value) AB_DEPRECATED("use [NSArray indexOfObjectPassingTest:] with the labeled value property and find the value");

// Mutable multivalues

typedef CFTypeRef ABMutableMultiValueRef AB_DEPRECATED("use NSMutableArray of CNLabeledValue");

AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutable(ABPropertyType type) AB_DEPRECATED("use [[NSMutableArray alloc] init]");
AB_EXTERN ABMutableMultiValueRef ABMultiValueCreateMutableCopy(ABMultiValueRef multiValue) AB_DEPRECATED("use [NSArray mutableCopy]");
 
AB_EXTERN bool ABMultiValueAddValueAndLabel(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, ABMultiValueIdentifier *outIdentifier) AB_DEPRECATED("use [NSMutableArray addObject:[CNLabeledValue labeledValueWithLabel:value:]]");
AB_EXTERN bool ABMultiValueInsertValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFStringRef label, CFIndex index, ABMultiValueIdentifier *outIdentifier) AB_DEPRECATED("use [NSMutableArray insertObject:[CNLabeledValue labeledValueWithLabel:value:] atIndex:]");
AB_EXTERN bool ABMultiValueRemoveValueAndLabelAtIndex(ABMutableMultiValueRef multiValue, CFIndex index) AB_DEPRECATED("use [NSMutableArray removeObjectAtIndex:]");
AB_EXTERN bool ABMultiValueReplaceValueAtIndex(ABMutableMultiValueRef multiValue, CFTypeRef value, CFIndex index) AB_DEPRECATED("use [NSMutableArray replaceObjectAtIndex: withObject:[CNLabeledValue labeledValueBySettingValue:]]");
AB_EXTERN bool ABMultiValueReplaceLabelAtIndex(ABMutableMultiValueRef multiValue, CFStringRef label, CFIndex index) AB_DEPRECATED("use [NSMutableArray replaceObjectAtIndex: withObject:[CNLabeledValue labeledValueBySettingLabel:]]");
    
#endif

