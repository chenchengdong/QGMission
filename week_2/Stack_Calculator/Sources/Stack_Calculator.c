#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"Stack_Calculator.h"

/*��ʼ��ջ*/
int InitStack(Stack* s) {
	s->top = NULL;
	s->count = 0;
	return OK;
}

/*�ж�ջ�Ƿ�Ϊ��*/
int EmptyStack(Stack* s) {
	if (s->count == 0) {
		return ERROR;
	}
	if (s->count != 0) {
		return OK;
	}
}

/*��ջ*/
int Push(Stack* s, int e) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		return ERROR;
	}
	p->data = e;
	p->next = s->top;
	s->top = p;
	s->count++;
	return OK;
}

/*��ջ*/
int Pop(Stack* s) {
	int e;
	if (NULL == s->top) {             //��ʱΪ��ջ
		return ERROR;
	}
	Node* p = s->top;
	e = p->data;
	s->top = p->next;
	free(p);
	s->count--;
	return e;                       //���س�ջԪ��
}

/*��ȡջ��Ԫ��*/
int GetTop(Stack* s) {
	if (NULL == s->top) {
		return ERROR;            //��ʱΪ��ջ
	}
	return (s->top->data);      //����ջ��Ԫ��
}

/*���ȼ��ж�*/
int Priority(char s) {
	switch (s) {
	case '(':            //Ϊ���ַ��ŷ������ȼ�
		return 0;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

int main() {
	Stack num, opt;                 //׼������ջ
	int judge = 1;
	while (judge) {
		printf("����������Ҫ����Ĺ�ʽ����λ���ļӼ��˳�!!�������Ϊ���������� ");
		char str1[100] = { 0 };            //׼������������
		char str2[100] = { 0 };
		scanf("%s", str1);                 //����
		int i = 0, j = 0, a, b, c, tem;
		InitStack(&num);                //��ʼ������ջ��һ�����ڴ����׺��һ�����ڴ�ź�׺
		InitStack(&opt);
		for (; str1[i] != '\0'; i++) {
			if (str1[i] >= '0' && str1[i] <= '9') {
				str2[j++] = str1[i];                    //����ʱֱ���������һ������
				continue;
			}
			if ((str1[i] < '0' || str1[i]>'9') && (EmptyStack(&num) == 0)) {
				Push(&num, str1[i]);                //��Ϊ�����ҵ�ǰΪ��ջʱ��ֱ����ջ
				continue;
			}
			if ((str1[i] < '0' || str1[i]>'9') && (EmptyStack(&num) == 1)) {
				if (str1[i] == '(') {
					Push(&num, str1[i]);         //��Ϊ�����Ҳ�Ϊ��ջʱ����ջ��Ԫ�������ȼ��жϣ��������ջ������ջ��С�ڵ��ڶ�Ҫһֱ��ջ֪��ջ��С����ջԪ�����ȼ�
					continue;                  //����������������� ʱֱ����ջ
				}
				a = GetTop(&num);
				b = Priority(a);
				c = Priority(str1[i]);
				if (c >b) {
					Push(&num, str1[i]);           //�����ȼ����ڵ���ջ�������ջ
					continue;
				}
				if (c <= b) {
					for (; tem = GetTop(&num), Priority(tem) >= c;) {
						if (tem == '(') {
							Pop(&num);
							break;
						}
						str2[j++] = tem;
						Pop(&num);                                  //�����ȼ�С��ջ������ջ����ջһֱ����С�ڡ��·��ŵ����ȼ�ʱ��ͣ
						if (EmptyStack(&num) == 0) {
							break;
						}
					}
					if (str1[i] == ')') {  //������ջΪ �� ʱ��������ջ
						continue;
					}
					Push(&num, str1[i]);   //�������Ŷ�Ҫ��ջ
				}
			}
		}
		while (EmptyStack(&num) != 0) {
			str2[j++] = Pop(&num);
		}
		//��׺���ʽ����
		int k = 0, d, e, final;          //����һ�����ڱ�����׺���ʽ�ı���k��������������ı���d,e,��һ��������������final
		for (; str2[k] != '\0'; k++) {
			if (str2[k] >= '0' && str2[k] <= '9') {
				Push(&opt, str2[k]);
				continue;                              //����������ֱ�ӽ�ջ
			}
			if (str2[k] < '0' || str2[k]>'9') {        //�����������������������
				d = Pop(&opt);
				if (d >= '0' && d <= '9') {
					d = d - '0';                 //����ascii�����ֻ���
				}
				e = Pop(&opt);
				if (e >= '0' && e <= '9') {
					e = e - '0';              //����ascii�����ֻ���
				}
				switch (str2[k]) {         //��������
				case '+':
					Push(&opt, (e + d));
					break;
				case '-':
					Push(&opt, (e - d));
					break;
				case '*':
					Push(&opt, (e * d)); break;
				case '/':
					Push(&opt, (e / (d * 1.0))); break;   //����������ջ
				}
			}
		}
		final = Pop(&opt);
		printf("���Ϊ�� %d\n", final);
		printf("�����������...");
		_getch();
		system("cls");
		printf("�Ƿ�Ҫ�������㣿���밴1�����밴0 ��  ");
		scanf("%d", &judge);
		printf("�����������...");
		_getch();
		system("cls");
	}
}