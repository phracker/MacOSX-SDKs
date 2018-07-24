//
//  JavaFrameView.h
//  JavaFrameEmbedding
//
//  Copyright (c) 2006, Apple Computer, Inc.
//  All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <JavaVM/jni.h>


@interface JavaFrameView : NSView {
@private
    // The delegate is called when the Java object is instantiated. See interface below.
    IBOutlet id delegate;
    
	BOOL _startedCreation;

	// JNI reference to Java window embedded in this view.
    jobject _embeddedFrameRef;    

    // This is the name of the Java class to instantiate.
    // It must extend com.apple.awt.EmbeddedFrame.
	NSString *_customJavaClassName;
    
    id reserved[4];
}

/* Specifies any arguments to pass when creating the JavaVM. Each element in the array must be an NSString object, and should follow all conventions for creating a Java VM via JNI.
*/
+ (void)setJavaStartupOptions:(NSArray *)inStartupOptions DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Designated initializer. 
*/
- (id)initWithFrame:(NSRect)inFrameRect	javaFrameClassName:(NSString *)inClassName DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Specify the class name to use
*/
- (void)setJavaFrameClassName:(NSString *)inClassName DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)javaFrameClassName DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns a global reference to the Java window embedded in this view.
   Will return NULL if this view is not hosted in a window.
   Will also return NULL if this view is hosted in a window, but creation of the Java object hasn't completed yet.
*/
- (jobject)javaFrame DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/* See JavaFrameViewDelegate, below. Not retained by view.
*/
- (void)setDelegate:(id)anObject DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;
- (id)delegate DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

@end

// Notifications

/* This notification is posted on the main thread.
*/
extern NSString *JavaFrameViewDidCreateJavaFrame DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Delegate interface
*/
@interface NSObject(JavaFrameViewDelegate)

/* NB: this callback will never happen on the AppKit thread.  Do not cache the JNIEnv structure passed to you.
*/
- (void)javaFrameView:(JavaFrameView *)sender didCreateJavaFrame:(jobject)javaFrame withJNIEnv:(JNIEnv *)theEnv DEPRECATED_IN_MAC_OS_X_VERSION_10_6_AND_LATER;

@end
