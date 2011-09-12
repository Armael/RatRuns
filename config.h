/*
*   Fichier de configuration de RatRuns
*/

/* Buttons :
    Left_Click
    Middle_Click
    Right_Click
    Top_Roll
    Bottom_Roll
*/

/* Les dimensions de la fenêtre captant les évènements */
static int window_width = 300;
static int window_height = 300;

static Binding bindings[] = { { /* The button to press */ Left_Click,
                                /* The command to launch */ "xterm" }
                            };
