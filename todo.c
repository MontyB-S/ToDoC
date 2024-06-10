#include <stdio.h>
#include <string.h>

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
		scanf("%d", &choice);
		getchar();
		printf("Entered: %c", choice);
		switch (choice) {
			case 1:
				add_task();
				break;
				
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



