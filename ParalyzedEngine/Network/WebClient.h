#ifndef __PE_WEB_CLIENT_H
#define __PE_WEB_CLIENT_H
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#ifdef __cplusplus
extern "C"{
#endif
typedef struct PECookie{
 char * id;
 char * path;
 char * host;
}PECookie;

extern void init_PECookie(PECookie*cookie);
extern void free_PECookie(PECookie*cookie);
extern char * PE_HTTPRequest(char * host,char * page,char * params);
extern char * PE_HTTPSRequest(const char *host,const char* page,PECookie*cookie,const char * params);

#ifdef __cplusplus
}
#endif
#endif