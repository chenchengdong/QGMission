#include<stdio.h>
#include<stdlib.h>
#include"AVL.h"

/*����*/
void R_Rotate(BiTree* p) {  //��pΪ���Ķ�������������������
	BiTree L;               //������֮��pָ���µ�������㣬����ת����ǰ�����������ڵ�
	L =(*p)->lchild;      //Lָ��p�������������
	(*p)->lchild = (*p)->rchild;  //L���������ҽ�Ϊp��������
	L->rchild = (*p);
	*p = L;    //pָ���µĸ��ڵ�

}

/*����*/
void L_Rotate(BiTree* p) {  //����pΪ���Ķ�������������������
	BiTree R;              //������֮��pָ���µ�������㣬����ת����֮ǰ���������ĸ����
	R = (*p)->rchild;     //Rָ��p�����������ڵ�
	(*p)->rchild = R->lchild;  //R���������ҽ�Ϊp��������
	R->lchild = (*p);
	*p = R;   //pָ���µĸ����

}

/*��ƽ��*/
void LeftBalance(BiTree* T) { //����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת����
	BiTree L, Lr;             //���㷨����ʱ��ָ��Tָ���µĸ����
	L=(*T)->lchild;  //Lָ��T���������ĸ����
	switch (L->bf) {
		/*  ���T����������ƽ��ȣ�������Ӧƽ�⴦�� */
		case LH:  /*  �½�������T�����ӵ��������ϣ�Ҫ������������ */
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		case RH:     /*  �½�������T�����ӵ��������ϣ�Ҫ��˫������ */
			Lr = L->rchild;  //Lrָ��T�����ӵ��������� 
			switch (Lr->bf) {
				/*  �޸�T�������ӵ�ƽ������ */
			case LH:
				(*T)->bf = RH;
				L->bf = EH;
				break;
			case EH:
				(*T)->bf = L->bf = EH;
				break;
			case RH:
				(*T)->bf = EH;
				L->bf = LH;
				break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);   /*  ��T��������������ƽ�⴦�� */
			R_Rotate(T);           /*  ��T������ƽ�⴦�� */
	}
}


/*��ƽ��*/
void RightBalance(BiTree* T) {   /*  ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���� */
	BiTree R, Rl;                /*  ���㷨����ʱ��ָ��Tָ���µĸ���� */ 
	R = (*T)->rchild;            /*  Rָ��T������������� */ 
	switch (R->bf) {
		/*  ���T����������ƽ��ȣ�������Ӧƽ�⴦�� */
	case RH:    /*  �½�������T���Һ��ӵ��������ϣ�Ҫ������������ */
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:     /*  �½�������T���Һ��ӵ��������ϣ�Ҫ��˫������ */
		Rl = R->lchild;               /*  Rlָ��T���Һ��ӵ��������� */ 
		switch (Rl->bf) {
			/*  �޸�T�����Һ��ӵ�ƽ������ */
		case RH:
			(*T)->bf = LH;
			R->bf = EH;
			break;
		case EH:
			(*T)->bf = R->bf = EH;
			break;
		case LH:
			(*T)->bf = EH;
			R->bf = RH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&(*T)->rchild);   /*  ��T��������������ƽ�⴦�� */
		L_Rotate(T);              /*  ��T������ƽ�⴦�� */

	}
}
//����ƽ��Ķ���������T�в����ں�e����ͬ�Ĺؼ��ֵĽ�㣬�����һ��
//����Ԫ��Ϊe���½�㣬�򷵻�1�����򷵻�0����������ʹ����������ʧȥƽ�⣬
//����ƽ����ת������������taller��ӳ�������
Status INsertAVL(BiTree* T, int e, Status* taller) {
	if (!*T) {
		//�����½ڵ㣬�����ߣ���tallerΪtrue
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else {
		if (e == (*T)->data) {
			//�������Ѿ����ں�e����ͬ�Ĺؼ��ֵĽ�����ٲ���
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data) {
			//Ӧ������T���������н�������
			if (!INsertAVL(&(*T)->lchild, e, taller)) {
				return FALSE;                 //δ�������
			}
			if (*taller) {    //�Ѳ��뵽T�����������������������ߡ�
				switch ((*T)->bf) {   //���T��ƽ���
				case LH:
					LeftBalance(T);    //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
					*taller = FALSE;
					break;
				case EH:
					(*T)->bf = LH;   //ԭ����������һ���ߣ�������Ϊ���������߶�ʹ��������
					*taller = TRUE;
					break;
				case RH:
					(*T)->bf = EH;        //ԭ�����������������ߣ�������������һ����
					*taller = FALSE;
					break;
				}
			}
		}
		else {
				//Ӧ��T����������������
			if (!INsertAVL(&(*T)->rchild, e, taller)) {
					return FALSE;    //δ����
			}
			if (*taller) {  //�Ѳ��뵽T���������������������ߡ�
				switch ((*T)->bf) { // ���T��ƽ���
				case LH:
					(*T)->bf=EH;   //ԭ�����������������ߣ��������������ȸ�
					*taller=FALSE;
					break;
				case EH:
					(*T)->bf = RH;  //ԭ�����������ȸߣ��������������߶��ǵ�������
					*taller = TRUE;
					break;
				case RH:
					RightBalance(T);  //ԭ�����������������ߣ���������ƽ�⴦��
					*taller = FALSE;
					break;

				}
			}
		}	
	}
	return TRUE;
}

/*��ʼ����*/
BinarySortTreePtr BST_init(BinarySortTreePtr B) {
	B = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	B->root = NULL;
	return B;     
}

/*���г�ʼ��--��һ���ձ�ͷ*/
LinkQueue* InitQueue() {
	LinkQueue* queue = (LinkQueue*)malloc(sizeof(LinkQueue));
	if (!queue) {
		printf("can not create space!\n");
		exit(0);
	}
	queue->front = (QueueNode*)malloc(sizeof(QueueNode));
	queue->front->next = NULL;
	queue->rear = queue->front;
	return queue;
}

/*���*/
void EnQueue(LinkQueue* queue, BiTNode* node) {
	QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));
	queueNode->data = node;
	queueNode->next = NULL;
	queue->rear->next = queueNode;
	queue->rear = queueNode;
}

