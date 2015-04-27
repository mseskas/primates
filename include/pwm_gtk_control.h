#ifndef PWM_GTK_CONTROL_H
#define PWM_GTK_CONTROL_H

#include <gtk/gtk.h>

#include "pwm_chip.h"
#include "servo.h"

#include <sys/utsname.h>

class pwm_gtk_control
{
    public:
        pwm_gtk_control(char * title, int pinNo);

        GtkWidget * get_main();

        static void btn_turn_click(GtkWidget *wid, gpointer user_data);
        static void scale_value_changed(GtkWidget *wid, gpointer user_data);
        static void entry_changed(GtkWidget *wid, gpointer user_data);
        static void btn_off_click(GtkWidget *wid, gpointer user_data);

    protected:
    private:


        GtkWidget * frame;
        GtkWidget * fixed;

        GtkWidget * scale;
        GtkWidget * btn_turn;
        GtkWidget * btn_off;
        GtkWidget * minTxt;
        GtkWidget * maxTxt;
        int is_entry_changed;

        int _servoPinNo;

        servo * ser;
        pwm_chip * chip;
};

#endif // PWM_GTK_CONTROL_H
