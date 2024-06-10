#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void add_task();
void remove_task();
void view_task();
void save_task();
void load_task();
void display_menu();

#define MAX_TASKS 100
#define TASK_LENGTH 256

int task_count = 0;
char tasks[MAX_TASKS][TASK_LENGTH];

int main() {
	int choice;
	while(1) {
		display_menu();
		printf("Enter your choice: ");
		scanf("%d", &choice); //Take the integer in stream and store in address of variable choice
		getchar(); //Consume the newline character | don't interrupt stream
		switch (choice) {
			case 1:
				add_task();
				break;
			case 2:
				remove_task();
				break;
			case 3:
				view_task();
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid choice, try again!\n");
		}
	}
}

void display_menu() {
	printf("1. Add Tasks\n");
	printf("2. Remove Task\n");
	printf("3. View Tasks\n");
	printf("4. Save Tasks\n");
	printf("5. Exit\n");
}

void add_task() {
	if (task_count < MAX_TASKS) {
		printf("Enter task: ");
		fgets(tasks[task_count], TASK_LENGTH, stdin);
		tasks[task_count][strcspn(tasks[task_count], "\n")] = 0;
		task_count++;
	} else {
		printf("Task list is too full!");
	}
}
//Need to add validation to input, check if valid task number
void remove_task() {
	int task_num;
	printf("Enter task number to be removed: ");
	scanf("%d", &task_num);
	getchar();

	if (task_num > 0 && task_num <= task_count) {
		for (int i = task_num - 1; i < task_count - 1; i++) {
			strcpy(tasks[i], tasks[i+1]);
		}
		task_count--;
		printf("Task Removed \n");
	} else {
		printf("Invalied task number. \n");
	}

}

void view_task() {
	for (int i = 0; i < task_count; i++) {
		printf("%d %s\n", i+1, tasks[i]);
	}
}
