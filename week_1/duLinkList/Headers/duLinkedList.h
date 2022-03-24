// define element type
typedef int ElemType;

// define struct of linked list
typedef struct DuLNode {
	ElemType data;
	struct DuLNode* prior, * next;
} DuLNode, * DuLinkedList;

// define status
typedef enum Status {                          //// define status
	ERROR,
	SUCCESS,
} Status;

/*create a head node*/
DuLinkedList headNode();

/**
 *  @name        : DuLinkedList InitList_DuL(DuLinkedList L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : DuLinkedList
 *  @notice      : None
 */
DuLinkedList InitList_DuL(DuLinkedList L);

/**
 *  @name        : ElemType DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType DestroyList_Dul(DuLinkedList* L);

/**
 *  @name        : ElemType InsertBeforeList_DuL(DuLinkedList* L)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType InsertBeforeList_DuL(DuLinkedList* L);

/**
 *  @name        : ElemType InsertAfterList_DuL(DuLinkedList* L)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType InsertAfterList_DuL(DuLinkedList* L);

/**
 *  @name        : Status DeleteList_DuL(DuLinkedList L, ElemType* e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : ElemType
 *  @notice      : None
 */
ElemType DeleteList_DuL(DuLinkedList L, ElemType* e);

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L)
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : none
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L);
