#include "../include/tower.h"
#include "../include/batiment.h"
#include "../include/headers.h"
#include "../include/batiment.h"
#include "../include/map.h"
#include "../include/node.h"
#include "../include/headers.h"


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


bool help_needed = false;


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

void open_help(GLuint* texture){
    if (NULL != texture){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(-400., -300.);
        
            glTexCoord2f(1, 1);
            glVertex2f(300., -300.);
        
            glTexCoord2f(1, 0);
            glVertex2f(400., 300.);
        
            glTexCoord2f(0, 0);
            glVertex2f(-400., 300.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of hep window failed\n");
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
    

/* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }
  
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Initialisation du titre de la fenetre */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);



    /* MAP TEXTURE */
    char image_path[] = "images/carte03.png";
    SDL_Surface* image = IMG_Load(image_path);
    if(NULL == image) {
        fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
        exit(EXIT_FAILURE);
    }
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", image_path);
            return EXIT_FAILURE;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);






    /* Texture help button */
    SDL_Surface* help_image = IMG_Load("images/help_button.png");
    if(NULL == help_image) {
        fprintf(stderr, "Echec du chargement de l'image du bouton d'aide.\n");
        exit(EXIT_FAILURE);
    }

    GLuint texture_help_btn;
    glGenTextures(1, &texture_help_btn);
    glBindTexture(GL_TEXTURE_2D, texture_help_btn);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        switch(help_image->format->BytesPerPixel) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                fprintf(stderr, "Format des pixels de l'image help button non supporte.\n");
                return EXIT_FAILURE;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, help_image->w, help_image->h, 0, format, GL_UNSIGNED_BYTE, help_image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);






    /* Texture help window */
    SDL_Surface* help_window_image = IMG_Load("images/help_window.png");
    if(NULL == help_window_image) {
        fprintf(stderr, "Echec du chargement de l'image de la fenêtre d'aide.\n");
        exit(EXIT_FAILURE);
    }

    GLuint texture_help_wdw;
    glGenTextures(1, &texture_help_wdw);
    glBindTexture(GL_TEXTURE_2D, texture_help_wdw);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        switch(help_window_image->format->BytesPerPixel) {
            case 1:
                format = GL_RED;
                break;
            case 3:
                format = GL_RGB;
                break;
            case 4:
                format = GL_RGBA;
                break;
            default:
                fprintf(stderr, "Format des pixels de l'image d'aide non supporte.\n");
                return EXIT_FAILURE;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, help_window_image->w, help_window_image->h, 0, format, GL_UNSIGNED_BYTE, help_window_image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);






  
    /* Main loop */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture_id);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();

            glBegin(GL_QUADS);
        
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
            draw_help(&texture_help_btn);
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
        
            if( e.type == SDL_KEYDOWN 
                && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
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
                    break;

                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
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

    /* Liberation de la memoire allouee sur le GPU pour la texture */
    glDeleteTextures(1, &texture_id);
    glDeleteTextures(1, &texture_help_btn);
    glDeleteTextures(1, &texture_help_wdw);

    /* Liberation de la mémoire occupee par img */ 
    SDL_FreeSurface(image);
    SDL_FreeSurface(help_image);
    SDL_FreeSurface(help_window_image);

    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();

	return 1;
}
