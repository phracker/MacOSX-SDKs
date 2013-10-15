/*

Copyright 1993, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

 * Copyright 1993, 1994 NCR Corporation - Dayton, Ohio, USA
 *
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name NCR not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.  NCR and makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * NCR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN
 * NO EVENT SHALL NCR BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef WIN32
#include <netdnet/dn.h>
#include <netdnet/dnetdb.h>
#include <sys/ioctl.h>
#endif /* !WIN32 */

#include <stdio.h>

#ifdef WIN32
#define _WILLWINSOCK_
#define BOOL wBOOL
#undef Status
#define Status wStatus
#include <prgpre.h> /* PATHWORKS header normally in %MSTOOLS%\h\pathwork */
#undef Status
#define Status int
#undef BOOL
#include <X11/Xw32defs.h>
#undef close
#define close closesocket
#endif /* WIN32 */


#if defined(X11_t)
#define DNETOBJ "X$X"
#endif
#if defined(XIM_t)
#define DNETOBJ "IMSERVER$"
#endif
#if defined(FS_t) || defined(FONT_t)
#define DNETOBJ "X$FONT"
#endif
#if defined(ICE_t)
#define DNETOBJ ""
#endif
#if defined(TEST_t)
#define DNETOBJ "X$TEST"
#endif


/*
 * This is the DNET implementation of the X Transport service layer
 */

/*
 * This function gets the local address of the socket and stores it in the
 * XtransConnInfo structure for the connection.
 */

static int
TRANS(DNETGetAddr) (XtransConnInfo ciptr)

{
    struct sockaddr_dn	sockname;
    int			namelen = sizeof(sockname);

    PRMSG (3,"DNETGetAddr(%x)\n", ciptr, 0, 0);

    if (getsockname (ciptr->fd, (struct sockaddr *) &sockname, &namelen) < 0)
    {
	PRMSG (1,"DNETGetAddr: getsockname() failed: %d\n",
	      EGET(), 0, 0);
	return -1;
    }


    /*
     * Everything looks good: fill in the XtransConnInfo structure.
     */

    if ((ciptr->addr = (char *) xalloc (namelen)) == NULL)
    {
        PRMSG (1, "DNETGetAddr: Can't allocate space for the addr\n",
	       0, 0, 0);
        return -1;
    }

    ciptr->family = sockname.sdn_family;
    ciptr->addrlen = namelen;
    memcpy (ciptr->addr, &sockname, ciptr->addrlen);

    return 0;
}


/*
 * This function gets the remote address of the socket and stores it in the
 * XtransConnInfo structure for the connection.
 */

static int
TRANS(DNETGetPeerAddr) (XtransConnInfo ciptr)

{
    struct sockaddr_dn	sockname;
    int			namelen = sizeof(sockname);

    PRMSG (3,"DNETGetPeerAddr(%x)\n", ciptr, 0, 0);

    if (getpeername (ciptr->fd, (struct sockaddr *) &sockname, &namelen) < 0)
    {
	PRMSG (1,"DNETGetPeerAddr: getpeername() failed: %d\n",
	      EGET(), 0, 0);
	return -1;
    }

    /*
     * Everything looks good: fill in the XtransConnInfo structure.
     */

    if ((ciptr->peeraddr = (char *) xalloc (namelen)) == NULL)
    {
        PRMSG (1,
	      "DNETGetPeerAddr: Can't allocate space for the addr\n",
	      0, 0, 0);
        return -1;
    }

    ciptr->peeraddrlen = namelen;
    memcpy (ciptr->peeraddr, &sockname, ciptr->peeraddrlen);

    return 0;
}


#ifdef TRANS_CLIENT

static XtransConnInfo
TRANS(DNETOpenCOTSClient) (Xtransport *thistrans, char *protocol, 
			   char *host, char *port)

