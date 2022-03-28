#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"LQueue.h"

/*初始化队列函数*/
void InitLQueue(LQueue** Q) {
    *Q = (LQueue*)malloc(sizeof(LQueue));
    (*Q)->front = NULL;
    (*Q)->rear = NULL;               //指向队列的结构体中的指针初始化指向NULL
    (*Q)->length = 0;               //开始队列长度为0
    printf("初始化队列完毕！\n");
    return TRUE;
}

/*销毁队列函数*/
Status DestoryLQueue(LQueue* Q) {
    if (!Q) {
        printf("队列销毁完毕！\n");             //未初始化队列返回
        return FALSE;
    }
    if (Q->front == NULL && Q->rear == NULL) {
        free(Q);
        printf("队列销毁完毕！\n");
        return FALSE;                         //避免提示性文字重复，在空队列时在这里就返回了
    }
    ClearLQueue(Q);                            //调用清空队列函数
    free(Q);                                   //清空完队列之后再销毁Q，达到销毁队列的目的
    printf("队列销毁完毕！\n");
    return FALSE;
}

/*查看队头元素函数*/
Status GetHeadLQueue(LQueue* Q, void* e) {
    if (!Q) {
        printf("队列未初始化！\n");
        return FALSE;                         //如果队列未初始化，返回FALSE；
    }
    if (!IsEmptyLQueue(Q)) {
        printf("队列为空！\n");
        return FALSE;                           //要先判断队列是否为空,若空，返回FALSE，这里避免重复提示文字
    }                                           
    e = Q->front->data;                        //将队头结点的指针域赋给void*指针
    printf("队头元素为：");
    switch (Q->front->type) {
    case 1:printf("%d\n", *(int*)e); break;
    case 2:printf("%.2f\n", *(float*)e); break;
    case 3:printf("%c\n", *(char*)e); break;
    case 4:printf("%.4lf\n", *(double*)e); break;
    case 5:printf("%ld\n", *(long*)e); break;
    case 6:printf("%s\n", (char*)e); break;
    case 7:printf("%d\n", *(long int*)e); break;
    case 8:printf("%d\n", *(long long*)e); break;
    case 9:printf("%d\n", *(short int*)e); break;
    }
    return TRUE;
}

/*检查队列是否为空函数*/
Status IsEmptyLQueue(const LQueue* Q) {
    if (!Q) {
        return UNUSUAL;                                   //如果未初始化队列则直接返回
    }
    if (Q->front==NULL&&Q->rear==NULL) {
        return FALSE;                                         //如果Q->front==Q->rear,则队列为空
    }
    if (Q->front!=NULL&&Q->rear!=NULL) {
        return TRUE;                               //如果Q->front!=Q->rear,则队列不为空
    }

}

/*查看队列长度函数*/
QElemType LengthLQueue(LQueue* Q) {
    if (!Q) {
        printf("队列未初始化！\n");
        return 0;                         //未初始化队列则直接返回
    }
    printf("队列长度为：%d\n", Q->length);            //队列长度
    return TRUE;
}

/*入队操作函数*/
Status EnLQueue(LQueue* Q, QNode*p) {
    if (!Q) {
        printf("未初始化队列！\n");               //未初始化队列直接返回
        return FALSE;
    }
    if (Q->front==NULL&&Q->rear==NULL) {
        Q->rear = p;
        Q->front = p;                          //如果是第一个结点入队，则特殊处理
        Q->length++;                           //入队后队长+1
        return TRUE;
    }
    Q->rear->next = p;
    Q->rear = p;
    Q->length++;                             //入队后队长+1
    return TRUE;
}

/*出队操作函数*/
Status DeLQueue(LQueue* Q) {
    if (!Q) {
        printf("队列未初始化！\n");               //未初始化队列直接返回
        return UNUSUAL;
    }
    if (!IsEmptyLQueue(Q)) {
        return FALSE;                           //如果队列为空则直接返回，避免提示语重复
    }
    else {
        QNode* p1 = NULL;
        p1 = Q->front;
        Q->front = Q->front->next;
        if (Q->rear == p1) {
            Q->rear = Q->front;            //如果删除的是队尾，则将队尾指针指向队头
        }
        free(p1);
        Q->length--;
        return TRUE;
    }
}

