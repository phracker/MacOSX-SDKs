/*
     File:       PMTemplate.h
 
     Contains:   Mac OS X Printing Manager Job Template Interfaces.
 
     Version:    Technology: Mac OS X
                 Release:    1.0
 
     Copyright:  © 1998-2001 by Apple Computer, Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __PMTEMPLATE__
#define __PMTEMPLATE__

#include <ApplicationServices/ApplicationServices.h>
#include <CoreFoundation/CoreFoundation.h>
#include <PrintCore/PMTicket.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Constants

|* An enum to distinguish between different kinds of template entries. Each entry in a template */
/* has a specific type that allows us to determine what other fields and functions are available. */

typedef SInt32 PMValueType;
enum {
    kPMValueUndefined           = 0,                            /* Template Entry is unknown or undefined */
    kPMValueBoolean             = 1,                            /* A CFBoolean of value true or false. */
    kPMValueData                = 2,                            /* A CFData, raw data converted to CFData. Has a default value, but no other constraints */
    kPMValueString              = 3,                            /* A CFString. Has a default value, but no other constraints */
    kPMValueSInt32              = 4,                            /* A CFNumber of long type. */
    kPMValueSInt32Range         = 5,                            /* A pair of CFNumbers, SInt32s, defining a range. */
    kPMValueUInt32              = 6,                            /* A CFNumber of unsigned long type (which isn't actually defined) */
    kPMValueUInt32Range         = 7,                            /* A pair of CFNumber, UInt32s, defining a range. */
    kPMValueDouble              = 8,                            /* A CFNumber of double type. */
    kPMValueDoubleRange         = 9,                            /* A pair of CFNumbers, doubles, defining a range of values. */
    kPMValuePMRect              = 10,                           /* A CFArray of 4 CFNumbers, all doubles. */
    kPMValueDate                = 11,                           /* A CFDate, holding date and time. */
    kPMValueArray               = 12,                           /* A CFArray, holding an array of values. No way to constrain these. */
    kPMValueDict                = 13,                           /* A CFDictionary, which has a default, but no constraints. */
    kPMValueTicket              = 14                            /* A PMTicket will require each key/value be identical - only works for list constraints. */
};


typedef SInt32 PMConstraintType;
enum {
    kPMConstraintUndefined      = 0,                            /* Undefined, no constraint checking required. */
    kPMConstraintRange          = 1,                            /* Range has a CFArray of two values, both CFTypeRefs */
    kPMConstraintList           = 2,                            /* List has an array CFTypeRefs, listing possible values. DefaultValues are CFNumberRef (zero-based index into the list) */
    kPMConstraintPrivate        = 3                             /* Private constraint, not checked by the system. */
};

/* Types */
/* A couple of keys are defined as special cases for the template code, only because it's */
/* a flat structure and the Job ticket is possibly a hierarchy of tickets. We need to be */
/* able to fetch the PaperInfo template information, but the Job Ticket has a separate */
/* ticket, so there is no key defined for fetching PaperInfo ticket from the Job Ticket. */
#define kPMTemplatePrelude       "com.apple.print.TemplateSpecific."
#define kPMPaperInfoListStr      kPMTemplatePrelude "PMTemplatePaperInfoTicket"
#define kPMPaperInfoList         CFSTR( kPMPaperInfoListStr )                      /* Will fetch the default value and constraint list for valid papers. */

#define kPMCustomPageWidthStr      kPMTemplatePrelude "CustomPaperWidth"
#define kPMCustomPageWidthKey         CFSTR( kPMCustomPageWidthStr )                      /* Will fetch the max and min range constraint for custom page width. */

#define kPMCustomPageHeightStr      kPMTemplatePrelude "CustomPaperHeight"
#define kPMCustomPageHeightKey         CFSTR( kPMCustomPageHeightStr )                      /* Will fetch the max and min range constraint for custom page height. */

#define kPMCustomPageMarginsStr      	    kPMTemplatePrelude "PMCustomPageMargins"
#define kPMCustomPageMarginsKey        	    CFSTR( kPMCustomPageMarginsStr )            /* Will fetch the margin data for a custom page. */

