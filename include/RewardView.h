#ifndef REWARDVIEW_H
#define REWARDVIEW_H

#include <gtk/gtk.h>
#include "Reward.h"

class RewardView
{
    public:
        RewardView(Reward * reward);

        static void btnStartClick(GtkWidget *wid, gpointer user_data);
        static void btnSetParamsClick(GtkWidget *wid, gpointer user_data);


        GtkWidget * get_main();
        void build_gui();

    protected:
    private:
        bool hasMPU;
        GtkWidget * frame;
        GtkWidget * fixed;


        GtkWidget * OutputLabel;

        GtkWidget * DurationEntry;
        GtkWidget * IntervalEntry;
        GtkWidget * ThresholdEntry;

        GtkWidget * StartButton;
        GtkWidget * SetParamsButton;







        Reward * _model;
};

#endif // REWARDVIEW_H
