/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */

/*
 * Find out about remote users
 */

#ifndef RPC_HDR
%#ifndef lint
%/*static char sccsid[] = "from: @(#)rnusers.x 1.2 87/09/20 Copyr 1987 Sun Micro";*/
/* @(#)rusers.x 1.1 91/12/01 Copyright 1991 Sun Microsystems, Inc. */
%static char rcsid[] = "$Id: rusers.x,v 1.2 2000/03/05 02:04:45 wsanchez Exp $";
%#endif /* not lint */
#endif

%/*
% * Find out about remote users
% */

const RUSERS_MAXUSERLEN = 32;
const RUSERS_MAXLINELEN = 32;
const RUSERS_MAXHOSTLEN = 257;

struct rusers_utmp {
	string ut_user<RUSERS_MAXUSERLEN>;	/* aka ut_name */
	string ut_line<RUSERS_MAXLINELEN>;	/* device */
	string ut_host<RUSERS_MAXHOSTLEN>;	/* host user logged on from */
	int ut_type;				/* type of entry */
	int ut_time;				/* time entry was made */
	unsigned int ut_idle;			/* minutes idle */
};

typedef rusers_utmp utmp_array<>;

#ifdef RPC_HDR
%
%/*
% * Values for ut_type field above.
% */
#endif
const	RUSERS_EMPTY = 0;
const	RUSERS_RUN_LVL = 1;
const	RUSERS_BOOT_TIME = 2;
const	RUSERS_OLD_TIME = 3;
const	RUSERS_NEW_TIME = 4;
const	RUSERS_INIT_PROCESS = 5;
const	RUSERS_LOGIN_PROCESS = 6;
const	RUSERS_USER_PROCESS = 7;
const	RUSERS_DEAD_PROCESS = 8;
const	RUSERS_ACCOUNTING = 9;

program RUSERSPROG {

	version RUSERSVERS_3 {
		int
		RUSERSPROC_NUM(void) = 1;

		utmp_array
		RUSERSPROC_NAMES(void) = 2;

		utmp_array
		RUSERSPROC_ALLNAMES(void) = 3;
	} = 3;

} = 100002;
