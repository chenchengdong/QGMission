#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"Sorting_Algorithm.h"

void swap(int*a, long i, long j) {
	int temp =a[i];
	a[i] = a[j];
	a[j] = temp;
}

/*插入排序算法*/
void insertSort(int* a, long n) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;                           //没有生成随机数时就立刻返回
	}
	for (long i = 0; i < n; i++) {        //开始遍历待排序数组
		for (long j = 0; j < i; j++) {
			if (a[i] < a[j]) {            //i之前的数据数据都是排号序了的，所有只是看a[i]能不能插入到哪一个a[j]中而已，所以插入完可以直接break
				int temp = a[i];          //将需要插入的元素先用一个临时变量存起来
				for (long k = i; k > j; k--) {        //定义一个重新用于遍历从a[j]到a[i]全部后退一格
					a[k] = a[k - 1];        //前一个数据往后移动，即数据右移动，k>j是当k==j+1时，k-1就为j所在数据，就已经右移了
				}
				a[j] = temp;               //将数据插入到a[j]处
				break;
			}
		}
	}
}

/*归并排序(合并数组)*/
void MergeArray(int* a, long begin, long mid, long end) {
	int result[ArrLen];
	long k = 0;
	long i = begin;
	long j = mid + 1;
	while (i <= mid && j <= end) {
		if (a[i] < a[j]) {
			result[k++] = a[i++];            // 若符合前小后大的话就直接存入新数组
		}                                   //此时i下标的数据比较小
		else{
			result[k++] = a[j++];          //若符合前大后小，则存j下标的数据进入新数组，此时是j下标的数比较小
		}
	}
	if (i == mid + 1) {                  //对应上面的i<=mid条件的否定出来的情况
		while (j <= end) {               //此时j还满足j<=end的情况，即j还未到元素组末端
			result[k++] = a[j++];        //由于mid两边的小数组都是各自排好顺序的，当一边小数组被遍历完放进新数组时，另一边的可以直接全部按顺序放入新数组
		}
	}
	if (j == end + 1) {
		while (i <= mid) {
			result[k++] = a[i++];         //道理同上
		}
	}
	for (j = 0, i = begin; j < k; i++, j++) {
		a[i] = result[j];                 //此时将新数组里的数据按照对应旧数组和长度个数放入替换
	}
}

/*归并排序*/
void MergeSort(int* a, long begin, long end) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	if (begin >= end) {
		return;
	}
	long mid = (begin + end) / 2; //先求出数组中间的下标
	MergeSort(a, begin, mid);//递归拆分左子数组
	MergeSort(a, mid + 1, end);//递归拆分右子数组
	MergeArray(a, begin, mid, end);//递归排序子数组

}

/*快速排序(递归版)*/                                     //哨兵的问题改了
void QuickSort_Recursion(int*a, long begin, long end,int check) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	long pivot;
	if (begin < end) {
		if (check == 1) {                             //当check参数为1时，调用未优化过的取数法
			pivot = Partition(a, begin, end);        //将a一分为二,并算出枢轴值pivot    
		}
		else if (check == 2) {
			pivot = Partition_Three(a,begin,end);      //将a一分为二,并算出枢轴值pivot
		}
		QuickSort_Recursion(a, begin, pivot-1,check);     //对低子表递归排序
		QuickSort_Recursion(a, pivot+1, end,check);       //对高子表递归排序
	}
}

/*快速排序（枢轴存放）*/
long Partition(int*a, long begin, long end) {
	int pivotkey;
	pivotkey = a[begin];                       //用子表的第一个记录作枢轴记录
	while (begin < end) {
		while (begin<end && a[end]>=pivotkey) {
			end--;                              //当begin<end时，且找不到比枢轴pivotkey小的数时，end下标往前走
		}
		swap(a, begin, end);                 //从上面出来就是找到比枢轴小的数了，此时交换它跟枢轴位置
		while (begin < end && a[begin] <= pivotkey) {
			begin++;                         //同理上面，当找不到比枢轴大的数时，begin下标要往后走
		}
		swap(a, begin, end);               //找到比枢轴大的数了，此时交换位置，此时枢轴又重新回到begin下标手中，即上面交换了两次。最后无论之间交换多少次，begin和end都会同时停留在枢轴上面，即相遇
	}
	return begin;
}

