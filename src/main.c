#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"../inc/qgsort.h"
#define small 10000
#define middle 50000
#define big 200000 
#define MAX 1000000 


int main(int argc, char *argv[]) {
	char choice;
	menu();
	int a[10] = {1,3,2,5,6,7,4,9,8,10};
	int result;
	printf("\n��ѡ����Ĳ���(������ĵ�һ���ַ�Ϊ׼)\n");
    while((choice = getchar()) != 'f')
	{
		if(choice == '\n')
			continue;
		if(choice >= 'a' && choice <= 'e')
		{
			switch(choice)
			{
				case 'a':
					Small();
					go();
					break;
				case 'b':
					Middle();
					go();
					break;
				case 'c':
					Big();
					go();
					break;
				case 'd':
					Tatal();
					go();
					break;
				case 'e':
					Color();
					go();
					break;			
				default:
					go();
			}
			
			
				
		}
		else 
			printf("\n�������,����������:  ");
		
		while(getchar() != '\n')
			continue;	
	}
	
		
	return 0;
}
