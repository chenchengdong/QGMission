#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"linkList.h"


/*��ʼ��������*/
LinkedList InitList(LinkedList L) {
	printf("��ʼ������ɹ���\n");
	printf("����������Ҫ�����Ľ�������");
	int num,ret; /*�������ڼ��Ƿ�����ı���*/
	while (1) {
		ret = scanf("%d", &num);         /*���Ƿ����뷵��ֵΪ0*/
		rewind(stdin);                   /*��ջ������Ĵ�������*/
		printf("\n");
		if (ret == 0) {
			printf("�������!����������:");
		}
		if (ret == 1 && num < 0) {                    /*����������ĸ���Ϊ�����������Ƿ����봦��*/
			printf("���벻Ϊ��ȷ������!����������:");
		}
		if (ret == 1&&num>=0) {
			fflush(stdin);
			break;                         /*������ȷ��������˳�ѭ�������봴����㲿��*/
		}
	}
	if(num==0){           /*��������������봴���Ľ��Ϊ0ʱ,��ʱֻ��һ����ͷ���*/
		return L;
	} 
	LinkedList p1 = NULL, p2 = NULL; /*�������ڴ���������ӳ�����Ľṹ��ָ��*/
	int i;
	for (i = 1; i <= num; i++) {
		if ((p1 = (LinkedList)malloc(sizeof(LNode))) == NULL) {
			printf("CAN NOT CREATE NODE FOR YOU\n");
		}
		printf("�������%d������ֵ:", i);
		while (1) {
			ret=scanf("%d", &p1->data);
			rewind(stdin);                   /*��ջ������Ĵ�������*/
			printf("\n");
			if (ret == 0) {
				printf("�������!�����������%d������ֵ:",i);
			}
			if (ret == 1) {
				fflush(stdin);
				break;                         /*������ȷ��������˳�ѭ��*/
			}
		}
		if (i == 1) {
			p2 = p1;
			L->next = p1;                     /*��ͷ��������ڵ�һ�����ǰ*/
		}                                     /*����ǵ�һ����㣬��p2, p1ָ��ͬһ�����*/
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	p2->next = NULL;
	return L;
}


/*����������*/
ElemType DestroyList(LinkedList* L) {
	if ((*L) == NULL) return 0;             /*δ��ʼ������ֱ���˳�����*/
	LinkedList p1 = NULL, p2 = NULL;
	p1 = (*L)->next;
	while (p1 != NULL) {
		p2 = p1->next;		               /*p2����ָ��λ��p1�ĺ��*/
		free(p1);			              /*�ͷ�p1���ڽ��ռ�*/
		p1 = p2;				         /*p1ָ��p2���ڽ��--���ѭ������ɾ������*/
	}
	(*L)->next = NULL;
	return 0;
}

/*�����㺯��*/
LinkedList InsertList(LinkedList* L) {
	if ((*L) == NULL) {
		printf("δ��ʼ������\n");
		return (*L);                                   /*δ��ʼ������ֱ�ӷ���*/
	}
	LNode* p, * q;
	int ret;                                          /*���ڼ��Ƿ�����*/
	p = (LNode*)malloc(sizeof(LNode));                /*ѭ������Ҳ���Բ���ֵ��ֻ������������*/
	q = (LNode*)malloc(sizeof(LNode));
	p->next = NULL, q->next = NULL;
	printf("����������Ҫ����λ�õ�ǰһ������:");
	ret=scanf("%d", &p->data);
	rewind(stdin);                   /*��ջ������Ĵ�������*/
	if (ret == 0) {
		printf("���벻��ȷ!\n");        /*�Ƿ�����ֱ�ӷ��ؽṹ��ָ��*/
		return (*L);
	}
	printf("\n����������Ҫ���������:");
	ret=scanf("%d", &q->data);
	rewind(stdin);                   /*��ջ������Ĵ�������*/
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return (*L);                //�Ƿ�����ֱ�ӷ���
	}
	LinkedList p1 = (*L)->next;
	while (p1 != NULL) {                //�޸�����  p1->next����Ϊ��
		if (p1->data == p->data) {
			q->next = p1->next;			//�Ƚ�q���ӵ�p1�ĺ�� 
			p1->next = q; 				//�ٽ�q��p1���ӣ�ʹ���Ϊp1�ĺ��
			printf("�������!\n");
			return (*L);                //������֮�����̷���
		}
		p1 = p1->next;
	}
	printf("û���ҵ�����λ�õ�ֵŶ~\n��˼�����������԰�\n");
	return (*L);
}

