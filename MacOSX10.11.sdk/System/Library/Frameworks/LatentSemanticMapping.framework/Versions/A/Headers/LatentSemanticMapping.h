/*
	File:		LatentSemanticMapping.h

	Contains:	Classifies texts based on latent semantic information

	Version:	Mac OS X

	Copyright:	© 2001-2010 by Apple Computer, Inc., all rights reserved.

	Bugs?:		For bug reports, consult the following page on
				the World Wide Web:

					http://developer.apple.com/bugreporter/
*/

/*! @header Latent Semantic Mapping
 *
 *	This framework classifies texts based on latent semantic information.
 */

#ifndef __LATENTSEMANTICMAPPING__
#define __LATENTSEMANTICMAPPING__

#include <CoreFoundation/CoreFoundation.h>
#if TARGET_OS_EMBEDDED || TARGET_IPHONE_SIMULATOR
#define __DRIVERSERVICES__
#define __FP__
#define __MACHINEEXCEPTIONS__
#define __HFSVOLUMES__
#define __OSSERVICES__
#define __WEBSERVICESCORE__
#else
#include <Carbon/Carbon.h>
#endif

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! @enum Error codes
 *	@discussion Errors returned from LSM routines
 *	@constant kLSMMapOutOfState		This call cannot be issued in this map 
 *									state
 *	@constant kLSMMapNoSuchCategory	Invalid category specified
 *	@constant kLSMMapWriteError		An error occurred writing the map
 *	@constant kLSMMapBadPath		The URL you specified does not exist
 *  @constant kLSMMapBadCluster		The clusters you specified are invalid
 *	@constant kLSMMapOverflow		Cannot add more data to map
 */
enum {
	kLSMMapOutOfState		=	-6640,
	kLSMMapNoSuchCategory	=	-6641,
	kLSMMapWriteError		= 	-6642,
	kLSMMapBadPath			= 	-6643,
	kLSMMapBadCluster		=   -6644,
	kLSMMapOverflow			=   -6645
};


/*! @typedef LSMMapRef
 *	
 * An opaque Core Foundation type representing an LSM map (mutable).
 */
typedef struct __LSMMap *	LSMMapRef;

/*! @function LSMMapGetTypeID
 *
 * Returns the Core Foundation type identifier for LSM maps.
 */
CFTypeID LSMMapGetTypeID(void);

/*! @typedef LSMTextRef
 *	
 * An opaque Core Foundation type representing an input text (mutable).
 */
typedef struct __LSMText *	LSMTextRef;

/*! @function LSMTextGetTypeID
 *
 * Returns the Core Foundation type identifier for LSM texts.
 */
CFTypeID LSMTextGetTypeID(void);

/*! @typedef LSMResult
 *
 * An opaque Core Foundation type representing the result of a lookup (immutable).
 */
typedef struct __LSMResult * LSMResultRef;

/*! @function LSMResultGetTypeID
 *
 * Returns the Core Foundation type identifier for LSM results.
 */
CFTypeID LSMResultGetTypeID(void);

/*! @typedef LSMCategory
 *
 * An integral type representing a category.
 */
typedef uint32_t	LSMCategory;

/*! @function LSMMapCreate
 *
 *	Creates a new LSM map. Call CFRelease to dispose.
 */
LSMMapRef LSMMapCreate(CFAllocatorRef alloc, CFOptionFlags flags);

/*! @enum Map Flags
 *	@discussion Options that can be specified for LSMMapCreate. These options
 *				can improve mapping accuracy, at a potentially significant 
 *				increase in memory use.
 *	@constant kLSMMapPairs		Use pairs in addition to single words.
 *  @constant kLSMMapTriplets	Use triplets and pairs in addition to single 
 *								words.	
 *
 *	@constant kLSMMapHashText	Transform the text so it's not trivially
 *								human readable. Disables creation of language
 *								models.
 */
enum {
	kLSMMapPairs	=	1,
	kLSMMapTriplets	=	2,

	kLSMMapHashText = 	256
};

/*! @function LSMMapSetProperties
 *
 *	Set a dictionary of properties for the map. LSM makes its own copy
 *	of the properties, there's no need to retain them past this call.
 */
void LSMMapSetProperties(LSMMapRef mapref, CFDictionaryRef properties);

/*! @function LSMMapGetProperties
 *
 *	Get a dictionary of properties for the map. LSM retains ownership of
 *	this dictionary, do not release it.
 */
CFDictionaryRef LSMMapGetProperties(LSMMapRef mapref);

