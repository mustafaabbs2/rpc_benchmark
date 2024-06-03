MSGSVC
This is the source code listing for the msgsvc program:

#include <stdio.h>
#include <rpc.h>
#include <pmapclnt.h>
#include <msg.h>
 
static void   messageprog_1();
static char   *printmessage_1();
 
static struct timeval TIMEOUT = { 25, 0 };
 
main()
{
    SVCXPRT *transp;
    (void)pmap_unset(MESSAGEPROG, MESSAGEVERS);
    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == (SVCXPRT *)NULL)
    {
        (void)fprintf(stderr, "CANNOT CREATE UDP SERVICE.\n");
        exit(16);
    }
    if (!svc_register(transp, MESSAGEPROG, MESSAGEVERS, messageprog_1, IPPROTO_UDP))
    {
        (void)fprintf(stderr,
        "UNABLE TO REGISTER (MESSAGEPROG, MESSAGEVERS, UDP).\n");
        exit(16);
    }
    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
    if (transp == (SVCXPRT *)NULL)
    {
        (void)fprintf(stderr, "CANNOT CREATE TCP SERVICE.\n");
        exit(16);
    }
    if (!svc_register(transp, MESSAGEPROG, MESSAGEVERS, messageprog_1, IPPROTO_TCP))
    {
        (void)fprintf(stderr,
        "UNABLE TO REGISTER (MESSAGEPROG, MESSAGEVERS, TCP).\n");
        exit(16);
    }
    svc_run();
    (void)fprintf(stderr, "SVC_RUN RETURNED\n");
    exit(16);
    return(0);
}
static void messageprog_1(rqstp, transp)
struct svc_req   *rqstp;
SVCXPRT  *transp;
{
    union
    {
        char  *printmessage_1_arg;
    }
    argument;
    char      *result;
    bool_t  (*xdr_argument)();
    bool_t  (*xdr_result)();
    char   *(*local)();
    switch (rqstp->rq_proc)
    {
        case NULLPROC:
            (void)svc_sendreply(transp, xdr_void, (char *)NULL);
            return;
        case PRINTMESSAGE:
            xdr_argument = xdr_wrapstring;
            xdr_result = xdr_int;
            local = (char *(*)()) printmessage_1;
            break;
        default:
            svcerr_noproc(transp);
            return;
    }
    bzero((char *)&argument, sizeof(argument));
    if (!svc_getargs(transp, xdr_argument, &argument))
    {
        svcerr_decode(transp);
        return;
    }
    result = (*local)(&argument, rqstp);
    if (result != (char *)NULL &&
        !svc_sendreply(transp, xdr_result, result))
    {
        svcerr_systemerr(transp);
    }
    if (!svc_freeargs(transp, xdr_argument, &argument))
    {
        (void)fprintf(stderr, "UNABLE TO FREE ARGUMENTS\n");
        exit(16);
    }
    return;
}
char  *printmessage_1(msg)
char  **msg;
{
    static char  result;
    fprintf(stderr, "%s\n", *msg);
    result = 1;
    return(&result);
}

MSGCLNT
This is the source listing for the msgclnt program:

/* @(#)rprintmsg.c 2.1 88/08/11 4.0 RPCSRC */
#include <stdio.h>
#include <rpc.h>
#include <time.h>
#include <msg.h>
 
static struct timeval TIMEOUT = { 25, 0 };
 
static int   *printmessage_1();
 
main(argc, argv)
int   argc;
char  *argv[];
{
    CLIENT   *cl;
    int      *result;
    char     *server ;
    char     *message;
    if (argc < 3)
    {
        fprintf(stderr, "USAGE: %s HOST MESSAGE\n", argv[0]);
        exit(16);
    }
    server  = argv[1];
    message = argv[2];
    cl = clnt_create(server , MESSAGEPROG, MESSAGEVERS, "tcp");
    if (cl == (CLIENT *)NULL)
    {
        clnt_pcreateerror(server );
        exit(16);
    }
    result = printmessage_1(&message, cl);
    if (result == (int *)NULL)
    {
        clnt_perror(cl, server );
        exit(16);
    }
    if (*result == 0)
    {
        fprintf(stderr, "%s: SORRY, %s COULDN'T PRINT YOUR MESSAGE\n",
            argv[0], server );
        exit(16);
    }
    printf("MESSAGE DELIVERED TO %s!\n", server );
    exit(0);
    return(0);
}
static int *printmessage_1(argp, clnt)
char    **argp;
CLIENT  *clnt;
{
    static int res;
    bzero((char *)&res, sizeof(res));
    if (clnt_call(clnt, PRINTMESSAGE, xdr_wrapstring,
        argp, xdr_int, &res, TIMEOUT) != RPC_SUCCESS)
    {
        return ((int *)NULL);
    }
    return (&res);
}

SORTSVC
This is the source code listing for the sortsvc program:

#include <stdio.h>
#include <rpc.h>
#include <pmapclnt.h>
#include <sort.h>
 
static void                  sortprog_1();
static bool_t                xdr_str();
static bool_t                xdr_sortstrings();
static int                   comparestrings();
static struct sortstrings    *sort_1();
 
