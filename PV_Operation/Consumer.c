#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include"test.h"

int main()
{
	char * msg;
	int qid;
	key_t key1,key2,key3;
	int empty,full;
	if((key1=ftok(".",'a'))==-1)
	{
		perror("ftok");
		exit(1);
	}
	if((key2=ftok(".",'c'))==-1)
	{
		perror("ftok");
		exit(1);
	}
	if((key3=ftok(".",'b'))==-1)
	{
		perror("ftok");
		exit(1);
	}
	
	/*创建信号量empty和full*/
	if((empty=semget(key1,1,IPC_CREAT|0666))<0)printf("semerr1");
	if((full=semget(key2,1,IPC_CREAT|0666))<0)printf("semerr2");
	
	/*创建共享内存*/
	if((qid=shmget(key3,64,IPC_CREAT|0666))<0)printf("err1\n");
	
	/*将共享内存映射到私有空间，以后访问共享内存就直接用msg*/
	if((msg=(char*)shmat(qid,(void*)0,0))<0)printf("err2\n");
	while(1)
	{
		sem_p(full);
		printf("out:");
		puts(msg);
		sem_v(empty);
		if(strncmp(msg,"end",3)==0)break;
	}
	return 0;
}

