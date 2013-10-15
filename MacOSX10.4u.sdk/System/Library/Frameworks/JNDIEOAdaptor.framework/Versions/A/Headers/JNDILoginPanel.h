/*
    JNDILoginPanel.h

    Copyright (c) 1999 Apple Computer Software, Inc.
    All rights reserved.
*/

#import <EOAccess/EOAccess.h>
#import <AppKit/AppKit.h>

// The following are the standard keys in the connection dictionary.

#define UsernameKey @"username"
#define PasswordKey @"password"
#define AuthenticationMethodKey @"authenticationMethod"
#define ServerUrlKey @"serverUrl"
#define TimeoutKey @"timeout"
#define ScopeKey @"scope"
#define PlugInClassNameKey @"plugInClassName"
#define InitialContextFactoryKey @"initialContextFactory"

@interface JNDILoginPanel : EOLoginPanel {
    id panel;
    id usernameTextField;
    id passwordTextField;
    id urlTextField;
    id authenticationComboBox;
    id timeoutTextField;
    id scopePopUp;
    id pluginClassTextField;
    id initialContextFactoryTextField;
}

- (NSDictionary *)runPanelForAdaptor:(EOAdaptor *)adaptor validate:(BOOL)yn allowsCreation:(BOOL)createFlag;

- (NSDictionary *)connectionDictionary;
- (void)setConnectionDictionary:(NSDictionary *)connectionInfo;

- (void)cancel:sender;
- (void)login:sender;

@end
