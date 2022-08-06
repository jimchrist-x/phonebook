#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LINE 30
#define NAME_SIZE 100
#define DESC_SIZE 300
#define PHONE_SIZE 50
#define JOB_SIZE 100 
void line(int size); // prints a line to stdout
void upper(char *buffer, short unsigned int size); // lowercase to uppercase
void clear_buff();
void remove_newline(char *buff, int size);
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
	unsigned char name[NAME_SIZE];
	unsigned char description[DESC_SIZE];
	unsigned char phone_number[PHONE_SIZE];
	unsigned char job[JOB_SIZE];
	unsigned char work_number[PHONE_SIZE]; 
	struct calendar calendar;
};
int main(int argc, char const *argv[])
{
	unsigned char option;
	typedef struct register_ REGISTER;
	REGISTER *person=malloc(sizeof(REGISTER));
	FILE *file;
	time_t unix_time;
	struct tm *time_ptr;
	file=fopen("database.phonebook","ab+");
	if (!file) {
		fprintf(stderr, "Error opening file...");
		exit(1);
	}
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
		printf("==>");
		scanf("%c",&option);
		upper(&option, 1);
		system("clear");
		clear_buff();
	} while (option<'A' || option>'Z');
	switch(option) {
		case 'A':
			break;
		case 'B':
			line(LINE);
			printf("WRITE MODE\n");
			line(LINE);
			printf("Name: ");
			fgets(person->name, NAME_SIZE,stdin);
			line(LINE);
			printf("Description: ");
			fgets(person->description, DESC_SIZE,stdin);
			line(LINE);
			printf("Job: ");
			fgets(person->job, JOB_SIZE,stdin);
			line(LINE);
			printf("Phone number: ");
			fgets(person->phone_number, PHONE_SIZE,stdin);
			line(LINE);
			printf("Work number: ");
			fgets(person->work_number, PHONE_SIZE,stdin);
			line(LINE);
			unix_time=time(NULL);
			time_ptr=localtime(&unix_time);
			person->calendar.date.day=time_ptr->tm_mday;
			person->calendar.date.month=time_ptr->tm_mon;
			person->calendar.date.year=time_ptr->tm_year+1900;
			person->calendar.time.seconds=time_ptr->tm_sec;
			person->calendar.time.minutes=time_ptr->tm_min;
			person->calendar.time.hours=time_ptr->tm_hour;
			remove_newline(person->name, NAME_SIZE);
			remove_newline(person->description, DESC_SIZE);
			remove_newline(person->job, JOB_SIZE);
			remove_newline(person->phone_number, PHONE_SIZE);
			remove_newline(person->work_number, PHONE_SIZE);
			fseek(file, 0, SEEK_END);
			fwrite(person, sizeof(REGISTER), 1, file);
			break;
		case 'C':
			break;
		case 'D':
			fseek(file, 0, SEEK_SET);
			
			while (1) {
				fread(person,sizeof(REGISTER), 1, file);
				if (feof(file)) break;
				line(LINE);
				printf("\t%s\n", person->name);
				line(LINE);
				printf("Description: %s\n\n", person->description);
				printf("Works as a/an %s\n", person->job);
				line(LINE);
				printf("Phone number: %s\n", person->phone_number);
				printf("Work number: %s\n", person->work_number);
				line(LINE);
				printf("Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
				printf("\n\n\n\n");
			}
			
			break;
		case 'E':
			break;
		case 'F':
			break;
		default:
			break;
	}
	free(person);
	fclose(file);
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
void clear_buff() {
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);  
}
void remove_newline(char *buff, int size) {
	for (int i=0;i<size;i++) {
		if (buff[i]=='\n')
			buff[i]='\0';
	}
}