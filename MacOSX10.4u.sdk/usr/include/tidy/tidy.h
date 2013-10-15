#ifndef __TIDY_H__
#define __TIDY_H__

/** @file tidy.h - Defines HTML Tidy API implemented by tidy library.

  Public interface is const-correct and doesn't explicitly depend
  on any globals.  Thus, thread-safety may be introduced w/out
  changing the interface.

  Looking ahead to a C++ wrapper, C functions always pass 
  this-equivalent as 1st arg.


  Copyright (c) 1998-2004 World Wide Web Consortium
  (Massachusetts Institute of Technology, European Research 
  Consortium for Informatics and Mathematics, Keio University).
  All Rights Reserved.

  CVS Info :

    $Author: rbraun $ 
    $Date: 2004/05/04 20:05:14 $ 
    $Revision: 1.1.1.1 $ 

  Contributing Author(s):

     Dave Raggett <dsr@w3.org>

  The contributing author(s) would like to thank all those who
  helped with testing, bug fixes and suggestions for improvements. 
  This wouldn't have been possible without your help.

  COPYRIGHT NOTICE:
 
  This software and documentation is provided "as is," and
  the copyright holders and contributing author(s) make no
  representations or warranties, express or implied, including
  but not limited to, warranties of merchantability or fitness
  for any particular purpose or that the use of the software or
  documentation will not infringe any third party patents,
  copyrights, trademarks or other rights. 

  The copyright holders and contributing author(s) will not be held
  liable for any direct, indirect, special or consequential damages
  arising out of any use of the software or documentation, even if
  advised of the possibility of such damage.

  Permission is hereby granted to use, copy, modify, and distribute
  this source code, or portions hereof, documentation and executables,
  for any purpose, without fee, subject to the following restrictions:

  1. The origin of this source code must not be misrepresented.
  2. Altered versions must be plainly marked as such and must
     not be misrepresented as being the original source.
  3. This Copyright notice may not be removed or altered from any
     source or altered source distribution.
 
  The copyright holders and contributing author(s) specifically
  permit, without fee, and encourage the use of this source code
  as a component for supporting the Hypertext Markup Language in
  commercial products. If you use this source code in a product,
  acknowledgment is not required but would be appreciated.


  Created 2001-05-20 by Charles Reitzel
  Updated 2002-07-01 by Charles Reitzel - 1st Implementation

*/

