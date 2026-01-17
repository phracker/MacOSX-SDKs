/* $XFree86: xc/lib/xtrans/Xtransos2.c,v 3.9tsi Exp $ */

/*
 * (c) Copyright 1996 by Sebastien Marineau and Holger Veit
 *			<marineau@genie.uottawa.ca>
 *                      <Holger.Veit@gmd.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * HOLGER VEIT  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of Sebastien Marineau or Holger Veit shall not be
 * used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization from Holger Veit or Sebastien Marineau.
 *
 */

/* Implementation of the OS/2 local pipe transport layer */

#define INCL_DOSNMPIPES
#define INCL_DOSPROCESS
#define INCL_DOSERRORS
#define INCL_DOSFILEMGR
#undef BYTE
#undef BOOL
#include <os2.h>

#ifdef XSERV_t
extern HEV hPipeSem;
BOOL init_server_pipes();
#endif

/*************************************************************************
 * Independent Layer
 *************************************************************************/
#ifdef TRANS_CLIENT

static XtransConnInfo
TRANS(Os2OpenClient)(Xtransport *thistrans, char *protocol,
		     char *host, char *port)
{
	APIRET rc;
	HFILE hfd,hServer;
	ULONG action,byteWritten,State;
	char pipename[256],clientname[256];
        char server_string[256];
        struct sockaddr *addr_name;
        unsigned char pipe_len;
	XtransConnInfo ciptr;
        static int unique_id=0;
        int i,namelen,try;

	PRMSG(2,"Os2OpenClient(%s,%s,%s)\n",protocol,host,port);

	/* test, whether the host is really local, i.e. either
	 * "os2" or "local"
	 */
	if (strcmp(protocol,"os2") && strcmp(protocol,"local")) {
		PRMSG (1,
			"Os2OpenClient: Cannot connect to non-local host %s\n",
			host, 0, 0);
		return NULL;
	}

   /* make the pipename */

    if (port && *port ) {
	if( *port == '/' ) { /* A full pathname */
		(void) sprintf(pipename, "\\PIPE\\X\\%s,", port);
	    } else {
		(void) sprintf(pipename, "%s%s", "\\PIPE\\X\\xf86.", port);
	    }
    } else {
	(void) sprintf(pipename, "\\PIPE\\X\\xfree86"); }

    PRMSG(5, "Os2OpenClient: Creating pipe %s\n",pipename, 0,0 );

	/* make a connection entry */	
	if( (ciptr=(XtransConnInfo)xcalloc(1,sizeof(struct _XtransConnInfo))) == NULL ) {
		PRMSG(1,"Os2OpenClient: calloc(1,%d) failed\n",
			sizeof(struct _XtransConnInfo),0,0 );
		return NULL;
	}

	/* open the pipe. Try ten times before giving up at 500ms intervals*/
    try = 0;
    do {
	rc = DosOpen(pipename,&hServer, &action, 0,
		FILE_NORMAL, FILE_OPEN,
		OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE,
		(PEAOP2)NULL);
        if(rc == 0) break;
	if (try >=10) {
		PRMSG(1,"Os2OpenClient: Open server pipe %s failed, rc=%d\n",
			pipename,rc,0 );
		PRMSG(1,"\tProbable causes: either the XServer is not running, or has not started properly,\n",
			0,0,0 );
		PRMSG(1,"\tor the DISPLAY variable is set incorrectly.\n",
			0,0,0 );
		xfree(ciptr);
		return NULL;
	    }
       try ++;
       DosSleep(500);
       } while (rc != 0);

/* OK, now we are talking to the server. Generate a unique pipe name and pass it to
 * the server. Make the pipe and wait for server to connect */

   sprintf(clientname,"\\PIPE\\X\\%d.%d",getpid(),unique_id++);

   rc = DosCreateNPipe (clientname, &hfd,
                       NP_NOINHERIT | NP_ACCESS_DUPLEX,
                       1 | NP_NOWAIT | NP_TYPE_BYTE | NP_READMODE_BYTE,
                       16384, 16384, 0);
   if (rc != 0){
        PRMSG(1, "Os2OpenClient: Unable to create pipe %s\n", pipename,0,0 );
	DosClose(hfd);
        pipe_len=0;
        DosWrite(hServer,&pipe_len,1,&byteWritten);
        DosClose(hServer);
        xfree(ciptr);
	return(NULL);
    }

 /* Connect to the pipe. */

  rc = DosConnectNPipe (hfd);
  if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
    {
        PRMSG(1, "Os2OpenClient: Unable to connect to pipe %s\n", pipename,0,0 );
        DosClose (hfd);
        DosClose(hServer);
        xfree(ciptr);
        return (NULL);
    }

/* Now write name to server on hServer */
        server_string[0]=(char) strlen(clientname)+1;
        strcpy(&server_string[1],clientname);
        rc = DosWrite(hServer,server_string,(ULONG)server_string[0]+1,&byteWritten);
        if(rc != 0){  /* Could not write to server pipe? */
           PRMSG(1, "Os2OpenClient: Error writing to server pipe, handle=%d, rc=%d, w=%d\n",
                hServer,rc,byteWritten );
           DosClose(hServer);
           DosClose(hfd);
           xfree(ciptr);
           return(NULL);
           }

      PRMSG (5, "Os2OpenCLient: Wrote pipename %s to server; len %d written %d \n",
        &server_string[1],server_string[0]+1,byteWritten);


/* The server will respond by opening the pipe. Wait for that for 30 secs */

        i=0;
        DosSleep(50);  /* Give it time to catch up but minimize race condition*/
        rc = DosConnectNPipe(hfd);
        while((rc == ERROR_PIPE_NOT_CONNECTED)&&(i++<60)) {
                DosSleep(500);
                rc = DosConnectNPipe(hfd);
                }

        if(rc != 0){  /* Server has not responded! */
           PRMSG(1, "Os2OpenClient: Timeout on wait for server response, handle=%d, rc=%d\n",hServer,rc,0 );
           PRMSG(1, "\tProbable cause: the XServer has exited or crashed while the connection was being established\n",0,0,0 );
           PRMSG(1, "\tor the XServer is too busy to respond.\n",0,0,0 );
           DosClose(hServer);
           DosClose(hfd);
           xfree(ciptr);
           return(NULL);
           }

/* OK, the server has connected! Fill-in the info and return */

        DosClose(hServer);

/* Last check: make sure client is connected! */

        rc = DosQueryNPHState(hfd,&State);
        if(rc != 0){  /* Client is not connected! */
           PRMSG(1, "Os2OpenClient: Client pipe does not appear connected. rc=%d, h=%d\n",rc,hfd,0 );
           PRMSG(1, "\tProbable cause: the XServer has just exited.\n",0,0,0 );
           DosClose(hfd);
           xfree(ciptr);
           return(NULL);
           }

        namelen=sizeof(struct sockaddr);
        if ((ciptr->addr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2OpenClient: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hfd);
                xfree(ciptr);
                return(NULL);
           }
        ciptr->addrlen = namelen;
        ((struct sockaddr *)ciptr->addr)->sa_family = AF_UNIX;
        strcpy(((struct sockaddr *)ciptr->addr)->sa_data, "local");

        if ((ciptr->peeraddr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2OpenCLient: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hfd);
                xfree(ciptr->addr);
                xfree(ciptr);
                return(NULL);
           }
       ciptr->peeraddrlen = namelen;
       ((struct sockaddr *)ciptr->peeraddr)->sa_family = AF_UNIX;
       strcpy (((struct sockaddr *)ciptr->peeraddr)->sa_data,"local");

       PRMSG (5, "Os2OpenCLient: Filled in struct: len %d %d name %s\n",
                ciptr->addrlen,ciptr->peeraddrlen,((struct sockaddr *)ciptr->peeraddr)->sa_data);


        ciptr->index=hfd;
        ciptr->family=AF_UNIX;
        if((ciptr->fd=_imphandle(hfd))<0){
           PRMSG(1, "Os2OpenClient: Could not import the pipe handle into EMX\n",0,0,0 );
           PRMSG(1, "\tProbable cause: EMX has run out of free file handles.\n",0,0,0 );
           DosClose(hfd);
           xfree(ciptr->addr);
           xfree(ciptr->peeraddr);
           xfree(ciptr);
           return(NULL);
           }
    PRMSG(5, "Os2OpenClient: pipe handle %d EMX handle %d\n",ciptr->index,ciptr->fd,0 );
        fcntl(ciptr->fd,F_SETFL,O_NDELAY);
        fcntl(ciptr->fd,F_SETFD,FD_CLOEXEC);
	return ciptr;
}
#endif /* TRANS_CLIENT */

