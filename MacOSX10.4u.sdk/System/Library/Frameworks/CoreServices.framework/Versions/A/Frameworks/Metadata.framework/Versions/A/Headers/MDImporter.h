/**
 *      filename: MDImporter.h
 *      created : Thu Apr  8 13:33:00 2004
 *      LastEditDate Was "Thu May 20 10:07:05 2004"
 *
 */

/*!
        @header MDImporter.h
        MDImporter is the link between the metadata contained  within a
        file and an MDItem. The Server listens for changes to files
        and loads in a CFPlugIn (MDImporter) and the importer will then
        extract all interesting data out of the file to store in a MDItem.

*/
#if !defined(__MDIMPORTER__)
#define __MDIMPORTER__ 1

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4

#include <CoreFoundation/CoreFoundation.h>
#include <Metadata/MDItem.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
        @constant kMDImporterTypeID The importer only loads CFPlugIns of type
        kMDImporterTypeID - 8B08C4BF-415B-11D8-B3F9-0003936726FC

        @constant kMDImporterInterfaceID Importers must implement this
        Interface - 6EBC27C4-899C-11D8-84A3-0003936726FC
*/

#define kMDImporterTypeID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,0x8B,0x08,0xC4,0xBF,0x41,0x5B,0x11,0xD8,0xB3,0xF9,0x00,0x03,0x93,0x67,0x26,0xFC)
#define kMDImporterInterfaceID CFUUIDGetConstantUUIDWithBytes(kCFAllocatorDefault,0x6E,0xBC,0x27,0xC4,0x89,0x9C,0x11,0xD8,0x84,0xAE,0x00,0x03,0x93,0x67,0x26,0xFC)

/*!
        @typedef MDImporterInterfaceStruct
        Interface for the plugIn. The plugin needs to provide at least
        the ImporterImportData function.

        @function ImporterImportData
        Import data from the file given to by path into the system.

        @param thisInterface this plugin

        @param attributes any attributes that can be gotten from the
        file should be places in the attributes
        CFMutableDictionaryRef. For example if the file has a
        kMDItemDuration  then the key would be kMDItemDuration and the
        value would be a CFNumberRef containing the duration of the
        song etc. If you want to remove an attribute, then in the
        dictionary place the attribute and set the value of the
        attribute to kCFNull.

        @param contentTypeUTI  The content type (a uniform type identifier)
        of the file that is given to this plugin.

        @param pathToFile location of the file on disk.

        @result Boolean indicating if the export was successful
*/

#if defined(__COREFOUNDATION_CFPLUGINCOM__)
typedef struct {
    IUNKNOWN_C_GUTS;
    Boolean    (*ImporterImportData)(void *thisInterface,CFMutableDictionaryRef attributes,CFStringRef contentTypeUTI,CFStringRef pathToFile);
} MDImporterInterfaceStruct;
#endif

#if defined(__cplusplus)
}
#endif

#endif
#endif
