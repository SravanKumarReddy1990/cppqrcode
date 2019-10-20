#include <iostream>
#include <gtk-3.0/gtk/gtk.h>

using namespace std;

static int counter = 0;
 GtkWidget *window;
   //GtkWidget *button;
GtkWidget *grid;
 GtkWidget *Login_button, *Quit_button;
GtkWidget *u_name;
GtkWidget *pass;
GtkWidget *label_user;
GtkWidget *label_pass;
GtkWidget  *button_container;

void create_window(GtkWidget *button, gpointer window) {

GtkWidget *win, *label;

//Username and Password to validate credentials
const char* USERNAME = "";
const char* PASSWORD = "xsd";
const char* usernames="";
const char* passwords="";


//Checking if user's entered credentials are equal to actual USERNAME and PASSWORD 
if (!(usernames==USERNAME) || !(passwords == PASSWORD))
{
    std::cout << "inside" << endl;
    label = gtk_label_new("Username and Password is correct.");
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(win), label);
    gtk_widget_show_all(win);

//label_user = gtk_label_new("Username and Password is correct.");
//gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);


}

//else if (username != USERNAME || password != PASSWORD)

//{
//    label = gtk_label_new("Username and Password is incorrect.");
//    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_container_add(GTK_CONTAINER(win), label);
//    gtk_widget_show_all(win);

//}

}

static void destroy(GtkWidget *widget, gpointer data){
gtk_main_quit();
}


 
int main( int   argc,char *argv[] )
{
 
   


   gtk_init (&argc, &argv);
   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
 window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "Login page");
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(window), 10);
gtk_window_set_resizable(GTK_WINDOW(window), FALSE);


grid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
gtk_container_add(GTK_CONTAINER(window), grid);

label_user = gtk_label_new("Username  ");
label_pass = gtk_label_new("Password  ");

u_name = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(u_name), "Username");
gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(grid), u_name, 1, 1, 2, 1);

pass = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(pass), "Password");
gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 2, 1, 1);
gtk_entry_set_visibility(GTK_ENTRY(pass), 0);
gtk_grid_attach(GTK_GRID(grid), pass, 1, 2, 1, 1);

Login_button = gtk_button_new_with_label("Log in");
g_signal_connect(Login_button, "clicked", G_CALLBACK(create_window), NULL);
gtk_grid_attach(GTK_GRID(grid), Login_button, 0, 3, 2, 1);

Quit_button = gtk_button_new_with_label("Quit");
g_signal_connect(Quit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
gtk_grid_attach(GTK_GRID(grid), Quit_button, 0, 4, 2, 1);


   //g_signal_connect (window, "destroy",
   //G_CALLBACK (destroy), NULL);
   /* Let's set the border width of the window to 20.
    * You may play with the value and see the
    * difference. */
   gtk_container_set_border_width
      (GTK_CONTAINER (window), 200);
 
 //  button = gtk_button_new_with_label ("Click Me!");
 //char* b="button";
 //  g_signal_connect ((button),
 //     "clicked",G_CALLBACK (greet),
 //     "button");
 
   //gtk_container_add (GTK_CONTAINER (window), button);
 
   gtk_widget_show_all(window); 
 
   gtk_main ();
 
   return 0;
}
