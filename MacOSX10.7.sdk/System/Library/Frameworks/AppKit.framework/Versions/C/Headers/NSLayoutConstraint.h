/*
	NSLayoutConstraint.h
	Application Kit
	Copyright (c) 2009-2011, Apple Inc.
	All rights reserved.
*/

#import <AppKit/NSWindow.h>
#import <AppKit/NSControl.h>
#import <AppKit/NSView.h>
#import <AppKit/NSAnimation.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSObject.h>

@class NSArray, NSDictionary;


enum {
    NSLayoutRelationLessThanOrEqual = -1,
    NSLayoutRelationEqual = 0,
    NSLayoutRelationGreaterThanOrEqual = 1,
};
typedef NSInteger NSLayoutRelation;

enum {
    NSLayoutAttributeLeft = 1,
    NSLayoutAttributeRight,
    NSLayoutAttributeTop,
    NSLayoutAttributeBottom,
    NSLayoutAttributeLeading,
    NSLayoutAttributeTrailing,
    NSLayoutAttributeWidth,
    NSLayoutAttributeHeight,
    NSLayoutAttributeCenterX,
    NSLayoutAttributeCenterY,
    NSLayoutAttributeBaseline,
    
    NSLayoutAttributeNotAnAttribute = 0
};
typedef NSInteger NSLayoutAttribute;

enum {        
    NSLayoutFormatAlignAllLeft = (1 << NSLayoutAttributeLeft),
    NSLayoutFormatAlignAllRight = (1 << NSLayoutAttributeRight),
    NSLayoutFormatAlignAllTop = (1 << NSLayoutAttributeTop),
    NSLayoutFormatAlignAllBottom = (1 << NSLayoutAttributeBottom),
    NSLayoutFormatAlignAllLeading = (1 << NSLayoutAttributeLeading),
    NSLayoutFormatAlignAllTrailing = (1 << NSLayoutAttributeTrailing),
    NSLayoutFormatAlignAllCenterX = (1 << NSLayoutAttributeCenterX),
    NSLayoutFormatAlignAllCenterY = (1 << NSLayoutAttributeCenterY),
    NSLayoutFormatAlignAllBaseline = (1 << NSLayoutAttributeBaseline),
    
    NSLayoutFormatAlignmentMask = 0xFFFF,
    
    /* choose only one of these three
     */
    NSLayoutFormatDirectionLeadingToTrailing = 0 << 16, // default
    NSLayoutFormatDirectionLeftToRight = 1 << 16,
    NSLayoutFormatDirectionRightToLeft = 2 << 16,  
    
    NSLayoutFormatDirectionMask = 0x3 << 16,  
};
typedef NSUInteger NSLayoutFormatOptions;

enum {
    NSLayoutConstraintOrientationHorizontal = 0,
    NSLayoutConstraintOrientationVertical = 1
};
typedef NSInteger NSLayoutConstraintOrientation;

typedef struct {
    CGFloat top; 
    CGFloat left; 
    CGFloat bottom;
    CGFloat right;
} NSEdgeInsets;

NS_INLINE NSEdgeInsets NSEdgeInsetsMake(CGFloat top, CGFloat left, CGFloat bottom, CGFloat right) {
    NSEdgeInsets e;
    e.top = top;
    e.left = left;
    e.bottom = bottom;
    e.right = right;
    return e;
}


/* Where AppKit's use of priority levels interacts with the user's use, we must define the priority levels involved.  Note that most of the time there is no interaction.  The use of priority levels is likely to be local to one sub-area of the window that is under the control of one author.  
 */

