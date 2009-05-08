class Gtk;
class GtkWidget;
class Window extends GtkWidget;
class Button extends GtkWidget;

void Gtk.init(Array argv);
//Window Gtk.createWindow(Closure deletefunc,Closure destroyfunc);
Window Gtk.createWindow();
Button Gtk.createButton(String name);
void Gtk.main();

void Window.setVisible(Boolean show);
void Window.setTitle(String title);
void Window.setSize(int width,int height);
void Window.add(GtkWidget w);
void Window.addButton(Button b);

//void Button.setAction(Closure c);
void Button.setAction();
void Button.setVisible(Boolean show);

