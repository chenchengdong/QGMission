#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"duLinkedList.h"

DuLinkedList headNode() {                       //����һ����ͷ��㺯��
	DuLinkedList head;
	if ((head = (DuLinkedList)malloc(sizeof(DuLNode))) == NULL) {
		printf("�ڴ治��!\n");
	}
	head->prior = NULL;
	head->next = NULL;
	return head;
}

/*������������*/
DuLinkedList InitList_DuL(DuLinkedList L) {
	printf("��ʼ������ɹ�!\n");
	printf("����������Ҫ�����Ľ�����:\n");
	int num,ret;
	while (1) {
		ret = scanf("%d", &num);
		rewind(stdin);                   //����������Ĵ�������
		printf("\n");
		if (ret == 0) {
			printf("�������!����������:");

		}
		if (ret == 1 && num < 0) {
			printf("���벻Ϊ��ȷ������!����������:");
		}
		if (ret == 1 && num >= 0) {
			fflush(stdin);
			break;                         //������ȷ��������˳�ѭ��
		}
	}
	if (num == 0) {
		return L;			//������������Ϊ0ʱ
	}
	DuLinkedList p1 = NULL, p2 = NULL;
	int i;
	for (i = 1; i <= num; i++) {
		if ((p1 = (DuLinkedList)malloc(sizeof(DuLNode))) == NULL) {
			printf("�ڴ治��!\n");
		}
		printf("�������%d������ֵ:", i);
		while (1) {
			ret = scanf("%d", &p1->data);
			rewind(stdin);                   //��ջ������Ĵ�������
			printf("\n");
			if (ret == 0) {
				printf("�������!�����������%d������ֵ:", i);

			}
			if (ret == 1) {
				fflush(stdin);
				break;                         //������ȷ��������˳�ѭ��
			}
		}
		if (i == 1) {
			p2 = p1;
			L->next = p1;  //��ͷ���ĺ�����һ����������
			p1->prior = L; //��һ������ǰ�������ڱ�ͷ��
		}
		else {
			p2->next = p1;  //�ڶ������ĺ�����ӵ��������
			p1->prior = p2;	//����������ǰ�����ӵڶ������
			p2 = p1;       //p2�ƶ���p1��
		}
	}
	p2->next = NULL;    //���һ�����ָ��գ���ʱ���������
	return L;
}

/*ɾ������������*/
ElemType DestroyList_Dul(DuLinkedList* L) {
	if ((*L) == NULL) return ERROR;
	DuLinkedList p1 = NULL, p2 = NULL;   //p1���ڶ�λҪɾ�����
	p1 = (*L)->next;
	while (p1 != NULL) {
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	(*L)->next = NULL;
	return ERROR;

}

/*�����㣨ǰ�˲��룩����*/
ElemType InsertBeforeList_DuL(DuLinkedList* L) {
	if ((*L) == NULL) {
		printf("δ��ʼ������~\n");
		return ERROR;
	}
	DuLinkedList p1 = (*L)->next;
	DuLNode* p = NULL, * q = NULL;
	int ret;                                    //�����ж��Ƿ���ȷ����
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	q = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	q->next = NULL, q->prior = NULL;
	printf("����������Ҫ�����λ�õ�����:");
	ret=scanf("%d", &p->data);
	rewind(stdin);                      //��ջ������Ĵ�������
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;
	}
	printf("\n����������Ҫ���������:");
	ret=scanf("%d", &q->data);
	rewind(stdin);
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;
	}
	while (p1 != NULL) {
		if (p1->data == p->data) {
			q->next = p1;
			q->prior = p1->prior;
			p1->prior->next = q;
			p1->prior = q;
			return SUCCESS;
		}
		p1=p1->next;
	}
	printf("û���ҵ���Ҫ�����λ����~\n");
	return ERROR;
}

