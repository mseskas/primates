#include "gui_main.h"


gui_main::gui_main( )
{

    _execution_thread = new std::thread (&gui_main::build_gui, this);
}

#include "pwm_gtk_control.h"

void gui_main::build_gui()
{
    gdk_threads_enter();
    XInitThreads();
    gtk_init( 0, NULL );

    /* Create the main window */
    _window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (_window), 8);
    gtk_window_set_title (GTK_WINDOW (_window), "PRIMATES control window");
    //gtk_window_set_default_size(GTK_WINDOW(_window), 400, 300);
    gtk_window_set_position (GTK_WINDOW (_window), GTK_WIN_POS_CENTER);

    _fixed_box = gtk_fixed_new();
    gtk_widget_set_usize(_fixed_box, 900, 450);


  /*  GtkWidget * frame = gtk_frame_new("Display");
    gtk_container_set_border_width(GTK_CONTAINER (_display_widget->get_main_box()), 10);
    gtk_container_add(GTK_CONTAINER (frame), _display_widget->get_main_box());


    gtk_fixed_put(GTK_FIXED (_fixed_box), frame, 0, 0);


    frame = gtk_frame_new("Control");
    gtk_container_set_border_width(GTK_CONTAINER (_control_widget->get_main_box()), 10);
    gtk_container_add(GTK_CONTAINER (frame), _control_widget->get_main_box());
    gtk_fixed_put(GTK_FIXED (_fixed_box), frame, 460, 0);

*/
    // PRIMATES
    //GtkWidget * drive_scale = gtk_hscale_new_with_range(50, 150, 1);
    //gtk_widget_set_usize(drive_scale, 150, 45);
    //gtk_fixed_put(GTK_FIXED (_fixed_box), drive_scale, 45, 350);


    // put everithing to window
    gtk_container_add (GTK_CONTAINER (_window), _fixed_box);


int d[36] =
{
25, 15, 40,
90, 60, 90,
55, 32, 55,
45, 25, 52,
37, 37, 70,
20, 20, 40,
45, 40, 65,
84, 47, 84,
50, 30, 50,
35, 20, 42,
10, 10, 40,
32, 32, 50

};

    for (int i = 1; i < 13; i++){
        int xOffset = (i-1) / 6;

        pwm_gtk_control * ctr8 = new pwm_gtk_control(to_string(i).c_str(), i, d[1 + (3 * (i - 1))], d[ 2 + (3 * (i - 1))], d[3 * (i - 1)]);
        gtk_fixed_put(GTK_FIXED (_fixed_box), ctr8->get_main(), xOffset * 400, (i-1) * 75 - xOffset * 450);
        /*pwm_gtk_control * ctr8 = new pwm_gtk_control("8", 8, 0, 120);
        gtk_fixed_put(GTK_FIXED (_fixed_box), ctr8->get_main(), 0, 0);
        */
    }

    /* Enter the main loop */
    gtk_widget_show_all (_window);
    gtk_main ();

    /* Release gtk's global lock */
    gdk_threads_leave();
}
