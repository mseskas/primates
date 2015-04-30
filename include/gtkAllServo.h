#include <gtk/gtk.h>
#include "servo.h"

class gtkAllServo
{
    public:
        gtkAllServo(char * title, servo * data[], int * params);
        GtkWidget * get_main();
        void SetServos(servo * servoMotor[]);
        static const int srvQuantity = 12;
        bool hasServos = false;
        servo * _servos[srvQuantity];

        static void btnOnClick(GtkWidget *wid, gpointer user_data);

        int * _servoParams;

        float ExecutePosition(char * data12,gtkAllServo * obj);

    private:
        GtkWidget * frame;
        GtkWidget * fixed;

        GtkWidget * txtLeg1;
        GtkWidget * txtLeg2;
        GtkWidget * txtLeg3;
        GtkWidget * txtLeg4;

        GtkWidget * btnON;  //GtkButton

};

