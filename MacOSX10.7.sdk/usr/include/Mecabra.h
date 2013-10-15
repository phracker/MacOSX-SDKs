/*
 * File: Mecabra.h
 *
 * Copyright: 2009 by Apple Inc. All rights reserved.
 *
 */

#ifndef Mecabra_h
#define Mecabra_h

#include <CoreFoundation/CoreFoundation.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
===============================================================================
    Basic Types And Constants
===============================================================================
*/
/*!
    @typedef  MecabraRef
    @abstract Opaque object that represents mecabra input engine
*/
typedef const struct __Mecabra*  MecabraRef;
    
/*! @enum     MecabraAnalysisOption
    @abstract Options for analyzing string
    @constant MecabraAnalysisDefault
              Default option
    @constant MecabraAnalysisNoPredictionMask
              Not do prediction.
    @constant MecabraAnalysisSingleWordMask
              Treat the input string as single word.
    @constant MecabraAnalysisAmbiguityMask
              Do ambiguous analysis.
    @constant MecabraAnalysisFuzzyPinyinMask
              Analyze with Fuzzy Pinyin.
*/
enum {
    MecabraAnalysisDefault              = 0,
    MecabraAnalysisNoPredictionMask     = 1 << 1,
    MecabraAnalysisSingleWordMask       = 1 << 2,
    MecabraAnalysisAmbiguityMask        = 1 << 3,
    MecabraAnalysisFuzzyPinyinMask      = 1 << 4
};
typedef CFOptionFlags MecabraAnalysisOption;

/*!
    @typedef  MecabraCandidateRef
    @abstract Opaque object that represents a mecabra candidate object
*/
typedef const void*  MecabraCandidateRef;

/*
===============================================================================
    Mecabra
===============================================================================
*/

/*! @function MecabraCreate
    @abstract Create a mecabra object.
    @param    language
              Language to be analyzed. 
              Japanese: "ja", Simplified Chinese: "zh-Hans",
              Traditional Chinese: "zh-Hant-Pinyin" or "zh-Hant-Zhuyin"
    @param    learningDictionaryDirectory
              CFURL of learning dictionary directory
    @param    specialSymbolConversion
              Specially used by Japanese Kana keyboard
    @result   Return a created MecabraRef object.
*/
extern 
MecabraRef MecabraCreate(const char* language, CFURLRef learningDictionaryDirectory, Boolean specialSymbolConversion);

/*! @function MecabraAnalyzeString
    @abstract Analyze a string.
    @param    mecabra
              Mecabra object
    @param    string
              String to be analyzed
    @param    options
              Options when analyzing
    @result   Return true if analysis is successful.
    @discussion
              If successful, use MecabraGetNextCandidate to get the candidates.
*/
extern
Boolean MecabraAnalyzeString(MecabraRef mecabra, CFStringRef string, MecabraAnalysisOption options);

/*! @function MecabraGetNextCandidate
    @abstract Enumerate to get next candidate.
    @param    mecabra
              Mecabra object
    @result   Return the next candidate being enumerated, or NULL when all
              the candidates have been enumerated.
    @discussion
              The returned candidates have been sorted by their priority.
*/
extern 
MecabraCandidateRef MecabraGetNextCandidate(MecabraRef mecabra);

/*! @function MecabraAcceptCandidate
    @abstract Accept a candidate so that mecabra can auto-learn it and also do prediction.
    @param    mecabra
              Mecabra object
    @param    candidate
              Candidate object to be accepted
    @param    isPartial
              Indicate if the candidate is partial or not.
    @result   Return true if accept is successful.
    @discussion
              MecabraGetNextCandidate can be used to get the predicted candidates.
*/
extern 
Boolean MecabraAcceptCandidate(MecabraRef mecabra, MecabraCandidateRef candidate, Boolean isPartial);

/*! @function MecabraCancelLastAcceptedCandidate
    @abstract Cancel last accepted candidate.
    @param    mecabra
              Mecabra object
    @discussion 
              Used to cancel the accepted candidate by MecabraAcceptCandidate.
*/
extern 
Boolean MecabraCancelLastAcceptedCandidate(MecabraRef mecabra);

/*! @function MecabraSetMaxPhraseNumber
    @abstract Set the maximum number of phrase candidates to be generated.
    @param    mecabra
              Mecabra object
    @param    maxNum
              Desired number of phrase candidates
*/
extern 
void MecabraSetMaxPhraseNumber(MecabraRef mecabra, CFIndex maxNum);