#ifdef TRANS_SERVER
static XtransConnInfo
TRANS(Os2OpenServer)(Xtransport *thistrans, char *protocol,
		     char *host, char *port)
{
   APIRET rc;
   HFILE hfd;
   ULONG action;
   char pipename[256];
   struct sockaddr *addr_name;
   XtransConnInfo ciptr;
   int namelen;

#ifdef XSERV_t
    if (! init_server_pipes()) return(NULL);
#endif

    PRMSG(2,"Os2OpenServer(%s,%s,%s)\n",protocol,host,port);

   if( (ciptr=(XtransConnInfo)xcalloc(1,sizeof(struct _XtransConnInfo))) == NULL )
    {
	PRMSG(1,"Os2OpenServer: xcalloc(1,%d) failed\n",
	      sizeof(struct _XtransConnInfo),0,0 );
	return NULL;
    }


    if (port && *port ) {
	if( *port == '/' ) { /* A full pathname */
		(void) sprintf(pipename, "\\PIPE\\X\\%s", port);
	    } else {
		(void) sprintf(pipename, "%s%s", "\\PIPE\\X\\xf86.", port);
	    }
    } else {
	(void) sprintf(pipename, "\\PIPE\\X\\xfree86");
    }

    PRMSG(5, "Os2OpenServer: Creating pipe %s\n",pipename, 0,0 );

   rc = DosCreateNPipe (pipename, &hfd,
                       NP_NOINHERIT | NP_ACCESS_INBOUND,
                       1 | NP_NOWAIT | NP_TYPE_BYTE | NP_READMODE_BYTE,
                       0, 8192, 0);
   if (rc != 0){
        PRMSG(1, "Os2OpenServer: Unable to create pipe %s, rc=%d\n", pipename,rc,0 );
        PRMSG(1, "\tProbable cause: there is already another XServer running on display :%s\n",port,0,0 );
	DosClose(hfd);
        xfree(ciptr);
	return(NULL);
    }

 /* Connect to the pipe. */

  rc = DosConnectNPipe (hfd);
  if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
    {
        PRMSG(1, "Os2OpenServer: Unable to connect to pipe %s\n", pipename,0,0 );
        DosClose (hfd);
        xfree(ciptr);
        return (NULL);
    }

/* Pipe is now connected and waiting for client connect */

/*** Put in info ***/

        namelen=sizeof(struct sockaddr);
        if ((ciptr->addr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2OpenServer: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hfd);
                xfree(ciptr);
                return(NULL);
           }
        ciptr->addrlen = namelen;
        ((struct sockaddr *)ciptr->addr)->sa_family = AF_UNIX;
        strcpy (((struct sockaddr *)ciptr->addr)->sa_data, "local");

        if ((ciptr->peeraddr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2OpenServer: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hfd);
                xfree(ciptr->addr);
                xfree(ciptr);
                return(NULL);
           }

       ciptr->peeraddrlen = namelen;
       ((struct sockaddr *)ciptr->peeraddr)->sa_family = AF_UNIX;
       strcpy(((struct sockaddr *)ciptr->peeraddr)->sa_data,"local");

      PRMSG (5, "Os2OpenServer: Filled in struct: len %d %d name %s\n",
                ciptr->addrlen,ciptr->peeraddrlen,((struct sockaddr *)ciptr->peeraddr)->sa_data);

    ciptr->index=hfd; /* Save this for later use in this unused member of struct */
    ciptr->flags=1;     /* Listener */
    ciptr->family=AF_UNIX;

    if((ciptr->fd=_imphandle(hfd))<0){
       DosClose(hfd);
       xfree(ciptr->addr);
       xfree(ciptr->peeraddr);
       xfree(ciptr);
       return(NULL);
       }
    PRMSG(5, "Os2OpenServer: Pipe handle %d EMX handle %d",ciptr->index,ciptr->fd,0 );

#ifdef XSERV_t
/* Attach the pipe sem to the pipe. Use handle index as key */
    rc = DosSetNPipeSem(ciptr->fd, (HSEM)hPipeSem, ciptr->fd);
    if (rc){
        PRMSG(1, "Os2OpenCOTSServer: Could not attach sem %d to pipe %d, rc=%d\n",
                 hPipeSem,ciptr->fd,rc);
        DosClose(ciptr->fd);
        xfree(ciptr->addr);
        xfree(ciptr->peeraddr);
        xfree(ciptr);
         return(NULL);
        }
#endif

    fcntl(ciptr->fd,F_SETFL,O_NDELAY);
    fcntl(ciptr->fd,F_SETFD,FD_CLOEXEC);
    return(ciptr);
}
#endif /* TRANS_SERVER */

