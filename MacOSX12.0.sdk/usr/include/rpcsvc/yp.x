/* @(#)yp.x	2.1 88/08/01 4.0 RPCSRC */

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
 * Protocol description file for the Yellow Pages Service
 */

#ifndef RPC_HDR
%#include <sys/cdefs.h>
%__RCSID("$FreeBSD: src/include/rpcsvc/yp.x,v 1.13 2003/05/04 02:51:42 obrien Exp $");
#endif

const YPMAXRECORD = 1024;
const YPMAXDOMAIN = 64;
const YPMAXMAP = 64;
const YPMAXPEER = 64;


enum ypstat {
	YP_TRUE		=  1,
	YP_NOMORE	=  2,
	YP_FALSE	=  0,
	YP_NOMAP	= -1,
	YP_NODOM	= -2,
	YP_NOKEY	= -3,
	YP_BADOP	= -4,
	YP_BADDB	= -5,
	YP_YPERR	= -6,
	YP_BADARGS	= -7,
	YP_VERS		= -8
};


enum ypxfrstat {
	YPXFR_SUCC	=  1,
	YPXFR_AGE	=  2,
	YPXFR_NOMAP	= -1,
	YPXFR_NODOM	= -2,
	YPXFR_RSRC	= -3,
	YPXFR_RPC	= -4,
	YPXFR_MADDR	= -5,
	YPXFR_YPERR	= -6,
	YPXFR_BADARGS	= -7,
	YPXFR_DBM	= -8,
	YPXFR_FILE	= -9,
	YPXFR_SKEW	= -10,
	YPXFR_CLEAR	= -11,
	YPXFR_FORCE	= -12,
	YPXFR_XFRERR	= -13,
	YPXFR_REFUSED	= -14
};


typedef string domainname<YPMAXDOMAIN>;
typedef string mapname<YPMAXMAP>;
typedef string peername<YPMAXPEER>;
typedef opaque keydat<YPMAXRECORD>;
typedef opaque valdat<YPMAXRECORD>;


struct ypmap_parms {
	domainname domain;	
	mapname map;
	unsigned int ordernum;
	peername peer;
};

struct ypreq_key {
	domainname domain;
	mapname map;
	keydat key;
};

struct ypreq_nokey {
	domainname domain;	
	mapname map;
};
	
struct ypreq_xfr {
	ypmap_parms map_parms;
	unsigned int transid;
	unsigned int prog;
	unsigned int port;
};


struct ypresp_val {
	ypstat stat;
	valdat val;
};

struct ypresp_key_val {
	ypstat stat;
#if 1 /* These are backwards */
	keydat key;
	valdat val;
#else
	valdat val;
	keydat key;
#endif
};


struct ypresp_master {
	ypstat stat;	
	peername peer;
};

struct ypresp_order {
	ypstat stat;
	unsigned int ordernum;
};

union ypresp_all switch (bool more) {
case TRUE:
	ypresp_key_val val;
case FALSE:
	void;
};

struct ypresp_xfr {
	unsigned int transid;
	ypxfrstat xfrstat;
};

struct ypmaplist {
	mapname map;
	ypmaplist *next;
};

struct ypresp_maplist {
	ypstat stat;
	ypmaplist *maps;
};

enum yppush_status {
	YPPUSH_SUCC	=  1,	/* Success */
	YPPUSH_AGE 	=  2,	/* Master's version not newer */
	YPPUSH_NOMAP	= -1,	/* Can't find server for map */
	YPPUSH_NODOM	= -2,	/* Domain not supported */
	YPPUSH_RSRC	= -3,	/* Local resource alloc failure */
	YPPUSH_RPC	= -4,	/* RPC failure talking to server */
	YPPUSH_MADDR 	= -5,	/* Can't get master address */
	YPPUSH_YPERR	= -6,	/* YP server/map db error */
	YPPUSH_BADARGS	= -7,	/* Request arguments bad */
	YPPUSH_DBM	= -8,	/* Local dbm operation failed */
	YPPUSH_FILE	= -9,	/* Local file I/O operation failed */
	YPPUSH_SKEW	= -10,	/* Map version skew during transfer */
	YPPUSH_CLEAR	= -11,	/* Can't send "Clear" req to local ypserv */
	YPPUSH_FORCE	= -12,	/* No local order number in map  use -f flag. */
	YPPUSH_XFRERR 	= -13,	/* ypxfr error */
	YPPUSH_REFUSED	= -14 	/* Transfer request refused by ypserv */
};

struct yppushresp_xfr {
	unsigned transid;
	yppush_status status;
};

/*
 * Response structure and overall result status codes.  Success and failure
 * represent two separate response message types.
 */
 
enum ypbind_resptype {
	YPBIND_SUCC_VAL = 1, 
	YPBIND_FAIL_VAL = 2
};
 
struct ypbind_binding {
    opaque ypbind_binding_addr[4]; /* In network order */
    opaque ypbind_binding_port[2]; /* In network order */
};   

