#if (defined(USE_UIKIT_PUBLIC_HEADERS) && USE_UIKIT_PUBLIC_HEADERS) || !__has_include(<UIKitCore/UIPickerView.h>)
//
//  UIPickerView.h
//  UIKit
//
//  Copyright (c) 2006-2018 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIView.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol UIPickerViewDataSource, UIPickerViewDelegate;

UIKIT_EXTERN API_AVAILABLE(ios(2.0)) API_UNAVAILABLE(tvos) @interface UIPickerView : UIView <NSCoding>

@property(nullable,nonatomic,weak) id<UIPickerViewDataSource> dataSource;                // default is nil. weak reference
@property(nullable,nonatomic,weak) id<UIPickerViewDelegate>   delegate;                  // default is nil. weak reference
@property(nonatomic) BOOL showsSelectionIndicator API_DEPRECATED("This property has no effect on iOS 7 and later.", ios(2.0, 13.0));

// info that was fetched and cached from the data source and delegate
@property(nonatomic,readonly) NSInteger numberOfComponents;
- (NSInteger)numberOfRowsInComponent:(NSInteger)component;
- (CGSize)rowSizeForComponent:(NSInteger)component;

// returns the view provided by the delegate via pickerView:viewForRow:forComponent:reusingView:
// or nil if the row/component is not visible or the delegate does not implement 
// pickerView:viewForRow:forComponent:reusingView:
- (nullable UIView *)viewForRow:(NSInteger)row forComponent:(NSInteger)component;

// Reloading whole view or single component
- (void)reloadAllComponents;
- (void)reloadComponent:(NSInteger)component;

// selection. in this case, it means showing the appropriate row in the middle
- (void)selectRow:(NSInteger)row inComponent:(NSInteger)component animated:(BOOL)animated;  // scrolls the specified row to center.

- (NSInteger)selectedRowInComponent:(NSInteger)component;                                   // returns selected row. -1 if nothing selected

@end


API_UNAVAILABLE(tvos)
@protocol UIPickerViewDataSource<NSObject>
@required

// returns the number of 'columns' to display.
- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView;

// returns the # of rows in each component..
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component;
@end

API_UNAVAILABLE(tvos)
@protocol UIPickerViewDelegate<NSObject>
@optional

// returns width of column and height of row for each component. 
- (CGFloat)pickerView:(UIPickerView *)pickerView widthForComponent:(NSInteger)component API_UNAVAILABLE(tvos);
- (CGFloat)pickerView:(UIPickerView *)pickerView rowHeightForComponent:(NSInteger)component API_UNAVAILABLE(tvos);

// these methods return either a plain NSString, a NSAttributedString, or a view (e.g UILabel) to display the row for the component.
// for the view versions, we cache any hidden and thus unused views and pass them back for reuse. 
// If you return back a different object, the old one will be released. the view will be centered in the row rect  
- (nullable NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component API_UNAVAILABLE(tvos);
- (nullable NSAttributedString *)pickerView:(UIPickerView *)pickerView attributedTitleForRow:(NSInteger)row forComponent:(NSInteger)component API_AVAILABLE(ios(6.0)) API_UNAVAILABLE(tvos); // attributed title is favored if both methods are implemented
- (UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(nullable UIView *)view API_UNAVAILABLE(tvos);

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component API_UNAVAILABLE(tvos);

@end

NS_ASSUME_NONNULL_END

#else
#import <UIKitCore/UIPickerView.h>
#endif