#ifdef TRANS_CLIENT
static XtransConnInfo
TRANS(Os2OpenCLTSClient)(Xtransport *thistrans, char *protocol,
			 char *host, char *port)
{
	PRMSG(2,"Os2OpenCLTSClient(%s,%s,%s)\n",protocol,host,port);
	return TRANS(Os2OpenClient)(thistrans, protocol, host, port);
}
#endif /* TRANS_CLIENT */

#ifdef TRANS_CLIENT
static XtransConnInfo
TRANS(Os2OpenCOTSClient)(Xtransport *thistrans, char *protocol,
			 char *host, char *port)
{
	PRMSG(2,"Os2OpenCOTSClient(%s,%s,%s)\n",protocol,host,port);
	return TRANS(Os2OpenClient)(thistrans, protocol, host, port);
}
#endif /* TRANS_CLIENT */


#ifdef TRANS_SERVER
static XtransConnInfo
TRANS(Os2OpenCLTSServer)(Xtransport *thistrans, char *protocol,
			 char *host, char *port)
{
	PRMSG(2,"Os2OpenCLTSServer(%s,%s,%s)\n",protocol,host,port);
	return TRANS(Os2OpenServer)(thistrans, protocol, host, port);
}
#endif /* TRANS_SERVER */


#ifdef TRANS_SERVER
static XtransConnInfo
TRANS(Os2OpenCOTSServer)(Xtransport *thistrans, char *protocol,
			 char *host, char *port)
{
	PRMSG(2,"Os2OpenCOTSServer(%s,%s,%s)\n",protocol,host,port);
	return TRANS(Os2OpenServer)(thistrans, protocol, host, port);
}
#endif /* TRANS_SERVER */


