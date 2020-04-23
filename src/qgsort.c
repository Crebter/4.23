#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/qgsort.h"
#define small 10000
#define middle 50000
#define big 200000 
#define MAX 1000000 



//0-9的数字 
#define BASE 10

//插入排序 
void insertSort(int *a,int n)
{
	int i,j,temp;
	for(i=1;i<n;i++)
	{
		temp = a[i];
		for(j=i-1;j>=0 && temp<a[j];j--)
		{
			a[j+1] = a[j];		
		}
		a[j+1] = temp;		
	}	
} 

/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	int left_begin = begin;
    int left_end   = mid;

    int right_begin = mid+1;
    int right_end   = end;

    int index = begin;

    while(left_begin<=left_end && right_begin<=right_end)
    {
        if(a[left_begin] > a[right_begin])
            temp[index++] = a[right_begin++];
        else
            temp[index++] = a[left_begin++];
    }

    while(left_begin <= left_end)
        temp[index++] = a[left_begin++];

    while(right_begin <= right_end)
        temp[index++] = a[right_begin++];

    for(index=begin; index<=end; index++)
        a[index] = temp[index];
}


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp)
{
	if(begin < end)
    {
        int mid = (begin+end) / 2; 
        MergeSort(a,begin,mid,temp);//向左边递归分解 
        MergeSort(a,mid+1,end,temp);//向右边递归分解 
        //void MergeArray(int *a,int begin,int mid,int end,int *temp)
        MergeArray(a,begin,mid,end,temp);//合并 
    }
} 


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
	int i,j,pivot;

    if (begin < end)
    {
        i = begin, j = end, pivot = a[begin];
        while (i < j)
        {
            while (i < j && a[j] >= pivot)
            {
                j--;
            }
            a[i] = a[j];
            
            while (i < j && a[i] <= pivot)
            {
                i++;
            }
            a[j] = a[i];
        }
        a[i] = pivot;
        QuickSort_Recursion(a, begin, i - 1);
        QuickSort_Recursion(a, i + 1, end);
    }
} 


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size)
{
	//用数组模拟栈 
	int *Stack = (int*)malloc(sizeof(int)*size);
	int top;
	int begin = 0;
	int end = size - 1;
	int p = Partition(a,begin,end);
	
	
	if(p > begin+1)  //枢轴的左边应该至少有两个数据，不然就排序完毕了
	{
		Stack[top++] = begin; //入栈最左边的数据 
		Stack[top++] = p - 1; //入栈左部分的尾部 
	}
	
	if(p < end-1)  ////枢轴的右边应该至少有两个数据，不然就排序完毕了
	{
		Stack[top++] = p + 1;
		Stack[top++] = end;
	} 
	
	while(top > 0)
	{
		end = Stack[--top];
		begin = Stack[--top];
		p = Partition(a,begin,end);
		
		//若栈中还有数据，则继续刚才的操作 
		if(p > begin+1)  //枢轴的左边应该至少有两个数据，不然就排序完毕了
		{
			Stack[top++] = begin; //入栈最左边的数据 
			Stack[top++] = p - 1; //入栈左部分的尾部 
		}
		
		if(p < end-1)  ////枢轴的右边应该至少有两个数据，不然就排序完毕了
		{
			Stack[top++] = p + 1;
			Stack[top++] = end;
		} 
	}
	free(Stack);
	Stack = NULL; 
} 

/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end)
{
	int temp = a[begin];
	while(begin < end)  //反复横跳 
	{
		while(begin < end && a[end] >= temp)
			end--;
		a[end] = a[begin];
		while(begin < end && a[begin] <= temp)
			begin++;
		a[begin] = a[end];				
	}
		a[begin] = temp;
	return begin;	
} 


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size , int max)
{
	//通过max和min计算出临时数组所需要开辟的空间大小,用时间换取空间 
	int min = a[0];
	int range,i,j;
	int *b;

	for (i = 0; i < size; i++){
		if (a[i] < min)
			min = a[i];
	}

	
	range = max - min + 1;
	//将数组元素全部置零 
	b = (int *)calloc(range, sizeof(int));

	//记录原始数组中每个元素出现的个数 
	for (i = 0; i < size; i++){
		b[a[i] - min] += 1;
	}
	j = 0;
	
	//放回原数组 
	for (i = 0; i < range; i++){
		while (b[i]--){
			a[j++] = i + min;
		}
	}

	free(b);
	b = NULL;
} 


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
 
 //BASE = 10  0-9的数字 
