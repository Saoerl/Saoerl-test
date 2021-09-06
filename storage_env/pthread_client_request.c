#include "global.h"

extern pthread_cond_t cond_sqlite;
extern pthread_cond_t cond_uart_cmd;
extern pthread_mutex_t mutex_sqlite;
extern pthread_mutex_t mutex_uart_cmd;


void *pthread_client_request(void *arg)
{
	//定义消息队列结构体
	struct msg msgsz;

	key_t key = ftok("/home",1);
	if(key < 0)
	{
		ERR_MSG("ftok");
		return NULL;
	}

	int msqid = msgget(key,IPC_CREAT|0664);
	if(msqid < 0)
	{
		ERR_MSG("msgget");
		return NULL;
	}

	while(1)
	{
		ssize_t size = msgrcv(msqid, &msgsz, sizeof(msgsz.text), 0, 0);
		if(size < 0)
		{
			ERR_MSG("msgrcv");
			return NULL;
		}

		printf("type = %ld\ntext = %s\n",msgsz.msgtype,msgsz.text);

		switch(msgsz.msgtype)
		{
		case 1:
			//LED数码管
			break;
		case 2:
			//风扇
			//pthr
			break;
		case 3:
			//蜂鸣器
			//条件变量
			break;
		case 4:
			//数据库最大最小值更新
			//条件变量
			break;
		case 5:
			//M0控制线程
			//条件变量
			break;

		}
	}
	return 0;
}
