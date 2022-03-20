// define element type
typedef int ElemType;

// define struct of linked list
typedef struct LNode {
	ElemType data;			//结构体数据域
	struct LNode* next;		//结构体连接指针
}LNode, * LinkedList;

// define Status
typedef enum Status {
	ERROR,					//枚举类型值为0
	SUCCESS					//枚举类型值为1
}Status;

/**
 *  @name        : LinkedList InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
LinkedList InitList(LinkedList L);

/**
 *  @name        : ElemType DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType DestroyList(LinkedList* L);

/**
 *  @name        : LinkedList InsertList(LinkedList* L)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : LinkedList
 *  @notice      : None
 */
LinkedList InsertList(LinkedList* L);

/**
 *  @name        : LinkedList DeleteList(LinkedList L, ElemType* e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : LinkedList
 *  @notice      : None
 */
LinkedList DeleteList(LinkedList L, ElemType* e);

/**
 *  @name        : Status SearchList(LinkedList L)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType SearchList(LinkedList L);

/**
 *  @name        : ElemType ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType ReverseList(LinkedList *L);

/**
 *  @name        : ElemType IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType IsLoopList(LinkedList L);

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList* L);

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList* L);

/*create a head node*/
LinkedList HeadNode();

/*make a list into a loop*/
LinkedList CreateLoopList(LinkedList L);

/**
 *  @name        : ElemType TraverseList(LinkedList L)
 *	@description : traverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
ElemType TraverseList(LinkedList L);