enum {
    NSLayoutPriorityRequired = 1000, // a required constraint.  Do not exceed this.
    NSLayoutPriorityDefaultHigh = 750, // this is the priority level with which a button resists compressing its content.  Note that it is higher than NSLayoutPriorityWindowSizeStayPut.  Thus dragging to resize a window will not make buttons clip.  Rather the window frame is constrained.
    NSLayoutPriorityDragThatCanResizeWindow = 510, // This is the appropriate priority level for a drag that may end up resizing the window.  This needn't be a drag whose explicit purpose is to resize the window. The user might be dragging around window contents, and it might be desirable that the window get bigger to accommodate.
    NSLayoutPriorityWindowSizeStayPut = 500, // This is the priority level at which the window prefers to stay the same size.  It's generally not appropriate to make a constraint at exactly this priority. You want to be higher or lower.
    NSLayoutPriorityDragThatCannotResizeWindow = 490, // This is the priority level at which a split view divider, say, is dragged.  It won't resize the window.
    NSLayoutPriorityDefaultLow = 250, // this is the priority level at which a button hugs its contents horizontally.  
    NSLayoutPriorityFittingSizeCompression = 50, // When you issue -[NSView fittingSize], the smallest size that is large enough for the view's contents is computed.  This is the priority level with which the view wants to be as small as possible in that computation.  It's quite low.  It is generally not appropriate to make a constraint at exactly this priority.  You want to be higher or lower.
};
typedef float NSLayoutPriority;

NS_CLASS_AVAILABLE(10_7, NA)
@interface NSLayoutConstraint : NSObject <NSAnimatablePropertyContainer>
{
    @private
    NSView *_container;
    id _firstItem;
    id _secondItem;
    CGFloat _constant;
    CGFloat _loweredConstant;
    id _marker;
    id _negativeError;    
    float _coefficient;
    NSLayoutPriority _priority;
    uint64_t _layoutConstraintFlags;
    id _flange;
}

/* Create an array of constraints using an ASCII art-like visual format string.
 */
+ (NSArray *)constraintsWithVisualFormat:(NSString *)format options:(NSLayoutFormatOptions)opts metrics:(NSDictionary *)metrics views:(NSDictionary *)views;

/* This macro is a helper for making view dictionaries for +constraintsWithVisualFormat:options:metrics:views:.  
 NSDictionaryOfVariableBindings(v1, v2, v3) is equivalent to [NSDictionary dictionaryWithObjectsAndKeys:v1, @"v1", v2, @"v2", v3, @"v3", nil];
 */
#define NSDictionaryOfVariableBindings(...) _NSDictionaryOfVariableBindings(@"" # __VA_ARGS__, __VA_ARGS__, nil)
APPKIT_EXTERN NSDictionary *_NSDictionaryOfVariableBindings(NSString *commaSeparatedKeysString, id firstValue, ...); // not for direct use


/* Create constraints explicitly.  Constraints are of the form "view1.attr1 = view2.attr2 * multiplier + constant" 
 If your equation does not have a second view and attribute, use nil and NSLayoutAttributeNotAnAttribute.
 */
+(id)constraintWithItem:(id)view1 attribute:(NSLayoutAttribute)attr1 relatedBy:(NSLayoutRelation)relation toItem:(id)view2 attribute:(NSLayoutAttribute)attr2 multiplier:(CGFloat)multiplier constant:(CGFloat)c;

/* If a constraint's priority level is less than NSLayoutPriorityRequired, then it is optional.  Higher priority constraints are met before lower priority constraints.
 Constraint satisfaction is not all or nothing.  If a constraint 'a == b' is optional, that means we will attempt to minimize 'abs(a-b)'.
 This property may only be modified as part of initial set up.  An exception will be thrown if it is set after a constraint has been added to a view.
 */
@property NSLayoutPriority priority;

/* When a view is archived, it archives some but not all constraints in its -constraints array.  The value of shouldBeArchived informs NSView if a particular constraint should be archived by NSView.
 If a constraint is created at runtime in response to the state of the object, it isn't appropriate to archive the constraint - rather you archive the state that gives rise to the constraint.  Since the majority of constraints that should be archived are created in Interface Builder (which is smart enough to set this prop to YES), the default value for this property is NO.
 */