void RadixCountSort(int *a,int size)
{
	int i; 
	int b[size];
	int max = a[0];
	int div = 1;

 	for(i = 1;i<size;i++) //找出最大的数据 
	{  
	    if (a[i] > max)
	      max = a[i];
	}
	while (max/div > 0) 
	{
	    int bucket[BASE] ={0};
	
		for (i=0; i<size; i++) 
		    bucket[(a[i]/div) % BASE]++;//每个位数有多少个相同的数据 
		
		for (i=1;i<BASE;i++) //统计个位相同的数在数组a中出现的位置 
			bucket[i] += bucket[i-1];
		    
		for (i = size - 1;i >= 0;i--) //从桶中拿出数据进行排序 
			b[--bucket[(a[i] / div) % BASE]] = a[i];
		
		for (i = 0;i < size;i++)  
		    a[i] = b[i];
	
   	 	div *= BASE;
	}
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a,int size)
{
	int begin = 0;
	int end = size - 1;
	int i,temp;
	for(i=0;i<size;i++)
	{
		while(2 == a[i] && i<end)
		{
			temp = a[i];
			a[i] = a[end];
			a[end] = temp;
			end--;
		}
		
		while(0 == a[i] && i>begin)
		{
			temp = a[i];
			a[i] = a[begin];
			a[begin] = temp;
			begin++;
		}
	}
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size
 */
 
// int Partition(int *a, int begin, int end)
int find_K(int *a,int begin,int end,int k)
{
	int index = Partition(a,begin,end);
	while(index != k)
	{
		if(index < k)
			begin = index + 1;
		else if(index > k)
			end = index - 1;
		
	}
	return a[index];
}


void menu()
{	 
	printf("***************排序算法******************\n"); 
	printf("*请输入你要看的层次各排序算法的排序表现:*\n");
	printf("*    a.10000            b.50000	        *\n");
	printf("*    c.200000           d.100*100k      *\n");
	printf("*    e.颜色排序         f.退出          *\n");
	printf("*****************************************\n");  
}

void go()
{
	printf("\n");
	system("PAUSE");
	system("cls");
	menu();
	printf("\n输入你选择的操作(以输入的第一个字符为准): ");
}


void Small()
{	

	srand((unsigned)time(NULL));
	int i;
	clock_t start,finish;
	double duration;
	int *s,*temp;
	s = (int *)malloc(sizeof(int)*small);
	temp = (int *)malloc(sizeof(int)*small);
		
	printf("*****10000层次排序表现*****\n");
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "插入排序用时:%f s\n",  duration);
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(s,0,small-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "归并排序用时:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(s,0,small-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(递归)用时:%f s\n", duration);
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(非递归)用时:%f s\n", duration);
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(s,small,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "计数排序用时:%f s\n",duration);
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "基数计数排序用时:%f s\n", duration);
	
	
	free(s);

}

void Middle()
{
	srand((unsigned)time(NULL));
	int i;
	clock_t start,finish;
	double duration;
	int *m,*temp;
	m = (int *)malloc(sizeof(int)*middle);
	temp = (int *)malloc(sizeof(int)*middle);
		
	printf("*****50000层次排序表现*****\n");
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "插入排序用时:%f s\n",  duration);
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(m,0,middle-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "归并排序用时:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(m,0,middle-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(递归)用时:%f s\n", duration);
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(非递归)用时:%f s\n", duration);
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(m,middle,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "计数排序用时:%f s\n",duration);
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "基数计数排序用时:%f s\n", duration);
	
	
	free(m);

}


