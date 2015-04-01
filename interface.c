#include "interface.h"
#define UTF8(string) g_locale_to_utf8(string, -1, NULL, NULL, NULL)

void OnQuitter(GtkWidget* widget, gpointer data);
void OnAbout(GtkWidget* widget, gpointer data);
void OnRadio(GtkWidget* widget, gpointer data);
void OnTearoff(GtkWidget* widget, gpointer data);
void OnCheck(GtkWidget* widget, gpointer data);
void creer_file_selection();
void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);
GtkWidget* CreateMenu(GtkWidget* widget);
GtkWidget* Create_toolbar();

static GtkWidget *pRadioLabel;
static GtkWidget *pCheckLabel;
static GtkWidget *pTearoffLabel;

int main(int argc, char *argv)
{
	GtkWidget *pWindow;
	GtkWidget *pMenuBar;
	GtkWidget *pToolBar;
	GtkWidget *pVBox;
	GtkWidget *pVBox2;
	gchar *sTempLabel;	
	gtk_init(&argc, &argv);
	 
	     // Création de la fenêtre 
	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(pWindow), "Apéro");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 280);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	    // Création de la GtkVBox 
	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	    /**** Création du menu ****/
	pMenuBar = CreateMenu(pWindow);
		//Creation de la Toolbar
	pToolBar = Create_toolbar();
	
/* Creation de la deuxieme GtkVBox (pour les labels) */
  pVBox2 = gtk_vbox_new(FALSE, 0);
		 
  pRadioLabel = gtk_label_new("Radio 1 est actif");
	gtk_box_pack_start(GTK_BOX(pVBox2), pRadioLabel, TRUE, TRUE, 0);
					  
	sTempLabel = g_locale_to_utf8("Check est décoché", -1, NULL, NULL, NULL);
	pCheckLabel = gtk_label_new(sTempLabel);
	g_free(sTempLabel);
	gtk_box_pack_start(GTK_BOX(pVBox2), pCheckLabel, TRUE, TRUE, 0);
	
	sTempLabel = g_locale_to_utf8("Menu attaché", -1, NULL, NULL, NULL);
	pTearoffLabel = gtk_label_new(sTempLabel);
	g_free(sTempLabel);
	gtk_box_pack_start(GTK_BOX(pVBox2), pTearoffLabel, TRUE, TRUE, 0);
																				

	  /* Ajout du menu a la fenêtre */
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
	  /* Ajout du toolbar a la fenetre */
	gtk_box_pack_start(GTK_BOX(pVBox), pToolBar, FALSE, FALSE, 0);
		/* Ajout des labels a la fenetre */
	gtk_box_pack_start(GTK_BOX(pVBox), pVBox2, TRUE, TRUE, 0);
																												 
	gtk_widget_show_all(pWindow);
																																		  
	 gtk_main();
																																		 
	 return EXIT_SUCCESS;
}

void OnRadio(GtkWidget* widget, gpointer data)
{
const gchar *sRadioName;
gchar *sLabel;
							 
  /* Récupérer le label du bouton radio active */
  sRadioName = gtk_label_get_label(GTK_LABEL(GTK_BIN(widget)->child));

  sLabel = g_strdup_printf("%s est actif",sRadioName);
	gtk_label_set_label(GTK_LABEL(pRadioLabel), sLabel);
	g_free(sLabel);
}

void OnCheck(GtkWidget* widget, gpointer data)
{
 gboolean bCoche;
 gchar *sLabel;
 gchar *sLabelUtf8;
									 
  /* Savoir si le GtkCheckMenuItem est coche ou non */
  bCoche = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget));
													  
  if(bCoche)
  sLabel = g_strdup("Check est coché");
  else
  sLabel = g_strdup("Check est décoché");
																																		 
  sLabelUtf8 = g_locale_to_utf8(sLabel, -1, NULL, NULL, NULL);
																																					  
  gtk_label_set_label(GTK_LABEL(pCheckLabel), sLabelUtf8);
  g_free(sLabel);
	g_free(sLabelUtf8);
}