/*! @function MecabraCopyLearningDictionaryNames
    @abstract Copy the names(CFString) of learning dictionaries. 
    @param    language
              Language to be analyzed. 
              Japanese: "ja", Simplified Chinese: "zh-Hans",
              Traditional Chinese: "zh-Hant-Pinyin" or "zh-Hant-Zhuyin"
    @result   Return CFArray of learning dictionaries names.
    @discussion
              Each name is CFString.
*/
extern 
CFArrayRef MecabraCopyLearningDictionaryNames(const char* language);

/*! @function MecabraSaveLearningDictionaries
    @abstract Save learning dictionaries. 
    @param    mecabra
              Mecabra object
*/
extern 
void MecabraSaveLearningDictionaries(MecabraRef mecabra);

/*! @function MecabraClearLearningDictionaries
    @abstract Clear learning dictionaries in memory. 
    @param    mecabra
              Mecabra object
*/
extern 
void MecabraClearLearningDictionaries(MecabraRef mecabra);

/*! @function MecabraSetAddressBookNamePhoneticPairs
    @abstract Set name phonetic pairs of AddressBook entries.
    @param    mecabra
              Mecabra object
    @param    namePhoneticPairs
              CFArray of name phonetic pairs
*/
extern 
void MecabraSetAddressBookNamePhoneticPairs(MecabraRef mecabra, CFArrayRef namePhoneticPairs);

/*! @function MecabraSetUserWordKeyPairs
    @abstract Set word key pairs of UserWord entries.
    @param    mecabra
              Mecabra object
    @param    wordKeyPairs
              CFArray of word key pairs
*/
extern 
void MecabraSetUserWordKeyPairs(MecabraRef mecabra, CFArrayRef wordKeyPairs);
    
/*! @function MecabraBuildLearningDictionary
    @abstract Build learning dictionary
    @param    mecabra
              Mecabra object
    @param    readings
              CFArray of reading
    @param    surfaces
              CFArray of surfaces
*/ 
extern 
Boolean MecabraBuildLearningDictionary(MecabraRef mecabra, CFArrayRef readings, CFArrayRef surfaces);
    
/*! @function MecabraRelease
    @abstract Release mecabra object. 
    @param    mecabra
              Mecabra object
*/ 
extern 
void MecabraRelease(MecabraRef mecabra);

/*
===============================================================================
Mecabra Word Completion
===============================================================================
*/

/*!
    @typedef MecabraWordCompletionRef
    @abstract Opaque object that represents mecabra word completion engine
 */
typedef const struct __MecabraWordCompletion* MecabraWordCompletionRef;

/*! @enum     MecabraWordCompletionOption
    @abstract Options for word completion
    @constant MecabraWordCompletionDefault
              Default option (words are sorted by length, then by score, in desending order)
    @constant MecabraWordCompletionSearchForSubstringsMask
              Consider both the string and its all substrings for potential completion.
    @constant MecabraWordCompletionSortByScoreOnlyMask
              Rank candidates purely based on their score, not by length
    @constant MecabraWordCompletionRescoreWithLanguageModelMask
              Rescore completion candidates using system language model.
 */
enum {
    MecabraWordCompletionDefault                            = 0,
    MecabraWordCompletionSearchForSubstringsMask            = 1 << 1,
    MecabraWordCompletionSortByScoreOnlyMask                = 1 << 2,
    MecabraWordCompletionRescoreWithLanguageModelMask       = 1 << 3,
};
typedef CFOptionFlags MecabraWordCompletionOption;

/*! @function MecabraWordCompletionCreate
    @abstract Create a mecabra word completion object.
    @param    language
              Language to be analyzed.
              Simplified Chinese: "zh-Hans",
              Traditional Chinese: "zh-Hant"
    @result   Return a created MecabraWordCompletionRef object.
*/
extern
MecabraWordCompletionRef MecabraWordCompletionCreate(const char* language);


/*! @function MecabraWordCompletionAnalyzeString
    @abstract Analyze a character string to find word completion candidates.
    @param    mecabraWordCompletion
              MecabraWordCompletion object
    @param    prefix
              String to be analyzed
    @param    maxNumberOfCandidates
              Maximum number of completion candidats to be returned. If it's 0, all available candidates are returned.
    @param    options
              Options for word completion.
    @result   Return true if the specified mecabra object supports word completion and the analysis is successful.
    @discussion
              If successful, use MecabraWordCompletionGetNextCandidate to get the candidates.
 */
