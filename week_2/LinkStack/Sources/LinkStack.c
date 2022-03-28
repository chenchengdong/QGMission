#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"LinkStack.h"

/*��ʼ��ջ*/
Status initLStack(LinkStack** s) {
	*s = (LinkStack*)malloc(sizeof(LinkStack));
	if (*s == NULL) {
		printf("�޷������ڴ�ռ䣡\n");
		return ERROR;                              //�ڴ治���򷵻�
	}
	(*s)->top = NULL;                              //��ʼ��ʹָ��ջ���Ľṹ��ָ���е�topָ�븳ΪNULL
	(*s)->count = 0;                               //ջ���Ľ�������Ϊ0
	printf("ջ��ʼ����ϣ�\n");
	return SUCCESS;
}

/*�ж�ջ�Ƿ�Ϊ�պ���*/
Status isEmptyLStack(LinkStack* s) {
	if (!s) {
		/*printf("ջδ��ʼ����\n");*/
		return UNUSUAL;
	}                                 //δ��ʼ��
	if (s->top == NULL) {
		/*printf("ջΪ��ջ��\n");*/       //��ջ�����
		return ERROR;
	}
	if (s->top != NULL) {
		/*printf("ջ��Ϊ��ջ��\n");*/
		return SUCCESS;             //��Ϊ��ջʱ
	}
}

/*�õ�ջ��Ԫ�غ���*/
Status getTopLStack(LinkStack* s, SElemType* e) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");
		return UNUSUAL;
	}
	if (check == 0) {
		printf("ջΪ��ջ��\n");
		return ERROR;
	}
	*e = s->top->data;
	printf("ջ��Ԫ��Ϊ��%d\n", s->top->data);
	return SUCCESS;
}

/*���ջ����*/
Status clearLStack(LinkStack* s) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");
		return UNUSUAL;
	}
	if (check == 0) {
		printf("ջΪ��ջ������Ҫ���\n");
		return ERROR;
	}
	SElemType assiss=0;
	while (s->top != NULL) {                     //����Ϊ��ջ������ó�ջ����������ջ
		popStack(s, &assiss);
	}
	return SUCCESS;
}

/*����ջ����*/
Status destroyLStack(LinkStack* s) {
	if (!s) {
		printf("ջ������ϣ�\n");
		return ERROR;          //������ζ��Ƿ���ERROR����ΪҪ�˳�����
	}
	if (s->top == NULL) {
		free(s);
		printf("����ջ��ϣ�\n");
		return ERROR;                //������ʾ�������ظ������ǿ�ջ����һ���ͷ���
	}
	clearLStack(s);
	free(s);
	printf("ջ������ϣ�\n");
	return ERROR;               //����ջ֮�󷵻�ERROR��0���������˳�����
}

/*���ջ���Ⱥ���*/
Status LStackLength(LinkStack* s, int* length) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");
		return UNUSUAL;
	}
	*length = s->count;
	printf("��ǰջ�ĳ���Ϊ��%d\n", *length);    //���ջ��
	return SUCCESS;
}

/*��ջ����*/
Status pushLStack(LinkStack* s, SElemType data) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");                   //ջδ��ʼ��ֱ�ӷ���
		return UNUSUAL;
	}
	StackNode* p1 = (StackNode*)malloc(sizeof(StackNode));
	p1->data = data;
	p1->next = NULL;
	if (check == 0) {
		s->top = p1;                             //ջδ��ջʱ��һ�������������
		s->count++;
		printf("��ջ��ϣ�\n");
		return SUCCESS;
	}
	p1->next = s->top;
	s->top = p1;
	s->count++;
	printf("��ջ��ϣ�\n");
	return SUCCESS;
}

/*��ջ����*/
Status popStack(LinkStack* s, SElemType* data) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");
		return UNUSUAL;                     //δ��ʼ��ֱ�ӷ���
	}
	if (check == 0) {
		printf("ջδ��ջ�����ܳ�ջ��\n");
		return ERROR;                    //��ջ���ܳ�ջ
	}
	LinkStackPtr p=s->top;
	s->top = s->top->next;
	s->count--;                       //��ջ�������1
	free(p);
	return SUCCESS;
}

