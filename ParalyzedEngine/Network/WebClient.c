#include "WebClient.h"



 char * PE_HTTPRequest(char * host,char * page,char * params){
    return "";
}
char * PE_HTTPSRequest( const char *webhost,const char * page,PECookie*cookie,const char * params)

{
        SSL_load_error_strings();
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
    printf("Making HTTPS request\n");
    int sock;
    int port= 443;
    struct sockaddr_in server;
    struct hostent *host = gethostbyname(webhost);
     
    if(host==NULL || host->h_addr==NULL){
        printf("failed to locate host\n");
       return NULL;
    }

    bzero(&server,sizeof(server));
    memset(&server,0,sizeof(struct sockaddr_in));
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    bcopy((char*)host->h_addr,(char*)&server.sin_addr.s_addr,host->h_length);

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        printf("failed to bind socket\n");
        return NULL;
    }

    if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0){
        printf("failed to connect to remote host\n");
        return NULL;
    }
    char *a = malloc(sizeof(char)*(256+strlen(params)));
    strcat(a,"POST /");
    strcat(a,page);
    strcat(a," HTTP/1.1\r\n");
      strcat(a,"Host: ");
    strcat(a,webhost);
   strcat(a,"\r\n");
   if(cookie!=NULL && cookie->id!=NULL){
       strcat(a,"Cookie: ");
       strcat(a, cookie->id);
       strcat(a,"\r\n");
   }
   strcat(a,"Accept: */*\r\nConnection: close\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ");
 
char plen;
sprintf( &plen, "%i", strlen(params) );
      strcat(a,&plen);
      strcat(a,"\r\n\r\n");
      strcat(a,params);   
//printf("%s\n%i \n",a,strlen(a));

SSL * ssl = SSL_new(ctx);
SSL_set_fd(ssl,sock);
SSL_connect(ssl);
if(SSL_write(ssl,a,strlen(a))<0){
    printf("error making request");
    return NULL;
}
char  packet[1];
char * responce = malloc(sizeof(char)*2048);
sprintf(responce,"",0);
char * html= NULL;
for(int i=0;SSL_read(ssl,&packet,1)>0;i++){
 //   printf("%s\n",&packet);
 //packet[strnlen(packet)] = "\0";
    strcat(responce,packet);
    char clen[16];
    if(i>=16){
    memcpy(clen,&responce[i-15],16);
   // clen[16]='\0';
        printf("%s\n",clen);
    
    if(clen == "Content-Length: "){
        printf("FOUND CONTENT LENGH\n");
    }
    }
}
printf("%s",responce);





//clean up
    SSL_CTX_free(ctx); 
    FIPS_mode_set(0);
    CRYPTO_set_locking_callback(NULL); 
   CRYPTO_set_id_callback(NULL);
 free (a);

return "";
}


 void init_PECookie(PECookie*cookie){
cookie->id=NULL;
cookie->path=NULL;
cookie->host=NULL;
}

 void free_PECookie(PECookie*cookie){
free (cookie->id);
free (cookie->path);
free (cookie->host);
free (cookie);
}