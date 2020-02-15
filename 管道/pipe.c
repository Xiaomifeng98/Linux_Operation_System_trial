/*pipe.c*/
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX_DATA_LEN 256
#define DELAY_TIME 1

int main()
{
	pid_t pid;
	int pipe_fd[2];		//管道读写描述符
	char buf[MAX_DATA_LEN];
	const char data[] = "Pipe Test Program";
	int real_read,real_write;
	
	memset((void * )buf, 0, sizeof(buf));
	/*创建管道*/
	if(pipe(pipe_fd) < 0)
	{
		printf("pipe create error\n");
		exit(1);
	}
	
	/*创建一个子进程*/
	if((pid = fork()) == 0)
	{/*子进程，读管道*/
		close(pipe_fd[1]);	//关闭写口
		sleep(DELAY_TIME * 3);
		/*读取管道内容*/
		if((real_read = read(pipe_fd[0], buf, MAX_DATA_LEN)) > 0)
		{
			printf("%d bytes read from the pipe is '%s'\n",real_read, buf);
		}
		close(pipe_fd[0]);	//关闭读口
		exit(0);
	}
	else if(pid > 0)
	{/*父进程，写管道*/
		close(pipe_fd[0]);	//关闭读口
		sleep(DELAY_TIME);
		/*写管道*/
		if((real_write = write(pipe_fd[1], data, strlen(data))) != -1)
		{
			printf("Parent wrote %d bytes : '%s'\n",real_write, data);
		}
		close(pipe_fd[1]);	//关闭写口
		/*等待子进程退出*/
		waitpid(pid, NULL, 0);
		exit(0);
	}
}
