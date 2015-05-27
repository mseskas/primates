#ifndef GTKALLSERVO_H
#define GTKALLSERVO_H

#include <gtk/gtk.h>

#include "ServoModel.h"

class gtkAllServo
{
    public:
        gtkAllServo(char * title, ServoModel * servoModel);
        GtkWidget * get_main();

        ServoModel * Servos;
        int srvQuantity;

        static void btnTurnClick(GtkWidget *wid, gpointer user_data);

    private:
        GtkWidget * frame;
        GtkWidget * fixed;

        GtkWidget * txtLeg1;
        GtkWidget * txtLeg2;
        GtkWidget * txtLeg3;
        GtkWidget * txtLeg4;

        GtkWidget * btnON;  //GtkButton

};

#endif // GTKALLSERVO_H
