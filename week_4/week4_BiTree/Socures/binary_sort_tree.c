#include<stdio.h>
#include<stdlib.h>
#include"binary_sort_tree.h"


/*��ʼ����*/
BinarySortTreePtr BST_init(BinarySortTreePtr B) {
	B = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	B->root = NULL;
	return B;        //��ʼ���ɹ��򷵻�successd
}

/*�������*/
Status BST_insert(NodePtr*T, ElemType key) {
	NodePtr p=NULL, s=NULL;
	if (!BST_search(*T, key, NULL, &p)) {  //���Ҳ��ɹ�
		s = (NodePtr)malloc(sizeof(Node));
		s->value = key;
		s->left = s->right = NULL;
		if (!p) {
				*T = s;    //����sΪ�µĸ����
		}
		else if (key < p->value) {
				p->left = s;    //����Ϊ����
		}
		else {
				p->right = s;   //����Ϊ�Һ���
		}
		return true;
	}
	else {
		return false;         //�������йؼ�����ͬ�Ľ�㣬���ٲ���
	}
}

/*ɾ������*/
Status BST_delete(NodePtr *T, ElemType key) {
	if (!*T) {
		return false;             //�����ڹؼ���Ϊkey������Ԫ��
	}
	else {
		if (key == (*T)->value) {
			return Delete(T);    //�ҵ��ؼ��ֵ���key������Ԫ��
		}
		else if (key < (*T)->value) {
			return BST_delete(&(*T)->left, key); //ȥ��������
		}
		else {
			return BST_delete(&(*T)->right, key);//ȥ��������
		}
	}
}

/*����ɾ��������*/
Status Delete(NodePtr* p) {
	NodePtr q, s;
	if ((*p)->right == NULL) {
		q = *p;
		*p = (*p)->left;
		free(q);          //����������ֻ���ؽ�����������
	}
	else if ((*p)->left == NULL) {
		q = *p;
		*p = (*p)->right;
		free(q);          //����������ֻ���ؽ�����������
	}
	else {                //������������Ϊ��
		q = *p;
		s = (*p)->left;
		while (s->right) { //ת��Ȼ�����ҵ���ͷ���ҵ���ɾ����ǰ����
			q = s;
			s = s->right;
		}
		(*p)->value = s->value;  //����ɾ���ֵ��ֱ��ǰ������
		if (q != *p) {
			q->right = s->left;  //�ؽ�q������������Ϊ��ʱ��qΪs�ĸ��ڵ�
		}
		else {
			q->left = s->left;    //�ؽ�q��������
		}
		free(s);
	}
	return true;
}


/*���Ҳ���*/
Status BST_search(NodePtr T, ElemType key,NodePtr f,NodePtr*p) {   //fָ��T��˫�ף����ʼ����ֵΪNULL
	if (!T) {                                                     //����ѯ�ɹ�����ָ��pָ���Ԫ�صĽ�㣬������true
		*p = f;                                                  //����ѯʧ�ܣ���ָ��pָ�����·���Ϸ��ʵ����һ����㲢����False
		return false;   //���Ҳ��ɹ�
	}
	else if (key == T->value) {
		*p = T;    //���ҳɹ�
		return true;
	}
	else if (key < T->value) {
		return BST_search(T->left, key, T, p);//����������������
	}
	else {
		return BST_search(T->right, key, T, p);//����������������
	}
}

//����һ��վ���ڴ���ݹ�
typedef struct {
	Node* data[20];
	ElemType top;
}Stack;

/*ǰ������ǵݹ�*/
Status BST_preorderI(NodePtr T) {
	Stack S;
	S.top = -1;
	if(T!=NULL) {
		Node* p;
		S.data[++(S.top)] = T;
		while (S.top != -1) {
			p = S.data[(S.top)--];
			printf("%d ", p->value);
			if (p->right != NULL) {    //��������������ջ
				S.data[++(S.top)] = p->right;
			}
			if (p->left != NULL) {    //�����������Ҳ��ջ��ֻ�������������Ƚ�
				S.data[++(S.top)] = p->left;
			}
		}
	}
}

/*ǰ������ݹ�*/
Status BST_preorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	printf("%d ", T->value);    //��ʾ�������
	BST_preorderR(T->left);   //���������������
	BST_preorderR(T->right);   //���������������

}

/*��������ǵݹ�*/
Status BST_inorderI(NodePtr T) {
	NodePtr* s;
	NodePtr p, q;
	int top = -1;
	//����ջ
	s = (NodePtr*)malloc((N + 1) * sizeof(NodePtr));
	if (T) {               
		while (T) {         //һֱ����������ֱ���ý�������Ϊ��Ϊֹ
			s[++top] = T;   //���������Ӵ���ջ��
			T = T->left;     //ָ����һ��������
		}
		while (top != -1) {  //ջ��ʱ����ѭ��
			p = s[top--];     //�տ�ʼ����pָ�����½ǵ����ӣ���������ý���˫�׽ڵ�
			printf("%d ", p->value); //������½ǵĽ��
			while (p->right) {    //�����ƶ�������û���ҽ��
				s[++top] = p->right;   //�����������������ջ
				q = p->right;       //�������������㸶��q
				while (q->left) {
					s[++top] = q->left;  //��������������������������������������������ջ
					q = q->left;
				}
				break;   //������ǰѭ�����ص��ڶ���whileѭ�������ղŵĲ���
			}
		}
	}
}

