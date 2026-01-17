/*
 * psops.h
 */
/*
 * (c) Copyright 1988-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */
#ifndef PSOPS_H
#define PSOPS_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void PSFontDirectory( void );

extern void PSGlobalFontDirectory( void );

extern void PSISOLatin1Encoding( void );

extern void PSSharedFontDirectory( void );

extern void PSStandardEncoding( void );

extern void PSUserObjects( void );

extern void PSabs( void );

extern void PSadd( void );

extern void PSaload( void );

extern void PSanchorsearch(int *truth);

extern void PSand( void );

extern void PSarc(double x, double y, double r, double angle1, double angle2);

extern void PSarcn(double x, double y, double r, double angle1, double angle2);

extern void PSarct(double x1, double y1, double x2, double y2, double r);

extern void PSarcto(double x1, double y1, double x2, double y2, double r, float *xt1, float *yt1, float *xt2, float *yt2);

extern void PSarray(int len);

extern void PSashow(double x, double y, const char *s);

extern void PSastore( void );

extern void PSatan( void );

extern void PSawidthshow(double cx, double cy, int c, double ax, double ay, const char *s);

extern void PSbanddevice( void );

extern void PSbegin( void );

extern void PSbind( void );

extern void PSbitshift(int shift);

extern void PSbytesavailable(int *n);

extern void PScachestatus( void );

extern void PSceiling( void );

extern void PScharpath(const char *s, int b);

extern void PSclear( void );

extern void PScleardictstack( void );

extern void PScleartomark( void );

extern void PSclientXready(int i0, int i1, int i2, int i3);

extern void PSclientsync( void );

extern void PSclip( void );

extern void PSclippath( void );

extern void PSclosefile( void );

extern void PSclosepath( void );

extern void PScolorimage( void );

extern void PSconcat(const float m[]);

extern void PSconcatmatrix( void );

extern void PScondition( void );

extern void PScopy(int n);

extern void PScopypage( void );

extern void PScos( void );

extern void PScount(int *n);

extern void PScountdictstack(int *n);

extern void PScountexecstack(int *n);

extern void PScounttomark(int *n);

extern void PScshow(const char *s);

extern void PScurrentXdrawingfunction(int *function);

extern void PScurrentXgcdrawable(int *gc, int *draw, int *x, int *y);

extern void PScurrentXgcdrawablecolor(int *gc, int *draw, int *x, int *y, int colorInfo[]);

extern void PScurrentXoffset(int *x, int *y);

extern void PScurrentblackgeneration( void );

extern void PScurrentcacheparams( void );

extern void PScurrentcmykcolor(float *c, float *m, float *y, float *k);

extern void PScurrentcolor( void );

extern void PScurrentcolorrendering( void );

extern void PScurrentcolorscreen( void );

extern void PScurrentcolorspace( void );

extern void PScurrentcolortransfer( void );

extern void PScurrentcontext(int *cid);

extern void PScurrentdash( void );

extern void PScurrentdevparams(const char *dev);

extern void PScurrentdict( void );

extern void PScurrentfile( void );

extern void PScurrentflat(float *flatness);

extern void PScurrentfont( void );

extern void PScurrentglobal(int *b);

extern void PScurrentgray(float *gray);

extern void PScurrentgstate(int gst);

extern void PScurrenthalftone( void );

extern void PScurrenthalftonephase(float *x, float *y);

extern void PScurrenthsbcolor(float *h, float *s, float *b);

extern void PScurrentlinecap(int *linecap);

extern void PScurrentlinejoin(int *linejoin);

extern void PScurrentlinewidth(float *width);

extern void PScurrentmatrix( void );

extern void PScurrentmiterlimit(float *limit);

extern void PScurrentobjectformat(int *code);

extern void PScurrentoverprint(int *b);

extern void PScurrentpacking(int *b);

extern void PScurrentpagedevice( void );

extern void PScurrentpoint(float *x, float *y);

extern void PScurrentrgbcolor(float *r, float *g, float *b);

