#include "Queue.h"
#include <stdio.h>
void InitQueue(Queue *q) //初始化队列
{
	q->front = q->rear = 0;
}
void EnQueue(Queue *q,ElemType e) //让元素e进队
{
	if((q->rear + 1) % MAXSIZE == q->front) //队列已满
		return;
	q->data[q->rear] = e; //元素e进队
	q->rear = (q->rear + 1) % MAXSIZE; //游标rear上前进一位,如果已达最后,就移到前面
}
void DeQueue(Queue *q,ElemType *e) //队头的元素出队存入*e
{
	if(q->rear == q->front) //如果队列为空返回
		return;
	*e = q->data[q->front]; //返回队头的元素
	q->front = (q->front + 1) % MAXSIZE; //游标front向前移一位,如果是队列的末尾移动到最前面
}
bool IsEmpty(Queue *q) //判断队列是否为空
{
	return q->front == q->rear ? true : false;
}
int GetQueueLength(Queue *q) //返回队列的长度
{
	return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}
void Clear(Queue *q) //清空队列
{
	q->front = q->rear = 0;
}
void Print(Queue *q) //打印队列
{
	if(q->front == q->rear)
		return;
	else if(q->rear < q->front)
	{
		for(int i = q->front;i < MAXSIZE;++i)
			printf("%d ",q->data[i]);
		for(int i = 0;i < q->rear;++i)
			printf("%d ",q->data[i]);
		printf("\n");
	}
	else{
		for(int i = q->front;i < q->rear;++i)
			printf("%d ",q->data[i]);
		printf("\n");
	}
}