#ifdef TRANS_REOPEN
static XtransConnInfo
TRANS(Os2ReopenCOTSServer)(Xtransport *thistrans, int fd, char *port)
{

    XtransConnInfo ciptr;
    char addr_name[256];
    int namelen;

    PRMSG(2,"Os2ReopenCOTSServer(%d,%s)\n", fd, port, 0);

    if( (ciptr=(XtransConnInfo)xcalloc(1,sizeof(struct _XtransConnInfo))) == NULL )
    {
	PRMSG(1,"Os2ReopenCOTSServer: xcalloc(1,%d) failed\n",
	      sizeof(struct _XtransConnInfo),0,0 );
	return NULL;
    }

        strcpy(addr_name,"local");
        namelen=sizeof(addr_name);
        if ((ciptr->addr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2ReopenCOTSServer: Can't allocate space for the addr\n",
	        0, 0, 0);
                xfree(ciptr);
                return(NULL);
           }

        ciptr->addrlen = namelen;
        memcpy (ciptr->addr, addr_name, ciptr->addrlen);
        if ((ciptr->peeraddr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2ReopenCOTSServer: Can't allocate space for the addr\n",
	        0, 0, 0);
                xfree(ciptr);
                return(NULL);
           }

       ciptr->peeraddrlen = namelen;
       memcpy (ciptr->peeraddr,addr_name, ciptr->addrlen);

    ciptr->fd = fd;
    ciptr->family=AF_UNIX;
    ciptr->flags=1;
    PRMSG(1,"Os2ReopenCOTSServer: Filled-in info for handle %d on port %s.\n", fd, port, 0);

    return(ciptr);
}