@property BOOL shouldBeArchived;

/* accessors
 firstItem.firstAttribute {==,<=,>=} secondItem.secondAttribute * multiplier + constant
 */
@property (readonly, assign) id firstItem;
@property (readonly) NSLayoutAttribute firstAttribute;
@property (readonly) NSLayoutRelation relation;
@property (readonly, assign) id secondItem;
@property (readonly) NSLayoutAttribute secondAttribute;
@property (readonly) CGFloat multiplier;

/* Unlike the other properties, the constant may be modified after constraint creation.  Setting the constant on an existing constraint performs much better than removing the constraint and adding a new one that's just like the old but for having a new constant.
 */
@property CGFloat constant;

@end

#pragma mark Installing Constraints

/* A constraint is typically installed on the closest common ancestor of the views involved in the constraint. 
 It is required that a constraint be installed on _a_ common ancestor of every view involved.  The numbers in a constraint are interpreted in the coordinate system of the view it is installed on.  A view is considered to be an ancestor of itself (as with other NSView API).
 */
@interface NSView (NSConstraintBasedLayoutInstallingConstraints)

- (NSArray *)constraints NS_AVAILABLE_MAC(10_7);

- (void)addConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_MAC(10_7);
- (void)addConstraints:(NSArray *)constraints NS_AVAILABLE_MAC(10_7);
- (void)removeConstraint:(NSLayoutConstraint *)constraint NS_AVAILABLE_MAC(10_7);
- (void)removeConstraints:(NSArray *)constraints NS_AVAILABLE_MAC(10_7);

@end

#pragma mark Core Layout Methods

/* To render a window, the following passes will occur, if necessary.  
 
 update constraints
 layout
 display
 
 Please see the conceptual documentation for a discussion of these methods.
 */

@interface NSWindow (NSConstraintBasedLayoutCoreMethods)
- (void)updateConstraintsIfNeeded NS_AVAILABLE_MAC(10_7);
- (void)layoutIfNeeded NS_AVAILABLE_MAC(10_7);
@end

@interface NSView (NSConstraintBasedLayoutCoreMethods) 
- (void)updateConstraintsForSubtreeIfNeeded NS_AVAILABLE_MAC(10_7);
- (void)updateConstraints NS_AVAILABLE_MAC(10_7);
- (BOOL)needsUpdateConstraints NS_AVAILABLE_MAC(10_7);
- (void)setNeedsUpdateConstraints:(BOOL)flag NS_AVAILABLE_MAC(10_7);

- (void)layoutSubtreeIfNeeded NS_AVAILABLE_MAC(10_7);
- (void)layout NS_AVAILABLE_MAC(10_7);
- (BOOL)needsLayout NS_AVAILABLE_MAC(10_7);
- (void)setNeedsLayout:(BOOL)flag NS_AVAILABLE_MAC(10_7);
@end

#pragma mark Compatibility and Adoption

@interface NSView (NSConstraintBasedCompatibility) 

/* by default, the autoresizing mask on a view gives rise to constraints that fully determine the view's position.  To do anything interesting with constraints, you need to turn that off. IB will turn it off.
 */
- (BOOL)translatesAutoresizingMaskIntoConstraints NS_AVAILABLE_MAC(10_7);
- (void)setTranslatesAutoresizingMaskIntoConstraints:(BOOL)flag NS_AVAILABLE_MAC(10_7);

/* constraint based layout engages lazily when someone tries to use it.  If you do all of your constraint set up in -updateConstraints, you might never even receive updateConstraints if no one makes a constraint.  To fix this chicken and egg problem, override this method to return YES if your view needs the window to use constraint based layout.  
 */
+ (BOOL)requiresConstraintBasedLayout NS_AVAILABLE_MAC(10_7);

@end

#pragma mark Separation of Concerns

@interface NSView (NSConstraintBasedLayoutLayering)

