/*
     File:       ImageCompression.k.h
 
     Contains:   QuickTime Image Compression Interfaces.
 
     Version:    QuickTime 7.2.1
 
     Copyright:  © 1990-2006 by Apple Inc., all rights reserved
 
     Bugs?:      For bug reports, consult the following page on
                 the World Wide Web:
 
                     http://developer.apple.com/bugreporter/
 
*/
#ifndef __IMAGECOMPRESSION_K__
#define __IMAGECOMPRESSION_K__

#include <QuickTime/ImageCompression.h>
#ifndef __QTUUID__
#define __QTUUID__ 1
#endif  /* !defined(__QTUUID__) */

/*
	Example usage:

		#define GRAPHICSIMPORT_BASENAME()	Fred
		#define GRAPHICSIMPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCompression.k.h>

	To specify that your component implementation does not use globals, do not #define GRAPHICSIMPORT_GLOBALS
*/
#ifdef GRAPHICSIMPORT_BASENAME
	#ifndef GRAPHICSIMPORT_GLOBALS
		#define GRAPHICSIMPORT_GLOBALS() 
		#define ADD_GRAPHICSIMPORT_COMMA 
	#else
		#define ADD_GRAPHICSIMPORT_COMMA ,
	#endif
	#define GRAPHICSIMPORT_GLUE(a,b) a##b
	#define GRAPHICSIMPORT_STRCAT(a,b) GRAPHICSIMPORT_GLUE(a,b)
	#define ADD_GRAPHICSIMPORT_BASENAME(name) GRAPHICSIMPORT_STRCAT(GRAPHICSIMPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDataReference) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle  dataRef, OSType  dataReType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataReference) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle * dataRef, OSType * dataReType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDataFile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const FSSpec * theFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataFile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA FSSpec * theFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDataHandle) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle  h);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataHandle) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle * h);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetImageDescription) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA ImageDescriptionHandle * desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataOffsetAndSize) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long * offset, unsigned long * size);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(ReadData) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * dataPtr, unsigned long  dataOffset, unsigned long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetClip) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA RgnHandle  clipRgn);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetClip) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA RgnHandle * clipRgn);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetSourceRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const Rect * sourceRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetSourceRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Rect * sourceRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetNaturalBounds) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Rect * naturalBounds);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(Draw) (GRAPHICSIMPORT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetGWorld) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CGrafPtr  port, GDHandle  gd);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetGWorld) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CGrafPtr * port, GDHandle * gd);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetMatrix) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const MatrixRecord * matrix);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetMatrix) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA MatrixRecord * matrix);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetBoundsRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const Rect * bounds);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetBoundsRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Rect * bounds);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SaveAsPicture) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const FSSpec * fss, ScriptCode  scriptTag);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetGraphicsMode) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA long  graphicsMode, const RGBColor * opColor);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetGraphicsMode) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA long * graphicsMode, RGBColor * opColor);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetQuality) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CodecQ  quality);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetQuality) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CodecQ * quality);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SaveAsQuickTimeImageFile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const FSSpec * fss, ScriptCode  scriptTag);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDataReferenceOffsetAndLimit) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long  offset, unsigned long  limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataReferenceOffsetAndLimit) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long * offset, unsigned long * limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetAliasedDataReference) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle * dataRef, OSType * dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(Validate) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Boolean * valid);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetMetaData) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * userData);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetMIMETypeList) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * qtAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(DoesDrawAllPixels) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA short * drawsAllPixels);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetAsPicture) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA PicHandle * picture);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(ExportImageFile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA OSType  fileType, OSType  fileCreator, const FSSpec * fss, ScriptCode  scriptTag);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetExportImageTypeList) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * qtAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(DoExportImageFileDialog) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const FSSpec * inDefaultSpec, StringPtr  prompt, ModalFilterYDUPP  filterProc, OSType * outExportedType, FSSpec * outExportedSpec, ScriptCode * outScriptTag);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetExportSettingsAsAtomContainer) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * qtAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetExportSettingsFromAtomContainer) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * qtAtomContainer);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetProgressProc) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA ICMProgressProcRecordPtr  progressProc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetProgressProc) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA ICMProgressProcRecordPtr  progressProc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetImageCount) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long * imageCount);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetImageIndex) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long  imageIndex);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetImageIndex) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA unsigned long * imageIndex);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataOffsetAndSize64) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA wide * offset, wide * size);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(ReadData64) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA void * dataPtr, const wide * dataOffset, unsigned long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDataReferenceOffsetAndLimit64) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const wide * offset, const wide * limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDataReferenceOffsetAndLimit64) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA wide * offset, wide * limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDefaultMatrix) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA MatrixRecord * defaultMatrix);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDefaultClip) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA RgnHandle * defaultRgn);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDefaultGraphicsMode) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA long * defaultGraphicsMode, RGBColor * defaultOpColor);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDefaultSourceRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Rect * defaultSourceRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetColorSyncProfile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle * profile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDestRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA const Rect * destRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDestRect) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Rect * destRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetFlags) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA long  flags);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetFlags) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA long * flags);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetBaseDataOffsetAndSize64) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA wide * offset, wide * size);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetImageIndexToThumbnail) (GRAPHICSIMPORT_GLOBALS());

