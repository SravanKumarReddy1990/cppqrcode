#include <gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <string.h>

static int counter = 0;
 GtkWidget *window;
//Login Forms;
GtkWidget *grid;
 GtkWidget *Login_button, *Quit_button;
GtkWidget *u_name;
GtkWidget *pass;
GtkWidget *label_user;
GtkWidget *label_pass;
GtkWidget  *button_container;

//Create Product Forms;
GtkWidget *plistgrid;
GtkWidget *label_p;
GtkWidget *label_p_name;
GtkWidget *label_p1;
GtkWidget *label_p_name1;
GtkWidget *p;
GtkWidget *p_name;

int displayplist(){
plistgrid = gtk_grid_new();
gtk_grid_set_row_spacing(GTK_GRID(plistgrid), 4);
gtk_container_add(GTK_CONTAINER(window), plistgrid);

label_p = gtk_label_new("Username  ");
label_p_name = gtk_label_new("Password  ");

label_p1 = gtk_label_new("Username  ");
label_p_name1 = gtk_label_new("Password  ");

p = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(p), "Username");
gtk_grid_attach(GTK_GRID(plistgrid), label_p, 0, 1, 1, 1);
gtk_grid_attach(GTK_GRID(plistgrid), label_p_name, 1, 1, 2, 1);

p_name = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(p_name), "Password");
gtk_grid_attach(GTK_GRID(plistgrid), label_p_name1, 0, 2, 1, 1);
gtk_grid_attach(GTK_GRID(plistgrid), label_p1, 1, 2, 1, 1);
//gtk_widget_destroy(pass);
gtk_widget_show_all(window);

}
//char compareStrings(char s1[],int slen, char s2[], int len){
//	int i=0;
//	for(i=0; i<len; i++){
//		if(s1[i]!=s2[i]){
//			return -1;
//		}
//	}
//	return 0;
//}
int hidefrontdis(){
gtk_widget_destroy(Login_button);
gtk_widget_destroy(Quit_button);
gtk_widget_destroy(u_name);
gtk_widget_destroy(pass);
gtk_widget_destroy(label_user);
gtk_widget_destroy(label_pass);
gtk_widget_destroy(button_container);
gtk_widget_destroy(grid);
	return 0;
}
void create_window(GtkWidget *button, gpointer data) {
GtkWidget *win, *label;
const gchar *PASSWORD;
PASSWORD=gtk_entry_get_text(GTK_ENTRY(pass));
//g_print (gtk_entry_get_text(GTK_ENTRY(entry)));
g_print("clicked %s\n", PASSWORD);
const gchar *USERNAME;
USERNAME=gtk_entry_get_text(GTK_ENTRY(u_name));
//g_print (gtk_entry_get_text(GTK_ENTRY(entry)));
g_print("clicked %s\n", USERNAME);
const char* usernames="";
const char* passwords="";
int len1=0, len2=0;
	int i;
	//calculate lengths
	i=0;
	while(USERNAME[i++]!='\0') len1++;
	i=0;
	while(PASSWORD[i++]!='\0') len2++;	
	//if(len1!=len2){
	//	printf("Strings are not same, lengths are different\n");
	//	return -1;
	//}
if (compareStrings(usernames,1,USERNAME,len1)!=0 || compareStrings(passwords,1,PASSWORD,len2)!=0)
{

//    label = gtk_label_new("Username and Password is correct.");
//    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_container_add(GTK_CONTAINER(win), label);
//    gtk_widget_show_all(win);
int i=mains(USERNAME,PASSWORD);
if(i==0){
hidefrontdis();
displayplist();
}
//label_user = gtk_label_new("Username and Password is correct.");
//gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);


}

}

static void destroy(GtkWidget *widget, gpointer data){
gtk_main_quit();
}

int displaylogin(int argc, char **argv){
//readqr("/home/ramu/Downloads/sravan.png");
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
gtk_entry_set_visibility(GTK_ENTRY(u_name), 0);

pass = gtk_entry_new();
gtk_entry_set_placeholder_text(GTK_ENTRY(pass), "Password");
gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 2, 1, 1);
gtk_grid_attach(GTK_GRID(grid), pass, 1, 2, 1, 1);
//gtk_widget_destroy(pass);

Login_button = gtk_button_new_with_label("Log in");
g_signal_connect(Login_button, "clicked", G_CALLBACK(create_window), NULL);
gtk_grid_attach(GTK_GRID(grid), Login_button, 0, 3, 2, 1);

Quit_button = gtk_button_new_with_label("Quit");
g_signal_connect(Quit_button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
gtk_grid_attach(GTK_GRID(grid), Quit_button, 0, 4, 2, 1);

//GtkWidget* image;
//windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//  image  = gtk_image_new_from_file("/home/ramu/Downloads/sravan.png");
  //gtk_signal_connect(GTK_OBJECT (window), "destroy",
    //         GTK_SIGNAL_FUNC (destroy), NULL);
  //gtk_container_add(GTK_CONTAINER (windows), image);
//gtk_widget_show_all(windows);
//gtk_grid_attach(GTK_GRID(grid), image, 0, 5, 2, 1);
   //g_signal_connect (window, "destroy",
   //G_CALLBACK (destroy), NULL);
  // gtk_container_set_border_width
    //  (GTK_CONTAINER (window), 200);
 //  button = gtk_button_new_with_label ("Click Me!");
 //char* b="button";
 //  g_signal_connect ((button),
 //     "clicked",G_CALLBACK (greet),
 //     "button");
   //gtk_container_add (GTK_CONTAINER (window), button);
   gtk_widget_show_all(window); 
   gtk_main ();

}
