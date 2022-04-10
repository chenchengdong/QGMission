
#define true 1
#define false 0
#define succeed 1
#define failed 0
#define Status int
#define N 20

typedef int ElemType;

typedef struct Node {
	ElemType value;
	struct Node* left, * right;
}Node, * NodePtr;

typedef struct BinarySortTree {
	NodePtr root;
}BinarySortTree, * BinarySortTreePtr;

typedef struct QueueNode {
	Node* data;
	struct QueueNode* next;
}QueueNode;


typedef struct {
	QueueNode* front;
	QueueNode* rear;
}LinkQueue;


/**
 * BST_init(BinarySortTreePtr B)
 * @param BinarySortTreePtr BST
 * @return BinarySortTreePtr
 */
BinarySortTreePtr BST_init(BinarySortTreePtr B);

/**
 * BST insert
 * @param BST_insert(NodePtr* T, ElemType key)
 * @param ElemType value to insert
 * @return is successful
 */
Status BST_insert(NodePtr* T, ElemType key);

/**
 * BST delete
 * @param BST_delete(NodePtr* T, ElemType key)
 * @param ElemType the value for Node which will be deleted
 * @return is successful
 */
Status BST_delete(NodePtr* T, ElemType key);

/**
 * BST search
 * @param BST_search(NodePtr T, ElemType key, NodePtr f, NodePtr* p)
 * @param ElemType the value to search
 * @return is exist
 */
Status BST_search(NodePtr T, ElemType key, NodePtr f, NodePtr* p);

/**
 * BST search
 * @param Delete(NodePtr* p)
 * @param NodePtr* p
 * @return is successful
 */
Status Delete(NodePtr* p);

/**
 * BST preorder traversal without recursion
 * @param BST_preorderI(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_preorderI(NodePtr T);

/**
 * BST preorder traversal with recursion
 * @param BST_preorderR(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_preorderR(NodePtr T);

/**
 * BST inorder traversal without recursion
 * @param BST_inorderI(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_inorderI(NodePtr T);

/**
 * BST inorder traversal with recursion
 * @param BST_inorderR(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_inorderR(NodePtr T);

/**
 * BST preorder traversal without recursion
 * @param BST_postorderI(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_postorderI(NodePtr T);

/**
 * BST postorder traversal with recursion
 * @param BST_postorderR(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BST_postorderR(NodePtr T);

/**
 * BST level order traversal
 * @param BSTlevelOrder(NodePtr T)
 * @param NodePtr T
 * @return is successful
 */
Status BSTlevelOrder(NodePtr T);

/*初始化队列*/
LinkQueue* InitQueue();

/*入队*/
void EnQueue(LinkQueue* queue, Node* node);

/*出队*/
Node* DeQueue(LinkQueue* queue);