#if TARGET_API_MAC_OSX
	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(CreateCGImage) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CGImageRef * imageRefOut, UInt32  flags);

#endif  /* TARGET_API_MAC_OSX */

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SaveAsPictureToDataRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SaveAsQuickTimeImageFileToDataRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(ExportImageFileToDataRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA OSType  fileType, OSType  fileCreator, Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(DoExportImageFileToDataRefDialog) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Handle  inDataRef, OSType  inDataRefType, CFStringRef  prompt, ModalFilterYDUPP  filterProc, OSType * outExportedType, Handle * outDataRef, OSType * outDataRefType);

#if TARGET_API_MAC_OSX
	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetOverrideSourceColorSyncProfileRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CMProfileRef  newOverrideSourceProfileRef);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetOverrideSourceColorSyncProfileRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CMProfileRef * outOverrideSourceProfileRef);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetDestinationColorSyncProfileRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CMProfileRef  newDestinationProfileRef);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetDestinationColorSyncProfileRef) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA CMProfileRef * destinationProfileRef);

#endif  /* TARGET_API_MAC_OSX */

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(WillUseColorMatching) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Boolean * outWillMatch);

#if TARGET_API_MAC_OSX
	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetGenericColorSyncProfile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA OSType  pixelFormat, void * reservedSetToNULL, UInt32  flags, Handle * genericColorSyncProfileOut);