/*��������ݹ�*/
Status BST_inorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	BST_inorderR(T->left);   //���������������
	printf("%d ", T->value);     //��ʾ�������
	BST_inorderR(T->right);   //���������������
}

/*���������ǵݹ�*/
Status BST_postorderI(NodePtr T) {
	NodePtr* s;
	NodePtr p;
	int top = -1;
	//����ջ
	s = (NodePtr*)malloc((N + 1) * sizeof(NodePtr));
	do {
		while (T) {  //һֱ����������ֱ����������������Ϊ��Ϊֹ
			s[++top] = T;   //���������Ӵ���ջ��
			T = T->left;   //ָ����һ��������
		}
		p = NULL;
		while (top != -1) {
			T = s[top];
			if (T->right == p) {   //p��ʾΪNULL���������ӽڵ㱻���ʹ���
				printf("%d ", T->value);
				top--;
				p = T;    //p��¼�¸ոշ��ʹ��Ľ��
			}
			else {
				T = T->right;    //�����������Ľ��
				break;
			}
		}
	} while (top != -1);

}

/*��������ݹ�*/
Status BST_postorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	BST_postorderR(T->left);   //���������������
	BST_postorderR(T->right);   //���������������
	printf("%d ", T->value);     //��ʾ�������
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
void EnQueue(LinkQueue* queue, Node* node) {
	QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));
	queueNode->data = node;
	queueNode->next = NULL;
	queue->rear->next = queueNode;
	queue->rear = queueNode;
}

/*����*/
Node* DeQueue(LinkQueue* queue) {
	if (queue->front == queue->rear) {
		return NULL;          //����Ϊ��
	}
	QueueNode* p = queue->front->next;
	Node* node = p->data;
	queue->front = p;
	return node;
}

/*�������*/
Status BSTlevelOrder(NodePtr T) {
	int curCount = 0;   //��¼��ǰ���еĽ����
	int nextCount = 0;  //��¼��һ��Ľ�����
	LinkQueue* queue = InitQueue(); //��ʼ������
	EnQueue(queue, T);  //��Ӳ���
	curCount++;
	Node* p;
	while (p = DeQueue(queue)) {
		curCount--;
		printf("%d ", p->value);
		if (p->left) {
			EnQueue(queue, p->left);
			nextCount++;
		}
		if (p->right) {
			EnQueue(queue, p->right);
			nextCount++;
		}
		if (curCount == 0) {
			curCount = nextCount;
			nextCount = 0;
			printf("\n");
		}
	}
}

/*��������*/

int main() {
	int judge = 1,key=0,check=0;
	BinarySortTreePtr B=NULL;
	NodePtr p = NULL;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************ϵͳ���ܲ˵�******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.��ʼ����                **         2.�������            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.ɾ������                **         4.��ѯ����            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.������������ݹ飩      **         6.������������ǵݹ飩*\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.������������ݹ飩      **         8.������������ǵݹ飩*\n");
		printf("                              **************************************************************\n");
		printf("                              * 9.������������ݹ飩      **         10.������������ǵݹ飩*\n");
		printf("                              **************************************************************\n");
		printf("                              * 11.��������������У�     **         12.�˳�����           *\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              ��ѡ��˵���ţ�");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);          //��մ������뻺��
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
		case 1:
			B=BST_init(B);
			printf("��ʼ���ɹ���\n");
			break;
		case 2:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			printf("����������Ҫ�����ֵ��");
			while (1) {
				ret= scanf("%d", &key);
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
			check=BST_insert(&(B->root), key);
			if (!check) printf("%d �Ѵ�������������У�\n",key);
			else printf("%d ����ɹ���\n",key);
			break;
		case 3:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			printf("����������Ҫɾ����ֵ��");
			while (1) {
				ret = scanf("%d", &key);
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
			check=BST_delete(&(B->root), key);
			if (check) printf("%d ��ɾ��\n", key);
			else printf("%d ��������������У��޷�ɾ��\n", key);
			break;
		case 4:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			printf("����������Ҫ��ѯ��ֵ��");
			while (1) {
				ret = scanf("%d", &key);
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
			check=BST_search(B->root, key, NULL, &p);
			if (check) printf("%d ������������У�\n", key);
			else printf("%d ��������������У�\n", key);
			break;
		case 5:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_preorderR(B->root);
			break;
		case 6:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_preorderI(B->root);
			break;
		case 7:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_inorderR(B->root);
			break;
		case 8:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_inorderI(B->root);
			break;
		case 9:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_postorderR(B->root);
			break;
		case 10:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BST_postorderI(B->root);
			break;
		case 11:
			if (B == NULL) {
				printf("���ȳ�ʼ������\n");
				break;
			}
			if (B->root == NULL) {
				printf("���Ȳ������ݵ�����������У�\n");
				break;
			}
			BSTlevelOrder(B->root);
			break;
		case 12:
			judge = 0;
			break;
		default:printf("������������ȷѡ�\n");
		}
		system("pause");
		system("cls");
	}
}