void Big()
{
	srand((unsigned)time(NULL));
	int i;
	clock_t start,finish;
	double duration;
	int *b,*temp;
	b = (int *)malloc(sizeof(int)*big);
	temp = (int *)malloc(sizeof(int)*big);
		
	printf("*****200000层次排序表现*****\n");
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "插入排序用时:%f s\n",  duration);
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(b,0,big-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "归并排序用时:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(b,0,big-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(递归)用时:%f s\n", duration);
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(非递归)用时:%f s\n", duration);
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(b,big,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "计数排序用时:%f s\n",duration);
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "基数计数排序用时:%f s\n", duration);
	
	
	free(b);

}

int getMax(int *a,int size)
{
	int max = a[0];
	int i;
	for(i=0;i<size;i++)
	{
		if(a[i]>max)
		{
			max = a[i];
		}
	}
	return max;
}


void Tatal()
{	
	int i,j;
	int *temp,*temp2;

	clock_t start,finish;
	double duration;
	srand((unsigned)time(NULL));
	
	printf("100*100k->插入排序测试:\n");
	
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;		
		insertSort(temp,100);
		free(temp);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "插入排序用时:%f s\n", duration);
	
	
	
	printf("\n100*100k->归并排序测试:\n");
//void MergeSort(int *a,int begin,int end,int *temp)
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		temp2 = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;		
		MergeSort(temp,0,100-1,temp2);
		free(temp);
		free(temp2);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "归并排序用时:%f s\n", duration);
	
	
	
	printf("\n100*100k->快速排序(递归)测试:\n");
	
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;	
//void QuickSort_Recursion(int *a, int begin, int end)				
		QuickSort_Recursion(temp,0,100-1);
		free(temp);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(递归)用时:%f s\n", duration);
	
	
	
	printf("\n100*100k->快速排序(非递归)测试:\n");
	
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;	
//void QuickSort(int *a,int size)			
		QuickSort(temp,100);
		free(temp);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "快速排序(非递归)用时:%f s\n", duration);
	
	
	int max1;
	printf("\n100*100k->计数排序测试:\n");
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;
			max1 = getMax(temp,100);	
//void CountSort(int *a, int size , int max)		
		CountSort(temp,100,max1);
		free(temp);
		temp = NULL;
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "计数排序用时:%f s\n", duration);

	

	printf("\n100*100k->基数计数排序测试:\n");
	
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% MAX;	
//void RadixCountSort(int *a,int size)		
		RadixCountSort(temp,100);
		free(temp);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "基数计数排序用时:%f s\n", duration);
	
}

void Color()
{
	int i,j;
	clock_t start,finish;
	double duration;
	int *s,*m,*b;
	s = (int *)malloc(sizeof(int)*small);
	m = (int *)malloc(sizeof(int)*middle);
	b = (int *)malloc(sizeof(int)*big);

		
	printf("*****10000层次排序表现*****\n");
	for(i=0;i<small;i++)    
		s[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "颜色排序用时:%f s\n\n",  duration);
	
	
	printf("*****50000层次排序表现*****\n");
	for(i=0;i<middle;i++)    
		m[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "颜色排序用时:%f s\n\n",  duration);
	
	
	printf("*****200000层次排序表现*****\n");
	for(i=0;i<big;i++)    
		b[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "颜色排序用时:%f s\n\n",  duration);
	
	
	int *temp;
	printf("\n100*100k->颜色排序测试:\n");
	
	start = clock();
	for(i = 0; i < 100000; i++)
	{
		temp = (int *)malloc(sizeof(int)*100);
		for(j=0; j < 100; j++ )    
			temp[j] =  rand()% 3;	
//void ColorSort(int *a,int size)	
		ColorSort(temp,100);
		free(temp);
	}
	finish = clock();
	
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "颜色排序用时:%f s\n\n", duration);
	
}