#endif  /* TARGET_API_MAC_OSX */

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(SetReturnGenericColorSyncProfile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Boolean  returnGenericProfilesUnlessDontMatchFlagSet);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSIMPORT_BASENAME(GetReturnGenericColorSyncProfile) (GRAPHICSIMPORT_GLOBALS() ADD_GRAPHICSIMPORT_COMMA Boolean * returnGenericProfilesUnlessDontMatchFlagSet);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppGraphicsImportSetDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsImportGetDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsImportSetDataFileProcInfo = 0x000003F0,
		uppGraphicsImportGetDataFileProcInfo = 0x000003F0,
		uppGraphicsImportSetDataHandleProcInfo = 0x000003F0,
		uppGraphicsImportGetDataHandleProcInfo = 0x000003F0,
		uppGraphicsImportGetImageDescriptionProcInfo = 0x000003F0,
		uppGraphicsImportGetDataOffsetAndSizeProcInfo = 0x00000FF0,
		uppGraphicsImportReadDataProcInfo = 0x00003FF0,
		uppGraphicsImportSetClipProcInfo = 0x000003F0,
		uppGraphicsImportGetClipProcInfo = 0x000003F0,
		uppGraphicsImportSetSourceRectProcInfo = 0x000003F0,
		uppGraphicsImportGetSourceRectProcInfo = 0x000003F0,
		uppGraphicsImportGetNaturalBoundsProcInfo = 0x000003F0,
		uppGraphicsImportDrawProcInfo = 0x000000F0,
		uppGraphicsImportSetGWorldProcInfo = 0x00000FF0,
		uppGraphicsImportGetGWorldProcInfo = 0x00000FF0,
		uppGraphicsImportSetMatrixProcInfo = 0x000003F0,
		uppGraphicsImportGetMatrixProcInfo = 0x000003F0,
		uppGraphicsImportSetBoundsRectProcInfo = 0x000003F0,
		uppGraphicsImportGetBoundsRectProcInfo = 0x000003F0,
		uppGraphicsImportSaveAsPictureProcInfo = 0x00000BF0,
		uppGraphicsImportSetGraphicsModeProcInfo = 0x00000FF0,
		uppGraphicsImportGetGraphicsModeProcInfo = 0x00000FF0,
		uppGraphicsImportSetQualityProcInfo = 0x000003F0,
		uppGraphicsImportGetQualityProcInfo = 0x000003F0,
		uppGraphicsImportSaveAsQuickTimeImageFileProcInfo = 0x00000BF0,
		uppGraphicsImportSetDataReferenceOffsetAndLimitProcInfo = 0x00000FF0,
		uppGraphicsImportGetDataReferenceOffsetAndLimitProcInfo = 0x00000FF0,
		uppGraphicsImportGetAliasedDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsImportValidateProcInfo = 0x000003F0,
		uppGraphicsImportGetMetaDataProcInfo = 0x000003F0,
		uppGraphicsImportGetMIMETypeListProcInfo = 0x000003F0,
		uppGraphicsImportDoesDrawAllPixelsProcInfo = 0x000003F0,
		uppGraphicsImportGetAsPictureProcInfo = 0x000003F0,
		uppGraphicsImportExportImageFileProcInfo = 0x0000BFF0,
		uppGraphicsImportGetExportImageTypeListProcInfo = 0x000003F0,
		uppGraphicsImportDoExportImageFileDialogProcInfo = 0x000FFFF0,
		uppGraphicsImportGetExportSettingsAsAtomContainerProcInfo = 0x000003F0,
		uppGraphicsImportSetExportSettingsFromAtomContainerProcInfo = 0x000003F0,
		uppGraphicsImportSetProgressProcProcInfo = 0x000003F0,
		uppGraphicsImportGetProgressProcProcInfo = 0x000003F0,
		uppGraphicsImportGetImageCountProcInfo = 0x000003F0,
		uppGraphicsImportSetImageIndexProcInfo = 0x000003F0,
		uppGraphicsImportGetImageIndexProcInfo = 0x000003F0,
		uppGraphicsImportGetDataOffsetAndSize64ProcInfo = 0x00000FF0,
		uppGraphicsImportReadData64ProcInfo = 0x00003FF0,
		uppGraphicsImportSetDataReferenceOffsetAndLimit64ProcInfo = 0x00000FF0,
		uppGraphicsImportGetDataReferenceOffsetAndLimit64ProcInfo = 0x00000FF0,
		uppGraphicsImportGetDefaultMatrixProcInfo = 0x000003F0,
		uppGraphicsImportGetDefaultClipProcInfo = 0x000003F0,
		uppGraphicsImportGetDefaultGraphicsModeProcInfo = 0x00000FF0,
		uppGraphicsImportGetDefaultSourceRectProcInfo = 0x000003F0,
		uppGraphicsImportGetColorSyncProfileProcInfo = 0x000003F0,
		uppGraphicsImportSetDestRectProcInfo = 0x000003F0,
		uppGraphicsImportGetDestRectProcInfo = 0x000003F0,
		uppGraphicsImportSetFlagsProcInfo = 0x000003F0,
		uppGraphicsImportGetFlagsProcInfo = 0x000003F0,
		uppGraphicsImportGetBaseDataOffsetAndSize64ProcInfo = 0x00000FF0,
		uppGraphicsImportSetImageIndexToThumbnailProcInfo = 0x000000F0,
		uppGraphicsImportCreateCGImageProcInfo = 0x00000FF0,
		uppGraphicsImportSaveAsPictureToDataRefProcInfo = 0x00000FF0,
		uppGraphicsImportSaveAsQuickTimeImageFileToDataRefProcInfo = 0x00000FF0,
		uppGraphicsImportExportImageFileToDataRefProcInfo = 0x0000FFF0,
		uppGraphicsImportDoExportImageFileToDataRefDialogProcInfo = 0x003FFFF0,
		uppGraphicsImportSetOverrideSourceColorSyncProfileRefProcInfo = 0x000003F0,
		uppGraphicsImportGetOverrideSourceColorSyncProfileRefProcInfo = 0x000003F0,
		uppGraphicsImportSetDestinationColorSyncProfileRefProcInfo = 0x000003F0,
		uppGraphicsImportGetDestinationColorSyncProfileRefProcInfo = 0x000003F0,
		uppGraphicsImportWillUseColorMatchingProcInfo = 0x000003F0,
		uppGraphicsImportGetGenericColorSyncProfileProcInfo = 0x0000FFF0,
		uppGraphicsImportSetReturnGenericColorSyncProfileProcInfo = 0x000001F0,
		uppGraphicsImportGetReturnGenericColorSyncProfileProcInfo = 0x000003F0
	};

