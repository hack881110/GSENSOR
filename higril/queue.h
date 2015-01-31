/*	������һ���Ƚ��ȳ������Ա�,�������Ա������:��Ϊ��ʽ������˳�����
	˳�����:��һ�ε�ַ�����Ĵ洢��Ԫ�洢����Ԫ�أ����������α�:ָ���ͷ
	���α�(front)��ָ���β���α�(rear),���front == rear����Ϊ��,���
	(rear + 1) % MAXSIZE == front������(��Ϊѭ������),����ͨ����rear==MAXSIZE������ */

#ifndef QUEUE_H
#define QUEUE_H
#define MAXSIZE 1024  //���е���󳤶�
typedef char ElemType; //���е���������
typedef struct{
	ElemType data[MAXSIZE]; //����
	int front; //��ͷ���α�
	int rear;  //��β���α�
}Queue;

void InitQueue(Queue *q); //��ʼ������

void EnQueue(Queue *q,ElemType e); //Ԫ��e����

void DeQueue(Queue *q,ElemType *e); //��ͷ��Ԫ�س���

bool IsEmpty(Queue *q); //�ж϶����Ƿ�Ϊ��

int GetQueueLength(Queue *q); //���ض��еĳ���

void Clear(Queue *q); //��ն���

void Print(Queue *q); //��ӡ����

#endif //QUEUE_H