#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

int main()
{
	FILE *fd;
	fd = fopen("fork.txt","a");
	
	if(fork())		//第一个进程
	{
		time_t timep;
		struct tm *p;
		time(&timep);
		p=gmtime(&timep);
		//printf("第一个进程的PID为： %d\n",(int)getpid());
		fprintf(fd,"第一个进程的PID号为：%d，创建时间为%d-%d-%d %d:%d:%d\n",(int)getpid(),p->tm_year+1900,p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	}
	else
	{
		if(fork())	//第二个进程
		{
			sleep(5);
			time_t timep;
			struct tm *p;
			time(&timep);
			p=gmtime(&timep);
			//printf("第二个进程的PID为： %d\n",(int)getpid());
			fprintf(fd,"第一个进程的PID号为：%d，创建时间为%d-%d-%d %d:%d:%d\n",(int)getpid(),p->tm_year+1900,p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
		}
		else		//第三个进程
		{
			sleep(10);
			time_t timep;
			struct tm *p;
			time(&timep);
			p=gmtime(&timep);
			//printf("第三个进程的PID为： %d\n",(int)getpid());
			fprintf(fd,"第一个进程的PID号为：%d，创建时间为%d-%d-%d %d:%d:%d\n",(int)getpid(),p->tm_year+1900,p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
		}
		
	}
	fclose(fd);
	
	return 0;
}