void OnTearoff(GtkWidget* widget, gpointer data)
{
	gboolean bDetache;
	gchar *sLabel;
	gchar *sLabelUtf8;
										 
	/* Savoir si le menu est détaché ou non */
	bDetache = gtk_menu_get_tearoff_state(GTK_MENU(data));
															 
	if(bDetache)
	sLabel = g_strdup("Menu détaché");
	else
	sLabel = g_strdup("Menu attaché");
																																			  
	sLabelUtf8 = g_locale_to_utf8(sLabel, -1, NULL, NULL, NULL);
	
	gtk_label_set_label(GTK_LABEL(pTearoffLabel), sLabelUtf8);
	g_free(sLabel);
	g_free(sLabelUtf8);
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
GtkWidget *pQuestion;
						 
	pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
		GTK_DIALOG_MODAL,
		GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_YES_NO,
		"Voulez vous vraiment\n"
		"quitter le programme?");
		
		switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
		{
			case GTK_RESPONSE_YES:
					gtk_main_quit();
					break;
			case GTK_RESPONSE_NONE:
			case GTK_RESPONSE_NO:
					gtk_widget_destroy(pQuestion);
					break;
		}
}

void OnAbout(GtkWidget* widget, gpointer data)
{
	GtkWidget *pAbout;
						 
	pAbout = gtk_message_dialog_new(GTK_WINDOW(data),
			GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO,
			GTK_BUTTONS_OK,
			"Programme realise par Les Pringles\n"
			"Pour plus d'information:\n"
			"http://gtk.developpez.com");
								  
	gtk_dialog_run(GTK_DIALOG(pAbout));
											 
	gtk_widget_destroy(pAbout);
}

GtkWidget* Create_toolbar()
{
	GtkWidget *pToolbar = NULL;

	pToolbar = gtk_toolbar_new();

	/* Creation a partir de stock */
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_REFRESH,
		"Refresh",
		NULL,
		NULL,
		NULL,
		-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_CLEAR,
		"Clear",
		NULL,
		NULL,
		NULL,
		-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_CONVERT,
		"Convert",
		NULL,
		NULL,
		NULL,
		-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_ZOOM_FIT,
		"Zoom",
		NULL,
		NULL,
		NULL,
		-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_ZOOM_IN,
		"Zoom In",
		NULL,
		NULL,
		NULL,
		-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_ZOOM_OUT,
		"Zoom Out",
		NULL,
		NULL,
		NULL,
		-1);

	gtk_toolbar_insert_stock(GTK_TOOLBAR(pToolbar),
		GTK_STOCK_QUIT,
		"Fermer",
		NULL,
		G_CALLBACK(gtk_main_quit),
		NULL,
		-1);

		/* Modification de la taille des icones*/
//		gtk_toolbar_set_icon_size(GTK_TOOLBAR(pToolbar),GTK_ICON_SIZE_BUTTON);


		/* Affichage uniquement des icones*/
		gtk_toolbar_set_style(GTK_TOOLBAR(pToolbar),GTK_TOOLBAR_ICONS);
	
	return pToolbar;
}