#include "platform.h"
#include "tidyenum.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Opaque Opaque Types
**
** Cast to implementation types within lib.
** Reduces inter-dependencies/conflicts w/ application code.
** @{
*/

/** @struct TidyDoc
**  Opaque document datatype
*/
opaque_type( TidyDoc );

/** @struct TidyOption
**  Opaque option datatype
*/
opaque_type( TidyOption );

/** @struct TidyNode
**  Opaque node datatype
*/
opaque_type( TidyNode );

/** @struct TidyAttr
**  Opaque attribute datatype
*/
opaque_type( TidyAttr );

/** @} */

TIDY_STRUCT struct _TidyBuffer;
typedef struct _TidyBuffer TidyBuffer;


/** @defgroup Basic Basic Operations
**
** Tidy public interface
**
** Several functions return an integer document status:
**
** <pre>
** 0    -> SUCCESS
** >0   -> 1 == TIDY WARNING, 2 == TIDY ERROR
** <0   -> SEVERE ERROR
** </pre>
** 
The following is a short example program.

<pre>
#include &lt;tidy.h&gt;
#include &lt;buffio.h&gt;
#include &lt;stdio.h&gt;
#include &lt;errno.h&gt;


int main(int argc, char **argv )
{
  const char* input = "&lt;title&gt;Foo&lt;/title&gt;&lt;p&gt;Foo!";
  TidyBuffer output = {0};
  TidyBuffer errbuf = {0};
  int rc = -1;
  Bool ok;

  TidyDoc tdoc = tidyCreate();                     // Initialize "document"
  printf( "Tidying:\t\%s\\n", input );

  ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
  if ( ok )
    rc = tidySetErrorBuffer( tdoc, &amp;errbuf );      // Capture diagnostics
  if ( rc &gt;= 0 )
    rc = tidyParseString( tdoc, input );           // Parse the input
  if ( rc &gt;= 0 )
    rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
  if ( rc &gt;= 0 )
    rc = tidyRunDiagnostics( tdoc );               // Kvetch
  if ( rc &gt; 1 )                                    // If error, force output.
    rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
  if ( rc &gt;= 0 )
    rc = tidySaveBuffer( tdoc, &amp;output );          // Pretty Print

  if ( rc &gt;= 0 )
  {
    if ( rc &gt; 0 )
      printf( "\\nDiagnostics:\\n\\n\%s", errbuf.bp );
    printf( "\\nAnd here is the result:\\n\\n\%s", output.bp );
  }
  else
    printf( "A severe error (\%d) occurred.\\n", rc );

  tidyBufFree( &amp;output );
  tidyBufFree( &amp;errbuf );
  tidyRelease( tdoc );
  return rc;
}
</pre>
** @{
*/

TIDY_EXPORT TidyDoc     tidyCreate(void);
TIDY_EXPORT void        tidyRelease( TidyDoc tdoc );

/** Let application store a chunk of data w/ each Tidy instance.
**  Useful for callbacks.
*/
TIDY_EXPORT void        tidySetAppData( TidyDoc tdoc, ulong appData );

/** Get application data set previously */
TIDY_EXPORT ulong       tidyGetAppData( TidyDoc tdoc );

/** Get release date (version) for current library */
TIDY_EXPORT ctmbstr     tidyReleaseDate(void);

/* Diagnostics and Repair
*/

/** Get status of current document. */
TIDY_EXPORT int         tidyStatus( TidyDoc tdoc );

/** Detected HTML version: 0, 2, 3 or 4 */
TIDY_EXPORT int         tidyDetectedHtmlVersion( TidyDoc tdoc );

/** Input is XHTML? */
TIDY_EXPORT Bool        tidyDetectedXhtml( TidyDoc tdoc );

/** Input is generic XML (not HTML or XHTML)? */
TIDY_EXPORT Bool        tidyDetectedGenericXml( TidyDoc tdoc );

/** Number of Tidy errors encountered.  If > 0, output is suppressed
**  unless TidyForceOutput is set.
*/
TIDY_EXPORT uint        tidyErrorCount( TidyDoc tdoc );

/** Number of Tidy warnings encountered. */
TIDY_EXPORT uint        tidyWarningCount( TidyDoc tdoc );

/** Number of Tidy accessibility warnings encountered. */
TIDY_EXPORT uint        tidyAccessWarningCount( TidyDoc tdoc );

/** Number of Tidy configuration errors encountered. */
TIDY_EXPORT uint        tidyConfigErrorCount( TidyDoc tdoc );

/* Get/Set configuration options
*/
/** Load an ASCII Tidy configuration file */
TIDY_EXPORT int         tidyLoadConfig( TidyDoc tdoc, ctmbstr configFile );

/** Load a Tidy configuration file with the specified character encoding */
TIDY_EXPORT int         tidyLoadConfigEnc( TidyDoc tdoc, ctmbstr configFile,
                                           ctmbstr charenc );

TIDY_EXPORT Bool        tidyFileExists( ctmbstr filename );


/** Set the input/output character encoding for parsing markup.
**  Values include: ascii, latin1, raw, utf8, iso2022, mac,
**  win1252, utf16le, utf16be, utf16, big5 and shiftjis.  Case in-sensitive.
*/
TIDY_EXPORT int         tidySetCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the input encoding for parsing markup.
** As for tidySetCharEncoding but only affects the input encoding
**/
TIDY_EXPORT int         tidySetInCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the output encoding.
**/
TIDY_EXPORT int         tidySetOutCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** @} end Basic group */


/** @defgroup Configuration Configuration Options
**
** Functions for getting and setting Tidy configuration options.
** @{
*/

/** Applications using TidyLib may want to augment command-line and
**  configuration file options.  Setting this callback allows an application 
**  developer to examine command-line and configuration file options after
**  TidyLib has examined them and failed to recognize them.
**/

typedef Bool (*TidyOptCallback)( ctmbstr option, ctmbstr value );

TIDY_EXPORT Bool          tidySetOptionCallback( TidyDoc tdoc, TidyOptCallback pOptCallback );

/** Get option ID by name */
TIDY_EXPORT TidyOptionId  tidyOptGetIdForName( ctmbstr optnam );