/*清空队列函数*/
Status ClearLQueue(LQueue* Q) {
    if (!Q) {
        printf("队列未初始化！\n");
        return FALSE;
    }                                                 //判断是否是未初始化队列
    if (!IsEmptyLQueue(Q)) {
        printf("队列为空！无法清空队列！\n");
        return FALSE;                                 //判断是否是空队列,避免重复性提示
    }                                                
    while (Q->front != NULL) {                       //若不为空队列，则调用出队函数进行清空队列
        DeLQueue(Q);
    }                      
    return TRUE;                                        //队列清空完毕
}

/*遍历队列函数*/
Status TraverseLQueue(const LQueue* Q,void(*foo)(void*q)) {
    if (!Q) {
        printf("队列未初始化！\n");                                     //未初始化队列无法输出
        return FALSE;
    }
    if (!IsEmptyLQueue(Q)) {
        printf("队列为空！\n");
        return FALSE;                                                 //队列为空直接返回，避免提示语重复
    }
    else {
        QNode* p1 = NULL;                                                   //定义一个遍历队列指针
        p1 = Q->front;                                                     //使遍历指针指向当前输出的结点
        printf("队头->队尾\n");
        while (p1!= NULL) {
            printf("队列元素：");
            if (p1->type == 1) printf("整型： %d\n", *(int*)(p1->data));
            else if (p1->type == 2) printf("浮点型： %.2f\n", *(float*)(p1->data));
            else if (p1->type == 3) printf("字符型： %c\n", *(char*)(p1->data));
            else if (p1->type == 4) printf("双精度浮点型： %.4lf\n", *(double*)(p1->data));
            else if (p1->type == 5) printf("长整型： %ld\n", *(long*)(p1->data));
            else if (p1->type == 6) printf("字符串型：%s\n", (char*)(p1->data));
            else if (p1->type == 7) printf("long int 型：%d\n", *(long int*)(p1->data));
            else if (p1->type == 8) printf("long long 型：%lld\n", *(long long*)(p1->data));
            else if (p1->type == 9) printf("short int 型：%d\n", *(short int*)(p1->data));
            (*foo)(&p1);
        }
        return TRUE;                                                      //遍历完之后返回TRUE
    }
}

/*操作函数*/
void LPrint(void** q) {
    (QNode*)(*q) = ((QNode*)(*q))->next;
}