GtkWidget* CreateMenu(GtkWidget* pWindow)
{
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pMenuBar;
	GSList *pList;
	GSList *pList2;
	GSList *pListC;
	char *color[] = {
					"DARK BLUE",
					"DARK GREEN",
					"DARK CYAN",
					"DARK RED",
					"OCHER",
					"LIGHT GREY",
					"GREY",
					"BLUE",
					"GREEN",
					"CYAN",
					"RED",
					"MAGENTA",
					"YELLOW",
					"WHITE"
	};

	/**** Création du menu ****/
																		  
	    /* ETAPE 1 */
	pMenuBar = gtk_menu_bar_new();
	    /** Premier sous-menu **/
	    /* ETAPE 2 */
	pMenu = gtk_menu_new();
			/* ETAPE 3 */

	    /* GtkTearoffMenuItem */
	pMenuItem = gtk_tearoff_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	g_signal_connect(G_OBJECT(pMenuItem),"activate",G_CALLBACK(OnTearoff),(gpointer)pMenu);
							 
		   /* GtkImageMenuItem */
	pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
  //fonction new sdl screen

	pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(creer_file_selection), NULL);								
	//ouvrir un fichier

	pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
  g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(creer_file_selection), NULL);
	//fonction pour save image a l'endroit choisi

	pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE,NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	//fermer l'image/widget sdl
																											 
	    /* GtkSeparatorItem */
  pMenuItem = gtk_separator_menu_item_new();
  gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

			/* GtkRadioMenuItem */
  pMenuItem = gtk_radio_menu_item_new_with_label(NULL, "Radio 1");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	    /* Il est inutile ici d'utiliser le signal "toggled" */
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);
										 
	pMenuItem = gtk_radio_menu_item_new_with_label(pList, "Radio 2");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem) ,"activate", G_CALLBACK(OnRadio), NULL);
																	  
	pMenuItem = gtk_radio_menu_item_new_with_label(pList, "Radio 3");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem) ,"activate", G_CALLBACK(OnRadio), NULL);
																									 
	     /* GtkSeparatorItem */
	pMenuItem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
																																  
	    /* GtkCheckMenuItem */
	pMenuItem = gtk_check_menu_item_new_with_label("Check");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	g_signal_connect(G_OBJECT(pMenuItem),"toggled",G_CALLBACK(OnCheck),(gpointer)pMenu);

		/* GtkSeparatorItem */
  pMenuItem = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
		 
	pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

    /* ETAPE 4 */
  pMenuItem = gtk_menu_item_new_with_label("File");
	  /* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	  /* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/*  Deuxieme sous-menu*/
		/* ETAPE 2*/
	pMenu = gtk_menu_new();
		/* ETAPE 3*/   //Menu des fonction utilise pour draw ex: dessiner un carre ou un cercle
	pMenuItem = gtk_radio_menu_item_new_with_label(NULL, "Rectangle");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList2 = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);

	pMenuItem = gtk_radio_menu_item_new_with_label(pList2, "Filled Rectangle");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList2 = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);

	pMenuItem = gtk_radio_menu_item_new_with_label(pList2, "Circle");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList2 = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);

	pMenuItem = gtk_radio_menu_item_new_with_label(pList2, "Disc");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList2 = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);

	pMenuItem = gtk_radio_menu_item_new_with_label(pList2, "Line");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pList2 = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);
		/* ETAPE 4*/
	pMenuItem = gtk_menu_item_new_with_label("Tools");
		/* ETAPE 5*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
		/* ETAPE 6*/
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Troisieme sous-menu **/
		/* ETAPE 2*/
	pMenu = gtk_menu_new();
		/* ETAPE 3*/
	pMenuItem = gtk_radio_menu_item_new_with_label(NULL, "BLACK");
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pListC = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);

	for(int i = 0; i < 14 ; i++)
	{
	pMenuItem = gtk_radio_menu_item_new_with_label(pListC, color[i]);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	pListC = gtk_radio_menu_item_get_group(GTK_RADIO_MENU_ITEM(pMenuItem));
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnRadio), NULL);
	}
		/* ETAPE 4*/
	pMenuItem = gtk_menu_item_new_with_label("Color");
		/* ETAPE 5*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
		/* ETAPE 6*/
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	/** Quatrieme sous-menu **/
	  /* ETAPE 2 */
	pMenu = gtk_menu_new();
	  /* ETAPE 3 */
	pMenuItem = gtk_menu_item_new_with_label("A propos de...");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnAbout), (GtkWidget*) pWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	  /* ETAPE 4 */
	pMenuItem = gtk_menu_item_new_with_label("?");
	  /* ETAPE 5 */
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
	  /* ETAPE 6 */
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	return pMenuBar;
}

void creer_file_selection()
{
	GtkWidget *selection;
	
	selection = gtk_file_selection_new( g_locale_to_utf8( "Selectionnez un fichier", -1, NULL, NULL, NULL));
	gtk_widget_show(selection);

	gtk_window_set_modal(GTK_WINDOW(selection), TRUE);

	g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(selection)->ok_button), "clicked", G_CALLBACK(recuperer_chemin), selection);

	g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(selection)->cancel_button), "clicked", G_CALLBACK(gtk_widget_destroy), selection);
}

void recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection)
{
    const gchar* chemin;
    GtkWidget *dialog;
    chemin = gtk_file_selection_get_filename(GTK_FILE_SELECTION (file_selection) );
     
    dialog = gtk_message_dialog_new(GTK_WINDOW(file_selection),
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_INFO,
    GTK_BUTTONS_OK,
    "Vous avez choisi :\n%s", chemin);
     
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    gtk_widget_destroy(file_selection);
}