static XtransConnInfo
TRANS(Os2ReopenCLTSServer)(Xtransport *thistrans, int fd, char *port)
{
    PRMSG(2,"Os2ReopenCLTSServer(%d,%s)\n", fd, port, 0);
    return TRANS(Os2ReopenCOTSServer)(thistrans, fd, port);
}
#endif

static
TRANS(Os2SetOption)(XtransConnInfo ciptr, int option, int arg)
{
    PRMSG(2,"Os2SetOption(%d,%d,%d)\n",ciptr->fd,option,arg);
    return -1;
}

#ifdef TRANS_SERVER

static
TRANS(Os2CreateListener)(XtransConnInfo ciptr, char *port, unsigned int flags)
{
	PRMSG(2,"Os2CreateListener(%x->%d,%s)\n",ciptr,ciptr->fd,port);
	return 0;
}

static XtransConnInfo
TRANS(Os2Accept)(XtransConnInfo ciptr, int *status)
{
    XtransConnInfo	newciptr;
    HFILE hClient;
    unsigned char length;
    ULONG action;
    char clientname[256];
    struct sockaddr *addr_name;
    int in,namelen;
    APIRET rc;


    PRMSG(2,"Os2Accept(%x->%d)\n", ciptr, ciptr->fd,0);
    if( (newciptr=(XtransConnInfo)xcalloc(1,sizeof(struct _XtransConnInfo)))==NULL )
    {
	PRMSG(1,"Os2Accept: xcalloc(1,%d) failed\n",
	      sizeof(struct _XtransConnInfo),0,0 );
	*status = TRANS_ACCEPT_BAD_MALLOC;
	return NULL;
    }

/* Read in length of client pipe name. If fails, then reset server pipe */
    if((in=read(ciptr->fd,&length,1))<=0){
        PRMSG(2,"Os2Accept: Error reading incoming connection, in=%d, error=%d\n",
	      in,errno,0 );
	*status = TRANS_ACCEPT_MISC_ERROR;
        xfree(newciptr);
        rc = DosDisConnectNPipe(ciptr->fd);
        rc = DosConnectNPipe (ciptr->fd);
        if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
        {
                PRMSG(1, "Os2Accept: Unable to reconnect server pipe %d\n", ciptr->fd,0,0 );
                }
	return NULL;
        }
	PRMSG(5, "Os2Accept: Bytes to read for name: %d\n",length,0,0 );


/* Check length for valid length ?? */

/* Now read in length bytes from pipe for client pipe name */
    if((in=read(ciptr->fd,clientname,length))<=0){
        PRMSG(2,"Os2Accept: Error reading incoming connection, in=%d, error=%d\n",
	      in,errno,0 );
	*status = TRANS_ACCEPT_MISC_ERROR;
        xfree(newciptr);
        rc = DosDisConnectNPipe(ciptr->fd);
        rc = DosConnectNPipe (ciptr->fd);
        if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
        {
                PRMSG(1, "Os2Accept: Unable to reconnect server pipe %d\n", ciptr->fd,0,0 );
                }
	return NULL;
        }
    clientname[length]='\0';
    PRMSG(5, "Os2Accept: Server name %s length %d\n",clientname,length,0 );


/* Now we have the client pipe name. Open it with DosOpen  */

     rc = DosOpen(clientname,&hClient, &action, 0,
	   FILE_NORMAL, FILE_OPEN,
	   OPEN_FLAGS_NOINHERIT | OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYREADWRITE,
	   (PEAOP2)NULL);

     PRMSG(5, "Os2Accept: Open pipe %s, handle = %d, rc=%d\n",clientname,hClient,rc );

       if (rc) {
	    PRMSG(1,"Os2Accept: Open pipe %s to client failed, rc=%d\n",
	    clientname,rc,0 );
            PRMSG(1, "\tProbable cause: the client has exited or timed-out.\n",0,0,0 );
            xfree(newciptr);
            rc = DosDisConnectNPipe(ciptr->fd);
            rc = DosConnectNPipe (ciptr->fd);
            if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
               {
                   PRMSG(1, "Os2Accept: Unable to reconnect server pipe %d\n", ciptr->fd,0,0 );
                   }
     	    return NULL;
            }

        rc = DosSetNPHState (hClient, NP_NOWAIT | NP_READMODE_BYTE);
        if (rc != 0)
        {
            PRMSG(1,"Os2Accept: Could not set pipe %s to non-blocking mode, rc=%d\n",
	    hClient,rc,0 );
            xfree(newciptr);
            rc = DosDisConnectNPipe(ciptr->fd);
            rc = DosConnectNPipe (ciptr->fd);
            if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
               {
                   PRMSG(1, "Os2Accept: Unable to reconnect server pipe %d\n", ciptr->fd,0,0 );
                   }
     	    return NULL;
            }

/* OK, we seem to be well connected to client. Now disconnect server pipe and put again in listen */

         rc = DosDisConnectNPipe(ciptr->fd);
         rc = DosConnectNPipe (ciptr->fd);
	PRMSG(5, "Os2Accept: Reconnecting server pipe %d, rc = %d\n",ciptr->fd,rc,0 );

         if (rc != 0 && rc != ERROR_PIPE_NOT_CONNECTED)
         {
              PRMSG(1, "Os2Accept: Unable to reconnect server pipe %d\n", ciptr->fd,0,0 );
              }  /* Consider this non-fatal for present connection */

/* And finally fill-in info in newciptr */

        namelen=sizeof(struct sockaddr);
        if ((newciptr->addr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2Accept: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hClient);
                xfree(newciptr);
                return(NULL);
           }

        newciptr->addrlen = namelen;
        ((struct sockaddr *)newciptr->addr)->sa_family = AF_UNIX;
        strcpy (((struct sockaddr *)newciptr->addr)->sa_data, "local");

        if ((newciptr->peeraddr = (char *) xalloc (namelen)) == NULL)
          {
                PRMSG (1, "Os2Accept: Can't allocate space for the addr\n",
	        0, 0, 0);
                DosClose(hClient);
                xfree(ciptr->addr);
                xfree(newciptr);
                return(NULL);
           }

       newciptr->peeraddrlen = namelen;
       ((struct sockaddr *)newciptr->peeraddr)->sa_family = AF_UNIX;
       strcpy (((struct sockaddr *)newciptr->peeraddr)->sa_data, "local");

      PRMSG (5, "Os2Accept: Filled in struct: len %d %d name %s\n",
                newciptr->addrlen,newciptr->peeraddrlen,newciptr->peeraddr);


        newciptr->index=hClient;
        newciptr->family=AF_UNIX;
        if((newciptr->fd=_imphandle(hClient))<0){
           PRMSG(1,"Os2Accept: Could not import pipe %d into EMX, errno=%d\n",
           hClient,errno,0 );
           PRMSG(1, "\tProbable cause: EMX has run out of file handles.\n",0,0,0 );
           DosClose(hClient);
           xfree(newciptr->addr);
           xfree(newciptr->peeraddr);
           xfree(newciptr);
           return(NULL);
           }
    PRMSG(5, "Os2Accept: Pipe handle %d EMX handle %d",newciptr->index,newciptr->fd,0 );

#ifdef XSERV_t
/* Attach the pipe sem to the pipe. Use handle index as key */
    rc = DosSetNPipeSem(newciptr->fd, (HSEM)hPipeSem, newciptr->fd);
    if (rc){
        PRMSG(1, "Os2OpenCOTSServer: Could not attach sem %d to pipe %d, rc=%d\n",
                 hPipeSem,newciptr->fd,rc);
        DosClose(newciptr->fd);
        xfree(newciptr->addr);
        xfree(newciptr->peeraddr);
        xfree(newciptr);
         return(NULL);
        }
#endif

    fcntl(ciptr->fd,F_SETFL,O_NDELAY);
    fcntl(ciptr->fd,F_SETFD,FD_CLOEXEC);
    *status=0;
    return newciptr;
}

