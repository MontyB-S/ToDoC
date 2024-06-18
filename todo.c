#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

void add_task();
void remove_task();
void view_task();
void save_task();
void load_task();
void display_menu();
void delete_tasks();

int is_run = 0;

#define MAX_TASKS 100
#define TASK_LENGTH 256

GtkWidget *entry;
GtkWidget *label;

int task_count = 0;
char tasks[MAX_TASKS][TASK_LENGTH];

static void on_destroy(GtkWidget *widget, gpointer data){
	gtk_main_quit();
}

static void print_tasks_gui(GtkWidget *widget, gpointer data) {
	GtkWidget *label = GTK_WIDGET(data);
	gchar *tasks_str = g_strdup("");
	for (int i=0; i < task_count; i++) {
		gchar *temp_str = g_strdup_printf("%d. %s\n", i+1, tasks[i]);
		gchar *new_tasks_str = g_strconcat(tasks_str, temp_str, NULL);
		g_free(temp_str);
		g_free(tasks_str);
		tasks_str = new_tasks_str;
	}
	gtk_label_set_text(GTK_LABEL(label), tasks_str);
	g_free(tasks_str);

	gtk_widget_queue_draw(label);
}

static void add_task_gui(GtkWidget *widget, gpointer data) {
	const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));
	

	if (is_run == 0) {
		text = gtk_entry_get_text(GTK_ENTRY(entry));
		g_strlcpy(tasks[task_count], text, TASK_LENGTH);
		task_count++;
	} else if (task_count < MAX_TASKS) {
		text = gtk_entry_get_text(GTK_ENTRY(entry));
		g_strlcpy(tasks[task_count], text, TASK_LENGTH);
		task_count++;
		gtk_label_set_text(GTK_LABEL(label), "Task added successfully.");
	} else {
		gtk_label_set_text(GTK_LABEL(label), "Task list is full!");
	}

	gtk_entry_set_text(GTK_ENTRY(entry), "");
	save_task();
}


int main(int argc, char *argv[]) {
	load_task();
	GtkWidget *window;
	GtkWidget *button;
	GtkWidget *vbox;
	GtkWidget *tasks_label;
	GtkWidget *button_save;
	GtkWidget *button_add;
	GtkWidget *label_add;
	GtkWidget *button_delete;

	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Blank");
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);

	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	tasks_label = gtk_label_new("Tasks displayed");
	gtk_box_pack_start(GTK_BOX(vbox), tasks_label, TRUE, TRUE, 0);

	button = gtk_button_new_with_label("Print Tasks");
	g_signal_connect(button, "clicked", G_CALLBACK(print_tasks_gui), tasks_label);
	gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

	button_save = gtk_button_new_with_label("Save Tasks");
	g_signal_connect(button_save, "clicked", G_CALLBACK(save_task), tasks_label);
	gtk_box_pack_start(GTK_BOX(vbox), button_save, FALSE, FALSE, 0);

	button_delete = gtk_button_new_with_label("Delete All Tasks");
	g_signal_connect(button_delete, "clicked", G_CALLBACK(delete_tasks), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button_delete, FALSE, FALSE, 0);

	entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

	button_add = gtk_button_new_with_label("Add Task");
	g_signal_connect(button, "clicked", G_CALLBACK(add_task_gui), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button_add, FALSE, FALSE, 0);



	label_add = gtk_label_new("Enter task and click 'Add Task'");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	gtk_widget_show_all(window);

	g_print("Starting gtl main loop");
	gtk_main();
	/*
	int choice;
	while(1) {
		display_menu();
		printf("Enter your choice: ");
		scanf("%d", &choice); //Take the integer in stream and store in address of variable choice
		getchar(); //Consume the newline character | do;t interrupt stream
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
			case 4:
				save_task();
				break;
			case 5:
				exit(0);
			default:
				printf("Invalid choice, try again!\n");
		}
	}
	*/
}


void delete_tasks() {
	FILE *fp;
	fp = fopen("saves.txt", "w");
	
	if (fclose(fp) != 0) {
		perror("Error closing file");
		exit(EXIT_FAILURE);
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

void save_task() {
	FILE *fp;
	fp = fopen("saves.txt", "w");

	if (fp == NULL) {
		printf("Error opening file for writing");
		return;
	}

	for (int i = 0; i < task_count; i++) {
		fprintf(fp, "%s\n", tasks[i]);
	}
	fclose(fp);
}

void load_task() {
	FILE *fp;
	fp = fopen("saves.txt", "r");
	if ( fp == NULL) {
		printf("Error opening file for reading");
		return;
	}

	while (fgets(tasks[task_count],TASK_LENGTH, fp)) {
		tasks[task_count][strcspn(tasks[task_count], "\n")] = 0;
		task_count ++;
	}
	fclose(fp);
}

