// define element type
typedef int SElemType;

// define struct of LinkStack list
typedef struct StackNode {
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

//����һ��ָ��ջ���Ľṹ��
typedef struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;

// define status
typedef enum {
	ERROR = 0,
	SUCCESS = 1,
	UNUSUAL = -1
}Status;

/**
 *  @name        :Status initLStack(LinkStack** s)
 *    @description : ��ʼ��ջ
 *    @param         s ջָ��s
 *  @notice      : Status
 */
Status initLStack(LinkStack** s);

/**
 *  @name        : Status isEmptyLStack(LinkStack* s)
 *    @description : ���ջ���Ƿ�Ϊ��
 *    @param         s ջָ��s
 *    @return         : Status
 *  @notice      : None
 */
Status isEmptyLStack(LinkStack* s);

/**
 *  @name        : Status getTopLStack(LinkStack* s, SElemType* e)
 *    @description : ��ȡջ��Ԫ��
 *    @param         s ջָ��s��e ���ڷ���ջ��Ԫ��ֵָ��
 *    @return         : Status
 *  @notice      : None
 */
Status getTopLStack(LinkStack* s, SElemType* e);

/**
 *  @name        : Status clearLStack(LinkStack* s)
 *    @description : ���ջ��
 *    @param         s ջָ��s
 *    @return         : Status
 *  @notice      : None
 */
Status clearLStack(LinkStack* s);

/**
 *  @name        : Status destroyLStack(LinkStack* s)
 *    @description : ����ջ
 *    @param         s ջָ��s
 *    @return         : Status
 *  @notice      : None
 */
Status destroyLStack(LinkStack* s);

/**
 *  @name        : Status LStackLength(LinkStack* s, int* length)
 *    @description : �鿴ջ������
 *    @param         s ջָ��s �� length ���ڷ���ջ������ֵָ��
 *    @return         : Status
 *  @notice      : None
 */
Status LStackLength(LinkStack* s, int* length);

/**
 *  @name        : Status pushLStack(LinkStack* s, SElemType data)
 *    @description : ��ջ����
 *    @param         s ջָ��s ��data ��ջԪ��ֵ
 *    @return         : Status
 *  @notice      : None
 */
Status pushLStack(LinkStack* s, SElemType data);

/**
 *  @name        : Status popStack(LinkStack* s, SElemType* data)
 *    @description : ��ջ����
 *    @param         s ջָ��s ��data ���س�ջԪ��ֵָ��
 *    @return         : Status
 *  @notice      : None
 */
Status popStack(LinkStack* s, SElemType* data);

/**
 *  @name        : SElemType* StackElement(LinkStack* s)
 *    @description : ������ջԪ��
 *    @param         s ջָ��s 
 *    @return         : SElemType*
 *  @notice      : None
 */
SElemType* StackElement(LinkStack* s);

/**
 *  @name        : Status TraverseLStack(LinkStack* s)
 *    @description : �������ջԪ��
 *    @param         s ջָ��s
 *    @return         : Status
 *  @notice      : None
 */
Status TraverseLStack(LinkStack* s);