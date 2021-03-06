#include "../include/tower.h"
#include "../include/headers.h"
#include "../include/batiment.h"
#include "../include/map.h"
#include "../include/node.h"
#include "../include/texture.h"
#include "../include/monster.h"
#include "../include/entity.h"
#include "../include/money.h"
#include "../include/display.h"




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
bool p_pressed = false;
bool d_pressed = false;
int nb_red_tower = 0;
int nb_blue_tower = 0;
int nb_green_tower = 0;
int nb_yellow_tower = 0;


int main(int argc, char *argv[]) {

	Map * newmap = new Map;
	char const *itd_map_name = "data/carte1.itd";
	char const *ppm_map_name = "images/carte1.ppm";

    Piece *money = new Piece();


    vector<Installation>* installation_array = new vector<Installation>;
    vector<Tower>* tower_array = new vector<Tower>;
    vector<Monster>* wave = new vector<Monster>;

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
    char money_amount[30];
    bool wanna_play = true;

    //loadMap
    load_check_Map(ppm_map_name, newmap);

    for ( unsigned int i=0; i < (*newmap).get_TabNode().size(); i++) {
        check_node_color( (*newmap).get_one_node_TabNode(i), *newmap );
    }

    /* Initializing SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
    {
        fprintf(
            stderr, 
            "Fail initializing SDL.\n");
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

    /* MONSTER 1 TEXTURE */
    char const *monster_1_path = "images/monster_1.png";
    GLuint texture_monster_1 = createTexture(monster_1_path);

    /* MONSTER 2 TEXTURE */
    char const *monster_2_path = "images/monster_2.png";
    GLuint texture_monster_2 = createTexture(monster_2_path);

    /* RADAR TEXTURE */
    char const *rythm_path = "images/cadence.png";
    GLuint texture_rythm= createTexture(rythm_path);

    /* FACTORY ARMAMENT/POWER TEXTURE */
    char const *power_path = "images/power.png";
    GLuint texture_power= createTexture(power_path);

    /* FACTORY STOCK_MUNITIONS TEXTURE */
    char const *distance_path = "images/distance.png";
    GLuint texture_distance= createTexture(distance_path);


    /* FACTORY STOCK_MUNITIONS TEXTURE */
    char const *welcome_path = "images/welcome.png";
    GLuint texture_welcome= createTexture(welcome_path);

    int monster1_react=0;
    int monster2_react=0;
    int tower_react=0;
    vector<Node> Go_node = newmap->get_TabNode();
    int x_entry = Go_node[0].get_pos_x();
    int y_entry = Go_node[0].get_pos_y();
    int level=1;
    wave_monster(wave, x_entry, y_entry, level);
  
    /* Main loop */
    int loop = 1;
    while(loop) 
    {

        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        if(wanna_play){
            glPushMatrix();
                display_welcome(&texture_welcome);
            glPopMatrix();

            if(help_needed){
                glPushMatrix();
                    display_map_texture(&texture_map_BG);
                glPopMatrix();
                glPushMatrix();
                    open_help(&texture_help_wdw);
                glPopMatrix();
            }

        } else {
            if (wave->size() == 0 && level<50) {
                cout << "You destroyed the wave " << level << " ! \n";
                sleep(10);
                level++;
                wave_monster(wave, x_entry, y_entry, level);
            }
            
            monster1_react++;
            monster2_react++;
            tower_react++;
            usleep(10000);
            if( wave_generate(wave, Go_node, monster1_react, monster2_react) == 0 ) {
                return 0;
            }

            if (tower_array->size()!=0) {
                shot_kill_monster(wave, tower_array, tower_react);
            }
            kill_monster(wave);

            /* Placer ici le code de dessin */
            glClear(GL_COLOR_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glEnable(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, texture_map_BG);

            glPushMatrix();
                display_map_texture(&texture_map_BG);
            glPopMatrix();

            for (unsigned int i = 0; i<tower_array->size(); i++){
                TYPE_TOWER type = (*tower_array)[i].get_type_tower();
                int x = (-1 + 2. * (*tower_array)[i].get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
                int y = -(-1 + 2. * (*tower_array)[i].get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
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

            for (unsigned int i = 0; i< installation_array->size(); i++){
                TYPE_INSTALL type = (*installation_array)[i].get_type();
                int x = (-1 + 2. * (*installation_array)[i].get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
                int y = -(-1 + 2. * (*installation_array)[i].get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.; 
                if(type == RADAR){
                    glPushMatrix();
                        draw_installation(&texture_distance, x, y);
                    glPopMatrix();
                } else if(type == FACTORY_ARMAMENT){
                    glPushMatrix();
                        draw_installation(&texture_power, x, y);
                    glPopMatrix();
                } else if(type == STOCK_MUNITIONS){
                    glPushMatrix();
                        draw_installation(&texture_rythm, x, y);
                    glPopMatrix();
                } 
            }

            for (unsigned int i = 0; i< wave->size(); i++){
                TYPE_MONSTER type =(*wave)[i].get_type();
                int x = (-1 + 2. * (*wave)[i].get_x() / (float) surface->w) * GL_VIEW_WIDTH / 2.;
                int y = -(-1 + 2. * (*wave)[i].get_y() / (float) surface->h) * GL_VIEW_HEIGHT / 2.;
                if (type == MONSTER1) {
                    glPushMatrix();
                        draw_monster(&texture_monster_1, x, y);
                    glPopMatrix();
                }
                else {
                    glPushMatrix();
                        draw_monster(&texture_monster_2, x, y);
                    glPopMatrix();
                }
            }

            glPushMatrix();
                draw_help(&texture_help_button);
            glPopMatrix();

            if (c_pressed){
                glPushMatrix();
                    draw_tower(&texture_red_tower,new_x, new_y);
                glPopMatrix();
                tower_title = "CHIHIRO";
                tower_type = "Type : rocket";
                tower_power = "Power : 8";
                tower_scope = "Scope : 2";
                tower_cadence = "Cadence : 2";
                tower_price = "Price : 5";
            } else if ( s_pressed){
                glPushMatrix();
                    draw_tower(&texture_green_tower, new_x, new_y);
                glPopMatrix();
                tower_title = "SUSWATARI";
                tower_type = "Type : laser";
                tower_power = "Power : 5";
                tower_scope = "Scope : 1";
                tower_cadence = "Cadence : 8";
                tower_price = "Price : 5";
            } else if (h_pressed){
                glPushMatrix();
                    draw_tower(&texture_blue_tower, new_x, new_y);
                glPopMatrix();
                tower_title = "HAKU";
                tower_type = "Type : hybrid";
                tower_power = "Power : 3";
                tower_scope = "Scope : 8";
                tower_cadence = "Cadence : 6";
                tower_price = "Price : 6";
            } else if (b_pressed){
                glPushMatrix();
                    draw_tower(&texture_yellow_tower, new_x, new_y);
                glPopMatrix();
                tower_title = "BO";
                tower_type = "Type : machine-gun";
                tower_power = "Power : 2";
                tower_scope = "Scope : 2";
                tower_cadence = "Cadence : 4";
                tower_price = "Price : 3";
            } else if (r_pressed){
                glPushMatrix();
                    draw_installation(&texture_rythm, new_x, new_y);
                glPopMatrix();
                tower_title = "INSTALLATION";
                tower_type = "Type : cadence";
                tower_power = "Increases rate";
                tower_scope = "of fire";
                tower_cadence = "";
                tower_price = "";
            } else if (p_pressed){
                glPushMatrix();
                    draw_installation(&texture_power, new_x, new_y);
                glPopMatrix();
                tower_title = "INSTALLATION";
                tower_type = "Type : power";
                tower_power = "Increases power";
                tower_scope = "of shots";
                tower_cadence = "";
                tower_price = "";
            } else if (d_pressed){
                glPushMatrix();
                    draw_installation(&texture_distance, new_x, new_y);
                glPopMatrix();
                tower_title = "INSTALLATION";
                tower_type = "Type : distance";
                tower_power = "Increases scope";
                tower_scope = "of fire";
                tower_cadence = "";
                tower_price = "";
            } else {
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
            


            int int_money = money->get_money();
            sprintf(money_amount,"Money amount : %d", int_money);
            write(250, -280, money_amount);



            if(help_needed){
                glPushMatrix();
                    open_help(&texture_help_wdw);
                glPopMatrix();
            }



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

                    if ((e.button.x <= 30) && (e.button.y >=570)) help_needed = true;

                    if(e.button.x>=451 && e.button.x<=711 && e.button.y>=403 && e.button.y<=528 && wanna_play) help_needed = true;

                    if(e.button.x>=92 && e.button.x<=351 && e.button.y>=403 && e.button.y<=528) wanna_play = false;

                    if(e.button.x>=730 && e.button.x<=770 && e.button.y>=30 && e.button.y<=70 && help_needed == true) help_needed = false;

                    if(c_pressed){
                        Tower rocketTower = Tower(e.button.x, e.button.y, ROCKET, 8.0, 20, 3.0, 6);
                        tower_array->push_back(rocketTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(s_pressed){
                        Tower laserTower = Tower(e.button.x, e.button.y, LASER, 5.0, 20, 8.0, 5);
                        tower_array->push_back(laserTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(h_pressed){
                        Tower hybridTower = Tower(e.button.x, e.button.y, HYBRID, 3.0, 20, 6.0, 6);
                        tower_array->push_back(hybridTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(b_pressed){
                        Tower machineTower = Tower(e.button.x, e.button.y, MACHINEGUN, 2.0, 20, 4.0, 3);
                        tower_array->push_back(machineTower);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(r_pressed){
                        Installation radarInst = Installation(e.button.x, e.button.y, STOCK_MUNITIONS, 18);
                        installation_array->push_back(radarInst);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(p_pressed){
                        Installation powerInst = Installation(e.button.x, e.button.y, FACTORY_ARMAMENT, 20);
                        installation_array->push_back(powerInst);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    if(d_pressed){
                        Installation distanceInst = Installation(e.button.x, e.button.y, RADAR, 25);
                        installation_array->push_back(distanceInst);
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    }

                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:
                    if(99 == e.key.keysym.sym){
                        c_pressed = true;
                        s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    } else if(115 == e.key.keysym.sym){
                        s_pressed = true;
                        c_pressed = h_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    } else if(104 == e.key.keysym.sym){
                        h_pressed = true;
                        c_pressed = s_pressed = b_pressed = r_pressed = p_pressed = d_pressed = false;
                    } else if(98 == e.key.keysym.sym){
                        b_pressed = true;
                        c_pressed = s_pressed = h_pressed = r_pressed = p_pressed = d_pressed = false;
                    } else if(114 == e.key.keysym.sym){
                        r_pressed = true;
                        c_pressed = s_pressed = h_pressed = b_pressed = p_pressed = d_pressed = false;
                    } else if(112 == e.key.keysym.sym){
                        p_pressed = true;
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = d_pressed = false;
                    } else if(100 == e.key.keysym.sym){
                        d_pressed = true;
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = false;
                    } else {
                        c_pressed = s_pressed = h_pressed = b_pressed = r_pressed = p_pressed = false;
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
    free_texture(texture_rythm);
    free_texture(texture_power);
    free_texture(texture_distance);
    free_texture(texture_welcome);

    glDisable(GL_BLEND);


    /* Liberation des ressources associees a la SDL */ 
    SDL_Quit();

    // delete (*wave)[i];
    delete installation_array;
    delete tower_array;
    delete wave;
    delete newmap;

	return 1;
}
