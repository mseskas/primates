
#include "../include/pwm_gtk_control.h"

#include "pwm_chip.h"
#include "servo.h"

/*
    Static fields must be declared in header file
    and initialized in source file
*/

GtkWidget * pwm_gtk_control::get_main()
{
    return this->frame;
}

void pwm_gtk_control::btnOnClick(GtkWidget *wid, gpointer user_data)
{
    pwm_gtk_control * obj = (pwm_gtk_control * )user_data;

    if (obj->isON == true) {
        obj->isON = false;
        gtk_button_set_label((GtkButton*)obj->btnON, "OFF");
        return;
    }
    else {
        obj->isON = true;
        gtk_button_set_label((GtkButton*)obj->btnON, "ON");
    }

    if (obj->ser == NULL) {
        printf("null\r\n");
        return;
    }
    // turn motor
    gdouble val = gtk_range_get_value(GTK_RANGE(obj->scale));
    double d = (double)val;
    d = d / 100;
    obj->ser->set_angle(d);
    printf("btnOn turn to %f\n\r", d);
}

void pwm_gtk_control::scale_value_changed(GtkWidget *wid, gpointer user_data)
{
    pwm_gtk_control * obj = (pwm_gtk_control * )user_data;
    if (obj->isON == false) {
        printf("Off\r\n");
        return;
    }
    if (obj->ser == NULL) {
        printf("null\r\n");
        return;
    }




    gdouble val = gtk_range_get_value(GTK_RANGE(obj->scale));
    double d = (double)val;
    d = d / 100;
    obj->ser->set_angle(d);


    //servo * ser = new servo(obj->chip, 4);
    //ser->set_angle(d);
   // ser = new servo(obj->chip, 3);
    //ser->set_angle(d);

    printf("Scale turn to %f\n\r", d);
}

void pwm_gtk_control::entry_changed(GtkWidget *wid, gpointer user_data)
{
    pwm_gtk_control * obj = (pwm_gtk_control * )user_data;

    obj->is_entry_changed = 1;
    obj->isON = false;
    gtk_button_set_label((GtkButton*)obj->btnON, "OFF");
    gtk_button_set_label((GtkButton*)obj->btnRelease, "Reset");

    printf("min max changed\r\n");
}

void pwm_gtk_control::btnReleaseClick(GtkWidget *wid, gpointer user_data)
{
    pwm_gtk_control * obj = (pwm_gtk_control * )user_data;

    if (obj->is_entry_changed == 1) {
        char* minText = gtk_entry_get_text((GtkEntry*)obj->minTxt);
        char* maxText = gtk_entry_get_text((GtkEntry*)obj->maxTxt);

        int minInt = std::stoi (minText);
        int maxInt = std::stoi (maxText);

        gtk_range_set_range((GtkRange*)obj->scale, minInt, maxInt);
        obj->is_entry_changed = 0;
        obj->minValue = minInt;
        obj->maxValue = maxInt;
        gtk_button_set_label((GtkButton*)obj->btnRelease, "Release");
        printf("Reset control\n\r");
        return;
    }

    if (obj->ser == NULL) {
        printf("null\r\n");
        return;
    }

    obj->ser->Reset();
    printf("Release pwm\n\r");
}

void pwm_gtk_control::SetServo(servo * servoMotor)
{
    ser = servoMotor;
}

pwm_gtk_control::pwm_gtk_control(char * title, int minVal, int maxVal, int startVal)
{
    is_entry_changed = 0;
    ser = NULL;
    scale = NULL;
    isON = false;

    minValue = minVal;
    maxValue = maxVal;
    startValue = startVal;//(minValue + maxValue) / 2;

    std::string fullTitle = "PWM - ";
    fullTitle.append(title);
    fullTitle.append(", control percentage");

    frame = gtk_frame_new(fullTitle.c_str());
    fixed = gtk_fixed_new();

    gtk_container_set_border_width(GTK_CONTAINER (fixed), 2);
    gtk_container_add(GTK_CONTAINER (frame), fixed);

    // min text box
    minTxt = gtk_entry_new_with_buffer(gtk_entry_buffer_new(to_string(minVal).c_str(), 7));
    g_signal_connect (minTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(minTxt, 35, 25);
    gtk_fixed_put(GTK_FIXED (fixed), minTxt, 10, 10);

    // scale
    scale = gtk_hscale_new_with_range(minVal, maxVal, 1);
    gtk_range_set_value(GTK_RANGE(scale), startValue);

    gtk_widget_set_usize(scale, 150, 45);
    g_signal_connect (scale, "value-changed", G_CALLBACK (pwm_gtk_control::scale_value_changed), this);
    gtk_fixed_put(GTK_FIXED (fixed), scale, 50, 0);

    // max text box
    maxTxt = gtk_entry_new_with_buffer(gtk_entry_buffer_new(to_string(maxVal).c_str(), 7));
    g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(maxTxt, 35, 25);
    gtk_fixed_put(GTK_FIXED (fixed), maxTxt, 205, 10);

    // button on/off
    btnON = gtk_button_new_with_label("OFF");
    g_signal_connect (btnON, "clicked", G_CALLBACK (pwm_gtk_control::btnOnClick), this);
    gtk_widget_set_usize(btnON, 50, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btnON, 245, 10);

    // button release/reset
    btnRelease = gtk_button_new_with_label("Release");
    g_signal_connect (btnRelease, "clicked", G_CALLBACK (pwm_gtk_control::btnReleaseClick), this);
    gtk_widget_set_usize(btnRelease, 70, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btnRelease, 300, 10);

    pwm_gtk_control::btnOnClick(btnON, this);
    delay(50);
}