/*! @defineblock LSM Map properties
 *  @discussion A CFDictionary of arbitrary properties may be associated.
 *                              with an LSM map. The following keys currently
 *                              are interpreted by LSM, and all other keys starting with LSM...
 *                              are reserved.
 * @define kLSMAlgorithmKey   Algorithm to be used
 * @define kLSMAlgorithmDense      Perform an SVD on a dense matrix
 * @define kLSMAlgorithmSparse     Perform an SVD on a sparse matrix
 * @define kLSMAlgorithmAuto       Pick appropriate algorithm (default)
 * @define kLSMPrecisionKey   Precision to be used
 * @define kLSMPrecisionSingle     Use float arithmetic (default for dense)
 * @define kLSMPrecisionDouble     Use double arithmetic (default for sparse)
 * @define kLSMDimensionKey   Number of singular values to compute (numeric)
 * @define kLSMIterationsKey  Number of iterations to compute (numeric)
 * @define kLSMSweepAgeKey    Number of days between sweeping generations
 * @define kLSMSweepCutoffKey Minimum count to keep entry (numeric)
 */
    
#define	kLSMAlgorithmKey	CFSTR("LSMAlgorithm")
#define kLSMAlgorithmDense	CFSTR("LSMAlgorithmDense")
#define kLSMAlgorithmSparse	CFSTR("LSMAlgorithmSparse")

#define	kLSMPrecisionKey	CFSTR("LSMPrecision")
#define kLSMPrecisionFloat	CFSTR("LSMPrecisionFloat")
#define kLSMPrecisionDouble	CFSTR("LSMPrecisionDouble")

#define kLSMDimensionKey	CFSTR("LSMDimension")
#define kLSMIterationsKey	CFSTR("LSMIterations")

#define kLSMSweepAgeKey		CFSTR("LSMSweepAge")
#define kLSMSweepCutoffKey	CFSTR("LSMSweepCutoff")

/*! @/defineblock */

/*! @function LSMMapStartTraining
 *
 *	Puts the map into training mode, preparing it for the addition of more
 *	categories and/or texts. This function will be somewhat expensive, as it
 *	requires substantial data structure reorganization.
 */
OSStatus LSMMapStartTraining(LSMMapRef mapref);

/*! @function LSMMapAddCategory
 *
 *	Adds another category and returns its category identifier.
 */
LSMCategory LSMMapAddCategory(LSMMapRef mapref);

/*! @function LSMMapGetCategoryCount
 *
 * Returns the number of categories in the map.
 */	  
CFIndex LSMMapGetCategoryCount(LSMMapRef mapref);

/*! @function LSMMapSetStopWords
 *
 *	The specified words will be omitted from all classification efforts.
 *	Needs to be called before any other texts are created.
 *	The textref is no longer needed after this call.
 */
OSStatus LSMMapSetStopWords(LSMMapRef mapref, LSMTextRef textref);

/*! @function LSMMapAddText
 *
 *	Adds a training text to the given category. 
 *	The textref is no longer needed after this call.
 */
OSStatus LSMMapAddText(LSMMapRef mapref, LSMTextRef textref, LSMCategory category);

/*! @function LSMMapAddTextWithWeight
 *
 *	Adds a training text to the given category with a weight different from 1.
 *      The weight may be negative, but global counts will be pinned to 0.
 *	The textref is no longer needed after this call.
 */
OSStatus LSMMapAddTextWithWeight(LSMMapRef mapref, LSMTextRef textref, LSMCategory category, float weight);

/*! @function LSMMapCompile
 *
 *	Compiles the map into executable form and puts it into mapping mode,
 *	preparing it for the classification of texts. This function is
 *	computationally expensive.
 */
OSStatus LSMMapCompile(LSMMapRef mapref);

/*! @function LSMMapCreateClusters
 *
 *  Compute a set of clusters grouping similar categories or words.
 *  If subset is non-NULL, only perform clustering on the categories 
 *  or words listed.
 */
CFArrayRef LSMMapCreateClusters(CFAllocatorRef alloc,
			  LSMMapRef mapref, CFArrayRef subset,
			  CFIndex numClusters, CFOptionFlags flags);		

/* @enum Clustering Flags
 * @discussion Options for LSMMapCreateClusters.
 * @constant kLSMClusterCategories		Cluster categories
 * @constant kLSMClusterWords			Cluster words
 * @constant kLSMClusterTokens			Cluster binary tokens
 *
 * @constant kLSMClusterKMeans			Cluster using k-Means algorithm
 * @constant kLSMClusterAgglomerative	Cluster using agglomerative algorithm
 */
enum {
	kLSMClusterCategories		= 0,
	kLSMClusterWords			= 1,
	kLSMClusterTokens			= 2,

	kLSMClusterKMeans			= 0,
	kLSMClusterAgglomerative	= 4
};

/*! @function LSMMapApplyClusters
 *
 *  Group categories or words (tokens) into the specified sets of clusters.
 */
OSStatus LSMMapApplyClusters(LSMMapRef mapref, CFArrayRef clusters);

/*! @function LSMResultCreate
 *
 *	Returns, in decreasing order of likelihood, the categories or words
 *	that best match when a text is mapped into a map.
 */
LSMResultRef LSMResultCreate(CFAllocatorRef alloc,
				LSMMapRef mapref, LSMTextRef textref, 
				CFIndex numResults, CFOptionFlags flags);

