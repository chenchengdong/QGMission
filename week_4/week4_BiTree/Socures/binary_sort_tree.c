#include<stdio.h>
#include<stdlib.h>
#include"binary_sort_tree.h"


/*初始化树*/
BinarySortTreePtr BST_init(BinarySortTreePtr B) {
	B = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	B->root = NULL;
	return B;        //初始化成功则返回successd
}

/*插入操作*/
Status BST_insert(NodePtr*T, ElemType key) {
	NodePtr p=NULL, s=NULL;
	if (!BST_search(*T, key, NULL, &p)) {  //查找不成功
		s = (NodePtr)malloc(sizeof(Node));
		s->value = key;
		s->left = s->right = NULL;
		if (!p) {
				*T = s;    //插入s为新的跟结点
		}
		else if (key < p->value) {
				p->left = s;    //插入为左孩子
		}
		else {
				p->right = s;   //插入为右孩子
		}
		return true;
	}
	else {
		return false;         //树中已有关键字相同的结点，不再插入
	}
}

/*删除操作*/
Status BST_delete(NodePtr *T, ElemType key) {
	if (!*T) {
		return false;             //不存在关键字为key的数据元素
	}
	else {
		if (key == (*T)->value) {
			return Delete(T);    //找到关键字等于key的数据元素
		}
		else if (key < (*T)->value) {
			return BST_delete(&(*T)->left, key); //去左子树找
		}
		else {
			return BST_delete(&(*T)->right, key);//去右子树找
		}
	}
}

/*辅助删除结点操作*/
Status Delete(NodePtr* p) {
	NodePtr q, s;
	if ((*p)->right == NULL) {
		q = *p;
		*p = (*p)->left;
		free(q);          //右子树空则只需重接它的左子树
	}
	else if ((*p)->left == NULL) {
		q = *p;
		*p = (*p)->right;
		free(q);          //左子树空则只需重接它的右子树
	}
	else {                //左右子树均不为空
		q = *p;
		s = (*p)->left;
		while (s->right) { //转左，然后向右到尽头（找到待删结点的前驱）
			q = s;
			s = s->right;
		}
		(*p)->value = s->value;  //将待删结点值与直接前驱交换
		if (q != *p) {
			q->right = s->left;  //重接q的右子树，因为这时候q为s的根节点
		}
		else {
			q->left = s->left;    //重接q的左子树
		}
		free(s);
	}
	return true;
}


/*查找操作*/
Status BST_search(NodePtr T, ElemType key,NodePtr f,NodePtr*p) {   //f指向T的双亲，其初始调用值为NULL
	if (!T) {                                                     //若查询成功，则指针p指向该元素的结点，并返回true
		*p = f;                                                  //若查询失败，则指针p指向查找路径上访问的最后一个结点并返回False
		return false;   //查找不成功
	}
	else if (key == T->value) {
		*p = T;    //查找成功
		return true;
	}
	else if (key < T->value) {
		return BST_search(T->left, key, T, p);//在左子树继续查找
	}
	else {
		return BST_search(T->right, key, T, p);//在右子树继续查找
	}
}

//定义一个站用于代替递归
typedef struct {
	Node* data[20];
	ElemType top;
}Stack;

/*前序遍历非递归*/
Status BST_preorderI(NodePtr T) {
	Stack S;
	S.top = -1;
	if(T!=NULL) {
		Node* p;
		S.data[++(S.top)] = T;
		while (S.top != -1) {
			p = S.data[(S.top)--];
			printf("%d ", p->value);
			if (p->right != NULL) {    //如果右右子树则进栈
				S.data[++(S.top)] = p->right;
			}
			if (p->left != NULL) {    //如果有左子树也进栈，只不过是右子树先进
				S.data[++(S.top)] = p->left;
			}
		}
	}
}

/*前序遍历递归*/
Status BST_preorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	printf("%d ", T->value);    //显示结点数据
	BST_preorderR(T->left);   //再先序遍历左子树
	BST_preorderR(T->right);   //再先序遍历右子树

}

/*中序遍历非递归*/
Status BST_inorderI(NodePtr T) {
	NodePtr* s;
	NodePtr p, q;
	int top = -1;
	//创建栈
	s = (NodePtr*)malloc((N + 1) * sizeof(NodePtr));
	if (T) {               
		while (T) {         //一直遍历左子树直到该结点的左孩子为空为止
			s[++top] = T;   //将所有左孩子存入栈中
			T = T->left;     //指向下一个左孩子树
		}
		while (top != -1) {  //栈空时结束循环
			p = s[top--];     //刚开始将最p指向左下角的左孩子，并且移向该结点的双亲节点
			printf("%d ", p->value); //输出左下角的结点
			while (p->right) {    //遍历移动后结点有没有右结点
				s[++top] = p->right;   //将这个结点的右子树入栈
				q = p->right;       //将这个右子树结点付给q
				while (q->left) {
					s[++top] = q->left;  //若这个结点有左子树，将与这个结点相连的左子树都入栈
					q = q->left;
				}
				break;   //结束当前循环，回到第二个while循环继续刚才的步骤
			}
		}
	}
}

