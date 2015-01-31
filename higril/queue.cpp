#include "Queue.h"
#include <stdio.h>
void InitQueue(Queue *q) //��ʼ������
{
	q->front = q->rear = 0;
}
void EnQueue(Queue *q,ElemType e) //��Ԫ��e����
{
	if((q->rear + 1) % MAXSIZE == q->front) //��������
		return;
	q->data[q->rear] = e; //Ԫ��e����
	q->rear = (q->rear + 1) % MAXSIZE; //�α�rear��ǰ��һλ,����Ѵ����,���Ƶ�ǰ��
}
void DeQueue(Queue *q,ElemType *e) //��ͷ��Ԫ�س��Ӵ���*e
{
	if(q->rear == q->front) //�������Ϊ�շ���
		return;
	*e = q->data[q->front]; //���ض�ͷ��Ԫ��
	q->front = (q->front + 1) % MAXSIZE; //�α�front��ǰ��һλ,����Ƕ��е�ĩβ�ƶ�����ǰ��
}
bool IsEmpty(Queue *q) //�ж϶����Ƿ�Ϊ��
{
	return q->front == q->rear ? true : false;
}
int GetQueueLength(Queue *q) //���ض��еĳ���
{
	return (q->rear - q->front + MAXSIZE) % MAXSIZE;
}
void Clear(Queue *q) //��ն���
{
	q->front = q->rear = 0;
}
void Print(Queue *q) //��ӡ����
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