#endif /* TRANS_SERVER */

#ifdef TRANS_CLIENT

static
TRANS(Os2Connect)(XtransConnInfo ciptr, char *host, char *port)
{
    PRMSG(2,"Os2Connect(%x->%d,%s)\n", ciptr, ciptr->fd, port);
    return 0;
}

#endif /* TRANS_CLIENT */

static int
TRANS(Os2BytesReadable)(XtransConnInfo ciptr, BytesReadable_t *pend )
{
   ULONG rc, state, nread;
  AVAILDATA avail;
  char buffer;

  PRMSG(2,"Os2BytesReadable(%x->%d,%x)\n", ciptr, ciptr->fd, pend);

  rc = DosPeekNPipe (ciptr->fd, &buffer, 0, &nread, &avail, &state);
  if (rc != 0)
    {
      errno = EPIPE;
      *pend = 0;
      return -1;
    }
  if (state == NP_STATE_CLOSING)
     {
        errno = EPIPE;
        *pend = 0;
        return -1;
      }
  errno = 0;
  *pend = avail.cbpipe;
  return 0;
}

static int
TRANS(Os2Read)(XtransConnInfo ciptr, char *buf, int size)
{
    int ret;
    APIRET rc;
    ULONG ulRead;
    PRMSG(2,"Os2Read(%d,%x,%d)\n", ciptr->fd, buf, size );
    errno = 0;
    rc = DosRead(ciptr->fd, buf, size, &ulRead);
    if (rc == 0){
        ret = ulRead;
        }
    else if ((rc == 232) || (rc == 231)){
        errno = EAGAIN;
        ret = -1;
        }
    else if (rc == 6){
        errno = EBADF;
        ret = -1;
        }
     else if ((rc == 109) || (rc == 230) || (rc == 233)){
        errno = EPIPE;
       ret = -1;
        }
    else {
           PRMSG(2,"Os2Read: Unknown return code from DosRead, fd %d rc=%d\n", ciptr->fd,rc,0 );
           errno = EINVAL;
           ret = -1;
           }
    return (ret);
}

