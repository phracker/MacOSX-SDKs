//
// PHProjectInfo.h
// PhotosUI
//
// Copyright © 2017 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PhotosUI/PhotosUITypes.h>
#import <MapKit/MapKit.h>

@class PHCloudIdentifier;
@class PHProjectSection;
@class PHProjectSectionContent;
@class PHProjectElement;

NS_ASSUME_NONNULL_BEGIN

API_UNAVAILABLE_BEGIN(ios, tvos, macCatalyst)

API_AVAILABLE_BEGIN(macos(10.13))

/**
 PHProjectCreationSource is provided as a hint to project extensions of the user context at the time of project creation.
 For example, if a user is viewing a Memory in the Photos app and from that chooses the 'Create Project' option, the
 creationSource provided in PHProjectInfo will be PHProjectCreationSourceMemory.
 */
typedef NS_ENUM(NSInteger, PHProjectCreationSource) {
    PHProjectCreationSourceUndefined = 0,
    PHProjectCreationSourceUserSelection = 1,
    PHProjectCreationSourceAlbum = 2,
    PHProjectCreationSourceMemory = 3,
    PHProjectCreationSourceMoment = 4,
    PHProjectCreationSourceProject = 20,
    PHProjectCreationSourceProjectBook = 21,
    PHProjectCreationSourceProjectCalendar = 22,
    PHProjectCreationSourceProjectCard = 23,
    PHProjectCreationSourceProjectPrintOrder = 24,
    PHProjectCreationSourceProjectSlideshow = 25,
    PHProjectCreationSourceProjectExtension = 26,
} NS_SWIFT_NAME(PHProjectInfo.CreationSource);


/**
 A PHProjectInfo object is created by Photos and passed along with a PHProjectExtensionContext any time Photos
 creates a new project. It comprises the complete content description which a Photos Project Extension can
 leverage to influence things like project layout, auto-flow, or theme selection. The properties in this class
 are inmutable and the class cannot be instatiated by an extension directly.
 */
OS_EXPORT
@interface PHProjectInfo : NSObject <NSSecureCoding>

/// Source from which the project was created.
@property (nonatomic, readonly) PHProjectCreationSource creationSource;

/**
 Selected projectType value from the extensions options as defined in -[PHProjectExtensionController supportedProjectTypes].
 See PHProjectExtensionController.h for more information on configuring the options.
 */
@property (nonatomic, readonly) PHProjectType projectType;

/// Array of project sections each containing one or more PHProjectSectionContent objects.
@property (nonatomic, readonly) NSArray<PHProjectSection *> *sections;


/**
 The following properties are only used when the user creates a new project from an existing Apple Print Product.
 */
/// YES if the source project had branding enabled.
@property (nonatomic, readonly) BOOL brandingEnabled API_AVAILABLE(macos(10.14));
/// YES if the source project had page numbers enabled.
@property (nonatomic, readonly) BOOL pageNumbersEnabled API_AVAILABLE(macos(10.14));
/// The product identifier of the originating Apple Print Product.
@property (nonatomic, readonly, nullable) NSString *productIdentifier API_AVAILABLE(macos(10.14));
/// The product theme identifier of the originating Apple Print Product.
@property (nonatomic, readonly, nullable) NSString *themeIdentifier API_AVAILABLE(macos(10.14));

// PHProjectInfo cannot be directly instantiated.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


/**
 Options for the sectionType property in PHProjectSection which provides a hint to a section's intended usage.

 - PHProjectSectionTypeUndefined: used when there is only one section and no suggested pagination or project construction
 - PHProjectSectionTypeCover: represents the cover or title section of a project
 - PHProjectSectionTypeContent: any section representing general content in a project
 - PHProjectSectionTypeAuxiliary: auxiliary content (for example, cover flap in a book)
 */
typedef NS_ENUM(NSInteger, PHProjectSectionType) {
    PHProjectSectionTypeUndefined = 0,
    
    PHProjectSectionTypeCover = 1,
    PHProjectSectionTypeContent = 2,
    PHProjectSectionTypeAuxiliary = 3,
} NS_SWIFT_NAME(PHProjectSection.SectionType);


/**
 A PHProjectSection object represents a collection of content for the project including asset elements and text elements.
 Each section contains one or more PHProjectSectionContent objects which provide suggested levels of "curation" for the
 content contained in the section. The number of sections included in PHProjectInfo will vary depending on the
 creation source at the time of the project initiation. For example:
 - if user creates a project from a Memory, there will be one cover section with a key asset element and titling, plus one section containing multiple levels of curation that mirror the "Show Summary" and "Show More" options of the Memory
 - if user creates a project from a single Album, the project info may only contain one section unless the album contains a large quantity of photos in which case, Photos may suggest section breaks based on Moments in the user's library
 - if user creates a project from an existing Apple Book, Card, or Calendar, the sections provided in the project info will exactly match the pagination in that project (e.g., one section per page in a book).
 */
OS_EXPORT
@interface PHProjectSection : NSObject <NSSecureCoding>

