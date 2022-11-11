//
//  SLComposeViewController.h
//  Social
//
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Social/SocialDefines.h>

typedef NS_ENUM(NSInteger, SLComposeViewControllerResult) {
    SLComposeViewControllerResultCancelled,
    SLComposeViewControllerResultDone
};

typedef void (^SLComposeViewControllerCompletionHandler)(SLComposeViewControllerResult result); 

// Although you may perform requests on behalf of the user, you cannot append
// text, images, or URLs without the user's knowledge. Hence, you can set the
// initial text and other content before presenting the view to the user, but
// cannot change the content after the user views it. All of the methods used
// to set the content return a Boolean value. The methods return NO if the
// content doesn't fit or if the view was already presented to the user and the
// content can no longer be changed.

SOCIAL_CLASS_AVAILABLE(NA, 6_0)
@interface SLComposeViewController : UIViewController

+ (BOOL)isAvailableForServiceType:(NSString *)serviceType;

+ (SLComposeViewController *)composeViewControllerForServiceType:(NSString *)serviceType;

@property(nonatomic, readonly) NSString *serviceType;

// Sets the initial text to be posted. Returns NO if the sheet has already been
// presented to the user. On iOS 6.x, this returns NO if the specified text
// will not fit within the character space currently available; on iOS 7.0 and
// later, you may supply text with a length greater than the service supports,
// and the sheet will allow the user to edit it accordingly.
- (BOOL)setInitialText:(NSString *)text;

// Adds an image to the post. Returns NO if the additional image will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addImage:(UIImage *)image;

// Removes all images from the post. Returns NO and does not perform an operation
// if the sheet has already been presented to the user. 
- (BOOL)removeAllImages;


// Adds a URL to the post. Returns NO if the additional URL will not fit
// within the character space currently available, or if the sheet has already
// been presented to the user.
- (BOOL)addURL:(NSURL *)url;


// Removes all URLs from the post. Returns NO and does not perform an operation
// if the sheet has already been presented to the user.
- (BOOL)removeAllURLs;


// Specify a block to be called when the user is finished. This block is not guaranteed
// to be called on any particular thread. It is cleared after being called.
@property (nonatomic, copy) SLComposeViewControllerCompletionHandler completionHandler;
@end