/*ɾ����㲢ȡֵ�ĺ���*/
LinkedList DeleteList(LinkedList L, ElemType* e) {
	if (L == NULL) {
		printf("δ��ʼ������Ŷ~\n");
		return L;                             //δ��ʼ������ֱ�ӷ���
	}
	LinkedList p1 = L->next,p2=NULL;         //����p2����ָ���Ǹ���ɾ��������         
	LNode* p;                                //ѭ������Ҳ��������ɾ��ֵ
	int ret;                                    //�����ж��Ƿ���ȷ����
	p = (LinkedList)malloc(sizeof(LNode));
	p->next = NULL;
	printf("��������Ҫɾ������ǰ��������:");
	ret=scanf("%d", &p->data);                 //����һ�������װ��Ҫɾ����ֵ
	rewind(stdin);                       //��ջ������Ĵ�������
	if (ret == 0) {
		printf("���벻��ȷ!\n");           //�Ƿ�����ֱ�ӷ���
		return L;
	}
	while (p1 != NULL&&p1->next!=NULL) {
		if (p1->data == p->data) {
			*e = p1->next->data;           //����p����ֵ 
			p2 = p1->next;
			p1->next = p1->next->next;    //������p�����ߵĽ���������� 
			printf("ɾ��������Ϊ:%d\n\n", p2->data);
			free(p2);
			return L;                   //ɾ��������֮��������̷�����
		}
		p2 = p1;                        //����p2���������ã�1�Ǳ�����p1��ǰһ����㴦��2���ڷ�����Ҫɾ����ֵλ���м�ʱ�����ɾ��ָ��
		p1 = p1->next;
	}
	//if (p1->next == NULL && (p1->data == p->data)) {
	//	p2 = NULL;						//�����������ʱ��������������1.����պñ�������β  2.��Ҫɾ���Ľ����Ǹý��  ע��p2����ɾ�����м�Ľ����������p1ǰһ�����
	//	free(p1); 
	//	return L;
	//}
	printf("û���ҵ���Ҫɾ����ֵ,������˼����������ɾ���~\n");    //���û�д�����ѭ����return���أ����ж�Ϊû�ҵ�ɾ��ֵ��ǰһ��ֵ������ԭ����
	return L;
}

/*��ѯ��㺯��*/
ElemType SearchList(LinkedList L) {
	if (L == NULL) {
		printf("δ��ʼ������Ŷ~\n");
		return ERROR;                       //δ��ʼ��������
	}
	LinkedList p1 = L->next;
	int e,ret;                               //ret�����ж��Ƿ�Ƿ�����
	printf("����������Ҫ��ѯ��ֵ:");
	ret=scanf("%d", &e);
	rewind(stdin);                       //��ջ������Ĵ�������
	if (ret == 0) {
		printf("���벻��ȷ!\n");
		return ERROR;                 //�Ƿ�����ֱ�ӷ���
	}
	while (p1 != NULL) {
		if (p1->data == e) {
			printf("%d����������\n",e);
			return SUCCESS;
		}
		p1 = p1->next;
	}
	printf("%d������������", e);
	return ERROR;
}

/*����������*/
ElemType ReverseList(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("�����𻵣��޷�����\n");
		return ERROR;                                          //�ж��Ƿ�Ϊѭ�������������޷�����
	}
	if ((*L) == NULL) {
		printf("δ��ʼ������Ŷ~\n");
		return (*L);                                          //Ϊ��ʼ������ֱ�ӷ���
	}
	LinkedList cur = (*L)->next, p1 = cur->next, nex = NULL;  //cur��ʾp1��ǰ�̽�㣬nex��ʾp1�ĺ�̽�� 
	/*Status cheak1;*/
	if (!cur) {
		printf("��û�������Ŷ~\n");
		return ERROR;       //ֻ��һ��ͷ���ʱ���޷����򣬷���0 
	}
	while (p1 != NULL) {
		nex = p1->next;
		p1->next = cur;
		if ((*L)->next == cur) {
			cur->next = NULL;			//���cur��ǰ����ͷ���Ļ�����cur��nextָ��NULL 
		}
		cur = p1;					//cur�ƶ���p1�� 
		p1 = nex;					//p1�ƶ���nex�� 
	}
	(*L)->next = cur;            //��ͷ�����������������������
	printf("�������!\n");
	return SUCCESS;              //�����귵�سɹ�success
};

