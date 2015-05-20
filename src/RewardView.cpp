#include "RewardView.h"

GtkWidget * RewardView::get_main()
{
    return this->frame;
}

RewardView::RewardView(Reward * reward)
{
    hasMPU = false;
    if (reward != NULL) {
        _model = reward;
        hasMPU = true;
    }
    build_gui();
}

void RewardView::btnStartClick(GtkWidget *wid, gpointer user_data)
{
    RewardView * obj = (RewardView * )user_data;

    if (obj->hasMPU == true){
        cout << "btnStartClick - starting to measure" << endl;



    } else cout << "btnStartClick - no MPU" << endl;
}

void RewardView::btnSetParamsClick(GtkWidget *wid, gpointer user_data)
{
    RewardView * obj = (RewardView * )user_data;

    if (obj->hasMPU == true){
        cout << "btnSetParamsClick - setting parameters" << endl;



    } else cout << "btnSetParamsClick - no MPU" << endl;
}

void RewardView::build_gui(){
    frame = gtk_frame_new("Reward Operation");
    fixed = gtk_fixed_new();

    gtk_container_set_border_width(GTK_CONTAINER (fixed), 2);
    gtk_container_add(GTK_CONTAINER (frame), fixed);

    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Output"), 10, 10);

    OutputLabel = gtk_label_new("here will be data");
    gtk_fixed_put(GTK_FIXED (fixed), OutputLabel, 70, 10);

    StartButton = gtk_button_new_with_label("Start");
    g_signal_connect (StartButton, "clicked", G_CALLBACK (RewardView::btnStartClick), this);
    gtk_widget_set_usize(StartButton, 70, 45);
    gtk_fixed_put(GTK_FIXED (fixed), StartButton, 190, 0);


    int groupX = 80;
    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Duration"), 10, 40);
    DurationEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new("", 0));
    gtk_widget_set_usize(DurationEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), DurationEntry, groupX, 40);

    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Interval"), 10, 73);
    IntervalEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new("", 0));
    gtk_widget_set_usize(IntervalEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), IntervalEntry, groupX, 70);

    SetParamsButton = gtk_button_new_with_label("Set Parameters");
    g_signal_connect (SetParamsButton, "clicked", G_CALLBACK (RewardView::btnSetParamsClick), this);
    gtk_widget_set_usize(SetParamsButton, 125, 45);
    gtk_fixed_put(GTK_FIXED (fixed), SetParamsButton, groupX+55, 58);

    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Threshold"), 10, 105);
    ThresholdEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new("", 0));
    gtk_widget_set_usize(ThresholdEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), ThresholdEntry, groupX, 100);


//GtkWidget * OutputLabel;
//
//GtkWidget * DurationEntry;
//GtkWidget * IntervalEntry;
//GtkWidget * ThresholdEntry;
//
//GtkWidget * StartButton;
//GtkWidget * SetParamsButton;



}
