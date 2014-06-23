#include <stdio.h>
#include <stdlib.h>

#include "gui.h"

int WhistGameLogic(GtkWidget *button, struct Input *input)
{
    const char *playerName = gtk_entry_get_text(GTK_ENTRY(input->name));
    int playerNumber = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON
                                                        (input->robotsNumber));
    int gameType;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(input->gameType)))
        gameType = 1;
    else
        gameType = 8;

    return 0;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *fixed;
    GtkWidget *labelName, *labelType, *labelNumber;
    GtkWidget *name;
    GtkWidget *vbox;
    GtkWidget *radio1, *radio8;
    GtkWidget *spinNumber;
    GtkAdjustment *number;
    struct Input *input = malloc(sizeof(struct Input));

    gtk_init(&argc, &argv);

    init(&window, &fixed, "Whist Game", 230, 200);
    playerName(window, fixed, &labelName, &name);
    gameType(window, fixed, &labelType, &radio1, &radio8, &vbox);
    noOfBots(window, fixed, &labelNumber, &spinNumber, &number);

    input->name = name;
    input->robotsNumber = spinNumber;
    input->gameType = radio1;

    button = gtk_button_new_with_label("Start");
    gtk_fixed_put(GTK_FIXED(fixed), button, 100, 160);
    g_signal_connect(G_OBJECT(button), "clicked", 
                     G_CALLBACK(WhistGameLogic), input);
    gtk_widget_show(button);

    gtk_main();

    free(input);
    
    return 0;
}

