#import <AppKit/AppKit.h>
#import <EOAccess/EOAccess.h>

@interface JDBCLoginPanel : EOLoginPanel
{
    id jdbcDriverField;
    id passwordField;
    id usernameField;
    id urlField;
    id jdbcPanel;
    id pluginField;
    NSMutableDictionary *extraInfoDictionary;
    NSMutableDictionary * loginTemplatesDict;
}

- (void) clearFields;

- (void)cancelConnection:(id)sender;
- (void)tryConnection:(id)sender;

- (NSDictionary *)runPanelForAdaptor:(EOAdaptor *)adaptor validate:(BOOL)validate allowsCreation:(BOOL)allowsCreation;
- (NSDictionary *)administrativeConnectionDictionaryForAdaptor:(EOAdaptor *)adaptor;
@end
