/*
        NSFileWrapper.h
        Application Kit
        Copyright (c) 1995-2009, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary, NSError, NSImage, NSURL;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

enum {
    
    /* Whether the contents and icons are read immediately, applied recursively in the case of directory file wrappers. If reading with this option succeeds then subsequent invocations of -fileWrappers, -regularFileContents, -symbolicLinkDestinationURL:, -icon, and -serializedRepresentation sent to the receiver and all its descendant file wrappers won't fail. For performance NSFileWrapper may or may not immediately read the contents of some file packages immediately even when this option is chosen. For example, the contents of bundles (not all file packages are bundles) are immutable to the user so NSFileWrapper may read the children of such a directory lazily. You can use this option to take a reasonable snapshot of a file or folder for writing later. For example, an application like TextEdit can use this option when creating new file wrappers to represent attachments that the user creates by copying and pasting or dragging and dropping from the Finder to a TextEdit document. You wouldn't use this option when reading a document file package because that would cause unnecessarily bad perfomance. For example, an application wouldn't use this option when creating file wrappers to represent attachments as it's opening a document stored in a file package.
    */
    NSFileWrapperReadingImmediate = 1 << 0,

    /* Whether file mapping for regular file wrappers is disallowed. In Mac OS 10.6 and newer NSFileWrapper only ever memory maps files on internal drives, regardless of whether this option is used. It never memory maps files on external drives or network volumes. You can use this option to keep NSFileWrapper from memory mapping files at all, even ones on internal drives. This is useful if you want to make sure your application doesn't hold files open (mapped files are open files) and therefore prevent the user from ejecting DVDs, unmounting disk partitions, or unmounting disk images.
    */
    NSFileWrapperReadingWithoutMapping = 1 << 1

};

#endif

typedef NSUInteger NSFileWrapperReadingOptions;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6

enum {

    /* Whether writing is done atomically. You can use this option to ensure that when overwriting a file package the overwriting either completely succeeds or completely fails, with no possibility of leaving the file package in an inconsistent state. Because this option causes additional I/O you shouldn't use it unnecessarily. For example, you wouldn't use this option in an override of -[NSDocument writeToURL:ofType:error:] because NSDocument's implementation of safe saving already does atomic writing.
    */
    NSFileWrapperWritingAtomic = 1 << 0,

    /* Whether descendant file wrappers are sent -setFilename: if the writing succeeds. This is necessary when your application passes original contents URLs to -writeToURL:options:originalContentsURL:error:. Without using this and reusing child file wrappers properly subsequent invocations of -writeToURL:options:originalContentsURL:error: wouldn't be able to reliably create hard links in a new file package for performance because the record of names in the old file package would be out of date.
    */
    NSFileWrapperWritingWithNameUpdating = 1 << 1

};

#endif

typedef NSUInteger NSFileWrapperWritingOptions;

@interface NSFileWrapper : NSObject<NSCoding> {
    @private
    NSDictionary *_fileAttributes;
    NSString *_preferredFileName;
    NSString *_fileName;
    id _contents;
    NSImage *_icon;
    id _moreVars;
}

#pragma mark *** Initialization ***

/* A designated initializer for creating an instance whose kind (directory, regular file, or symbolic link) is determined based on what the URL locates. If reading is not successful return NO after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be read.
*/
- (id)initWithURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* A designated initializer for creating an instance for which -isDirectory returns YES. The passed-in dictionary must contain entries whose values are the file wrappers that are to become children and whose keys are file names. Each file wrapper that does not already have a preferred file name is sent -setPreferredFilename: with the corresponding key as the argument.
*/
- (id)initDirectoryWithFileWrappers:(NSDictionary *)childrenByPreferredName;

/* A designated initializer for creating an instance for which -isRegularFile returns YES.
*/
- (id)initRegularFileWithContents:(NSData *)contents;

/* A designated initializer for creating an instance for which -isSymbolicLink returns YES. -writeToURL:options:originalContentsURL:error: uses the result of sending -relativePath to this URL when creating a symbolic link. (An NSURL initialized by -initFileURLWithPath: returns that entire path when sent -relativePath though.)
*/
- (id)initSymbolicLinkWithDestinationURL:(NSURL *)url AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* A designated initializer. The data must be in the same format as that returned by -serializedRepresentation.
*/
- (id)initWithSerializedRepresentation:(NSData *)serializeRepresentation;

#pragma mark *** Properties Applicable to Every Kind of File Wrapper ***

/* What kind of file wrapper it is. Invocations of -readFromURL:options:error: may change what subsequent invocations of these methods return.
*/
- (BOOL)isDirectory;
- (BOOL)isRegularFile;
- (BOOL)isSymbolicLink;

/* The file name that is "preferred." When the receiver is added to a parent directory file wrapper the parent will attempt to use this name as the key into its dictionary of children. Usually the preferred file name will actually get used in this situation but it won't be if if that key is already in use. The default implementation of this method causes existing parents to remove and re-add the child to accommodate the change. Preferred file names of children are not effectively preserved when you write a file wrapper to disk and then later instantiate another file wrapper by reading. If your application needs to preserve the user-visible names of attachments it has to make its own arrangements for their storage.
*/
- (void)setPreferredFilename:(NSString *)fileName;
- (NSString *)preferredFilename;

/* The actual file name. Often it will be the same as the preferred file name but might instead be a name derived from the preferred file name. You can use this method to find out the name of a child that's just been read but you should not use it to find out the name of a child that's about to be written, because the name might be about to change. Send -keyForFileWrapper: to the parent instead.
*/
- (void)setFilename:(NSString *)fileName;
- (NSString *)filename;

