#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <gtk/gtk.h>

#include <smlog.h>
#include <nubix.h>

#include "nubix-taskbar.h"
#include "nubix-background.h"

struct starter {
	GtkBox *wrapper;
	GtkImage *icon;
	GtkLinkButton *link;
};

static gboolean menu_flag = FALSE;
static GtkWindow *menu;

static void system_callback(void *data)
{
	smlogifo("system_callback");
}

static void menu_destroy(void *data)
{
	menu_flag = FALSE;
	gtk_widget_destroy(GTK_WIDGET(menu));
}

void menu_show()
{
	if(menu_flag == FALSE)
	{
		menu = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
		GtkVBox *layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
		GtkLabel *header = gtk_label_new("Nubix Desktop Submenu");
		GtkLabel *placeholder = gtk_label_new("----------------------------------------");
		GtkLabel *entry = gtk_label_new("empty");

		gtk_container_add(GTK_CONTAINER(menu), layout);

		gtk_box_pack_start(GTK_BOX(layout), GTK_WIDGET(header), FALSE, FALSE, 10);
		gtk_box_pack_start(GTK_BOX(layout), GTK_WIDGET(placeholder), FALSE, FALSE, 10);
		gtk_box_pack_start(GTK_BOX(layout), GTK_WIDGET(entry), FALSE, FALSE, 10);

		g_signal_connect(menu, "destroy", menu_destroy, menu);
		menu_flag = TRUE;
		gtk_widget_show_all(GTK_WIDGET(menu));
	}
	else
	{
		gtk_window_activate_focus(menu);
		smlogifo("menu is allready started!");
	}
}

gboolean btn_press_callback(GtkWidget *btn, GdkEventButton *event, gpointer data)
{
	if(event->type == GDK_BUTTON_PRESS && event->button == 3)
		menu_show();
}

int main(int argc, char **argv)
{
	verbose =1;

	smlogmsg(SMLOGLVL_IFO, "starting nubix desktop environment");
	gtk_init(&argc, &argv);

	struct _screen_resolution reso;
	nubix_get_screen_resolution(&reso);

	GtkBuilder *builder = gtk_builder_new_from_file("../nubix-desktop-env/res/desktop.ui");
	smlogifo("loading desktop ui ressource done");

	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "../nubix-desktop-env/res/desktop.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER );
	smlogifo("loading desktop style sheet done");

	nubix_background_setup(reso.width, reso.height);
	nubix_taskbar_setup(reso.width, 25);
	nubix_taskbar_set_pos(reso.width, reso.height);

	smlogifo("setting object names of css assoiciation terminated");

	gtk_main();

	return 0;
}