static int
TRANS(Os2Write)(XtransConnInfo ciptr, char *buf, int size)
{
    int ret;
    APIRET rc;
    ULONG nWritten;
    PRMSG(2,"Os2Write(%d,%x,%d)\n", ciptr->fd, buf, size );
    rc = DosWrite(ciptr->fd, buf, size, &nWritten);
    if (rc == 0){
         ret = nWritten;
         if(nWritten == 0) {
                 errno=EAGAIN;
                 ret = -1;
                 }
         }
    else if ((rc == 39) || (rc == 112)){
        errno = EAGAIN;
        ret = -1;
        }
    else if ((rc == 109) || (rc == 230) || (rc == 233)){
        errno = EPIPE;
        ret = -1;
        }
    else if (rc == 6){
         errno=EBADF;
         ret = -1;
         }
    else {
        PRMSG(2,"(Os2Write)Unknown return code from DosWrite, fd %d rc=%d\n", ciptr->fd,rc,0 );
        errno = EINVAL;
        ret = -1;
        }
    return (ret);
}

static int
TRANS(Os2Readv)(XtransConnInfo ciptr, struct iovec *buf, int size)
{
    int ret;
    PRMSG(2,"Os2Readv(%d,%x,%d)\n", ciptr->fd, buf, size );
    ret = READV(ciptr,buf,size);
    if ((ret <0) && (errno == EINVAL)) errno = EPIPE;
    return (ret);
}

