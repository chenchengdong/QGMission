#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"duLinkedList.h"

DuLinkedList headNode() {                       //创建一个表头结点函数
	DuLinkedList head;
	if ((head = (DuLinkedList)malloc(sizeof(DuLNode))) == NULL) {
		printf("内存不足!\n");
	}
	head->prior = NULL;
	head->next = NULL;
	return head;
}

/*创建新链表函数*/
DuLinkedList InitList_DuL(DuLinkedList L) {
	printf("初始化链表成功!\n");
	printf("请输入你需要创建的结点个数:\n");
	int num,ret;
	while (1) {
		ret = scanf("%d", &num);
		rewind(stdin);                   //情况缓冲区的错误输入
		printf("\n");
		if (ret == 0) {
			printf("输入错误!请重新输入:");

		}
		if (ret == 1 && num < 0) {
			printf("输入不为正确结点个数!请重新输入:");
		}
		if (ret == 1 && num >= 0) {
			fflush(stdin);
			break;                         //输入正确的情况下退出循环
		}
	}
	if (num == 0) {
		return L;			//当输出创建结点为0时
	}
	DuLinkedList p1 = NULL, p2 = NULL;
	int i;
	for (i = 1; i <= num; i++) {
		if ((p1 = (DuLinkedList)malloc(sizeof(DuLNode))) == NULL) {
			printf("内存不足!\n");
		}
		printf("请输入第%d个结点的值:", i);
		while (1) {
			ret = scanf("%d", &p1->data);
			rewind(stdin);                   //清空缓冲区的错误输入
			printf("\n");
			if (ret == 0) {
				printf("输入错误!请重新输入第%d个结点的值:", i);

			}
			if (ret == 1) {
				fflush(stdin);
				break;                         //输入正确的情况下退出循环
			}
		}
		if (i == 1) {
			p2 = p1;
			L->next = p1;  //表头结点的后继与第一个几点连接
			p1->prior = L; //第一个结点的前驱连接在表头处
		}
		else {
			p2->next = p1;  //第二个结点的后继连接第三个结点
			p1->prior = p2;	//第三个结点的前驱连接第二个结点
			p2 = p1;       //p2移动到p1处
		}
	}
	p2->next = NULL;    //最后一个结点指向空，此时链表创建完毕
	return L;
}

/*删除整个链表函数*/
ElemType DestroyList_Dul(DuLinkedList* L) {
	if ((*L) == NULL) return ERROR;
	DuLinkedList p1 = NULL, p2 = NULL;   //p1用于定位要删除结点
	p1 = (*L)->next;
	while (p1 != NULL) {
		p2 = p1->next;
		free(p1);
		p1 = p2;
	}
	(*L)->next = NULL;
	return ERROR;

}

/*插入结点（前端插入）函数*/
ElemType InsertBeforeList_DuL(DuLinkedList* L) {
	if ((*L) == NULL) {
		printf("未初始化链表~\n");
		return ERROR;
	}
	DuLinkedList p1 = (*L)->next;
	DuLNode* p = NULL, * q = NULL;
	int ret;                                    //用于判断是否正确输入
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	q = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	q->next = NULL, q->prior = NULL;
	printf("请输入你需要插入的位置的数据:");
	ret=scanf("%d", &p->data);
	rewind(stdin);                      //清空缓存区的错误输入
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;
	}
	printf("\n请输入你需要插入的数据:");
	ret=scanf("%d", &q->data);
	rewind(stdin);
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;
	}
	while (p1 != NULL) {
		if (p1->data == p->data) {
			q->next = p1;
			q->prior = p1->prior;
			p1->prior->next = q;
			p1->prior = q;
			return SUCCESS;
		}
		p1=p1->next;
	}
	printf("没有找到你要插入的位置噢~\n");
	return ERROR;
}

