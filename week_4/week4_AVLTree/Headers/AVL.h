#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* 存储空间初始分配量 */

#define LH +1 /*  左高 */ 
#define EH 0  /*  等高 */ 
#define RH -1 /*  右高 */

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

/*二叉树结构体*/
typedef struct BiTNode {
	int data;
	int bf;
	struct BiNode* lchild, * rchild; //左右孩子指针
}BiTNode, * BiTree;

typedef struct BinarySortTree {
	BiTree root;
}BinarySortTree, * BinarySortTreePtr;

/*队列结构体*/
typedef struct QueueNode {
	BiTNode* data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkQueue;


/*右旋*/
void R_Rotate(BiTree* p);

/*左旋*/
void L_Rotate(BiTree* p);

/*左平衡*/
void LeftBalance(BiTree* T);

/*右平衡*/
void RightBalance(BiTree* T);

/*插入操作*/
Status INsertAVL(BiTree* T, int e, Status* taller);

/*初始化树*/
BinarySortTreePtr BST_init(BinarySortTreePtr B);

/*队列初始化--有一个空表头*/
LinkQueue* InitQueue();

/*入队*/
void EnQueue(LinkQueue* queue, BiTNode* node);

/*出队*/
BiTNode* DeQueue(LinkQueue* queue);

/*层序遍历*/
Status BSTlevelOrder(BiTree T);