static int
TRANS(Os2Writev)(XtransConnInfo ciptr, struct iovec *buf, int size)
{
    int ret;
    PRMSG(2,"Os2Writev(%d,%x,%d)\n", ciptr->fd, buf, size );
    ret = WRITEV(ciptr,buf,size);
    if ((ret <0) && (errno == EINVAL)) errno = EPIPE;
    if ((ret <0) && (errno == ENOSPC)) errno = EAGAIN;
    return (ret);
}

static int
TRANS(Os2Disconnect)(XtransConnInfo ciptr)
{
    PRMSG(2,"Os2Disconnect(%x->%d)\n", ciptr, ciptr->fd, 0);
    return 0;
}

static int
TRANS(Os2Close)(XtransConnInfo ciptr)
{
    int ret;
    PRMSG(2,"Os2Close(%x->%d)\n", ciptr, ciptr->fd ,0);
    ret=close(ciptr->fd);
    return ret;
}

static int
TRANS(Os2CloseForCloning)(XtransConnInfo ciptr)
{
    int ret;

    PRMSG(2,"Os2CloseForCloning(%x->%d)\n", ciptr, ciptr->fd ,0);
    ret=close(ciptr->fd);
    return ret;
}


Xtransport	TRANS(OS2LocalFuncs) = {
	/* Local Interface */
	"local",
	TRANS_LOCAL,
#ifdef TRANS_CLIENT
	TRANS(Os2OpenCOTSClient),
#endif /* TRANS_CLIENT */
#ifdef TRANS_SERVER
	NULL,
	TRANS(Os2OpenCOTSServer),
#endif /* TRANS_SERVER */
#ifdef TRANS_CLIENT
	TRANS(Os2OpenCLTSClient),
#endif /* TRANS_CLIENT */
#ifdef TRANS_SERVER
	TRANS(Os2OpenCLTSServer),
#endif /* TRANS_SERVER */
#ifdef TRANS_REOPEN
	TRANS(Os2ReopenCOTSServer),
	TRANS(Os2ReopenCLTSServer),
#endif
	TRANS(Os2SetOption),
#ifdef TRANS_SERVER
	TRANS(Os2CreateListener),
	NULL,                  /* ResetListener */
	TRANS(Os2Accept),
#endif /* TRANS_SERVER */
#ifdef TRANS_CLIENT
	TRANS(Os2Connect),
#endif /* TRANS_CLIENT */
	TRANS(Os2BytesReadable),
	TRANS(Os2Read),
	TRANS(Os2Write),
	TRANS(Os2Readv),
	TRANS(Os2Writev),
	TRANS(Os2Disconnect),
	TRANS(Os2Close),
	TRANS(Os2CloseForCloning),
};

#ifdef XSERV_t
/* This function is used in the server to initialize the semaphore used with pipes */

BOOL init_server_pipes()
{
   static BOOL first_time=TRUE;
   ULONG rc;

   if(first_time){
        rc = DosCreateEventSem(NULL, &hPipeSem,DC_SEM_SHARED,FALSE);
        if (rc){
           PRMSG(1,"Os2OpenListener (init_server_pipes): Could not create pipe semaphore, rc=%d\n",
                rc,0,0);
           return(FALSE);
           }
     first_time=FALSE;
     }
return(TRUE);
}
#endif  /* XSERV_t */
