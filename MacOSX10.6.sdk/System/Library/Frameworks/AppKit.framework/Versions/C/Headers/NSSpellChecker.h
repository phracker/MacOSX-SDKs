/*
        NSSpellChecker.h
        Application Kit
        Copyright (c) 1990-2009, Apple Inc.
        All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>
#import <Foundation/NSGeometry.h>
#import <Foundation/NSTextCheckingResult.h>
#import <AppKit/AppKitDefines.h>

@class NSArray, NSDictionary, NSString, NSOrthography, NSPanel, NSView, NSViewController, NSMenu;

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
- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag wordCount:(NSInteger *)wordCount;

- (NSRange)checkSpellingOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset;

/* Just counts the words without checking spelling.  Returns -1 if counting words isn't supported by the spell server selected. */
- (NSInteger)countWordsInString:(NSString *)stringToCount language:(NSString *)language;

/* Initiates a grammar-check of a string.  Returns the range of the first flagged sentence (or similar grammatical unit), and optionally an array of dictionaries describing details within this sentence.  Keys in the details dictionaries are described in Foundation/NSSpellServer.h. */
- (NSRange)checkGrammarOfString:(NSString *)stringToCheck startingAt:(NSInteger)startingOffset language:(NSString *)language wrap:(BOOL)wrapFlag inSpellDocumentWithTag:(NSInteger)tag details:(NSArray **)details AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
/* Requests unified text checking for the given range of the given string.  The checkingTypes should be a bitmask of checking types from NSTextCheckingResult.h, describing which types of checking are desired.  The options dictionary allows clients to pass in options for certain types of checking.  The orthography and wordCount arguments will return by reference these two attributes of the range as a whole, while the return value is an array of NSTextCheckingResult objects describing particular items found during checking and their individual ranges, sorted by range origin, then range end, then result type. */  
- (NSArray *)checkString:(NSString *)stringToCheck range:(NSRange)range types:(NSTextCheckingTypes)checkingTypes options:(NSDictionary *)options inSpellDocumentWithTag:(NSInteger)tag orthography:(NSOrthography **)orthography wordCount:(NSInteger *)wordCount;

#if NS_BLOCKS_AVAILABLE
/* Requests unified text checking in the background.  The return value is a monotonically increasing sequence number that can be used to keep track of requests in flight.  The completion handler will be called (in an arbitrary context) when results are available, with the sequence number and results.  The arguments and results are otherwise the same as for the previous method. */
- (NSInteger)requestCheckingOfString:(NSString *)stringToCheck range:(NSRange)range types:(NSTextCheckingTypes)checkingTypes options:(NSDictionary *)options inSpellDocumentWithTag:(NSInteger)tag completionHandler:(void (^)(NSInteger sequenceNumber, NSArray *results, NSOrthography *orthography, NSInteger wordCount))completionHandler;
#endif /* NS_BLOCKS_AVAILABLE */

/* Provides a menu containing contextual menu items suitable for certain kinds of detected results (notably date/time/address results).  The options dictionary allows clients to pass in information associated with the document.  */
- (NSMenu *)menuForResult:(NSTextCheckingResult *)result string:(NSString *)checkedString options:(NSDictionary *)options atLocation:(NSPoint)location inView:(NSView *)view;
#endif /* MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6 */

/* Optional keys that may be used in the options dictionary with checkString:range:types:options:inSpellDocumentWithTag:orthography:wordCount:, requestCheckingOfString:range:types:options:inSpellDocumentWithTag:completionHandler:, and menuForResult:string:options:atLocation:inView:. */
APPKIT_EXTERN NSString *NSTextCheckingOrthographyKey        AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSOrthography indicating an orthography to be used as a starting point for orthography checking, or as the orthography if orthography checking is not enabled
APPKIT_EXTERN NSString *NSTextCheckingQuotesKey             AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSArray containing four strings to be used with NSTextCheckingTypeQuote (opening double quote, closing double quote, opening single quote, and closing single quote in that order); if not specified, values will be taken from user's preferences
APPKIT_EXTERN NSString *NSTextCheckingReplacementsKey       AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSDictionary containing replacements to be used with NSTextCheckingTypeReplacement; if not specified, values will be taken from user's preferences
APPKIT_EXTERN NSString *NSTextCheckingReferenceDateKey      AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSDate to be associated with the document, used as a referent for relative dates; if not specified, the current date will be used
APPKIT_EXTERN NSString *NSTextCheckingReferenceTimeZoneKey  AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSTimeZone to be associated with the document, used as a referent for dates without time zones; if not specified, the current time zone will be used
APPKIT_EXTERN NSString *NSTextCheckingDocumentURLKey        AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSURL to be associated with the document
APPKIT_EXTERN NSString *NSTextCheckingDocumentTitleKey      AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSString, a title to be associated with the document
APPKIT_EXTERN NSString *NSTextCheckingDocumentAuthorKey     AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;  // NSString, name of an author to be associated with the document

