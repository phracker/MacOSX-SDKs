/*	NSSpellServer.h
	Copyright 1990-2002, Apple, Inc. All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSRange.h>

@class NSArray;

/*
The server just handles all the checking in and IAC and delegates the real work to its delegate.  A single server can handle more than one language.  Services is used to rendezvous applications with servers.  The format of a services descriptor for a spell-checker:

Spell Checker: NeXT
Language: French
Language: English
Executable: franglais.daemon
*/


@interface NSSpellServer : NSObject {

  /*All instance variables are private*/

  @private
    // All instance variables are private and subject to future change.  Do not access them.
    id _delegate;
    int _caseSensitive;
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
This is the protocol the object in the server that does the real work must respond to.  The first method checks spelling and the second suggests proper corrections.  The third and fourth allow the delegate to be notified when new words are learned or forgotten.  Only the first method is required.

The argument wordCount is an out parameter.  It should return the number of words found in the document from startPosition until the misspelled word was found (or the end of the stream)  If your spell server can't count words (though it is hard to imagine why that might be), return -1 in wordCount.  countOnly of Yes means forget about checking the spelling of words, just count them until you get to the end of the stream.
*/

@interface NSObject(NSSpellServerDelegate)

- (NSRange)spellServer:(NSSpellServer *)sender findMisspelledWordInString:(NSString *)stringToCheck language:(NSString *)language wordCount:(int *)wordCount countOnly:(BOOL)countOnly;

- (NSArray *)spellServer:(NSSpellServer *)sender suggestGuessesForWord:(NSString *)word inLanguage:(NSString *)language;

- (void)spellServer:(NSSpellServer *)sender didLearnWord:(NSString *)word inLanguage:(NSString *)language;

- (void)spellServer:(NSSpellServer *)sender didForgetWord:(NSString *)word inLanguage:(NSString *)language;

@end
