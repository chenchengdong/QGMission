// define element type
typedef int SElemType;

// define struct of LinkStack list
typedef struct StackNode {
	SElemType data;
	struct StackNode* next;
}StackNode, * LinkStackPtr;

//定义一个指向栈顶的结构体
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
 *    @description : 初始化栈
 *    @param         s 栈指针s
 *  @notice      : Status
 */
Status initLStack(LinkStack** s);

/**
 *  @name        : Status isEmptyLStack(LinkStack* s)
 *    @description : 检查栈链是否为空
 *    @param         s 栈指针s
 *    @return         : Status
 *  @notice      : None
 */
Status isEmptyLStack(LinkStack* s);

/**
 *  @name        : Status getTopLStack(LinkStack* s, SElemType* e)
 *    @description : 获取栈顶元素
 *    @param         s 栈指针s，e 用于返回栈顶元素值指针
 *    @return         : Status
 *  @notice      : None
 */
Status getTopLStack(LinkStack* s, SElemType* e);

/**
 *  @name        : Status clearLStack(LinkStack* s)
 *    @description : 清空栈链
 *    @param         s 栈指针s
 *    @return         : Status
 *  @notice      : None
 */
Status clearLStack(LinkStack* s);

/**
 *  @name        : Status destroyLStack(LinkStack* s)
 *    @description : 销毁栈
 *    @param         s 栈指针s
 *    @return         : Status
 *  @notice      : None
 */
Status destroyLStack(LinkStack* s);

/**
 *  @name        : Status LStackLength(LinkStack* s, int* length)
 *    @description : 查看栈链长度
 *    @param         s 栈指针s ， length 用于返回栈链长度值指针
 *    @return         : Status
 *  @notice      : None
 */
Status LStackLength(LinkStack* s, int* length);

/**
 *  @name        : Status pushLStack(LinkStack* s, SElemType data)
 *    @description : 入栈操作
 *    @param         s 栈指针s ，data 入栈元素值
 *    @return         : Status
 *  @notice      : None
 */
Status pushLStack(LinkStack* s, SElemType data);

/**
 *  @name        : Status popStack(LinkStack* s, SElemType* data)
 *    @description : 出栈操作
 *    @param         s 栈指针s ，data 返回出栈元素值指针
 *    @return         : Status
 *  @notice      : None
 */
Status popStack(LinkStack* s, SElemType* data);

/**
 *  @name        : SElemType* StackElement(LinkStack* s)
 *    @description : 生成入栈元素
 *    @param         s 栈指针s 
 *    @return         : SElemType*
 *  @notice      : None
 */
SElemType* StackElement(LinkStack* s);

/**
 *  @name        : Status TraverseLStack(LinkStack* s)
 *    @description : 遍历输出栈元素
 *    @param         s 栈指针s
 *    @return         : Status
 *  @notice      : None
 */
Status TraverseLStack(LinkStack* s);