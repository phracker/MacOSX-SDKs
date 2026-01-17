//
//  CPNowPlayingTemplate.h
//  CarPlay
//
//  Copyright © 2019 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CarPlay/CPTemplate.h>
#import <UIKit/UIKit.h>
#import <CarPlay/CPNowPlayingButton.h>

NS_ASSUME_NONNULL_BEGIN

@class CPNowPlayingTemplate;

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol CPNowPlayingTemplateObserver <NSObject>
@optional

/**
 The user has selected the Up Next button on the now playing template. Your application
 should push a new template displaying the list of upcoming or queued content.
 */
- (void)nowPlayingTemplateUpNextButtonTapped:(CPNowPlayingTemplate *)nowPlayingTemplate;

/**
 The user has selected the album/artist button on the now playing template. Your application
 should push a new template displaying the content appearing in this container (album, playlist, or show).
 */
- (void)nowPlayingTemplateAlbumArtistButtonTapped:(CPNowPlayingTemplate *)nowPlayingTemplate;

@end

API_AVAILABLE(ios(14.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface CPNowPlayingTemplate : CPTemplate

/**
 Access the shared now playing template for your app. Instead of creating your own
 now playing template, you should configure the properties of this shared instance.
 
 You should present this shared instance when your app needs to present now playing,
 for example in response to the user selecting a playable item.
 
 When the system needs to present now playing on behalf of your app, it will present
 this shared instance.
 */
@property (nonatomic, strong, class, readonly) CPNowPlayingTemplate *sharedTemplate;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 Add an observer. Observers are notified about now playing template events.
 */
- (void)addObserver:(id <CPNowPlayingTemplateObserver>)observer;

/**
 Remove an observer.
 */
- (void)removeObserver:(id <CPNowPlayingTemplateObserver>)observer;

/**
 Playback control buttons on the Now Playing screen, like repeat, shuffle, and more.
 
 Your application may specify a maximum of 5 now playing buttons.
 
 @discussion Buttons are filled in array order, from the leading side to the trailing side of the screen.
 */
@property (nonatomic, strong, readonly) NSArray<__kindof CPNowPlayingButton *> *nowPlayingButtons;

/**
 A Boolean value indicating whether the "Up Next" button on the upper right of a Now Playing view is enabled.

 @discussion Set the value of this property to @c YES to enable the button.
 
 Defaults to NO.
 */
@property (nonatomic, assign, getter=isUpNextButtonEnabled) BOOL upNextButtonEnabled;

/**
 If your template elects to display the "Up Next" button, you may optionally specify a string
 indicating the title for the up next button. If no title is specified, a default system title
 will be used.
 
 @see -[CPNowPlayingTemplate upNextButtonEnabled].
 */
@property (nonatomic, copy) NSString *upNextTitle;

/**
 A Boolean value indicating whether the string that displays the album and artist above the playback controls should be a tappable button
 
 @discussion Set the value of this property to @c YES to enable the button.
 
 Defaults to NO.
 */
@property (nonatomic, assign, getter=isAlbumArtistButtonEnabled) BOOL albumArtistButtonEnabled;

/**
 Update the buttons displayed in this Now Playing template.
 */
- (void)updateNowPlayingButtons:(NSArray <__kindof CPNowPlayingButton *> *)nowPlayingButtons;

@end

NS_ASSUME_NONNULL_END
