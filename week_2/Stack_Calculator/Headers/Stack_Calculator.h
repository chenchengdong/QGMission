#define OK 1
#define ERROR 0
#define UNUSUAL -1

typedef struct node {         //����ṹ��
	int data;
	struct node* next;
}Node;

typedef struct stack {     //����ջ���ṹ��ָ��
	Node* top;
	int count;
}Stack;
#pragma once
