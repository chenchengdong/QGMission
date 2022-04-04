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

/*���������㷨*/
void insertSort(int* a, long n) {
	if (!a) {
		printf("���������������\n");
		return;                           //û�����������ʱ�����̷���
	}
	for (long i = 0; i < n; i++) {        //��ʼ��������������
		for (long j = 0; j < i; j++) {
			if (a[i] < a[j]) {            //i֮ǰ���������ݶ����ź����˵ģ�����ֻ�ǿ�a[i]�ܲ��ܲ��뵽��һ��a[j]�ж��ѣ����Բ��������ֱ��break
				int temp = a[i];          //����Ҫ�����Ԫ������һ����ʱ����������
				for (long k = i; k > j; k--) {        //����һ���������ڱ�����a[j]��a[i]ȫ������һ��
					a[k] = a[k - 1];        //ǰһ�����������ƶ������������ƶ���k>j�ǵ�k==j+1ʱ��k-1��Ϊj�������ݣ����Ѿ�������
				}
				a[j] = temp;               //�����ݲ��뵽a[j]��
				break;
			}
		}
	}
}

/*�鲢����(�ϲ�����)*/
void MergeArray(int* a, long begin, long mid, long end) {
	int result[ArrLen];
	long k = 0;
	long i = begin;
	long j = mid + 1;
	while (i <= mid && j <= end) {
		if (a[i] < a[j]) {
			result[k++] = a[i++];            // ������ǰС���Ļ���ֱ�Ӵ���������
		}                                   //��ʱi�±�����ݱȽ�С
		else{
			result[k++] = a[j++];          //������ǰ���С�����j�±�����ݽ��������飬��ʱ��j�±�����Ƚ�С
		}
	}
	if (i == mid + 1) {                  //��Ӧ�����i<=mid�����ķ񶨳��������
		while (j <= end) {               //��ʱj������j<=end���������j��δ��Ԫ����ĩ��
			result[k++] = a[j++];        //����mid���ߵ�С���鶼�Ǹ����ź�˳��ģ���һ��С���鱻������Ž�������ʱ����һ�ߵĿ���ֱ��ȫ����˳�����������
		}
	}
	if (j == end + 1) {
		while (i <= mid) {
			result[k++] = a[i++];         //����ͬ��
		}
	}
	for (j = 0, i = begin; j < k; i++, j++) {
		a[i] = result[j];                 //��ʱ��������������ݰ��ն�Ӧ������ͳ��ȸ��������滻
	}
}

/*�鲢����*/
void MergeSort(int* a, long begin, long end) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	if (begin >= end) {
		return;
	}
	long mid = (begin + end) / 2; //����������м���±�
	MergeSort(a, begin, mid);//�ݹ�����������
	MergeSort(a, mid + 1, end);//�ݹ�����������
	MergeArray(a, begin, mid, end);//�ݹ�����������

}

/*��������(�ݹ��)*/                                     //�ڱ����������
void QuickSort_Recursion(int*a, long begin, long end,int check) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	long pivot;
	if (begin < end) {
		if (check == 1) {                             //��check����Ϊ1ʱ������δ�Ż�����ȡ����
			pivot = Partition(a, begin, end);        //��aһ��Ϊ��,���������ֵpivot    
		}
		else if (check == 2) {
			pivot = Partition_Three(a,begin,end);      //��aһ��Ϊ��,���������ֵpivot
		}
		QuickSort_Recursion(a, begin, pivot-1,check);     //�Ե��ӱ�ݹ�����
		QuickSort_Recursion(a, pivot+1, end,check);       //�Ը��ӱ�ݹ�����
	}
}

/*�������������ţ�*/
long Partition(int*a, long begin, long end) {
	int pivotkey;
	pivotkey = a[begin];                       //���ӱ�ĵ�һ����¼�������¼
	while (begin < end) {
		while (begin<end && a[end]>=pivotkey) {
			end--;                              //��begin<endʱ�����Ҳ���������pivotkeyС����ʱ��end�±���ǰ��
		}
		swap(a, begin, end);                 //��������������ҵ�������С�����ˣ���ʱ������������λ��
		while (begin < end && a[begin] <= pivotkey) {
			begin++;                         //ͬ�����棬���Ҳ�������������ʱ��begin�±�Ҫ������
		}
		swap(a, begin, end);               //�ҵ������������ˣ���ʱ����λ�ã���ʱ���������»ص�begin�±����У������潻�������Ρ��������֮�佻�����ٴΣ�begin��end����ͬʱͣ�����������棬������
	}
	return begin;
}

