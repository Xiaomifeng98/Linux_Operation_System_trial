#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

int sock;
static struct sockaddr_in addrCli;

void* solve(void)
{
	int new_fd;
	int sin_size=sizeof(struct sockaddr_in);
	perror("Server is run");
	if((new_fd=accept(sock,(struct sockaddr*)&addrCli,&sin_size))==-1)
	{
		perror("accpet");
		exit(1);
	}

	char buf[100];
	int num;
	if((num=recv(new_fd,buf,100,0))==-1)
	{
		perror("recv");
		exit(1);
	}

	buf[num]='\0';

	DIR *dirp;
	struct dirent *dp;
	int flag=0;

	dirp = opendir("/tmp");
	while((dp=readdir(dirp))!=NULL)
	{
		if(strcmp(dp->d_name,buf)==0)
		{
			flag=1;
		}
	}

	(void)closedir(dirp);
	if(flag)
	{
		printf("find %s success\n",buf);
		char file_name[512];
		char buffer[1024];

		bzero(file_name,512);
		sprintf(file_name,"/tmp/%s",buf);
		FILE *fp=fopen(file_name,"r");
		struct stat statbuf;		
		stat(file_name,&statbuf);		
		int size=statbuf.st_size;

		sprintf(buf,"FILELEN=%d",size);
		if(send(new_fd,buf,strlen(buf),0)==-1)
		{
			perror("send");
			exit(0);
		}
		num=recv(new_fd,buf,strlen(buf),0);
		buf[num]='\0';

		if(strcmp(buf,"READY")==0)
		{
			printf("Read success\n");
			if(fp == NULL)
				perror("open file error");
			int length=0;
			while((length=fread(buffer,sizeof(char),1024,fp))>0)
			{
				if(send(new_fd,buffer,length,0)<0)
				{
					printf("Send File error");
					break;
				}
				bzero(buffer,1024);

			}
		}

		fclose(fp);

	}
	else
	{
		printf("there is no %s\n",buf);
		strncpy(buf,"NOFILE",6);
		send(new_fd,buf,strlen(buf),0);
	}
	close(new_fd);
	exit(0);

}

int main(int argc,char **argv)
{
	struct sockaddr_in addrSrv;
	
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket");
		exit(0);
	}

	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(8000);
	addrSrv.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&(addrSrv.sin_zero),8);

	addrCli.sin_family=AF_INET;
	addrCli.sin_port=htons(81);
	addrCli.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&(addrCli.sin_zero),8);

	if(bind(sock,(struct sockaddr *)&addrSrv,sizeof(struct sockaddr))==-1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(sock,10)==-1)
	{
		perror("listen");
		exit(1);
	}

	pthread_t thread;
	pthread_create(&thread,NULL,(void *)solve,NULL);
	pthread_join(thread,NULL);
	close(sock);

	return 0;
}

