#include "RewardView.h"

GtkWidget * RewardView::get_main()
{
    return this->frame;
}

RewardView::RewardView(Reward * reward)
{
    hasMPU = false;
    if (reward != NULL) {
        Model = reward;
        hasMPU = true;
    }
    build_gui();
}

void RewardView::btnStartClick(GtkWidget *wid, gpointer user_data)
{
    RewardView * obj = (RewardView * )user_data;

    if (obj->hasMPU == true){
        cout << "btnStartClick - starting to measure" << endl;

        double result = -0.02;//obj->Model->GetReward();

        string output = to_string(result);

        if (result > 0)output.append(" - BACKWARD");
        else output.append(" - FORWARD");

        gtk_label_set_text((GtkLabel*)obj->OutputLabel, output.c_str() );

    } else cout << "btnStartClick - no MPU" << endl;
}

void RewardView::btnSetParamsClick(GtkWidget *wid, gpointer user_data)
{
    RewardView * obj = (RewardView * )user_data;

    if (obj->hasMPU == true){
        cout << "btnSetParamsClick - setting parameters" << endl;
        char* txt1 = gtk_entry_get_text((GtkEntry*)obj->DurationEntry);
        char* txt2 = gtk_entry_get_text((GtkEntry*)obj->IntervalEntry);
        char* txt3 = gtk_entry_get_text((GtkEntry*)obj->ThresholdEntry);
        int duration = stoi (txt1);
        float interval = stof (txt2);
        float threshold = stof (txt3);

        obj->Model->DurationMs = duration;
        obj->Model->IntervalMs = interval;
        obj->Model->Threshold = threshold;

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
    gtk_widget_set_usize(StartButton, 120, 45);
    gtk_fixed_put(GTK_FIXED (fixed), StartButton, 140, 40);

    string duration = "none";
    string interval = "none";
    string threshold = "none";

    if (hasMPU == true){
       duration = to_string(Model->DurationMs);
       interval = to_string(Model->IntervalMs);
       threshold = to_string(Model->Threshold);
    }

    int groupX = 80;
    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Duration"), 10, 40);
    DurationEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new(duration.c_str(), duration.length()));
    gtk_widget_set_usize(DurationEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), DurationEntry, groupX, 40);

    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Interval"), 10, 73);
    IntervalEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new(interval.c_str(), interval.length()));
    gtk_widget_set_usize(IntervalEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), IntervalEntry, groupX, 70);

    SetParamsButton = gtk_button_new_with_label("Set Parameters");
    g_signal_connect (SetParamsButton, "clicked", G_CALLBACK (RewardView::btnSetParamsClick), this);
    gtk_widget_set_usize(SetParamsButton, 125, 45);
    gtk_fixed_put(GTK_FIXED (fixed), SetParamsButton, groupX+55, 85);

    gtk_fixed_put(GTK_FIXED (fixed), gtk_label_new("Threshold"), 10, 105);
    ThresholdEntry = gtk_entry_new_with_buffer(gtk_entry_buffer_new(threshold.c_str(), threshold.length()));
    gtk_widget_set_usize(ThresholdEntry, 50, 25);
    gtk_fixed_put(GTK_FIXED (fixed), ThresholdEntry, groupX, 100);
}
