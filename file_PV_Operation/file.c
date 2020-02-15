#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>

int lock_set(int fd,int type)
{
	struct flock lock;
	lock.l_whence=SEEK_SET;
	lock.l_start=0;
	lock.l_len=0;
	lock.l_type=type;
	lock.l_pid=-1;
	fcntl(fd,F_GETLK,&lock);
}

int main()
{
	FILE *fp;
	int i,n,ch;
	char buf[10];
	
	fp=fopen("test.txt","r");
	lock_set(fp->_fileno,F_RDLCK);
	fgets(buf,10,fp);
	i=0;
	while(buf[i]>='0'&&buf[i]<='9')
		i++;
	buf[i]='\0';
	n=atoi(buf);
	fclose(fp);
	printf("The number in file is %d\n",n);
	lock_set(fp->_fileno,F_UNLCK);

	for(i=1;i<=50;i++)
	{
		fp=fopen("test.txt","w");
		lock_set(fp->_fileno,F_WRLCK);
		n+=1;
		sprintf(buf,"%d",n);
		printf("%s\n",buf);
		fputs(buf,fp);
		fclose(fp);
		lock_set(fp->_fileno,F_UNLCK);
	}
	return 0;
}