extern void PScurrentscreen( void );

extern void PScurrentshared(int *b);

extern void PScurrentstrokeadjust(int *b);

extern void PScurrentsystemparams( void );

extern void PScurrenttransfer( void );

extern void PScurrentundercolorremoval( void );

extern void PScurrentuserparams( void );

extern void PScurveto(double x1, double y1, double x2, double y2, double x3, double y3);

extern void PScvi( void );

extern void PScvlit( void );

extern void PScvn( void );

extern void PScvr( void );

extern void PScvrs( void );

extern void PScvs( void );

extern void PScvx( void );

extern void PSdef( void );

extern void PSdefaultmatrix( void );

extern void PSdefinefont( void );

extern void PSdefineresource(const char *category);

extern void PSdefineusername(int i, const char *username);

extern void PSdefineuserobject( void );

extern void PSdeletefile(const char *filename);

extern void PSdetach( void );

extern void PSdeviceinfo( void );

extern void PSdict(int len);

extern void PSdictstack( void );

extern void PSdiv( void );

extern void PSdtransform(double x1, double y1, float *x2, float *y2);

extern void PSdup( void );

extern void PSecho(int b);

extern void PSend( void );

extern void PSeoclip( void );

extern void PSeofill( void );

extern void PSeoviewclip( void );

extern void PSeq( void );

extern void PSequals( void );

extern void PSequalsequals( void );

extern void PSerasepage( void );

extern void PSerrordict( void );

extern void PSexch( void );

extern void PSexec( void );

extern void PSexecform( void );

extern void PSexecstack( void );

extern void PSexecuserobject(int userObjIndex);

extern void PSexecuteonly( void );

extern void PSexit( void );

extern void PSexp( void );

extern void PSfalse( void );

extern void PSfile(const char *name, const char *access);

extern void PSfilenameforall( void );

extern void PSfileposition(int *pos);

extern void PSfill( void );

extern void PSfilter( void );

extern void PSfindencoding(const char *key);

extern void PSfindfont(const char *name);

extern void PSfindresource(const char *key, const char *category);

extern void PSflattenpath( void );

extern void PSfloor( void );

extern void PSflush( void );

extern void PSflushfile( void );

extern void PSfor( void );

extern void PSforall( void );

extern void PSfork( void );

extern void PSframedevice( void );

extern void PSgcheck(int *b);

extern void PSge( void );

extern void PSget( void );

extern void PSgetboolean(int *it);

extern void PSgetchararray(int size, char s[]);

extern void PSgetfloat(float *it);

extern void PSgetfloatarray(int size, float a[]);

extern void PSgetint(int *it);

extern void PSgetintarray(int size, int a[]);

extern void PSgetinterval( void );

extern void PSgetstring(char *s);

extern void PSglobaldict( void );

extern void PSglyphshow(const char *name);

extern void PSgrestore( void );

extern void PSgrestoreall( void );

extern void PSgsave( void );

extern void PSgstate( void );

extern void PSgt( void );

extern void PSidentmatrix( void );

extern void PSidiv( void );

extern void PSidtransform(double x1, double y1, float *x2, float *y2);

extern void PSif( void );

extern void PSifelse( void );

extern void PSimage( void );

extern void PSimagemask( void );

extern void PSindex(int i);

extern void PSineofill(double x, double y, int *b);

extern void PSinfill(double x, double y, int *b);

extern void PSinitclip( void );

extern void PSinitgraphics( void );

extern void PSinitmatrix( void );

extern void PSinitviewclip( void );

extern void PSinstroke(double x, double y, int *b);

