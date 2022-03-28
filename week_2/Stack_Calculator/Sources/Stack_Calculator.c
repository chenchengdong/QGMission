#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"Stack_Calculator.h"

/*初始化栈*/
int InitStack(Stack* s) {
	s->top = NULL;
	s->count = 0;
	return OK;
}

/*判断栈是否为空*/
int EmptyStack(Stack* s) {
	if (s->count == 0) {
		return ERROR;
	}
	if (s->count != 0) {
		return OK;
	}
}

/*入栈*/
int Push(Stack* s, int e) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		return ERROR;
	}
	p->data = e;
	p->next = s->top;
	s->top = p;
	s->count++;
	return OK;
}

/*出栈*/
int Pop(Stack* s) {
	int e;
	if (NULL == s->top) {             //此时为空栈
		return ERROR;
	}
	Node* p = s->top;
	e = p->data;
	s->top = p->next;
	free(p);
	s->count--;
	return e;                       //返回出栈元素
}

/*获取栈顶元素*/
int GetTop(Stack* s) {
	if (NULL == s->top) {
		return ERROR;            //此时为空栈
	}
	return (s->top->data);      //返回栈顶元素
}

/*优先级判断*/
int Priority(char s) {
	switch (s) {
	case '(':            //为各种符号分配优先级
		return 0;
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return 0;
	}
}

int main() {
	Stack num, opt;                 //准备两个栈
	int judge = 1;
	while (judge) {
		printf("请输入你想要计算的公式（个位数的加减乘除!!结果不能为负数！）： ");
		char str1[100] = { 0 };            //准备两个大数组
		char str2[100] = { 0 };
		scanf("%s", str1);                 //输入
		int i = 0, j = 0, a, b, c, tem;
		InitStack(&num);                //初始化两个栈，一个用于存放中缀，一个用于存放后缀
		InitStack(&opt);
		for (; str1[i] != '\0'; i++) {
			if (str1[i] >= '0' && str1[i] <= '9') {
				str2[j++] = str1[i];                    //数字时直接输出到另一个数组
				continue;
			}
			if ((str1[i] < '0' || str1[i]>'9') && (EmptyStack(&num) == 0)) {
				Push(&num, str1[i]);                //不为数字且当前为空栈时，直接入栈
				continue;
			}
			if ((str1[i] < '0' || str1[i]>'9') && (EmptyStack(&num) == 1)) {
				if (str1[i] == '(') {
					Push(&num, str1[i]);         //不为数字且不为空栈时，与栈顶元素作优先级判断，如果大于栈顶则入栈，小于等于都要一直出栈知道栈顶小于入栈元素优先级
					continue;                  //特殊情况，当遇到（ 时直接入栈
				}
				a = GetTop(&num);
				b = Priority(a);
				c = Priority(str1[i]);
				if (c >b) {
					Push(&num, str1[i]);           //若优先级大于等于栈顶，则进栈
					continue;
				}
				if (c <= b) {
					for (; tem = GetTop(&num), Priority(tem) >= c;) {
						if (tem == '(') {
							Pop(&num);
							break;
						}
						str2[j++] = tem;
						Pop(&num);                                  //若优先级小于栈顶，则栈顶出栈一直到“小于”新符号的优先级时才停
						if (EmptyStack(&num) == 0) {
							break;
						}
					}
					if (str1[i] == ')') {  //遇到出栈为 ） 时，不用入栈
						continue;
					}
					Push(&num, str1[i]);   //其它符号都要入栈
				}
			}
		}
		while (EmptyStack(&num) != 0) {
			str2[j++] = Pop(&num);
		}
		//后缀表达式运算
		int k = 0, d, e, final;          //创建一个用于遍历后缀表达式的变量k，两个用于运算的变量d,e,和一个最终输出结果的final
		for (; str2[k] != '\0'; k++) {
			if (str2[k] >= '0' && str2[k] <= '9') {
				Push(&opt, str2[k]);
				continue;                              //若是数字则直接进栈
			}
			if (str2[k] < '0' || str2[k]>'9') {        //若不是数字则出来两个数字
				d = Pop(&opt);
				if (d >= '0' && d <= '9') {
					d = d - '0';                 //利用ascii对数字化简
				}
				e = Pop(&opt);
				if (e >= '0' && e <= '9') {
					e = e - '0';              //利用ascii对数字化简
				}
				switch (str2[k]) {         //进行运算
				case '+':
					Push(&opt, (e + d));
					break;
				case '-':
					Push(&opt, (e - d));
					break;
				case '*':
					Push(&opt, (e * d)); break;
				case '/':
					Push(&opt, (e / (d * 1.0))); break;   //运算完结果入栈
				}
			}
		}
		final = Pop(&opt);
		printf("结果为： %d\n", final);
		printf("按任意键继续...");
		_getch();
		system("cls");
		printf("是否要继续运算？是请按1，否请按0 ：  ");
		scanf("%d", &judge);
		printf("按任意键继续...");
		_getch();
		system("cls");
	}
}