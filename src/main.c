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
	printf("\n请选择你的操作(以输入的第一个字符为准)\n");
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
			printf("\n输入错误,请重新输入:  ");
		
		while(getchar() != '\n')
			continue;	
	}
	
		
	return 0;
}
