#include<stdio.h>
#include<stdlib.h>
#include"AVL.h"

/*右旋*/
void R_Rotate(BiTree* p) {  //以p为根的二叉排序树作右旋处理
	BiTree L;               //处理完之后p指向新的树根结点，即旋转处理前的左子树根节点
	L =(*p)->lchild;      //L指向p的左子树根结点
	(*p)->lchild = (*p)->rchild;  //L的右子树挂接为p的左子树
	L->rchild = (*p);
	*p = L;    //p指向新的根节点

}

/*左旋*/
void L_Rotate(BiTree* p) {  //对以p为根的二叉排序树作左旋处理
	BiTree R;              //处理完之后p指向新的树根结点，即旋转处理之前的右子树的根结点
	R = (*p)->rchild;     //R指向p的右子树根节点
	(*p)->rchild = R->lchild;  //R的左子树挂接为p的右子树
	R->lchild = (*p);
	*p = R;   //p指向新的根结点

}

/*左平衡*/
void LeftBalance(BiTree* T) { //对以指针T所指结点为根的二叉树作左平衡旋转处理
	BiTree L, Lr;             //本算法结束时，指针T指向新的根结点
	L=(*T)->lchild;  //L指向T的左子树的根结点
	switch (L->bf) {
		/*  检查T的左子树的平衡度，并作相应平衡处理 */
		case LH:  /*  新结点插入在T的左孩子的左子树上，要作单右旋处理 */
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		case RH:     /*  新结点插入在T的左孩子的右子树上，要作双旋处理 */
			Lr = L->rchild;  //Lr指向T的左孩子的右子树根 
			switch (Lr->bf) {
				/*  修改T及其左孩子的平衡因子 */
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
			L_Rotate(&(*T)->lchild);   /*  对T的左子树作左旋平衡处理 */
			R_Rotate(T);           /*  对T作右旋平衡处理 */
	}
}


/*右平衡*/
void RightBalance(BiTree* T) {   /*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */
	BiTree R, Rl;                /*  本算法结束时，指针T指向新的根结点 */ 
	R = (*T)->rchild;            /*  R指向T的右子树根结点 */ 
	switch (R->bf) {
		/*  检查T的右子树的平衡度，并作相应平衡处理 */
	case RH:    /*  新结点插入在T的右孩子的右子树上，要作单左旋处理 */
		(*T)->bf = R->bf = EH;
		L_Rotate(T);
		break;
	case LH:     /*  新结点插入在T的右孩子的左子树上，要作双旋处理 */
		Rl = R->lchild;               /*  Rl指向T的右孩子的左子树根 */ 
		switch (Rl->bf) {
			/*  修改T及其右孩子的平衡因子 */
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
		R_Rotate(&(*T)->rchild);   /*  对T的右子树作右旋平衡处理 */
		L_Rotate(T);              /*  对T作左旋平衡处理 */

	}
}
//若在平衡的二叉排序树T中不存在和e有相同的关键字的结点，则插入一个
//数据元素为e的新结点，则返回1，否则返回0，若因插入而使二叉排序树失去平衡，
//则作平衡旋转处理，布尔变量taller反映长高与否
Status INsertAVL(BiTree* T, int e, Status* taller) {
	if (!*T) {
		//插入新节点，树长高，置taller为true
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else {
		if (e == (*T)->data) {
			//树里面已经存在和e有相同的关键字的结点则不再插入
			*taller = FALSE;
			return FALSE;
		}
		if (e < (*T)->data) {
			//应继续在T的左子树中进行搜索
			if (!INsertAVL(&(*T)->lchild, e, taller)) {
				return FALSE;                 //未插入情况
			}
			if (*taller) {    //已插入到T的左子树中且左子树“长高”
				switch ((*T)->bf) {   //检查T的平衡度
				case LH:
					LeftBalance(T);    //原本左子树比右子树高，需要作左平衡处理
					*taller = FALSE;
					break;
				case EH:
					(*T)->bf = LH;   //原本左右子树一样高，现在因为左子树增高而使得树增高
					*taller = TRUE;
					break;
				case RH:
					(*T)->bf = EH;        //原本右子树比左子树高，现在左右子树一样高
					*taller = FALSE;
					break;
				}
			}
		}
		else {
				//应在T的右子树进行搜索
			if (!INsertAVL(&(*T)->rchild, e, taller)) {
					return FALSE;    //未插入
			}
			if (*taller) {  //已插入到T的右子树且右子树”长高“
				switch ((*T)->bf) { // 检查T的平衡度
				case LH:
					(*T)->bf=EH;   //原本左子树比右子树高，现在左，右子树等高
					*taller=FALSE;
					break;
				case EH:
					(*T)->bf = RH;  //原本左右子树等高，现因右子树增高而是得树增高
					*taller = TRUE;
					break;
				case RH:
					RightBalance(T);  //原本右子树比左子树高，需做有右平衡处理
					*taller = FALSE;
					break;

				}
			}
		}	
	}
	return TRUE;
}

/*初始化树*/
BinarySortTreePtr BST_init(BinarySortTreePtr B) {
	B = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	B->root = NULL;
	return B;     
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
void EnQueue(LinkQueue* queue, BiTNode* node) {
	QueueNode* queueNode = (QueueNode*)malloc(sizeof(QueueNode));
	queueNode->data = node;
	queueNode->next = NULL;
	queue->rear->next = queueNode;
	queue->rear = queueNode;
}

/*出队*/
BiTNode* DeQueue(LinkQueue* queue) {
	if (queue->front == queue->rear) {
		return NULL;          //队列为空
	}
	QueueNode* p = queue->front->next;
	BiTNode* node = p->data;
	queue->front = p;
	return node;
}

/*层序遍历*/
Status BSTlevelOrder(BiTree T) {
	int curCount = 0;   //记录当前层中的结点数
	int nextCount = 0;  //记录下一层的结点个数
	LinkQueue* queue = InitQueue(); //初始化队列
	EnQueue(queue, T);  //入队操作
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
		printf("                           * 1.初始化二叉树*\n");
		printf("                           * 2.插入AVL结点 *\n");
		printf("                           * 3.层序遍历AVL *\n");
		printf("                           * 4.退出程序    *\n");
		printf("                           ****************\n");
		printf("                           ****************\n");
		printf("                           -----请输入选项：");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);          //清空错误输入缓存
			if (ret == 0) {
				printf("                   输入错误！请重新输入：");
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
			printf("初始化成功！\n");
			break;
		case 2:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			printf("请输入你要插入的值：");
			while (1) {
				ret = scanf("%d", &e);
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
			check = INsertAVL(&(B->root), e, &taller);
			if (check) printf("%d 插入成功！\n", e);
			else printf("%d 已存在AVL树中！\n", e);
			break;
		case 3:
			if (B == NULL) {
				printf("请先初始化树！\n");
				break;
			}
			if (B->root == NULL) {
				printf("请先插入数据到AVL树中！\n");
				break;
			}
			BSTlevelOrder(B->root);
			break;
		case 4:
			judge = 0;
			break;
		default:printf("请重新输入正确选项：\n");
		}
		system("pause");
		system("cls");
	}
}