#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include <stdlib.h>
#include <gtk/gtk.h>

#include <X11/Xlib.h>

#include <thread>

#include <sys/utsname.h>

#include "servo.h"

class gui_main
{
    public:
        gui_main( );

        void build_gui();

        void LoadServoControls(GtkWidget * frame);

        static const int srvQuantity = 12;

    protected:
    private:

        servo * _servos[srvQuantity];

        GtkWidget * _window;
        GtkWidget * _fixed_box;
        std::thread * _execution_thread;
};

#endif // GUI_MAIN_H