/*快速排序（非递归版）*/
void QuickSort(int* a, long begin, long end) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	int* stack = (int*)malloc(end * sizeof(int));         //申请一块内存做栈使用，用来临时存放
	if (!stack) {
		return;                                            //申请空间失败则返回
	}
	long begin_temp = begin;
	long end_temp = end;
	int stack_top = 0;                                  //初始栈顶下标为设0
	long p = Partition(a, begin_temp, end_temp);            //先进行第一次排序
	if (p > (begin_temp + 1)) {                        //此时子数组起码还有3个
		stack[stack_top++]=p - 1;                     //后出栈的先进栈
		stack[stack_top++] = begin_temp;              //先出栈的后进栈
	}
	if (p < (end_temp - 1)) {                        //此时子数组起码还有3个
		stack[stack_top++] = end_temp;
		stack[stack_top++] = p + 1;
	}                                      
	while (stack_top > 0) {                          //若stack_top==0，说明两个if都未执行过，则排序结束
		begin_temp = stack[--stack_top];              //从栈中获得起始地址
		end_temp = stack[--stack_top];   
		p = Partition(a, begin_temp, end_temp);
		if (p > (begin_temp + 1)) {                 //此时子数组起码还有3个
			stack[stack_top++] = p - 1;  
			stack[stack_top++] = begin_temp;         //先出栈的后进栈
		}
		if (p < (end_temp - 1)) {                  //此时子数组起码还有3个
			stack[stack_top++] = end_temp;
			stack[stack_top++] = p + 1;
		}
	}
	free(stack);                                  //释放空间

}

/*快速排序（优化后的枢轴存放--三数取中法）*/
long Partition_Three(int*a, int begin, long end) {
	int pivotkey;
	long m = begin + (end - begin) / 2;            //计算子数组的中间下标
	if (a[begin] > a[end]) {
		swap(a, begin, end);                //保持左端较小
	} 
	if (a[m] > a[end]) {
		swap(a, end, m);                 //保持中间较小
	}
	if (a[m] > a[begin]) {
		swap(a, m, begin);                //保持左端较中
	}
	pivotkey = a[begin];
	while (begin < end) {
		while (begin<end && a[end]>=pivotkey) {
			end--;                             //当begin<end时，且找不到比枢轴pivotkey小的数时，end下标往前走
		}
		swap(a, begin, end);                 //从上面出来就是找到比枢轴小的数了，此时交换它跟枢轴位置
		while (begin < end && a[begin] <= pivotkey) {
			begin++;                         //同理上面，当找不到比枢轴大的数时，begin下标要往后走
		}
		swap(a, begin, end);                //找到比枢轴大的数了，此时交换位置，此时枢轴又重新回到begin下标手中，即上面交换了两次。最后无论之间交换多少次，begin和end都会同时停留在枢轴上面，即相遇
	}
	return begin;
	
}

/*计数排序*/
void CountSort(int* a, long size) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	int max = a[0];
	int min = a[0];
	for (long i = 0; i < size; i++) {           //先用循环找到输入数组的最大最小值
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;                    //算出需要创建的数组长度
	int* b = (int*)calloc(range, sizeof(int));   //创建长度为range*int的空间数组
	for (long i = 0; i < size; i++) {
		b[a[i] - min] += 1;                     //统计各个数据减去min所占的个数   记b的下标为i1,a的下标为i2
	}
	int j = 0;
	for (int i = 0; i < range; i++) {          //遍历统计数组
		while (b[i]--) {                       //这个区间段的个数即为循环次数即为需要放入的个数
			a[j++] = i + min;                  //需放回的数与下标存在一定关系，即 i1=a[i2]-min;a[i2]=i1+min,所以存回去的数是正确的
		}
	}
	free(b);                                  //释放临时数组
	b = NULL;
}

