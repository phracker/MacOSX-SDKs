/*
        NSSpellChecker.h
        Application Kit
        Copyright (c) 1990-2015, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSDictionary.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSTextCheckingResult.h>
#import <AppKit/AppKitDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class NSString, NSOrthography, NSPanel, NSView, NSViewController, NSMenu;

/* The NSSpellChecker object is used by a client (e.g. a document in an application) to spell-check a given NSString.  There is only one NSSpellChecker instance per application (since spell-checking is interactive and you only have one mouse and one keyboard).

The string being spell-checked need only be valid for the duration of the call to checkSpellingOfString:... or countWordsInString:.

The usual usage of this is to implement a checkSpelling: method in an object that has text to check, then, upon receiving checkSpelling:, the object calls [[NSSpellChecker sharedInstance] checkSpellingOfString:...] with an NSString object consisting of the text that should be checked.  The caller is responsible for selecting the misspelled word that is found and for updating the panel UI if desired with the updateSpellPanelWithMisspelledWord: method.
*/

@interface NSSpellChecker : NSObject  {

/*All instance variables are private*/

@private
    // All instance variables are private and subject to future change.  Do not access them.
    id _guessesBrowser;
    id _wordField;
    id _languagePopUp;
    id _reserved1;
    id _panel;
    id _reserved2;
    id _correctButton;
    id _guessButton;
    id _ignoreButton;
    id _reserved3;
    id _languagesBrowser;
    id _quotesBrowser;
    id _replacementsBrowser;
    id _defineButton;
    
    struct __scFlags {
        unsigned int autoShowGuesses:1;
        unsigned int needDelayedGuess:1;
        unsigned int unignoreInProgress:1;
        unsigned int wordFieldEdited:1;
        unsigned int inSpelling:1;
        unsigned int reconnectSpelling:1;
        unsigned int inGrammar:1;
        unsigned int reconnectGrammar:1;
        unsigned int languageIdentification:1;
        unsigned int languagesHidden:1;
        unsigned int quotesByLanguage:1;
        unsigned int _reserved:21;
    } _scFlags;
    
    id _substitutionsPanel;
    id _reserved4;
    id _learnButton;
    id _infoField;
    id _grammarControl;
}

/* Only one per application. */
+ (NSSpellChecker *)sharedSpellChecker;
+ (BOOL)sharedSpellCheckerExists;

/* Returns a guaranteed unique tag to use as the spell document tag for a document.  You should use this method to generate tags, if possible, to avoid collisions with other objects that can be spell checked. */
+ (NSInteger)uniqueSpellDocumentTag;

