#define ArrLen 200001
#define RADIX_10 10                 //基数排序时创建临时数组大小,表示个位大小
#define KEYNUM_31 5                //基数排序时最大数字的位数，如110，3位

/**
 *  @name        : void swap(int* a, long i, long j);
 *  @description : 交换元素位置
 *  @param       : 数组指针 a, 下标i j
 */
void swap(int* a, long i, long j);

/**
 *  @name        : void insertSort(int *a,long n);
 *  @description : 插入排序算法
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int* a, long n);

/**
 *  @name        : void MergeArray(int *a,long begin,long mid,long end);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end
 */
void MergeArray(int* a, long begin, long mid, long end);

/**
 *  @name        : void MergeSort(int* a, long begin, long end);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void MergeSort(int* a, long begin, long end);

/**
 *  @name        : void QuickSort_Recursion(int* a, long begin, long end, int check);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end,选择枢轴法参数check
 */
void QuickSort_Recursion(int* a, long begin, long end, int check);

/**
 *  @name        : long Partition(int* a, long begin, long end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
long Partition(int* a, long begin, long end);

/**
 *  @name        : void QuickSort(int* a, long begin, long end)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort(int* a, long begin, long end);

/**
 *  @name        : long Partition(int* a, long begin, long end)
 *  @description : 快速排序（枢轴存放--三数取中法）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
long Partition_Three(int* a, int begin, long end);

/**
 *  @name        : void CountSort(int* a, long size)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size
 */
void CountSort(int* a, long size);

/**
 *  @name        : void RadixCountSort(int* a, long size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
void RadixCountSort(int* a, long size);

/**
 *  @name        : int* ColorSort(int* b, long* size2)
 *  @description : 颜色排序
 *  @param       : 数组指针b，数组长度size指针
 */
int* ColorSort(int* b, long* size2);

/**
 *  @name        : void FindKMin(int* a, long begin, long end, long k)
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组起点begin，数组终点end，第k大/小数
 */
void FindKMin(int* a, long begin, long end, long k);

/**
 *  @name        : long Createrand()
 *  @description : 生成随机数
 *  @param       : 
 */
long Createrand();

/**
 *  @name        : int* ReadRand(long count)
 *  @description : 读文件函数
 *  @param       : 随机数个数count
 */
int* ReadRand(long count);

/**
 *  @name        : void Display(int* a, long length)
 *  @description : 打印函数
 *  @param       : 数组指针a,数组长度
 */
void Display(int* a, long length);

/**
 *  @name        : void statisticTime1(int* a, int begin, int end, int size1)
 *  @description : 统计大量数据单次排序时间函数
 *  @param       : 数组指针a,数组长度size1，数组起点begin,数组终点end
 */
void statisticTime1(int* a, int begin, int end, int size1);

/**
 *  @name        : void statisticTime2(int* a, int begin, int end, int size1)
 *  @description : 统计少量量数据多次排序时间函数
 *  @param       : 数组指针a,数组长度size1，数组起点begin,数组终点end
 */
void statisticTime2(int* a, int begin, int end, int size1);

