#include "gui_main.h"
#include "pwm_gtk_control.h"

gui_main::gui_main( )
{
    bool isRaspberryPi = false;
    _execution_thread = new std::thread (&gui_main::build_gui, this);
}

void gui_main::build_gui()
{
    struct utsname sysinfo;
    uname(&sysinfo);
    //cout << "Your computer is : " << sysinfo.nodename << endl;
    std::string g = "raspberrypi";
    if ( g.compare(sysinfo.nodename) == 0) isRaspberryPi = true;  // if raspberry


    int params[12][3] = {
            {25, 15, 40},
            {90, 60, 90},
            {50, 32, 60},
            {45, 25, 52},
            {37, 37, 70},
            {20, 10, 40},
            {45, 40, 65},
            {84, 47, 84},
            {50, 30, 75},
            {35, 20, 42},
            {10, 10, 40},
            {32, 15, 50}
        };

    _servoParams = &params[0][0];

    gdk_threads_enter();
    XInitThreads();
    gtk_init( 0, NULL );

    /* Create the main window */
    _window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (_window), 8);
    gtk_window_set_title (GTK_WINDOW (_window), "PRIMATES control window");
    //gtk_window_set_default_size(GTK_WINDOW(_window), 400, 300);
    gtk_window_set_position (GTK_WINDOW (_window), GTK_WIN_POS_CENTER);

    _pwmControlPage = gtk_fixed_new();
    gtk_widget_set_usize(_pwmControlPage, 900, 450);

    LoadServoControls(_pwmControlPage);

    GtkWidget * noteBook = gtk_notebook_new ();

// second page initialization

    _positionPage = gtk_fixed_new();
    gtk_widget_set_usize(_positionPage, 900, 450);


    gtkAllServo * all = new gtkAllServo("Start position", _servos, _servoParams);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 0);

    all = new gtkAllServo("2nd position", _servos, _servoParams);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 60);

    RewardView * view;
    if (isRaspberryPi) {
        view = new RewardView(new Reward(new MPU6050()));
    } else {
        view = new RewardView(NULL);
    }

    gtk_fixed_put(GTK_FIXED (_positionPage), view->get_main(), 250, 0);







    gtk_notebook_append_page ((GtkNotebook*)noteBook, _positionPage, gtk_label_new("Position"));
    gtk_notebook_append_page ((GtkNotebook*)noteBook, _pwmControlPage, gtk_label_new("PWM Control"));

    // put everithing to window
    gtk_container_add (GTK_CONTAINER (_window), noteBook);
    /* Enter the main loop */
    gtk_widget_show_all (_window);
    gtk_main ();
    /* Release gtk's global lock */
    gdk_threads_leave();
}

void gui_main::LoadServoControls(GtkWidget * frame){

    pwm_chip * chip = NULL;
    if (isRaspberryPi) chip = new pwm_chip(PWM_CHIP_ADDR);

    for (int i = 1; i < 13; i++){
        int xOffset = (i-1) / 6;
        pwm_gtk_control * ctr = new pwm_gtk_control(to_string(i).c_str(), _servoParams[(i - 1)* 3 + 1], _servoParams[(i - 1)* 3 + 2], _servoParams[(i - 1)* 3 ]);

        if (isRaspberryPi){
            _servos[i-1] = new servo(chip, i);
            ctr->SetServo(_servos[i-1]);
        }

        gtk_fixed_put(GTK_FIXED (_pwmControlPage), ctr->get_main(), xOffset * 400, (i-1) * 75 - xOffset * 450);
        /*pwm_gtk_control * ctr8 = new pwm_gtk_control("8", 8, 0, 120);
        gtk_fixed_put(GTK_FIXED (_pwmControlPage), ctr8->get_main(), 0, 0);
        */
    }

}