/* Constraints do not actually relate the frames of the views, rather they relate the "alignment rects" of views.  This is the same as the frame unless overridden by a subclass of NSView.  Alignment rects are the same as the "layout rects" shown in Interface Builder 3.  Typically the alignment rect of a view is what the end user would think of as the bounding rect around a control, omitting ornamentation like shadows and engraving lines.  The edges of the alignment rect are what is interesting to align, not the shadows and such.  
 */

/* These two methods should be inverses of each other.  AppKit will call both as part of layout computation.
 They may be overridden to provide arbitrary transforms between frame and alignment rect, though the two methods must be inverses of each other.
 However, the default implementation uses -alignmentRectInsets, so just override that if it's applicable.  It's easier to get right. If you do override these be sure to account for the top of your frame being either minY or maxY depending on the superview's flippedness.
 A view that displayed an image with some ornament would typically override these, because the ornamental part of an image would scale up with the size of the frame.  
 Set the NSUserDefault NSViewShowAlignmentRects to YES to see alignment rects drawn.
 */
- (NSRect)alignmentRectForFrame:(NSRect)frame NS_AVAILABLE_MAC(10_7);
- (NSRect)frameForAlignmentRect:(NSRect)alignmentRect NS_AVAILABLE_MAC(10_7);

/* override this if the alignment rect is obtained from the frame by insetting each edge by a fixed amount.  This is only called by alignmentRectForFrame: and frameForAlignmentRect:.
 */
- (NSEdgeInsets)alignmentRectInsets NS_AVAILABLE_MAC(10_7);

/* override this to provide the distance between NSLayoutAttributeBottom and NSLayoutAttributeBaseline.  NSView's implementation returns zero.
 */
- (CGFloat)baselineOffsetFromBottom NS_AVAILABLE_MAC(10_7);


/* Override this method to tell the layout system that there is something it doesn't natively understand in this view, and this is how large it intrinsically is.  A typical example would be a single line text field.  The layout system does not understand text - it must just be told that there's something in the view, and that that something will take a certain amount of space if not clipped.  
 
 In response, AppKit will set up constraints that specify (1) that the opaque content should not be compressed or clipped, (2) that the view prefers to hug tightly to its content. 
 
 A user of a view may need to specify the priority of these constraints.  For example, by default, a push button 
 -strongly wants to hug its content in the vertical direction (buttons really ought to be their natural height)
 -weakly hugs its content horizontally (extra side padding between the title and the edge of the bezel is acceptable)
 -strongly resists compressing or clipping content in both directions. 
 
 However, in the case of the scope bar in Finder, the buttons only weakly resist compressing content in the horizontal direction.  You can make the window small enough that buttons start truncating their contents.  Thus, Finder wants to lower the priority with which these buttons resist compressing content.
 
 The default 'strong' and 'weak' priorities referred to above are NSLayoutPriorityDefaultHigh and NSLayoutPriorityDefaultLow.  
 
 Note that not all views have an intrinsicContentSize.  A horizontal slider has an intrinsic height, but no intrinsic width - the slider artwork has no intrinsic best width.  A horizontal NSSlider returns (NSViewNoInstrinsicMetric, <slider height>) for intrinsicContentSize.  An NSBox returns (NSViewNoInstrinsicMetric, NSViewNoInstrinsicMetric).  The _intrinsic_ content size is concerned only with data that is in the view itself, not in other views.
 */
APPKIT_EXTERN const CGFloat NSViewNoInstrinsicMetric; // -1
- (NSSize)intrinsicContentSize NS_AVAILABLE_MAC(10_7);
- (void)invalidateIntrinsicContentSize NS_AVAILABLE_MAC(10_7); // call this when something changes that affects the intrinsicContentSize.  Otherwise AppKit won't notice that it changed.  

