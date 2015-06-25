#include "WalkView.h"

WalkView::WalkView(ServoModel * model)
{
    Model = model;
    build_gui();
}


GtkWidget * WalkView::get_main()
{
    return this->fixed;
}

void WalkView::btnStandClick(GtkWidget *wid, gpointer user_data)
{
    WalkView * obj = (WalkView * )user_data;
    float angle = obj->Model->ServoPositions[0] + 10;
    obj->Model->ServoPositions[0] = angle;
    obj->Model->SetSinglePosition(0, angle);
}

void WalkView::build_gui(){
    fixed = gtk_fixed_new();
    gtk_container_set_border_width(GTK_CONTAINER (fixed), 2);

    StandButton = gtk_button_new_with_label("Stand");
    g_signal_connect (StandButton, "clicked", G_CALLBACK (WalkView::btnStandClick), this);
    gtk_widget_set_usize(StandButton, 100, 40);
    gtk_fixed_put(GTK_FIXED (fixed), StandButton, 150, 20);

    SitButton = gtk_button_new_with_label("Sit");
    //g_signal_connect (SitButton, "clicked", G_CALLBACK (RewardView::btnStartClick), this);
    gtk_widget_set_usize(SitButton, 100, 40);
    gtk_fixed_put(GTK_FIXED (fixed), SitButton, 150, 60);


    GtkWidget * scale = gtk_hscale_new_with_range(0, 100, 1);
    gtk_range_set_value(GTK_RANGE(scale), 0);

    gtk_widget_set_usize(scale, 130, 45);
   // g_signal_connect (scale, "value-changed", G_CALLBACK (pwm_gtk_control::scale_value_changed), this);
    gtk_fixed_put(GTK_FIXED (fixed), scale, 10, 0);


}
