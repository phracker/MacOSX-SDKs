/*
 * dpsops.h
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
#ifndef DPSOPS_H
#define DPSOPS_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void DPSFontDirectory(DPSContext ctxt);

extern void DPSGlobalFontDirectory(DPSContext ctxt);

extern void DPSISOLatin1Encoding(DPSContext ctxt);

extern void DPSSharedFontDirectory(DPSContext ctxt);

extern void DPSStandardEncoding(DPSContext ctxt);

extern void DPSUserObjects(DPSContext ctxt);

extern void DPSabs(DPSContext ctxt);

extern void DPSadd(DPSContext ctxt);

extern void DPSaload(DPSContext ctxt);

extern void DPSanchorsearch(DPSContext ctxt, int *truth);

extern void DPSand(DPSContext ctxt);

extern void DPSarc(DPSContext ctxt, double x, double y, double r, double angle1, double angle2);

extern void DPSarcn(DPSContext ctxt, double x, double y, double r, double angle1, double angle2);

extern void DPSarct(DPSContext ctxt, double x1, double y1, double x2, double y2, double r);

extern void DPSarcto(DPSContext ctxt, double x1, double y1, double x2, double y2, double r, float *xt1, float *yt1, float *xt2, float *yt2);

extern void DPSarray(DPSContext ctxt, int len);

extern void DPSashow(DPSContext ctxt, double x, double y, const char *s);

extern void DPSastore(DPSContext ctxt);

extern void DPSatan(DPSContext ctxt);

extern void DPSawidthshow(DPSContext ctxt, double cx, double cy, int c, double ax, double ay, const char *s);

extern void DPSbanddevice(DPSContext ctxt);

extern void DPSbegin(DPSContext ctxt);

extern void DPSbind(DPSContext ctxt);

extern void DPSbitshift(DPSContext ctxt, int shift);

extern void DPSbytesavailable(DPSContext ctxt, int *n);

extern void DPScachestatus(DPSContext ctxt);

extern void DPSceiling(DPSContext ctxt);

extern void DPScharpath(DPSContext ctxt, const char *s, int b);

extern void DPSclear(DPSContext ctxt);

extern void DPScleardictstack(DPSContext ctxt);

extern void DPScleartomark(DPSContext ctxt);

extern void DPSclientXready(DPSContext ctxt, int i0, int i1, int i2, int i3);

extern void DPSclientsync(DPSContext ctxt);

extern void DPSclip(DPSContext ctxt);

extern void DPSclippath(DPSContext ctxt);

extern void DPSclosefile(DPSContext ctxt);

extern void DPSclosepath(DPSContext ctxt);

extern void DPScolorimage(DPSContext ctxt);

extern void DPSconcat(DPSContext ctxt, const float m[]);

extern void DPSconcatmatrix(DPSContext ctxt);

extern void DPScondition(DPSContext ctxt);

extern void DPScopy(DPSContext ctxt, int n);

extern void DPScopypage(DPSContext ctxt);

extern void DPScos(DPSContext ctxt);

extern void DPScount(DPSContext ctxt, int *n);

extern void DPScountdictstack(DPSContext ctxt, int *n);

extern void DPScountexecstack(DPSContext ctxt, int *n);

extern void DPScounttomark(DPSContext ctxt, int *n);

extern void DPScshow(DPSContext ctxt, const char *s);

extern void DPScurrentXdrawingfunction(DPSContext ctxt, int *function);

extern void DPScurrentXgcdrawable(DPSContext ctxt, int *gc, int *draw, int *x, int *y);

extern void DPScurrentXgcdrawablecolor(DPSContext ctxt, int *gc, int *draw, int *x, int *y, int colorInfo[]);

extern void DPScurrentXoffset(DPSContext ctxt, int *x, int *y);

extern void DPScurrentblackgeneration(DPSContext ctxt);

extern void DPScurrentcacheparams(DPSContext ctxt);

extern void DPScurrentcmykcolor(DPSContext ctxt, float *c, float *m, float *y, float *k);

extern void DPScurrentcolor(DPSContext ctxt);

extern void DPScurrentcolorrendering(DPSContext ctxt);

extern void DPScurrentcolorscreen(DPSContext ctxt);

extern void DPScurrentcolorspace(DPSContext ctxt);

extern void DPScurrentcolortransfer(DPSContext ctxt);

extern void DPScurrentcontext(DPSContext ctxt, int *cid);

extern void DPScurrentdash(DPSContext ctxt);

extern void DPScurrentdevparams(DPSContext ctxt, const char *dev);

extern void DPScurrentdict(DPSContext ctxt);

extern void DPScurrentfile(DPSContext ctxt);

extern void DPScurrentflat(DPSContext ctxt, float *flatness);

extern void DPScurrentfont(DPSContext ctxt);

extern void DPScurrentglobal(DPSContext ctxt, int *b);

extern void DPScurrentgray(DPSContext ctxt, float *gray);

extern void DPScurrentgstate(DPSContext ctxt, int gst);

extern void DPScurrenthalftone(DPSContext ctxt);

extern void DPScurrenthalftonephase(DPSContext ctxt, float *x, float *y);

extern void DPScurrenthsbcolor(DPSContext ctxt, float *h, float *s, float *b);

extern void DPScurrentlinecap(DPSContext ctxt, int *linecap);

extern void DPScurrentlinejoin(DPSContext ctxt, int *linejoin);

extern void DPScurrentlinewidth(DPSContext ctxt, float *width);

extern void DPScurrentmatrix(DPSContext ctxt);

extern void DPScurrentmiterlimit(DPSContext ctxt, float *limit);

extern void DPScurrentobjectformat(DPSContext ctxt, int *code);

extern void DPScurrentoverprint(DPSContext ctxt, int *b);

extern void DPScurrentpacking(DPSContext ctxt, int *b);

extern void DPScurrentpagedevice(DPSContext ctxt);

extern void DPScurrentpoint(DPSContext ctxt, float *x, float *y);

extern void DPScurrentrgbcolor(DPSContext ctxt, float *r, float *g, float *b);

extern void DPScurrentscreen(DPSContext ctxt);

extern void DPScurrentshared(DPSContext ctxt, int *b);

extern void DPScurrentstrokeadjust(DPSContext ctxt, int *b);

extern void DPScurrentsystemparams(DPSContext ctxt);

extern void DPScurrenttransfer(DPSContext ctxt);

extern void DPScurrentundercolorremoval(DPSContext ctxt);

extern void DPScurrentuserparams(DPSContext ctxt);

extern void DPScurveto(DPSContext ctxt, double x1, double y1, double x2, double y2, double x3, double y3);

extern void DPScvi(DPSContext ctxt);

extern void DPScvlit(DPSContext ctxt);

extern void DPScvn(DPSContext ctxt);

extern void DPScvr(DPSContext ctxt);

extern void DPScvrs(DPSContext ctxt);

extern void DPScvs(DPSContext ctxt);

extern void DPScvx(DPSContext ctxt);

extern void DPSdef(DPSContext ctxt);

extern void DPSdefaultmatrix(DPSContext ctxt);

extern void DPSdefinefont(DPSContext ctxt);

extern void DPSdefineresource(DPSContext ctxt, const char *category);

extern void DPSdefineusername(DPSContext ctxt, int i, const char *username);

extern void DPSdefineuserobject(DPSContext ctxt);

extern void DPSdeletefile(DPSContext ctxt, const char *filename);

extern void DPSdetach(DPSContext ctxt);

extern void DPSdeviceinfo(DPSContext ctxt);

extern void DPSdict(DPSContext ctxt, int len);

extern void DPSdictstack(DPSContext ctxt);

extern void DPSdiv(DPSContext ctxt);

extern void DPSdtransform(DPSContext ctxt, double x1, double y1, float *x2, float *y2);

extern void DPSdup(DPSContext ctxt);

extern void DPSecho(DPSContext ctxt, int b);

extern void DPSend(DPSContext ctxt);

extern void DPSeoclip(DPSContext ctxt);

extern void DPSeofill(DPSContext ctxt);

extern void DPSeoviewclip(DPSContext ctxt);

extern void DPSeq(DPSContext ctxt);

extern void DPSequals(DPSContext ctxt);

extern void DPSequalsequals(DPSContext ctxt);

extern void DPSerasepage(DPSContext ctxt);

extern void DPSerrordict(DPSContext ctxt);

extern void DPSexch(DPSContext ctxt);

extern void DPSexec(DPSContext ctxt);

extern void DPSexecform(DPSContext ctxt);

extern void DPSexecstack(DPSContext ctxt);

extern void DPSexecuserobject(DPSContext ctxt, int userObjIndex);

extern void DPSexecuteonly(DPSContext ctxt);

extern void DPSexit(DPSContext ctxt);

extern void DPSexp(DPSContext ctxt);

extern void DPSfalse(DPSContext ctxt);

extern void DPSfile(DPSContext ctxt, const char *name, const char *access);

extern void DPSfilenameforall(DPSContext ctxt);

extern void DPSfileposition(DPSContext ctxt, int *pos);

extern void DPSfill(DPSContext ctxt);

extern void DPSfilter(DPSContext ctxt);

extern void DPSfindencoding(DPSContext ctxt, const char *key);

extern void DPSfindfont(DPSContext ctxt, const char *name);

extern void DPSfindresource(DPSContext ctxt, const char *key, const char *category);

extern void DPSflattenpath(DPSContext ctxt);

extern void DPSfloor(DPSContext ctxt);

extern void DPSflush(DPSContext ctxt);

extern void DPSflushfile(DPSContext ctxt);

extern void DPSfor(DPSContext ctxt);

extern void DPSforall(DPSContext ctxt);

extern void DPSfork(DPSContext ctxt);

extern void DPSframedevice(DPSContext ctxt);

extern void DPSgcheck(DPSContext ctxt, int *b);

extern void DPSge(DPSContext ctxt);

extern void DPSget(DPSContext ctxt);

extern void DPSgetboolean(DPSContext ctxt, int *it);

extern void DPSgetchararray(DPSContext ctxt, int size, char s[]);

extern void DPSgetfloat(DPSContext ctxt, float *it);

extern void DPSgetfloatarray(DPSContext ctxt, int size, float a[]);

extern void DPSgetint(DPSContext ctxt, int *it);

extern void DPSgetintarray(DPSContext ctxt, int size, int a[]);

extern void DPSgetinterval(DPSContext ctxt);

extern void DPSgetstring(DPSContext ctxt, char *s);

extern void DPSglobaldict(DPSContext ctxt);

extern void DPSglyphshow(DPSContext ctxt, const char *name);

extern void DPSgrestore(DPSContext ctxt);

extern void DPSgrestoreall(DPSContext ctxt);

extern void DPSgsave(DPSContext ctxt);

extern void DPSgstate(DPSContext ctxt);

extern void DPSgt(DPSContext ctxt);

extern void DPSidentmatrix(DPSContext ctxt);

extern void DPSidiv(DPSContext ctxt);

extern void DPSidtransform(DPSContext ctxt, double x1, double y1, float *x2, float *y2);

extern void DPSif(DPSContext ctxt);

extern void DPSifelse(DPSContext ctxt);

extern void DPSimage(DPSContext ctxt);

extern void DPSimagemask(DPSContext ctxt);

extern void DPSindex(DPSContext ctxt, int i);

extern void DPSineofill(DPSContext ctxt, double x, double y, int *b);

extern void DPSinfill(DPSContext ctxt, double x, double y, int *b);

extern void DPSinitclip(DPSContext ctxt);

extern void DPSinitgraphics(DPSContext ctxt);

extern void DPSinitmatrix(DPSContext ctxt);

extern void DPSinitviewclip(DPSContext ctxt);

extern void DPSinstroke(DPSContext ctxt, double x, double y, int *b);

extern void DPSinueofill(DPSContext ctxt, double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void DPSinufill(DPSContext ctxt, double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void DPSinustroke(DPSContext ctxt, double x, double y, const char nums[], int n, const char ops[], int l, int *b);

extern void DPSinvertmatrix(DPSContext ctxt);

extern void DPSitransform(DPSContext ctxt, double x1, double y1, float *x2, float *y2);

extern void DPSjoin(DPSContext ctxt);

extern void DPSknown(DPSContext ctxt, int *b);

extern void DPSkshow(DPSContext ctxt, const char *s);

extern void DPSlanguagelevel(DPSContext ctxt, int *n);

extern void DPSle(DPSContext ctxt);

extern void DPSleftbracket(DPSContext ctxt);

extern void DPSleftleft(DPSContext ctxt);

extern void DPSlength(DPSContext ctxt, int *len);

extern void DPSlineto(DPSContext ctxt, double x, double y);

extern void DPSln(DPSContext ctxt);

extern void DPSload(DPSContext ctxt);

extern void DPSlock(DPSContext ctxt);

extern void DPSlog(DPSContext ctxt);

extern void DPSloop(DPSContext ctxt);

extern void DPSlt(DPSContext ctxt);

extern void DPSmakefont(DPSContext ctxt);

extern void DPSmakepattern(DPSContext ctxt);

extern void DPSmark(DPSContext ctxt);

extern void DPSmatrix(DPSContext ctxt);

extern void DPSmaxlength(DPSContext ctxt, int *len);

extern void DPSmod(DPSContext ctxt);

extern void DPSmonitor(DPSContext ctxt);

extern void DPSmoveto(DPSContext ctxt, double x, double y);

extern void DPSmul(DPSContext ctxt);

extern void DPSne(DPSContext ctxt);

extern void DPSneg(DPSContext ctxt);

extern void DPSnewpath(DPSContext ctxt);

extern void DPSnoaccess(DPSContext ctxt);

extern void DPSnot(DPSContext ctxt);

extern void DPSnotify(DPSContext ctxt);

extern void DPSnull(DPSContext ctxt);

extern void DPSnulldevice(DPSContext ctxt);

extern void DPSor(DPSContext ctxt);

extern void DPSpackedarray(DPSContext ctxt);

extern void DPSpathbbox(DPSContext ctxt, float *llx, float *lly, float *urx, float *ury);

extern void DPSpathforall(DPSContext ctxt);

extern void DPSpop(DPSContext ctxt);

extern void DPSprint(DPSContext ctxt);

extern void DPSprintobject(DPSContext ctxt, int tag);

extern void DPSproduct(DPSContext ctxt);

extern void DPSprompt(DPSContext ctxt);

extern void DPSpstack(DPSContext ctxt);

extern void DPSput(DPSContext ctxt);

extern void DPSputinterval(DPSContext ctxt);

extern void DPSquit(DPSContext ctxt);

extern void DPSrand(DPSContext ctxt);

extern void DPSrcheck(DPSContext ctxt, int *b);

extern void DPSrcurveto(DPSContext ctxt, double x1, double y1, double x2, double y2, double x3, double y3);

extern void DPSread(DPSContext ctxt, int *b);

extern void DPSreadhexstring(DPSContext ctxt, int *b);

extern void DPSreadline(DPSContext ctxt, int *b);

extern void DPSreadonly(DPSContext ctxt);

extern void DPSreadstring(DPSContext ctxt, int *b);

extern void DPSrealtime(DPSContext ctxt, int *i);

extern void DPSrectclip(DPSContext ctxt, double x, double y, double w, double h);

extern void DPSrectfill(DPSContext ctxt, double x, double y, double w, double h);

extern void DPSrectstroke(DPSContext ctxt, double x, double y, double w, double h);

extern void DPSrectviewclip(DPSContext ctxt, double x, double y, double w, double h);

extern void DPSrenamefile(DPSContext ctxt, const char *oldname, const char *newname);

extern void DPSrenderbands(DPSContext ctxt);

extern void DPSrepeat(DPSContext ctxt);

extern void DPSresetfile(DPSContext ctxt);

extern void DPSresourceforall(DPSContext ctxt, const char *category);

extern void DPSresourcestatus(DPSContext ctxt, const char *key, const char *category, int *b);

extern void DPSrestore(DPSContext ctxt);

extern void DPSreversepath(DPSContext ctxt);

extern void DPSrevision(DPSContext ctxt, int *n);

extern void DPSrightbracket(DPSContext ctxt);

extern void DPSrightright(DPSContext ctxt);

extern void DPSrlineto(DPSContext ctxt, double x, double y);

extern void DPSrmoveto(DPSContext ctxt, double x, double y);

extern void DPSroll(DPSContext ctxt, int n, int j);

extern void DPSrootfont(DPSContext ctxt);

extern void DPSrotate(DPSContext ctxt, double angle);

extern void DPSround(DPSContext ctxt);

extern void DPSrrand(DPSContext ctxt);

extern void DPSrun(DPSContext ctxt, const char *filename);

extern void DPSsave(DPSContext ctxt);

extern void DPSscale(DPSContext ctxt, double x, double y);

extern void DPSscalefont(DPSContext ctxt, double size);

extern void DPSscheck(DPSContext ctxt, int *b);

extern void DPSsearch(DPSContext ctxt, int *b);

extern void DPSselectfont(DPSContext ctxt, const char *name, double scale);

extern void DPSsendboolean(DPSContext ctxt, int it);

extern void DPSsendchararray(DPSContext ctxt, const char s[], int size);

extern void DPSsendfloat(DPSContext ctxt, double it);

extern void DPSsendfloatarray(DPSContext ctxt, const float a[], int size);

extern void DPSsendint(DPSContext ctxt, int it);

extern void DPSsendintarray(DPSContext ctxt, const int a[], int size);

extern void DPSsendstring(DPSContext ctxt, const char *s);

extern void DPSserialnumber(DPSContext ctxt, int *n);

extern void DPSsetXdrawingfunction(DPSContext ctxt, int function);

extern void DPSsetXgcdrawable(DPSContext ctxt, int gc, int draw, int x, int y);

extern void DPSsetXgcdrawablecolor(DPSContext ctxt, int gc, int draw, int x, int y, const int colorInfo[]);

extern void DPSsetXoffset(DPSContext ctxt, int x, int y);

extern void DPSsetXrgbactual(DPSContext ctxt, double r, double g, double b, int *success);

extern void DPSsetbbox(DPSContext ctxt, double llx, double lly, double urx, double ury);

extern void DPSsetblackgeneration(DPSContext ctxt);

extern void DPSsetcachedevice(DPSContext ctxt, double wx, double wy, double llx, double lly, double urx, double ury);

extern void DPSsetcachelimit(DPSContext ctxt, int n);

extern void DPSsetcacheparams(DPSContext ctxt);

extern void DPSsetcharwidth(DPSContext ctxt, double wx, double wy);

extern void DPSsetcmykcolor(DPSContext ctxt, double c, double m, double y, double k);

extern void DPSsetcolor(DPSContext ctxt);

extern void DPSsetcolorrendering(DPSContext ctxt);

extern void DPSsetcolorscreen(DPSContext ctxt);

extern void DPSsetcolorspace(DPSContext ctxt);

extern void DPSsetcolortransfer(DPSContext ctxt);

extern void DPSsetdash(DPSContext ctxt, const float pat[], int size, double offset);

extern void DPSsetdevparams(DPSContext ctxt);

extern void DPSsetfileposition(DPSContext ctxt, int pos);

extern void DPSsetflat(DPSContext ctxt, double flatness);

extern void DPSsetfont(DPSContext ctxt, int f);

extern void DPSsetglobal(DPSContext ctxt, int b);

extern void DPSsetgray(DPSContext ctxt, double gray);

extern void DPSsetgstate(DPSContext ctxt, int gst);

extern void DPSsethalftone(DPSContext ctxt);

extern void DPSsethalftonephase(DPSContext ctxt, double x, double y);

extern void DPSsethsbcolor(DPSContext ctxt, double h, double s, double b);

extern void DPSsetlinecap(DPSContext ctxt, int linecap);

extern void DPSsetlinejoin(DPSContext ctxt, int linejoin);

extern void DPSsetlinewidth(DPSContext ctxt, double width);

extern void DPSsetmatrix(DPSContext ctxt);

extern void DPSsetmiterlimit(DPSContext ctxt, double limit);

extern void DPSsetobjectformat(DPSContext ctxt, int code);

extern void DPSsetoverprint(DPSContext ctxt, int b);

extern void DPSsetpacking(DPSContext ctxt, int b);

extern void DPSsetpagedevice(DPSContext ctxt);

extern void DPSsetpattern(DPSContext ctxt);

extern void DPSsetrgbcolor(DPSContext ctxt, double r, double g, double b);

extern void DPSsetscreen(DPSContext ctxt);

extern void DPSsetshared(DPSContext ctxt, int b);

extern void DPSsetstrokeadjust(DPSContext ctxt, int b);

extern void DPSsetsystemparams(DPSContext ctxt);

extern void DPSsettransfer(DPSContext ctxt);

extern void DPSsetucacheparams(DPSContext ctxt);

extern void DPSsetundercolorremoval(DPSContext ctxt);

extern void DPSsetuserparams(DPSContext ctxt);

extern void DPSsetvmthreshold(DPSContext ctxt, int i);

extern void DPSshareddict(DPSContext ctxt);

extern void DPSshow(DPSContext ctxt, const char *s);

extern void DPSshowpage(DPSContext ctxt);

extern void DPSsin(DPSContext ctxt);

extern void DPSsqrt(DPSContext ctxt);

extern void DPSsrand(DPSContext ctxt);

extern void DPSstack(DPSContext ctxt);

extern void DPSstart(DPSContext ctxt);

extern void DPSstartjob(DPSContext ctxt, int b, const char *password);

extern void DPSstatus(DPSContext ctxt, int *b);

extern void DPSstatusdict(DPSContext ctxt);

extern void DPSstop(DPSContext ctxt);

extern void DPSstopped(DPSContext ctxt);

extern void DPSstore(DPSContext ctxt);

extern void DPSstring(DPSContext ctxt, int len);

extern void DPSstringwidth(DPSContext ctxt, const char *s, float *xp, float *yp);

extern void DPSstroke(DPSContext ctxt);

extern void DPSstrokepath(DPSContext ctxt);

extern void DPSsub(DPSContext ctxt);

extern void DPSsystemdict(DPSContext ctxt);

extern void DPStoken(DPSContext ctxt, int *b);

extern void DPStransform(DPSContext ctxt, double x1, double y1, float *x2, float *y2);

extern void DPStranslate(DPSContext ctxt, double x, double y);

extern void DPStrue(DPSContext ctxt);

extern void DPStruncate(DPSContext ctxt);

extern void DPStype(DPSContext ctxt);

extern void DPSuappend(DPSContext ctxt, const char nums[], int n, const char ops[], int l);

extern void DPSucache(DPSContext ctxt);

extern void DPSucachestatus(DPSContext ctxt);

extern void DPSueofill(DPSContext ctxt, const char nums[], int n, const char ops[], int l);

extern void DPSufill(DPSContext ctxt, const char nums[], int n, const char ops[], int l);

extern void DPSundef(DPSContext ctxt, const char *name);

extern void DPSundefinefont(DPSContext ctxt, const char *name);

extern void DPSundefineresource(DPSContext ctxt, const char *key, const char *category);

extern void DPSundefineuserobject(DPSContext ctxt, int userObjIndex);

extern void DPSupath(DPSContext ctxt, int b);

extern void DPSuserdict(DPSContext ctxt);

extern void DPSusertime(DPSContext ctxt, int *milliseconds);

extern void DPSustroke(DPSContext ctxt, const char nums[], int n, const char ops[], int l);

extern void DPSustrokepath(DPSContext ctxt, const char nums[], int n, const char ops[], int l);

extern void DPSversion(DPSContext ctxt, int bufsize, char buf[]);

extern void DPSviewclip(DPSContext ctxt);

extern void DPSviewclippath(DPSContext ctxt);

extern void DPSvmreclaim(DPSContext ctxt, int code);

extern void DPSvmstatus(DPSContext ctxt, int *level, int *used, int *maximum);

extern void DPSwait(DPSContext ctxt);

extern void DPSwcheck(DPSContext ctxt, int *b);

extern void DPSwhere(DPSContext ctxt, int *b);

extern void DPSwidthshow(DPSContext ctxt, double x, double y, int c, const char *s);

extern void DPSwrite(DPSContext ctxt);

extern void DPSwritehexstring(DPSContext ctxt);

extern void DPSwriteobject(DPSContext ctxt, int tag);

extern void DPSwritestring(DPSContext ctxt);

extern void DPSwtranslation(DPSContext ctxt, float *x, float *y);

extern void DPSxcheck(DPSContext ctxt, int *b);

extern void DPSxor(DPSContext ctxt);

extern void DPSxshow(DPSContext ctxt, const char *s, const float numarray[], int size);

extern void DPSxyshow(DPSContext ctxt, const char *s, const float numarray[], int size);

extern void DPSyield(DPSContext ctxt);

extern void DPSyshow(DPSContext ctxt, const char *s, const float numarray[], int size);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPSOPS_H */
