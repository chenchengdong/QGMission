#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"linkList.h"


/*初始化链表函数*/
LinkedList InitList(LinkedList L) {
	printf("初始化链表成功！\n");
	printf("请输入你需要创建的结点个数：");
	int num,ret; /*定义用于检测非法输入的变量*/
	while (1) {
		ret = scanf("%d", &num);         /*若非法输入返回值为0*/
		rewind(stdin);                   /*清空缓冲区的错误输入*/
		printf("\n");
		if (ret == 0) {
			printf("输入错误!请重新输入:");
		}
		if (ret == 1 && num < 0) {                    /*如果创建结点的个数为负数，则当作非法输入处理*/
			printf("输入不为正确结点个数!请重新输入:");
		}
		if (ret == 1&&num>=0) {
			fflush(stdin);
			break;                         /*输入正确的情况下退出循环，进入创建结点部分*/
		}
	}
	if(num==0){           /*特殊情况，当输入创建的结点为0时,此时只有一个表头结点*/
		return L;
	} 
	LinkedList p1 = NULL, p2 = NULL; /*定义用于创建结点连接成链表的结构体指针*/
	int i;
	for (i = 1; i <= num; i++) {
		if ((p1 = (LinkedList)malloc(sizeof(LNode))) == NULL) {
			printf("CAN NOT CREATE NODE FOR YOU\n");
		}
		printf("请输入第%d个结点的值:", i);
		while (1) {
			ret=scanf("%d", &p1->data);
			rewind(stdin);                   /*清空缓冲区的错误输入*/
			printf("\n");
			if (ret == 0) {
				printf("输入错误!请重新输入第%d个结点的值:",i);
			}
			if (ret == 1) {
				fflush(stdin);
				break;                         /*输入正确的情况下退出循环*/
			}
		}
		if (i == 1) {
			p2 = p1;
			L->next = p1;                     /*表头结点连接在第一个结点前*/
		}                                     /*如果是第一个结点，则p2, p1指向同一个结点*/
		else {
			p2->next = p1;
			p2 = p1;
		}
	}
	p2->next = NULL;
	return L;
}


/*销毁链表函数*/
ElemType DestroyList(LinkedList* L) {
	if ((*L) == NULL) return 0;             /*未初始化链表直接退出程序*/
	LinkedList p1 = NULL, p2 = NULL;
	p1 = (*L)->next;
	while (p1 != NULL) {
		p2 = p1->next;		               /*p2总是指向位于p1的后继*/
		free(p1);			              /*释放p1所在结点空间*/
		p1 = p2;				         /*p1指向p2所在结点--如此循环遍历删除链表*/
	}
	(*L)->next = NULL;
	return 0;
}

/*插入结点函数*/
LinkedList InsertList(LinkedList* L) {
	if ((*L) == NULL) {
		printf("未初始化链表\n");
		return (*L);                                   /*未初始化链表直接返回*/
	}
	LNode* p, * q;
	int ret;                                          /*用于检测非法输入*/
	p = (LNode*)malloc(sizeof(LNode));                /*循环链表也可以插入值，只是最后输出不了*/
	q = (LNode*)malloc(sizeof(LNode));
	p->next = NULL, q->next = NULL;
	printf("请输入你需要插入位置的前一个数据:");
	ret=scanf("%d", &p->data);
	rewind(stdin);                   /*清空缓冲区的错误输入*/
	if (ret == 0) {
		printf("输入不正确!\n");        /*非法输入直接返回结构体指针*/
		return (*L);
	}
	printf("\n请输入你需要插入的数据:");
	ret=scanf("%d", &q->data);
	rewind(stdin);                   /*清空缓冲区的错误输入*/
	if (ret == 0) {
		printf("输入不正确!\n");
		return (*L);                //非法输入直接返回
	}
	LinkedList p1 = (*L)->next;
	while (p1 != NULL) {                //修改条件  p1->next可以为空
		if (p1->data == p->data) {
			q->next = p1->next;			//先将q连接到p1的后继 
			p1->next = q; 				//再将q与p1连接，使其成为p1的后继
			printf("插入完毕!\n");
			return (*L);                //插入完之后立刻返回
		}
		p1 = p1->next;
	}
	printf("没有找到插入位置的值哦~\n请思考后再来尝试吧\n");
	return (*L);
}