extern
Boolean MecabraWordCompletionAnalyzeString(MecabraWordCompletionRef mecabraWordCompletion, CFStringRef prefix, CFIndex maxNumberOfCandidates, MecabraWordCompletionOption option);

/*! @function MecabraWordCompletionGetNextCandidate
    @abstract Enumerate to get next candidate.
    @param    mecabraWordCompletion
              MecabraWordCompletion object
    @result   Return the next candidate being enumerated, or NULL when all
              the candidates have been enumerated.
    @discussion
              The returned candidates have been sorted by their priority.
*/
extern
MecabraCandidateRef MecabraWordCompletionGetNextCandidate(MecabraWordCompletionRef mecabraWordCompletion);

/*! @function MecabraWordCompletionRelease
    @abstract Release mecabra word completion object.
    @param    mecabraWordCompletion
              MecabraWordCompletion object
 */
extern
void MecabraWordCompletionRelease(MecabraWordCompletionRef mecabraWordCompletion);

/*
===============================================================================
    Mecabra Candidate
===============================================================================
*/

/*! @enum     MecabraCandidateType
    @abstract Underlying type of MecabraCandidate object.
    @constant MecabraCandidateTypeUndefined
    @constant MecabraCandidateTypeConversion
              Type of candidate returned by MecabraGetNextCandidate() and MecabraCandidateCreate().
    @constant MecabraCandidateTypeCompletion
              Type of candidate returned by MecabraWordCompletionGetNextCandidate().
 */
enum {
    MecabraCandidateTypeUndefined                           = 0,
    MecabraCandidateTypeConversion                          = 1,
    MecabraCandidateTypeCompletion                          = 2,
};
typedef int MecabraCandidateType;

/*! @function MecabraCandidateCopy
    @abstract Create MecabraCandidate object by copying an existing object.
    @param    candidate
              Object to be copied.
    @result   A new object that contains the same value as candidate, or NULL if candidate is NULL.
 */
extern
MecabraCandidateRef MecabraCandidateCopy(MecabraCandidateRef candidate);

/*! @function MecabraCandidateGetType
    @abstract Query the underlying type of a MecabraCandidate object.
    @param    candidate
              Candidate object to query.
    @discussion
              Some functions declared in this header support only certain type of candidate.
 */
extern
MecabraCandidateType MecabraCandidateGetType(MecabraCandidateRef candidate);

/*! @function MecabraCandidateCreate
    @abstract Create a candidate object. 
    @param    surface
              Surface string of candidate
    @param    reading
              Reading string of candidate
    @result   Return a candidate object.
    @discussion
              This function is DEPRECATED. If you frequently use MecabraCandidateCreate() and MecabraCandidateReplace()
              together to copy a MecabraCandidate object, you are encouraged to use MecabraCandidateCopy(). If you must
              create a MecabraCandidate object, please use MecabraConversionCandidateCreate() instead.
              
              This function returns a MecabraCandidate object whose candidate type is MecabraCandidateTypeConversion.
              Creating MecabraCandidateTypeCompletion type of MecabraCandidate object is not supported.

              Either surface or reading can be NULL.
*/
extern 
MecabraCandidateRef MecabraCandidateCreate(CFStringRef surface, CFStringRef reading);

/*! @function MecabraCandidateReplace
    @abstract Replace candidate content with another candidate.
    @param    candidate
              Candidate object to modify
    @param    replacement
              Candidate whose content to be put into candidate
    @discussion
              This function is DEPRECATED. If you frequently use MecabraCandidateCreate() and MecabraCandidateReplace()
              together to copy a MecabraCandidate object, you are encouraged to use MecabraCandidateCopy().
 
              Both candidate and replacement must be of MecabraCandidateTypeConversion type. Otherwise, this function is
              no-op. Replacing a MecabraCandidate object of MecabraCandidate object is not supported.
*/
extern 
void MecabraCandidateReplace(MecabraCandidateRef candidate, MecabraCandidateRef replacement);

/*! @function MecabraCandidateGetSurface
    @abstract Get the surface string of candidate.
    @param    candidate
              Candidate object
    @result   Return the surface string of candidate.
*/
extern 
CFStringRef MecabraCandidateGetSurface(MecabraCandidateRef candidate);

/*! @function MecabraCandidateGetReading
    @abstract Get the reading string of candidate.
    @param    candidate
              Candidate object
    @result   Return the reading string of candidate.
*/    
extern 
CFStringRef MecabraCandidateGetReading(MecabraCandidateRef candidate);