/*������ջԪ�غ���*/
SElemType* StackElement(LinkStack*s) {             //�����÷���ָ��������Ϊ�˷�ֹ����-1ʱ��ջδ��ʼ���ķ���ֵ��ͻ����NULL���
	if (!s) {
		printf("ջδ��ʼ����\n");
		return NULL;
	}
	SElemType* element = (SElemType*)malloc(sizeof(SElemType));
	if (element == NULL) {
		printf("�޷������ڴ棡\n");
		return NULL;
	}
	int ret;
	printf("��������Ҫ��ջ������");                  //����������������ɺ���Ҫ��ջ��Ԫ�غ��ڵ�����������
	while (1) {
		ret=scanf("%d", element);
		printf("\n");
		rewind(stdin);                             //��մ������뻺��
		if (ret == 0) {
			printf("����������������룺");        //��������������������
		}
		if (ret == 1) {
			fflush(stdin);                       //����ȷ����������ѭ��
			break;
		}
	}
	return element;
}

/*�������ջԪ�غ���*/
Status TraverseLStack(LinkStack* s) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("ջδ��ʼ����\n");
		return UNUSUAL;                     //δ��ʼ��ֱ�ӷ���
	}
	if (check == 0) {
		printf("ջδ��ջ��û��Ԫ��\n");
		return ERROR;                    //��ջ���ܱ���
	}
	LinkStackPtr p = s->top;            //����һ�����ڱ�����ָ��
	printf("ջ��->ջβ\n");             
	while (p!= NULL) {
		printf("ջԪ�أ�%d\n",p->data);
		p = p->next;
	}
}

/*������*/
int main() {
	LinkStack* s = NULL;
	int judge = 1,check;
	SElemType e1,*e2,length;                    //�ֱ�Ϊ��ȡ��ջ��Ԫ��,��ջԪ�غ�ջ������
	while (judge) {
		printf("\n\n");
		printf("                         ******************************ϵͳ���ܲ˵�******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.��ʼ��ջ                **         2.�ж�ջ�Ƿ�Ϊ��ջ    *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.ջ��Ԫ��                **         4.���ջ              *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.����ջ(���˳�)          **         6.�鿴ջ�ĳ���        *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.��ջ����                **         8.��ջ����            *\n");
		printf("                              **************************************************************\n");
		printf("                              *                    9.�������ջԪ�أ�ջ��->ջ�ף�          *\n");
		printf("                              **************************************************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              ��ѡ��˵���ţ�");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);                                 //������մ������뻺��
			if (ret == 0) {
				printf("                         ����������������룺");
			}
			if (ret == 1) {
				fflush(stdin);
				break;
			}
		}
		system("cls");
		switch (option) {
		case 1:initLStack(&s); break;                          //��ʼ��ջ����
		case 2:
			check=isEmptyLStack(s);
			if (check == -1) printf("ջδ��ʼ����\n");          //�ж��Ƿ�Ϊ��ջ
			else if (check == 0) printf("ջΪ��ջ��\n");
			else printf("ջ��Ϊ��ջ��\n");
			break;
		case 3:getTopLStack(s, &e1); break;                      //���ջ��Ԫ�غ���
		case 4:
			check=clearLStack(s);
			if (check == 1) printf("���ջ��ϣ�\n");
			break;                                           //���ջ����
		case 5:judge=destroyLStack(s); break;         //����ջ����
		case 6:LStackLength(s, &length); break;       //���ջ��Ԫ��
		case 7:
			e2 = StackElement(s);
			if (e2 != NULL) {
				pushLStack(s, *e2);                     //��ջ����
			}
			break;
		case 8:
			check=popStack(s, &e1);
			if (check == 1) printf("��ջ��ϣ�\n");
			break;                 //��ջ����
		case 9:TraverseLStack(s); break;               //�������ջԪ��
		default:printf("������������ȷ�Ĳ˵�ѡ�"); break;
		}
		printf("�����������...");
		_getch();                                   //�ȴ��û�����
		system("cls");                              //����
	}
}