/*�������򣨷ǵݹ�棩*/
void QuickSort(int* a, long begin, long end) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	int* stack = (int*)malloc(end * sizeof(int));         //����һ���ڴ���ջʹ�ã�������ʱ���
	if (!stack) {
		return;                                            //����ռ�ʧ���򷵻�
	}
	long begin_temp = begin;
	long end_temp = end;
	int stack_top = 0;                                  //��ʼջ���±�Ϊ��0
	long p = Partition(a, begin_temp, end_temp);            //�Ƚ��е�һ������
	if (p > (begin_temp + 1)) {                        //��ʱ���������뻹��3��
		stack[stack_top++]=p - 1;                     //���ջ���Ƚ�ջ
		stack[stack_top++] = begin_temp;              //�ȳ�ջ�ĺ��ջ
	}
	if (p < (end_temp - 1)) {                        //��ʱ���������뻹��3��
		stack[stack_top++] = end_temp;
		stack[stack_top++] = p + 1;
	}                                      
	while (stack_top > 0) {                          //��stack_top==0��˵������if��δִ�й������������
		begin_temp = stack[--stack_top];              //��ջ�л����ʼ��ַ
		end_temp = stack[--stack_top];   
		p = Partition(a, begin_temp, end_temp);
		if (p > (begin_temp + 1)) {                 //��ʱ���������뻹��3��
			stack[stack_top++] = p - 1;  
			stack[stack_top++] = begin_temp;         //�ȳ�ջ�ĺ��ջ
		}
		if (p < (end_temp - 1)) {                  //��ʱ���������뻹��3��
			stack[stack_top++] = end_temp;
			stack[stack_top++] = p + 1;
		}
	}
	free(stack);                                  //�ͷſռ�

}

/*���������Ż����������--����ȡ�з���*/
long Partition_Three(int*a, int begin, long end) {
	int pivotkey;
	long m = begin + (end - begin) / 2;            //������������м��±�
	if (a[begin] > a[end]) {
		swap(a, begin, end);                //������˽�С
	} 
	if (a[m] > a[end]) {
		swap(a, end, m);                 //�����м��С
	}
	if (a[m] > a[begin]) {
		swap(a, m, begin);                //������˽���
	}
	pivotkey = a[begin];
	while (begin < end) {
		while (begin<end && a[end]>=pivotkey) {
			end--;                             //��begin<endʱ�����Ҳ���������pivotkeyС����ʱ��end�±���ǰ��
		}
		swap(a, begin, end);                 //��������������ҵ�������С�����ˣ���ʱ������������λ��
		while (begin < end && a[begin] <= pivotkey) {
			begin++;                         //ͬ�����棬���Ҳ�������������ʱ��begin�±�Ҫ������
		}
		swap(a, begin, end);                //�ҵ������������ˣ���ʱ����λ�ã���ʱ���������»ص�begin�±����У������潻�������Ρ��������֮�佻�����ٴΣ�begin��end����ͬʱͣ�����������棬������
	}
	return begin;
	
}

/*��������*/
void CountSort(int* a, long size) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	int max = a[0];
	int min = a[0];
	for (long i = 0; i < size; i++) {           //����ѭ���ҵ���������������Сֵ
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;                    //�����Ҫ���������鳤��
	int* b = (int*)calloc(range, sizeof(int));   //��������Ϊrange*int�Ŀռ�����
	for (long i = 0; i < size; i++) {
		b[a[i] - min] += 1;                     //ͳ�Ƹ������ݼ�ȥmin��ռ�ĸ���   ��b���±�Ϊi1,a���±�Ϊi2
	}
	int j = 0;
	for (int i = 0; i < range; i++) {          //����ͳ������
		while (b[i]--) {                       //�������εĸ�����Ϊѭ��������Ϊ��Ҫ����ĸ���
			a[j++] = i + min;                  //��Żص������±����һ����ϵ���� i1=a[i2]-min;a[i2]=i1+min,���Դ��ȥ��������ȷ��
		}
	}
	free(b);                                  //�ͷ���ʱ����
	b = NULL;
}