/** Get iterator for list of option */
/** 
Example:
<pre>
TidyIterator itOpt = tidyGetOptionList( tdoc );
while ( itOpt )
{
  TidyOption opt = tidyGetNextOption( tdoc, &itOpt );
  .. get/set option values ..
}
</pre>
*/

TIDY_EXPORT TidyIterator  tidyGetOptionList( TidyDoc tdoc );
/** Get next Option */
TIDY_EXPORT TidyOption    tidyGetNextOption( TidyDoc tdoc, TidyIterator* pos );

/** Lookup option by ID */
TIDY_EXPORT TidyOption    tidyGetOption( TidyDoc tdoc, TidyOptionId optId );
/** Lookup option by name */
TIDY_EXPORT TidyOption    tidyGetOptionByName( TidyDoc tdoc, ctmbstr optnam );

/** Get ID of given Option */
TIDY_EXPORT TidyOptionId  tidyOptGetId( TidyOption opt );

/** Get name of given Option */
TIDY_EXPORT ctmbstr       tidyOptGetName( TidyOption opt );

/** Get datatype of given Option */
TIDY_EXPORT TidyOptionType tidyOptGetType( TidyOption opt );

/** Is Option read-only? */
TIDY_EXPORT Bool          tidyOptIsReadOnly( TidyOption opt );

/** Get category of given Option */
TIDY_EXPORT TidyConfigCategory tidyOptGetCategory( TidyOption opt );

/** Get default value of given Option as a string */
TIDY_EXPORT ctmbstr       tidyOptGetDefault( TidyOption opt );

/** Get default value of given Option as an unsigned integer */
TIDY_EXPORT ulong         tidyOptGetDefaultInt( TidyOption opt );

/** Get default value of given Option as a Boolean value */
TIDY_EXPORT Bool          tidyOptGetDefaultBool( TidyOption opt );

/** Iterate over Option "pick list" */
TIDY_EXPORT TidyIterator  tidyOptGetPickList( TidyOption opt );
/** Get next string value of Option "pick list" */
TIDY_EXPORT ctmbstr       tidyOptGetNextPick( TidyOption opt, TidyIterator* pos );

