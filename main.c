#include <stdio.h>


#define LINE 30 
void line(int size); // prints a line to stdout
void upper(char *buffer, short unsigned int size); // lowercase to uppercase


struct time {
	int seconds;
	int minutes;
	int hours;
};
struct date {
	unsigned short int day;
	unsigned short int month;
	unsigned short int year;
};
struct calendar {
	struct date date;
	struct time time;
};
struct register_ {
	unsigned char name[100];
	unsigned char description[300];
	unsigned char phone_number[50];
	unsigned char job[100];
	unsigned char Work_number[100]; 
	struct calendar calendar;
};
int main(int argc, char const *argv[])
{
	unsigned char option;
	typedef struct register_ REGISTER;
	REGISTER person;
	do {
		line(LINE);
		printf("\tCHOOSE OPTION\n");
		line(LINE);
		printf("A. READ REGISTER\n");
		printf("B. WRITE REGISTER\n");
		printf("C. DELETE REGISTER\n");
		printf("D. LIST REGISTERS\n");
		printf("E. SEARCH REGISTER\n");
		printf("F. DELETE ALL\n");
		scanf("%c", &option);
		upper(&option, 1);
		fflush(stdin);
	} while (option<'A' || option>'Z');
	switch(option) {
		case 'A':
			break;
		case 'B':
			break;
		case 'C':
			break;
		case 'D':
			break;
		case 'E':
			break;
		case 'F':
			break;
		default:
			break;
	}
	return 0;
}
void line(int size) {
	for (int i=0;i<size;i++) {
		printf("=");
	}
	printf("\n");
}
void upper(char *buffer, short unsigned int size) {
	for (int i=0;i<size;i++) {
		if (buffer[i]>'Z') 
			buffer[i]=buffer[i]-32;
	}
}