/*! @enum Result Flags
 *	@discussion Options for LSMResultCreate. 
 *	@constant kLSMResultBestWords	Find the words, rather than categories,
 *									that best match.
 */
enum {
	kLSMResultBestWords		= 1,
};

/*! @function LSMResultGetCount
 * 	Returns the number of results.
 */
CFIndex LSMResultGetCount(LSMResultRef result);

/*! @function LSMResultGetCategory
 * 	Returns the category of the n-th best (zero based) result.
 */
LSMCategory LSMResultGetCategory(LSMResultRef result, CFIndex n);

/*! @function LSMResultGetScore
 * 	Returns the likelihood of the n-th best (zero based) result. 
 * A nan score often indicates that the category does not contain
 * any token.
 */
float LSMResultGetScore(LSMResultRef result, CFIndex n);

/*! @function LSMResultCopyWord
 *
 * Returns the word for the n-th best (zero based) result.
 */
CFStringRef	LSMResultCopyWord(LSMResultRef result, CFIndex n);

/*! @function LSMResultCopyToken
 *
 * Returns the token for the n-th best (zero based) result.
 */
CFDataRef	LSMResultCopyToken(LSMResultRef mapref, CFIndex n);

/*! @function LSMResultCopyWordCluster
 *
 * Returns the cluster of words for the n-th best (zero based) result.
 */
CFArrayRef	LSMResultCopyWordCluster(LSMResultRef result, CFIndex n);

/*! @function LSMResultCopyTokenCluster
 *
 * Returns the cluster of tokens for the n-th best (zero based) result.
 */
CFArrayRef	LSMResultCopyTokenCluster(LSMResultRef mapref, CFIndex n);

/*! @function LSMMapWriteToURL
 *
 *	Compiles the map if necessary and then stores it into the given file.
 */
OSStatus LSMMapWriteToURL(LSMMapRef mapref, CFURLRef file, CFOptionFlags flags);

/*! @function LSMMapCreateFromURL
 *
 *	Loads a map from a given file.
 */
LSMMapRef LSMMapCreateFromURL(CFAllocatorRef alloc, CFURLRef file, 
							  CFOptionFlags flags);

/*! @enum Storage Flags
 *	@discussion Options for LSMMap{CreateFrom,WriteTo}URL. 
 *	@constant kLSMMapDiscardCounts		Don't keep counts. If specified on
 *										loading, the map needs to be reloaded
 *										without this option before calling
 *										LSMStartTraining.
 *										If specified on storing, the stored
 *										map can't be retrained at all.
 *										This option can save a lot of memory 
 *                                      and/or disk space.
 *  @constant kLSMMapLoadMutable		Load map as mutable in training state.
 *  @constant kLSMMapHashText			(Defined above) If specified on 
 *										storing, will hash the map if it 
 *										hasn't been hashed yet.
 */
enum {
	kLSMMapDiscardCounts		= 1,
	kLSMMapLoadMutable		  	= 2,
};

/*! @function LSMMapWriteToStream
 *	
 * 	Writes information about a map and/or text to a stream in text form
 */
OSStatus LSMMapWriteToStream(LSMMapRef mapref, LSMTextRef textref,
							 CFWriteStreamRef stream, CFOptionFlags options);

/*! @function LSMTextCreate
 *
 *	Creates a new text.
 */
LSMTextRef LSMTextCreate(CFAllocatorRef alloc, LSMMapRef mapref);

/*! @function LSMTextAddWord
 *
 *	Adds a word to the text. The order of words is significant if the map
 *	uses pairs or triplets, and the count of words is always significant.
 */
OSStatus LSMTextAddWord(LSMTextRef textref, CFStringRef word);

/*! @function LSMTextAddWords
 *
 *	Breaks a string into words using the locale provided and adds the words 
 *  to the text. 
 */
OSStatus LSMTextAddWords(LSMTextRef textref, CFStringRef words, 
						 CFLocaleRef locale, CFOptionFlags flags);

/*! @enum Parsing Flags
 *	@discussion Options you can specify for LSMTextAddWords. 
 *	@constant kLSMTextPreserveAcronyms	Don't map all uppercase words to 
 *										lowercase.
 *  @constant kLSMTextPreserveCase		Don't change any words to lowercase.
 *	@constant kLSMTextApplySpamHeuristics	Try to find words in hostile text.
 */
enum {
	kLSMTextPreserveCase		= 1,
	kLSMTextPreserveAcronyms	= 2,
	kLSMTextApplySpamHeuristics	= 4
};

/*! @function LSMTextAddToken
 *
 *	Adds an arbitrary binary token to the text. The order of tokens is 
 *	significant if the map uses pairs or triplets, and the count of 
 *	tokens is always significant.
 */
OSStatus LSMTextAddToken(LSMTextRef textref, CFDataRef token);
	
#ifdef __cplusplus
}
#endif

#endif /* __LATENTSEMANTICMAPPING__ */
