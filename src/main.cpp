#include "../include/tower.h"
#include "../include/headers.h"
#include "../include/batiment.h"
#include "../include/map.h"
#include "../include/node.h"
#include "../include/texture.h"
#include "../include/monster.h"
#include "../include/entity.h"


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
bool c_pressed = false;
bool s_pressed = false;
bool h_pressed = false;
bool b_pressed = false;
bool r_pressed = false;
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


void drawSquare(float x, float y, GLuint* texture) {

    if (texture != NULL){   
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f( x-15, y-30);
        
            glTexCoord2f(1, 1);
            glVertex2f( x+15, y-30);
        
            glTexCoord2f(1, 0);
            glVertex2f( x+15, y+30);
        
            glTexCoord2f(0, 0);
            glVertex2f( x-15, y+30);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of cursor failed\n");
    }

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
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_tower);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-15, y-32.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+15., y-32.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+15., y+31.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-15., y+31.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of tower failed\n");
    }
}

void draw_monster(GLuint* texture_monster, int x, int y){
    if (NULL != texture_monster){
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, *texture_monster);
        glBegin(GL_QUADS);
            glColor3ub(255,255,255);
            glTexCoord2f(0, 1);
            glVertex2f(x-15, y-18.);
        
            glTexCoord2f(1, 1);
            glVertex2f(x+15., y-18.);
        
            glTexCoord2f(1, 0);
            glVertex2f(x+15., y+18.);
        
            glTexCoord2f(0, 0);
            glVertex2f(x-15., y+18.);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    } else {
        printf("display of monster failed\n");
    }
}

void write(int x, int y,  char const *string) {

        char const *c;
        glColor3ub(0,0,0);
        // Positionne le premier caractère de la chaîne
        glRasterPos2f(x, y);
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c); // Affiche chaque caractère de la chaîne

        // Réinitialise la position du premier caractère de la chaîne
        glRasterPos2f(0, 0);
}