/* kPMDefaultReverseOutputOrderKey specifies whether the default page stacking order for the Tioga based printer is reverse.
	If true, the default output stacking order without host intervention is N, N-1, ... 2, 1. 
	If false, the default output stacking order without host intervention is 1, 2, ... , N-1 , N
	If this key is not present the default value is true since the typical 
	    Tioga printer module based raster printer stacks pages in reverse order.
*/
#define kPMDefaultReverseOutputOrderStr		kPMTemplatePrelude "PMDefaultReverseOutputOrder"
#define kPMDefaultReverseOutputOrderKey        	CFSTR( kPMDefaultReverseOutputOrderStr ) 


/* Function Prototypes */
/* The PMTemplateRef is defined in PMTicket.h to avoid circular references, and  */
/* included here just in case you do a search and can't find it. (you're welcome) */
/* It is supposed to be commented out because this header includes PMTicket.h */


/* Functions to create or delete a template */
EXTERN_API_C( OSStatus )
PMTemplateCreate                (PMTemplateRef *        newTemplate);

EXTERN_API_C( OSStatus )
PMTemplateDelete                (PMTemplateRef *        oldTemplate);


/* Functions to send to and from XML. Also a function to tell us if the template is locked and */
/* can't be modified. */

/*!
 * @function	PMTemplateWriteXML
 * @abstract	Write an XML description of the specified template to a file
 *		stream.
 */
EXTERN_API_C( OSStatus )
PMTemplateWriteXML		(PMTemplateRef 		srcTemplate,
				 FILE *			file);

EXTERN_API_C( OSStatus )
PMTemplateCreateXML             (PMTemplateRef          srcTemplate,
                                 CFDataRef *            xmlData);

EXTERN_API_C( OSStatus )
PMTemplateLoadFromXML           (CFDataRef              srcData,
                                 PMTemplateRef *        destTemplate);

EXTERN_API_C( OSStatus )
PMTemplateIsLocked              (PMTemplateRef          srcTemplate,
                                 Boolean *              locked);


/* Functions to add entries in a template. Each entry describes a value type and constraint */
/* type as well as default and constraint values for a specific key. This key must match the */
/* key we wish to validate in a PMTicket. */
EXTERN_API_C( OSStatus )
PMTemplateMakeFullEntry         (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMValueType            valueType,
                                 PMConstraintType       constraintType,
                                 CFTypeRef              defaultValue,
                                 CFTypeRef              constraintValue);

/* This function allows a caller to create the template entry in a series of calls, first to */
/* establish what type of entry it is and then later to set default and constraint values. This */
/* is especially useful for direct (non-cf) access to create template entries. There are various */
/* specialized functions for adding the default and cosntraint values with standard "C" types. */
EXTERN_API_C( OSStatus )
PMTemplateMakeEntry             (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMValueType            valueType,
                                 PMConstraintType       constraintType);