/**
 Array containing one or more PHProjectSectionContent objects. Ordered by number of elements from least to most.
 Projects should only present one level of content to the user at a time as assets will be reused within
 individual content objects.
 */
@property (nonatomic, readonly) NSArray<PHProjectSectionContent *> *sectionContents;

/// The intended usage of the section (e.g., cover, content, auxiliary)
@property (nonatomic, readonly) PHProjectSectionType sectionType;

/// Title for the section (e.g., a Moment name or a general geographical location), might be an empty string.
@property (nonatomic, readonly) NSString *title;

// PHProjectSection cannot be directly instantiated.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


/**
 A PHProjectSectionContent object contains all the elements and suggested layout information for a specific
 level of curation within a PHProjectSection. A section can provide multiple content objects, but
 only one is intended to be used in a project based on the amount of content detail desired.
 */
OS_EXPORT
@interface PHProjectSectionContent : NSObject <NSSecureCoding>

/// Array of asset, text, or journal entry elements contained in the content.
@property (nonatomic, readonly) NSArray<__kindof PHProjectElement *> *elements;

/**
 The suggested layout of the content is provided in resolution-independent "grid space" units
 where one grid space is the width of the defined project canvas divided by numberOfColumns.
 If a project represents a "fixed layout" (e.g., it was created from an existing Apple Book, Card, or Calendar)
 the specified numberOfColumns will always be 1.
 */
@property (nonatomic, readonly) NSInteger numberOfColumns;

/// Overall aspect ratio of the full content layout (width/height) to enable faithful replication in the project's layout.
@property (nonatomic, readonly) double aspectRatio;

/// Convenience for getting a single array of all cloud asset identifiers referenced in the content without needing to enumerate elements.
@property (nonatomic, readonly) NSArray<PHCloudIdentifier *> *cloudAssetIdentifiers;

/**
 Background color of the section content.
 This property is only used when the user creates a new project from an existing Apple Print Product
 */
@property (nonatomic, readonly, nullable) NSColor *backgroundColor API_AVAILABLE(macos(10.14));

// PHProjectSectionContent cannot be directly instantiated.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


/**
 PHProjectElement is the superclass for all element objects. It is never directly used, but defines the shared
 properties of any element in an instance of PHProjectSectionContent.
 */
OS_EXPORT
@interface PHProjectElement : NSObject <NSSecureCoding>

/**
 Relative significance of any element in the section content is defined by it's weight.
 Values range from 0.0 to 1.0 where the higher numbers represent higher overall significance.
 Projects that allow a user to reduce the number of elements in any section content can use
 this hint to determine which elements are most important to keep in order to preserve context.
 Default is 0.5.
 */
@property (nonatomic, readonly) double weight;

/**
 Placement of elements in the suggested layout is provided in grid space coordinates. For example, a rect of (0,0,3,4)
 represents a placement in the upper-left of the layout grid that is 3 grid units wide by 4 grid units high.
 For layout grids with more than one column, the values in the rect will always be integral. For fixed layouts,
 rect values will be in fractional unit values. If suggested placement could not be determined at time of project
 creation, placement will contain CGRectNull.
 */
@property (nonatomic, readonly) CGRect placement;

// PHProjectElement cannot be directly instantiated.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


typedef NSString * PHProjectRegionOfInterestIdentifier NS_SWIFT_NAME(PHProjectRegionOfInterest.Identifier) NS_EXTENSIBLE_STRING_ENUM;

/**
 In PHProjectAssetElement objects, an array of PHProjectRegionOfInterest objects may be provided.
 These regions represent specific areas in an asset that have signficant meaning. For example, faces
 that are relevant to the user (as opposed to faces in a crowd) will be highlighted in the asset
 to help with things like auto-pan, auto-zoom, or focusing on specific areas in the asset during animations or 
 transitions. Regions representing the same person or object across multiple assets are cross-referenced through
 the use of the identifier.
 */
OS_EXPORT
@interface PHProjectRegionOfInterest : NSObject <NSSecureCoding>

/*
 Rect of the regionOfInterest in unit coordinates. For example: {(0.25, 0.25), (0.5, 0.5)}
 The coordinate system is based on the dimensions of the asset's current version.
 It does not take PHProjectAssetElement.cropRect into account.
 */
@property (nonatomic, readonly) CGRect rect;

/**
 Significance of the regionOfInterest in the overall project context is provided as a weight score.
 All regions of interest with the same identifier in the project have the same weight.
 For projects doing things like animation or transition between assets, focusing on the highest weighted
 regions of interest will ensure that the presentation represents something that is most meaningful to the user.
 Value range is a double between 0.0 and 1.0.
 Default is 0.5.
 */
@property (nonatomic, readonly) double weight;

/**
 Quality of the represented region of interest in the asset.
 Different regions of interest with the same identifier may have different quality values.
 If the project wants to decide between multiple assets containing the same region of interest,
 the quality score can be used to pick the best representation of the region of interest.
 Value range is a double between 0.0 and 1.0.
 */
@property (nonatomic, readonly) double quality API_AVAILABLE(macos(10.14));

