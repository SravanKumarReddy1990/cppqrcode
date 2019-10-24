/* quirc -- QR-code recognition library
 * Copyright (C) 2010-2012 Daniel Beer <dlbeer@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "quirc_internal.h"
#include "dbgutil.h"

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

char compareStrings(char s1[],int slen, char s2[], int len){
	int i=0;

	for(i=0; i<len; i++){
		if(s1[i]!=s2[i]){
			return -1;
		}
	}
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
	
	if(len1!=len2){
		printf("Strings are not same, lengths are different\n");
		return -1;
	}
	

if (compareStrings(usernames,1,USERNAME,len1)!=0 || compareStrings(passwords,1,PASSWORD,len2)!=0)
{
//    std::cout << "inside" << endl;
    label = gtk_label_new("Username and Password is correct.");
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_add(GTK_CONTAINER(win), label);
    gtk_widget_show_all(win);

//label_user = gtk_label_new("Username and Password is correct.");
//gtk_grid_attach(GTK_GRID(grid), label_user, 0, 1, 1, 1);


}

}

static void destroy(GtkWidget *widget, gpointer data){
gtk_main_quit();
}

static void dump_info(struct quirc *q)
{
	int count = quirc_count(q);
	int i;

	printf("%d QR-codes found:\n\n", count);
	for (i = 0; i < count; i++) {
		struct quirc_code code;
		struct quirc_data data;
		quirc_decode_error_t err;

		quirc_extract(q, i, &code);
		err = quirc_decode(&code, &data);

		dump_cells(&code);
		printf("\n");

		if (err) {
			printf("  Decoding FAILED: %s\n", quirc_strerror(err));
		} else {
			printf("  Decoding successful:\n");
			dump_data(&data);
		}

		printf("\n");
	}
}

static void draw_frame(SDL_Surface *screen, struct quirc *q)
{
	uint8_t *pix;
	uint8_t *raw = q->image;
	int x, y;

	SDL_LockSurface(screen);
	pix = screen->pixels;
	for (y = 0; y < q->h; y++) {
		uint32_t *row = (uint32_t *)pix;

		for (x = 0; x < q->w; x++) {
			uint8_t v = *(raw++);
			uint32_t color = (v << 16) | (v << 8) | v;
			struct quirc_region *reg = &q->regions[v];

			switch (v) {
			case QUIRC_PIXEL_WHITE:
				color = 0x00ffffff;
				break;

			case QUIRC_PIXEL_BLACK:
				color = 0x00000000;
				break;

			default:
				if (reg->capstone >= 0)
					color = 0x00008000;
				else
					color = 0x00808080;
				break;
			}

			*(row++) = color;
		}

		pix += screen->pitch;
	}
	SDL_UnlockSurface(screen);
}

static void draw_blob(SDL_Surface *screen, int x, int y)
{
	int i, j;

	for (i = -2; i <= 2; i++)
		for (j = -2; j <= 2; j++)
			pixelColor(screen, x + i, y + j, 0x0000ffff);
}

static void draw_mark(SDL_Surface *screen, int x, int y)
{
	pixelColor(screen, x, y, 0xff0000ff);
	pixelColor(screen, x + 1, y, 0xff0000ff);
	pixelColor(screen, x - 1, y, 0xff0000ff);
	pixelColor(screen, x, y + 1, 0xff0000ff);
	pixelColor(screen, x, y - 1, 0xff0000ff);
}

static void draw_capstone(SDL_Surface *screen, struct quirc *q, int index)
{
	struct quirc_capstone *cap = &q->capstones[index];
	int j;
	char buf[8];

	for (j = 0; j < 4; j++) {
		struct quirc_point *p0 = &cap->corners[j];
		struct quirc_point *p1 = &cap->corners[(j + 1) % 4];

		lineColor(screen, p0->x, p0->y, p1->x, p1->y,
			  0x800080ff);
	}

	draw_blob(screen, cap->corners[0].x, cap->corners[0].y);

	if (cap->qr_grid < 0) {
		snprintf(buf, sizeof(buf), "?%d", index);
		stringColor(screen, cap->center.x, cap->center.y, buf,
			    0x000000ff);
	}
}

static void perspective_map(const double *c,
			    double u, double v, struct quirc_point *ret)
{
	double den = c[6]*u + c[7]*v + 1.0;
	double x = (c[0]*u + c[1]*v + c[2]) / den;
	double y = (c[3]*u + c[4]*v + c[5]) / den;

	ret->x = rint(x);
	ret->y = rint(y);
}

static void draw_grid(SDL_Surface *screen, struct quirc *q, int index)
{
	struct quirc_grid *qr = &q->grids[index];
	int x, y;
	int i;

	for (i = 0; i < 3; i++) {
		struct quirc_capstone *cap = &q->capstones[qr->caps[i]];
		char buf[8];

		snprintf(buf, sizeof(buf), "%d.%c", index, "ABC"[i]);
		stringColor(screen, cap->center.x, cap->center.y, buf,
			    0x000000ff);
	}

	lineColor(screen, qr->tpep[0].x, qr->tpep[0].y,
		  qr->tpep[1].x, qr->tpep[1].y, 0xff00ffff);
	lineColor(screen, qr->tpep[1].x, qr->tpep[1].y,
		  qr->tpep[2].x, qr->tpep[2].y, 0xff00ffff);

	if (qr->align_region >= 0)
		draw_blob(screen, qr->align.x, qr->align.y);

	for (y = 0; y < qr->grid_size; y++) {
		for (x = 0; x < qr->grid_size; x++) {
			double u = x + 0.5;
			double v = y + 0.5;
			struct quirc_point p;

			perspective_map(qr->c, u, v, &p);
			draw_mark(screen, p.x, p.y);
		}
	}
}

static int sdl_examine(struct quirc *q)
{
	SDL_Surface *screen;
	SDL_Event ev;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "couldn't init SDL: %s\n", SDL_GetError());
		return -1;
	}

	screen = SDL_SetVideoMode(q->w, q->h, 32, SDL_SWSURFACE);
	if (!screen) {
		fprintf(stderr, "couldn't init video mode: %s\n",
			SDL_GetError());
		return -1;
	}

	while (SDL_WaitEvent(&ev) >= 0) {
		int i;

		if (ev.type == SDL_QUIT)
			break;

		if (ev.type == SDL_KEYDOWN &&
		    ev.key.keysym.sym == 'q')
			break;

		draw_frame(screen, q);
		for (i = 0; i < q->num_capstones; i++)
			draw_capstone(screen, q, i);
		for (i = 0; i < q->num_grids; i++)
			draw_grid(screen, q, i);
		SDL_Flip(screen);
	}

	SDL_Quit();
	return 0;
}

int main(int argc, char **argv)
{



	struct quirc *q;

	printf("quirc inspection program\n");
	printf("Copyright (C) 2010-2012 Daniel Beer <dlbeer@gmail.com>\n");
	printf("Library version: %s\n", quirc_version());
	printf("\n");

	//if (argc < 2) {
	//	fprintf(stderr, "Usage: %s <testfile.jpg|testfile.png>\n", argv[0]);
	//	return -1;
	//}

	q = quirc_new();
	if (!q) {
		perror("can't create quirc object");
		return -1;
	}
argv[1]="/home/ramu/Downloads/sravan.png";
	int status = -1;
	if (check_if_png(argv[1])) {
		status = load_png(q, argv[1]);
	} else {
		status = load_jpeg(q, argv[1]);
	}
	if (status < 0) {
		quirc_destroy(q);
		return -1;
	}

	quirc_end(q);
	dump_info(q);

	if (sdl_examine(q) < 0) {
		quirc_destroy(q);
		return -1;
	}

	quirc_destroy(q);


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

GtkWidget* windows;
GtkWidget* image;
windows = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  image  = gtk_image_new_from_file("/home/ramu/Downloads/sravan.png");
  //gtk_signal_connect(GTK_OBJECT (window), "destroy",
    //         GTK_SIGNAL_FUNC (destroy), NULL);
  //gtk_container_add(GTK_CONTAINER (windows), image);
//gtk_widget_show_all(windows);
gtk_grid_attach(GTK_GRID(grid), image, 0, 5, 2, 1);


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