/*中序遍历递归*/
Status BST_inorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	BST_inorderR(T->left);   //再先序遍历左子树
	printf("%d ", T->value);     //显示结点数据
	BST_inorderR(T->right);   //再先序遍历右子树
}

/*后续遍历非递归*/
Status BST_postorderI(NodePtr T) {
	NodePtr* s;
	NodePtr p;
	int top = -1;
	//创建栈
	s = (NodePtr*)malloc((N + 1) * sizeof(NodePtr));
	do {
		while (T) {  //一直遍历左子树直到该左子树的左孩子为空为止
			s[++top] = T;   //将所有左孩子存入栈中
			T = T->left;   //指向下一个左子树
		}
		p = NULL;
		while (top != -1) {
			T = s[top];
			if (T->right == p) {   //p表示为NULL，或者右子节点被访问过了
				printf("%d ", T->value);
				top--;
				p = T;    //p记录下刚刚访问过的结点
			}
			else {
				T = T->right;    //访问右子树的结点
				break;
			}
		}
	} while (top != -1);

}

/*后序遍历递归*/
Status BST_postorderR(NodePtr T) {
	if (T == NULL) {
		return;
	}
	BST_postorderR(T->left);   //再先序遍历左子树
	BST_postorderR(T->right);   //再先序遍历右子树
	printf("%d ", T->value);     //显示结点数据
}


/*队列初始化--有一个空表头*/
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

/*入队*/
void EnQueue(LinkQueue* queue, Node* node) {
	QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));
	queueNode->data = node;
	queueNode->next = NULL;
	queue->rear->next = queueNode;
	queue->rear = queueNode;
}

/*出队*/
Node* DeQueue(LinkQueue* queue) {
	if (queue->front == queue->rear) {
		return NULL;          //队列为空
	}
	QueueNode* p = queue->front->next;
	Node* node = p->data;
	queue->front = p;
	return node;
}

/*层序遍历*/
Status BSTlevelOrder(NodePtr T) {
	int curCount = 0;   //记录当前层中的结点数
	int nextCount = 0;  //记录下一层的结点个数
	LinkQueue* queue = InitQueue(); //初始化队列
	EnQueue(queue, T);  //入队操作
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

/*遍历函数*/

int main() {
	int judge = 1,key=0,check=0;
	BinarySortTreePtr B=NULL;
	NodePtr p = NULL;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************系统功能菜单******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.初始化树                **         2.插入操作            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.删除操作                **         4.查询操作            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.先序遍历树（递归）      **         6.先序遍历树（非递归）*\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.中序遍历树（递归）      **         8.中序遍历树（非递归）*\n");
		printf("                              **************************************************************\n");
		printf("                              * 9.后序遍历树（递归）      **         10.后序遍历树（非递归）*\n");
		printf("                              **************************************************************\n");
		printf("                              * 11.层序遍历树（队列）     **         12.退出程序           *\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              请选择菜单编号：");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);          //清空错误输入缓存
			if (ret == 0) {
				printf("                         输入错误！请重新输入：");
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
			printf("初始化成功！\n");
			break;
		case 2:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			printf("请输入你需要插入的值：");
			while (1) {
				ret= scanf("%d", &key);
				printf("\n");
				rewind(stdin);          //清空错误输入缓存
				if (ret == 0) {
					printf("输入错误！请重新输入：");
				}
				if (ret == 1) {
					fflush(stdin);
					break;
				}
			}
			check=BST_insert(&(B->root), key);
			if (!check) printf("%d 已存在排序二叉树中！\n",key);
			else printf("%d 插入成功！\n",key);
			break;
		case 3:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			printf("请输入你需要删除的值：");
			while (1) {
				ret = scanf("%d", &key);
				printf("\n");
				rewind(stdin);          //清空错误输入缓存
				if (ret == 0) {
					printf("输入错误！请重新输入：");
				}
				if (ret == 1) {
					fflush(stdin);
					break;
				}
			}
			check=BST_delete(&(B->root), key);
			if (check) printf("%d 已删除\n", key);
			else printf("%d 不在排序二叉树中，无法删除\n", key);
			break;
		case 4:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			printf("请输入你需要查询的值：");
			while (1) {
				ret = scanf("%d", &key);
				printf("\n");
				rewind(stdin);          //清空错误输入缓存
				if (ret == 0) {
					printf("输入错误！请重新输入：");
				}
				if (ret == 1) {
					fflush(stdin);
					break;
				}
			}
			check=BST_search(B->root, key, NULL, &p);
			if (check) printf("%d 在排序二叉树中！\n", key);
			else printf("%d 不在排序二叉树中！\n", key);
			break;
		case 5:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_preorderR(B->root);
			break;
		case 6:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_preorderI(B->root);
			break;
		case 7:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_inorderR(B->root);
			break;
		case 8:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_inorderI(B->root);
			break;
		case 9:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_postorderR(B->root);
			break;
		case 10:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BST_postorderI(B->root);
			break;
		case 11:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到排序二叉树中！\n");
				break;
			}
			BSTlevelOrder(B->root);
			break;
		case 12:
			judge = 0;
			break;
		default:printf("请重新输入正确选项！\n");
		}
		system("pause");
		system("cls");
	}
}