/*基数计数排序*/
void RadixCountSort(int* a, long size) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	int* tem[RADIX_10];                           //创建一个临时指针数组
	for (int i = 0; i < 10; i++) {
		tem[i] = (int*)malloc(sizeof(int) * (size + 1));
		tem[i][0] = 0;                            //index为0处记录这组数据的个数
	}
	for (int pos = 1; pos <= KEYNUM_31; pos++) {
		for (long i = 0; i < size; i++) {
			int temp = 1;
			for (int k = 0; k < pos - 1; k++)
			{
				temp *= 10;
			}
			int num = (a[i] / temp) % 10;  //先整除掉尾数再取余得到当前位的数字,如果数字位数较少，取整取余之后会得到一个0
			int index = ++tem[num][0];     //对应数字（得到的那个个位数）第几个进入该数字的“桶”
			tem[num][index] = a[i];      //将该数第index个放进对应数子的“桶”
		}
		for (int i = 0, j = 0; i < RADIX_10; i++) {
			for (long k = 1; k <= tem[i][0]; k++) {
				a[j++] = tem[i][k];    //tem[i][0]表示每个对应数字的桶里面对应的个数，故k不能超过他
			}                         //按顺序重新全部放回到a数组中去
			tem[i][0] = 0;           //然后再将对应数字的桶记录个数的位置复0
		}
	}
}

/*颜色排序*/
int* ColorSort(int* b,long*size2) {
	printf("请输入你要生成0-2的随机数个数：");
	long num;
	int ret;
	while (1) {
		ret= scanf("%ld", &num);
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("输入错误！请重新输入：");
		}
		if (ret == 1 && num < 1) {
			printf("输入错误！不能生成小于1个随机数！请重新输入：");
		}
		if (ret == 1 && num >= 1) {
			fflush(stdin);
			break;
		}
	}
	*size2 = num;                       //返回数组个数
	FILE* fp1;                         //创建打开文件的指针 写模式
	if ((fp1 = fopen("随机数2.dat", "w")) == NULL) {
		printf("Can not open the file\n");
	}
	srand((unsigned int)time(0));  //初始化随机数种子
	for (long i = 0; i < num; i++) {
		fprintf(fp1, "%d\t", rand() % 3);
	}
	fclose(fp1);
	FILE* fp2;
	if ((fp2 = fopen("随机数2.dat", "r")) == NULL) {
		printf("Can not open the file\n");
		exit(1);
	}
	b = (int*)calloc(num, sizeof(int));
	for (long i = 0; i < num; i++) {
		fscanf(fp2, "%d", &b[i]);
	}
	fclose(fp2);
	int* p2 = &b[num - 1];
	int* p0 = &b[0];
	int* p1 = &b[0];
	int temp = 3;
	for (; p1 <= p2;) {           //p1,p2相遇时结束
		if (*p1 == 0) {         //p0与p1调换之后，p1是移动的
			temp = *p1;
			*p1 = *p0;
			*p0 = temp;
			p0++;
			p1++;
		}
		else if (*p1 == 1) p1++;
		else if (*p1 == 2) {         //p2与p1调换之后，p1是不移动的
			temp = *p1;
			*p1 = *p2;
			*p2 = temp;
			p2--;
		}
	}
	return b;
}

/*自拟（在一个无序序列中找到第K大的数）*/
void FindKMin(int* a, long begin, long end,long k) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	long pivot;
	if (begin < end) {
		pivot = Partition(a, begin, end);      //将a一分为二,并算出枢轴值pivot 
		if (pivot + 1 > k) {
			FindKMin(a, begin, pivot - 1, k); //此时第K大的数位于右侧子数组
			return;
		}
		else if (pivot + 1 < k) {
			FindKMin(a, pivot + 1, end, k);  //此时第K大的数位于左侧子数组
			return;
		}
		else if (pivot + 1 == k) {
			return;
		}
	}

}

