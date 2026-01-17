//
//  BEAccessibility.h
//  BrowserEngineKit
//
//  Copyright © 2024 Apple Inc. All rights reserved.
//

#import <BrowserEngineKit/BEMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BEAccessibilityPressedState) {
    BEAccessibilityPressedStateUndefined = 0,
    BEAccessibilityPressedStateFalse,
    BEAccessibilityPressedStateTrue,
    BEAccessibilityPressedStateMixed,
} BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

typedef NS_OPTIONS(NSUInteger, BEAccessibilityContainerType) {
    BEAccessibilityContainerTypeNone             = 0,
    BEAccessibilityContainerTypeLandmark         = 1 << 0,
    BEAccessibilityContainerTypeTable            = 1 << 1,
    BEAccessibilityContainerTypeList             = 1 << 2,
    BEAccessibilityContainerTypeFieldset         = 1 << 3,
    BEAccessibilityContainerTypeDialog           = 1 << 4,
    BEAccessibilityContainerTypeTree             = 1 << 5,
    BEAccessibilityContainerTypeFrame            = 1 << 6,
    BEAccessibilityContainerTypeArticle          = 1 << 7,
    BEAccessibilityContainerTypeSemanticGroup    = 1 << 8,
    BEAccessibilityContainerTypeScrollArea       = 1 << 9,
    BEAccessibilityContainerTypeAlert            = 1 << 10,
    BEAccessibilityContainerTypeDescriptionList  = 1 << 11,
} BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

@interface NSObject (BEAccessibility)

/**
 * Represents the value of aria-current.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilityCurrentStatus BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-sort.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilitySortDirection BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-roledescription.
 * default: nil
 */
@property (nonatomic, strong, nullable) NSString *browserAccessibilityRoleDescription BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-required.
 * default: false
 */
@property (nonatomic, assign) BOOL browserAccessibilityIsRequired BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents the value of aria-pressed.
 * default: BEAccessibilityPressedStateUndefined
 */
@property (nonatomic, assign) BEAccessibilityPressedState browserAccessibilityPressedState BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * Represents whether the current element has native DOM focus.
 * default: false
 */
@property (nonatomic, assign) BOOL browserAccessibilityHasDOMFocus BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 * An option set of the types that contain this element. For example, an object within a table cell
 * will return the Table container type.
 * default: BEAccessibilityContainerTypeNone
 */
@property (nonatomic, assign) BEAccessibilityContainerType browserAccessibilityContainerType BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns an range representing the selected text on the page.
 default: { NSNotFound, 0 }
 */
- (NSRange)browserAccessibilitySelectedTextRange BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Set the selected text range.
 @param range The range to make selected.
 */
- (void)browserAccessibilitySetSelectedTextRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns the value of this element in the given range.
 @param range The range of this element's value to return.
 */
- (NSString *)browserAccessibilityValueInRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Returns the attributed value of this element in the given range.
 @param range The range of this element's value to return.
 */
- (NSAttributedString *)browserAccessibilityAttributedValueInRange:(NSRange)range BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Insert text at the current cursor position.
 @param text The text to insert.
 */
- (void)browserAccessibilityInsertTextAtCursor:(NSString *)text NS_SWIFT_NAME(browserAccessibilityInsertTextAtCursor(text:)) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract Delete text at the current cursor position.
 @param numberOfCharacters Number of characters to delete.
 */
- (void)browserAccessibilityDeleteTextAtCursor:(NSInteger)numberOfCharacters NS_SWIFT_NAME(browserAccessibilityDeleteTextAtCursor(numberOfCharacters:)) BROWSERENGINE_ACCESSIBILITY_AVAILABILITY;

/**
 @abstract The text cursor position of the soft line end should be returned, starting from the current selection (or beginning if no selection).
 */
- (NSInteger)accessibilityLineEndPositionFromCurrentSelection BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

/**
 @abstract The text cursor position of the soft line start should be returned, starting from the current selection (or beginning if no selection).
 */
- (NSInteger)accessibilityLineStartPositionFromCurrentSelection BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

/**
 @abstract The text cursor range of the soft line should be returned depending on the position.
 @param position A text cursor position within a line of text.
 */
- (NSRange)accessibilityLineRangeForPosition:(NSInteger)position BROWSERENGINE_ACCESSIBILITY_MARKER_AVAILABILITY;

@end

NS_ASSUME_NONNULL_END
