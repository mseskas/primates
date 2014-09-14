
#include "../include/pwm_gtk_control.h"

#include "pwm_chip.h"
#include "servo.h"

/*
    Static fields must be declared in header file
    and initialized in source file
*/
int pwm_gtk_control::is_entry_changed = 0;
servo * pwm_gtk_control::ser = NULL;
pwm_chip * pwm_gtk_control::chip = NULL;
GtkWidget * pwm_gtk_control::scale = NULL;


GtkWidget * pwm_gtk_control::get_main()
{
    return this->frame;

}

void pwm_gtk_control::btn_turn_click(GtkWidget *wid, gpointer user_data)
{

    gdouble val = gtk_range_get_value(GTK_RANGE(scale));

    if (ser != NULL)
    {
        double d = (double)val;

        d = d / 100;
        printf("%f", d);
        ser->set_angle(d);

    }
    else printf("null");

    if (is_entry_changed == 1)
        printf("changed entry\n\r");
    else printf("button turn\n\r");

    is_entry_changed = 0;
}

void pwm_gtk_control::scale_value_changed(GtkWidget *wid, gpointer user_data)
{

    gdouble val = gtk_range_get_value(GTK_RANGE(scale));

    if (ser != NULL)
    {
        double d = (double)val;

        d = d / 100;
        printf("%f", d);
        ser->set_angle(d);

    }
    else printf("null");

    if (is_entry_changed == 1)
        printf("changed entry\n\r");
    else printf("button turn\n\r");

    printf("scale\n\r");

}

void pwm_gtk_control::entry_changed(GtkWidget *wid, gpointer user_data)
{
    is_entry_changed = 1;
    //printf("min max");
}

void pwm_gtk_control::btn_off_click(GtkWidget *wid, gpointer user_data)
{
    printf("turn off pwm\n\r");
    chip->reset();
}


pwm_gtk_control::pwm_gtk_control(char * title, int pinNo)
{
    int is_entry_changed = 0;
    frame = gtk_frame_new(title);
    fixed = gtk_fixed_new();

    chip = new pwm_chip(PWM_CHIP_ADDR);
    _servoPinNo = pinNo;
    ser = new servo(chip, _servoPinNo);

    gtk_container_set_border_width(GTK_CONTAINER (fixed), 5);
    gtk_container_add(GTK_CONTAINER (frame), fixed);

    // min text box
    minTxt = gtk_entry_new_with_buffer(gtk_entry_buffer_new("50", 7));
    g_signal_connect (minTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), NULL);
    gtk_widget_set_usize(minTxt, 25, 25);
    gtk_fixed_put(GTK_FIXED (fixed), minTxt, 10, 10);

    // scale
    scale = gtk_hscale_new_with_range(0, 150, 1);
    gtk_widget_set_usize(scale, 150, 45);
    g_signal_connect (scale, "value-changed", G_CALLBACK (pwm_gtk_control::scale_value_changed), NULL);
    gtk_fixed_put(GTK_FIXED (fixed), scale, 40, 0);

    // max text box
    maxTxt = gtk_entry_new_with_buffer(gtk_entry_buffer_new("150", 7));
    g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), NULL);
    gtk_widget_set_usize(maxTxt, 25, 25);
    gtk_fixed_put(GTK_FIXED (fixed), maxTxt, 195, 10);

    // button turn
    btn_turn = gtk_button_new_with_label("Turn");
    g_signal_connect (btn_turn, "clicked", G_CALLBACK (pwm_gtk_control::btn_turn_click), NULL);
    gtk_widget_set_usize(btn_turn, 50, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btn_turn, 225, 10);

    // button off
    btn_off = gtk_button_new_with_label("OFF");
    g_signal_connect (btn_off, "clicked", G_CALLBACK (pwm_gtk_control::btn_off_click), NULL);
    gtk_widget_set_usize(btn_off, 50, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btn_off, 280, 10);

}