main()
{
    SVCXPRT    *transp;
    (void)pmap_unset(SORTPROG, SORTVERS);
    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == (SVCXPRT *)NULL)
    {
        (void)fprintf(stderr, "CANNOT CREATE UDP SERVICE.\n");
        exit(16);
    }
    if (!svc_register(transp, SORTPROG, SORTVERS, sortprog_1, IPPROTO_UDP))
    {
        (void)fprintf(stderr,
        "UNABLE TO REGISTER (SORTPROG, SORTVERS, UDP).\n");
        exit(16);
    }
    svc_run();
    (void)fprintf(stderr, "SVC_RUN RETURNED\n");
    exit(16);
    return(0);
}
static void sortprog_1(rqstp, transp)
struct svc_req   *rqstp;
SVCXPRT          *transp;
{
    union
    {
        sortstrings sort_1_arg;
    } 
    argument;
    char      *result;
    bool_t    (*xdr_argument)();
    bool_t    (*xdr_result)();
    char      *(*local)();
    switch (rqstp->rq_proc)
    {
    case NULLPROC:
        (void)svc_sendreply(transp, xdr_void, (char *)NULL);
        return;
    case SORT:
        xdr_argument = xdr_sortstrings;
        xdr_result = xdr_sortstrings;
        local = (char *(*)()) sort_1;
        break;
    default:
        svcerr_noproc(transp);
        return;
    }
    bzero((char *)&argument, sizeof(argument));
    if (!svc_getargs(transp, xdr_argument, &argument))
    {
        svcerr_decode(transp);
        return;
    }
    result = (*local)(&argument, rqstp);
    if (result != (char *)NULL &&
        !svc_sendreply(transp, xdr_result, result))
    {
        svcerr_systemerr(transp);
    }
    if (!svc_freeargs(transp, xdr_argument, &argument))
    {
        (void)fprintf(stderr, "UNABLE TO FREE ARGUMENTS\n");
        exit(16);
    }
    return;
}
static int comparestrings(sp1, sp2)
char   **sp1;
char   **sp2;
{
    return (strcmp(*sp1, *sp2));
}
static struct sortstrings  *sort_1(ssp)
struct sortstrings         *ssp;
{
    static struct sortstrings  ss_res;
    if (ss_res.ss.ss_val != (str *)NULL)
    {
        free(ss_res.ss.ss_val);
    }
    qsort(ssp->ss.ss_val, ssp->ss.ss_len, sizeof(char *), comparestrings);
    ss_res.ss.ss_len = ssp->ss.ss_len; 
    ss_res.ss.ss_val = (str *)malloc(ssp->ss.ss_len * sizeof(str *));
    bcopy(ssp->ss.ss_val, ss_res.ss.ss_val, ssp->ss.ss_len * sizeof(str *));
    return(&ss_res);
}
static bool_t xdr_str(xdrs, objp)
XDR        *xdrs;
str        *objp;
{
    if (!xdr_string(xdrs, objp, MAXSTRINGLEN))
    {
        return (FALSE);
    }
    return (TRUE);
}
static bool_t xdr_sortstrings(xdrs, objp)
XDR            *xdrs;
sortstrings    *objp;
{
    if (!xdr_array(
                   xdrs, (char **)&objp->ss.ss_val, 
                   (u_int *)&objp->ss.ss_len, MAXSORTSIZE, 
                   sizeof(str), xdr_str))
    {
        return (FALSE);
    }
    return (TRUE);
}

SORTCLNT
This is the source code listing for the sortclnt program:

/* @(#)rsort.c 2.1 88/08/11 4.0 RPCSRC */
#include <stdio.h>
#include <rpc.h>
#include <sort.h>
 
static bool_t        xdr_sortstrings();
static bool_t        xdr_str();
static sortstrings   *sort_1();
main(argc, argv)
int     argc;
char    **argv;
{
    char                 *machinename;
    struct sortstrings   args;
    struct sortstrings   res;
    int                  i;
    if (argc < 3)
    {
        fprintf(stderr, "USAGE: %s MACHINENAME {S1 ...}\n", argv[0]);
        exit(16);
    }
    machinename = argv[1];
    args.ss.ss_len = argc - 2;
    args.ss.ss_val = &argv[2];
    res.ss.ss_val = (char **)NULL;
    if ((i = callrpc(machinename, SORTPROG, SORTVERS, SORT,
        xdr_sortstrings, (char *)&args, xdr_sortstrings, (char *)&res)))
    {
        fprintf(stderr, "%s: CALL TO SORT SERVICE FAILED. ", argv[0]);
        clnt_perrno(i);
        fprintf(stderr, "\n");
        exit(16);
    }
    for (i = 0; i < res.ss.ss_len; i++)
    {
        printf("%s\n", res.ss.ss_val[i]);
    }
    exit(0);
    return(0);
}
static struct timeval TIMEOUT = { 25, 0 };
static sortstrings   *sort_1(argp, clnt)
sortstrings          *argp;
CLIENT               *clnt;
{
    static sortstrings    res;
    bzero((char *)&res, sizeof(res));
    if (clnt_call(clnt, SORT, xdr_sortstrings, argp,
        xdr_sortstrings, &res, TIMEOUT) != RPC_SUCCESS)
    {
        return ((sortstrings *)NULL);
    }
    return (&res);
}
static bool_t xdr_str(xdrs, objp)
XDR    *xdrs;
str    *objp;
{
    if (!xdr_string(xdrs, objp, MAXSTRINGLEN))
    {
        return (FALSE);
    }
    return (TRUE);
}
static bool_t xdr_sortstrings(xdrs, objp)
XDR           *xdrs;
sortstrings   *objp;
{
    if (!xdr_array(
                   xdrs, (char **)&objp->ss.ss_val,
                   (u_int *)&objp->ss.ss_len, MAXSORTSIZE,
                   sizeof(str), xdr_str))
    {
        return (FALSE);
    }
    return (TRUE);
}

