
// define element type
typedef int QElemType;

// define struct of LinkQueue list
typedef struct node
{
    void* data;                   //������ָ��
    struct node* next;            //ָ��ǰ������һ���
    QElemType type;               //���ڱ����������������
} QNode;

//����һ��ָ����еĽṹ��
typedef struct Lqueue
{
    QNode* front;                   //��ͷ
    QNode* rear;                    //��β
    QElemType length;            //���г���
} LQueue;

// define status
typedef enum
{
    FALSE = 0, TRUE = 1,UNUSUAL=-1
} Status;

/**
 *  @name        :void InitLQueue(LQueue** Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��
 *  @notice      : none
 */
void InitLQueue(LQueue** Q);

/**
 *  @name        : Status DestoryLQueue(LQueue* Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status DestoryLQueue(LQueue* Q);

/**
 *  @name        : Status GetHeadLQueue(LQueue* Q, void* e)
 *    @description : ���ض�ͷԪ��
 *    @param         Q ����ָ�� e void*ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status GetHeadLQueue(LQueue* Q, void* e);

/**
 *  @name        : Status GetHeadLQueue(LQueue* Q, void* e)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ�� e void*ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue* Q);

/**
 *  @name        : QElemType LengthLQueue(LQueue* Q)
 *    @description : ���г���
 *    @param         Q ����ָ��
 *    @return         : Status
 *  @notice      : None
 */
QElemType LengthLQueue(LQueue* Q);

/**
 *  @name        : Status EnLQueue(LQueue* Q, QNode* p)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ�� p ��Ҫ��ӵĽ��ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status EnLQueue(LQueue* Q, QNode* p);

/**
 *  @name        : Status DeLQueue(LQueue* Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status DeLQueue(LQueue* Q);

/**
 *  @name        : void ClearLQueue(LQueue* Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��
 *    @return         : none
 *  @notice      : None
 */
Status ClearLQueue(LQueue* Q);

/**
 *  @name        : Status TraverseLQueue(const LQueue* Q, void(*foo)(void* q))
 *    @description : ��������
 *    @param         Q ����ָ�� *fooָ������ָ��
 *    @return         : Status
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue* Q, void(*foo)(void* q));

/**
 *  @name        : void LPrint(void** q)
 *    @description : ��������
 *    @param         void**��ָ��
 *    @return         : none
 *  @notice      : None
 */
void LPrint(void** q);

/**
 *  @name        : QNode* ChosenType(LQueue*Q)
 *    @description : ѡ���������������
 *    @param         Q ָ����е�ָ��
 *    @return         : Status
 *  @notice      : None
 */
QNode* ChosenType(LQueue*Q);



