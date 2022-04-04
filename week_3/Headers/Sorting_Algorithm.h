#define ArrLen 200001
#define RADIX_10 10                 //��������ʱ������ʱ�����С,��ʾ��λ��С
#define KEYNUM_31 5                //��������ʱ������ֵ�λ������110��3λ

/**
 *  @name        : void swap(int* a, long i, long j);
 *  @description : ����Ԫ��λ��
 *  @param       : ����ָ�� a, �±�i j
 */
void swap(int* a, long i, long j);

/**
 *  @name        : void insertSort(int *a,long n);
 *  @description : ���������㷨
 *  @param       : ����ָ�� a, ���鳤�� n
 */
void insertSort(int* a, long n);

/**
 *  @name        : void MergeArray(int *a,long begin,long mid,long end);
 *  @description : �鲢���򣨺ϲ����飩
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end
 */
void MergeArray(int* a, long begin, long mid, long end);

/**
 *  @name        : void MergeSort(int* a, long begin, long end);
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void MergeSort(int* a, long begin, long end);

/**
 *  @name        : void QuickSort_Recursion(int* a, long begin, long end, int check);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end,ѡ�����ᷨ����check
 */
void QuickSort_Recursion(int* a, long begin, long end, int check);

/**
 *  @name        : long Partition(int* a, long begin, long end)
 *  @description : �������������ţ�
 *  @param       : ����ָ��a���������begin�������յ�end
 */
long Partition(int* a, long begin, long end);

/**
 *  @name        : void QuickSort(int* a, long begin, long end)
 *  @description : �������򣨷ǵݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
 */
void QuickSort(int* a, long begin, long end);

/**
 *  @name        : long Partition(int* a, long begin, long end)
 *  @description : ��������������--����ȡ�з���
 *  @param       : ����ָ��a���������begin�������յ�end
 */
long Partition_Three(int* a, int begin, long end);

/**
 *  @name        : void CountSort(int* a, long size)
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size
 */
void CountSort(int* a, long size);

/**
 *  @name        : void RadixCountSort(int* a, long size)
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
 */
void RadixCountSort(int* a, long size);

/**
 *  @name        : int* ColorSort(int* b, long* size2)
 *  @description : ��ɫ����
 *  @param       : ����ָ��b�����鳤��sizeָ��
 */
int* ColorSort(int* b, long* size2);

/**
 *  @name        : void FindKMin(int* a, long begin, long end, long k)
 *  @description : ��һ�������������ҵ���K��/С����
 *  @param       : ����ָ��a���������begin�������յ�end����k��/С��
 */
void FindKMin(int* a, long begin, long end, long k);

/**
 *  @name        : long Createrand()
 *  @description : ���������
 *  @param       : 
 */
long Createrand();

/**
 *  @name        : int* ReadRand(long count)
 *  @description : ���ļ�����
 *  @param       : ���������count
 */
int* ReadRand(long count);

/**
 *  @name        : void Display(int* a, long length)
 *  @description : ��ӡ����
 *  @param       : ����ָ��a,���鳤��
 */
void Display(int* a, long length);

/**
 *  @name        : void statisticTime1(int* a, int begin, int end, int size1)
 *  @description : ͳ�ƴ������ݵ�������ʱ�亯��
 *  @param       : ����ָ��a,���鳤��size1���������begin,�����յ�end
 */
void statisticTime1(int* a, int begin, int end, int size1);

/**
 *  @name        : void statisticTime2(int* a, int begin, int end, int size1)
 *  @description : ͳ�����������ݶ������ʱ�亯��
 *  @param       : ����ָ��a,���鳤��size1���������begin,�����յ�end
 */
void statisticTime2(int* a, int begin, int end, int size1);