#endif	/* GRAPHICSIMPORT_BASENAME */

/*
	Example usage:

		#define GRAPHICSEXPORT_BASENAME()	Fred
		#define GRAPHICSEXPORT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCompression.k.h>

	To specify that your component implementation does not use globals, do not #define GRAPHICSEXPORT_GLOBALS
*/
#ifdef GRAPHICSEXPORT_BASENAME
	#ifndef GRAPHICSEXPORT_GLOBALS
		#define GRAPHICSEXPORT_GLOBALS() 
		#define ADD_GRAPHICSEXPORT_COMMA 
	#else
		#define ADD_GRAPHICSEXPORT_COMMA ,
	#endif
	#define GRAPHICSEXPORT_GLUE(a,b) a##b
	#define GRAPHICSEXPORT_STRCAT(a,b) GRAPHICSEXPORT_GLUE(a,b)
	#define ADD_GRAPHICSEXPORT_BASENAME(name) GRAPHICSEXPORT_STRCAT(GRAPHICSEXPORT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(DoExport) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * actualSizeWritten);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(CanTranscode) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * canTranscode);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(DoTranscode) (GRAPHICSEXPORT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(CanUseCompressor) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * canUseCompressor, void * codecSettingsAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(DoUseCompressor) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * codecSettingsAtomContainer, ImageDescriptionHandle * outDesc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(DoStandaloneExport) (GRAPHICSEXPORT_GLOBALS());

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetDefaultFileTypeAndCreator) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA OSType * fileType, OSType * fileCreator);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetDefaultFileNameExtension) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA OSType * fileNameExtension);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetMIMETypeList) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * qtAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(RequestSettings) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA ModalFilterYDUPP  filterProc, void * yourDataProc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetSettingsFromAtomContainer) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * qtAtomContainer);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetSettingsAsAtomContainer) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * qtAtomContainerPtr);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetSettingsAsText) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * theText);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetDontRecompress) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean  dontRecompress);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetDontRecompress) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * dontRecompress);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInterlaceStyle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long  interlaceStyle);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInterlaceStyle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * interlaceStyle);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetMetaData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * userData);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetMetaData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * userData);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetTargetDataSize) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long  targetDataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetTargetDataSize) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * targetDataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetCompressionMethod) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA long  compressionMethod);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetCompressionMethod) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA long * compressionMethod);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetCompressionQuality) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CodecQ  spatialQuality);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetCompressionQuality) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CodecQ * spatialQuality);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetResolution) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Fixed  horizontalResolution, Fixed  verticalResolution);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetResolution) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Fixed * horizontalResolution, Fixed * verticalResolution);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetDepth) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA long  depth);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetDepth) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA long * depth);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetColorSyncProfile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle  colorSyncProfile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetColorSyncProfile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * colorSyncProfile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetProgressProc) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA ICMProgressProcRecordPtr  progressProc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetProgressProc) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA ICMProgressProcRecordPtr  progressProc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputDataReference) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle  dataRef, OSType  dataRefType, ImageDescriptionHandle  desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputDataReference) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * dataRef, OSType * dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputFile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA const FSSpec * theFile, ImageDescriptionHandle  desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputFile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA FSSpec * theFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputHandle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle  h, ImageDescriptionHandle  desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputHandle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * h);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputPtr) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Ptr  p, unsigned long  size, ImageDescriptionHandle  desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputPtr) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Ptr * p, unsigned long * size);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputGraphicsImporter) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA GraphicsImportComponent  grip);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputGraphicsImporter) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA GraphicsImportComponent * grip);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputPicture) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA PicHandle  picture);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputPicture) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA PicHandle * picture);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputGWorld) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA GWorldPtr  gworld);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputGWorld) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA GWorldPtr * gworld);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputPixmap) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA PixMapHandle  pixmap);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputPixmap) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA PixMapHandle * pixmap);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputOffsetAndLimit) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long  offset, unsigned long  limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputOffsetAndLimit) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * offset, unsigned long * limit);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(MayExporterReadInputData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * mayReadInputData);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputDataSize) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * size);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(ReadInputData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * dataPtr, unsigned long  dataOffset, unsigned long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputImageDescription) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA ImageDescriptionHandle * desc);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputImageDimensions) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Rect * dimensions);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputImageDepth) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA long * inputDepth);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(DrawInputImage) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CGrafPtr  gw, GDHandle  gd, const Rect * srcRect, const Rect * dstRect);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputDataReference) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle  dataRef, OSType  dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputDataReference) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * dataRef, OSType * dataRefType);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputFile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA const FSSpec * theFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputFile) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA FSSpec * theFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputHandle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle  h);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputHandle) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Handle * h);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputOffsetAndMaxSize) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long  offset, unsigned long  maxSize, Boolean  truncateFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputOffsetAndMaxSize) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * offset, unsigned long * maxSize, Boolean * truncateFile);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputFileTypeAndCreator) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA OSType  fileType, OSType  fileCreator);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputFileTypeAndCreator) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA OSType * fileType, OSType * fileCreator);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(WriteOutputData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA const void * dataPtr, unsigned long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetOutputMark) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long  mark);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetOutputMark) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA unsigned long * mark);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(ReadOutputData) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA void * dataPtr, unsigned long  dataOffset, unsigned long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetThumbnailEnabled) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean  enableThumbnail, long  maxThumbnailWidth, long  maxThumbnailHeight);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetThumbnailEnabled) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * thumbnailEnabled, long * maxThumbnailWidth, long * maxThumbnailHeight);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetExifEnabled) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean  enableExif);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetExifEnabled) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA Boolean * exifEnabled);

