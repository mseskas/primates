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
    gtk_widget_set_usize(_fixed_box, 900, 400);


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


pwm_gtk_control * ctr = new pwm_gtk_control("8", 8);
gtk_fixed_put(GTK_FIXED (_fixed_box), ctr->get_main(), 20, 50);


pwm_gtk_control * ctr2 = new pwm_gtk_control("9", 9);
gtk_fixed_put(GTK_FIXED (_fixed_box), ctr2->get_main(), 400, 50);

    /* Enter the main loop */
    gtk_widget_show_all (_window);
    gtk_main ();

    /* Release gtk's global lock */
    gdk_threads_leave();
}