/*������������*/
void RadixCountSort(int* a, long size) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	int* tem[RADIX_10];                           //����һ����ʱָ������
	for (int i = 0; i < 10; i++) {
		tem[i] = (int*)malloc(sizeof(int) * (size + 1));
		tem[i][0] = 0;                            //indexΪ0����¼�������ݵĸ���
	}
	for (int pos = 1; pos <= KEYNUM_31; pos++) {
		for (long i = 0; i < size; i++) {
			int temp = 1;
			for (int k = 0; k < pos - 1; k++)
			{
				temp *= 10;
			}
			int num = (a[i] / temp) % 10;  //��������β����ȡ��õ���ǰλ������,�������λ�����٣�ȡ��ȡ��֮���õ�һ��0
			int index = ++tem[num][0];     //��Ӧ���֣��õ����Ǹ���λ�����ڼ�����������ֵġ�Ͱ��
			tem[num][index] = a[i];      //��������index���Ž���Ӧ���ӵġ�Ͱ��
		}
		for (int i = 0, j = 0; i < RADIX_10; i++) {
			for (long k = 1; k <= tem[i][0]; k++) {
				a[j++] = tem[i][k];    //tem[i][0]��ʾÿ����Ӧ���ֵ�Ͱ�����Ӧ�ĸ�������k���ܳ�����
			}                         //��˳������ȫ���Żص�a������ȥ
			tem[i][0] = 0;           //Ȼ���ٽ���Ӧ���ֵ�Ͱ��¼������λ�ø�0
		}
	}
}

/*��ɫ����*/
int* ColorSort(int* b,long*size2) {
	printf("��������Ҫ����0-2�������������");
	long num;
	int ret;
	while (1) {
		ret= scanf("%ld", &num);
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("����������������룺");
		}
		if (ret == 1 && num < 1) {
			printf("������󣡲�������С��1������������������룺");
		}
		if (ret == 1 && num >= 1) {
			fflush(stdin);
			break;
		}
	}
	*size2 = num;                       //�����������
	FILE* fp1;                         //�������ļ���ָ�� дģʽ
	if ((fp1 = fopen("�����2.dat", "w")) == NULL) {
		printf("Can not open the file\n");
	}
	srand((unsigned int)time(0));  //��ʼ�����������
	for (long i = 0; i < num; i++) {
		fprintf(fp1, "%d\t", rand() % 3);
	}
	fclose(fp1);
	FILE* fp2;
	if ((fp2 = fopen("�����2.dat", "r")) == NULL) {
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
	for (; p1 <= p2;) {           //p1,p2����ʱ����
		if (*p1 == 0) {         //p0��p1����֮��p1���ƶ���
			temp = *p1;
			*p1 = *p0;
			*p0 = temp;
			p0++;
			p1++;
		}
		else if (*p1 == 1) p1++;
		else if (*p1 == 2) {         //p2��p1����֮��p1�ǲ��ƶ���
			temp = *p1;
			*p1 = *p2;
			*p2 = temp;
			p2--;
		}
	}
	return b;
}

/*���⣨��һ�������������ҵ���K�������*/
void FindKMin(int* a, long begin, long end,long k) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	long pivot;
	if (begin < end) {
		pivot = Partition(a, begin, end);      //��aһ��Ϊ��,���������ֵpivot 
		if (pivot + 1 > k) {
			FindKMin(a, begin, pivot - 1, k); //��ʱ��K�����λ���Ҳ�������
			return;
		}
		else if (pivot + 1 < k) {
			FindKMin(a, pivot + 1, end, k);  //��ʱ��K�����λ�����������
			return;
		}
		else if (pivot + 1 == k) {
			return;
		}
	}

}

/*���ɲ������ݲ�д�뺯��*/
long Createrand() {
	printf("1. 0-50֮��������        2.0-100֮��������           3. 0-1000֮��������\n4. 0-10000֮��������          5. 0-����������ֵ֮��������     6.0-2֮��������\n");
	printf("�밴�ղ˵�ѡ����Ҫ���ɵ��������Χ��");
	int option,ret,num=1,judge=1;
	while (1) {
		ret= scanf("%d", &option);                //��ֹ�쳣����
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("����������������룺");
		}
		if (ret == 1 && (option < 1 || option>6)) {
			printf("������ѡ����ȷ�Ĳ˵�ѡ�");
		}
		if (ret == 1 && (option >= 1 && option <= 6)) {
			fflush(stdin);
			break;
		}
	}
	printf("��ѡ����Ҫ���ɵ������������");
	long count = 0;
	while (1) {
		ret=scanf("%ld", &count);              //��ֹ�쳣����
		printf("\n");
		rewind(stdin);
		if (ret == 0) {
			printf("����������������룺");
		}
		if (ret == 1 && count < 1) {
			printf("������󣡲�������С��1������������������룺");
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
		default:printf("��ѡ����ȷ����ţ�\n"); judge = 1; break;
		}
	}
	FILE* fp;                         //�������ļ���ָ�� дģʽ
	if ((fp = fopen("�����1.dat", "w")) == NULL) {
		printf("Can not open the file\n");
	}
	srand((unsigned int)time(0));  //��ʼ�����������
	for (int i = 0; i < count; i++) {
		fprintf(fp, "%d\t", rand() % num);
	}
	fclose(fp);
	printf("������ϣ�\n");
	return count;        //�������ɸ�����������������
}