/*删除结点并取值的函数*/
LinkedList DeleteList(LinkedList L, ElemType* e) {
	if (L == NULL) {
		printf("未初始化链表哦~\n");
		return L;                             //未初始化链表直接返回
	}
	LinkedList p1 = L->next,p2=NULL;         //定义p2用于指向那个被删除的数据         
	LNode* p;                                //循环链表也可以用于删除值
	int ret;                                    //用于判断是否正确输入
	p = (LinkedList)malloc(sizeof(LNode));
	p->next = NULL;
	printf("请输入你要删除结点的前结点的数据:");
	ret=scanf("%d", &p->data);                 //创建一个结点来装需要删除的值
	rewind(stdin);                       //清空缓冲区的错误输入
	if (ret == 0) {
		printf("输入不正确!\n");           //非法输入直接返回
		return L;
	}
	while (p1 != NULL&&p1->next!=NULL) {
		if (p1->data == p->data) {
			*e = p1->next->data;           //返回p结点的值 
			p2 = p1->next;
			p1->next = p1->next->next;    //将除了p的两边的结点连接起来 
			printf("删除的数据为:%d\n\n", p2->data);
			free(p2);
			return L;                   //删除完数据之后可以立刻返回了
		}
		p2 = p1;                        //这里p2有两个作用，1是保持在p1的前一个结点处，2是在发现需要删除的值位于中间时作标记删除指针
		p1 = p1->next;
	}
	//if (p1->next == NULL && (p1->data == p->data)) {
	//	p2 = NULL;						//这种情况出来时，有两个特征：1.链表刚好遍历到表尾  2.需要删除的结点就是该结点  注：p2除了删除在中间的结点的情况都在p1前一个结点
	//	free(p1); 
	//	return L;
	//}
	printf("没有找到你要删除的值,请认真思考过后再来删除嗷~\n");    //如果没有从上面循环的return返回，则判定为没找到删除值的前一个值，返回原链表
	return L;
}

/*查询结点函数*/
ElemType SearchList(LinkedList L) {
	if (L == NULL) {
		printf("未初始化链表哦~\n");
		return ERROR;                       //未初始化链表返回
	}
	LinkedList p1 = L->next;
	int e,ret;                               //ret用于判断是否非法输入
	printf("请输入你需要查询的值:");
	ret=scanf("%d", &e);
	rewind(stdin);                       //清空缓冲区的错误输入
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;                 //非法输入直接返回
	}
	while (p1 != NULL) {
		if (p1->data == e) {
			printf("%d存在链表中\n",e);
			return SUCCESS;
		}
		p1 = p1->next;
	}
	printf("%d不存在链表中", e);
	return ERROR;
}

/*链表逆序函数*/
ElemType ReverseList(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("链表损坏，无法操作\n");
		return ERROR;                                          //判断是否为循环链表，若是则无法逆序
	}
	if ((*L) == NULL) {
		printf("未初始化链表哦~\n");
		return (*L);                                          //为初始化链表直接返回
	}
	LinkedList cur = (*L)->next, p1 = cur->next, nex = NULL;  //cur表示p1的前继结点，nex表示p1的后继结点 
	/*Status cheak1;*/
	if (!cur) {
		printf("还没创建结点哦~\n");
		return ERROR;       //只有一个头结点时，无法逆序，返回0 
	}
	while (p1 != NULL) {
		nex = p1->next;
		p1->next = cur;
		if ((*L)->next == cur) {
			cur->next = NULL;			//如果cur的前继是头结点的话，将cur的next指向NULL 
		}
		cur = p1;					//cur移动到p1处 
		p1 = nex;					//p1移动到nex处 
	}
	(*L)->next = cur;            //将头结点与逆序后的链表连接起来
	printf("逆序完毕!\n");
	return SUCCESS;              //逆序完返回成功success
};

