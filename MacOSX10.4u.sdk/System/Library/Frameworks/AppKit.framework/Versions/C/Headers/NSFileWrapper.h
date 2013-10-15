/*
        NSFileWrapper.h
        Application Kit
        Copyright (c) 1995-2005, Apple Computer, Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>

@class NSData, NSDictionary, NSImage;

@interface NSFileWrapper : NSObject <NSCoding> {
  /*All instance variables are private*/
  @private
    id _impl;
    NSString *_fileName;
    NSString *_preferredFileName;
    NSDictionary *_fileAttributes;
    NSImage *_image;
    id _subdocuments;
}

////////////////////////////// Initialization //////////////////////////////

- (id)initDirectoryWithFileWrappers:(NSDictionary *)docs;
    // Designated initializer. Inits new directory type instances.

- (id)initRegularFileWithContents:(NSData *)data;
    // Designated initializer. Inits new regular file type instances.

- (id)initSymbolicLinkWithDestination:(NSString *)path;
    // Designated initializer. Inits new symbolic link type instances.

- (id)initWithPath:(NSString *)path;
    // Designated initializer. Inits the instance from the file, directory, or symbolic link at path.  This can end up creating a whole tree of instances with a directory type instance at the root.

- (id)initWithSerializedRepresentation:(NSData *)data;
    // Designated initializer. Inits the instance from the data which is in the standard serialization format.  This standard format is the same format as the data returned by NSText's RTFDFromRange: method.  It is also the same format used for the NSFileContentsPasteboardType.  This can end up creating a whole tree of instances with a directory type instance at the root.

////////////////////// General methods for all instance types //////////////////////

- (BOOL)writeToFile:(NSString *)path atomically:(BOOL)atomicFlag updateFilenames:(BOOL)updateFilenamesFlag;
    // Writes the instance to disk at the path specified.  For a directory type instance these methods will recursively descend child fileWrappers.  If updateFilenamesFlag is YES then the filename of the wrapper (and all sub-wrappers for directory-type instances) will be updated with the file names used to write that wrapper(s).  Usually, "Save" and "Save As" operations would pass YES for this flag, while "Save To" operations would pass NO.

- (NSData *)serializedRepresentation;
    // Returns an NSData containing a serialized representation of the instance in the standard format.  For a directory type instance these methods will recursively descend child fileWrappers.

- (void)setFilename:(NSString *)filename;
- (NSString *)filename;
    // The filename is best thought of as the last known actual file name of the wrapper.  Usually it will be the same as the preferredFilename, but may be different.  It is just a filename, not a full path.  Its extension indicates its type.  The filename is automatically set for instances initialized from the file system (via initWithPath:).  It is updated whenever updateFromPath: is sent.  It is also updated when writeToFile:atomically:updateFilenames: is called, but only if the last argument is YES. 

- (void)setPreferredFilename:(NSString *)filename;
- (NSString *)preferredFilename;
    // The preferredFilename is usually the original name.  It is just a filename, not a full path.  Its extension indicates its type.  Usually this will be the name used to save the document when it is a subdocument in some other directory type NSFileWrapper, but it might not be if there is more than one subdocument with the same preferred name.

- (void)setFileAttributes:(NSDictionary *)attributes;
- (NSDictionary *)fileAttributes;
    // The file attributes are initialized with the actual file's attributes when it is initialized from disk.  If the instance is initialized through the serialized data format the attributes are deserialized along with everything else.  When an instance is initialized from one of the designated initializers it initially has suitable default attributes for its type.  Some file attributes will be serialized as part of the serialized represenation and some will be set on the resulting file when the instance is written to the file system.  After saving to the file system, the attributes will be updated from the actual values on the disk (which might be different).  You should not attempt to change the file type through the setFileAttributes: method.

- (BOOL)isRegularFile;
- (BOOL)isDirectory;
- (BOOL)isSymbolicLink;
    // Just covers on [[self fileAttributes] fileType].

- (void)setIcon:(NSImage *)icon;
- (NSImage *)icon;
    // This is the image that should be used to represent this file to the user if an image cannot be found by better means (ie by checking for a file or file type image with NSWorkspace).

- (BOOL)needsToBeUpdatedFromPath:(NSString *)path;
- (BOOL)updateFromPath:(NSString *)path;
    // These methods provide a way to keep the instance in sync with changes that might occur in the file system behind the instance's back.  For a directory type instance these methods will recursively descend child fileWrappers.  The contents, file attributes, and image are all updated as needed.  There is a convenience method in the text system that allows an even easier way to update text attachments from disk that makes use of these methods.  The path is a full path to the file to update from.  The update "needs" to be done for regular files if the mod time or mode of the file has changed.  For symlinks it "needs" to be done only if the link destination is now different.  For directories the file attributes and icon are always updated and then the children are updated.  Deleted children and new children are noticed and the directory's child fileWrappers are updated accordingly.

///////////////////////// Directory type instance methods /////////////////////////

// The following methods work only for directory type instances.  For other types they raise.

- (NSString *)addFileWrapper:(NSFileWrapper *)doc;
    // Adds a new subdocument.  If a subdocument already exists with this document's preferredFileName then this document's preferredFileName is uniqued to determine the key assigned to this document.  The key (whether modified from the preferredFileName or not) is returned.  The key used is always based on the preferredFileName (usually it is identical to it) so after a document is made a subdocument its preferredFileName should not be changed.

- (void)removeFileWrapper:(NSFileWrapper *)doc;
    // Removes the given subdocument.

- (NSDictionary *)fileWrappers;
    // Returns a dictionary with (possibly uniqued) preferredFileNames as keys and NSFileWrapper instances as values.

- (NSString *)keyForFileWrapper:(NSFileWrapper *)doc;
    // Returns the key in the receiver's fileWrappers dictionary whose value is doc or nil if doc is not a subdocument of the receiver.

- (NSString *)addFileWithPath:(NSString *)path;
- (NSString *)addRegularFileWithContents:(NSData *)data preferredFilename:(NSString *)filename;
- (NSString *)addSymbolicLinkWithDestination:(NSString *)path preferredFilename:(NSString *)filename;
    // Convenience methods which create new instnaces and add them as child fileWrappers of the receiver.

///////////////////////// Regular file type instance methods /////////////////////////

// The following methods work only for regular file type instances.  For other types they raise.

- (NSData *)regularFileContents;
    // Returns an NSData with the contents of the file.

//////////////////////// Symbolic link type instance methods ////////////////////////

// The following methods work only for symbolic link type instances.  For other types they raise.

- (NSString *)symbolicLinkDestination;
    // Returns the path of the destination of the symbolic link.

@end