extern void PSinueofill(double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void PSinufill(double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void PSinustroke(double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void PSinvertmatrix( void );

extern void PSitransform(double x1, double y1, float *x2, float *y2);

extern void PSjoin( void );

extern void PSknown(int *b);

extern void PSkshow(const char *s);

extern void PSlanguagelevel(int *n);

extern void PSle( void );

extern void PSleftbracket( void );

extern void PSleftleft( void );

extern void PSlength(int *len);

extern void PSlineto(double x, double y);

extern void PSln( void );

extern void PSload( void );

extern void PSlock( void );

extern void PSlog( void );

extern void PSloop( void );

extern void PSlt( void );

extern void PSmakefont( void );

extern void PSmakepattern( void );

extern void PSmark( void );

extern void PSmatrix( void );

extern void PSmaxlength(int *len);

extern void PSmod( void );

extern void PSmonitor( void );

extern void PSmoveto(double x, double y);

extern void PSmul( void );

extern void PSne( void );

extern void PSneg( void );

extern void PSnewpath( void );

extern void PSnoaccess( void );

extern void PSnot( void );

extern void PSnotify( void );

extern void PSnull( void );

extern void PSnulldevice( void );

extern void PSor( void );

extern void PSpackedarray( void );

extern void PSpathbbox(float *llx, float *lly, float *urx, float *ury);

extern void PSpathforall( void );

extern void PSpop( void );

extern void PSprint( void );

extern void PSprintobject(int tag);

extern void PSproduct( void );

extern void PSprompt( void );

extern void PSpstack( void );

extern void PSput( void );

extern void PSputinterval( void );

extern void PSquit( void );

extern void PSrand( void );

extern void PSrcheck(int *b);

extern void PSrcurveto(double x1, double y1, double x2, double y2, double x3, double y3);

extern void PSread(int *b);

extern void PSreadhexstring(int *b);

extern void PSreadline(int *b);

extern void PSreadonly( void );

extern void PSreadstring(int *b);

extern void PSrealtime(int *i);

extern void PSrectclip(double x, double y, double w, double h);

extern void PSrectfill(double x, double y, double w, double h);

extern void PSrectstroke(double x, double y, double w, double h);

extern void PSrectviewclip(double x, double y, double w, double h);

extern void PSrenamefile(const char *oldname, const char *newname);

extern void PSrenderbands( void );

extern void PSrepeat( void );

extern void PSresetfile( void );

extern void PSresourceforall(const char *category);

extern void PSresourcestatus(const char *key, const char *category, int *b);

extern void PSrestore( void );

extern void PSreversepath( void );

extern void PSrevision(int *n);

extern void PSrightbracket( void );

extern void PSrightright( void );

extern void PSrlineto(double x, double y);

extern void PSrmoveto(double x, double y);

extern void PSroll(int n, int j);

extern void PSrootfont( void );

extern void PSrotate(double angle);

extern void PSround( void );

extern void PSrrand( void );

extern void PSrun(const char *filename);

extern void PSsave( void );

extern void PSscale(double x, double y);

extern void PSscalefont(double size);

extern void PSscheck(int *b);

extern void PSsearch(int *b);

extern void PSselectfont(const char *name, double scale);

extern void PSsendboolean(int it);

extern void PSsendchararray(const char s[], int size);

extern void PSsendfloat(double it);

extern void PSsendfloatarray(const float a[], int size);

extern void PSsendint(int it);

extern void PSsendintarray(const int a[], int size);

extern void PSsendstring(const char *s);

extern void PSserialnumber(int *n);

extern void PSsetXdrawingfunction(int function);

extern void PSsetXgcdrawable(int gc, int draw, int x, int y);

extern void PSsetXgcdrawablecolor(int gc, int draw, int x, int y, const int colorInfo[]);

extern void PSsetXoffset(int x, int y);

extern void PSsetXrgbactual(double r, double g, double b, int *success);

extern void PSsetbbox(double llx, double lly, double urx, double ury);

extern void PSsetblackgeneration( void );

extern void PSsetcachedevice(double wx, double wy, double llx, double lly, double urx, double ury);

extern void PSsetcachelimit(int n);

extern void PSsetcacheparams( void );

extern void PSsetcharwidth(double wx, double wy);

extern void PSsetcmykcolor(double c, double m, double y, double k);

extern void PSsetcolor( void );

extern void PSsetcolorrendering( void );

extern void PSsetcolorscreen( void );

extern void PSsetcolorspace( void );

extern void PSsetcolortransfer( void );

extern void PSsetdash(const float pat[], int size, double offset);

extern void PSsetdevparams( void );

extern void PSsetfileposition(int pos);

extern void PSsetflat(double flatness);

extern void PSsetfont(int f);

extern void PSsetglobal(int b);

extern void PSsetgray(double gray);

extern void PSsetgstate(int gst);

extern void PSsethalftone( void );

extern void PSsethalftonephase(double x, double y);

extern void PSsethsbcolor(double h, double s, double b);

extern void PSsetlinecap(int linecap);

extern void PSsetlinejoin(int linejoin);

extern void PSsetlinewidth(double width);

extern void PSsetmatrix( void );

extern void PSsetmiterlimit(double limit);

extern void PSsetobjectformat(int code);

extern void PSsetoverprint(int b);

extern void PSsetpacking(int b);

extern void PSsetpagedevice( void );

extern void PSsetpattern( void );

extern void PSsetrgbcolor(double r, double g, double b);

extern void PSsetscreen( void );

extern void PSsetshared(int b);

extern void PSsetstrokeadjust(int b);

extern void PSsetsystemparams( void );

extern void PSsettransfer( void );

extern void PSsetucacheparams( void );

extern void PSsetundercolorremoval( void );

extern void PSsetuserparams( void );

extern void PSsetvmthreshold(int i);

extern void PSshareddict( void );

extern void PSshow(const char *s);

extern void PSshowpage( void );

extern void PSsin( void );

extern void PSsqrt( void );

extern void PSsrand( void );

extern void PSstack( void );

extern void PSstart( void );

extern void PSstartjob(int b, const char *password);

extern void PSstatus(int *b);

extern void PSstatusdict( void );

extern void PSstop( void );

extern void PSstopped( void );

extern void PSstore( void );

extern void PSstring(int len);

extern void PSstringwidth(const char *s, float *xp, float *yp);

extern void PSstroke( void );

extern void PSstrokepath( void );

extern void PSsub( void );

extern void PSsystemdict( void );

extern void PStoken(int *b);

extern void PStransform(double x1, double y1, float *x2, float *y2);

extern void PStranslate(double x, double y);

extern void PStrue( void );

extern void PStruncate( void );

extern void PStype( void );

extern void PSuappend(const char nums[], int n, const char ops[], int l);

extern void PSucache( void );

extern void PSucachestatus( void );

extern void PSueofill(const char nums[], int n, const char ops[], int l);

extern void PSufill(const char nums[], int n, const char ops[], int l);

extern void PSundef(const char *name);

extern void PSundefinefont(const char *name);

extern void PSundefineresource(const char *key, const char *category);

extern void PSundefineuserobject(int userObjIndex);

extern void PSupath(int b);

extern void PSuserdict( void );

extern void PSusertime(int *milliseconds);

extern void PSustroke(const char nums[], int n, const char ops[], int l);

extern void PSustrokepath(const char nums[], int n, const char ops[], int l);

extern void PSversion(int bufsize, char buf[]);

extern void PSviewclip( void );

extern void PSviewclippath( void );

extern void PSvmreclaim(int code);

extern void PSvmstatus(int *level, int *used, int *maximum);

extern void PSwait( void );

extern void PSwcheck(int *b);

extern void PSwhere(int *b);

extern void PSwidthshow(double x, double y, int c, const char *s);

extern void PSwrite( void );

extern void PSwritehexstring( void );

extern void PSwriteobject(int tag);

extern void PSwritestring( void );

extern void PSwtranslation(float *x, float *y);

extern void PSxcheck(int *b);

extern void PSxor( void );

extern void PSxshow(const char *s, const float numarray[], int size);

extern void PSxyshow(const char *s, const float numarray[], int size);

extern void PSyield( void );

extern void PSyshow(const char *s, const float numarray[], int size);


#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* PSOPS_H */
