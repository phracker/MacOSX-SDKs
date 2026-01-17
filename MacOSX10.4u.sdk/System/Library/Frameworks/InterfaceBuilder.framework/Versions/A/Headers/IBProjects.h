// ================================================================================
//	**** PUBLIC HEADER ****
//
//	InterfaceBuilder.framework - IBProjects.h
//	Copyright (c) 1996-2000 Apple Computer, Inc.
//	All rights reserved.
//
// ================================================================================

#import <InterfaceBuilder/IBSystem.h>
#import <AppKit/NSInterfaceStyle.h>
#import <Foundation/NSDictionary.h>

@protocol IBProjects <NSObject>

/* Returns the name of the project. */
- (NSString *)projectName;

/* Returns if this project has a live connection to an IDE */
- (BOOL)isLive;

/* Returns the directory for the project. */
- (NSString *)projectDirectory;

/* Returns the project immediately above this project in the project
 * hierarchy.  Returns nil if this project is the root project. */
- (id <IBProjects>)superproject;

/* Returns an array of objects conforming to the IBProjects protocol
 * of the subprojects of this project. */
- (NSArray *)subprojects;

/* Returns the project at the top of the project hierarchy for this
 * project.  Returns self if this project is the root project. */
- (id <IBProjects>)rootProject;

/* Returns YES if self is a subproject of `otherProject'. */
- (BOOL)isDescendantOfProject:(id <IBProjects>)otherProject;

/* Returns YES if self is a superproject of `otherProject'. */
- (BOOL)isAncestorOfProject:(id <IBProjects>)otherProject;

/* Returns an array of objects conforming to the IBProjectFiles protocol
 * associated with `fileType'. */
- (NSArray *)filesForFileType:(NSString *)fileType;

/* Returns YES if the project contains the file at `path'. */
- (BOOL)containsFileAtPath:(NSString *)path;

/* Returns the name of language for the file at `path', or nil if the
 * file is not localized.  The file must be a member of the project. */
- (NSString *)languageForFileAtPath:(NSString *)path;

/* Returns an object conforming to the IBProjectFiles protocol representing
 * the application's icon for the interface style `style' in the language
 * `language'.  This is typically nil unless the project is the root
 * project.  The return value can't be appropriately typed since we
 * can't forward-declare protocols. */
- (id)applicationIconForInterfaceStyle:(NSInterfaceStyle)style
			    inLanguage:(NSString *)language;

/* Returns the project's main nib file.  This is typically nil unless the
 * project is the root project. The return value can't be appropriately
 * typed since we can't forward-declare protocols. */
- (id)mainNibFileForInterfaceStyle:(NSInterfaceStyle)style
			inLanguage:(NSString *)language;

/* Returns the project manager associated with this project. */
- (id)projectManager;

- (NSString*)pathForFilename:(NSString*)name;

@end

/* File types. */
IB_EXTERN NSString * const IBProjectSourcesFileType;
IB_EXTERN NSString * const IBProjectHeadersFileType;
IB_EXTERN NSString * const IBProjectInterfacesFileType;
IB_EXTERN NSString * const IBProjectResourcesFileType;
IB_EXTERN NSString * const IBProjectSubprojectsFileType;
IB_EXTERN NSString * const IBProjectContextHelpFilesFileType;
IB_EXTERN NSString * const IBProjectDocumentationFilesFileType;
IB_EXTERN NSString * const IBProjectLibrariesFileType;
IB_EXTERN NSString * const IBProjectFrameworksFileType;
IB_EXTERN NSString * const IBProjectSupportingFilesFileType;
/* An unconnected project has reconnected with IB */
IB_EXTERN NSString * const IBProjectZombieProjectReanimated;
IB_EXTERN NSString * const IBProjectLiveProjectMadeZombie;