/* The file attributes, in a dictionary of the same sort as those returned by -[NSFileManager attributesOfItemAtPath:error:].
*/
- (void)setFileAttributes:(NSDictionary *)fileAttributes;
- (NSDictionary *)fileAttributes;

/* The icon. -icon may return nil even if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that). The image that's returned might be shared by many NSFileWrappers so your application must not mutate it. If your application needs to mutate the returned image it should make a copy and mutate the copy instead.
*/
- (void)setIcon:(NSImage *)icon;
- (NSImage *)icon;

#pragma mark *** Reading ***

/* Whether the receiver matches the directory, regular file, or symbolic link that is located by the URL. For a directory, children are compared against the files in the directory, recursively. The contents of files are not compared; matching of regular files is based on file modification dates. Because children of directory file wrappers are not read immediately by -initWithURL:options:error: or -readFromURL:options:error: unless NSFileWrapperReadingImmediate is used, creating a file wrapper and then later sending it this message is not a reliable way to simply check whether anything in a directory has changed. You can use this method to determine whether the receiver's contents in memory are out of date relative to the file system.
*/
- (BOOL)matchesContentsOfURL:(NSURL *)url AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Recursively reread the entire contents of the receiver from the specified location, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be reread. When reading a directory children are added and removed as necessary to match the file system.
*/
- (BOOL)readFromURL:(NSURL *)url options:(NSFileWrapperReadingOptions)options error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#pragma mark *** Writing ***

/* Recursively write the entire contents of the receiver at the specified location, and return YES if successful. If not successful, return NO after setting *outError to an NSError that encapsulates the reason why the file wrapper could not be written. originalContentsURL may be nil or it may be the location of a previous revision of what is being written. If it is not nil the default implementation of this method attempts to avoid unnecessary I/O by merely writing hard links to regular files instead of actually writing out their contents. The descendant file wrappers must return accurate values when sent -filename for this to work (use NSFileWrapperWritingWithNameUpdating to increase the likelihood of that).
*/
- (BOOL)writeToURL:(NSURL *)url options:(NSFileWrapperWritingOptions)options originalContentsURL:(NSURL *)originalContentsURL error:(NSError **)outError AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

#pragma mark *** Serialization ***

/* Return an NSData suitable for passing to -initWithSerializedRepresentation:. This method may return nil if the receiver is the result of reading from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
- (NSData *)serializedRepresentation;

#pragma mark *** Directories ***

/* Each of these methods throw an exception when [receiver isDirectory]==NO. */

/* Add a file wrapper to the receiver's children and return the file name that uniquely identifies it among the receiver's children. The unique file name will be the same as the passed-in file wrapper's preferred file name unless that name is already in use as a key into the receiver's dictionary of children.
*/
- (NSString *)addFileWrapper:(NSFileWrapper *)child;

/* A convenience method. The default implementation merely allocates a new file wrapper, initializes it with -initRegularFileWithContents:, sends it -setPreferredFileName:fileName, adds it to the receiver with -addFileWrapper:, and returns what -addFileWrapper: returned.
*/
- (NSString *)addRegularFileWithContents:(NSData *)data preferredFilename:(NSString *)fileName;

/* Remove a file wrapper from the receiver's children.
*/
- (void)removeFileWrapper:(NSFileWrapper *)child;

/* Return a dictionary whose values are the receiver's children and whose keys are the unique file name that has been assigned to each one. This method may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
- (NSDictionary *)fileWrappers;

/* Return the unique file name that has been assigned to a child or nil if it is not a child of the receiver.
*/
- (NSString *)keyForFileWrapper:(NSFileWrapper *)child;

#pragma mark *** Regular Files ***

/* This method throws an exception when [receiver isRegularFile]==NO. */

/* Return the receiver's contents. This may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
- (NSData *)regularFileContents;

#pragma mark *** Symbolic Links ***

/* This method throws an exception when [receiver isSymbolicLink]==NO. */

/* Return the destination link of the receiver. This may return nil if the receiver is the result of reading a parent from the file system (use NSFileWrapperReadingImmediately if appropriate to prevent that).
*/
- (NSURL *)symbolicLinkDestinationURL AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

@interface NSFileWrapper(NSDeprecated)

#pragma mark *** Backward Compatibility ***

/* Methods that were deprecated in Mac OS 10.6. You can instead use -initWithURL:options:error: and -initSymbolicLinkWithDestinationURL:.
*/
- (id)initWithPath:(NSString *)path;
- (id)initSymbolicLinkWithDestination:(NSString *)path;

/* Methods that were deprecated in Mac OS 10.6. You can instead use -matchesContentsOfURL: and -readFromURL:options:error:.
*/
- (BOOL)needsToBeUpdatedFromPath:(NSString *)path;
- (BOOL)updateFromPath:(NSString *)path;

/* A method that was deprecated in Mac OS 10.6. You can instead use -writeToURL:options:originalContentsURL:error:.
*/
- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)atomicFlag updateFilenames:(BOOL)updateFilenamesFlag;

/* Methods that were deprecated in Mac OS 10.6. You can instead instantiate NSFileWrapper with one of the initializers, send it -setPreferredFileName: if necessary, and pass the result to -addFileWrapper:.
*/
- (NSString *)addFileWithPath:(NSString *)path;
- (NSString *)addSymbolicLinkWithDestination:(NSString *)path preferredFilename:(NSString *)filename;

/* A method that was deprecated in Mac OS 10.6. You can instead use -symbolicLinkDestinationURL.
*/
- (NSString *)symbolicLinkDestination;

@end
