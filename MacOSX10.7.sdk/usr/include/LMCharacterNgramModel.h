/*
 *  LMCharacterNgramModel.h
 *
 *  Copyright 2010 Apple Inc. All rights reserved.
 *
 */

#ifndef _LMCHARACTERNGRAMMODEL_H_
#define _LMCHARACTERNGRAMMODEL_H_

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __LMCharacterNgramModel *LMCharacterNgramModelRef;

enum {
    kNgramUNK         = 0xfffd,
    kNgramBOSSentinel = 0x2402,
    kNgramEOSSentinel = 0x2403
};

enum {
    /* Automatically insert BOS sentinel in place of punctuation and whitespace characters */
    kNgramSubstituteSentinels = 1
};

/* Returns NULL if no model file could be found for the given locale or path */    
extern
LMCharacterNgramModelRef LMCharacterNgramModelCreate(CFStringRef lm_path, CFStringRef charmap_path);

extern
LMCharacterNgramModelRef LMCharacterNgramModelCreateWithPath(CFStringRef lm_path, CFStringRef charmap_path, CFIndex options);

extern
LMCharacterNgramModelRef LMCharacterNgramModelCreateWithLocale(CFLocaleRef locale);
	
extern
CFStringRef LMCharacterNgramModelGetPath(LMCharacterNgramModelRef lm);

extern
int LMCharacterNgramModelGetOrder(LMCharacterNgramModelRef lm);

/* -log10(Pr(current|history)) */
extern
double LMCharacterNgramModelScore(LMCharacterNgramModelRef lm, UniChar current, UniChar *history, CFIndex history_length);

extern
double LMCharacterNgramModelScoreWithHistoryLengthUsed(LMCharacterNgramModelRef lm, UniChar current, UniChar *history, CFIndex history_length, CFIndex *history_used_length);

/* -log10(Pr(c|history)) for each c in characters */
extern
bool LMCharacterNgramModelScoreVector(LMCharacterNgramModelRef lm, UniChar *characters, CFIndex character_count, UniChar *history, CFIndex history_length, double *vector);

extern
bool LMCharacterNgramModelScoreVectorWithHistoryLengthUsed(LMCharacterNgramModelRef lm, UniChar *characters, CFIndex character_count, UniChar *history, CFIndex history_length, CFIndex *history_length_used, double *vector);

extern 
void LMCharacterNgramModelDecodeString(LMCharacterNgramModelRef lm, UniChar *characters);

extern
void LMCharacterNgramModelRelease(LMCharacterNgramModelRef lm);

#ifdef __cplusplus
}
#endif

#endif /* _LMCHARACTERNGRAMMMODEL_H_ */