/*生成测试数据并写入函数*/
long Createrand() {
	printf("1. 0-50之间的随机数        2.0-100之间的随机数           3. 0-1000之间的随机数\n4. 0-10000之间的随机数          5. 0-随机库中最大值之间的随机数     6.0-2之间的随机数\n");
	printf("请按照菜单选择你要生成的随机数范围：");
	int option,ret,num=1,judge=1;
	while (1) {
		ret= scanf("%d", &option);                //防止异常输入
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("输入错误！请重新输入：");
		}
		if (ret == 1 && (option < 1 || option>6)) {
			printf("请重新选择正确的菜单选项！");
		}
		if (ret == 1 && (option >= 1 && option <= 6)) {
			fflush(stdin);
			break;
		}
	}
	printf("请选择你要生成的随机数个数：");
	long count = 0;
	while (1) {
		ret=scanf("%ld", &count);              //防止异常输入
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("输入错误！请重新输入：");
		}
		if (ret == 1 && count < 1) {
			printf("输入错误！不能生成小于1个随机数！请重新输入：");
		}
		if (ret == 1 && count >= 1) {
			fflush(stdin);
			break;
		}
	}
	while (judge) {
		switch (option) {
		case 1:num = 50; judge = 0; break;
		case 2:num = 100; judge = 0; break;
		case 3:num = 1000; judge = 0; break;
		case 4:num = 10000; judge = 0; break;
		case 5:num = 32767; judge = 0; break;
		case 6:num = 3; judge = 0; break;
		default:printf("请选择正确的序号！\n"); judge = 1; break;
		}
	}
	FILE* fp;                         //创建打开文件的指针 写模式
	if ((fp = fopen("随机数1.dat", "w")) == NULL) {
		printf("Can not open the file\n");
	}
	srand((unsigned int)time(0));  //初始化随机数种子
	for (int i = 0; i < count; i++) {
		fprintf(fp, "%d\t", rand() % num);
	}
	fclose(fp);
	printf("生成完毕！\n");
	return count;        //返回生成个数，便于生成数组
}

/*读文件函数*/
int* ReadRand(long count) {
	FILE* fp;                         //创建打开文件的指针 写模式
	if ((fp = fopen("随机数1.dat", "r")) == NULL) {
		printf("Can not open the file\n");
		exit(1);
	}
	int* a = (int*)calloc(count, sizeof(int));
	for (long i = 0; i < count; i++) {
		fscanf(fp, "%d", &a[i]);
	}
	fclose(fp);
	return a;
}