/*�����㣨��˲��룩����*/
ElemType InsertAfterList_DuL(DuLinkedList* L) {
	if ((*L) == NULL) {
		printf("δ��ʼ������~\n");
		return ERROR;
	}
	DuLinkedList p1 = (*L)->next;
	DuLNode* p = NULL, * q = NULL;
	int ret;                                       //�����ж��Ƿ���ȷ����
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	q = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	q->next = NULL, q->prior = NULL;
	printf("����������Ҫ�����λ�õ�����:");
	ret=scanf("%d", &p->data);
	rewind(stdin);
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;
	}
	printf("\n����������Ҫ���������:");
	ret=scanf("%d", &q->data);
	rewind(stdin);
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;                         //�Ƿ�����ֱ�ӷ���
	}
	while (p1 != NULL&&p1->next!=NULL) {                //���������һ��λ�ò�����߿ս��ʱ����  �������
		if (p1->data == p->data) {
			q->prior = p1;
			q->next = p1->next;
			p1->next->prior = q;
			p1->next = q;
			return SUCCESS;
		}
		p1 = p1->next;
	}
	if (p1 == NULL) {
		printf("û���ҵ���������λ����~\n");              //��ֻ��һ����ͷ���ʱ���޷�����
		return ERROR;
	}
	if ((p1->next == NULL) && (p1->data == p->data)) {   //��Ҫ����ĵط�Ϊ��βʱ����������
		p1->next = q;
		q->prior = p1;
		q->next = NULL;
		return SUCCESS;
	}
	printf("û���ҵ�����Ҫ����ֵ��λ����~\n");
	return ERROR;
}

/*ɾ����㲢ȡֵ*/
ElemType DeleteList_DuL(DuLinkedList L, ElemType *e) {
	if (L == NULL) {
		printf("δ��ʼ������~\n");
		return ERROR;                      //δ��ʼ������ֱ�ӷ���
	}
	DuLinkedList p1 = L->next,p2 = NULL;    //p2����ָ���Ǹ���ɾ���Ľ��
	DuLinkedList p=NULL;
	int ret;                                   //�����жϷǷ�����
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	printf("��������Ҫɾ������ǰ��������:");
	ret=scanf("%d", &p->data);
	rewind(stdin);
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;
	}
	while (p1 != NULL&&p1->next!=NULL) {        //����Ҫɾ��ֵ��ǰһ��ֵ��������һ��ֵ�����޷�ɾ��
		if (p1->data == p->data) {
			*e = p1->next->data;
			p2 = p1->next;
			p1->next = p2->next;
			p2->next->prior = p1;   //��Ҫɾ���Ľ���ǰһ��������һ�������������
			printf("ɾ��������Ϊ:%d\n\n", p2->data);
			free(p2);
			return SUCCESS;
		}
		p1 = p1->next;
	}
	printf("û���ҵ���Ҫɾ����ֵ����˼��������ɾ���~\n");       //û�ҵ�ֵ����     
	return ERROR;
}

/*���������*/
void TraverseList_DuL(DuLinkedList L) {
	if (L == NULL) {
		printf("δ��ʼ������~\n");
		return;                  //δ��ʼ�����������ֱ�ӷ���
	}
	DuLinkedList p1 = L->next;
	printf("��ǰ����Ϊ:");
	while (p1 != NULL) {
		printf("%d->", p1->data);
		p1 = p1->next;
	}
	printf("NULL");
	printf("\n\n");
}





int main() {
	DuLinkedList L = NULL;    //��������ָ���ͷ����ָ��
	int e1 = 0;               //�������ڷ���ɾ��ֵ����
	int judge = 1;
	while (judge) {
		printf("\n\n");
		printf("                    ******************************ϵͳ���ܲ˵�******************************\n");
		printf("                    -----------------------------------------------------------------------\n");
		printf("                         *************************************************************\n");
		printf("                         * 1.����������                **       2.���������˳����� *\n");
		printf("                         *************************************************************\n");
		printf("                         * 3.�����½�㣨ǰ�β��룩    **     4.�����½��(��˲���) *\n");
		printf("                         *************************************************************\n");
		printf("                         * 5.ɾ�����ȡֵ              **       6.�������           *\n");
		printf("                    -----------------------------------------------------------------------\n");
		printf("                    ��ѡ��˵����:");
		int option,ret;
		while (1) {
			ret = scanf("%d", &option);
			rewind(stdin);                  //��ջ�������������
			printf("\n");
			if (ret == 0) {
				printf("�������!����������:");
			}
			if (ret == 1 && (option < 1 || option>6)) {
				printf("�������!����������:");
			}
			if (ret == 1 && (option >= 1 && option <= 6)) {
				fflush(stdin);
				break;                      //������ȷ������˳�ѭ��
			}
		}
		system("cls");
		switch (option) {
		case 1:L = InitList_DuL(headNode()); break;
		case 2:judge=DestroyList_Dul(&L); break;
		case 3:InsertBeforeList_DuL(&L); break;
		case 4:InsertAfterList_DuL(&L); break;
		case 5:DeleteList_DuL(L, &e1); break;
		case 6:TraverseList_DuL(L); break;

		}
		printf("�����������...");
		_getch();
		system("cls");
		if (judge != 0)judge = 1;
	}

}