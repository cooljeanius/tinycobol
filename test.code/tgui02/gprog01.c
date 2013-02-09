/* 
 *  Copyright (C) 2008 Rildo Pragana, David Essex.
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this software; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 *  Boston, MA 02111-1307 USA
 */

#include <gtk/gtk.h>
#include <glib.h>

#include "wprog.h"

/* Declare the GTK call-back functions */
static void destroy(GtkWidget *widget, gpointer data);

/* Declare the function to open a dialog box displaying the message provided. */
gint display_dialog (void);

/* Declare the function to parse command line and call COBOL sub-program (function)  */
int call_sub_program(int ac, char *av[]);

/* Declare the C equivalent type for the COBOL sub-program */
extern int subp01(char*);

/* Declare the GTK Widgets */
GtkWidget *mwindow;

int main (int ac, char *av[])
{
 int r=0; 
 gint result;

 /* Declare the GTK Widgets */
 GtkWidget *mdialog;

 /* Initialize GTK */
 gtk_init (&ac, &av);

 /* Create the top window */
 mwindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

 /* Connect the main window's destroy handler */
 g_signal_connect(G_OBJECT(mwindow), "destroy", G_CALLBACK(destroy), NULL);
 
 /* Display the dialog */
 result = display_dialog(); 
 switch (result)
 {
   case GTK_RESPONSE_ACCEPT:
      r = call_sub_program(ac, av);
      break;
   default:
      /* Assume user cancelled and ignore */
      break;
 }

 /* Return and exit */
 return r;
}

/* Exit program when the window is closed */
static void destroy(GtkWidget *widget, gpointer data)
{
  gtk_main_quit();
}
  
/* Function to open a dialog box displaying the message provided. */
gint display_dialog () {

 GtkWidget *mdialog, *mlabel, *mcontent_area;
 gint result;
   
 /* Create the dialog widgets */
 /* mdialog = gtk_dialog_new_with_buttons (IDCH_DIALOG_CAPTION, */
 mdialog = gtk_dialog_new_with_buttons(IDCH_DIALOG_MSG,
                                       mwindow,
                                       GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                       GTK_STOCK_OK,
                                       GTK_RESPONSE_ACCEPT,
                                       GTK_STOCK_CANCEL,
                                       GTK_RESPONSE_REJECT,
                                       NULL);

 /* Get the dialog content area */
// mcontent_area = gtk_dialog_get_content_area (GTK_DIALOG (mdialog));
// mlabel = gtk_label_new(IDCH_DIALOG_MSG);
   
 /* Add the label, and show everything we've added to the dialog. */
// gtk_container_add(GTK_CONTAINER (mcontent_area), mlabel);

 /* Set dialog separator off */
 gtk_dialog_set_has_separator(mdialog, FALSE);

 /* Resize the border for the dialog */
 gtk_container_border_width (GTK_CONTAINER (mdialog), 60);

 result = gtk_dialog_run(GTK_DIALOG (mdialog));

 gtk_widget_destroy(mdialog);

 return result;
}

/* Parse command line and call COBOL sub-program (function)  */
int call_sub_program(int ac, char *av[])
{
 char s[256] = "";
 int r=0, i, len=0;

 for (i=0; i<ac; i++) {
   len = strlen(s);
   if (len < 256) {
     strcat(s, av[i]);
     strcat(s, " "); 
   }     
 }

 r = subp01(s);

 return r;
}