/*�жϳɻ�����*/
ElemType IsLoopList(LinkedList L) {
	if (L == NULL) {
		printf("��û�г�ʼ������Ŷ~\n");
		return ERROR;                            //��û�г�ʼ������ʱֱ�ӷ���
	}
	LinkedList fast = L->next, slow = L->next;    //��ʼʱ��ָ���һ�������ݵĽ��
	
	if (!fast) {
		printf("����ѭ������!\n");
		return ERROR;          //���ֻ��һ��ͷ��㣬�Ҳ�Ϊѭ�������򷵻�0
		
	}
	if (fast->next == fast) {
		printf("��ѭ������!\n");
		return SUCCESS;        //���ֻ��һ��ͷ��㣬����Ȼ�Ǹ�ѭ�������򷵻�1 
	}
	while (fast!=NULL && fast->next!=NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (fast == NULL || slow == NULL) {
			printf("����ѭ������!\n");
			return ERROR;				//���fast����slow�����˵���NULL����������ж�Ϊ����ѭ������ 
		}
		if (fast == slow || fast->next == slow) {
			printf("��ѭ������!\n");
			return SUCCESS;					//���fast׷�Ͽ�slow�����ܵ���slow�ĺ��棬��Ϊѭ������ 
			
		}
		
	}
	printf("����ѭ������!\n");
}

/*�ҵ�������м��㺯��*/
LNode* FindMidNode(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("�����𻵣��޷�����\n");
		return (*L);                                          //�ж��Ƿ�Ϊѭ�������������޷�����
	}
	if ((*L) == NULL) {
		printf("δ��ʼ������Ŷ~\n");                                //Ϊ��ʼ������ʱ�Ҳ����е����ݣ�ֱ�ӷ���
		return(*L);
	}
	LinkedList fast = (*L)->next, slow = fast;                         //����һ����ָ��һ����ָ��
	if (!fast) {
		return 0;                   //���ֻ��һ��ͷ��㣬�򷵻�0 
	}
	while (slow!=NULL) {
		if (fast->next == NULL || fast->next->next == NULL) {       //��fastָ��ĺ��Ϊ��βʱ����ʱΪż��������������ĵ�һ���е� 
			break;                                 //��fastָ���ߵ���βʱ����ʱΪ�����������������е� 
		}
		fast = fast->next->next;     //fastָ��һ�������� 
		slow = slow->next;           //slowָ��һ����һ�� 
	}
	printf("�е�����Ϊ:%d\n\n", slow->data);
	return slow;
}

/*�������ż�Ի�����*/
LNode* ReverseEvenList(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("�����𻵣��޷�����\n");
		return (*L);                                          //�ж��Ƿ�Ϊѭ�������������޷�����
	}
	if ((*L) == NULL) {
		printf("δ��ʼ������Ŷ~\n");
		return(*L);                                         //δ��ʼ�������ֱ�ӷ���
	}
	LinkedList p1 = (*L)->next;
	if (p1 == NULL) { 
		printf("��û�д������Ŷ~\n�������޷���ż�Ի���~\n");
		return 0;                       //�ų�ֻ��һ����ͷ����������޷���ż�Ի�
	}
	LinkedList p2 = p1->next;	         //p1ָ��������㣬p2ָ��ż�����
	
	int tem = 0;                        //���ڽ�����ż���ֵ���м����
	while (p2!=NULL&&p2->next!=NULL) {
		tem = p1->data;
		p1->data = p2->data;
		p2->data = tem;              //����ż���������һ�¼��� 
		p1 = p1->next->next;			//p1��p2ÿ�ζ������������� 
		p2 = p2->next->next;
	}
	if (p2 == NULL) {
		printf("��ż��ת���!\n");
		return (*L);				//����p2ָ��ż��λ���Ľ�㣬����p2����ȵ���NULL����NULL��ǰһ�����
	}								//�������NULL�Ļ�����Ϊ����������㣬����ֱ�ӷ������������������������ֻ��1�����������
	else {
		tem = p1->data;				//���p2����NULL��ǰһ����㣬��˵����������������δ���򣬹��������������ٷ�������
		p1->data = p2->data;
		p2->data = tem;
		printf("��ż��ת���!\n");
		return (*L);			
	}
}


