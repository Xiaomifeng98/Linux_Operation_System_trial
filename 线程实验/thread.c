#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

int num=0;
int total=0;
pthread_mutex_t mutex;


void* r_w(void* arg)
{
	int p_id=*((int *)arg);
	FILE *f,*f2;
	char buf[1024],add[10];
	int i,n;


	


	while(num<total)
	{
if((f=fopen("test.txt","a+"))==NULL)
		{
			perror("open file error!");
			return NULL;
		}
		if((f2=fopen("test2.txt","a"))==NULL)
		{
			perror("open file error!");
			return NULL;
		}
		strcpy(buf,"");strcpy(add,"");
		n=0;
	 	pthread_mutex_lock(&mutex);

		rewind(f);
		int ch;
		for(i=0;i<num;i++)
		{
			fscanf(f,"%*[^\n]%*c");
		}
		while((ch=fgetc(f))=='*')
		{
			buf[n++]=ch;
		}
		buf[n]='\0';
		sprintf(add,"(%d,id=%d)\n",n,p_id);
		strcat(buf,add);
		fwrite(buf,1,strlen(buf),f2);	
		num++;

		pthread_mutex_unlock(&mutex);
		fclose(f);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t p1,p2,p3;
	int p1_id=1,p2_id=2,p3_id=3;
	int ch;
	FILE *file;

	file=fopen("test.txt","r");
	while((ch=fgetc(file))!=EOF)
		if(ch=='\n')
			total++;

	fclose(file);
	printf("%d\n",total);

	pthread_mutex_init(&mutex,NULL);
	pthread_create(&p1,NULL,r_w,&p1_id);
	pthread_create(&p2,NULL,r_w,&p2_id);
	pthread_create(&p3,NULL,r_w,&p3_id);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	return 0;
}

