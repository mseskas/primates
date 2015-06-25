#ifndef WALKVIEW_H
#define WALKVIEW_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include "ServoModel.h"

class WalkView
{
    public:
        WalkView(ServoModel * model);
        GtkWidget * get_main();
        void build_gui();

        GtkWidget * StandButton;
        GtkWidget * SitButton;
        ServoModel * Model;

        GtkWidget * Zscale;

        static void btnStandClick(GtkWidget *wid, gpointer user_data);
        static void scale_Z_changed(GtkWidget *wid, gpointer user_data);
    private:
        GtkWidget * fixed;

        GtkWidget * StartButton;
        GtkWidget * SetParamsButton;



};

#endif // WALKVIEW_H