{
    XtransConnInfo	ciptr;

    PRMSG (2,"DNETOpenCOTSClient(%s,%s,%s)\n", protocol, host, port);

    if ((ciptr = (XtransConnInfo) xcalloc (
	1, sizeof(struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETOpenCOTSClient: malloc failed\n", 0, 0, 0);
	return NULL;
    }

    ciptr->index = 0;		/* only one form of DECnet */

    /* nothing else to do here */

    return ciptr;
}

#endif /* TRANS_CLIENT */


#ifdef TRANS_SERVER

static XtransConnInfo
TRANS(DNETOpenCOTSServer) (Xtransport *thistrans, char *protocol, 
			   char *host, char *port)

{
    XtransConnInfo	ciptr;

    PRMSG (2,"DNETOpenCOTSServer(%s,%s,%s)\n", protocol, host, port);

    if ((ciptr = (XtransConnInfo) xcalloc (
	1, sizeof(struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETOpenCOTSServer: malloc failed\n", 0, 0, 0);
	return NULL;
    }

    if ((ciptr->fd = socket (AF_DECnet, SOCK_STREAM, 0)) < 0)
    {
	xfree ((char *) ciptr);
	return NULL;
    }

    ciptr->index = 0;		/* only one form of DECnet */

    return (ciptr);
}

#endif /* TRANS_SERVER */


#ifdef TRANS_CLIENT

static XtransConnInfo
TRANS(DNETOpenCLTSClient) (Xtransport *thistrans, char *protocol, 
			   char *host, char *port)

{
    XtransConnInfo	ciptr;

    PRMSG (2,"DNETOpenCLTSClient(%s,%s,%s)\n", protocol, host, port);

    if ((ciptr = (XtransConnInfo) xcalloc (
	1, sizeof (struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETOpenCLTSClient: malloc failed\n", 0, 0, 0);
	return NULL;
    }

    ciptr->index = 0;		/* only one form of DECnet */

    /* nothing else to do here */

    return ciptr;
}

#endif /* TRANS_CLIENT */


#ifdef TRANS_SERVER

static XtransConnInfo
TRANS(DNETOpenCLTSServer) (Xtransport *thistrans, char *protocol, 
			   char *host, char *port)

{
    /* NEED TO IMPLEMENT */

    PRMSG (2,"DNETOpenCLTSServer(%s,%s,%s)\n", protocol, host, port);
    return NULL;
}

#endif /* TRANS_SERVER */


#ifdef TRANS_REOPEN

static XtransConnInfo
TRANS(DNETReopenCOTSServer) (Xtransport *thistrans, int fd, char *port)

{
    XtransConnInfo	ciptr;

    PRMSG (2,"DNETReopenCOTSServer(%d,%s)\n", fd, port, 0);

    if ((ciptr = (XtransConnInfo) xcalloc (
	1, sizeof(struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETReopenCOTSServer: malloc failed\n", 0, 0, 0);
	return NULL;
    }

    ciptr->fd = fd;
    ciptr->index = 0;		/* only one form of DECnet */

    return (ciptr);
}

static XtransConnInfo
TRANS(DNETReopenCLTSServer) (Xtransport *thistrans, int fd, char *port)

{
    XtransConnInfo	ciptr;

    PRMSG (2,"DNETReopenCLTSServer(%d,%s)\n", fd, port, 0);

    if ((ciptr = (XtransConnInfo) xcalloc (
	1, sizeof(struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETReopenCLTSServer: malloc failed\n", 0, 0, 0);
	return NULL;
    }

    ciptr->fd = fd;
    ciptr->index = 0;		/* only one form of DECnet */

    return (ciptr);
}

#endif /* TRANS_REOPEN */


static int
TRANS(DNETSetOption) (XtransConnInfo ciptr, int option, int arg)

{
    PRMSG (2,"DNETSetOption(%d,%d,%d)\n", ciptr->fd, option, arg);

    return -1;
}


#ifdef TRANS_SERVER

static int
TRANS(DNETCreateListener) (XtransConnInfo ciptr, char *port, unsigned int flags)

{
    struct sockaddr_dn  dnsock;
    int			fd = ciptr->fd;

    PRMSG (3, "DNETCreateListener(%x,%d)\n", ciptr, fd, 0);

    bzero ((char *) &dnsock, sizeof (dnsock));
    dnsock.sdn_family = AF_DECnet;

    if (port && *port )
	sprintf (dnsock.sdn_objname, "%s%s", DNETOBJ, port);
    else
#ifdef X11_t
	return -1;
#else
	sprintf (dnsock.sdn_objname, "%s%d", DNETOBJ, getpid ());
#endif

    dnsock.sdn_objnamel = strlen (dnsock.sdn_objname);

    if (bind (fd, (struct sockaddr *) &dnsock, sizeof (dnsock)))
    {
	close (fd);
	return -1;
    }

    if (listen (fd, 5))
    {
	close (fd);
	return (-1);
    }


    /* Set a flag to indicate that this connection is a listener */

    ciptr->flags = 1 | (ciptr->flags & TRANS_KEEPFLAGS);

    return 0;
}


static XtransConnInfo
TRANS(DNETAccept) (XtransConnInfo ciptr, int *status)

{
    XtransConnInfo	newciptr;
    struct sockaddr_dn	sockname;
    int			namelen = sizeof(sockname);

    PRMSG (2, "DNETAccept(%x,%d)\n", ciptr, ciptr->fd, 0);

    if ((newciptr = (XtransConnInfo) xcalloc(
	1, sizeof (struct _XtransConnInfo))) == NULL)
    {
	PRMSG (1, "DNETAccept: malloc failed\n", 0, 0, 0);
	*status = TRANS_ACCEPT_BAD_MALLOC;
	return NULL;
    }

    if((newciptr->fd = accept (ciptr->fd,
	(struct sockaddr *) &sockname, &namelen)) < 0)
    {
	PRMSG (1, "DNETAccept: accept() failed\n", 0, 0, 0);

	xfree (newciptr);
	*status = TRANS_ACCEPT_FAILED;
	return NULL;
    }

    /*
     * Get this address again because the transport may give a more 
     * specific address now that a connection is established.
     */

    if (TRANS(DNETGetAddr) (newciptr) < 0)
    {
	PRMSG(1,
	"DNETAccept: ...DNETGetAddr() failed:\n", 0, 0, 0);
	close (newciptr->fd);
	xfree (newciptr);
	*status = TRANS_ACCEPT_MISC_ERROR;
        return NULL;
    }

    if (TRANS(DNETGetPeerAddr) (newciptr) < 0)
    {
	PRMSG(1,
	"DNETAccept: ...DNETGetPeerAddr() failed:\n", 0, 0, 0);

	close (newciptr->fd);
	if (newciptr->addr) xfree (newciptr->addr);
	xfree (newciptr);
	*status = TRANS_ACCEPT_MISC_ERROR;
        return NULL;
    }

    *status = 0;

    return newciptr;
}

#endif /* TRANS_SERVER */


#ifdef TRANS_CLIENT

#define OBJBUFSIZE 64

static int
TRANS(DNETConnect) (XtransConnInfo ciptr, char *host, char *port)

{
    char objname[OBJBUFSIZE];

    extern int dnet_conn();
    
    PRMSG (2,"DNETConnect(%d,%s,%s)\n", ciptr->fd, host, port);

#ifdef X11_t
    /*
     * X has a well known port, that is transport dependent. It is easier
     * to handle it here, than try and come up with a transport independent
     * representation that can be passed in and resolved the usual way.
     *
     * The port that is passed here is really a string containing the idisplay
     * from ConnectDisplay().
     */

    if (is_numeric (port))
    {
	short tmpport = (short) atoi (port);

	sprintf (objname, "X$X%d", tmpport);
    }
    else
#endif
	strncpy(objname, port, OBJBUFSIZE);


    /*
     * Do the connect
     */

    if (!host) host = "0";

    if ((ciptr->fd = dnet_conn (host, objname, SOCK_STREAM, 0, 0, 0, 0)) < 0)
    {
	return TRANS_CONNECT_FAILED;
    }


    /*
     * Sync up the address fields of ciptr.
     */

    if (TRANS(DNETGetAddr) (ciptr) < 0)
    {
	PRMSG (1,
	      "DNETConnect: ...DNETGetAddr() failed:\n", 0, 0, 0);
	return TRANS_CONNECT_FAILED;
    }

    if (TRANS(DNETGetPeerAddr) (ciptr) < 0)
    {
	PRMSG (1,
	      "DNETConnect: ...DNETGetPeerAddr() failed:\n",
	      0, 0, 0);
	return TRANS_CONNECT_FAILED;
    }

    return 0;
}

#endif /* TRANS_CLIENT */


static int
TRANS(DNETBytesReadable) (XtransConnInfo ciptr, BytesReadable_t *pend)

{
    PRMSG (2,"DNETBytesReadable(%x,%d,%x)\n", ciptr, ciptr->fd, pend);

#ifdef WIN32
    {
	int ret = ioctlsocket ((SOCKET) ciptr->fd, FIONREAD, (u_long *) pend);
	errno = WSAGetLastError();
	return ret;
    }
#else
    return ioctl(ciptr->fd, FIONREAD, (char *)pend);
#endif /* WIN32 */
}


static int
TRANS(DNETRead) (XtransConnInfo ciptr, char *buf, int size)

{
    PRMSG (2,"DNETRead(%d,%x,%d)\n", ciptr->fd, buf, size);

#ifdef WIN32
    {
	int ret = recv ((SOCKET)ciptr->fd, buf, size, 0);
	errno = WSAGetLastError();
	return ret;
    }
#else
    return read (ciptr->fd, buf, size);
#endif /* WIN32 */
}


static int
TRANS(DNETWrite) (XtransConnInfo ciptr, char *buf, int size)

{
    PRMSG (2,"DNETWrite(%d,%x,%d)\n", ciptr->fd, buf, size);

#ifdef WIN32
    {
	int ret = send ((SOCKET)ciptr->fd, buf, size, 0);
	errno = WSAGetLastError();
	return ret;
    }
#else
    return write (ciptr->fd, buf, size);
#endif /* WIN32 */
}


static int
TRANS(DNETReadv) (XtransConnInfo ciptr, struct iovec *buf, int size)

{
    PRMSG (2,"DNETReadv(%d,%x,%d)\n", ciptr->fd, buf, size);

    return READV (ciptr, buf, size);
}


static int
TRANS(DNETWritev) (XtransConnInfo ciptr, struct iovec *buf, int size)

{
    PRMSG (2,"DNETWritev(%d,%x,%d)\n", ciptr->fd, buf, size);

    return WRITEV (ciptr, buf, size);
}


static int
TRANS(DNETDisconnect) (XtransConnInfo ciptr)

{
    PRMSG (2,"DNETDisconnect(%x,%d)\n", ciptr, ciptr->fd, 0);

#ifdef WIN32
    {
	int ret = shutdown (ciptr->fd, 2);
	errno = WSAGetLastError();
	return ret;
    }
#else
    return shutdown (ciptr->fd, 2); /* disallow further sends and receives */
#endif
}


static int
TRANS(DNETClose) (XtransConnInfo ciptr)

{
    PRMSG (2,"DNETClose(%x,%d)\n", ciptr, ciptr->fd, 0);

#ifdef WIN32
    {
	int ret = close (ciptr->fd);
	errno = WSAGetLastError();
	return ret;
    }
#else
    return close (ciptr->fd);
#endif
}


Xtransport	TRANS(DNETFuncs) = {
    /* DNET Interface */
    "dnet",
    0,
#ifdef TRANS_CLIENT
    TRANS(DNETOpenCOTSClient),
#endif /* TRANS_CLIENT */
#ifdef TRANS_SERVER
    TRANS(DNETOpenCOTSServer),
#endif /* TRANS_SERVER */
#ifdef TRANS_CLIENT
    TRANS(DNETOpenCLTSClient),
#endif /* TRANS_CLIENT */
#ifdef TRANS_SERVER
    TRANS(DNETOpenCLTSServer),
#endif /* TRANS_SERVER */
#ifdef TRANS_REOPEN
    TRANS(DNETReopenCOTSServer),
    TRANS(DNETReopenCLTSServer),
#endif /* TRANS_REOPEN */
    TRANS(DNETSetOption),
#ifdef TRANS_SERVER
    TRANS(DNETCreateListener),
    NULL,		       			/* ResetListener */
    TRANS(DNETAccept),
#endif /* TRANS_SERVER */
#ifdef TRANS_CLIENT
    TRANS(DNETConnect),
#endif /* TRANS_CLIENT */
    TRANS(DNETBytesReadable),
    TRANS(DNETRead),
    TRANS(DNETWrite),
    TRANS(DNETReadv),
    TRANS(DNETWritev),
    TRANS(DNETDisconnect),
    TRANS(DNETClose),
    TRANS(DNETClose),
};
