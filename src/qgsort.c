#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/qgsort.h"
#define small 10000
#define middle 50000
#define big 200000 
#define MAX 1000000 



//0-9������ 
#define BASE 10

//�������� 
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
 *  @description : �鲢���򣨺ϲ����飩
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end����������ָ��temp
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
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end����������ָ��temp
 */
void MergeSort(int *a,int begin,int end,int *temp)
{
	if(begin < end)
    {
        int mid = (begin+end) / 2; 
        MergeSort(a,begin,mid,temp);//����ߵݹ�ֽ� 
        MergeSort(a,mid+1,end,temp);//���ұߵݹ�ֽ� 
        //void MergeArray(int *a,int begin,int mid,int end,int *temp)
        MergeArray(a,begin,mid,end,temp);//�ϲ� 
    }
} 


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
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
 *  @description : �������򣨷ǵݹ�棩
 *  @param       : ����ָ��a�����鳤��size
 */
void QuickSort(int *a,int size)
{
	//������ģ��ջ 
	int *Stack = (int*)malloc(sizeof(int)*size);
	int top;
	int begin = 0;
	int end = size - 1;
	int p = Partition(a,begin,end);
	
	
	if(p > begin+1)  //��������Ӧ���������������ݣ���Ȼ�����������
	{
		Stack[top++] = begin; //��ջ����ߵ����� 
		Stack[top++] = p - 1; //��ջ�󲿷ֵ�β�� 
	}
	
	if(p < end-1)  ////������ұ�Ӧ���������������ݣ���Ȼ�����������
	{
		Stack[top++] = p + 1;
		Stack[top++] = end;
	} 
	
	while(top > 0)
	{
		end = Stack[--top];
		begin = Stack[--top];
		p = Partition(a,begin,end);
		
		//��ջ�л������ݣ�������ղŵĲ��� 
		if(p > begin+1)  //��������Ӧ���������������ݣ���Ȼ�����������
		{
			Stack[top++] = begin; //��ջ����ߵ����� 
			Stack[top++] = p - 1; //��ջ�󲿷ֵ�β�� 
		}
		
		if(p < end-1)  ////������ұ�Ӧ���������������ݣ���Ȼ�����������
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
 *  @description : �������������ţ�
 *  @param       : ����ָ��a���������begin�������յ�end
 */
int Partition(int *a, int begin, int end)
{
	int temp = a[begin];
	while(begin < end)  //�������� 
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
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size���������ֵmax
 */
void CountSort(int *a, int size , int max)
{
	//ͨ��max��min�������ʱ��������Ҫ���ٵĿռ��С,��ʱ�任ȡ�ռ� 
	int min = a[0];
	int range,i,j;
	int *b;

	for (i = 0; i < size; i++){
		if (a[i] < min)
			min = a[i];
	}

	
	range = max - min + 1;
	//������Ԫ��ȫ������ 
	b = (int *)calloc(range, sizeof(int));

	//��¼ԭʼ������ÿ��Ԫ�س��ֵĸ��� 
	for (i = 0; i < size; i++){
		b[a[i] - min] += 1;
	}
	j = 0;
	
	//�Ż�ԭ���� 
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
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
 */
 
 //BASE = 10  0-9������ 
void RadixCountSort(int *a,int size)
{
	int i; 
	int b[size];
	int max = a[0];
	int div = 1;

 	for(i = 1;i<size;i++) //�ҳ��������� 
	{  
	    if (a[i] > max)
	      max = a[i];
	}
	while (max/div > 0) 
	{
	    int bucket[BASE] ={0};
	
		for (i=0; i<size; i++) 
		    bucket[(a[i]/div) % BASE]++;//ÿ��λ���ж��ٸ���ͬ������ 
		
		for (i=1;i<BASE;i++) //ͳ�Ƹ�λ��ͬ����������a�г��ֵ�λ�� 
			bucket[i] += bucket[i-1];
		    
		for (i = size - 1;i >= 0;i--) //��Ͱ���ó����ݽ������� 
			b[--bucket[(a[i] / div) % BASE]] = a[i];
		
		for (i = 0;i < size;i++)  
		    a[i] = b[i];
	
   	 	div *= BASE;
	}
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : ��ɫ����
 *  @param       : ����ָ��a��ֻ��0��1��2Ԫ�أ������鳤��size
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
 *  @name        : ����
 *  @description : ��һ�������������ҵ���K��/С����
 *  @param       : ����ָ��a�����鳤��size
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
	printf("***************�����㷨******************\n"); 
	printf("*��������Ҫ���Ĳ�θ������㷨���������:*\n");
	printf("*    a.10000            b.50000	        *\n");
	printf("*    c.200000           d.100*100k      *\n");
	printf("*    e.��ɫ����         f.�˳�          *\n");
	printf("*****************************************\n");  
}

void go()
{
	printf("\n");
	system("PAUSE");
	system("cls");
	menu();
	printf("\n������ѡ��Ĳ���(������ĵ�һ���ַ�Ϊ׼): ");
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
		
	printf("*****10000����������*****\n");
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",  duration);
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(s,0,small-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "�鲢������ʱ:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(s,0,small-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ݹ�)��ʱ:%f s\n", duration);
	
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ǵݹ�)��ʱ:%f s\n", duration);
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(s,small,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",duration);
	
	
	for(i=0;i<small;i++)    
		s[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������������ʱ:%f s\n", duration);
	
	
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
		
	printf("*****50000����������*****\n");
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",  duration);
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(m,0,middle-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "�鲢������ʱ:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(m,0,middle-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ݹ�)��ʱ:%f s\n", duration);
	
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ǵݹ�)��ʱ:%f s\n", duration);
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(m,middle,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",duration);
	
	
	for(i=0;i<middle;i++)    
		m[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������������ʱ:%f s\n", duration);
	
	
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
		
	printf("*****200000����������*****\n");
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX; 
	start = clock();
	//void insertSort(int *a,int n)
	insertSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",  duration);
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start=clock();
	//void MergeSort(int *a,int begin,int end,int *temp)
	MergeSort(b,0,big-1,temp);
	
	finish=clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "�鲢������ʱ:%f s\n",  duration);
	free(temp);
	
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void QuickSort_Recursion(int *a, int begin, int end)
	QuickSort_Recursion(b,0,big-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ݹ�)��ʱ:%f s\n", duration);
	
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void QuickSort(int *a,int size)
	QuickSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������(�ǵݹ�)��ʱ:%f s\n", duration);
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void CountSort(int *a, int size , int max)
	CountSort(b,big,MAX-1);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "����������ʱ:%f s\n",duration);
	
	
	for(i=0;i<big;i++)    
		b[i] = rand()% MAX;
	start = clock();
	//void RadixCountSort(int *a,int size)
	RadixCountSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��������������ʱ:%f s\n", duration);
	
	
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
	
	printf("100*100k->�����������:\n");
	
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
	printf( "����������ʱ:%f s\n", duration);
	
	
	
	printf("\n100*100k->�鲢�������:\n");
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
	printf( "�鲢������ʱ:%f s\n", duration);
	
	
	
	printf("\n100*100k->��������(�ݹ�)����:\n");
	
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
	printf( "��������(�ݹ�)��ʱ:%f s\n", duration);
	
	
	
	printf("\n100*100k->��������(�ǵݹ�)����:\n");
	
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
	printf( "��������(�ǵݹ�)��ʱ:%f s\n", duration);
	
	
	int max1;
	printf("\n100*100k->�����������:\n");
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
	printf( "����������ʱ:%f s\n", duration);

	

	printf("\n100*100k->���������������:\n");
	
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
	printf( "��������������ʱ:%f s\n", duration);
	
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

		
	printf("*****10000����������*****\n");
	for(i=0;i<small;i++)    
		s[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(s,small);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��ɫ������ʱ:%f s\n\n",  duration);
	
	
	printf("*****50000����������*****\n");
	for(i=0;i<middle;i++)    
		m[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(m,middle);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��ɫ������ʱ:%f s\n\n",  duration);
	
	
	printf("*****200000����������*****\n");
	for(i=0;i<big;i++)    
		b[i] = rand()% 3; 
	start = clock();
//void ColorSort(int *a,int size)
	ColorSort(b,big);
	
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf( "��ɫ������ʱ:%f s\n\n",  duration);
	
	
	int *temp;
	printf("\n100*100k->��ɫ�������:\n");
	
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
	printf( "��ɫ������ʱ:%f s\n\n", duration);
	
}