#if TARGET_API_MAC_OSX
	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputCGImage) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CGImageRef  imageRef);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputCGImage) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CGImageRef * imageRefOut);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetInputCGBitmapContext) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CGContextRef  bitmapContextRef);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetInputCGBitmapContext) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA CGContextRef * bitmapContextRefOut);

#endif  /* TARGET_API_MAC_OSX */

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(SetFlags) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA UInt32  flags);

	EXTERN_API( ComponentResult  ) ADD_GRAPHICSEXPORT_BASENAME(GetFlags) (GRAPHICSEXPORT_GLOBALS() ADD_GRAPHICSEXPORT_COMMA UInt32 * flagsOut);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppGraphicsExportDoExportProcInfo = 0x000003F0,
		uppGraphicsExportCanTranscodeProcInfo = 0x000003F0,
		uppGraphicsExportDoTranscodeProcInfo = 0x000000F0,
		uppGraphicsExportCanUseCompressorProcInfo = 0x00000FF0,
		uppGraphicsExportDoUseCompressorProcInfo = 0x00000FF0,
		uppGraphicsExportDoStandaloneExportProcInfo = 0x000000F0,
		uppGraphicsExportGetDefaultFileTypeAndCreatorProcInfo = 0x00000FF0,
		uppGraphicsExportGetDefaultFileNameExtensionProcInfo = 0x000003F0,
		uppGraphicsExportGetMIMETypeListProcInfo = 0x000003F0,
		uppGraphicsExportRequestSettingsProcInfo = 0x00000FF0,
		uppGraphicsExportSetSettingsFromAtomContainerProcInfo = 0x000003F0,
		uppGraphicsExportGetSettingsAsAtomContainerProcInfo = 0x000003F0,
		uppGraphicsExportGetSettingsAsTextProcInfo = 0x000003F0,
		uppGraphicsExportSetDontRecompressProcInfo = 0x000001F0,
		uppGraphicsExportGetDontRecompressProcInfo = 0x000003F0,
		uppGraphicsExportSetInterlaceStyleProcInfo = 0x000003F0,
		uppGraphicsExportGetInterlaceStyleProcInfo = 0x000003F0,
		uppGraphicsExportSetMetaDataProcInfo = 0x000003F0,
		uppGraphicsExportGetMetaDataProcInfo = 0x000003F0,
		uppGraphicsExportSetTargetDataSizeProcInfo = 0x000003F0,
		uppGraphicsExportGetTargetDataSizeProcInfo = 0x000003F0,
		uppGraphicsExportSetCompressionMethodProcInfo = 0x000003F0,
		uppGraphicsExportGetCompressionMethodProcInfo = 0x000003F0,
		uppGraphicsExportSetCompressionQualityProcInfo = 0x000003F0,
		uppGraphicsExportGetCompressionQualityProcInfo = 0x000003F0,
		uppGraphicsExportSetResolutionProcInfo = 0x00000FF0,
		uppGraphicsExportGetResolutionProcInfo = 0x00000FF0,
		uppGraphicsExportSetDepthProcInfo = 0x000003F0,
		uppGraphicsExportGetDepthProcInfo = 0x000003F0,
		uppGraphicsExportSetColorSyncProfileProcInfo = 0x000003F0,
		uppGraphicsExportGetColorSyncProfileProcInfo = 0x000003F0,
		uppGraphicsExportSetProgressProcProcInfo = 0x000003F0,
		uppGraphicsExportGetProgressProcProcInfo = 0x000003F0,
		uppGraphicsExportSetInputDataReferenceProcInfo = 0x00003FF0,
		uppGraphicsExportGetInputDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsExportSetInputFileProcInfo = 0x00000FF0,
		uppGraphicsExportGetInputFileProcInfo = 0x000003F0,
		uppGraphicsExportSetInputHandleProcInfo = 0x00000FF0,
		uppGraphicsExportGetInputHandleProcInfo = 0x000003F0,
		uppGraphicsExportSetInputPtrProcInfo = 0x00003FF0,
		uppGraphicsExportGetInputPtrProcInfo = 0x00000FF0,
		uppGraphicsExportSetInputGraphicsImporterProcInfo = 0x000003F0,
		uppGraphicsExportGetInputGraphicsImporterProcInfo = 0x000003F0,
		uppGraphicsExportSetInputPictureProcInfo = 0x000003F0,
		uppGraphicsExportGetInputPictureProcInfo = 0x000003F0,
		uppGraphicsExportSetInputGWorldProcInfo = 0x000003F0,
		uppGraphicsExportGetInputGWorldProcInfo = 0x000003F0,
		uppGraphicsExportSetInputPixmapProcInfo = 0x000003F0,
		uppGraphicsExportGetInputPixmapProcInfo = 0x000003F0,
		uppGraphicsExportSetInputOffsetAndLimitProcInfo = 0x00000FF0,
		uppGraphicsExportGetInputOffsetAndLimitProcInfo = 0x00000FF0,
		uppGraphicsExportMayExporterReadInputDataProcInfo = 0x000003F0,
		uppGraphicsExportGetInputDataSizeProcInfo = 0x000003F0,
		uppGraphicsExportReadInputDataProcInfo = 0x00003FF0,
		uppGraphicsExportGetInputImageDescriptionProcInfo = 0x000003F0,
		uppGraphicsExportGetInputImageDimensionsProcInfo = 0x000003F0,
		uppGraphicsExportGetInputImageDepthProcInfo = 0x000003F0,
		uppGraphicsExportDrawInputImageProcInfo = 0x0000FFF0,
		uppGraphicsExportSetOutputDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsExportGetOutputDataReferenceProcInfo = 0x00000FF0,
		uppGraphicsExportSetOutputFileProcInfo = 0x000003F0,
		uppGraphicsExportGetOutputFileProcInfo = 0x000003F0,
		uppGraphicsExportSetOutputHandleProcInfo = 0x000003F0,
		uppGraphicsExportGetOutputHandleProcInfo = 0x000003F0,
		uppGraphicsExportSetOutputOffsetAndMaxSizeProcInfo = 0x00001FF0,
		uppGraphicsExportGetOutputOffsetAndMaxSizeProcInfo = 0x00003FF0,
		uppGraphicsExportSetOutputFileTypeAndCreatorProcInfo = 0x00000FF0,
		uppGraphicsExportGetOutputFileTypeAndCreatorProcInfo = 0x00000FF0,
		uppGraphicsExportWriteOutputDataProcInfo = 0x00000FF0,
		uppGraphicsExportSetOutputMarkProcInfo = 0x000003F0,
		uppGraphicsExportGetOutputMarkProcInfo = 0x000003F0,
		uppGraphicsExportReadOutputDataProcInfo = 0x00003FF0,
		uppGraphicsExportSetThumbnailEnabledProcInfo = 0x00003DF0,
		uppGraphicsExportGetThumbnailEnabledProcInfo = 0x00003FF0,
		uppGraphicsExportSetExifEnabledProcInfo = 0x000001F0,
		uppGraphicsExportGetExifEnabledProcInfo = 0x000003F0,
		uppGraphicsExportSetInputCGImageProcInfo = 0x000003F0,
		uppGraphicsExportGetInputCGImageProcInfo = 0x000003F0,
		uppGraphicsExportSetInputCGBitmapContextProcInfo = 0x000003F0,
		uppGraphicsExportGetInputCGBitmapContextProcInfo = 0x000003F0,
		uppGraphicsExportSetFlagsProcInfo = 0x000003F0,
		uppGraphicsExportGetFlagsProcInfo = 0x000003F0
	};