union ypbind_resp switch (ypbind_resptype ypbind_status) {
case YPBIND_FAIL_VAL:
        unsigned ypbind_error;
case YPBIND_SUCC_VAL:
        ypbind_binding ypbind_bindinfo;
};     

/* Detailed failure reason codes for response field ypbind_error*/
 
const YPBIND_ERR_ERR    = 1;	/* Internal error */
const YPBIND_ERR_NOSERV = 2;	/* No bound server for passed domain */
const YPBIND_ERR_RESC   = 3;	/* System resource allocation failure */
 
 
/*
 * Request data structure for ypbind "Set domain" procedure.
 */
struct ypbind_setdom {
	domainname ypsetdom_domain;
	ypbind_binding ypsetdom_binding;
	unsigned ypsetdom_vers;
};


/*
 * NIS v1 support for backwards compatibility
 */
enum ypreqtype {
	YPREQ_KEY = 1,
	YPREQ_NOKEY = 2,
	YPREQ_MAP_PARMS = 3
};

enum ypresptype {
	YPRESP_VAL = 1,
	YPRESP_KEY_VAL = 2,
	YPRESP_MAP_PARMS = 3
};

union yprequest switch (ypreqtype yp_reqtype) {
case YPREQ_KEY:
	ypreq_key yp_req_keytype;
case YPREQ_NOKEY:
	ypreq_nokey yp_req_nokeytype;
case YPREQ_MAP_PARMS:
	ypmap_parms yp_req_map_parmstype;
};

union ypresponse switch (ypresptype yp_resptype) {
case YPRESP_VAL:
	ypresp_val yp_resp_valtype;
case YPRESP_KEY_VAL:
	ypresp_key_val yp_resp_key_valtype;
case YPRESP_MAP_PARMS:
	ypmap_parms yp_resp_map_parmstype;
};

#if !defined(YPBIND_ONLY) && !defined(YPPUSH_ONLY)
/*
 * YP access protocol
 */
program YPPROG {
/*
 * NIS v1 support for backwards compatibility
 */
	version YPOLDVERS {
		void
		YPOLDPROC_NULL(void) = 0;

		bool
		YPOLDPROC_DOMAIN(domainname) = 1;

		bool
		YPOLDPROC_DOMAIN_NONACK(domainname) = 2;

		ypresponse
		YPOLDPROC_MATCH(yprequest) = 3;

		ypresponse
		YPOLDPROC_FIRST(yprequest) = 4;

		ypresponse
		YPOLDPROC_NEXT(yprequest) = 5;

		ypresponse
		YPOLDPROC_POLL(yprequest) = 6;

		ypresponse
		YPOLDPROC_PUSH(yprequest) = 7;

		ypresponse
		YPOLDPROC_PULL(yprequest) = 8;

		ypresponse
		YPOLDPROC_GET(yprequest) = 9;
	} = 1;

	version YPVERS {
		void 
		YPPROC_NULL(void) = 0;

		bool 
		YPPROC_DOMAIN(domainname) = 1;	

		bool
		YPPROC_DOMAIN_NONACK(domainname) = 2;

		ypresp_val
		YPPROC_MATCH(ypreq_key) = 3;

		ypresp_key_val 
#if 1 /* should be ypreq_nokey */
		YPPROC_FIRST(ypreq_key) = 4;
#else
		YPPROC_FIRST(ypreq_nokey) = 4;
#endif
		ypresp_key_val 
		YPPROC_NEXT(ypreq_key) = 5;

		ypresp_xfr
		YPPROC_XFR(ypreq_xfr) = 6;

		void
		YPPROC_CLEAR(void) = 7;

		ypresp_all
		YPPROC_ALL(ypreq_nokey) = 8;

		ypresp_master
		YPPROC_MASTER(ypreq_nokey) = 9;

		ypresp_order
		YPPROC_ORDER(ypreq_nokey) = 10;

		ypresp_maplist 
		YPPROC_MAPLIST(domainname) = 11;
	} = 2;
} = 100004;
#endif
#if !defined(YPSERV_ONLY) && !defined(YPBIND_ONLY)
/*
 * YPPUSHPROC_XFRRESP is the callback routine for result of YPPROC_XFR
 */
program YPPUSH_XFRRESPPROG {
	version YPPUSH_XFRRESPVERS {
		void
		YPPUSHPROC_NULL(void) = 0;
#if 1 /* argument and return value are backwards */
		yppushresp_xfr	
		YPPUSHPROC_XFRRESP(void) = 1;
#else
		void
		YPPUSHPROC_XFRRESP(yppushresp_xfr) = 1;
#endif
	} = 1;
} = 0x40000000;	/* transient: could be anything up to 0x5fffffff */
#endif
#if !defined(YPSERV_ONLY) && !defined(YPPUSH_ONLY)
/*
 * YP binding protocol
 */
program YPBINDPROG {
	version YPBINDVERS {
		void
		YPBINDPROC_NULL(void) = 0;
	
		ypbind_resp
		YPBINDPROC_DOMAIN(domainname) = 1;

		void
		YPBINDPROC_SETDOM(ypbind_setdom) = 2;
	} = 2;
} = 100007;

#endif
