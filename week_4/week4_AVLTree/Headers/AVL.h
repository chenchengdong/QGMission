#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

#define LH +1 /*  ��� */ 
#define EH 0  /*  �ȸ� */ 
#define RH -1 /*  �Ҹ� */

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

/*�������ṹ��*/
typedef struct BiTNode {
	int data;
	int bf;
	struct BiNode* lchild, * rchild; //���Һ���ָ��
}BiTNode, * BiTree;

typedef struct BinarySortTree {
	BiTree root;
}BinarySortTree, * BinarySortTreePtr;

/*���нṹ��*/
typedef struct QueueNode {
	BiTNode* data;
	struct QueueNode* next;
}QueueNode;

typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkQueue;


/*����*/
void R_Rotate(BiTree* p);

/*����*/
void L_Rotate(BiTree* p);

/*��ƽ��*/
void LeftBalance(BiTree* T);

/*��ƽ��*/
void RightBalance(BiTree* T);

/*�������*/
Status INsertAVL(BiTree* T, int e, Status* taller);

/*��ʼ����*/
BinarySortTreePtr BST_init(BinarySortTreePtr B);

/*���г�ʼ��--��һ���ձ�ͷ*/
LinkQueue* InitQueue();

/*���*/
void EnQueue(LinkQueue* queue, BiTNode* node);

/*����*/
BiTNode* DeQueue(LinkQueue* queue);

/*�������*/
Status BSTlevelOrder(BiTree T);


