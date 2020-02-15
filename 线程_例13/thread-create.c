/*thread-create*/
#include<pthread.h>
#include<stdio.h>

/*线程执行函数char_print的参数*/
struct char_print_parms
{
	char character;		/*用于输出的字符*/
	int count;			/*输出的次数*/
};

/*线程直线型的函数，功能是输出参数所指内容*/
void* char_print(void* parameters)
{
	struct char_print_parms *p = (struct char_print_parms *) parameters;
	int i;
	for(i = 0; i < p->count; i++)
	{
		fputc(p->character, stderr);
		//printf("%c", p->character);
	}
	return NULL;
}

int main()
{
	pthread_t thread1_id;
	pthread_t thread2_id;
	struct char_print_parms thread1_args;
	struct char_print_parms thread2_args;
	
	/*创建一个输出30 000个x的线程*/
	thread1_args.character = 'x';
	thread1_args.count = 30000;
	pthread_create(&thread1_id, NULL, char_print, &thread1_args);
	
	/*创建一个输出20 000个o的线程*/
	thread2_args.character = 'o';
	thread2_args.count = 20000;
	pthread_create(&thread2_id, NULL, char_print, &thread2_args);
	
	   
	/*确保第一个线程结束*/
	pthread_join(thread1_id, NULL);
	
	/*确保第二个线程结束*/
	pthread_join(thread2_id, NULL);
	
	/*现在可以安全地返回*/
	return 0;
	
}

