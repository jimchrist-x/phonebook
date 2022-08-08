#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LINE 25
#define NAME_SIZE 100
#define DESC_SIZE 300
#define PHONE_SIZE 50
#define JOB_SIZE 100


void line(int size); // prints a line to stdout
void upper(char *buffer, short unsigned int size); // lowercase to uppercase
void clear_buff(); 
void remove_newline(char *buff, int size);
void delete_register(char *string, FILE *file, unsigned short int option);
void find_register(char *string, FILE *file, unsigned short int option);
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
typedef struct register_ REGISTER;
int main(int argc, char const *argv[])
{
	unsigned char option;
	REGISTER *person=malloc(sizeof(REGISTER));
	FILE *file;
	time_t unix_time;
	struct tm *time_ptr;
	unsigned char *buffer;

	file=fopen("database.phonebook","ab+");


	if (!person) {
		fprintf(stderr, "Error allocating memory...");
		free(person);
		exit(1);
	}
	if (!file) {
		fprintf(stderr, "Error opening file...");
		free(person);
		exit(1);
	}
	do {
		line(LINE);
		printf("║     CHOOSE OPTION\t║\n");
		line(LINE);
		printf("║ A. SEARCH REGISTER\t║\n"); //DONE
		printf("║ B. WRITE REGISTER\t║\n"); //DONE
		printf("║ C. DELETE REGISTER\t║\n"); //DONE
		printf("║ D. LIST REGISTERS\t║\n"); //DONE
		printf("║ E. DELETE ALL\t\t║\n"); //Done
		line(LINE);
		printf("==>");
		scanf("%c",&option);
		upper(&option, 1);
		system("clear");
		clear_buff();
	} while (option<'A' || option>'Z');
	switch(option) {
		case 'A':
			do {
				line(LINE);
				printf("║     CHOOSE OPTION\t║\n");
				line(LINE);
				printf("║ A. SEARCH BY NAME\t║\n");
				printf("║ B. SEARCH BY JOB\t║\n");
				printf("║ C. SEARCH BY PHONE NUM║\n");
				printf("║ D. SEARCH BY WORK NUM\t║\n");
				line(LINE);
				printf("==>");
				scanf("%c",&option);
				upper(&option, 1);
				system("clear");
				clear_buff();
			} while(option<'A' || option>'D');
			switch(option) {
				case 'A':
					buffer=malloc(sizeof(unsigned char)*NAME_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						free(buffer);
						exit(1);
					}
					printf("NAME|>");
					fgets(buffer, NAME_SIZE, stdin);
					remove_newline(buffer, NAME_SIZE);
					free(buffer);
					find_register(buffer, file, 1);
					break;
				case 'B':
					buffer=malloc(sizeof(unsigned char)*JOB_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("JOB|>");
					fgets(buffer, JOB_SIZE, stdin);
					remove_newline(buffer, JOB_SIZE);
					free(buffer);
					find_register(buffer, file, 2);
					break;
				case 'C':
					buffer=malloc(sizeof(unsigned char)*PHONE_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("PHONE|>");
					fgets(buffer, PHONE_SIZE, stdin);
					remove_newline(buffer, PHONE_SIZE);
					free(buffer);
					find_register(buffer, file, 3);
					break;
				case 'D':
					buffer=malloc(sizeof(unsigned char)*PHONE_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("WORK PHONE|>");
					fgets(buffer, PHONE_SIZE, stdin);
					remove_newline(buffer, PHONE_SIZE);
					free(buffer);
					find_register(buffer, file, 4);
					break;
				default:
					break;
			}
			break;
		case 'B':
			line(LINE);
			printf("║      WRITE MODE\t║\n");
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
			do {
				line(LINE);
				printf("║     CHOOSE OPTION\t║\n");
				line(LINE);
				printf("║ A. DELETE BY NAME\t║\n");
				printf("║ B. DELETE BY JOB\t║\n");
				printf("║ C. DELETE BY PHONE NUM║\n");
				printf("║ D. DELETE BY WORK NUM\t║\n");
				line(LINE);
				printf("==>");
				scanf("%c",&option);
				upper(&option, 1);
				system("clear");
				clear_buff();
			} while(option<'A' || option>'D');
			switch(option) {
				case 'A':
					buffer=malloc(sizeof(unsigned char)*NAME_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("NAME|>");
					fgets(buffer, NAME_SIZE, stdin);
					remove_newline(buffer, NAME_SIZE);
					free(buffer);
					delete_register(buffer, file, 1);
					break;
				case 'B':
					buffer=malloc(sizeof(unsigned char)*JOB_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("JOB|>");
					fgets(buffer, JOB_SIZE, stdin);
					remove_newline(buffer, JOB_SIZE);
					free(buffer);
					delete_register(buffer, file, 2);
					break;
				case 'C':
					buffer=malloc(sizeof(unsigned char)*PHONE_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("PHONE|>");
					fgets(buffer, PHONE_SIZE, stdin);
					remove_newline(buffer, PHONE_SIZE);
					free(buffer);
					delete_register(buffer, file, 3);
					break;
				case 'D':
					buffer=malloc(sizeof(unsigned char)*PHONE_SIZE);
					if (!buffer) {
						printf("Error allocating memory...");
						free(person);
						exit(1);
					}
					printf("WORK PHONE|>");
					fgets(buffer, PHONE_SIZE, stdin);
					remove_newline(buffer, PHONE_SIZE);
					free(buffer);
					delete_register(buffer, file, 4);
					break;
				default:
					break;
			}
			break;
		case 'D':
			fseek(file, 0, SEEK_SET);
			
			while (1) {
				fread(person,sizeof(REGISTER), 1, file);
				if (feof(file)) break;
				line(LINE);
				printf("║\t  %s\t\t║\n", person->name);
				line(LINE);
				printf("║ Description: %s\n", person->description);
				printf("║ Works as a/an %s\n", person->job);
				printf("║ Phone number: %s\n", person->phone_number);
				printf("║ Work number: %s\n", person->work_number);
				printf("║ Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
				printf("\n║\n");
			}
			
			break;
		case 'E':
			remove("database.phonebook");
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
		printf("═");
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
void delete_register(char *string, FILE *file, unsigned short int option) {
	REGISTER *person=malloc(sizeof(REGISTER));
	FILE *temp_file;
	temp_file=fopen("temp.phonebook", "w");
	fseek(temp_file, 0, SEEK_SET);
	fseek(file, 0, SEEK_SET);
	while(1) {
		fread(person, sizeof(REGISTER), 1, file);
		if (feof(file)) {
			free(person);
			break;
		}
		switch(option) {
			case 1:
				if (!strcmp(person->name, string)) {
					printf("Found register!\nDeleting by name...\n");
					continue;
				}
				else {
					fwrite(person, sizeof(REGISTER), 1, temp_file);
				}
				break;
			case 2:
				if (!strcmp(person->job, string)) {
					printf("Found register!\nDeleting by job...\n");
					continue;
				}
				else {
					fwrite(person, sizeof(REGISTER), 1, temp_file);
				}
				break;
			case 3:
				if (!strcmp(person->phone_number, string)) {
					printf("Found register!\nDeleting by phone...\n");
					continue;
				}
				else {
					fwrite(person, sizeof(REGISTER), 1, temp_file);
				}
				break;
			case 4:
				if (!strcmp(person->work_number, string)) {
					printf("Found register!\nDeleting by work phone...\n");
					continue;
				}
				else {
					fwrite(person, sizeof(REGISTER), 1, temp_file);
				}
				break;
			default:
				break;
		}	
		
		
	}
	fclose(file);
	fclose(temp_file);
	remove("database.phonebook");
	rename("temp.phonebook", "database.phonebook");
	free(string);
	exit(0);
}
void find_register(char *string, FILE *file, unsigned short int option) {
	REGISTER *person=malloc(sizeof(REGISTER));
	fseek(file, 0, SEEK_SET);
	while(1) {
		fread(person, sizeof(REGISTER), 1, file);
		if (feof(file)) {
			free(person);
			break;
		}
		switch(option) {
			case 1:
				if (!strcmp(person->name, string)) {
					line(LINE);
					printf("║\t  %s\t\t║\n", person->name);
					line(LINE);
					printf("║ Description: %s\n", person->description);
					printf("║ Works as a/an %s\n", person->job);
					printf("║ Phone number: %s\n", person->phone_number);
					printf("║ Work number: %s\n", person->work_number);
					printf("║ Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
					printf("\n║\n");
					continue;
				}
				break;
			case 2:
				if (!strcmp(person->job, string)) {
					line(LINE);
					printf("║\t%s\t\t║\n", person->name);
					line(LINE);
					printf("║ Description: %s\n", person->description);
					printf("║ Works as a/an %s\n", person->job);
					printf("║ Phone number: %s\n", person->phone_number);
					printf("║ Work number: %s\n", person->work_number);
					printf("║ Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
					printf("\n║\n");
					continue;
				}
				break;
			case 3:
				if (!strcmp(person->phone_number, string)) {
					line(LINE);
					printf("║\t%s\t\t║\n", person->name);
					line(LINE);
					printf("║ Description: %s\n", person->description);
					printf("║ Works as a/an %s\n", person->job);
					printf("║ Phone number: %s\n", person->phone_number);
					printf("║ Work number: %s\n", person->work_number);
					printf("║ Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
					printf("\n║\n");
					continue;
				}
				break;
			case 4:
				if (!strcmp(person->work_number, string)) {
					line(LINE);
					printf("║\t%s\t\t║\n", person->name);
					line(LINE);
					printf("║ Description: %s\n", person->description);
					printf("║ Works as a/an %s\n", person->job);
					printf("║ Phone number: %s\n", person->phone_number);
					printf("║ Work number: %s\n", person->work_number);
					printf("║ Registered at [%d/%d/%d] (%d:%d:%d)", person->calendar.date.day, person->calendar.date.month, person->calendar.date.year, person->calendar.time.hours, person->calendar.time.minutes, person->calendar.time.seconds);
					printf("\n║\n");
					continue;
				}
				break;
			default:
				break;
			}	
	}
	fclose(file);
	free(string);
	exit(0);
}