/*判断成环函数*/
ElemType IsLoopList(LinkedList L) {
	if (L == NULL) {
		printf("还没有初始化链表哦~\n");
		return ERROR;                            //当没有初始化链表时直接返回
	}
	LinkedList fast = L->next, slow = L->next;    //开始时都指向第一个有数据的结点
	
	if (!fast) {
		printf("不是循环链表!\n");
		return ERROR;          //如果只有一个头结点，且不为循环链表，则返回0
		
	}
	if (fast->next == fast) {
		printf("是循环链表!\n");
		return SUCCESS;        //如果只有一个头结点，且依然是个循环链表，则返回1 
	}
	while (fast!=NULL && fast->next!=NULL) {
		slow = slow->next;
		fast = fast->next->next;
		if (fast == NULL || slow == NULL) {
			printf("不是循环链表!\n");
			return ERROR;				//如果fast或者slow出现了到达NULL的情况，则判定为不是循环链表 
		}
		if (fast == slow || fast->next == slow) {
			printf("是循环链表!\n");
			return SUCCESS;					//如果fast追上看slow或者跑到了slow的后面，则为循环链表 
			
		}
		
	}
	printf("不是循环链表!\n");
}

/*找到链表的中间结点函数*/
LNode* FindMidNode(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("链表损坏，无法操作\n");
		return (*L);                                          //判断是否为循环链表，若是则无法操作
	}
	if ((*L) == NULL) {
		printf("未初始化链表哦~\n");                                //为初始化链表时找不到中点数据，直接返回
		return(*L);
	}
	LinkedList fast = (*L)->next, slow = fast;                         //定义一个快指针一个慢指针
	if (!fast) {
		return 0;                   //如果只有一个头结点，则返回0 
	}
	while (slow!=NULL) {
		if (fast->next == NULL || fast->next->next == NULL) {       //当fast指针的后继为表尾时，此时为偶数结点个数的链表的第一个中点 
			break;                                 //当fast指针走到表尾时，此时为奇数结点个数的链表中点 
		}
		fast = fast->next->next;     //fast指针一次走两步 
		slow = slow->next;           //slow指针一次走一步 
	}
	printf("中点数据为:%d\n\n", slow->data);
	return slow;
}

/*将结点奇偶对换函数*/
LNode* ReverseEvenList(LinkedList* L) {
	int check;
	check = IsLoopList(*L);
	if (check == 1) {
		printf("链表损坏，无法操作\n");
		return (*L);                                          //判断是否为循环链表，若是则无法操作
	}
	if ((*L) == NULL) {
		printf("未初始化链表哦~\n");
		return(*L);                                         //未初始化链表就直接返回
	}
	LinkedList p1 = (*L)->next;
	if (p1 == NULL) { 
		printf("还没有创建结点哦~\n酱紫是无法奇偶对换滴~\n");
		return 0;                       //排除只有一个表头结点的情况，无法奇偶对换
	}
	LinkedList p2 = p1->next;	         //p1指向奇数结点，p2指向偶数结点
	
	int tem = 0;                        //用于交换奇偶结点值的中间变量
	while (p2!=NULL&&p2->next!=NULL) {
		tem = p1->data;
		p1->data = p2->data;
		p2->data = tem;              //将奇偶结点数据域换一下即可 
		p1 = p1->next->next;			//p1、p2每次都向后走两个结点 
		p2 = p2->next->next;
	}
	if (p2 == NULL) {
		printf("奇偶反转完毕!\n");
		return (*L);				//由于p2指向偶数位数的结点，所有p2会更先到达NULL或者NULL的前一个结点
	}								//如果到达NULL的话表明为共奇数个结点，所以直接返回逆序完的链表（此情况会包含只有1个结点的情况）
	else {
		tem = p1->data;				//如果p2到达NULL的前一个结点，则说明还有最后两个结点未逆序，故先作最后的逆序再返回链表
		p1->data = p2->data;
		p2->data = tem;
		printf("奇偶反转完毕!\n");
		return (*L);			
	}
}


