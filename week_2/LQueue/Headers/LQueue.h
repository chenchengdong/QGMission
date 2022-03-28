
// define element type
typedef int QElemType;

// define struct of LinkQueue list
typedef struct node
{
    void* data;                   //数据域指针
    struct node* next;            //指向当前结点的下一结点
    QElemType type;               //用于标记是哪种数据类型
} QNode;

//定义一个指向队列的结构体
typedef struct Lqueue
{
    QNode* front;                   //队头
    QNode* rear;                    //队尾
    QElemType length;            //队列长度
} LQueue;

// define status
typedef enum
{
    FALSE = 0, TRUE = 1,UNUSUAL=-1
} Status;

/**
 *  @name        :void InitLQueue(LQueue** Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针
 *  @notice      : none
 */
void InitLQueue(LQueue** Q);

/**
 *  @name        : Status DestoryLQueue(LQueue* Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针
 *    @return         : Status
 *  @notice      : None
 */
Status DestoryLQueue(LQueue* Q);

/**
 *  @name        : Status GetHeadLQueue(LQueue* Q, void* e)
 *    @description : 返回队头元素
 *    @param         Q 队列指针 e void*指针
 *    @return         : Status
 *  @notice      : None
 */
Status GetHeadLQueue(LQueue* Q, void* e);

/**
 *  @name        : Status GetHeadLQueue(LQueue* Q, void* e)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针 e void*指针
 *    @return         : Status
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q);

/**
 *  @name        : QElemType LengthLQueue(LQueue* Q)
 *    @description : 队列长度
 *    @param         Q 队列指针
 *    @return         : Status
 *  @notice      : None
 */
QElemType LengthLQueue(LQueue* Q);

/**
 *  @name        : Status EnLQueue(LQueue* Q, QNode* p)
 *    @description : 入队操作
 *    @param         Q 队列指针 p 需要入队的结点指针
 *    @return         : Status
 *  @notice      : None
 */
Status EnLQueue(LQueue* Q, QNode* p);

/**
 *  @name        : Status DeLQueue(LQueue* Q)
 *    @description : 出队操作
 *    @param         Q 队列指针
 *    @return         : Status
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q);

/**
 *  @name        : void ClearLQueue(LQueue* Q)
 *    @description : 清空队列
 *    @param         Q 队列指针
 *    @return         : none
 *  @notice      : None
 */
Status ClearLQueue(LQueue* Q);

/**
 *  @name        : Status TraverseLQueue(const LQueue* Q, void(*foo)(void* q))
 *    @description : 遍历队列
 *    @param         Q 队列指针 *foo指向函数的指针
 *    @return         : Status
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void(*foo)(void* q));

/**
 *  @name        : void LPrint(void** q)
 *    @description : 操作函数
 *    @param         void**型指针
 *    @return         : none
 *  @notice      : None
 */
void LPrint(void** q);

/**
 *  @name        : QNode* ChosenType(LQueue*Q)
 *    @description : 选择输入的数据类型
 *    @param         Q 指向队列的指针
 *    @return         : Status
 *  @notice      : None
 */
QNode* ChosenType(LQueue*Q);



