#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"LQueue.h"

/*��ʼ�����к���*/
void InitLQueue(LQueue** Q) {
    *Q = (LQueue*)malloc(sizeof(LQueue));
    (*Q)->front = NULL;
    (*Q)->rear = NULL;               //ָ����еĽṹ���е�ָ���ʼ��ָ��NULL
    (*Q)->length = 0;               //��ʼ���г���Ϊ0
    printf("��ʼ��������ϣ�\n");
    return TRUE;
}

/*���ٶ��к���*/
Status DestoryLQueue(LQueue* Q) {
    if (!Q) {
        printf("����������ϣ�\n");             //δ��ʼ�����з���
        return FALSE;
    }
    if (Q->front == NULL && Q->rear == NULL) {
        free(Q);
        printf("����������ϣ�\n");
        return FALSE;                         //������ʾ�������ظ����ڿն���ʱ������ͷ�����
    }
    ClearLQueue(Q);                            //������ն��к���
    free(Q);                                   //��������֮��������Q���ﵽ���ٶ��е�Ŀ��
    printf("����������ϣ�\n");
    return FALSE;
}

/*�鿴��ͷԪ�غ���*/
Status GetHeadLQueue(LQueue* Q, void* e) {
    if (!Q) {
        printf("����δ��ʼ����\n");
        return FALSE;                         //�������δ��ʼ��������FALSE��
    }
    if (!IsEmptyLQueue(Q)) {
        printf("����Ϊ�գ�\n");
        return FALSE;                           //Ҫ���ж϶����Ƿ�Ϊ��,���գ�����FALSE����������ظ���ʾ����
    }                                           
    e = Q->front->data;                        //����ͷ����ָ���򸳸�void*ָ��
    printf("��ͷԪ��Ϊ��");
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

/*�������Ƿ�Ϊ�պ���*/
Status IsEmptyLQueue(const LQueue* Q) {
    if (!Q) {
        return UNUSUAL;                                   //���δ��ʼ��������ֱ�ӷ���
    }
    if (Q->front==NULL&&Q->rear==NULL) {
        return FALSE;                                         //���Q->front==Q->rear,�����Ϊ��
    }
    if (Q->front!=NULL&&Q->rear!=NULL) {
        return TRUE;                               //���Q->front!=Q->rear,����в�Ϊ��
    }

}

/*�鿴���г��Ⱥ���*/
QElemType LengthLQueue(LQueue* Q) {
    if (!Q) {
        printf("����δ��ʼ����\n");
        return 0;                         //δ��ʼ��������ֱ�ӷ���
    }
    printf("���г���Ϊ��%d\n", Q->length);            //���г���
    return TRUE;
}

/*��Ӳ�������*/
Status EnLQueue(LQueue* Q, QNode*p) {
    if (!Q) {
        printf("δ��ʼ�����У�\n");               //δ��ʼ������ֱ�ӷ���
        return FALSE;
    }
    if (Q->front==NULL&&Q->rear==NULL) {
        Q->rear = p;
        Q->front = p;                          //����ǵ�һ�������ӣ������⴦��
        Q->length++;                           //��Ӻ�ӳ�+1
        return TRUE;
    }
    Q->rear->next = p;
    Q->rear = p;
    Q->length++;                             //��Ӻ�ӳ�+1
    return TRUE;
}

/*���Ӳ�������*/
Status DeLQueue(LQueue* Q) {
    if (!Q) {
        printf("����δ��ʼ����\n");               //δ��ʼ������ֱ�ӷ���
        return UNUSUAL;
    }
    if (!IsEmptyLQueue(Q)) {
        return FALSE;                           //�������Ϊ����ֱ�ӷ��أ�������ʾ���ظ�
    }
    else {
        QNode* p1 = NULL;
        p1 = Q->front;
        Q->front = Q->front->next;
        if (Q->rear == p1) {
            Q->rear = Q->front;            //���ɾ�����Ƕ�β���򽫶�βָ��ָ���ͷ
        }
        free(p1);
        Q->length--;
        return TRUE;
    }
}

/*��ն��к���*/
Status ClearLQueue(LQueue* Q) {
    if (!Q) {
        printf("����δ��ʼ����\n");
        return FALSE;
    }                                                 //�ж��Ƿ���δ��ʼ������
    if (!IsEmptyLQueue(Q)) {
        printf("����Ϊ�գ��޷���ն��У�\n");
        return FALSE;                                 //�ж��Ƿ��ǿն���,�����ظ�����ʾ
    }                                                
    while (Q->front != NULL) {                       //����Ϊ�ն��У�����ó��Ӻ���������ն���
        DeLQueue(Q);
    }                      
    return TRUE;                                        //����������
}

/*�������к���*/
Status TraverseLQueue(const LQueue* Q,void(*foo)(void*q)) {
    if (!Q) {
        printf("����δ��ʼ����\n");                                     //δ��ʼ�������޷����
        return FALSE;
    }
    if (!IsEmptyLQueue(Q)) {
        printf("����Ϊ�գ�\n");
        return FALSE;                                                 //����Ϊ��ֱ�ӷ��أ�������ʾ���ظ�
    }
    else {
        QNode* p1 = NULL;                                                   //����һ����������ָ��
        p1 = Q->front;                                                     //ʹ����ָ��ָ��ǰ����Ľ��
        printf("��ͷ->��β\n");
        while (p1!= NULL) {
            printf("����Ԫ�أ�");
            if (p1->type == 1) printf("���ͣ� %d\n", *(int*)(p1->data));
            else if (p1->type == 2) printf("�����ͣ� %.2f\n", *(float*)(p1->data));
            else if (p1->type == 3) printf("�ַ��ͣ� %c\n", *(char*)(p1->data));
            else if (p1->type == 4) printf("˫���ȸ����ͣ� %.4lf\n", *(double*)(p1->data));
            else if (p1->type == 5) printf("�����ͣ� %ld\n", *(long*)(p1->data));
            else if (p1->type == 6) printf("�ַ����ͣ�%s\n", (char*)(p1->data));
            else if (p1->type == 7) printf("long int �ͣ�%d\n", *(long int*)(p1->data));
            else if (p1->type == 8) printf("long long �ͣ�%lld\n", *(long long*)(p1->data));
            else if (p1->type == 9) printf("short int �ͣ�%d\n", *(short int*)(p1->data));
            (*foo)(&p1);
        }
        return TRUE;                                                      //������֮�󷵻�TRUE
    }
}

/*��������*/
void LPrint(void** q) {
    (QNode*)(*q) = ((QNode*)(*q))->next;
}

/*ѡ���������ͺ���*/
QNode* ChosenType(LQueue*Q) {
    if (!Q) {
        printf("����δ��ʼ����\n");
        return NULL;
    }
    QNode* p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL) {
        printf("�����ڴ�ʧ�ܣ�\n");
        return;
    }
    p->next = NULL;
    printf("1.����int;  2.������float;   3.�ַ���char\n4.˫���ȸ�����double;     5.������long;\n6.�ַ�������     7.long int��    8.long long��\n9.short int ��\n��������Ҫ������������ͣ�");
    int option,ret;                                    //����ѡ�������������ͺ��ж��쳣����
    while (1) {
        ret=scanf("%d", &option);
        rewind(stdin);
        if (ret == 0) {
            printf("����������������룺");
        }
        if (ret == 1 && (option < 1 || option>9)) {
            printf("������������ȷѡ�");
        }
        if (ret == 1 && (option >= 1 && option <= 9)) {
            fflush(stdin);                                  //��ȷ�����������˳�ѭ���������������ݲ���
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
    int* Data1 = (int*)malloc(sizeof(int));           //Ϊ�������͵����ݿ��ٿռ�
    float* Data2 = (float*)malloc(sizeof(float));
    char* Data3 = (char*)malloc(sizeof(char));
    double* Data4 = (double*)malloc(sizeof(double));
    long* Data5 = (long*)malloc(sizeof(long));
    char*Data6=(char*)malloc(sizeof(char)*50);
    long int* Data7 = (long int*)malloc(sizeof(long int));
    long long* Data8 = (long long*)malloc(sizeof(long long));
    short int* Data9 = (short int*)malloc(sizeof(short int));
    printf("�������������(��������������������룡)��");
    switch (option) {
    case 1:
        while (1) {
            ret=scanf("%d", Data1);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("����������������룺");
            }
            if (ret == 1) {
                fflush(stdin);                                  //��ȷ�����������˳�ѭ��,�����������
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
                printf("����������������룺");
            }
            if (ret == 1) {
                fflush(stdin);                                  //��ȷ�����������˳�ѭ��,�����������
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
                printf("����������������룺");
            }
            if (ret == 1) {
                fflush(stdin);                                  //��ȷ�����������˳�ѭ��,�����������
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
                printf("����������������룺");
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
                printf("����������������룺");
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
            ret = scanf("%s", Data6);      //�����������������
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("����������������룺");
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
                printf("����������������룺");
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
                printf("����������������룺");
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
                printf("����������������룺");
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
    LQueue* Q = NULL;                               //����һ��ָ��LQueue�ͽṹ��ָ�룬���������ʼ��
    QNode* p = NULL;                               //����һ��ָ��QNode�ͽṹ��ָ�룬�������������
    void* e1=NULL;
    int judge = 1,check;                          //����һ�����ڿ���ѭ���ı�����һ�����ڽ��շ���ֵ�ı���
    while (judge) {
        printf("\n\n");
        printf("                         ******************************ϵͳ���ܲ˵�******************************\n");
        printf("                         ------------------------------------------------------------------------\n");
        printf("                              **************************************************************\n");
        printf("                              * 1.��ʼ������                  **          2.���ٶ��в��˳� *\n");
        printf("                              **************************************************************\n");
        printf("                              * 3.�������Ƿ�Ϊ��            **          4.�鿴��ͷԪ��   *\n");
        printf("                              **************************************************************\n");
        printf("                              * 5.�鿴���г���                **          6.��Ӳ���       *\n");
        printf("                              **************************************************************\n");
        printf("                              * 7.���Ӳ���                    **          8.��ն���       *\n");
        printf("                              **************************************************************\n");
        printf("                              *                            9.��������                      *\n");
        printf("                              **************************************************************\n");
        printf("                         ------------------------------------------------------------------------\n");
        printf("                              ��ѡ��˵���ţ�");

        int option,ret;                                                //retΪ�����ж��쳣����ı���
        while (1) {
            ret=scanf("%d", &option);
            printf("\n");
            rewind(stdin);
            if (ret == 0) {
                printf("                         ����������������룺");
            }
            if (ret == 1) {
                fflush(stdin);
                break;
            }
        }
        system("cls");
        switch (option) {
        case 1:InitLQueue(&Q); break;                                               //��ʼ�����к���
        case 2:judge=DestoryLQueue(Q); break;                                            //���ٶ��к���           
        case 3:
            check = IsEmptyLQueue(Q);
            if (check == -1) printf("����δ��ʼ����\n");
            else if (check==0) printf("����Ϊ�գ�\n");
            else printf("���в�Ϊ�գ�\n");
            break;                                            //�������Ƿ�Ϊ�պ���
        case 4:GetHeadLQueue(Q,e1); break;                                         //�鿴��ͷԪ�غ���
        case 5:LengthLQueue(Q); break;                                            //�鿴���г��Ⱥ���
        case 6:
            p=ChosenType(Q);
            if (p ==NULL) break;
            else {
                EnLQueue(Q, p);
                printf("�����ϣ�\n");
                break;
            }                                                                       //��Ӳ�������
        case 7:
            check = DeLQueue(Q);
            if (check == 1) printf("������ϣ�\n");                                //���Ӳ�������
            else if (check == -1) break;
            else printf("����Ϊ�գ����ܳ��ӣ�\n");
            break;                                                                
        case 8:
            check=ClearLQueue(Q);
            if (check == 1) {
                printf("��ն�����ϣ�\n");
            }
            break;                                             //��ն��к���
        case 9:TraverseLQueue(Q, LPrint); break;      //�������к���
        default:printf("����������������ȷѡ�\n");
        }
        printf("�����������...");
        _getch();
        system("cls");
    }
}