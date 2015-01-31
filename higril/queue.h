/*	队列是一种先进先出的线性表,具有线性表的特性:分为链式队列与顺序队列
	顺序队列:用一段地址连续的存储单元存储数据元素，定义两个游标:指向队头
	的游标(front)、指向队尾的游标(rear),如果front == rear队列为空,如果
	(rear + 1) % MAXSIZE == front队列满(此为循环队列),如普通队列rear==MAXSIZE队列满 */

#ifndef QUEUE_H
#define QUEUE_H
#define MAXSIZE 1024  //队列的最大长度
typedef char ElemType; //队列的数据类型
typedef struct{
	ElemType data[MAXSIZE]; //队列
	int front; //队头的游标
	int rear;  //队尾的游标
}Queue;

void InitQueue(Queue *q); //初始化队列

void EnQueue(Queue *q,ElemType e); //元素e进队

void DeQueue(Queue *q,ElemType *e); //队头的元素出队

bool IsEmpty(Queue *q); //判断队列是否为空

int GetQueueLength(Queue *q); //返回队列的长度

void Clear(Queue *q); //清空队列

void Print(Queue *q); //打印队列

#endif //QUEUE_H