/*输出数据函数*/
void Display(int* a,long length) {
	if (!a) return;
	printf("排序完后：\n");
	for (long i = 0; i < length; i++) {
		printf("%d  ", a[i]);
		if (i!=0&&i % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

/*统计大量不同数据时间*/
void statisticTime1(int*a,int begin,int end,int size1) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	//统计插入排序时间
	clock_t start1, diff1;
	start1= clock();
	insertSort(a, size1);
	diff1 = clock()-start1;
	double d1;
	d1 = (double)diff1 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计归并排序时间
	clock_t start2 = clock();
	MergeSort(a, begin, end);
	clock_t diff2 = clock() - start2;
	double d2;
	d2 = (double)diff2 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计快速排序（递归）时间
	clock_t start3 = clock();
	QuickSort_Recursion(a,begin,end,1);
	clock_t diff3 = clock() - start3;
	double d3;
	d3 = (double)diff3 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计快速排序优化版（递归）时间
	clock_t start4 = clock();
	QuickSort_Recursion(a, begin, end, 2);
	clock_t diff4 = clock() - start4;
	double d4;
	d4 = (double)diff4 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计快速排序非递归版时间
	clock_t start5 = clock();
	QuickSort(a,begin,end);
	clock_t diff5 = clock() - start5;
	double d5;
	d5 = (double)diff5 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计计数排序时间
	clock_t start6 = clock();
	CountSort(a,size1);
	clock_t diff6 = clock() - start6;
	double d6;
	d6 = (double)diff6 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	//统计基数排序时间
	clock_t start7 = clock();
	RadixCountSort(a,size1);
	clock_t diff7 = clock() - start7;
	double d7;
	d7 = (double)diff7 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	printf("插入排序总用时间：% lf s \n归并排序总用时： %lf s\n快速排序总用时： %lf s\n快速排序优化枢轴总用时：%lf s\n快速排序非递归总用时：%lf s\n计数排序总用时：%lf s\n基数排序总用时：%lf s\n",d1,d2,d3,d4,d5,d6,d7);
}

/*统计少量多次的数据排序时间*/
void statisticTime2(int* a, int begin, int end, int size1) {
	if (!a) {
		printf("请先生成随机数！\n");
		return;
	}
	/*统计插入排序时间*/
	clock_t start1;
	clock_t diff1=0;
	double times1 = 0;
	double temp1 = 0;
	for (long i = 0; i < 100000; i++) {
		start1 = clock();
		insertSort(a, size1);
		diff1 = clock();
		temp1 = (double)(diff1 - start1) / CLOCKS_PER_SEC;
		times1 += temp1;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计归并排序时间
	clock_t start2;
	clock_t diff2 = 0;
	double times2 = 0;
	double temp2 = 0;
	for (long i = 0; i < 100000; i++) {
		start2 = clock();
		MergeSort(a, begin, end);
		diff2 = clock();
		temp2 = (double)(diff2 - start2) / CLOCKS_PER_SEC;
		times2 += temp2;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计快速排序（递归）时间
	clock_t start3;
	clock_t  diff3 = 0;
	double times3 = 0;
	double temp3 = 0;
	for (long i = 0; i < 100000; i++) {
		start3 = clock();
		QuickSort_Recursion(a, begin, end, 1);
		diff3 = clock();
		temp3 = (double)(diff3 - start3) / CLOCKS_PER_SEC;
		times3 += temp3;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计快速排序优化版（递归）时间
	clock_t start4;
	clock_t diff4 = 0;
	double times4 = 0;
	double temp4 = 0;
	for (long i = 0; i < 100000; i++) {
		start4 = clock();
		QuickSort_Recursion(a, begin, end, 2);
		diff4 = clock();
		temp4 = (double)(diff4 - start4) / CLOCKS_PER_SEC;
		times4 += temp4;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计快速排序非递归版时间
	clock_t start5;
	clock_t diff5 = 0;
	double times5 = 0;
	double temp5 = 0;
	for (long i = 0; i < 100000; i++) {
		start5 = clock();
		QuickSort(a, begin, end);
		diff5 = clock();
		temp5 = (double)(diff5 - start5) / CLOCKS_PER_SEC;
		times5 += temp5;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计计数排序时间
	clock_t start6;
	clock_t diff6 = 0;
	double temp6 = 0;
	double times6 = 0;
	for (long i = 0; i < 100000; i++) {
		start6 = clock();
		CountSort(a, size1);
		diff6 = clock();
		temp6 = (double)(diff6 - start6) / CLOCKS_PER_SEC;
		times6 += temp6;
		a= ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	//统计基数排序时间
	clock_t start7;
	clock_t diff7 = 0;
	double temp7 = 0;
	double times7 = 0;
	for (long i = 0; i < 100000; i++) {
		start7 = clock();
		RadixCountSort(a, size1);
		diff7 = clock();
		temp7 = (double)(diff7 - start7) / CLOCKS_PER_SEC;
		times7 += temp7;
		a = ReadRand(size1);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
	}
	printf("插入排序总用时间：%lf s  \n归并排序总用时： %lf s \n快速排序总用时： %lf s \n快速排序优化枢轴总用时：%lf s  \n快速排序非递归总用时：%lf s \n计数排序总用时：%lf s \n基数排序总用时：%lf s \n",times1,times2,times3,times4 ,times5,times6,times7);
}

int main() {
	int judge = 1;
	int* a = NULL;
	int *b = NULL;        //定义一个指针，用于指向数组
	int temp = 0;    //size1是数组个数，其它是下标，temp是存放临时变量的地方
	long count = 0, size1 = 0, size2 = 0,end=0,begin = 0,k1 = 0, k2 = 0;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************系统功能菜单******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.插入排序                 **        2.归并排序            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.快速排序(递归)           **      4.快速排序优化版（递归）*\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.快速排序（非递归）       **          6.计数排序          *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.基数排序                 **         8.颜色排序           *\n");
		printf("                              **************************************************************\n");
		printf("                              * 9.找出第K小值              **         10.找出第K大值       *\n");
		printf("                              **************************************************************\n");
		printf("                              * 11.生成随机数              **         12.退出程序          *\n");
		printf("                              **************************************************************\n");
		printf("                              * 13.统计各个排序时间(多数据少次排序,先自行生成随机数20k)    *\n");
		printf("                              **************************************************************\n");
		printf("                              * 14.统计各个排序算法排序时间(少数据多次排序,请先自行生成100个数据)*\n");
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
		clock_t start, diff;
		switch (option) {
		case 1:
			start = clock();
			insertSort(a, size1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 2:
			start = clock();
			MergeSort(a, begin, end);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 3:
			start = clock();
			QuickSort_Recursion(a, begin, end,1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 4:
			start = clock();
			QuickSort_Recursion(a,begin,end,2);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 5:
			start = clock();
			QuickSort(a, begin, end);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 6:
			start = clock();
			CountSort(a, size1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 7:
			start = clock();
			RadixCountSort(a, size1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("总排序时间为：%ld ms", diff - start);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 8:
			b=ColorSort(b,&size2);
			Display(b,size2);
			break;
		case 9:
			if (!a) {
				printf("请先生成随机数！\n");
				break;
			}
			printf("请输入你想要查询的第K小的数：");
			while (1) {
				ret = scanf("%d", &k1);             //0<k<=count
				printf("\n");
				rewind(stdin);
				if (ret == 0) {
					printf("输入错误！请重新输入：");
				}
				if (ret == 1 && (k1<1 || k1>count)) {
					printf("输入的查找值超出范围！请重新输入：");
				}
				if (ret == 1 && (k1 >= 1 && k1 <= count)) {
					fflush(stdin);
					break;
				}
			}
			FindKMin(a,begin,end,k1);
			printf("第K小的数为：%d \n", a[k1 - 1]);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 10:
			if (!a) {
				printf("请先生成随机数！\n");
				break;
			}
			printf("请输入你想要查询的第K大的数：");
			while (1) {
				ret=scanf("%d", &k2);
				printf("\n");
				rewind(stdin);
				if (ret == 0) {
					printf("输入错误！请重新输入：");
				}
				if (ret == 1 && (k2<1 || k2>count)) {
					printf("输入的查找值超出范围！请重新输入：");
				}
				if (ret == 1 && (k2 >= 1 && k2 <= count)) {
					fflush(stdin);
					break;
				}
			}
			k2 = count - k2 + 1;          //将第k大的转化为第k小
			FindKMin(a, begin, end, k2);
			printf("第K大的数为：%d \n", a[k2 - 1]);
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 11:
			count = Createrand();
			size1 = count;          //将生成的随机数个数记录下来
			end = count - 1;
			a=ReadRand(count);
			break;
		case 12:
			judge = 0;
			break;
		case 13:
			statisticTime1(a,begin,end,size1);
			if (!a) break;
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		case 14:
			statisticTime2(a, begin, end, size1);
			if (!a) break;
			a = ReadRand(count);            //每次排完序都重新调出文件里的随机数，不然后面的选择都不需要排了
			break;
		default:printf("请重新输入正确选项！\n");
		}
		system("pause");
		system("cls");
	}
}