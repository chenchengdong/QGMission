#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"LinkStack.h"

/*初始化栈*/
Status initLStack(LinkStack** s) {
	*s = (LinkStack*)malloc(sizeof(LinkStack));
	if (*s == NULL) {
		printf("无法申请内存空间！\n");
		return ERROR;                              //内存不足则返回
	}
	(*s)->top = NULL;                              //初始化使指向栈链的结构体指针中的top指针赋为NULL
	(*s)->count = 0;                               //栈链的结点个数赋为0
	printf("栈初始化完毕！\n");
	return SUCCESS;
}

/*判断栈是否为空函数*/
Status isEmptyLStack(LinkStack* s) {
	if (!s) {
		/*printf("栈未初始化！\n");*/
		return UNUSUAL;
	}                                 //未初始化
	if (s->top == NULL) {
		/*printf("栈为空栈！\n");*/       //空栈的情况
		return ERROR;
	}
	if (s->top != NULL) {
		/*printf("栈不为空栈！\n");*/
		return SUCCESS;             //不为空栈时
	}
}

/*得到栈顶元素函数*/
Status getTopLStack(LinkStack* s, SElemType* e) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");
		return UNUSUAL;
	}
	if (check == 0) {
		printf("栈为空栈！\n");
		return ERROR;
	}
	*e = s->top->data;
	printf("栈顶元素为：%d\n", s->top->data);
	return SUCCESS;
}

/*清空栈函数*/
Status clearLStack(LinkStack* s) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");
		return UNUSUAL;
	}
	if (check == 0) {
		printf("栈为空栈！不需要清空\n");
		return ERROR;
	}
	SElemType assiss=0;
	while (s->top != NULL) {                     //若不为空栈，则调用出栈函数进行清栈
		popStack(s, &assiss);
	}
	return SUCCESS;
}

/*销毁栈函数*/
Status destroyLStack(LinkStack* s) {
	if (!s) {
		printf("栈销毁完毕！\n");
		return ERROR;          //无论如何都是返回ERROR，因为要退出程序
	}
	if (s->top == NULL) {
		free(s);
		printf("销毁栈完毕！\n");
		return ERROR;                //避免提示性文字重复，若是空栈在这一步就返回
	}
	clearLStack(s);
	free(s);
	printf("栈销毁完毕！\n");
	return ERROR;               //销毁栈之后返回ERROR（0），用于退出程序
}

/*检测栈长度函数*/
Status LStackLength(LinkStack* s, int* length) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");
		return UNUSUAL;
	}
	*length = s->count;
	printf("当前栈的长度为：%d\n", *length);    //输出栈长
	return SUCCESS;
}

/*入栈函数*/
Status pushLStack(LinkStack* s, SElemType data) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");                   //栈未初始化直接返回
		return UNUSUAL;
	}
	StackNode* p1 = (StackNode*)malloc(sizeof(StackNode));
	p1->data = data;
	p1->next = NULL;
	if (check == 0) {
		s->top = p1;                             //栈未空栈时第一个结点链接特殊
		s->count++;
		printf("入栈完毕！\n");
		return SUCCESS;
	}
	p1->next = s->top;
	s->top = p1;
	s->count++;
	printf("入栈完毕！\n");
	return SUCCESS;
}

/*出栈函数*/
Status popStack(LinkStack* s, SElemType* data) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");
		return UNUSUAL;                     //未初始化直接返回
	}
	if (check == 0) {
		printf("栈未空栈！不能出栈！\n");
		return ERROR;                    //空栈不能出栈
	}
	LinkStackPtr p=s->top;
	s->top = s->top->next;
	s->count--;                       //出栈后个数减1
	free(p);
	return SUCCESS;
}

/*生成入栈元素函数*/
SElemType* StackElement(LinkStack*s) {             //这里用返回指针类型是为了防止输入-1时于栈未初始化的返回值冲突，用NULL解决
	if (!s) {
		printf("栈未初始化！\n");
		return NULL;
	}
	SElemType* element = (SElemType*)malloc(sizeof(SElemType));
	if (element == NULL) {
		printf("无法开辟内存！\n");
		return NULL;
	}
	int ret;
	printf("请输入你要进栈的数：");                  //在这个函数里面生成好了要进栈的元素后在当作参数传参
	while (1) {
		ret=scanf("%d", element);
		printf("\n");
		rewind(stdin);                             //清空错误输入缓存
		if (ret == 0) {
			printf("输入错误！请重新输入：");        //若错误输入则重新输入
		}
		if (ret == 1) {
			fflush(stdin);                       //若正确输入则跳出循环
			break;
		}
	}
	return element;
}

/*遍历输出栈元素函数*/
Status TraverseLStack(LinkStack* s) {
	int check;
	check = isEmptyLStack(s);
	if (check == -1) {
		printf("栈未初始化！\n");
		return UNUSUAL;                     //未初始化直接返回
	}
	if (check == 0) {
		printf("栈未空栈！没有元素\n");
		return ERROR;                    //空栈不能遍历
	}
	LinkStackPtr p = s->top;            //定义一个用于遍历的指针
	printf("栈顶->栈尾\n");             
	while (p!= NULL) {
		printf("栈元素：%d\n",p->data);
		p = p->next;
	}
}

/*主函数*/
int main() {
	LinkStack* s = NULL;
	int judge = 1,check;
	SElemType e1,*e2,length;                    //分别为获取的栈顶元素,入栈元素和栈链长度
	while (judge) {
		printf("\n\n");
		printf("                         ******************************系统功能菜单******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.初始化栈                **         2.判断栈是否为空栈    *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.栈顶元素                **         4.清空栈              *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.销毁栈(并退出)          **         6.查看栈的长度        *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.入栈操作                **         8.出栈操作            *\n");
		printf("                              **************************************************************\n");
		printf("                              *                    9.遍历输出栈元素（栈顶->栈底）          *\n");
		printf("                              **************************************************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              请选择菜单编号：");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);                                 //用于清空错误输入缓存
			if (ret == 0) {
				printf("                         输入错误！请重新输入：");
			}
			if (ret == 1) {
				fflush(stdin);
				break;
			}
		}
		system("cls");
		switch (option) {
		case 1:initLStack(&s); break;                          //初始化栈函数
		case 2:
			check=isEmptyLStack(s);
			if (check == -1) printf("栈未初始化！\n");          //判断是否为空栈
			else if (check == 0) printf("栈为空栈！\n");
			else printf("栈不为空栈！\n");
			break;
		case 3:getTopLStack(s, &e1); break;                      //获得栈顶元素函数
		case 4:
			check=clearLStack(s);
			if (check == 1) printf("清空栈完毕！\n");
			break;                                           //清空栈函数
		case 5:judge=destroyLStack(s); break;         //销毁栈函数
		case 6:LStackLength(s, &length); break;       //获得栈顶元素
		case 7:
			e2 = StackElement(s);
			if (e2 != NULL) {
				pushLStack(s, *e2);                     //入栈操作
			}
			break;
		case 8:
			check=popStack(s, &e1);
			if (check == 1) printf("出栈完毕！\n");
			break;                 //出栈操作
		case 9:TraverseLStack(s); break;               //遍历输出栈元素
		default:printf("请重新输入正确的菜单选项："); break;
		}
		printf("按任意键继续...");
		_getch();                                   //等待用户输入
		system("cls");                              //清屏
	}
}