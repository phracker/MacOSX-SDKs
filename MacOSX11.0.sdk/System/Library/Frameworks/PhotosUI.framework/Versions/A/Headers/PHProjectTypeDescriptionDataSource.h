//
//  PHProjectTypeDescriptionDataSource.h
//  PhotosUI
//
//  Copyright © 2018 Apple. All rights reserved.
//

#import <PhotosUI/PHProjectTypeDescription.h>

NS_ASSUME_NONNULL_BEGIN
API_AVAILABLE_BEGIN(macos(10.14))

@protocol PHProjectTypeDescriptionDataSource <NSObject>
@required
/**
 Called to get the root level project type descriptions and for any PHProjectTypeDescriptions that promised
 subtypes with canProvideSubtypes == YES
 @param projectType PHProjectTypeUndefined when fetching the root level.
                    Or the type of project types that promised to provide subtypes.
 @return An array of subtype descriptions for the projectType.
 */
- (NSArray<PHProjectTypeDescription *> *)subtypesForProjectType:(PHProjectType)projectType;

/**
 Called to fetch the updated project type description for previously invalidated project types.
 @praram projectType The previously invalidated project type.
 @return Return the current PHProjectTypeDescription for the given project type.
         The returned PHProjectTypeDescription's projectType has to be equal to the given projectType.
 */
- (nullable PHProjectTypeDescription *)typeDescriptionForProjectType:(PHProjectType)projectType;

/**
 Called to fetch the footer text for the subtypes of the given projectType
 @param projectType PHProjectTypeUndefined for root level, when showing subtypes
                    it's the parent project type of the currently visible subtype descriptions.
 @return  Return a footer text for the projectType.
 */
- (nullable NSAttributedString *)footerTextForSubtypesOfProjectType:(PHProjectType)projectType;

@optional
/**
 Called by the system when the data source is no longer needed.
 After this call the data source is no longer strongly referenced by the extension context.
 */
- (void)extensionWillDiscardDataSource;

@end


@protocol PHProjectTypeDescriptionInvalidator <NSObject>
@required

/**
 Invalidate the properties of the PHProjectTypeDescription with projectType.
 If you call this method for other project types than PHProjectTypeUndefined you have to
 implement -[PHProjectTypeDescriptionDataSource typeDescriptionForProjectType:] accordingly.
 @param projectType The project type to invalidate.
                    Use PHProjectTypeUndefined to invalidate the root level.
 */
- (void)invalidateTypeDescriptionForProjectType:(PHProjectType)projectType;
/**
 Invalidate the footer text for the subtypes of the given projectType.
 @param projectType The project type of the level to invalidate.
                    Use PHProjectTypeUndefined to invalidate the root level footer text.
 */
- (void)invalidateFooterTextForSubtypesOfProjectType:(PHProjectType)projectType;
@end

API_AVAILABLE_END
NS_ASSUME_NONNULL_END
