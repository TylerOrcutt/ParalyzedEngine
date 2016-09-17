#ifndef _PE_TCPCLIENT_H_
#define _PE_TCPCLIENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _cplusplus
extern "C"{
#endif
typedef struct PETCPClient{
fd_set master;
	fd_set read_fds;
	struct timeval t;
	int fdmax;
    int socket;
struct addrinfo hints, *result, *ptr, *servinfo;
}PETCPClient;

int PE_TCPConnect(PETCPClient *c){
memset(&c->hints,0,sizeof c->hints);
		c->hints.ai_family=AF_UNSPEC;//use ipv4 or ipv6
		c->hints.ai_socktype=SOCK_STREAM;//tcp socket
		int res;

		//
		if((res=getaddrinfo("127.0.0.1","9898",&c->hints,&c->servinfo))!=0){
			 printf("host not found.\n");
				return -1;
		}
		//setup socket
		c->socket=socket(c->servinfo->ai_family,c->servinfo->ai_socktype,c->servinfo->ai_protocol);
		if(c->socket==-1){
			printf("socket error.\n");
			return -1;
		}
		if(connect(c->socket,c->servinfo->ai_addr,c->servinfo->ai_addrlen)==-1){
	 	close(c->socket);
			printf("Unable to connect.\n");
			return -1;
		}/*
//std::cout<<"Atempting SSL Connection\n";
		ssl = SSL_new(ctx);
		SSL_set_fd(ssl,con);
		if ( SSL_connect(ssl)==-1){
			printf*"SSL Connection failed\n";
			return -1;
		}*/

		//std::cout<<con<<std::endl;
		c->fdmax=c->socket;
	//	SSL_set_fd(ssl,con);
		FD_SET(c->socket,&c->master);
return 1;
}
int PE_TCPClient_Write(PETCPClient * c, const char * data, int length){
return write(c->socket,data,length);
}


int   PE_TCPClient_Read(PETCPClient * c,char * data){
int bytes=0;
if (c->socket == -1){
		return 0;
	}
  c->read_fds=c->master;
 
            FD_SET(c->socket, &c->read_fds);
            c->t.tv_sec = 0;
               c->t.tv_usec = 10;

  if(select(c->socket+1,&c->read_fds,NULL,NULL,&c->t)==-1){
    printf("select error\n");
    c->socket= -1;
    return  0;
  }
//std::cout<<"reading data 2\n";
   if(FD_ISSET(c->socket,&c->read_fds)){//data to be red
  char buffer[1024];
 
  //cout<<"data?\n";
//std::cout<<"reading data\n";
  bytes=read(c->socket,buffer,sizeof(buffer));
  if (bytes<=0){
	  c->socket = -1;
	  return 0;
  }
  buffer[bytes-2]='\0';
  //data=buffer;
  memcpy(data,buffer,1024);
//write(c->socket,data,length);
}
return  bytes;
}

#ifdef _cplusplus
}
#endif
#endif