/*������ͷ��㺯��*/
LinkedList HeadNode() {
	LinkedList head;
	if ((head = (LinkedList)malloc(sizeof(LNode))) == NULL) {
		printf("�ڴ治�㣡\n");
	}
	head->next = NULL;
	return head;
}

/*����ѭ��������*/
LinkedList CreateLoopList(LinkedList L) {
	if (L == NULL) {
		printf("δ��ʼ������Ŷ~\n");
		return L;                             //δ��ʼ������ֱ�ӷ���
	}
	LinkedList p1 = L->next;                  //����һ������ѭ�������ָ��
	if (p1 == NULL) {
		L->next = L;
		return L;                         //��û�д��������ݵĽ��ʱ����ͷ����Լ��γ�һ��ѭ������
		printf("����ѭ���������!\n");
	}                                    
	while (p1->next != NULL) {
		p1 = p1->next;				//����������β 
	}
	p1->next = L;           			//����β���ͷ���� ����ѭ��
	printf("����ѭ���������!\n");        
	return L;
}

/*���������*/
ElemType TraverseList(LinkedList L) {
	if (L == NULL) {
		printf("��û�д�������Ŷ~\n�봴��������֮��������~\n");    //���������ͷ��㶼û�д�������ʱ�����
		return ERROR;
	}
	int check;
	check=IsLoopList(L);                                           //�����ж��Ƿ���ѭ��������
	LinkedList p1 = L->next;
	if (check == 1) {
		printf("�����𻵣��޷����\n");                       //�����ѭ������Ļ����޷����
		return;
	}
	if (p1 == NULL) {                                       //���������ֻ�����˸�ͷ��㣬�Ҳ�Ϊѭ������
		printf("��ǰ����Ϊ:");
		printf("NULL");
		return;                                                      //����
	}
	printf("��ǰ����Ϊ:");
	while (p1 != NULL) {
		printf("%d->", p1->data);
		p1 = p1->next;
	}
	printf("NULL");
	printf("\n\n");
	return;
}


int main() {
	LinkedList L = NULL;	//��������ָ���ͷ����ָ�� 
	int e1 = 0;           //�������ڷ���ɾ��ֵ���� 
	int judge = 1;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************ϵͳ���ܲ˵�******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.����������                  **      2.�����½ڵ�         *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.�������                    **      4.����������         *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.�ҵ���������е�            **      6.�ж��Ƿ�ɻ�       *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.ɾ�����ȡֵ                **      8.��ż��ת           *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      9.��ѯ�����Ƿ��ڱ���                  *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      10.ɾ�������˳�ϵͳ                 *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      11.����ѭ������                       *\n");
		printf("                              **************************************************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              ��ѡ��˵����:");
		int option,ret;
		while (1) {
			ret = scanf("%d", &option);
			rewind(stdin);                   //��ջ������Ĵ�������
			printf("\n");
			if (ret == 0) {
				printf("                              �������!����������:");
				
			}
			if (ret == 1 && (option < 1 || option>11)) {
				printf("                              �������!����������:");      //���벻Ϊ�ַ����ǲ�����ѡ�����������
			}
			if (ret==1&&(option >= 1 && option <= 11)) {
				fflush(stdin);
				break;                         //������ȷ��������˳�ѭ��
			}
			
		}
		system("cls");
		switch (option) {
		case 1:L = InitList(HeadNode());break;	//��ʼ������ 
		case 2:L = InsertList(&L); break;	//�����½�� 
		case 3:TraverseList(L); break;//������� 
		case 4:ReverseList(&L); break;	//���������� 
		case 5:FindMidNode(&L); break;  //�ҵ��������е� 
		case 6:IsLoopList(L); break;    //�ж��Ƿ�ɻ� 
		case 7:DeleteList(L, &e1); break;  //ɾ�����ȡֵ
		case 8:L = ReverseEvenList(&L); break;  //��ż��ת 
		case 9:SearchList(L); break;                    //��ѯ�����Ƿ��ڱ��� 
		case 10:judge=DestroyList(&L); break;        //ɾ�������˳�ϵͳ
		case 11:CreateLoopList(L); break;
		}
		printf("�����������...");
		_getch();
		system("cls");                    //����
		if (judge != 0) judge = 1;        //��judgeΪ1����������ѡ����� 
	}
}