/*! @function MecabraCandidateGetWordCount
    @abstract Get the count of containing words.
    @param    candidate
              Candidate object
    @result   Return the count of containing words if candidate is of MecabraCandidateTypeConversion type.
              Return 0 otherwise.
    @discussion 
              Each candidate consists of one or more words. 
*/        
extern 
int MecabraCandidateGetWordCount(MecabraCandidateRef candidate);  
    
/*! @function MecabraCandidateGetWordLengthAtIndex
    @abstract Get the word length at index.
    @param    candidate
              Candidate object
    @param    index
              Index of the word
    @result   Return the word length at index if candidate is of MecabraCandidateTypeConversion type.
              Return 0 otherwise.
*/        
extern
unsigned short MecabraCandidateGetWordLengthAtIndex(MecabraCandidateRef candidate, CFIndex index);
    
/*! @function MecabraCandidateGetWordReadingLengthAtIndex
    @abstract Get the word reading length at index.
    @param    candidate
              Candidate object
    @param    index
              Index of the word
    @result   Return the word reading length at index  if candidate is of MecabraCandidateTypeConversion type.
              Return 0 otherwise.
*/        
extern
unsigned short MecabraCandidateGetWordReadingLengthAtIndex(MecabraCandidateRef candidate, CFIndex index);

    
extern
Boolean MecabraCandidateIsExtensionCandidate(MecabraCandidateRef candidate);
    
/*! @function MecabraCandidateRelease
    @abstract Release mecabra candidate object. 
    @param    candidate
              Mecabra candidate object
*/    
extern 
void MecabraCandidateRelease(MecabraCandidateRef candidate);

/*! @function MecabraConversionCandidateCreate
    @abstract Create a candidate object. 
    @param    surface
              Surface string of candidate
    @param    reading
              Reading string of candidate
    @result   Return a conversion candidate object.
    @discussion
              This function returns a MecabraCandidate object whose candidate type is MecabraCandidateTypeConversion.
              Creating MecabraCandidateTypeCompletion type of MecabraCandidate object is not supported.

              Either surface or reading can be NULL.
*/
extern 
MecabraCandidateRef MecabraConversionCandidateCreate(CFStringRef surface, CFStringRef reading);

/*
===============================================================================
    Extra API for Ruby Tools
===============================================================================
*/
    
/*
 * Except MecabraCandidateGetWeight(), functions in this section only support MecabraCandiate object of MecabraCandidateTypeConversion type.
 * For other type of candiate object, the behavior is undefined.
 */
extern
unsigned short MecabraCandidateGetLcAttrAtIndex(MecabraCandidateRef candidate, CFIndex index);

extern
unsigned short MecabraCandidateGetRcAttrAtIndex(MecabraCandidateRef candidate, CFIndex index);

extern
unsigned int MecabraCandidateGetTrieValueAtIndex(MecabraCandidateRef candidate, CFIndex index);

extern
unsigned short MecabraCandidateGetLastPrefixValue(MecabraCandidateRef candidate);
    
extern
int MecabraCandidateGetWeight(MecabraCandidateRef candidate);

extern
unsigned short MecabraCandidateGetKind(MecabraCandidateRef candidate);

extern
unsigned short MecabraCandidateGetKindIndex(MecabraCandidateRef candidate);

extern 
void MecabraCandidateSetTypeAsSingleWord(MecabraCandidateRef candidate, uint8_t kind, uint8_t kindIndex);

/*
===============================================================================
    SPI
===============================================================================
*/

extern
Boolean MecabraAnalyzeStringWithGeometryModel(MecabraRef mecabra, CFStringRef string, MecabraAnalysisOption options, void* geometryModel);

/* 
 * Return an array of CFNumber if candidate is of MecabraCandidateTypeConversion type.
 * Return NULL otherwise.
 */
extern
CFArrayRef MecabraCandidateCopySyllableLengthArray(MecabraCandidateRef candidate);

extern
void MecabraSetCandidateOrderAdjustment(MecabraRef mecabra, Boolean adjustOrder);

/* 
 * Specially used by Chinese
*/
extern
Boolean MecabraDeleteEntryFromLearningDictionary(MecabraRef mecabra, CFStringRef reading, CFStringRef surface);

#ifdef __cplusplus
}
#endif

#endif /* Mecabra_h */

