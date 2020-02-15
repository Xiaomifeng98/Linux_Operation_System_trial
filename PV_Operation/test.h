#include<sys/ipc.h>
#include<sys/sem.h>

/*信号量数据结构*/
union semun
{
	int val;
	struct semid_ds * buf;
	unsigned short * array;
};

/*将信号量sem_id的值初始化为ini_value*/
int init_sem(int sem_id, int init_value)
{
	union semun sem_union;
	sem_union.val = init_value;
	if (semctl (sem_id, 0, SETVAL, sem_union) == -1)
	{
		perror ("Initialize semaphore");
		return-1;
	}
	return 0;
}

/*删除信号量sem_id*/
int del_sem(int sem_id)
{
	union semun sem_union;
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
	{
		perror("Delete semaphore");
		return -1;
	}
}

/*对信号量sem_id进行P操作*/
int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		perror("P operation");
		return -1;
	}
	return 0;
}

/*对信号量sem_id进行V操作*/
int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		perror("V Operation");
		return -1;
	}
	return 0;
}

