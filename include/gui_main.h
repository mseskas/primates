#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <stdlib.h>
#include <gtk/gtk.h>

#include <X11/Xlib.h>

#include <thread>


class gui_main
{
    public:
        gui_main( );

        void build_gui();
    protected:
    private:

        GtkWidget * _window;
        GtkWidget * _fixed_box;
        std::thread * _execution_thread;
};

#endif // GUI_MAIN_H
