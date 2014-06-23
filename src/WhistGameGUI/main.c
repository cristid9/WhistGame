#include <stdio.h>
#include <stdlib.h>
#include "gui.h"

struct Input {
    GtkWidget *name;
    GtkWidget *robotsNumber;
    GtkWidget *gameType;
};

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

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(window, 230, 200);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Whist Game");
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show(fixed);

    labelName = gtk_label_new("Name ");
    gtk_fixed_put(GTK_FIXED(fixed), labelName, 10, 15);
    gtk_widget_show(labelName);

    name = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(name), 10);
    gtk_fixed_put(GTK_FIXED(fixed), name, 50, 10);
    gtk_widget_show(name);

    labelType = gtk_label_new("Choose the game type");
    gtk_fixed_put(GTK_FIXED(fixed), labelType, 10, 40);
    gtk_widget_show(labelType);

    radio1 = gtk_radio_button_new_with_label(NULL, "11-88-11");
    radio8 = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(radio1), "88-11-88");
    gtk_widget_show(radio1);
    gtk_widget_show(radio8);
    vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), radio8);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), radio1);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 10, 60);
    gtk_widget_show(vbox);

    labelNumber = gtk_label_new("Choose the robots number");
    gtk_fixed_put(GTK_FIXED(fixed), labelNumber, 10, 110);
    gtk_widget_show(labelNumber);

    number = GTK_ADJUSTMENT(gtk_adjustment_new(2.0, 2.0, 5.0, 1.0, 0.0, 0.0));
    spinNumber = gtk_spin_button_new(number, 1.0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), spinNumber, 10, 130);
    gtk_widget_show(spinNumber);

    input->name = name;
    input->robotsNumber = spinNumber;
    input->gameType = radio1;

    button = gtk_button_new_with_label("Start");
    gtk_fixed_put(GTK_FIXED(fixed), button, 100, 160);
    g_signal_connect(G_OBJECT(button), "clicked", 
                     G_CALLBACK(WhistGameLogic), input);
    gtk_widget_show(button);
    
    gtk_widget_show(window);

    gtk_main();

    free(input);
    
    return 0;
}

