#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COUNTRIES 100

char *countries[NUM_COUNTRIES];
int currentCountry = 0;

static void addCountry(GtkWidget *widget, gpointer data)
{
	if (currentCountry >= NUM_COUNTRIES) {
		g_print("Too many countries.");
	}
	char *text = (char *)gtk_entry_get_text(data);
	int size = strlen(text);
	char *copy = (char *)malloc((size + 1) * sizeof(char));
	copy[size] = '\0';
	char *ptr = &text[0]; 
    int index = 0;
    while (*ptr != '\0') {
    	copy[index++] = *ptr++;
    }
    countries[currentCountry++] = copy;


	g_print("Added %s\n", gtk_entry_get_text(data));
	gtk_entry_set_text(data, "");
}

static void printCountries(GtkWidget *widget, gpointer data)
{
	int x;
	for (x = 0; x < NUM_COUNTRIES; x++) {
		if (countries[x] == NULL) {
			break;
		}
		g_print("%s\n", countries[x]);
	}
}

static void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *label;
	GtkWidget *grid;
	GtkWidget *entry;
	GtkWidget *button;

	window = gtk_application_window_new(app);
	label = gtk_label_new("Hello GNOME!");
	//gtk_container_add (GTK_CONTAINER(window), label);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_title (GTK_WINDOW (window), "Welcome to GNOME");
	gtk_window_set_default_size (GTK_WINDOW(window), 600, 480);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	entry = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

	button = gtk_button_new_with_label("Add");
	g_signal_connect(button, "clicked", G_CALLBACK(addCountry), entry);
	g_signal_connect(entry, "activate", G_CALLBACK(addCountry), entry);
	gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 1, 1);

	button = gtk_button_new_with_label("List");
	g_signal_connect(button, "clicked", G_CALLBACK(printCountries), entry);
	gtk_grid_attach(GTK_GRID(grid), button, 1, 2, 1, 1);

	label = gtk_label_new("Enter Country name:");
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
	gtk_widget_show_all (window);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	int i;
	for (i = 0; i < NUM_COUNTRIES; ++i) {
		countries[i] = NULL;
	}

	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}