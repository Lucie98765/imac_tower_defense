#include "../include/tower.h"
#include "../include/batiment.h"
#include "../include/headers.h"
#include "../include/batiment.h"
#include "../include/map.h"
#include "../include/node.h"
#include "../include/headers.h"


/* Dimensions initiales et titre de la fenetre */
// static const unsigned int WINDOW_WIDTH = 800;
// static const unsigned int WINDOW_HEIGHT = 600;
// static const char WINDOW_TITLE[] = "Imac Tower Defense";

// static float aspectRatio;

// /* Espace fenetre virtuelle */
// static const float GL_VIEW_SIZE = 200.;

// /* Nombre de bits par pixel de la fenetre */
// static const unsigned int BIT_PER_PIXEL = 32;

// /* Nombre minimal de millisecondes separant le rendu de deux images */
// static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


// void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
// { 
//     SDL_Surface* surface_temp = SDL_SetVideoMode(   
//         width, height, BIT_PER_PIXEL,
//         SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
//     if(NULL == surface_temp) 
//     {
//         fprintf(
//             stderr, 
//             "Erreur lors du redimensionnement de la fenetre.\n");
//         exit(EXIT_FAILURE);
//     }
//     *surface = surface_temp;

//     aspectRatio = width / (float) height;

//     glViewport(0, 0, (*surface)->w, (*surface)->h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     if( aspectRatio > 1) 
//     {
//         gluOrtho2D(
//         -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
//         -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
//     }
//     else
//     {
//         gluOrtho2D(
//         -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
//         -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
//     }
// }


// void drawSquare(unsigned int x, unsigned int y) 
// {
    
//     glBegin(GL_TRIANGLE_FAN);
    
//     glVertex2f(0.0, 0.0);
//     glVertex2f( x+15 , y-15);
//     glVertex2f( x+15 , y+15);
//     glVertex2f( x-15 , y+15);
//     glVertex2f( x-15 , y-15);
//     glVertex2f( x+15 , y-15);

//     glEnd();
// }


int main(int argc, char const *argv[]) {
	char const *itd_map_name = "data/carte1.itd";
	char const *ppm_map_name = "images/carte1.ppm";

	vector<Node>* Tab_Node = new vector<Node>;
	int itd_ok = check_itd(itd_map_name, Tab_Node);

	if (itd_ok == 0){
		printf("Error while reading itd file, programm is over.\n");
		return 0;
	}

	cout << (*Tab_Node)[0].get_pos_x() << "\n";
    //unsigned int x_mouse = 0, y_mouse = 0;


	//verifier_ppm

	Tower newtower(4,5,ROCKET,8.0,2.0,3.0,6);
    printf("%f\n",newtower.get_power());

    //loadMap
    Map * newmap = new Map;
    load_check_Map(ppm_map_name,newmap);
    cout << newmap->get_width();

	int color_node=check_node_color(Tab_Node, newmap);



	delete(newmap);
	delete Tab_Node;
// 	/* Initialisation de la SDL */
//     if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
//     {
//         fprintf(
//             stderr, 
//             "Impossible d'initialiser la SDL. Fin du programme.\n");
//         exit(EXIT_FAILURE);
//     }
  
//     /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
//     SDL_Surface* surface;
//     reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

//     /* Initialisation du titre de la fenetre */
//     SDL_WM_SetCaption(WINDOW_TITLE, NULL);

// 	/* Chargement de l'image de fond */
//     char image_path[] = "images/carte03.png";
//     SDL_Surface* image = IMG_Load(image_path);
//     if(NULL == image) {
//         fprintf(stderr, "Echec du chargement de l'image %s\n", image_path);
//         exit(EXIT_FAILURE);
//     }

//    /* Initialisation de la texture */
//     GLuint texture_id;
//     glGenTextures(1, &texture_id);

//     glBindTexture(GL_TEXTURE_2D, texture_id);

//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

//     GLenum format;
//     switch(image->format->BytesPerPixel) {
//         case 1:
//             format = GL_RED;
//             break;
//         case 3:
//             format = GL_RGB;
//             break;
//         case 4:
//             format = GL_RGBA;
//             break;
//         default:
//             fprintf(stderr, "Format des pixels de l'image %s non supporte.\n", image_path);
//             return EXIT_FAILURE;
//     }

//     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

//     glBindTexture(GL_TEXTURE_2D, 0);

  
//     /* Boucle principale */
//     int loop = 1;
//     while(loop) 
//     {
//         /* Recuperation du temps au debut de la boucle */
//         Uint32 startTime = SDL_GetTicks();

//         /* Placer ici le code de dessin */
//         glClear(GL_COLOR_BUFFER_BIT);

//         glEnable(GL_TEXTURE_2D);

//         glBindTexture(GL_TEXTURE_2D, texture_id);

//         glMatrixMode(GL_MODELVIEW);
//         glLoadIdentity();

//         glPushMatrix();

//             glBegin(GL_QUADS);
        
//             glTexCoord2f(0, 1);
//             glVertex2f(-133., -100.);
        
//             glTexCoord2f(1, 1);
//             glVertex2f(133., -100.);
        
//             glTexCoord2f(1, 0);
//             glVertex2f(133., 100.);
        
//             glTexCoord2f(0, 0);
//             glVertex2f(-133., 100.);

//             glEnd();

//         glPopMatrix();

//         glBindTexture(GL_TEXTURE_2D, 0);
        
//         glDisable(GL_TEXTURE_2D);


//         glPushMatrix();
//             drawSquare(x_mouse, y_mouse);
//             //drawSquare();
//         glPopMatrix();
        
//         /* Echange du front et du back buffer : mise a jour de la fenetre */
//         SDL_GL_SwapBuffers();
        
//         /* Boucle traitant les evenements */
//         SDL_Event e;
//         while(SDL_PollEvent(&e)) 
//         {
//             /* L'utilisateur ferme la fenetre : */
//             if(e.type == SDL_QUIT) 
//             {
//                 loop = 0;
//                 break;
//             }

//             /* L'utilisateur ferme la fenetre : */
// 			if(e.type == SDL_QUIT) 
// 			{
// 				loop = 0;
// 				break;
// 			}
		
// 			if(	e.type == SDL_KEYDOWN 
// 				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
// 			{
// 				loop = 0; 
// 				break;
// 			}


//             /* Quelques exemples de traitement d'evenements : */
//             switch(e.type) 
//             {
                
//                 /* Clic souris */
//                 case SDL_MOUSEBUTTONUP:
//                     if (e.button.button == SDL_BUTTON_LEFT){
//                         printf("clic en (%d, %d)\n", e.button.x, e.button.y);
//                     } 
//                     break;

                
//                 /* Touche clavier */
//                 case SDL_KEYDOWN:
//                     printf("touche pressee (code = %d)\n", e.key.keysym.sym);
//                     break;



//                 case SDL_MOUSEMOTION:
//                     x_mouse = e.motion.x;
//                     y_mouse = e.motion.y;

                    
//                 default:
//                     break;

//             }
//         }

//         /* Calcul du temps ecoule */
//         Uint32 elapsedTime = SDL_GetTicks() - startTime;
//         /* Si trop peu de temps s'est ecoule, on met en pause le programme */
//         if(elapsedTime < FRAMERATE_MILLISECONDS) 
//         {
//             SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
//         }
//     }

//     /* Liberation de la memoire allouee sur le GPU pour la texture */
//     glDeleteTextures(1, &texture_id);

//     /* Liberation de la mémoire occupee par img */ 
//     SDL_FreeSurface(image);


//     /* Liberation des ressources associees a la SDL */ 
//     SDL_Quit();
	return 1;
}
