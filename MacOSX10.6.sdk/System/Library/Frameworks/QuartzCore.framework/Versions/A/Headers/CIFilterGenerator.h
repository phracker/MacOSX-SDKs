/* CoreImage - CIFilterGenerator.h

   Copyright (c) 2006 Apple Computer, Inc.
   All rights reserved. */
   
#import <Foundation/NSObject.h>

@class NSURL, NSDictionary, CIFilter;
/*!
    @header CIFilterGenerator
    @abstract   The goal is to CIFilters to be connected and form a single CIFilter for ease of reusability.
    @discussion The CIFilterGenerator allows developers to create complex effects built out of one or more CIFilter and reuse them without changing code. The resulting CIFilterGenerator can be written into a file for which we introduce a new file type (extension). A CIFilterGenerator can be created from the API or more conveniently through an editor view that we provide.
CIFilterGenerator files can be put into the Image Units folders on the system and they will be loaded when the user invokes one of the loadPlugIns methods. They will be registered by their filename or if present by an attribute in its description. 
*/

/*!
    @const      kCIFilterGeneratorExportedKey
    @abstract   CIFilterGeneratorExportedKey
    @discussion The key of the target object that is exported
*/
extern NSString *const kCIFilterGeneratorExportedKey;

/*!
    @const      kCIFilterGeneratorExportedKeyTargetObject
    @abstract   CIFilterGeneratorExportedKeyTargetObject
    @discussion Target object for the exported key
*/
extern NSString *const kCIFilterGeneratorExportedKeyTargetObject;

/*!
    @const      kIfilterGeneratorExportedKeyName
    @abstract   CIFilterGeneratorExportedKeyName
    @discussion Name of the key under which it is exported.
*/
extern NSString *const kCIFilterGeneratorExportedKeyName;

/*!
    @class	CIFilterGenerator
    @abstract    The CIFilterGenerator allows you to create a reusable chain of connected CIFilters and images.
    @discussion  (comprehensive description)
*/
@interface CIFilterGenerator : NSObject <NSCoding, NSCopying>
{

@private
	struct CIFilterGeneratorStruct	*__strong _filterGeneratorStruct;
}

/*!
    @method     filterGenerator
    @abstract   Create an empty CIFilterGenerator.
    @discussion This creates an empty CIFilterGenerator in which you connect filters and images.
    @result     CIFilterGenerator object.
*/
+ (CIFilterGenerator*)filterGenerator;
/*!
    @method     filterGeneratorWithContentsOfURL:
    @abstract   Create a CIFilterGenerator with the contents of the file.
    @discussion This method reads the file at the URL and creates a CIFilterGenerator object for you. 
    @param      aURL URL of the CIFilterGenerator file.
    @result     CIFilterGenerator object. If the file could not be read it returns nil.
*/
+ (CIFilterGenerator*)filterGeneratorWithContentsOfURL:(NSURL*)aURL;

/*!
    @method     initWithContentsOfURL:
    @abstract   Initializes a CIFilterGenerator with the contents of the file.
    @discussion This method reads the file at the URL and initializes the CIFilterGenerator object with it. 
    @param      aURL URL of the CIFilterGenerator file.
    @result     CIFilterGenerator object. If the file could not be read it returns nil.
*/
- (id)initWithContentsOfURL:(NSURL*)aURL;

/*!
    @method     connectObject:withKey:toObject:withKey:
    @abstract   Connect two objects into the filter chain.
    @discussion This method connects two object in the filter chain. For instance you can connect the outputImage key of a CISepiaTone filter object to the inputImage key of another CIFilter.
    @param      sourceObject A CIFilter or CIImage or an NSString or an NSURL describing the path to the image 
    @param      sourceKey For KVC access to the source object. Can be nil which means that the source object will be used directly.
    @param      targetObject The object that you link the source object to.
    @param      targetKey The key that you assign the source object to
*/
- (void)connectObject:(id)sourceObject withKey:(NSString*)sourceKey toObject:(id)targetObject withKey:(NSString*)targetKey;
	
/*!
    @method     disconnectObject:withKey:toObject:withKey:
    @abstract   Removes the connection between two objects in the filter chain.
    @discussion Use this method to disconnect two objects that you connected using the connectObject:withKey:toObject:withKey: method.
    @param      sourceObject A CIFilter or CIImage or an NSString or an NSURL describing the path to the image 
    @param      sourceKey For KVC access to the source object. Can be nil which means that the source object will be used directly.
    @param      targetObject The object that you linked the source object to.
    @param      targetKey The key that you assigned the source object to
*/
- (void)disconnectObject:(id)sourceObject withKey:(NSString*)key toObject:(id)targetObject withKey:(NSString*)targetKey;

