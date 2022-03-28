#define OK 1
#define ERROR 0
#define UNUSUAL -1

typedef struct node {         //定义结构体
	int data;
	struct node* next;
}Node;

typedef struct stack {     //定义栈顶结构体指针
	Node* top;
	int count;
}Stack;
#pragma once
