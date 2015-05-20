#include "../include/gtkAllServo.h"
#include "servo.h"


GtkWidget * gtkAllServo::get_main()
{
    return this->frame;
}

void gtkAllServo::btnOnClick(GtkWidget *wid, gpointer user_data)
{
    gtkAllServo * obj = (gtkAllServo * )user_data;

    if (obj->hasServos == false) {
        printf("has no servos\r\n");
        return;
    }

    char* leg1txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg1);
    char* leg2txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg2);
    char* leg3txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg3);
    char* leg4txt = gtk_entry_get_text((GtkEntry*)obj->txtLeg4);

    std::string g = "";
    g.append(leg1txt);
    g.append(leg2txt);
    g.append(leg3txt);
    g.append(leg4txt);

    float t= obj->ExecutePosition(g.c_str(), obj);

}

float gtkAllServo::ExecutePosition(char * data12, gtkAllServo * obj){
    int min = 0;
    int max = 0;
    double d = 0.0;

    for (int i = 0; i < srvQuantity; i++){
        char cr = data12[i];


        switch (cr){
            case 'x':
                printf("x");
                //skip
            break;
            case '1':
                printf("1");
                min = obj->_servoParams[i*3 + 1];
                printf("set d%\r\n", min);
                d = (float)min / 100;
                obj->_servos[i]->set_angle(d);

            break;
            case '2':
                printf("2");
                max = obj->_servoParams[i*3 + 2];
                d = (float)max / 100;
                printf("set d%\r\n", max);
                obj->_servos[i]->set_angle(d);
            break;

            default:
                return 0.0;
            break;
        }
    }
    printf("\r\n");
    return 8.8;
}

void gtkAllServo::SetServos(servo * servoMotor[])
{
    for (int i = 0; i < srvQuantity; i++) _servos[i] = servoMotor[i];
    hasServos = true;
    //pwm_gtk_control::btnOnClick(btnON, this);
    //delay(50);
}

gtkAllServo::gtkAllServo(char * title, servo * data[], int * params)
{
    hasServos = false;
    for (int i = 0; i < srvQuantity; i++) _servos[i] = data[i];
    hasServos = true;

    _servoParams = params;

    frame = gtk_frame_new(title);
    fixed = gtk_fixed_new();

    gtk_container_set_border_width(GTK_CONTAINER (fixed), 2);
    gtk_container_add(GTK_CONTAINER (frame), fixed);

    txtLeg1 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("xxx", 3));
    //g_signal_connect (minTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg1, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg1, 10, 10);


    txtLeg2 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("xxx", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg2, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg2, 55, 10);

    txtLeg3 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("xxx", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg3, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg3, 100, 10);

    txtLeg4 = gtk_entry_new_with_buffer(gtk_entry_buffer_new("xxx", 3));
    //g_signal_connect (maxTxt, "changed", G_CALLBACK (pwm_gtk_control::entry_changed), this);
    gtk_widget_set_usize(txtLeg4, 40, 25);
    gtk_fixed_put(GTK_FIXED (fixed), txtLeg4, 145, 10);


    // button on/off
    btnON = gtk_button_new_with_label("Turn");
    g_signal_connect (btnON, "clicked", G_CALLBACK (gtkAllServo::btnOnClick), this);
    gtk_widget_set_usize(btnON, 50, 30);
    gtk_fixed_put(GTK_FIXED (fixed), btnON, 190, 10);

}