/**
 Identifier of the region of interest. Regions representing the same person or object will have
 the same identifier across multiple assets.
 */
@property (nonatomic, readonly) PHProjectRegionOfInterestIdentifier identifier;

// PHProjectRegionOfInterest cannot be directly instantiated.
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end


/**
 A PHProjectAssetElement object represents a media asset within a PHProjectSectionContent.
 The underlying PHAsset can be accessed by converting the provided cloudAssetIdentifier to a localIdentifier,
 then using the fetchAssetsWithLocalIdentifiers:options: class method defined in PHAsset.h.
 */
OS_EXPORT
@interface PHProjectAssetElement : PHProjectElement <NSSecureCoding>

/**
 Cloud identifier for the underlying PHAsset. This identifier must be converted to a localIdentifier
 before fetching, but if archiving the identifier in project data the provided PHCloudIdentifier should always be used.
 */
@property (nonatomic, readonly) PHCloudIdentifier *cloudAssetIdentifier;

/// If a user has explicitly annotated an asset (e.g., caption) that value will be provided in this property.
@property (nonatomic, readonly) NSString *annotation;

/**
 If the asset was presented to the user in a cropped manner in Photos either automatically or
 through user manipulation (pan & zoom) before the creation of the project, the visible image
 area shown to the user will be provided as a crop rect. As a fallback, Photos may suggest a general
 "safe crop" based on image content through this property. The rect is in unit coordinates with an upper left origin.
 Default value: {(0.0, 0.0), (1.0,1.0)}
 */
@property (nonatomic, readonly) CGRect cropRect;

/**
 Array of regions of interest (faces, objects, etc.) in the assets.
 Note: Photos will filter out features of an asset that it doesn't believe to be meaningful in the context
 of the user's full library. For example, random faces in a crowd.
 */
@property (nonatomic, readonly) NSArray<PHProjectRegionOfInterest *> *regionsOfInterest;

/**
 The following properties are only used when the user creates a new project from an existing Apple Print Product.
 */
/// YES if the asset was presented horizontally flipped in the originating project.
@property (nonatomic, readonly) BOOL horizontallyFlipped API_AVAILABLE(macos(10.14));
/// YES if the asset was presented vertically flipped in the originating project.
@property (nonatomic, readonly) BOOL verticallyFlipped API_AVAILABLE(macos(10.14));
@end

/// Options for PHProjectTextElementType
typedef NS_ENUM(NSInteger, PHProjectTextElementType) {
    PHProjectTextElementTypeBody = 0,
    PHProjectTextElementTypeTitle,
    PHProjectTextElementTypeSubtitle,
} NS_SWIFT_NAME(PHProjectTextElement.ElementType);

/**
 A PHProjectTextElement object represents formatted, positioned text that should be considered
 for inclusion in a project. In this case of a Memory, this will always be the Title and Subtitle show in the
 Memory header view. For projects created from Apple Book, Card, and Calendar projects, text appearing on any page. 
 */
OS_EXPORT
@interface PHProjectTextElement : PHProjectElement <NSSecureCoding>

/// Unformatted, raw string for the text element
@property (nonatomic, readonly) NSString *text;

/**
 If the text was presented to the user in a stylized manner in Photos,
 attributedText will provide access to those same attributes.
 */
@property (nonatomic, readonly, nullable) NSAttributedString *attributedText;
@property (readonly) PHProjectTextElementType textElementType;
@end

/**
 A PHProjectJournalEntryElement object represents auxilary, date specific information that may be interesting
 to include in a project. For example, callouts for specific birthdays or holidays. In general, these will only
 be included for projects created from existing Apple Calendar projects.
 */
OS_EXPORT
@interface PHProjectJournalEntryElement : PHProjectElement <NSSecureCoding>

/// Date to which the provided asset and/or text pertain
@property (nonatomic, readonly) NSDate *date;

/// Representative asset, if any, for that date.
@property (nonatomic, readonly, nullable) PHProjectAssetElement *assetElement;

/// Descriptive text (e.g., "Mom's Birthday") for that date.
@property (nonatomic, readonly, nullable) PHProjectTextElement *textElement;
@end

API_AVAILABLE_END // macos(10.13)
API_AVAILABLE_BEGIN(macos(10.14))

/**
 A PHProjectMapElement object representing a map with annotations.
 In general, these will only be included for projects created from existing Apple Print Product projects.
 */
OS_EXPORT
@interface PHProjectMapElement : PHProjectElement <NSSecureCoding>
/// The type of the map in the project.
@property (nonatomic, readonly) MKMapType mapType;

@property (nonatomic, readonly) CLLocationCoordinate2D centerCoordinate;
@property (nonatomic, readonly) CLLocationDirection heading;
@property (nonatomic, readonly) CGFloat pitch;
@property (nonatomic, readonly) CLLocationDistance altitude;

@property (nonatomic, copy, readonly) NSArray<id<MKAnnotation>> *annotations;
@end

API_AVAILABLE_END // macos(10.14)

API_UNAVAILABLE_END

NS_ASSUME_NONNULL_END