/*����*/
BiTNode* DeQueue(LinkQueue* queue) {
	if (queue->front == queue->rear) {
		return NULL;          //����Ϊ��
	}
	QueueNode* p = queue->front->next;
	BiTNode* node = p->data;
	queue->front = p;
	return node;
}

/*�������*/
Status BSTlevelOrder(BiTree T) {
	int curCount = 0;   //��¼��ǰ���еĽ����
	int nextCount = 0;  //��¼��һ��Ľ�����
	LinkQueue* queue = InitQueue(); //��ʼ������
	EnQueue(queue, T);  //��Ӳ���
	curCount++;
	BiTNode* p;
	while (p = DeQueue(queue)) {
		curCount--;
		printf("%d ", p->data);
		if (p->lchild) {
			EnQueue(queue, p->lchild);
			nextCount++;
		}
		if (p->rchild) {
			EnQueue(queue, p->rchild);
			nextCount++;
		}
		if (curCount == 0) {
			curCount = nextCount;
			nextCount = 0;
			printf("\n");
		}
	}
}

int main() {
	int judge = 1,e,taller,check=0;
	BinarySortTreePtr B=NULL;

	while (judge) {
		printf("\n\n");
		printf("                           ****************\n");
		printf("                           ****************\n");
		printf("                           * 1.��ʼ��������*\n");
		printf("                           * 2.����AVL��� *\n");
		printf("                           * 3.�������AVL *\n");
		printf("                           * 4.�˳�����    *\n");
		printf("                           ****************\n");
		printf("                           ****************\n");
		printf("                           -----������ѡ�");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);          //��մ������뻺��
			if (ret == 0) {
				printf("                   ����������������룺");
			}
			if (ret == 1) {
				fflush(stdin);
				break;
			}
		}
		system("cls");
		switch (option) {
		case 1:
			B = BST_init(B);
			printf("��ʼ���ɹ���\n");
			break;
		case 2:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			printf("��������Ҫ�����ֵ��");
			while (1) {
				ret = scanf("%d", &e);
				printf("\n");
				rewind(stdin);          //��մ������뻺��
				if (ret == 0) {
					printf("����������������룺");
				}
				if (ret == 1) {
					fflush(stdin);
					break;
				}
			}
			check = INsertAVL(&(B->root), e, &taller);
			if (check) printf("%d ����ɹ���\n", e);
			else printf("%d �Ѵ���AVL���У�\n", e);
			break;
		case 3:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�AVL���У�\n");
				break;
			}
			BSTlevelOrder(B->root);
			break;
		case 4:
			judge = 0;
			break;
		default:printf("������������ȷѡ�\n");
		}
		system("pause");
		system("cls");
	}
}