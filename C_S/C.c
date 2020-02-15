#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	int sock,numbytes;
	char buf[100];
	struct hostent *he;
	struct sockaddr_in addrSrv;

	if(argc!=3)
	{
		printf("Usage:%s ip port",argv[0]);
		exit(0);
	}
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket");
		exit(0);
	}
	char ip[20],port[10];
	int i=0;
	while(*(argv[1]+i)!=':')
	{
		ip[i]=*(argv[1]+i);
		i++;
	}
	ip[i]='\0';

	sprintf(port,"%s",argv[1]+i+1);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(atoi(port));
	addrSrv.sin_addr.s_addr=inet_addr(ip);
	bzero(&(addrSrv.sin_zero),8);

	struct sockaddr_in addrCli;
	addrCli.sin_family=AF_INET;
	addrCli.sin_port=htons(8100);
	addrCli.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&(addrCli.sin_zero),8);
	if(bind(sock,(struct sockaddr *)&addrCli,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}


	if(connect(sock,(struct sockaddr *)&addrSrv,sizeof(struct sockaddr))==-1)
	{
		perror("connect");
		exit(1);
	}

	if(send(sock,argv[2],strlen(argv[2]),0)==-1)
	{
		perror("send");
		exit(1);
	}

	if((numbytes=recv(sock,buf,100,0))==-1)
	{
		perror("recv");
		exit(2);
	}
	buf[numbytes]='\0';

	if(strcmp(buf,"NOFILE")==0)
	{
		perror("no file!");
		exit(0);
	}
	else 
	{
		send(sock,"READY",5,0);
		char buffer[1024];
		int num=0;

		bzero(buffer,1024);	
		FILE *fp=fopen("/tmp/recv.txt","a");
		if(fp == NULL)
		{
			perror("file open fail");
			exit(1);
		}	
		while((num=recv(sock,buffer,1024,0))>0)
		{
			if(fwrite(buffer,sizeof(char),num,fp)<num)
			{
				perror("file write error");
				break;
			}
			bzero(buffer,1024);
		}
		printf("recevie file success");
		close(sock);
	}	
	exit(0);	
}

