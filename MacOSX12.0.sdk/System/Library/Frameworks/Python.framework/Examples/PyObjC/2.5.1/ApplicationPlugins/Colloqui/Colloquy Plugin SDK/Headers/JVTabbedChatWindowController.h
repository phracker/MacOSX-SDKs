#import <JVChatWindowController.h>

@class AICustomTabsView;
@class NSTabView;
@class NSImageView;

@interface JVTabbedChatWindowController : JVChatWindowController {
	IBOutlet AICustomTabsView *customTabsView;
	IBOutlet NSTabView *tabView;
	IBOutlet NSImageView *icon;
	NSMutableArray *_tabItems;
    BOOL _supressHiding;
    BOOL _tabIsShowing;
    BOOL _autoHideTabBar;
	int _forceTabBarVisible; // -1 = Doesn't matter, 0 = NO, 1 = YES;
    float _tabHeight;
}
- (IBAction) toggleTabBarVisible:(id) sender;
- (void) updateTabBarVisibilityAndAnimate:(BOOL) animate;
@end