#endif	/* GRAPHICSEXPORT_BASENAME */

/*
	Example usage:

		#define IMAGETRANSCODER_BASENAME()	Fred
		#define IMAGETRANSCODER_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCompression.k.h>

	To specify that your component implementation does not use globals, do not #define IMAGETRANSCODER_GLOBALS
*/
#ifdef IMAGETRANSCODER_BASENAME
	#ifndef IMAGETRANSCODER_GLOBALS
		#define IMAGETRANSCODER_GLOBALS() 
		#define ADD_IMAGETRANSCODER_COMMA 
	#else
		#define ADD_IMAGETRANSCODER_COMMA ,
	#endif
	#define IMAGETRANSCODER_GLUE(a,b) a##b
	#define IMAGETRANSCODER_STRCAT(a,b) IMAGETRANSCODER_GLUE(a,b)
	#define ADD_IMAGETRANSCODER_BASENAME(name) IMAGETRANSCODER_STRCAT(IMAGETRANSCODER_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_IMAGETRANSCODER_BASENAME(BeginSequence) (IMAGETRANSCODER_GLOBALS() ADD_IMAGETRANSCODER_COMMA ImageDescriptionHandle  srcDesc, ImageDescriptionHandle * dstDesc, void * data, long  dataSize);

	EXTERN_API( ComponentResult  ) ADD_IMAGETRANSCODER_BASENAME(Convert) (IMAGETRANSCODER_GLOBALS() ADD_IMAGETRANSCODER_COMMA void * srcData, long  srcDataSize, void ** dstData, long * dstDataSize);

	EXTERN_API( ComponentResult  ) ADD_IMAGETRANSCODER_BASENAME(DisposeData) (IMAGETRANSCODER_GLOBALS() ADD_IMAGETRANSCODER_COMMA void * dstData);

	EXTERN_API( ComponentResult  ) ADD_IMAGETRANSCODER_BASENAME(EndSequence) (IMAGETRANSCODER_GLOBALS());


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppImageTranscoderBeginSequenceProcInfo = 0x0000FFF0,
		uppImageTranscoderConvertProcInfo = 0x0000FFF0,
		uppImageTranscoderDisposeDataProcInfo = 0x000003F0,
		uppImageTranscoderEndSequenceProcInfo = 0x000000F0
	};