/** Get current Option value as a string */
TIDY_EXPORT ctmbstr       tidyOptGetValue( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a string */
TIDY_EXPORT Bool          tidyOptSetValue( TidyDoc tdoc, TidyOptionId optId, ctmbstr val );
/** Set named Option value as a string.  Good if not sure of type. */
TIDY_EXPORT Bool          tidyOptParseValue( TidyDoc tdoc, ctmbstr optnam, ctmbstr val );

/** Get current Option value as an integer */
TIDY_EXPORT ulong         tidyOptGetInt( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as an integer */
TIDY_EXPORT Bool          tidyOptSetInt( TidyDoc tdoc, TidyOptionId optId, ulong val );

/** Get current Option value as a Boolean flag */
TIDY_EXPORT Bool          tidyOptGetBool( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a Boolean flag */
TIDY_EXPORT Bool          tidyOptSetBool( TidyDoc tdoc, TidyOptionId optId, Bool val );

/** Reset option to default value by ID */
TIDY_EXPORT Bool          tidyOptResetToDefault( TidyDoc tdoc, TidyOptionId opt );
/** Reset all options to their default values */
TIDY_EXPORT Bool          tidyOptResetAllToDefault( TidyDoc tdoc );

/** Take a snapshot of current config settings */
TIDY_EXPORT Bool          tidyOptSnapshot( TidyDoc tdoc );
/** Reset config settings to snapshot (after document processing) */
TIDY_EXPORT Bool          tidyOptResetToSnapshot( TidyDoc tdoc );

/** Any settings different than default? */
TIDY_EXPORT Bool          tidyOptDiffThanDefault( TidyDoc tdoc );
/** Any settings different than snapshot? */
TIDY_EXPORT Bool          tidyOptDiffThanSnapshot( TidyDoc tdoc );

/** Copy current configuration settings from one document to another */
TIDY_EXPORT Bool          tidyOptCopyConfig( TidyDoc tdocTo, TidyDoc tdocFrom );

/** Get character encoding name.  Used with TidyCharEncoding,
**  TidyOutCharEncoding, TidyInCharEncoding */
TIDY_EXPORT ctmbstr       tidyOptGetEncName( TidyDoc tdoc, TidyOptionId optId );

/** Get current pick list value for option by ID.  Useful for enum types. */
TIDY_EXPORT ctmbstr       tidyOptGetCurrPick( TidyDoc tdoc, TidyOptionId optId);

/** Iterate over user declared tags */
TIDY_EXPORT TidyIterator  tidyOptGetDeclTagList( TidyDoc tdoc );
/** Get next declared tag of specified type: TidyInlineTags, TidyBlockTags,
**  TidyEmptyTags, TidyPreTags */
TIDY_EXPORT ctmbstr       tidyOptGetNextDeclTag( TidyDoc tdoc, 
                                                 TidyOptionId optId,
                                                 TidyIterator* iter );
/** @} end Configuration group */

/** @defgroup IO  I/O and Messages
**
** By default, Tidy will define, create and use 
** instances of input and output handlers for 
** standard C buffered I/O (i.e. FILE* stdin,
** FILE* stdout and FILE* stderr for content
** input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler
** will be used for config files.  Command line
** options will just be set directly.
**
** @{
*/

/*****************
   Input Source
*****************/
/** Input Callback: get next byte of input */
typedef int  (*TidyGetByteFunc)( ulong sourceData );

/** Input Callback: unget a byte of input */
typedef void (*TidyUngetByteFunc)( ulong sourceData, byte bt );

/** Input Callback: is end of input? */
typedef Bool (*TidyEOFFunc)( ulong sourceData );

/** End of input "character" */
#define EndOfStream (~0u)

/** TidyInputSource - Delivers raw bytes of input
*/
TIDY_STRUCT
typedef struct _TidyInputSource
{
  /* Instance data */
  ulong               sourceData;  /**< Input context.  Passed to callbacks */

  /* Methods */
  TidyGetByteFunc     getByte;     /**< Pointer to "get byte" callback */
  TidyUngetByteFunc   ungetByte;   /**< Pointer to "unget" callback */
  TidyEOFFunc         eof;         /**< Pointer to "eof" callback */
} TidyInputSource;

/** Facilitates user defined source by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool tidyInitSource( TidyInputSource*  source,
                                 void*             srcData,
                                 TidyGetByteFunc   gbFunc,
                                 TidyUngetByteFunc ugbFunc,
                                 TidyEOFFunc       endFunc );

/** Helper: get next byte from input source */
TIDY_EXPORT uint tidyGetByte( TidyInputSource* source );

/** Helper: unget byte back to input source */
TIDY_EXPORT void tidyUngetByte( TidyInputSource* source, uint byteValue );

/** Helper: check if input source at end */
TIDY_EXPORT Bool tidyIsEOF( TidyInputSource* source );


/****************
   Output Sink
****************/
/** Output callback: send a byte to output */
typedef void (*TidyPutByteFunc)( ulong sinkData, byte bt );


/** TidyOutputSink - accepts raw bytes of output
*/
TIDY_STRUCT
typedef struct _TidyOutputSink
{
  /* Instance data */
  ulong               sinkData;  /**< Output context.  Passed to callbacks */

  /* Methods */
  TidyPutByteFunc     putByte;   /**< Pointer to "put byte" callback */
} TidyOutputSink;

/** Facilitates user defined sinks by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool tidyInitSink( TidyOutputSink* sink, 
                               void*           snkData,
                               TidyPutByteFunc pbFunc );

/** Helper: send a byte to output */
TIDY_EXPORT void tidyPutByte( TidyOutputSink* sink, uint byteValue );


/** Callback to filter messages by diagnostic level:
**  info, warning, etc.  Just set diagnostic output 
**  handler to redirect all diagnostics output.  Return true
**  to proceed with output, false to cancel.
*/
typedef Bool (*TidyReportFilter)( TidyDoc tdoc, TidyReportLevel lvl,
                                  uint line, uint col, ctmbstr mssg );

/** Give Tidy a filter callback to use */
TIDY_EXPORT Bool    tidySetReportFilter( TidyDoc tdoc,
                                         TidyReportFilter filtCallback );

/** Set error sink to named file */
TIDY_EXPORT FILE*   tidySetErrorFile( TidyDoc tdoc, ctmbstr errfilnam );
/** Set error sink to given buffer */
TIDY_EXPORT int     tidySetErrorBuffer( TidyDoc tdoc, TidyBuffer* errbuf );
/** Set error sink to given generic sink */
TIDY_EXPORT int     tidySetErrorSink( TidyDoc tdoc, TidyOutputSink* sink );

/** @} end IO group */


/** @defgroup Memory  Memory Allocation
**
** By default, Tidy will use its own wrappers
** around standard C malloc/free calls. 
** These wrappers will abort upon any failures.
** If any are set, all must be set.
** Pass NULL to clear previous setting.
**
** May be used to set environment-specific allocators
** such as used by web server plugins, etc.
**
** @{
*/

/** Callback for "malloc" replacement */
typedef void* (*TidyMalloc)( size_t len );
/** Callback for "realloc" replacement */
typedef void* (*TidyRealloc)( void* buf, size_t len );
/** Callback for "free" replacement */
typedef void  (*TidyFree)( void* buf );
/** Callback for "out of memory" panic state */
typedef void  (*TidyPanic)( ctmbstr mssg );

/** Give Tidy a malloc() replacement */
TIDY_EXPORT Bool        tidySetMallocCall( TidyMalloc fmalloc );
/** Give Tidy a realloc() replacement */
TIDY_EXPORT Bool        tidySetReallocCall( TidyRealloc frealloc );
/** Give Tidy a free() replacement */
TIDY_EXPORT Bool        tidySetFreeCall( TidyFree ffree );
/** Give Tidy an "out of memory" handler */
TIDY_EXPORT Bool        tidySetPanicCall( TidyPanic fpanic );

/** @} end Memory group */

/* TODO: Catalog all messages for easy translation
TIDY_EXPORT ctmbstr     tidyLookupMessage( int errorNo );
*/



/** @defgroup Parse Document Parse
**
** Parse markup from a given input source.  String and filename 
** functions added for convenience.  HTML/XHTML version determined
** from input.
** @{
*/

/** Parse markup in named file */
TIDY_EXPORT int         tidyParseFile( TidyDoc tdoc, ctmbstr filename );

/** Parse markup from the standard input */
TIDY_EXPORT int         tidyParseStdin( TidyDoc tdoc );

/** Parse markup in given string */
TIDY_EXPORT int         tidyParseString( TidyDoc tdoc, ctmbstr content );

/** Parse markup in given buffer */
TIDY_EXPORT int         tidyParseBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Parse markup in given generic input source */
TIDY_EXPORT int         tidyParseSource( TidyDoc tdoc, TidyInputSource* source);

/** @} End Parse group */


/** @defgroup Clean Diagnostics and Repair
**
** @{
*/
/** Execute configured cleanup and repair operations on parsed markup */
TIDY_EXPORT int         tidyCleanAndRepair( TidyDoc tdoc );

/** Run configured diagnostics on parsed and repaired markup. 
**  Must call tidyCleanAndRepair() first.
*/
TIDY_EXPORT int         tidyRunDiagnostics( TidyDoc tdoc );

/** @} end Clean group */


/** @defgroup Save Document Save Functions
**
** Save currently parsed document to the given output sink.  File name
** and string/buffer functions provided for convenience.
** @{
*/

/** Save to named file */
TIDY_EXPORT int         tidySaveFile( TidyDoc tdoc, ctmbstr filename );

/** Save to standard output (FILE*) */
TIDY_EXPORT int         tidySaveStdout( TidyDoc tdoc );

/** Save to given TidyBuffer object */
TIDY_EXPORT int         tidySaveBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Save document to application buffer.  If buffer is not big enough,
**  ENOMEM will be returned and the necessary buffer size will be placed
**  in *buflen.
*/
TIDY_EXPORT int         tidySaveString( TidyDoc tdoc,
                                        tmbstr buffer, uint* buflen );

/** Save to given generic output sink */
TIDY_EXPORT int         tidySaveSink( TidyDoc tdoc, TidyOutputSink* sink );

/** @} end Save group */


/** @addtogroup Basic
** @{
*/
/** Save current settings to named file.
    Only non-default values are written. */
TIDY_EXPORT int         tidyOptSaveFile( TidyDoc tdoc, ctmbstr cfgfil );

/** Save current settings to given output sink.
    Only non-default values are written. */
TIDY_EXPORT int         tidyOptSaveSink( TidyDoc tdoc, TidyOutputSink* sink );


/* Error reporting functions 
*/

/** Write more complete information about errors to current error sink. */
TIDY_EXPORT void        tidyErrorSummary( TidyDoc tdoc );

/** Write more general information about markup to current error sink. */
TIDY_EXPORT void        tidyGeneralInfo( TidyDoc tdoc );

/** @} end Basic group (again) */


/** @defgroup Tree Document Tree
**
** A parsed and, optionally, repaired document is
** represented by Tidy as a Tree, much like a W3C DOM.
** This tree may be traversed using these functions.
** The following snippet gives a basic idea how these
** functions can be used.
**
<pre>
void dumpNode( TidyNode tnod, int indent )
{
  TidyNode child;

  for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
  {
    ctmbstr name = tidyNodeGetName( child );
    if ( !name )
    {
      switch ( tidyNodeGetType(child) )
      {
      case TidyNode_Root:       name = "Root";                    break;
      case TidyNode_DocType:    name = "DOCTYPE";                 break;
      case TidyNode_Comment:    name = "Comment";                 break;
      case TidyNode_ProcIns:    name = "Processing Instruction";  break;
      case TidyNode_Text:       name = "Text";                    break;
      case TidyNode_CDATA:      name = "CDATA";                   break;
      case TidyNode_Section:    name = "XML Section";             break;
      case TidyNode_Asp:        name = "ASP";                     break;
      case TidyNode_Jste:       name = "JSTE";                    break;
      case TidyNode_Php:        name = "PHP";                     break;
      case TidyNode_XmlDecl:    name = "XML Declaration";         break;

      case TidyNode_Start:
      case TidyNode_End:
      case TidyNode_StartEnd:
      default:
        assert( name != NULL ); // Shouldn't get here
        break;
      }
    }
    assert( name != NULL );
    printf( "\%*.*sNode: \%s\\n", indent, indent, tidy );
    dumpNode( child, indent + 4 );
  }
}

void dumpDoc( TidyDoc tdoc )
{
  dumpNode( tidyGetRoot(tdoc), 0 );
}

void dumpBody( TidyDoc tdoc )
{
  dumpNode( tidyGetBody(tdoc), 0 );
}
</pre>

@{

*/

TIDY_EXPORT TidyNode    tidyGetRoot( TidyDoc tdoc );
TIDY_EXPORT TidyNode    tidyGetHtml( TidyDoc tdoc );
TIDY_EXPORT TidyNode    tidyGetHead( TidyDoc tdoc );
TIDY_EXPORT TidyNode    tidyGetBody( TidyDoc tdoc );

/* parent / child */
TIDY_EXPORT TidyNode    tidyGetParent( TidyNode tnod );
TIDY_EXPORT TidyNode    tidyGetChild( TidyNode tnod );

/* siblings */
TIDY_EXPORT TidyNode    tidyGetNext( TidyNode tnod );
TIDY_EXPORT TidyNode    tidyGetPrev( TidyNode tnod );

/* Null for non-element nodes and all pure HTML
TIDY_EXPORT ctmbstr     tidyNodeNsLocal( TidyNode tnod );
TIDY_EXPORT ctmbstr     tidyNodeNsPrefix( TidyNode tnod );
TIDY_EXPORT ctmbstr     tidyNodeNsUri( TidyNode tnod );
*/

/* Iterate over attribute values */
TIDY_EXPORT TidyAttr    tidyAttrFirst( TidyNode tnod );
TIDY_EXPORT TidyAttr    tidyAttrNext( TidyAttr tattr );

TIDY_EXPORT ctmbstr     tidyAttrName( TidyAttr tattr );
TIDY_EXPORT ctmbstr     tidyAttrValue( TidyAttr tattr );

/* Null for pure HTML
TIDY_EXPORT ctmbstr     tidyAttrNsLocal( TidyAttr tattr );
TIDY_EXPORT ctmbstr     tidyAttrNsPrefix( TidyAttr tattr );
TIDY_EXPORT ctmbstr     tidyAttrNsUri( TidyAttr tattr );
*/

/** @} end Tree group */


/** @defgroup NodeAsk Node Interrogation
**
** Get information about any givent node.
** @{
*/

/* Node info */
TIDY_EXPORT TidyNodeType tidyNodeGetType( TidyNode tnod );
TIDY_EXPORT ctmbstr     tidyNodeGetName( TidyNode tnod );

TIDY_EXPORT Bool tidyNodeIsText( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsProp( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsHeader( TidyNode tnod ); /* h1, h2, ... */

TIDY_EXPORT Bool tidyNodeHasText( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool tidyNodeGetText( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf );

TIDY_EXPORT TidyTagId tidyNodeGetId( TidyNode tnod );

TIDY_EXPORT uint tidyNodeLine( TidyNode tnod );
TIDY_EXPORT uint tidyNodeColumn( TidyNode tnod );

TIDY_EXPORT Bool tidyNodeIsHTML( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsHEAD( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTITLE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBASE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsMETA( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBODY( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsFRAMESET( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsFRAME( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsIFRAME( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsNOFRAMES( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsHR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH1( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH2( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsPRE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsLISTING( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsP( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsUL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsOL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsDL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsDIR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsLI( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsDT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsDD( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTABLE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsCAPTION( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTD( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTH( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsCOL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsCOLGROUP( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsA( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsLINK( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsB( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsI( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSTRONG( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsEM( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBIG( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSMALL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsPARAM( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsOPTION( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsOPTGROUP( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsIMG( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsMAP( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsAREA( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsNOBR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsWBR( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsFONT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsLAYER( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSPACER( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsCENTER( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSTYLE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSCRIPT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsNOSCRIPT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsFORM( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsTEXTAREA( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBLOCKQUOTE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsAPPLET( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsOBJECT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsDIV( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSPAN( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsINPUT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsQ( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsLABEL( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH3( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH4( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH5( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsH6( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsADDRESS( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsXMP( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSELECT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBLINK( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsMARQUEE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsEMBED( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsBASEFONT( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsISINDEX( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsS( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsSTRIKE( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsU( TidyNode tnod );
TIDY_EXPORT Bool tidyNodeIsMENU( TidyNode tnod );

/** @} End NodeAsk group */


/** @defgroup Attribute Attribute Interrogation
**
** Get information about any given attribute.
** @{
*/

TIDY_EXPORT TidyAttrId tidyAttrGetId( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsEvent( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsProp( TidyAttr tattr );

TIDY_EXPORT Bool tidyAttrIsHREF( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsSRC( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsID( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsNAME( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsSUMMARY( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsALT( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsLONGDESC( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsUSEMAP( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsISMAP( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsLANGUAGE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsTYPE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsVALUE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsCONTENT( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsTITLE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsXMLNS( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsDATAFLD( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsWIDTH( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsHEIGHT( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsFOR( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsSELECTED( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsCHECKED( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsLANG( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsTARGET( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsHTTP_EQUIV( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsREL( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnMOUSEMOVE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnMOUSEDOWN( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnMOUSEUP( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnCLICK( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnMOUSEOVER( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnMOUSEOUT( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnKEYDOWN( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnKEYUP( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnKEYPRESS( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnFOCUS( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsOnBLUR( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsBGCOLOR( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsLINK( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsALINK( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsVLINK( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsTEXT( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsSTYLE( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsABBR( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsCOLSPAN( TidyAttr tattr );
TIDY_EXPORT Bool tidyAttrIsROWSPAN( TidyAttr tattr );

/** @} end AttrAsk group */


/** @defgroup AttrGet Attribute Retrieval
**
** Lookup an attribute from a given node
** @{
*/


TIDY_EXPORT TidyAttr tidyAttrGetHREF( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetSRC( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetID( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetNAME( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetSUMMARY( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetALT( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetLONGDESC( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetUSEMAP( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetISMAP( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetLANGUAGE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetTYPE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetVALUE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetCONTENT( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetTITLE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetXMLNS( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetDATAFLD( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetWIDTH( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetHEIGHT( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetFOR( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetSELECTED( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetCHECKED( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetLANG( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetTARGET( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetHTTP_EQUIV( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetREL( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnMOUSEMOVE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnMOUSEDOWN( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnMOUSEUP( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnCLICK( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnMOUSEOVER( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnMOUSEOUT( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnKEYDOWN( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnKEYUP( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnKEYPRESS( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnFOCUS( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetOnBLUR( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetBGCOLOR( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetLINK( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetALINK( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetVLINK( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetTEXT( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetSTYLE( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetABBR( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetCOLSPAN( TidyNode tnod );
TIDY_EXPORT TidyAttr tidyAttrGetROWSPAN( TidyNode tnod );


/** @} end AttrGet group */

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* __TIDY_H__ */
