#include "../include/tower.h"
#include "../include/batiment.h"
#include "../include/headers.h"
#include "../include/batiment.h"
#include "../include/map.h"
#include "../include/node.h"
#include "../include/texture.h"


/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "Imac Tower Defense";

/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 800.;
static const float GL_VIEW_HEIGHT = 600.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Needed global variables */
bool help_needed = false;
bool r_pressed = false;
bool g_pressed = false;
bool b_pressed = false;
bool y_pressed = false;
int nb_red_tower = 0;
int nb_blue_tower = 0;
int nb_green_tower = 0;
int nb_yellow_tower = 0;




void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{ 
    SDL_Surface* surface_temp = SDL_SetVideoMode(   
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp) 
    {
        fprintf(
            stderr, 
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-GL_VIEW_WIDTH/2, GL_VIEW_WIDTH/2, -GL_VIEW_HEIGHT/2, GL_VIEW_HEIGHT/2);

}


void drawSquare(float x, float y) {

    glBegin(GL_TRIANGLE_FAN);
    if (r_pressed){
        glColor3ub(255, 0, 0);
    } else if ( g_pressed){
        glColor3ub(0, 255, 0);
    } else if (b_pressed){
        glColor3ub(0, 0, 255);
    } else if (y_pressed){
        glColor3ub(255, 255, 0);
    } else {
        glColor3ub(255, 255, 255);
    }
    glVertex2f( x+15, y-15);
    glVertex2f( x+15, y+15);
    glVertex2f( x-15, y+15);
    glVertex2f( x-15, y-15);
    glEnd();

}

void draw_help(GLuint* texture_help){
    if (NULL != texture_help){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_help);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(-370., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(-370., -270.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., -270.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of help button failed\n");
    }

}

void open_help(GLuint* texture_wdw){
    if (NULL != texture_wdw){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_wdw);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(400., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of help window failed\n");
    }
}


void draw_tower(GLuint* texture_tower, int x, int y){
    if (NULL != texture_tower){
        printf("ouaip\n");
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_tower);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-15, y-15.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+15., y-15.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+15., y+15.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-15., y+15.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of tower failed\n");
    }
}



int main(int argc, char const *argv[]) {
	char const *itd_map_name = "data/carte1.itd";
	char const *ppm_map_name = "images/carte1.ppm";


    float new_x = 0;
    float new_y = 0;

	vector<Node>* Tab_Node = new vector<Node>;
	int itd_ok = check_itd(itd_map_name, Tab_Node);

	if (itd_ok == 0){
		printf("Error while reading itd file, programm is over.\n");
		return 0;
	}

	cout << (*Tab_Node)[0].get_pos_x() << "\n";
	delete Tab_Node;
    unsigned int x_mouse = 0, y_mouse = 0;


	//verifier_ppm

	Tower newtower(4,5,ROCKET,8.0,2.0,3.0,6);
    printf("%f\n",newtower.get_power());

    //loadMap
    Map * newmap = new Map;
    load_check_Map(ppm_map_name,newmap);
    cout << newmap->get_width();
    delete(newmap);
    

    /* Initializing SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
  
    /* Openning a window */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Initializing the title of the window */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);





    /* MAP TEXTURE */
    char const *image_path = "images/carte03.png";
    GLuint texture_map_BG = createTexture(image_path);
    


    /* HELP BUTTON TEXTURE */
    char const *help_btn_path = "images/help_button.png";
    GLuint texture_help_button = createTexture(help_btn_path);
    


    /* HELP WINDOW TEXTURE*/
    char const *help_wdw_path = "images/help_window2.png";
    GLuint texture_help_wdw= createTexture(help_wdw_path);



    /* RED TOWER TEXTURE */
    char const *red_tower_path = "images/red_tower.png";
    GLuint texture_red_tower = createTexture(red_tower_path);

    /* GREEN TOWER TEXTURE */
    char const *green_tower_path = "images/green_tower.png";
    GLuint texture_green_tower = createTexture(green_tower_path);

    /* BLUE TOWER TEXTURE */
    char const *blue_tower_path = "images/blue_tower.png";
    GLuint texture_blue_tower = createTexture(blue_tower_path);

    /* YELLOW TOWER TEXTURE */
    char const *yellow_tower_path = "images/yellow_tower.png";
    GLuint texture_yellow_tower = createTexture(yellow_tower_path);




  
    /* Main loop */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture_map_BG);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
            glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(400., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
            glEnd();
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, 0);
        
        glDisable(GL_TEXTURE_2D);




        glPushMatrix();
            drawSquare(new_x, new_y);
        glPopMatrix();




       glPushMatrix();
            draw_help(&texture_help_button);
        glPopMatrix();



        if(help_needed){
            glPushMatrix();
                open_help(&texture_help_wdw);
            glPopMatrix();
        }



        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }

            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT) 
            {
                loop = 0;
                break;
            }
        
            if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                loop = 0; 
                break;
            }


            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == SDL_BUTTON_LEFT){
                        printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    } 

                    if ((e.button.x <=30) && (e.button.x <=30)) help_needed = true;

                    if(e.button.x>=730 && e.button.x<=770 && e.button.y>=30 && e.button.y<=70 && help_needed == true){
                        help_needed = false;
                    }





                    if(r_pressed){
                        Tower newtower(e.button.x, e.button.y, ROCKET, 8.0, 2.0, 3.0, 6);
                        printf("Red tower created\n");
                        draw_tower(&texture_red_tower, e.button.x, e.button.y);
                    }

                    if(g_pressed){
                        Tower newtower(e.button.x, e.button.y, LASER, 5.0, 1.0, 8.0, 5);
                        printf("Green tower created\n");
                    }

                    if(b_pressed){
                        Tower newtower(e.button.x, e.button.y, HYBRID, 3.0, 8.0, 6.0, 6);
                        printf("Blue tower created\n");
                    }

                    if(y_pressed){
                        Tower newtower(e.button.x, e.button.y, MACHINEGUN, 2.0, 2.0, 4.0, 3);
                        printf("Yellow tower created\n");
                    }






                    break;

                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if(114 == e.key.keysym.sym){
                        printf("R pressed\n");
                        r_pressed = true;
                        g_pressed = b_pressed = y_pressed = false;
                    } else if(103 == e.key.keysym.sym){
                        printf("g pressed\n");
                        g_pressed = true;
                        r_pressed = b_pressed = y_pressed = false;
                    } else if(98 == e.key.keysym.sym){
                        printf("b pressed\n");
                        b_pressed = true;
                        r_pressed = g_pressed = y_pressed = false;
                    } else if(121 == e.key.keysym.sym){
                        printf("y pressed\n");
                        y_pressed = true;
                        r_pressed = g_pressed = b_pressed = false;
                    }
                    break;



                case SDL_MOUSEMOTION:

                    x_mouse = e.motion.x;
                    y_mouse = e.motion.y;

                    new_x = (-1 + 2. * x_mouse / (float) surface->w) * GL_VIEW_WIDTH / 2.;
                    new_y = -(-1 + 2. * y_mouse / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
                    
                    
                default:
                    break;

            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation de la mémoire occupee par img */ 
    free_texture(texture_map_BG);
    free_texture(texture_help_button);
    free_texture(texture_help_wdw);
    free_texture(texture_red_tower);
    free_texture(texture_green_tower);
    free_texture(texture_blue_tower);
    free_texture(texture_yellow_tower);

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();

	return 1;
}