#endif	/* IMAGETRANSCODER_BASENAME */

/*
	Example usage:

		#define QT_BASENAME()	Fred
		#define QT_GLOBALS()	FredGlobalsHandle
		#include <QuickTime/ImageCompression.k.h>

	To specify that your component implementation does not use globals, do not #define QT_GLOBALS
*/
#ifdef QT_BASENAME
	#ifndef QT_GLOBALS
		#define QT_GLOBALS() 
		#define ADD_QT_COMMA 
	#else
		#define ADD_QT_COMMA ,
	#endif
	#define QT_GLUE(a,b) a##b
	#define QT_STRCAT(a,b) QT_GLUE(a,b)
	#define ADD_QT_BASENAME(name) QT_STRCAT(QT_BASENAME(),name)

	EXTERN_API( ComponentResult  ) ADD_QT_BASENAME(GetComponentPropertyInfo) (QT_GLOBALS() ADD_QT_COMMA ComponentPropertyClass  inPropClass, ComponentPropertyID  inPropID, ComponentValueType * outPropType, ByteCount * outPropValueSize, UInt32 * outPropertyFlags);

	EXTERN_API( ComponentResult  ) ADD_QT_BASENAME(GetComponentProperty) (QT_GLOBALS() ADD_QT_COMMA ComponentPropertyClass  inPropClass, ComponentPropertyID  inPropID, ByteCount  inPropValueSize, ComponentValuePtr  outPropValueAddress, ByteCount * outPropValueSizeUsed);

	EXTERN_API( ComponentResult  ) ADD_QT_BASENAME(SetComponentProperty) (QT_GLOBALS() ADD_QT_COMMA ComponentPropertyClass  inPropClass, ComponentPropertyID  inPropID, ByteCount  inPropValueSize, ConstComponentValuePtr  inPropValueAddress);

	EXTERN_API( ComponentResult  ) ADD_QT_BASENAME(AddComponentPropertyListener) (QT_GLOBALS() ADD_QT_COMMA ComponentPropertyClass  inPropClass, ComponentPropertyID  inPropID, QTComponentPropertyListenerUPP  inDispatchProc, void * inUserData);

	EXTERN_API( ComponentResult  ) ADD_QT_BASENAME(RemoveComponentPropertyListener) (QT_GLOBALS() ADD_QT_COMMA ComponentPropertyClass  inPropClass, ComponentPropertyID  inPropID, QTComponentPropertyListenerUPP  inDispatchProc, void * inUserData);


	/* MixedMode ProcInfo constants for component calls */
	enum {
		uppQTGetComponentPropertyInfoProcInfo = 0x0003FFF0,
		uppQTGetComponentPropertyProcInfo = 0x0003FFF0,
		uppQTSetComponentPropertyProcInfo = 0x0000FFF0,
		uppQTAddComponentPropertyListenerProcInfo = 0x0000FFF0,
		uppQTRemoveComponentPropertyListenerProcInfo = 0x0000FFF0
	};

#endif	/* QT_BASENAME */

#define kQTComponentPropertyListenerCollectionContextVersion 1

#endif /* __IMAGECOMPRESSION_K__ */