/*!
    @method     exportKey:fromObject:withName:
    @abstract   This methods allows you to export an input or output key of an object in the filter chain to be available through the inputKeys or outputKeys API when converted into a CIFilter
    @discussion When you create a CIFilter from the CIFilterGenerator, you might want the client of the filter being able to set some of the paramters of the filter chain. To do so these parameters have to be exported as keys much like the inputKeys and outputKeys of all CIFilters.
    @param      key The key path that is to be exported from the target object (eg. inputImage)
    @param      targetObject The object of which the key is to be exported (eg the filter).
    @param      exportedKeyName The name under which you want the new key to be available. This parameter can be nil in which case the original key name will be used. This name has to be unique. If a key being exported is an inputKey of the filter it will be exported as an input key and the other way around for output keys.
*/
- (void)exportKey:(NSString*)key fromObject:(id)targetObject withName:(NSString*)exportedKeyName;

/*!
    @method     removeExportedKey:
    @abstract   Removes a key that was exported before using exportKey:fromObject:withName:
    @discussion Use this method when you want to remove a prior exported key. It will not show up under inputKeys or outputKeys anymore.
	@param      exportedKeyName Name of the key that was exported. If you didn't specify a name, it is the name of the key on the target object.
*/
- (void)removeExportedKey:(NSString*)exportedKeyName;
/*!
    @method     exportedKeys
    @abstract   An array of the exported keys.
    @discussion Use this method to get an NSArray of all the keys that you have exported using exportKey:fromObject:withName: or that were exported before written to a file from which you read the filter chain.
    @result     An array of dictionaries that describe the exported key and target object. See CIExportedKey, CIExportedKeyTargetObject and CIExportedKeyName for keys used in the dictionary.
*/
- (NSDictionary*)exportedKeys;
/*!
    @method     setAttributes:forExportedKey:
    @abstract   Set a new dictionary of attributes for an exported key.
    @discussion By default, the exported key inherits the attributes from its original key and target object. Use this method to for instance change the default value or lower the maximum allowed value.
    @param      attributes See attribute description in CIFilter description.
    @param      key The exported key for which the attributes should be set.
*/

- (void)setAttributes:(NSDictionary*)attributes forExportedKey:(NSString*)key;

/*!
    @method     classAttributes
    @abstract   Retrieve the class attributes that will be used to register the filter using the registerFilterName method.
    @discussion Make sure you set the class attributes first - see CIFilter for a description of the classAttributes that are needed to register a filter.
    @result     NSDictionary with class attributes that will be used to register the filter
*/
- (NSDictionary*)classAttributes;

/*!
    @method     setClassAttributes:
    @abstract   Set the class attributes that will be used to register the filter using the registerFilterName method.
    @discussion Make sure you set the class attributes first - see CIFilter for a description of the classAttributes that are needed to register a filter.
    @param      attributes NSDictionary - see CIFilter for a description of the classAttributes that are needed to register a filter
*/
- (void)setClassAttributes:(NSDictionary*)attributes;

/*!
    @method     filter
    @abstract   Create a CIFilter object based on this filter chain.
    @discussion This method creates a CIFilter from the filter chain where the topology of the chain is immutable, meaning that changes to the filter chain will not be reflected in the filter. The filter will have the input and output keys that were exported as described above.
    @result     CIFilter object
*/
- (CIFilter*)filter;

/*!
    @method     registerFilterName:
    @abstract   Register the resulting filter of the chain in the CIFilter repository.
    @discussion This method allows you to register the filter chain as a named filter in the filter repository. You can then create a CIFilter object from it using the filterWithName: method. Make sure you set the class attributes first - see CIFilter for a description of the classAttributes that are needed to register a filter.
    @param      name The name under which the filter will be registered. This name has to be unique.
*/
- (void)registerFilterName:(NSString *)name;
	// when registering we automatically add the kCIFilterGeneratorCategory to the filters categories. The kCIFilterGeneratorCategory is purely for identification purpose and will not be exposed in the filter browser as a seperate category

/*!
    @method     writeToURL:atomically:
    @abstract   Write the CIFilterGenerator into a file
    @discussion Use this method to save your filter chain into a file.
    @param      aURL Target URL of the file.
    @param      flag When true it first creates an inerim file befor overwritting any existing file.
    @result     Returns true when the chain with written our succesfully
*/
- (BOOL)writeToURL:(NSURL *)aURL atomically:(BOOL)flag;

@end