/* Initiates a spell-check of a string.  Returns the range of the first misspelled word (and optionally the wordCount by reference). */
- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(nullable NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag wordCount:(nullable NSInteger *)wordCount;

- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset;

/* Just counts the words without checking spelling.  Returns -1 if counting words isn't supported by the spell server selected. */
- (NSInteger)countWordsInString:(NSString *)stringToCount language:(nullable NSString *)language;

/* Initiates a grammar-check of a string.  Returns the range of the first flagged sentence (or similar grammatical unit), and optionally an array of dictionaries describing details within this sentence.  Keys in the details dictionaries are described in Foundation/NSSpellServer.h. */
- (NSRange)checkGrammarOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(nullable NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag details:(NSArray<NSDictionary<NSString *, id> *> * __nullable * __nullable)details NS_AVAILABLE_MAC(10_5);

/* Requests unified text checking for the given range of the given string.  The checkingTypes should be a bitmask of checking types from NSTextCheckingResult.h, describing which types of checking are desired.  The options dictionary allows clients to pass in options for certain types of checking.  The orthography and wordCount arguments will return by reference these two attributes of the range as a whole, while the return value is an array of NSTextCheckingResult objects describing particular items found during checking and their individual ranges, sorted by range origin, then range end, then result type. */  
- (NSArray<NSTextCheckingResult *> *)checkString:(NSString *)stringToCheck range:(NSRange)range types:(NSTextCheckingTypes)checkingTypes options:(nullable NSDictionary<NSString *, id> *)options inSpellDocumentWithTag:(NSInteger)tag orthography:(NSOrthography * __nullable * __nullable)orthography wordCount:(nullable NSInteger *)wordCount NS_AVAILABLE_MAC(10_6);

/* Requests unified text checking in the background.  The return value is a monotonically increasing sequence number that can be used to keep track of requests in flight.  The completion handler will be called (in an arbitrary context) when results are available, with the sequence number and results.  The arguments and results are otherwise the same as for the previous method. */
- (NSInteger)requestCheckingOfString:(NSString *)stringToCheck range:(NSRange)range types:(NSTextCheckingTypes)checkingTypes options:(nullable NSDictionary<NSString *, id> *)options inSpellDocumentWithTag:(NSInteger)tag completionHandler:(void (^ __nullable)(NSInteger sequenceNumber, NSArray<NSTextCheckingResult *> *results, NSOrthography *orthography, NSInteger wordCount))completionHandler NS_AVAILABLE_MAC(10_6);

/* Provides a menu containing contextual menu items suitable for certain kinds of detected results (notably date/time/address results).  The options dictionary allows clients to pass in information associated with the document.  */
- (nullable NSMenu *)menuForResult:(NSTextCheckingResult *)result string:(NSString *)checkedString options:(nullable NSDictionary<NSString *, id> *)options atLocation:(NSPoint)location inView:(NSView *)view NS_AVAILABLE_MAC(10_6);

/* Optional keys that may be used in the options dictionary with checkString:range:types:options:inSpellDocumentWithTag:orthography:wordCount:, requestCheckingOfString:range:types:options:inSpellDocumentWithTag:completionHandler:, and menuForResult:string:options:atLocation:inView:. */
APPKIT_EXTERN NSString * NSTextCheckingOrthographyKey        NS_AVAILABLE_MAC(10_6);  // NSOrthography indicating an orthography to be used as a starting point for orthography checking, or as the orthography if orthography checking is not enabled
APPKIT_EXTERN NSString * NSTextCheckingQuotesKey             NS_AVAILABLE_MAC(10_6);  // NSArray containing four strings to be used with NSTextCheckingTypeQuote (opening double quote, closing double quote, opening single quote, and closing single quote in that order); if not specified, values will be taken from user's preferences
APPKIT_EXTERN NSString * NSTextCheckingReplacementsKey       NS_AVAILABLE_MAC(10_6);  // NSDictionary containing replacements to be used with NSTextCheckingTypeReplacement; if not specified, values will be taken from user's preferences
APPKIT_EXTERN NSString * NSTextCheckingReferenceDateKey      NS_AVAILABLE_MAC(10_6);  // NSDate to be associated with the document, used as a referent for relative dates; if not specified, the current date will be used
APPKIT_EXTERN NSString * NSTextCheckingReferenceTimeZoneKey  NS_AVAILABLE_MAC(10_6);  // NSTimeZone to be associated with the document, used as a referent for dates without time zones; if not specified, the current time zone will be used
APPKIT_EXTERN NSString * NSTextCheckingDocumentURLKey        NS_AVAILABLE_MAC(10_6);  // NSURL to be associated with the document
APPKIT_EXTERN NSString * NSTextCheckingDocumentTitleKey      NS_AVAILABLE_MAC(10_6);  // NSString, a title to be associated with the document
APPKIT_EXTERN NSString * NSTextCheckingDocumentAuthorKey     NS_AVAILABLE_MAC(10_6);  // NSString, name of an author to be associated with the document
APPKIT_EXTERN NSString * NSTextCheckingRegularExpressionsKey NS_AVAILABLE_MAC(10_7);  // NSArray of NSRegularExpressions to be matched in the text of the document

/* Methods for obtaining the default values for NSTextCheckingQuotesKey and NSTextCheckingReplacementsKey. */
- (NSArray<NSString *> *)userQuotesArrayForLanguage:(NSString *)language NS_AVAILABLE_MAC(10_6);
@property (readonly, copy) NSDictionary<NSString *, NSString *> *userReplacementsDictionary NS_AVAILABLE_MAC(10_6);

/* The checkSpellingOfString:... methods return the range of the misspelled word found.  It is up to the client to select that word in their document and to cause the spelling panel to update itself to reflect the found misspelling.  Clients should call updateSpellPanelWithMisspelledWord: to inform the spelling panel of the word to be displayed. */
- (void)updateSpellingPanelWithMisspelledWord:(NSString *)word;

/* The checkGrammarOfString:... method return the range of the sentence (or equivalent grammatical unit) with grammar issues, and an array of details describing the individual issues.  It is up to the client to select one of those details in their document and to cause the spelling panel to update itself to reflect the found issue.  Clients should call updateSpellingPanelWithGrammarString:detail: to inform the spelling panel of this.  The string should be the entire sentence, i.e., the substring corresponding to the overall range returned by checkGrammarOfString:..., and the detail should be one of the elements of the details array. */
- (void)updateSpellingPanelWithGrammarString:(NSString *)string detail:(NSDictionary<NSString *, id> *)detail NS_AVAILABLE_MAC(10_5);

/* Set and get attributes of the spelling and grammar panel. */
@property (readonly, strong) NSPanel *spellingPanel;
@property (nullable, strong) NSView *accessoryView;

/* Set and get attributes of the substitutions panel. */
@property (readonly, strong) NSPanel *substitutionsPanel NS_AVAILABLE_MAC(10_6);
@property (nullable, strong) NSViewController *substitutionsPanelAccessoryViewController NS_AVAILABLE_MAC(10_6);

/* This method should be called when a client changes some relevant setting, such as what kind of spelling, grammar checking, or substitutions it uses. */
- (void)updatePanels NS_AVAILABLE_MAC(10_6);

/* This method should be called from the client's implementation of -ignoreSpelling: */
- (void)ignoreWord:(NSString *)wordToIgnore inSpellDocumentWithTag:(NSInteger)tag;

- (nullable NSArray<NSString *> *)ignoredWordsInSpellDocumentWithTag:(NSInteger)tag;
- (void)setIgnoredWords:(NSArray<NSString *> *)words inSpellDocumentWithTag:(NSInteger)tag;

/* This method returns multiple proposed alternatives for a given word, whether it is misspelled or not, in the order in which they should be presented. */
- (nullable NSArray<NSString *> *)guessesForWordRange:(NSRange)range inString:(NSString *)string language:(nullable NSString *)language inSpellDocumentWithTag:(NSInteger)tag NS_AVAILABLE_MAC(10_6);

/* If a word is misspelled, this will return a single proposed correction, if one is available.  Correction functionality is available starting in 10.6 as part of unified text checking, but for convenience this method makes it available separately starting in 10.7. */
- (nullable NSString *)correctionForWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language inSpellDocumentWithTag:(NSInteger)tag NS_AVAILABLE_MAC(10_7);

/* Returns an array of strings, in the order in which they should be presented, representing complete words that the user might be trying to type when starting by typing the partial word at the given range in the given string. */
- (nullable NSArray<NSString *> *)completionsForPartialWordRange:(NSRange)range inString:(NSString *)string language:(nullable NSString *)language inSpellDocumentWithTag:(NSInteger)tag;

/* Clients who have an NSOrthography from NSTextCheckingTypeOrthography checking and wish to determine a specific language from it for a particular word, for example to pass in to -guessesForWordRange:inString:language:inSpellDocumentWithTag:, -correctionForWordRange:inString:language:inSpellDocumentWithTag:, or -completionsForPartialWordRange:inString:language:inSpellDocumentWithTag:, should use this method to obtain it. */
- (nullable NSString *)languageForWordRange:(NSRange)range inString:(NSString *)string orthography:(nullable NSOrthography *)orthography NS_AVAILABLE_MAC(10_7);

/* When a document closes, it should notify the NSSpellChecker via closeSpellDocumentWithTag: so that any associated data such as its ignored word list can be cleaned up. */
- (void)closeSpellDocumentWithTag:(NSInteger)tag;

/* When a correction is automatically proposed, the user may respond in one of several ways.  Clients may report this to the spell checker so that it can learn from the user's response and adjust future correction behavior accordingly.  The tag, language, word, and correction should match those from the original correction result, so that the spellchecker can match them.  This implies that in order to record responses properly, clients must store the original word and original correction at least from the point at which the user accepts it until the user edits or reverts it. */
typedef NS_ENUM(NSInteger, NSCorrectionResponse) {
    NSCorrectionResponseNone,       // No response was received from the user
    NSCorrectionResponseAccepted,   // The user accepted the correction
    NSCorrectionResponseRejected,   // The user rejected the correction
    NSCorrectionResponseIgnored,    // The user continued in such a way as to ignore the correction 
    NSCorrectionResponseEdited,     // After the correction was accepted, the user edited the corrected word (to something other than its original form)
    NSCorrectionResponseReverted    // After the correction was accepted, the user reverted the correction back to the original word
};

- (void)recordResponse:(NSCorrectionResponse)response toCorrection:(NSString *)correction forWord:(NSString *)word language:(nullable NSString *)language inSpellDocumentWithTag:(NSInteger)tag NS_AVAILABLE_MAC(10_7);

/* Client views may use the NSCorrectionIndicator APIs to display a suitable user interface to indicate a correction intended to be made, and allowing the user to accept or reject it; or once a correction has been made, to indicate the original form, allowing the user to revert back to it; or to display multiple alternatives from which the user may choose one if desired.  The primaryString is the first string displayed, a correction or reversion according to the type of indicator; the alternativeStrings should be additional alternatives, if available.  Only one indicator at a time may be displayed for a given view, and the only thing a client may do with the indicator after displaying it is to dismiss it.  When an indicator is dismissed, whether by user action or by the view, the completion block will be called, with the acceptedString argument being either the replacement string accepted by the user, or nil if the user has not accepted a replacement. */
typedef NS_ENUM(NSInteger, NSCorrectionIndicatorType) {
    NSCorrectionIndicatorTypeDefault = 0,   // The default indicator shows a proposed correction
    NSCorrectionIndicatorTypeReversion,     // Used to offer to revert to the original form after a correction has been made
    NSCorrectionIndicatorTypeGuesses        // Shows multiple alternatives from which the user may choose
};

- (void)showCorrectionIndicatorOfType:(NSCorrectionIndicatorType)type primaryString:(NSString *)primaryString alternativeStrings:(NSArray<NSString *> *)alternativeStrings forStringInRect:(NSRect)rectOfTypedString view:(NSView *)view completionHandler:(void (^ __nullable)(NSString * __null_unspecified acceptedString))completionBlock NS_AVAILABLE_MAC(10_7);

- (void)dismissCorrectionIndicatorForView:(NSView *)view NS_AVAILABLE_MAC(10_7);


/* Entries in the availableLanguages list are all available spellchecking languages in user preference order, as described in the spellchecker's info dictionary, usually language abbreviations such as en_US.  The userPreferredLanguages will be a subset of the availableLanguages, as selected by the user for use with spellchecking, in preference order.  If automaticallyIdentifiesLanguages is YES, then text checking will automatically use these as appropriate; otherwise, it will use the language set by setLanguage:.  The older checkSpellingOfString:... and checkGrammarOfString:... methods will use the language set by setLanguage:, if they are called with a nil language argument.  */
@property (readonly, copy) NSArray<NSString *> *availableLanguages NS_AVAILABLE_MAC(10_5);
@property (readonly, copy) NSArray<NSString *> *userPreferredLanguages NS_AVAILABLE_MAC(10_6);
@property BOOL automaticallyIdentifiesLanguages NS_AVAILABLE_MAC(10_6);

/* Allows programmatic setting of the misspelled word field. */
- (void)setWordFieldStringValue:(NSString *)aString;

/* These allow clients to programmatically instruct the spellchecker to learn and unlearn words, and to determine whether a word has been learned (and hence can potentially be unlearned). */
- (void)learnWord:(NSString *)word;
- (BOOL)hasLearnedWord:(NSString *)word NS_AVAILABLE_MAC(10_5);
- (void)unlearnWord:(NSString *)word NS_AVAILABLE_MAC(10_5);

/* These methods allow clients to determine the global user preference settings for automatic text replacement, spelling correction, quote substitution, and dash substitution.  Text views by default will follow these automatically, but clients may override that by programmatically setting the values on the text view.  These methods will be useful for non-text view clients and others who wish to keep track of the settings.  Notifications are available (see below) when the settings change. */
+ (BOOL)isAutomaticTextReplacementEnabled NS_AVAILABLE_MAC(10_7);
+ (BOOL)isAutomaticSpellingCorrectionEnabled NS_AVAILABLE_MAC(10_7);
+ (BOOL)isAutomaticQuoteSubstitutionEnabled NS_AVAILABLE_MAC(10_9);
+ (BOOL)isAutomaticDashSubstitutionEnabled NS_AVAILABLE_MAC(10_9);

/* Use of the following methods is discouraged; ordinarily language identification should be allowed to take place automatically, or else a specific language should be passed in to the methods that take such an argument, if the language is known in advance.  -setLanguage: allows programmatic setting of the language to spell-check in, for compatibility use if other methods are called with no language specified.  -setLanguage: accepts any of the language formats used by NSBundle, and tries to find the closest match among the available languages.  If -setLanguage: has been called, then -language will return that match; otherwise, it will return Multilingual if there is more than one element in -userPreferredLanguages, or the one element in that array if there is only one.  */

- (NSString *)language;
- (BOOL)setLanguage:(NSString *)language;

@end

/* These notifications are made available via the default notification center when the global user preference settings mentioned above are changed. */
APPKIT_EXTERN NSString * const NSSpellCheckerDidChangeAutomaticSpellingCorrectionNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSSpellCheckerDidChangeAutomaticTextReplacementNotification NS_AVAILABLE_MAC(10_7);
APPKIT_EXTERN NSString * const NSSpellCheckerDidChangeAutomaticQuoteSubstitutionNotification NS_AVAILABLE_MAC(10_9);
APPKIT_EXTERN NSString * const NSSpellCheckerDidChangeAutomaticDashSubstitutionNotification NS_AVAILABLE_MAC(10_9);


@interface NSSpellChecker(NSDeprecated)

/* This is the pre-10.6 equivalent of guessesForWordRange:inString:language:inSpellDocumentWithTag:. */
- (null_unspecified NSArray *)guessesForWord:(null_unspecified NSString *)word NS_DEPRECATED_MAC(10_0, 10_6, "Use -guessesForWordRange:inString:language:inSpellDocumentWithTag instead");

/* This is the deprecated pre-10.5 equivalent of unlearnWord:. */
- (void)forgetWord:(null_unspecified NSString *)word NS_DEPRECATED_MAC(10_0, 10_5);

@end

NS_ASSUME_NONNULL_END
