#include <konoha.h>
#include <gtk/gtk.h>

static void hello( GtkWidget *widget,gpointer data)
{
    g_print ("Hello World\n");
}

static void destroy( GtkWidget *widget, gpointer data)
{
    g_print ("delete event occurred\n");
    gtk_main_quit ();
}
static gboolean delete_event( GtkWidget *widget,GdkEvent *event, gpointer data)
{
    g_print ("quit\n");
    destroy(NULL,NULL);
    return TRUE;
}

Closure* destroy_func;
Closure* delete_event_func;
Closure* clicked_func;
METHOD Gtk_init(Ctx *ctx, knh_sfp_t *sfp)
{
    int i, argc;
    char **argv;
    Array *a = (Array *)sfp[1].o;
    argc = knh_Array_size(a);
    argv = (char **)alloca(argc * sizeof(char*));
    for (i = 0; i < argc; i++) {
        argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
    }

    gtk_init (&argc, &argv);

    KNH_RETURN_void(ctx, sfp);
}

METHOD Gtk_createWindow(Ctx *ctx, knh_sfp_t *sfp)
{
    delete_event_func = sfp[1].cc;
    destroy_func = sfp[2].cc;

    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    g_signal_connect (G_OBJECT (window), "delete_event",
            G_CALLBACK (delete_event), NULL);
    /*
    g_signal_connect (G_OBJECT (window), "destroy",
            G_CALLBACK (destroy), NULL);
            */

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    KNH_RETURN(ctx,sfp,new_Glue(ctx,"gtk.Window",window,NULL));
}
METHOD Gtk_createButton(Ctx *ctx, knh_sfp_t *sfp)
{
    char* label = p_char(sfp[1]);
    GtkWidget *button = gtk_button_new_with_label (label);
    KNH_RETURN(ctx,sfp,new_Glue(ctx,"gtk.Button",button,NULL));
}
METHOD Gtk_main(Ctx *ctx, knh_sfp_t *sfp)
{
    gtk_main();
    KNH_RETURN_void(ctx,sfp);
}


/* ---------------------------------------------------*/
/* [window] */
METHOD Window_setVisible(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *window = (GtkWidget*) p_cptr(sfp[0]);
    int show = p_int(sfp[1]);
    if(show == 0){
        gtk_widget_hide (window);
    } else {
        gtk_widget_show (window);
    }
    KNH_RETURN_void(ctx,sfp);
}

METHOD Window_setSize(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *window = (GtkWidget*) p_cptr(sfp[0]);
    int width  = p_int(sfp[1]);
    int height = p_int(sfp[2]);
    gtk_widget_set_size_request(window,width,height);
    KNH_RETURN_void(ctx,sfp);
}

METHOD Window_setTitle(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWindow *window = (GtkWindow*) p_cptr(sfp[0]);
    char* title = p_char(sfp[1]);
    gtk_window_set_title(window,title);
    KNH_RETURN_void(ctx,sfp);
}

METHOD Window_add(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *window = (GtkWidget*) p_cptr(sfp[0]);
    GtkWidget *button = (GtkWidget*) p_cptr(sfp[1]);
    gtk_container_add (GTK_CONTAINER (window), button);
    KNH_RETURN_void(ctx,sfp);
}
METHOD Window_addButton(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *window = (GtkWidget*) p_cptr(sfp[0]);
    GtkWidget *button = (GtkWidget*) p_cptr(sfp[1]);
    gtk_container_add (GTK_CONTAINER (window), button);
    KNH_RETURN_void(ctx,sfp);
}

/* ---------------------------------------------------*/
/* [button] */
METHOD Button_setAction(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *button = (GtkWidget*) p_cptr(sfp[0]);
    clicked_func = sfp[1].cc;
    g_signal_connect (G_OBJECT (button), "clicked",
            G_CALLBACK (hello), NULL);
    KNH_RETURN_void(ctx,sfp);
}

METHOD Button_setVisible(Ctx *ctx, knh_sfp_t *sfp)
{
    GtkWidget *button = (GtkWidget*) p_cptr(sfp[0]);
    int show = p_int(sfp[1]);
    if(show == 0){
        gtk_widget_hide (button);
    } else {
        gtk_widget_show (button);
    }
   gtk_widget_show (button);
    KNH_RETURN_void(ctx,sfp);
}