int main(int argc, char *argv[]) {

	Map * newmap = new Map;
	char const *itd_map_name = "data/carte1.itd";
	char const *ppm_map_name = "images/carte1.ppm";


    vector<Tower> tower_array = vector<Tower>();
    vector<Installation> installation_array = vector<Installation>();
    vector<Monster*> monster_array = vector<Monster*>();


    float new_x = 0;
    float new_y = 0;

	int itd_ok = check_itd(itd_map_name, newmap);
	if (itd_ok == 0){
		printf("Error while reading itd file, programm is over.\n");
		return 0;
	}

    unsigned int x_mouse = 0, y_mouse = 0;


    char const *tower_title;
    char const *tower_type;
    char const *tower_power;
    char const *tower_scope;
    char const *tower_cadence;
    char const *tower_price;


	cout << (*newmap).get_one_node_TabNode(0).get_pos_x() << "\n";

    //loadMap
    load_check_Map(ppm_map_name, newmap);
    cout << newmap->get_width();

    for ( unsigned int i=0; i < (*newmap).get_TabNode().size(); i++) {
        check_node_color( (*newmap).get_one_node_TabNode(i), *newmap );
    }

    Node node1 = (*newmap).get_one_node_TabNode(0);
    cout << node1.get_pos_x();
    Node node2 = (*newmap).get_one_node_TabNode(1);
    cout << node2.get_pos_x();

    delete(newmap);
    

    int x_monster = 14, y_monster = 74;

    Monster *monster_1 = new Monster(x_monster,y_monster,MONSTER1,0,15+0,3,5,0.75,1,1,1.25);
    monster_array.push_back(monster_1);




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
    glutInit(&argc, argv); // initialisation de GLUTs
	
    /* Initializing the title of the window */
    SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//for ( unsigned int j=1; j < (*newmap).get_TabNode().size(); j++) {


		

		/*if (bressenham(node1, node2, newmap) != true) {
			cout << "Y a encore du chemin à faire.. lol on check le chemin";
		}*/
	


    /* MAP TEXTURE */
    char const *image_path = "images/background1.png";
    GLuint texture_map_BG = createTexture(image_path);
    
    /* HELP BUTTON TEXTURE */
    char const *help_btn_path = "images/help_button.png";
    GLuint texture_help_button = createTexture(help_btn_path);

    /* HELP WINDOW TEXTURE*/
    char const *help_wdw_path = "images/help_window2.png";
    GLuint texture_help_wdw= createTexture(help_wdw_path);

    /* RED TOWER TEXTURE */
    char const *red_tower_path = "images/chihiro_tower.png";
    GLuint texture_red_tower = createTexture(red_tower_path);

    /* GREEN TOWER TEXTURE */
    char const *green_tower_path = "images/susuwatari_tower.png";
    GLuint texture_green_tower = createTexture(green_tower_path);

    /* BLUE TOWER TEXTURE */
    char const *blue_tower_path = "images/haku_tower.png";
    GLuint texture_blue_tower = createTexture(blue_tower_path);

    /* YELLOW TOWER TEXTURE */
    char const *yellow_tower_path = "images/bo_tower.png";
    GLuint texture_yellow_tower = createTexture(yellow_tower_path);

    /* CURSOR TEXTURE */
    char const *cursor_path = "images/cursor.png";
    GLuint texture_cursor = createTexture(cursor_path);

    /* MONSTER 1 TEXTURE */
    char const *monster_1_path = "images/monster_1.png";
    GLuint texture_monster_1 = createTexture(monster_1_path);

    /* MONSTER 2 TEXTURE */
    char const *monster_2_path = "images/monster_2.png";
    GLuint texture_monster_2 = createTexture(monster_2_path);

    /* RADAR TEXTURE */
    char const *rythm_path = "images/cadence.png";
    GLuint texture_rythm= createTexture(rythm_path);


    

  
    /* Main loop */
    int loop = 1;
    while(loop) 
    {
        //usleep(10000);
        //monster_1->move(monster_1->get_x(), monster_1->get_y(), 385, 74);
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



        if (c_pressed){
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_red_tower);
            glPopMatrix();
            tower_title = "CHIHIRO";
            tower_type = "Type : rocket";
            tower_power = "Power : 8";
            tower_scope = "Scope : 2";
            tower_cadence = "Cadence : 2";
            tower_price = "Price : 5";
        } else if ( s_pressed){
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_green_tower);
            glPopMatrix();
            tower_title = "SUSWATARI";
            tower_type = "Type : laser";
            tower_power = "Power : 5";
            tower_scope = "Scope : 1";
            tower_cadence = "Cadence : 8";
            tower_price = "Price : 5";
        } else if (h_pressed){
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_blue_tower);
            glPopMatrix();
            tower_title = "HAKU";
            tower_type = "Type : hybrid";
            tower_power = "Power : 3";
            tower_scope = "Scope : 8";
            tower_cadence = "Cadence : 6";
            tower_price = "Price : 6";
        } else if (b_pressed){
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_yellow_tower);
            glPopMatrix();
            tower_title = "BO";
            tower_type = "Type : machine-gun";
            tower_power = "Power : 2";
            tower_scope = "Scope : 2";
            tower_cadence = "Cadence : 4";
            tower_price = "Price : 3";
        } else if (r_pressed){
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_rythm);
            glPopMatrix();
            tower_title = "INSTALLATION";
            tower_type = "Type : rythm";
            tower_power = "Increases cadence";
            tower_scope = "";
            tower_cadence = "";
            tower_price = "";
        } else {
            glPushMatrix();
                drawSquare(new_x, new_y, &texture_cursor);
            glPopMatrix();
            tower_title = "";
            tower_type = "";
            tower_power = "";
            tower_scope = "";
            tower_cadence = "";
            tower_price = "";
        }
        if(tower_title!=""){
            write(250, 280, tower_title);
            write(250, 260, tower_type);
            write(250, 240, tower_power);
            write(250, 220, tower_scope);
            write(250, 200, tower_cadence);
            write(250, 180, tower_price);
        }
        

        


        glPushMatrix();
            draw_help(&texture_help_button);
        glPopMatrix();

       

        char const *string = "bonsoir je suis un texte";
        
        //write(200, 200, string);

        for (unsigned int i = 0; i<tower_array.size(); i++){
            TYPE_TOWER type = tower_array[i].get_type_tower();
            int x = (-1 + 2. * tower_array[i].get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
            int y = -(-1 + 2. * tower_array[i].get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
            if(type == ROCKET){
                glPushMatrix();
                    draw_tower(&texture_red_tower, x, y);
                glPopMatrix();
            } else if(type == LASER){
                glPushMatrix();
                    draw_tower(&texture_green_tower, x, y);
                glPopMatrix();
            } else if(type == MACHINEGUN){
                glPushMatrix();
                    draw_tower(&texture_yellow_tower, x, y);
                glPopMatrix();
            } else if(type == HYBRID){
                glPushMatrix();
                    draw_tower(&texture_blue_tower, x, y);
                glPopMatrix();
            }
        }

        for (unsigned int i = 0; i<installation_array.size(); i++){
            TYPE_INSTALL type = installation_array[i].get_type();
            int x = (-1 + 2. * installation_array[i].get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
            int y = -(-1 + 2. * installation_array[i].get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
            if(type == RADAR){
                glPushMatrix();
                    draw_tower(&texture_rythm, x, y);
                glPopMatrix();
            } 
        }

        for (unsigned int i = 0; i<monster_array.size(); i++){
            int x = (-1 + 2. * monster_array[i]->get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
            int y = -(-1 + 2. * monster_array[i]->get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
                glPushMatrix();
                    draw_monster(&texture_monster_1, x, y);
                glPopMatrix();
        }



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





                    if(c_pressed){
                        Tower rocketTower = Tower(e.button.x, e.button.y, ROCKET, 8.0, 2.0, 3.0, 6);
                        tower_array.push_back(rocketTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = false;
                    }

                    if(s_pressed){
                        Tower laserTower = Tower(e.button.x, e.button.y, LASER, 5.0, 1.0, 8.0, 5);
                        tower_array.push_back(laserTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = false;
                    }

                    if(h_pressed){
                        Tower hybridTower = Tower(e.button.x, e.button.y, HYBRID, 3.0, 8.0, 6.0, 6);
                        tower_array.push_back(hybridTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = false;
                    }

                    if(b_pressed){
                        Tower machineTower = Tower(e.button.x, e.button.y, MACHINEGUN, 2.0, 2.0, 4.0, 3);
                        tower_array.push_back(machineTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = false;
                    }

                    if(r_pressed){
                        Installation radarInst = Installation(e.button.x, e.button.y, RADAR, 15);
                        installation_array.push_back(radarInst);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = false;
                    }

                    break;

                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if(99 == e.key.keysym.sym){
                        printf("c pressed\n");
                        c_pressed = true;
                        s_pressed = h_pressed = b_pressed = r_pressed = false;
                        drawSquare(new_x, new_y, &texture_red_tower);
                    } else if(115 == e.key.keysym.sym){
                        printf("s pressed\n");
                        s_pressed = true;
                        c_pressed = h_pressed = b_pressed = r_pressed = false;
                        drawSquare(new_x, new_y, &texture_green_tower);
                    } else if(104 == e.key.keysym.sym){
                        printf("h pressed\n");
                        h_pressed = true;
                        c_pressed = s_pressed = b_pressed = r_pressed = false;
                        drawSquare(new_x, new_y, &texture_blue_tower);
                    } else if(98 == e.key.keysym.sym){
                        printf("b pressed\n");
                        b_pressed = true;
                        c_pressed = s_pressed = h_pressed = r_pressed =false;
                        drawSquare(new_x, new_y, &texture_yellow_tower);
                    } else if(114 == e.key.keysym.sym){
                        printf("r pressed\n");
                        r_pressed = true;
                        c_pressed = s_pressed = h_pressed = b_pressed = false;
                        drawSquare(new_x, new_y, &texture_yellow_tower);
                    } else {
                        printf("no tower\n");
                        c_pressed = s_pressed = h_pressed = b_pressed = false;
                        drawSquare(new_x, new_y, &texture_cursor);
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
    free_texture(texture_cursor);
    free_texture(texture_rythm);

    glDisable(GL_BLEND);


    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();

	return 1;
}
