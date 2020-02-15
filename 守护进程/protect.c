#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<time.h>	//时间头文件
#define MAXFILE 65535

volatile sig_atomic_t _running = 1;

void sigterm_handler(int arg)
{
	_running = 0;
}

int main()
{
	pid_t pc;
	int i,len;
	FILE *fd;
	pc = fork(); //第一步
	if(pc<0)
	{
		printf("error fork\n");
		exit(1);
	}
	else if(pc>0)
	exit(0);
	setsid(); //第二步
	chdir("/"); //第三步
	umask(0); //第四步
	for(i=0;i<MAXFILE;i++) //第五步
	close(i);
	signal(SIGTERM, sigterm_handler);
	while( _running)
	{
		fd = fopen("/tmp/dameon.log","a");
		if(fd>=0)
		{
			//时间
			time_t timep;
			struct tm *p;
			time(&timep);
			p=gmtime(&timep);
			fprintf(fd,"%d-%d-%d %d:%d:%d\n",p->tm_year+1900,p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
			//fprintf(fd,"\n");
			fclose(fd);
			system("top -b -n 1|grep -v ^top > /tmp/1.txt");
			system("sed -n '1p' /tmp/1.txt >> /tmp/dameon.log");
			sleep(30); //1
		}
	}
}