/*创建表头结点函数*/
LinkedList HeadNode() {
	LinkedList head;
	if ((head = (LinkedList)malloc(sizeof(LNode))) == NULL) {
		printf("内存不足！\n");
	}
	head->next = NULL;
	return head;
}

/*构造循环链表函数*/
LinkedList CreateLoopList(LinkedList L) {
	if (L == NULL) {
		printf("未初始化链表哦~\n");
		return L;                             //未初始化链表直接返回
	}
	LinkedList p1 = L->next;                  //创建一个用于循环链表的指针
	if (p1 == NULL) {
		L->next = L;
		return L;                         //当没有创建有数据的结点时，表头结点自己形成一个循环链表
		printf("构造循环链表完毕!\n");
	}                                    
	while (p1->next != NULL) {
		p1 = p1->next;				//遍历链表到表尾 
	}
	p1->next = L;           			//将表尾与表头相连 构成循环
	printf("构造循环链表完毕!\n");        
	return L;
}

/*输出链表函数*/
ElemType TraverseList(LinkedList L) {
	if (L == NULL) {
		printf("还没有创建链表哦~\n请创建链表了之后再来吧~\n");    //这种情况是头结点都没有创建，此时不输出
		return ERROR;
	}
	int check;
	check=IsLoopList(L);                                           //调用判断是否是循环链表函数
	LinkedList p1 = L->next;
	if (check == 1) {
		printf("链表损坏，无法输出\n");                       //如果是循环链表的化将无法输出
		return;
	}
	if (p1 == NULL) {                                       //这种情况是只创建了个头结点，且不为循环链表
		printf("当前链表为:");
		printf("NULL");
		return;                                                      //返回
	}
	printf("当前链表为:");
	while (p1 != NULL) {
		printf("%d->", p1->data);
		p1 = p1->next;
	}
	printf("NULL");
	printf("\n\n");
	return;
}


int main() {
	LinkedList L = NULL;	//创建用于指向表头结点的指针 
	int e1 = 0;           //创建用于返回删除值变量 
	int judge = 1;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************系统功能菜单******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.创建新链表                  **      2.插入新节点         *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.输出链表                    **      4.将链表逆序         *\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.找到单链表的中点            **      6.判断是否成环       *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.删除结点取值                **      8.奇偶反转           *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      9.查询数据是否在表中                  *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      10.删除链表并退出系统                 *\n");
		printf("                              **************************************************************\n");
		printf("                              *                      11.构造循环链表                       *\n");
		printf("                              **************************************************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              请选择菜单编号:");
		int option,ret;
		while (1) {
			ret = scanf("%d", &option);
			rewind(stdin);                   //清空缓冲区的错误输入
			printf("\n");
			if (ret == 0) {
				printf("                              输入错误!请重新输入:");
				
			}
			if (ret == 1 && (option < 1 || option>11)) {
				printf("                              输入错误!请重新输入:");      //输入不为字符但是不符合选项则继续输入
			}
			if (ret==1&&(option >= 1 && option <= 11)) {
				fflush(stdin);
				break;                         //输入正确的情况下退出循环
			}
			
		}
		system("cls");
		switch (option) {
		case 1:L = InitList(HeadNode());break;	//初始化链表 
		case 2:L = InsertList(&L); break;	//插入新结点 
		case 3:TraverseList(L); break;//输出链表 
		case 4:ReverseList(&L); break;	//将链表逆序 
		case 5:FindMidNode(&L); break;  //找到单链表中点 
		case 6:IsLoopList(L); break;    //判断是否成环 
		case 7:DeleteList(L, &e1); break;  //删除结点取值
		case 8:L = ReverseEvenList(&L); break;  //奇偶反转 
		case 9:SearchList(L); break;                    //查询数据是否在表中 
		case 10:judge=DestroyList(&L); break;        //删除链表并退出系统
		case 11:CreateLoopList(L); break;
		}
		printf("按任意键继续...");
		_getch();
		system("cls");                    //清屏
		if (judge != 0) judge = 1;        //令judge为1，继续出现选择界面 
	}
}