#include "gui_main.h"

gui_main::gui_main(AllServoModel * allServoModel, Reward * rewardModel)
{
    ServosModel = allServoModel;
    RewardModel = rewardModel;
    srvQuantity = allServoModel->srvQuantity;

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

    _pwmControlPage = gtk_fixed_new();
    gtk_widget_set_usize(_pwmControlPage, 900, 450);

    LoadServoControls(_pwmControlPage);

    GtkWidget * noteBook = gtk_notebook_new ();

// second page initialization

    _positionPage = gtk_fixed_new();
    gtk_widget_set_usize(_positionPage, 900, 450);

    gtkAllServo * all = new gtkAllServo("Start", ServosModel);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 0);

    all = new gtkAllServo("2nd", ServosModel);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 60);

    all = new gtkAllServo("3nd", ServosModel);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 120);

    all = new gtkAllServo("4nd", ServosModel);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 180);

    all = new gtkAllServo("5nd", ServosModel);
    gtk_fixed_put(GTK_FIXED (_positionPage), all->get_main(), 0, 240);

    RewardView * view = new RewardView(RewardModel);


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
    for (int i = 1; i < srvQuantity + 1; i++){
        int xOffset = (i-1) / 6;
        PwmViews[i-1] = new pwm_gtk_control(to_string(i).c_str(), ServosModel->ServoParams[(i - 1) * 3 + 1], ServosModel->ServoParams[(i - 1) * 3 + 2], ServosModel->ServoParams[(i - 1) * 3]);
        PwmViews[i-1]->SetServo(ServosModel->Servos[i-1]);
        gtk_fixed_put(GTK_FIXED (_pwmControlPage), PwmViews[i-1]->get_main(), xOffset * 400, (i-1) * 75 - xOffset * 450);
    }
    // add all pwm controls
    AllOffButton = gtk_button_new_with_label("All OFF");
    g_signal_connect (AllOffButton, "clicked", G_CALLBACK (gui_main::btnAllOffClick), this);
    gtk_widget_set_usize(AllOffButton, 100, 40);
    gtk_fixed_put(GTK_FIXED (_pwmControlPage), AllOffButton, 785, 20);

    AllOnButton = gtk_button_new_with_label("All ON");
    g_signal_connect (AllOnButton, "clicked", G_CALLBACK (gui_main::btnAllOnClick), this);
    gtk_widget_set_usize(AllOnButton, 100, 40);
    gtk_fixed_put(GTK_FIXED (_pwmControlPage), AllOnButton, 785, 65);
}

void gui_main::btnAllOnClick(GtkWidget *wid, gpointer user_data)
{
    gui_main * obj = (gui_main * )user_data;
    for (int i = 0; i < obj->srvQuantity; i++){
       //
       if (obj->PwmViews[i]->isON != true)
        obj->PwmViews[i]->btnOnClick(NULL, obj->PwmViews[i]);
    }
}

void gui_main::btnAllOffClick(GtkWidget *wid, gpointer user_data)
{
    gui_main * obj = (gui_main * )user_data;
    for (int i = 0; i < obj->srvQuantity; i++){
       //
       if (obj->PwmViews[i]->isON == true)
        obj->PwmViews[i]->btnReleaseClick(NULL, obj->PwmViews[i]);
    }
}


