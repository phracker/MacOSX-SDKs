/*	NSSpellServer.h
	Copyright (c) 1990-2007, Apple Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray;

/*
The server just handles all the checking in and IAC and delegates the real work to its delegate.  A single server can handle more than one language.  Services is used to rendezvous applications with servers.
*/


@interface NSSpellServer : NSObject {

  /*All instance variables are private*/

  @private
    // All instance variables are private and subject to future change.  Do not access them.
    id _delegate;
    NSInteger _caseSensitive;
    id _spellServerConnection;
    id _dictionaries;
    NSArray *_learnedDictionaries;
    
    struct __ssFlags {
        unsigned int delegateLearnsWords:1;
        unsigned int delegateForgetsWords:1;
        unsigned int busy:1;
        unsigned int _reserved:29;
    } _ssFlags;

    void *_reservedSpellServer1;
    void *_reservedSpellServer2;
}

- (void)setDelegate:(id)anObject;
- (id)delegate;

/* Used to check in */
- (BOOL)registerLanguage:(NSString *)language byVendor:(NSString *)vendor;

/* Way to query user's private dictionary(ies). */
- (BOOL)isWordInUserDictionaries:(NSString *)word caseSensitive:(BOOL)flag;

/* Waits for spell-check request to come in. */
- (void)run;

@end

/*
These are the methods the object in the server that does the real work should respond to.  Only the first method is required.  The first method checks spelling and the second suggests proper corrections.  The third and fourth allow the delegate to be notified when new words are learned or forgotten.  

The argument wordCount is an out parameter.  It should return the number of words found in the document from startPosition until the misspelled word was found (or the end of the stream)  If your spell server can't count words (though it is hard to imagine why that might be), return -1 in wordCount.  countOnly of Yes means forget about checking the spelling of words, just count them until you get to the end of the stream.

The fifth method suggests potential completions, in the order in which they should be presented to the user.  The elements of the suggested completions array should be complete words that the user might be trying to type when starting by typing the partial word at the given range in the given string.  

The sixth method permits those delegates that support it to provide grammar checking.  The return value should be the range of the next sentence or other similar grammatical unit that contains sections to be flagged for grammatical issues; the details array optionally points out subranges of that range with specific issues.  The elements of the details array should be dictionaries with some or all of the keys listed below.  

The value for the NSGrammarRange key should be an NSValue containing an NSRange, a subrange of the sentence range used as the return value, whose location should be an offset from the beginning of the sentence--so, for example, an NSGrammarRange for the first four characters of the overall sentence range should be {0, 4}.  The value for the NSGrammarUserDescription key should be an NSString containing descriptive text about that range, to be presented directly to the user; it is intended that the user description should provide enough information to allow the user to correct the problem.  A value may also be provided for the NSGrammarCorrections key, consisting of an NSArray of NSStrings representing potential substitutions to correct the problem, but it is expected that this may not be available in all cases.  It is recommended that NSGrammarUserDescription be supplied in all cases; in any event, either NSGrammarUserDescription or NSGrammarCorrections must be supplied in order for something to be presented to the user.  If NSGrammarRange is not present, it will be assumed to be equal to the overall sentence range.  Additional keys may be added in future releases.

*/

@interface NSObject(NSSpellServerDelegate)

- (NSRange)spellServer:(NSSpellServer *)sender findMisspelledWordInString:(NSString *)stringToCheck language:(NSString *)language wordCount:(NSInteger *)wordCount countOnly:(BOOL)countOnly;

- (NSArray *)spellServer:(NSSpellServer *)sender suggestGuessesForWord:(NSString *)word inLanguage:(NSString *)language;

- (void)spellServer:(NSSpellServer *)sender didLearnWord:(NSString *)word inLanguage:(NSString *)language;

- (void)spellServer:(NSSpellServer *)sender didForgetWord:(NSString *)word inLanguage:(NSString *)language;

#if MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED 
- (NSArray *)spellServer:(NSSpellServer *)sender suggestCompletionsForPartialWordRange:(NSRange)range inString:(NSString *)string language:(NSString *)language;
#endif /* MAC_OS_X_VERSION_10_3 <= MAC_OS_X_VERSION_MAX_ALLOWED */

#if MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED 
- (NSRange)spellServer:(NSSpellServer *)sender checkGrammarInString:(NSString *)stringToCheck language:(NSString *)language details:(NSArray **)details;

/* Keys for the dictionaries in the details array. */
FOUNDATION_EXPORT NSString *const NSGrammarRange;
FOUNDATION_EXPORT NSString *const NSGrammarUserDescription;
FOUNDATION_EXPORT NSString *const NSGrammarCorrections;

#endif /* MAC_OS_X_VERSION_10_5 <= MAC_OS_X_VERSION_MAX_ALLOWED */

@end