/* Methods for obtaining the default values for NSTextCheckingQuotesKey and NSTextCheckingReplacementsKey. */
- (NSArray *)userQuotesArrayForLanguage:(NSString *)language AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSDictionary *)userReplacementsDictionary AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* The checkSpellingOfString:... methods return the range of the misspelled word found.  It is up to the client to select that word in their document and to cause the spelling panel to update itself to reflect the found misspelling.  Clients should call updateSpellPanelWithMisspelledWord: to inform the spelling panel of the word to be displayed. */
- (void)updateSpellingPanelWithMisspelledWord:(NSString *)word;

/* The checkGrammarOfString:... method return the range of the sentence (or equivalent grammatical unit) with grammar issues, and an array of details describing the individual issues.  It is up to the client to select one of those details in their document and to cause the spelling panel to update itself to reflect the found issue.  Clients should call updateSpellingPanelWithGrammarString:detail: to inform the spelling panel of this.  The string should be the entire sentence, i.e., the substring corresponding to the overall range returned by checkGrammarOfString:..., and the detail should be one of the elements of the details array. */
- (void)updateSpellingPanelWithGrammarString:(NSString *)string detail:(NSDictionary *)detail AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Set and get attributes of the spelling and grammar panel. */
- (NSPanel *)spellingPanel;
- (NSView *)accessoryView;
- (void)setAccessoryView:(NSView *)aView;

/* Set and get attributes of the substitutions panel. */
- (NSPanel *)substitutionsPanel AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSViewController *)substitutionsPanelAccessoryViewController AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setSubstitutionsPanelAccessoryViewController:(NSViewController *)accessoryController AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method should be called when a client changes some relevant setting, such as what kind of spelling, grammar checking, or substitutions it uses. */
- (void)updatePanels AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* This method should be called from the client's implementation of -ignoreSpelling: */
- (void)ignoreWord:(NSString *)wordToIgnore inSpellDocumentWithTag:(NSInteger)tag;

- (NSArray *)ignoredWordsInSpellDocumentWithTag:(NSInteger)tag;
- (void)setIgnoredWords:(NSArray *)words inSpellDocumentWithTag:(NSInteger)tag;
- (NSArray *)guessesForWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language inSpellDocumentWithTag:(NSInteger)tag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;

/* Returns an array of strings, in the order in which they should be presented, representing complete words that the user might be trying to type when starting by typing the partial word at the given range in the given string. */
- (NSArray *)completionsForPartialWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language inSpellDocumentWithTag:(NSInteger)tag AVAILABLE_MAC_OS_X_VERSION_10_3_AND_LATER;

/* When a document closes, it should notify the NSSpellChecker via closeSpellDocumentWithTag: so that any associated data such as its ignored word list can be cleaned up. */
- (void)closeSpellDocumentWithTag:(NSInteger)tag;

/* Entries in the availableLanguages list are all available spellchecking languages in user preference order, as described in the spellchecker's info dictionary, usually language abbreviations such as en_US.  The userPreferredLanguages will be a subset of the availableLanguages, as selected by the user for use with spellchecking, in preference order.  If automaticallyIdentifiesLanguages is YES, then text checking will automatically use these as appropriate; otherwise, it will use the language set by setLanguage:.  The older checkSpellingOfString:... and checkGrammarOfString:... methods will use the language set by setLanguage:, if they are called with a nil language argument.  */
- (NSArray *)availableLanguages AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (NSArray *)userPreferredLanguages AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (BOOL)automaticallyIdentifiesLanguages AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (void)setAutomaticallyIdentifiesLanguages:(BOOL)flag AVAILABLE_MAC_OS_X_VERSION_10_6_AND_LATER;
- (NSString *)language;
- (BOOL)setLanguage:(NSString *)language;

/* Allows programmatic setting of the misspelled word field. */
- (void)setWordFieldStringValue:(NSString *)aString;

/* These allow clients to programmatically instruct the spellchecker to learn and unlearn words, and to determine whether a word has been learned (and hence can potentially be unlearned). */
- (void)learnWord:(NSString *)word;
- (BOOL)hasLearnedWord:(NSString *)word AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;
- (void)unlearnWord:(NSString *)word AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER;

/* Use of the following methods is discouraged; ordinarily language identification should be allowed to take place automatically, or else a specific language should be passed in to the methods that take such an argument, if the language is known in advance.  -setLanguage: allows programmatic setting of the language to spell-check in, for compatibility use if other methods are called with no language specified.  -setLanguage: accepts any of the language formats used by NSBundle, and tries to find the closest match among the available languages.  If -setLanguage: has been called, then -language will return that match; otherwise, it will return Multilingual if there is more than one element in -userPreferredLanguages, or the one element in that array if there is only one.  */

@end

@interface NSSpellChecker(NSDeprecated)

/* This is the pre-10.6 equivalent of guessesForWordRange:inString:language:inSpellDocumentWithTag:. */
- (NSArray *)guessesForWord:(NSString *)word;

/* This is the deprecated pre-10.5 equivalent of unlearnWord:. */
- (void)forgetWord:(NSString *)word DEPRECATED_IN_MAC_OS_X_VERSION_10_5_AND_LATER;

@end