/*选择数据类型函数*/
QNode* ChosenType(LQueue*Q) {
    if (!Q) {
        printf("队列未初始化！\n");
        return NULL;
    }
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL) {
        printf("开辟内存失败！\n");
        return;
    }
    p->next = NULL;
    printf("1.整型int;  2.浮点型float;   3.字符型char\n4.双精度浮点型double;     5.长整型long;\n6.字符串类型     7.long int型    8.long long型\n9.short int 型\n请输入需要输入的数据类型：");
    int option,ret;                                    //用于选择输入数据类型和判断异常输入
    while (1) {
        ret=scanf("%d", &option);
        rewind(stdin);
        if (ret == 0) {
            printf("输入错误！请重新输入：");
        }
        if (ret == 1 && (option < 1 || option>9)) {
            printf("请重新输入正确选项：");
        }
        if (ret == 1 && (option >= 1 && option <= 9)) {
            fflush(stdin);                                  //正确输入则正常退出循环，进入输入数据部分
            break;
        }
    }
    switch (option) {
    case 1:p->type = 1; break;
    case 2:p->type = 2; break;
    case 3:p->type = 3; break;
    case 4:p->type = 4; break;
    case 5:p->type = 5; break;
    case 6:p->type = 6; break;
    case 7:p->type = 7; break;
    case 8:p->type = 8; break;
    case 9:p->type = 9; break;
    }
    int* Data1 = (int*)malloc(sizeof(int));           //为各种类型的数据开辟空间
    float* Data2 = (float*)malloc(sizeof(float));
    char* Data3 = (char*)malloc(sizeof(char));
    double* Data4 = (double*)malloc(sizeof(double));
    long* Data5 = (long*)malloc(sizeof(long));
    char*Data6=(char*)malloc(sizeof(char)*50);
    long int* Data7 = (long int*)malloc(sizeof(long int));
    long long* Data8 = (long long*)malloc(sizeof(long long));
    short int* Data9 = (short int*)malloc(sizeof(short int));
    printf("请输入入队数据(根据输入的数据类型输入！)：");
    switch (option) {
    case 1:
        while (1) {
            ret=scanf("%d", Data1);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);                                  //正确输入则正常退出循环,输入数据完毕
                break;
            }
        }
        p->data = Data1;
        break;
    case 2:
        while (1) {
            ret = scanf("%f", Data2);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);                                  //正确输入则正常退出循环,输入数据完毕
                break;
            }
        }
        p->data = Data2;
        break;
    case 3:
        while (1) {
            ret = scanf("%c", Data3);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);                                  //正确输入则正常退出循环,输入数据完毕
                break;
            }
        }
        p->data = Data3;
        break;
    case 4:
        while (1) {
            ret = scanf("%lf", Data4);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data4;
        break;
    case 5:
        while (1) {
            ret = scanf("%ld", Data5);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data5;
        break;
    case 6:
        while (1) {
            ret = scanf("%s", Data6);      //这个数据类型有问题
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data6;
        break;
    case 7:
        while (1) {
            ret = scanf("%d", Data7);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data7;
        break;
    case 8:
        while (1) {
            ret = scanf("%lld", Data8);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data8;
        break;
    case 9:
        while (1) {
            ret = scanf("%d", Data9);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("输入错误！请重新输入：");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        p->data = Data9;
        break;
    }
    rewind(stdin);
    return p;
}


int main() {
    LQueue* Q = NULL;                               //定义一个指向LQueue型结构体指针，方便后续初始化
    QNode* p = NULL;                               //定义一个指向QNode型结构体指针，方便后续结点入队
    void* e1=NULL;
    int judge = 1,check;                          //定义一个用于控制循环的变量和一个用于接收返回值的变量
    while (judge) {
        printf("\n\n");
        printf("                         ******************************系统功能菜单******************************\n");
        printf("                         ------------------------------------------------------------------------\n");
        printf("                              **************************************************************\n");
        printf("                              * 1.初始化队列                  **          2.销毁队列并退出 *\n");
        printf("                              **************************************************************\n");
        printf("                              * 3.检查队列是否为空            **          4.查看队头元素   *\n");
        printf("                              **************************************************************\n");
        printf("                              * 5.查看队列长度                **          6.入队操作       *\n");
        printf("                              **************************************************************\n");
        printf("                              * 7.出队操作                    **          8.清空队列       *\n");
        printf("                              **************************************************************\n");
        printf("                              *                            9.遍历队列                      *\n");
        printf("                              **************************************************************\n");
        printf("                         ------------------------------------------------------------------------\n");
        printf("                              请选择菜单编号：");

        int option,ret;                                                //ret为用于判断异常输入的变量
        while (1) {
            ret=scanf("%d", &option);
            printf("\n");
            rewind(stdin);
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
        case 1:InitLQueue(&Q); break;                                               //初始化队列函数
        case 2:judge=DestoryLQueue(Q); break;                                            //销毁队列函数           
        case 3:
            check = IsEmptyLQueue(Q);
            if (check == -1) printf("队列未初始化！\n");
            else if (check==0) printf("队列为空！\n");
            else printf("队列不为空！\n");
            break;                                            //检查队列是否为空函数
        case 4:GetHeadLQueue(Q,e1); break;                                         //查看对头元素函数
        case 5:LengthLQueue(Q); break;                                            //查看队列长度函数
        case 6:
            p=ChosenType(Q);
            if (p ==NULL) break;
            else {
                EnLQueue(Q, p);
                printf("入队完毕！\n");
                break;
            }                                                                       //入队操作函数
        case 7:
            check = DeLQueue(Q);
            if (check == 1) printf("出队完毕！\n");                                //出队操作函数
            else if (check == -1) break;
            else printf("队列为空，不能出队！\n");
            break;                                                                
        case 8:
            check=ClearLQueue(Q);
            if (check == 1) {
                printf("清空队列完毕！\n");
            }
            break;                                             //清空队列函数
        case 9:TraverseLQueue(Q, LPrint); break;      //遍历队列函数
        default:printf("请输入重新输入正确选项：\n");
        }
        printf("按任意键继续...");
        _getch();
        system("cls");
    }
}