#ifndef REWARDVIEW_H
#define REWARDVIEW_H

#include <gtk/gtk.h>
#include "Reward.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class RewardView
{
    public:
        RewardView(Reward * reward);

        static void btnStartClick(GtkWidget *wid, gpointer user_data);
        static void btnSetParamsClick(GtkWidget *wid, gpointer user_data);
        GtkWidget * get_main();
        void build_gui();
        Reward * Model;

        GtkWidget * DurationEntry;
        GtkWidget * IntervalEntry;
        GtkWidget * ThresholdEntry;
    protected:
    private:
        bool hasMPU;
        GtkWidget * frame;
        GtkWidget * fixed;
        GtkWidget * OutputLabel;

        GtkWidget * StartButton;
        GtkWidget * SetParamsButton;
};

#endif // REWARDVIEW_H