- (NSLayoutPriority)contentHuggingPriorityForOrientation:(NSLayoutConstraintOrientation)orientation NS_AVAILABLE_MAC(10_7);
- (void)setContentHuggingPriority:(NSLayoutPriority)priority forOrientation:(NSLayoutConstraintOrientation)orientation NS_AVAILABLE_MAC(10_7);

- (NSLayoutPriority)contentCompressionResistancePriorityForOrientation:(NSLayoutConstraintOrientation)orientation NS_AVAILABLE_MAC(10_7);
- (void)setContentCompressionResistancePriority:(NSLayoutPriority)priority forOrientation:(NSLayoutConstraintOrientation)orientation NS_AVAILABLE_MAC(10_7);
@end

@interface NSControl (NSConstraintBasedLayoutLayering)
/* should be called by a cell on its -controlView
 */
- (void)invalidateIntrinsicContentSizeForCell:(NSCell *)cell NS_AVAILABLE_MAC(10_7);
@end

#pragma mark Window anchoring

@interface NSWindow (NSConstraintBasedLayoutAnchoring)
/* If changes in the interior content (and thus, constraints) of a window force the window to get smaller or larger, what part of the window stays motionless?  By default, the top left corner of the window is anchored in place.  
 */
- (NSLayoutAttribute)anchorAttributeForOrientation:(NSLayoutConstraintOrientation)orientation;
- (void)setAnchorAttribute:(NSLayoutAttribute)attr forOrientation:(NSLayoutConstraintOrientation)orientation;
@end

#pragma mark Size To Fit
@interface NSView (NSConstraintBasedLayoutFittingSize)
/* like sizeToFit, but for arbitrary views, and returns the size rather than changing the view's frame.  This considers everything in the receiver's subtree.
 */
- (NSSize)fittingSize NS_AVAILABLE_MAC(10_7);
@end

#pragma mark Debugging

/* Everything in this section should be used in debugging only, never in shipping code.  These methods may not exist in the future - no promises.  
 
 
 set default NSViewShowAlignmentRects to YES to see alignment rects drawn.  Useful in conjunction with NSShowAllViews, which shows frames.
 the existing -[NSView _subtreeDescription] is also very useful
 */
@interface NSView (NSConstraintBasedLayoutDebugging)

/* This returns a list of all the constraints that are affecting the current location of the receiver.  The constraints do not necessarily involve the receiver, they may affect the frame indirectly.
 Pass YES for the constraints affecting NSMinX([self frame]) and NSWidth([self frame]), and NO for the constraints affecting NSMinY([self frame]) and NSHeight([self frame]).
 */
- (NSArray *)constraintsAffectingLayoutForOrientation:(NSLayoutConstraintOrientation)orientation NS_AVAILABLE_MAC(10_7);

/* If there aren't enough constraints in the system to uniquely determine layout, we say the layout is ambiguous.  For example, if the only constraint in the system was x = y + 100, then there are lots of different possible values for x and y.  This situation is not automatically detected by AppKit, due to performance considerations and details of the algorithm used for layout.  
 The symptom of ambiguity is that views sometimes jump from place to place, or possibly are just in the wrong place.
 -hasAmbiguousLayout runs a check for whether there is any other frame the receiver could have that could also satisfy the constraints.
 -exerciseAmbiguousLayout does more.  It randomly changes the frames of views in your window to another of their valid possible layouts.  Making the UI jump back and forth can be helpful for figuring out where you're missing a constraint.  
 */
- (BOOL)hasAmbiguousLayout NS_AVAILABLE_MAC(10_7);
- (void)exerciseAmbiguityInLayout NS_AVAILABLE_MAC(10_7); 
@end

@interface NSWindow (NSConstraintBasedLayoutDebugging)
/* This draws a visual representation of the given constraints in the receiver window.  It's a nice way to understand exactly what a collection of constraints specifies.  
 */
- (void)visualizeConstraints:(NSArray *)constraints NS_AVAILABLE_MAC(10_7);
@end