/*插入结点（后端插入）函数*/
ElemType InsertAfterList_DuL(DuLinkedList* L) {
	if ((*L) == NULL) {
		printf("未初始化链表~\n");
		return ERROR;
	}
	DuLinkedList p1 = (*L)->next;
	DuLNode* p = NULL, * q = NULL;
	int ret;                                       //用于判断是否正确输入
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	q = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	q->next = NULL, q->prior = NULL;
	printf("请输入你需要插入的位置的数据:");
	ret=scanf("%d", &p->data);
	rewind(stdin);
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;
	}
	printf("\n请输入你需要插入的数据:");
	ret=scanf("%d", &q->data);
	rewind(stdin);
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;                         //非法输入直接返回
	}
	while (p1 != NULL&&p1->next!=NULL) {                //不能是最后一个位置插入或者空结点时插入  特殊情况
		if (p1->data == p->data) {
			q->prior = p1;
			q->next = p1->next;
			p1->next->prior = q;
			p1->next = q;
			return SUCCESS;
		}
		p1 = p1->next;
	}
	if (p1 == NULL) {
		printf("没有找到你想插入的位置噢~\n");              //当只有一个表头结点时，无法插入
		return ERROR;
	}
	if ((p1->next == NULL) && (p1->data == p->data)) {   //当要插入的地方为表尾时，单独处理
		p1->next = q;
		q->prior = p1;
		q->next = NULL;
		return SUCCESS;
	}
	printf("没有找到你想要插入值的位置噢~\n");
	return ERROR;
}

/*删除结点并取值*/
ElemType DeleteList_DuL(DuLinkedList L, ElemType *e) {
	if (L == NULL) {
		printf("未初始化链表~\n");
		return ERROR;                      //未初始化链表直接返回
	}
	DuLinkedList p1 = L->next,p2 = NULL;    //p2用于指向那个被删除的结点
	DuLinkedList p=NULL;
	int ret;                                   //用于判断非法输入
	p = (DuLinkedList)malloc(sizeof(DuLNode));
	p->next = NULL, p->prior = NULL;
	printf("请输入你要删除结点的前结点的数据:");
	ret=scanf("%d", &p->data);
	rewind(stdin);
	if (ret == 0) {
		printf("输入不正确!\n");
		return ERROR;
	}
	while (p1 != NULL&&p1->next!=NULL) {        //输入要删除值的前一个值如果是最后一个值，则无法删除
		if (p1->data == p->data) {
			*e = p1->next->data;
			p2 = p1->next;
			p1->next = p2->next;
			p2->next->prior = p1;   //将要删除的结点的前一个结点与后一个结点连接起来
			printf("删除的数据为:%d\n\n", p2->data);
			free(p2);
			return SUCCESS;
		}
		p1 = p1->next;
	}
	printf("没有找到你要删除的值，请思考后再来删除嗷~\n");       //没找到值返回     
	return ERROR;
}

/*输出链表函数*/
void TraverseList_DuL(DuLinkedList L) {
	if (L == NULL) {
		printf("未初始化链表~\n");
		return;                  //未初始化不能输出，直接返回
	}
	DuLinkedList p1 = L->next;
	printf("当前链表为:");
	while (p1 != NULL) {
		printf("%d->", p1->data);
		p1 = p1->next;
	}
	printf("NULL");
	printf("\n\n");
}





int main() {
	DuLinkedList L = NULL;    //创建用于指向表头结点的指针
	int e1 = 0;               //创建用于返回删除值变量
	int judge = 1;
	while (judge) {
		printf("\n\n");
		printf("                    ******************************系统功能菜单******************************\n");
		printf("                    -----------------------------------------------------------------------\n");
		printf("                         *************************************************************\n");
		printf("                         * 1.创建新链表                **       2.销毁链表并退出程序 *\n");
		printf("                         *************************************************************\n");
		printf("                         * 3.插入新结点（前段插入）    **     4.插入新结点(后端插入) *\n");
		printf("                         *************************************************************\n");
		printf("                         * 5.删除结点取值              **       6.输出链表           *\n");
		printf("                    -----------------------------------------------------------------------\n");
		printf("                    请选择菜单编号:");
		int option,ret;
		while (1) {
			ret = scanf("%d", &option);
			rewind(stdin);                  //清空缓冲区错误输入
			printf("\n");
			if (ret == 0) {
				printf("输入错误!请重新输入:");
			}
			if (ret == 1 && (option < 1 || option>6)) {
				printf("输入错误!请重新输入:");
			}
			if (ret == 1 && (option >= 1 && option <= 6)) {
				fflush(stdin);
				break;                      //输入正确情况下退出循环
			}
		}
		system("cls");
		switch (option) {
		case 1:L = InitList_DuL(headNode()); break;
		case 2:judge=DestroyList_Dul(&L); break;
		case 3:InsertBeforeList_DuL(&L); break;
		case 4:InsertAfterList_DuL(&L); break;
		case 5:DeleteList_DuL(L, &e1); break;
		case 6:TraverseList_DuL(L); break;

		}
		printf("按任意键继续...");
		_getch();
		system("cls");
		if (judge != 0)judge = 1;
	}

}