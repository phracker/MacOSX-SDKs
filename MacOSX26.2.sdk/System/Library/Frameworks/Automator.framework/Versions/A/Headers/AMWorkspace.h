/*	
    AMWorkspace.h
    Copyright (C) 2006 Apple Inc. All rights reserved.    
    
    Public header file.
*/

#import <Cocoa/Cocoa.h>

API_UNAVAILABLE_BEGIN(ios)

@interface AMWorkspace : NSObject
{
	@private
	id _reserved;
	id _reserved2;
	id _reserved3;
	NSError *_error;
	BOOL _didStart;
	BOOL _finishedRunning;
}

@property (class, readonly, nonatomic) AMWorkspace *sharedWorkspace;

- (id)runWorkflowAtPath:(NSString *)path withInput:(id)input error:(NSError **)error;

@end

API_UNAVAILABLE_END