/* The following functions update an already created entry. */
EXTERN_API_C( OSStatus )
PMTemplateSetCFDefaultValue     (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFTypeRef              defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetSInt32DefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 SInt32                 defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetSInt32RangeDefaultValue (PMTemplateRef     pmTemplate,
                                 CFStringRef            key,
                                 SInt32                 min,
                                 SInt32                 max);

EXTERN_API_C( OSStatus )
PMTemplateSetBooleanDefaultValue (PMTemplateRef         pmTemplate,
                                 CFStringRef            key,
                                 Boolean                defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetDoubleDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 double                 defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetDoubleRangeDefaultValue (PMTemplateRef     pmTemplate,
                                 CFStringRef            key,
                                 double                 min,
                                 double                 max);

EXTERN_API_C( OSStatus )
PMTemplateSetCFDataDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFDataRef              defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetPMRectDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMRect *               defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateSetPMTicketDefaultValue (PMTemplateRef        pmTemplate,
                                 CFStringRef            key,
                                 PMTicketRef            defaultValue);

/* Functions to allow various constraints to be set up. */
EXTERN_API_C( OSStatus )
PMTemplateSetCFArrayConstraintValue (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 CFArrayRef             constraintValue);

EXTERN_API_C( OSStatus )
PMTemplateSetCFRangeConstraint  (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFTypeRef              min,
                                 CFTypeRef              max);

EXTERN_API_C( OSStatus )
PMTemplateSetSInt32RangeConstraint (PMTemplateRef       pmTemplate,
                                 CFStringRef            key,
                                 SInt32                 min,
                                 SInt32                 max);

/* Note - if the default value is a range, then the constraint should be a pair */
/* of ranges. */
EXTERN_API_C( OSStatus )
PMTemplateSetSInt32RangesConstraint (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 SInt32                 minForMin,
                                 SInt32                 maxForMin,
                                 SInt32                 minForMax,
                                 SInt32                 maxForMax);

EXTERN_API_C( OSStatus )
PMTemplateSetDoubleRangeConstraint (PMTemplateRef       pmTemplate,
                                 CFStringRef            key,
                                 double                 min,
                                 double                 max);

EXTERN_API_C( OSStatus )
PMTemplateSetDoubleRangesConstraint (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 double                 minForMin,
                                 double                 maxForMin,
                                 double                 minForMax,
                                 double                 maxForMax);


/* A List constraint could be a simple list of SInt32s. */
EXTERN_API_C( OSStatus )
PMTemplateSetSInt32ListConstraint (PMTemplateRef        pmTemplate,
                                 CFStringRef            key,
                                 int                    listSize,
                                 SInt32 *               sint32List);

/* Or a list of doubles. */
EXTERN_API_C( OSStatus )
PMTemplateSetDoubleListConstraint (PMTemplateRef        pmTemplate,
                                 CFStringRef            key,
                                 int                    listSize,
                                 double *               doubleList);

/* A list of rectangles. */
EXTERN_API_C( OSStatus )
PMTemplateSetPMRectListConstraint (PMTemplateRef        pmTemplate,
                                 CFStringRef            key,
                                 int                    listSize,
                                 PMRect *               rectList);

/* Or a ticket list. */
EXTERN_API_C( OSStatus )
PMTemplateSetPMTicketListConstraint (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 PMTicketRef            listTicket);


/* Boolean constraints don't need to be set - the constraint type is enough. */
/* Accessors for reaching specific template entry info based on the key passed in. */
EXTERN_API_C( OSStatus )
PMTemplateGetValueType          (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMValueType *          valueType);

EXTERN_API_C( OSStatus )
PMTemplateGetConstraintType     (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMConstraintType *     constraintType);

/* Fetch the various types of default values. */
EXTERN_API_C( OSStatus )
PMTemplateGetCFDefaultValue     (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFTypeRef *            defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetSInt32DefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 SInt32 *               defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetSInt32RangeDefaultValue (PMTemplateRef     pmTemplate,
                                 CFStringRef            key,
                                 SInt32 *               min,
                                 SInt32 *               max);

EXTERN_API_C( OSStatus )
PMTemplateGetBooleanDefaultValue (PMTemplateRef         pmTemplate,
                                 CFStringRef            key,
                                 Boolean *              defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetDoubleDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 double *               defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetDoubleRangeDefaultValue (PMTemplateRef     pmTemplate,
                                 CFStringRef            key,
                                 double *               min,
                                 double *               max);

EXTERN_API_C( OSStatus )
PMTemplateGetCFDataDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFDataRef *            defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetPMRectDefaultValue (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 PMRect *               defaultValue);

EXTERN_API_C( OSStatus )
PMTemplateGetPMTicketDefaultValue (PMTemplateRef        pmTemplate,
                                 CFStringRef            key,
                                 PMTicketRef *          defaultValue);

/* Fetch the various flavors of constraint values. */
EXTERN_API_C( OSStatus )
PMTemplateGetCFArrayConstraintValue (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 CFArrayRef *           constraintValue);

EXTERN_API_C( OSStatus )
PMTemplateGetCFRangeConstraintValue (PMTemplateRef      pmTemplate,
                                 CFStringRef            key,
                                 CFTypeRef *            min,
                                 CFTypeRef *            max);

EXTERN_API_C( OSStatus )
PMTemplateGetSInt32RangeConstraintValue (PMTemplateRef  pmTemplate,
                                 CFStringRef            key,
                                 SInt32 *               min,
                                 SInt32 *               max);

EXTERN_API_C( OSStatus )
PMTemplateGetSInt32RangesConstraintValue (PMTemplateRef  pmTemplate,
                                 CFStringRef            key,
                                 SInt32 *               minForMin,
                                 SInt32 *               maxForMin,
                                 SInt32 *               minForMax,
                                 SInt32 *               maxForMax);

EXTERN_API_C( OSStatus )
PMTemplateGetDoubleRangeConstraintValue (PMTemplateRef  pmTemplate,
                                 CFStringRef            key,
                                 double *               min,
                                 double *               max);

EXTERN_API_C( OSStatus )
PMTemplateGetDoubleRangesConstraintValue (PMTemplateRef  pmTemplate,
                                 CFStringRef            key,
                                 double *               minForMin,
                                 double *               maxForMin,
                                 double *               minForMax,
                                 double *               maxForMax);

/* The following functions need to be called twice, first to determine the length of */
/* the list and a second time, after allocating space, to actually fetch the list.*/
EXTERN_API_C( OSStatus )
PMTemplateGetSInt32ListConstraintValue (PMTemplateRef   pmTemplate,
                                 CFStringRef            key,
                                 int *                  listSize,
                                 SInt32 *               sint32List);

EXTERN_API_C( OSStatus )
PMTemplateGetDoubleListConstraintValue (PMTemplateRef   pmTemplate,
                                 CFStringRef            key,
                                 int *                  listSize,
                                 double *               doubleList);

EXTERN_API_C( OSStatus )
PMTemplateGetPMRectListConstraintValue (PMTemplateRef   pmTemplate,
                                 CFStringRef            key,
                                 int *                  listSize,
                                 PMRect *               rectList);

/* The Ticket APIs support a "List Ticket" that can hold numerous other tickets, so there is */
/* no need to allocate space for an array in this case. */
/* Always returns length and list at one time. */
EXTERN_API_C( OSStatus )
PMTemplateGetListTicketConstraintValue (PMTemplateRef   pmTemplate,
                                 CFStringRef            key,
                                 PMTicketRef *          listTicket);

/* Remove an entry from our template. */
EXTERN_API_C( OSStatus )
PMTemplateRemoveEntry           (PMTemplateRef          pmTemplate,
                                 CFStringRef            key);


/* Validate a ticket item - passing in the key and the item data. */
EXTERN_API_C( OSStatus )
PMTemplateValidateItem          (PMTemplateRef          pmTemplate,
                                 CFStringRef            key,
                                 CFTypeRef              item,
                                 Boolean *              validationResults);


/* Move a set of template entries from one template to another. Any entry in the destination */
/* template will be overwritten by an entry with the same key in the source template */
EXTERN_API_C( OSStatus )
PMTemplateMergeTemplates        (PMTemplateRef          sourceTemplate,
                                 PMTemplateRef          destTemplate);

/* NOTES:
    
    A few comments about some special template entry types:
    
    Rectangles - We assume a PMRect is four doubles. To verify a Rectangle, we allow the caller to 
        define a list of rectangles, of which one must match exactly, or, planned for the future, a
        range constraint that defines the min and max for horizontal and vertical, as well as the 
        maximum width and height. For now, only a list of rectangles can be used to validate a rect.
        
    Tickets - To facilitate validating a PaperInfo ticket, we provide a mechanism to construct a 
        list constraint for a ticket. A given ticket may then be validated by checking each key/value
        pair to confirm that it holds exactly the same value as a ticket in the list. There won't be
        any range checking for values within the ticket being validated, only a comparison with the
        fixed values in the ticket list.
    
    For other tickets, such as Print Settings, or Page Format, we call the validate functions to
        confirm that each entry complies with the proper constraint in the template. This allows
        for range constraints to be built for some entries, and list constraints for other entries.
*/

#ifdef __cplusplus
}
#endif

#endif /* __PMTEMPLATE__ */

