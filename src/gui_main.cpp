#include "gui_main.h"
#include "pwm_gtk_control.h"

gui_main::gui_main( )
{

    _execution_thread = new std::thread (&gui_main::build_gui, this);
}



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

    LoadServoControls(_fixed_box);

    GtkWidget * noteBook = gtk_notebook_new ();
    gtk_notebook_append_page ((GtkNotebook*)noteBook, _fixed_box, gtk_label_new("Single"));

    gtkAllServo * all = new gtkAllServo("Start position", _servos, &_servoParams[0][0]);
    gtk_notebook_append_page ((GtkNotebook*)noteBook, all->get_main(), gtk_label_new("Position"));



    // put everithing to window
    gtk_container_add (GTK_CONTAINER (_window), noteBook);


    /* Enter the main loop */
    gtk_widget_show_all (_window);
    gtk_main ();

    /* Release gtk's global lock */
    gdk_threads_leave();
}

void gui_main::LoadServoControls(GtkWidget * frame){
    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    bool isRaspberryPi = false;
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry

    pwm_chip * chip = NULL;
    if (isRaspberryPi) chip = new pwm_chip(PWM_CHIP_ADDR);

    for (int i = 1; i < 13; i++){
        int xOffset = (i-1) / 6;
        pwm_gtk_control * ctr = new pwm_gtk_control(to_string(i).c_str(), _servoParams[i - 1][1], _servoParams[(i - 1)][2], _servoParams[i - 1][0]);

        if (isRaspberryPi){
            _servos[i-1] = new servo(chip, i);
            ctr->SetServo(_servos[i-1]);
        }

        gtk_fixed_put(GTK_FIXED (_fixed_box), ctr->get_main(), xOffset * 400, (i-1) * 75 - xOffset * 450);
        /*pwm_gtk_control * ctr8 = new pwm_gtk_control("8", 8, 0, 120);
        gtk_fixed_put(GTK_FIXED (_fixed_box), ctr8->get_main(), 0, 0);
        */
    }

}