/*���ļ�����*/
int* ReadRand(long count) {
	FILE* fp;                         //�������ļ���ָ�� дģʽ
	if ((fp = fopen("�����1.dat", "r")) == NULL) {
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

/*������ݺ���*/
void Display(int* a,long length) {
	if (!a) return;
	printf("�������\n");
	for (long i = 0; i < length; i++) {
		printf("%d  ", a[i]);
		if (i!=0&&i % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

/*ͳ�ƴ�����ͬ����ʱ��*/
void statisticTime1(int*a,int begin,int end,int size1) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	//ͳ�Ʋ�������ʱ��
	clock_t start1, diff1;
	start1= clock();
	insertSort(a, size1);
	diff1 = clock()-start1;
	double d1;
	d1 = (double)diff1 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�ƹ鲢����ʱ��
	clock_t start2 = clock();
	MergeSort(a, begin, end);
	clock_t diff2 = clock() - start2;
	double d2;
	d2 = (double)diff2 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�ƿ������򣨵ݹ飩ʱ��
	clock_t start3 = clock();
	QuickSort_Recursion(a,begin,end,1);
	clock_t diff3 = clock() - start3;
	double d3;
	d3 = (double)diff3 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�ƿ��������Ż��棨�ݹ飩ʱ��
	clock_t start4 = clock();
	QuickSort_Recursion(a, begin, end, 2);
	clock_t diff4 = clock() - start4;
	double d4;
	d4 = (double)diff4 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�ƿ�������ǵݹ��ʱ��
	clock_t start5 = clock();
	QuickSort(a,begin,end);
	clock_t diff5 = clock() - start5;
	double d5;
	d5 = (double)diff5 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�Ƽ�������ʱ��
	clock_t start6 = clock();
	CountSort(a,size1);
	clock_t diff6 = clock() - start6;
	double d6;
	d6 = (double)diff6 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	//ͳ�ƻ�������ʱ��
	clock_t start7 = clock();
	RadixCountSort(a,size1);
	clock_t diff7 = clock() - start7;
	double d7;
	d7 = (double)diff7 / CLOCKS_PER_SEC;
	a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	printf("������������ʱ�䣺% lf s \n�鲢��������ʱ�� %lf s\n������������ʱ�� %lf s\n���������Ż���������ʱ��%lf s\n��������ǵݹ�����ʱ��%lf s\n������������ʱ��%lf s\n������������ʱ��%lf s\n",d1,d2,d3,d4,d5,d6,d7);
}

/*ͳ��������ε���������ʱ��*/
void statisticTime2(int* a, int begin, int end, int size1) {
	if (!a) {
		printf("���������������\n");
		return;
	}
	/*ͳ�Ʋ�������ʱ��*/
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�ƹ鲢����ʱ��
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�ƿ������򣨵ݹ飩ʱ��
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�ƿ��������Ż��棨�ݹ飩ʱ��
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�ƿ�������ǵݹ��ʱ��
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�Ƽ�������ʱ��
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
		a= ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	//ͳ�ƻ�������ʱ��
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
		a = ReadRand(size1);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
	}
	printf("������������ʱ�䣺%lf s  \n�鲢��������ʱ�� %lf s \n������������ʱ�� %lf s \n���������Ż���������ʱ��%lf s  \n��������ǵݹ�����ʱ��%lf s \n������������ʱ��%lf s \n������������ʱ��%lf s \n",times1,times2,times3,times4 ,times5,times6,times7);
}

int main() {
	int judge = 1;
	int* a = NULL;
	int *b = NULL;        //����һ��ָ�룬����ָ������
	int temp = 0;    //size1������������������±꣬temp�Ǵ����ʱ�����ĵط�
	long count = 0, size1 = 0, size2 = 0,end=0,begin = 0,k1 = 0, k2 = 0;
	while (judge) {
		printf("\n\n");
		printf("                         ******************************ϵͳ���ܲ˵�******************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              **************************************************************\n");
		printf("                              * 1.��������                 **        2.�鲢����            *\n");
		printf("                              **************************************************************\n");
		printf("                              * 3.��������(�ݹ�)           **      4.���������Ż��棨�ݹ飩*\n");
		printf("                              **************************************************************\n");
		printf("                              * 5.�������򣨷ǵݹ飩       **          6.��������          *\n");
		printf("                              **************************************************************\n");
		printf("                              * 7.��������                 **         8.��ɫ����           *\n");
		printf("                              **************************************************************\n");
		printf("                              * 9.�ҳ���KСֵ              **         10.�ҳ���K��ֵ       *\n");
		printf("                              **************************************************************\n");
		printf("                              * 11.���������              **         12.�˳�����          *\n");
		printf("                              **************************************************************\n");
		printf("                              * 13.ͳ�Ƹ�������ʱ��(�������ٴ�����,���������������20k)    *\n");
		printf("                              **************************************************************\n");
		printf("                              * 14.ͳ�Ƹ��������㷨����ʱ��(�����ݶ������,������������100������)*\n");
		printf("                              **************************************************************\n");
		printf("                         ------------------------------------------------------------------------\n");
		printf("                              ��ѡ��˵���ţ�");
		int option, ret;
		while (1) {
			ret = scanf("%d", &option);
			printf("\n");
			rewind(stdin);                                 //������մ������뻺��
			if (ret == 0) {
				printf("                         ����������������룺");
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
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 2:
			start = clock();
			MergeSort(a, begin, end);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 3:
			start = clock();
			QuickSort_Recursion(a, begin, end,1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 4:
			start = clock();
			QuickSort_Recursion(a,begin,end,2);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 5:
			start = clock();
			QuickSort(a, begin, end);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 6:
			start = clock();
			CountSort(a, size1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 7:
			start = clock();
			RadixCountSort(a, size1);
			diff = clock();
			Display(a, size1);
			if (!a) break;
			printf("������ʱ��Ϊ��%ld ms", diff - start);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 8:
			b=ColorSort(b,&size2);
			Display(b,size2);
			break;
		case 9:
			if (!a) {
				printf("���������������\n");
				break;
			}
			printf("����������Ҫ��ѯ�ĵ�KС������");
			while (1) {
				ret = scanf("%d", &k1);             //0<k<=count
				printf("\n");
				rewind(stdin);
				if (ret == 0) {
					printf("����������������룺");
				}
				if (ret == 1 && (k1<1 || k1>count)) {
					printf("����Ĳ���ֵ������Χ�����������룺");
				}
				if (ret == 1 && (k1 >= 1 && k1 <= count)) {
					fflush(stdin);
					break;
				}
			}
			FindKMin(a,begin,end,k1);
			printf("��KС����Ϊ��%d \n", a[k1 - 1]);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 10:
			if (!a) {
				printf("���������������\n");
				break;
			}
			printf("����������Ҫ��ѯ�ĵ�K�������");
			while (1) {
				ret=scanf("%d", &k2);
				printf("\n");
				rewind(stdin);
				if (ret == 0) {
					printf("����������������룺");
				}
				if (ret == 1 && (k2<1 || k2>count)) {
					printf("����Ĳ���ֵ������Χ�����������룺");
				}
				if (ret == 1 && (k2 >= 1 && k2 <= count)) {
					fflush(stdin);
					break;
				}
			}
			k2 = count - k2 + 1;          //����k���ת��Ϊ��kС
			FindKMin(a, begin, end, k2);
			printf("��K�����Ϊ��%d \n", a[k2 - 1]);
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 11:
			count = Createrand();
			size1 = count;          //�����ɵ������������¼����
			end = count - 1;
			a=ReadRand(count);
			break;
		case 12:
			judge = 0;
			break;
		case 13:
			statisticTime1(a,begin,end,size1);
			if (!a) break;
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		case 14:
			statisticTime2(a, begin, end, size1);
			if (!a) break;
			a = ReadRand(count);            //ÿ�����������µ����ļ�������������Ȼ�����ѡ�񶼲���Ҫ����
			break;
		default:printf("������������ȷѡ�\n");
		}
		system("pause");
		system("cls");
	}
}