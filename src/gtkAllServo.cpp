#include "../include/gtkAllServo.h"
#include "servo.h"


GtkWidget * gtkAllServo::get_main()
{
    return this->frame;
}

void gtkAllServo::btnTurnClick(GtkWidget *wid, gpointer user_data)
{
    gtkAllServo * obj = (gtkAllServo * )user_data;

    char* leg1txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg1);
    char* leg2txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg2);
    char* leg3txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg3);
    char* leg4txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg4);

    std::string g = "";
    g.append(leg1txt);
    g.append(leg2txt);
    g.append(leg3txt);
    g.append(leg4txt);

    obj->ServoModel->ExecutePosition(g.c_str());
}

gtkAllServo::gtkAllServo(char * title, AllServoModel * servoModel)
{
    ServoModel = servoModel;

    frame = gtk_frame_new(title);
    fixed = gtk_fixed_new();

    gtk_container_set_border_width(GTK_CONTAINER (fixed), 2);
    gtk_container_add(GTK_CONTAINER (frame), fixed);

    txtLeg1 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("010", 3));
    //g_signal_connect (minTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg1, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg1, 10, 10);

    txtLeg2 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("101", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg2, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg2, 55, 10);

    txtLeg3 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("010", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg3, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg3, 100, 10);

    txtLeg4 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("101", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg4, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg4, 145, 10);

    // button on/off
    btnON = gtk_button_new_with_label("Turn");
    g_signal_connect (btnON, "clicked", G_CALLBACK (gtkAllServo::btnTurnClick), this);
    gtk_widget_set_usize(btnON, 50, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btnON, 190, 10);

}


