#include <drivers/pit.h>

#include <printf.h>

#include <video.h>
#include <input.h>

#include <collision.h>

#include <files.h>

#include <random.h>

const int BALL_SPEED = 1;
const int PLAYER_SPEED = 2;

const int WALLS_SPEED = 1;
const int MAX_ENEMYS = 30; //for every level
const int ENEMY_SPEED = 1;
const int MAX_BULLETS = 30;
const int BULLET_SPEED = 1;


typedef struct 
{
    vec2_t pos, vel;
    rect_t rect;
} SS_Generic;


typedef struct 
{
	vec2_t pos, vel;
    rect_t rect;
	int health;
} Entity;


typedef SS_Generic Ball;
typedef SS_Generic Enemy;
typedef Entity Player;


void move(void *s)
{
    // TODO(eos175) esto era un template c++, asi q esto es lo mas cercano

    SS_Generic a = *(SS_Generic *)s; 
    
    a.pos.x += a.vel.x;
    a.pos.y += a.vel.y;

    a.rect.x = a.pos.x;
    a.rect.y = a.pos.y;

    *(SS_Generic *)s = a;
}

static void enemys_init(Entity *x)
{
	x->pos.x  = (width/4) + (randint(0, width/2)); //x->pos.x  = (width/4) + (randint(0, width/2))
	x->pos.y  = 0;
	x->vel.x  = 0;
	x->vel.y  = 1 * ENEMY_SPEED;
	x->rect.w = 50;
	x->rect.h = 50;
	x->health = 0;
}
const int OFFSET = 60;
const int MAX_WALLS = (width/OFFSET) * 2;


static void walls_init(SS_Generic *x, Entity *p)
{
    int offset = 60; //20(offset) + 40(heigh)
    for (int i = 0; i < MAX_WALLS; i++)
    {
        x[i].vel.y = WALLS_SPEED;
        x[i].vel.x = 0;

		if ((i % 2) == 0)
		{
			x[i].pos.x = (width/4) - p->rect.w;
            
			if (i == 0)
			{
				x[i].pos.y = 0;

			}
			else
			{
				x[i].pos.y = x[i-2].pos.y + OFFSET; 
			}
			//printf("[%d] = %d\n", i, walls[i].rect.y);
			
		}

		else
		{
			x[i].pos.x = (width - (width/4)) + p->rect.w;
			if (i == 1)
			{
				x[i].pos.y = 0;
			}
			else
			{
				x[i].pos.y = x[i-2].pos.y + OFFSET; 
			}
			//printf("[%d] = %d\n", i, walls[i].rect.y);
		}
		x[i].rect.w = 20;
		x[i].rect.h = 40;
  
    }
}


static void init_bullets(Entity *x, Entity *p)

{
	x->pos.y = p->pos.y - 5;
	x->pos.x = p->pos.x + p->rect.w/2;
	x->health = 1; 
}

static void draw_score(int score)
{


    int i = 0;
    do
    {
        int a = score % 10;

        
        rect_t dst = {95 - (15*i), 0, 10, 10};
        rect_t src = {0, 10 * a , 10, 10};
        video_blit_bmp(dst, src, numbermap_data);
        i++;
        score /= 10;
    } while (score);
    
}

int64_t abs(int64_t a)
{
    if (a < 0)
        return -a;
    return a;
}

bool check_margin(int *arr, size_t size, int value, int eps)
{
    for (int i = 0; i < size; i++)
    {
        int tmp = arr[i];
        if ((abs(tmp - value) - 1 ) < eps)
        {
            return true;
        }
        
    }
    return false;  
}


static void init_rocks(Entity *r, SS_Generic *w_1, SS_Generic *w_2)
{

    int distance = w_2->pos.x - w_1->pos.x;
    int rand = randint(0, distance);
    if (rand < 10)
    {
        rand = 20;
    }
    
    r->pos.x = w_1->pos.x + rand;
    if (w_1->pos.y > 400)
    {
        w_1->pos.y = w_1->pos.y + 40;
    }
    
    r->pos.y = w_1->pos.y;
  
}


int states = 0;


int main(int argc, char const *argv[])
{
    
    files_init();
    
    rect_t player_src = {0, 0, 50, 50};
    rect_t enemy_src = {0,50,50,50};
    Player player = {{width/2, height - 55}, {0, 0}, {width/2,height/2, 50, 50}, 3};
    rect_t rect1 = {140, 150, 360, 180};

    //player.health = 3;
    rect_t beginning = {0,0,640,480};
    rect_t stage_1 = {0,480,640,480};
    rect_t stage_2 = {0,960,640,480};
    rect_t end_game = {0,1440,640,480};
    rect_t dst = {0, 0, 640, 480};
    SS_Generic walls[MAX_WALLS];
    Entity enemys[MAX_ENEMYS];
    Entity bullets[MAX_BULLETS];
    Entity rocks[76];
    SS_Generic walls_level2_w1[12];
    SS_Generic walls_level2_w2[22];
    SS_Generic walls_level2_w3[32];
    SS_Generic walls_level2_w4[10];
    SS_Generic walls_level2[76];
    SS_Generic walls_level2_2[76];

    
    Entity enemys_lvl2[4];


    //rect_t rect1 = {331, 294, 360, 180};
    int random[MAX_ENEMYS];

    rect_t score_all[3];
    rect_t prueba = {0, 480, 0, 0};

    rect_t src_score = {0, 0, 60, 10};
    rect_t dst_score = {0, 0, 60, 10};
    

    rect_t src_score_u = {0, 0, 10, 10};
    rect_t src_score_d = {0, 0, 10, 10};
    rect_t src_score_c = {0, 0, 10, 10};

    rect_t dst_score_u = {95, 0, 10, 10};
    rect_t dst_score_d = {80, 0, 10, 10};
    rect_t dst_score_c = {65, 0, 10, 10};


    rect_t src_health_1 = {0, 0, 10, 10};
    rect_t src_health_2 = {0, 10, 10, 10};
    rect_t src_health_3 = {0, 20, 10, 10};

    rect_t dst_health_1 = {width - 15, 0, 10, 10};
    rect_t dst_health_2 = {width - 30, 0, 10, 10};
    rect_t dst_health_3 = {width - 45, 0, 10, 10};

    
    int score = 0;
    int score_u = 0;
    int score_d = 0;
    int score_c = 0;

    int enemySpawnTimer = 0;
    int colorEnemy = 0;
    int k = 0;
    int r = 0;
    //init the values for the enemys
    for (int i = 0; i < MAX_ENEMYS; i++)
    {
        enemys_init(&enemys[i]);
    }
    
    
        

    //set the health of the bullets
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].pos.x = player.pos.x;
        bullets[i].pos.y = player.pos.y;
        bullets[i].vel.x = 0;
        bullets[i].vel.y = -BULLET_SPEED;
        bullets[i].health = 0;
        bullets[i].rect.w = 5;
        bullets[i].rect.h = 10;
    }



    
    
    video_refresh();

    //int tmp = player.health;;
    sleep(100);
    int state_0 = 1;
    int state_1 = 0;
    int state_2 = 0;
    int state_3 = 0;
    int draw_stage_1 = 1;
    int draw_stage_2 = 1;
    int state_game_over = 0;

    while (1)
    {
        
        video_refresh();

        Input key = input_read();
        if (state_0)
        {
            video_draw_bmp(beginning, transition_data);
            
            if (key.space)
            {
                state_1 = 1;
                state_0 = 0;
                state_game_over = 0;
                player.health = 3;
                Player player = {{width/2, height - 55}, {0, 0}, {width/2,height/2, 50, 50}, 3};
                score = 0;

                //walls_init();
                //init the values for level 1
                walls_init(walls, &player);

                for (int i = 0; i < MAX_ENEMYS; i++)
                {
                    enemys_init(&enemys[i]);
                }
                
                //set the health of the bullets
                for (int i = 0; i < MAX_BULLETS; i++)
                {
                    bullets[i].pos.x = player.pos.x;
                    bullets[i].pos.y = player.pos.y;
                    bullets[i].vel.x = 0;
                    bullets[i].vel.y = -BULLET_SPEED;
                    bullets[i].health = 0;
                    bullets[i].rect.w = 5;
                    bullets[i].rect.h = 10;
                }



                
                int offset_y = 40;
                int offset_x = 10;
                int index = 0;
                for (int i = 0; i < 12; i++)
                {   
                    //parte recta ->primer pantalla

                    
                    walls_level2_w1[i].vel.y = 2*WALLS_SPEED;
                    walls_level2_w1[i].vel.x = 0;
                    if (i == 0)
                    {
                            
                        walls_level2_w1[i].pos.y = height;
                    }
                        
                    else
                    {
                        walls_level2_w1[i].pos.x = width/4 + 50;
                        walls_level2_w1[i].pos.y = walls_level2_w1[i - 1].pos.y - offset_y;
                    }
                        
                    walls_level2_w1[i].rect.w = 10;
                    walls_level2_w1[i].rect.h = 30;
                    walls_level2[index] = walls_level2_w1[i];


                    walls_level2_2[index].pos.x = walls_level2_w1[i].pos.x + 320;
                    walls_level2_2[index].pos.y = walls_level2_w1[i].pos.y;
                    walls_level2_2[index].vel.y = walls_level2_w1[i].vel.y;
                    walls_level2_2[index].vel.x = walls_level2_w1[i].vel.x;

                    walls_level2_2[index].rect.w = walls_level2_w1[i].rect.w;
                    walls_level2_2[index].rect.h = walls_level2_w1[i].rect.h;
                    
                    

                
                    
                    index++;
                
                }

                for (int i = 0; i < 22; i++)
                {   
                    //parte izquierda ->segunda pantalla
                    walls_level2_w2[i].vel.y = 2*WALLS_SPEED;
                    walls_level2_w2[i].vel.x = 0;
                    
                    if (i == 0)
                    {
                        
                        walls_level2_w2[i].pos.y = height;
                        walls_level2_w2[i].pos.x = width/4 + 50;
                    }
                    
                    else
                    {
                        walls_level2_w2[i].pos.x = walls_level2_w2[i - 1].pos.x - offset_x;
                        walls_level2_w2[i].pos.y = walls_level2_w2[i - 1].pos.y - 23;
                    }
                    
                    walls_level2_w2[i].rect.w = 10;
                    walls_level2_w2[i].rect.h = 23;
                    //walls_level2[index] = walls_level2_w2[i];
                    
                    walls_level2[index].pos.y = walls_level2_w2[i].pos.y - 480;
                    walls_level2[index].pos.x = walls_level2_w2[i].pos.x;
                    walls_level2[index].rect.w = walls_level2_w2[i].rect.w;
                    walls_level2[index].rect.h = walls_level2_w2[i].rect.h;
                    walls_level2[index].vel.y = walls_level2_w2[i].vel.y;
                    walls_level2[index].vel.x = walls_level2_w2[i].vel.x;
                    

                    walls_level2_2[index].pos.y = walls_level2_w2[i].pos.y - 480;
                    walls_level2_2[index].pos.x = walls_level2_w2[i].pos.x + 320;
                    walls_level2_2[index].rect.w = walls_level2_w2[i].rect.w;
                    walls_level2_2[index].rect.h = walls_level2_w2[i].rect.h;
                    walls_level2_2[index].vel.y = walls_level2_w2[i].vel.y;
                    walls_level2_2[index].vel.x = walls_level2_w2[i].vel.x;
                    
                    

                    index++;
                
                }
                for (int i = 0; i < 32; i++)
                {   
                    //parte izquierda ->tercera pantalla
                    walls_level2_w3[i].vel.y = 2*WALLS_SPEED;
                    walls_level2_w3[i].vel.x = 0;
                    if (i == 0)
                    {
                        
                        walls_level2_w3[i].pos.y = height - 15;
                        walls_level2_w3[i].pos.x = 0;
                    }
                    
                    else
                    {
                        walls_level2_w3[i].pos.x = walls_level2_w3[i - 1].pos.x + offset_x;
                        walls_level2_w3[i].pos.y = walls_level2_w3[i - 1].pos.y - 15;
                    }
                    
                    walls_level2_w3[i].rect.w = 10;
                    walls_level2_w3[i].rect.h = 15;

                
                    walls_level2[index].pos.y = walls_level2_w3[i].pos.y - 960;
                    walls_level2[index].pos.x = walls_level2_w3[i].pos.x;
                    walls_level2[index].rect.w = walls_level2_w3[i].rect.w;
                    walls_level2[index].rect.h = walls_level2_w3[i].rect.h;
                    walls_level2[index].vel.y = walls_level2_w3[i].vel.y;
                    walls_level2[index].vel.x = walls_level2_w3[i].vel.x;

                    walls_level2_2[index].pos.y = walls_level2_w3[i].pos.y - 960;
                    walls_level2_2[index].pos.x = walls_level2_w3[i].pos.x + 320;
                    walls_level2_2[index].rect.w = walls_level2_w3[i].rect.w;
                    walls_level2_2[index].rect.h = walls_level2_w3[i].rect.h;
                    walls_level2_2[index].vel.y = walls_level2_w3[i].vel.y;
                    walls_level2_2[index].vel.x = walls_level2_w3[i].vel.x;

                    

                    index++;

                    

                }

                for (int i = 0; i < 10; i++)
                {   
                    //parte izquierda ->cuarta pantalla
                    walls_level2_w4[i].vel.y = 2*WALLS_SPEED;
                    walls_level2_w4[i].vel.x = 0;

                    if (i == 0)
                    {
                        
                        walls_level2_w4[i].pos.y = height - 44;
                        walls_level2_w4[i].pos.x = 320;
                    }
                    
                    else
                    {
                        walls_level2_w4[i].pos.x = walls_level2_w4[i - 1].pos.x - offset_x;
                        walls_level2_w4[i].pos.y = walls_level2_w4[i - 1].pos.y - 44;
                    }
                    
                    walls_level2_w4[i].rect.w = 10;
                    walls_level2_w4[i].rect.h = 44;

                    walls_level2[index].pos.y = walls_level2_w4[i].pos.y - 1460;
                    walls_level2[index].pos.x = walls_level2_w4[i].pos.x;
                    walls_level2[index].rect.w = walls_level2_w4[i].rect.w;
                    walls_level2[index].rect.h = walls_level2_w4[i].rect.h;
                    walls_level2[index].vel.y = walls_level2_w4[i].vel.y;
                    walls_level2[index].vel.x = walls_level2_w4[i].vel.x;



                    walls_level2_2[index].pos.y = walls_level2_w4[i].pos.y - 1460;
                    walls_level2_2[index].pos.x = walls_level2_w4[i].pos.x + 320;
                    walls_level2_2[index].rect.w = walls_level2_w4[i].rect.w;
                    walls_level2_2[index].rect.h = walls_level2_w4[i].rect.h;
                    walls_level2_2[index].vel.y = walls_level2_w4[i].vel.y;
                    walls_level2_2[index].vel.x = walls_level2_w4[i].vel.x;

                    

                    //walls_level2[index] = walls_level2_w4[i];
                    index++;
                
                }





                int proba = 0;
                int posicion = 0;
                
                for (int i = 0; i < 1; i++)
                {   
                    proba = randint(0, 12);
                    //enemigos en pantalla 1
                    enemys_lvl2[posicion].pos.x = walls_level2_w1[proba].pos.x + randint(35,125);
                    enemys_lvl2[posicion].pos.y = walls_level2_w1[proba].pos.y - randint(0, 300);
                    enemys_lvl2[posicion].vel.y = 2;
                    enemys_lvl2[posicion].vel.x = 0;
                    enemys_lvl2[posicion].health = 1;
                    enemys_lvl2[posicion].rect.w = 30;
                    enemys_lvl2[posicion].rect.h = 30;
                    posicion++;
                    
                }

                
                for (int i = 0; i < 1; i++)
                {   
                    proba = randint(0, 22);
                    //enemigos en pantalla 2
                    enemys_lvl2[posicion].pos.x = walls_level2_w2[proba].pos.x + randint(35,175) + 20;
                    enemys_lvl2[posicion].pos.y = walls_level2_w2[proba].pos.y - 480;
                    enemys_lvl2[posicion].vel.y = 2;
                    enemys_lvl2[posicion].vel.x = 0;
                    enemys_lvl2[posicion].health = 1;
                    enemys_lvl2[posicion].rect.w = 30;
                    enemys_lvl2[posicion].rect.h = 30;
                    
                    posicion++;
                }
                
                for (int i = 0; i < 1; i++)
                {   
                    proba = randint(0, 32);
                    //enemigos en pantalla 3
                    enemys_lvl2[posicion].pos.x = walls_level2_w3[proba].pos.x + randint(35,80);
                    enemys_lvl2[posicion].pos.y = walls_level2_w3[proba].pos.y - 960;
                    enemys_lvl2[posicion].vel.y = 2;
                    enemys_lvl2[posicion].vel.x = 0;
                    enemys_lvl2[posicion].health = 1;
                    enemys_lvl2[posicion].rect.w = 30;
                    enemys_lvl2[posicion].rect.h = 30;
                    
                    posicion++;
                }
                
                for (int i = 0; i < 1; i++)
                {   
                    proba = randint(0, 10);
                    //enemigos en pantalla 4
                    enemys_lvl2[posicion].pos.x = walls_level2_w4[proba].pos.x + randint(35, 200);
                    enemys_lvl2[posicion].pos.y = walls_level2_w4[proba].pos.y - 1460;
                    enemys_lvl2[posicion].vel.y = 2;
                    enemys_lvl2[posicion].vel.x = 0;
                    enemys_lvl2[posicion].health = 1;
                    enemys_lvl2[posicion].rect.w = 30;
                    enemys_lvl2[posicion].rect.h = 30;
                    
                    posicion++;
                }
                
               
                

                player.pos.x = width/2;
                player.pos.y = height - 55;
                

                draw_stage_1 = 1;
                draw_stage_2 = 2;
            }
        }
        

        
        


        if (state_1)//state_1 controla que siempre este el jugador /score/corazones pintados
        {
            
            if (key.up) {
                player.vel.y = -PLAYER_SPEED;
            } else if (key.down) {
                player.vel.y = PLAYER_SPEED;
            } else {
                player.vel.y = 0;
            }
            
            if (key.right) {
                player.vel.x = PLAYER_SPEED;
            } else if (key.left) {
                player.vel.x = -PLAYER_SPEED;
            } else {
                player.vel.x = 0;
            }

            
           if (score == 0)
           {
               state_2 = 1;
           }
           

            // NIVEL 1
            if (state_2)
            {
                
                if (draw_stage_1)
                {
                    video_blit_bmp(dst, stage_1, transition_data);
                    player.health = 3;
                    if (key.right)
                    {
                        draw_stage_1 = 0;
                    }
                    
                }
                
                if (player.health == 0)
                {
                    state_game_over = 1;
                    state_2 = 0;
                    state_1 = 0;
                    state_0 = 1;
                }
                
                

                //enemys
                if (--enemySpawnTimer <= -1)
                {
                    if (r > 35)
                    {
                        //160---480

                        for (int i = 0; i < MAX_ENEMYS; i++)
                        {
                            if (enemys[i].health == 0)
                            {
                                //enemys[i].health = 1;
                                
                                enemys[i].health = 1;
                                
                                r = 0;
                                break;
                            }
                        }
                    }    
                }
                enemySpawnTimer = randint(0, 200);
                //move the enemys for the level 1
                for (int i = 0; i < MAX_ENEMYS; i++)
                {
                    if (enemys[i].health == 1)
                    {
                        move(&enemys[i]);
                        colorEnemy = randint(1,2);
                        enemy_src.y = 50*colorEnemy;
                        video_blit_bmp(enemys[i].rect, enemy_src, graphics_data);
                        
                        if (check_wall_collision(enemys[i].rect) == CollisionType_Bottom)
                        {
                            enemys[i].pos.x  = width + width/2;
                            enemys[i].pos.y  = height/2;
                            enemys[i].vel.y  = 0;
                            enemys[i].health = 0;
                            move(&enemys[i]);
                            player.health--;
                        } 
                        if (check_collision(enemys[i].rect, player.rect))
                        {
                            enemys[i].pos.x  = width + width/2;
                            enemys[i].pos.y  = height/2;
                            enemys[i].vel.y  = 0;
                            enemys[i].health = 0;
                            move(&enemys[i]);
                            player.health--;
                        }
                        
                    }
                }

                //estas balas solo se utilizan en el nivel 1
                //bullets
            
                if (k > 50)
                {
                    if (key.a)
                    {
                        
                        for (int i = 0; i < MAX_BULLETS; i++)
                        {
                                
                                
                            if (bullets[i].health == 0)
                            {
                                //set the values for the bullets
                                init_bullets(&bullets[i], &player);  
                                k = 0;
                                
                                break;
                            }

                            if (bullets[i].pos.y < 0)
                            {
                                bullets[i].health = 0;
                            }
                        }           
                    }
                }
                //pintar balas y verificar colision con los enemigos que salen
                for (int i = 0; i < MAX_BULLETS; i++)
                {
                    if (bullets[i].health == 1)
                    {
                        move(&bullets[i]);
                        video_fill_rect(bullets[i].rect, 0x00FFFFFF);
                        for (int e = 0; e < MAX_ENEMYS; e++)
                        {
                            if (enemys[e].health == 1 && check_collision(enemys[e].rect, bullets[i].rect))
                            {
                                score += 3; 
                                enemys[e].vel.y = 0;
                                enemys[e].pos.x = width + width/2;
                                enemys[e].health = 0;

                                bullets[i].health = 0;

                                move(&enemys[e]);
                                if (score >= 10)
                                {
                                    state_2 = 0;
                                    state_3 = 1;
                                }
                                
                            }
                        }
                    }
                    
                }

                //calle diseñaba para el nivel 1
                //for level 1 background
                for (int i = 0; i < MAX_WALLS; i++)
                {
                    //walls[i].rect.y += WALLS_SPEED;
                    
                    move(&walls[i]);
                    video_fill_rect(walls[i].rect, 0x009B9B9B);

                    if (check_collision(walls[i].rect, player.rect))
                    {
                        if (walls[i].rect.x > player.rect.x)
                        {
                            player.pos.x = walls[i].rect.x - 63;
                        }
                        else
                        {
                            player.pos.x = walls[i].rect.x + 23;
                        }
                        
                    }

                    if (check_wall_collision(walls[i].rect) == CollisionType_Bottom)
                    {
                        walls[i].pos.y = 0;
                    }	
                }

                if (check_wall_collision(player.rect) == CollisionType_Bottom)
                {
                    player.pos.y = height - 55;
                }
                

                k++;
                r++;

                


            }

            if (state_3)//state_3 controlo el nivel dos del juego el zic zac
            {
                
                if (draw_stage_2)
                {
                    //player.health = 3;
                    
                    video_blit_bmp(dst, stage_2, transition_data);
                    if (key.right)
                    {
                        draw_stage_2 = 0;
                    }
                    
                }
               
                int flag_hit = 0;
                for (int i = 0; i < 4; i++)
                {
                    move(&enemys_lvl2[i]);
                    video_draw_bmp(enemys_lvl2[i].rect, peaks_data);
                    if (check_wall_collision(enemys_lvl2[i].rect) == CollisionType_Bottom)
                    {
                        enemys_lvl2[i].pos.y = -1920 + enemys_lvl2[i].pos.y + 30;
                        score += 9;
                    }
                    if (check_collision(enemys_lvl2[i].rect, player.rect))
                    {
                        
                        enemys_lvl2[i].pos.y  = -1920 + enemys_lvl2[i].pos.y + 30;
                        move(&enemys_lvl2[i]);
                        player.health --;
                        flag_hit = 1;
                    }
                    
                    
           
  
                }
                
                

                for (int i = 0; i < 76; i++)
                {
                    move(&walls_level2[i]);
                    move(&walls_level2_2[i]);
                    
                    video_fill_rect(walls_level2[i].rect, 0x0033FF66);
                    video_fill_rect(walls_level2_2[i].rect, 0x0033FF66);
                    if (check_wall_collision(walls_level2[i].rect) == CollisionType_Bottom)
                    {
                        walls_level2[i].pos.y = -1920 + walls_level2[i].pos.y + 30;
                        walls_level2_2[i].pos.y = -1920 + walls_level2_2[i].pos.y + 30;
                    }
                    if (check_collision(walls_level2[i].rect, player.rect))
                    {
                        player.pos.x = player.pos.x + 3;
                    }
                    if (check_collision(walls_level2_2[i].rect, player.rect))
                    {
                        player.pos.x = player.pos.x - 3;
                    }
                }

                
                if (player.health == 0)
                {
                    state_3 = 0;
                    state_0 = 1;
                    state_1 = 0;

                    state_game_over = 1;
                }
                
                
                

                

            }
            
           
            draw_score(score);
            video_draw_bmp(dst_score, score_word_data);
            
            if (player.health == 3)
            {
                video_blit_bmp(dst_health_1, src_health_1, health_graph_data);
                video_blit_bmp(dst_health_2, src_health_1, health_graph_data);
                video_blit_bmp(dst_health_3, src_health_1, health_graph_data);
            }
            if (player.health == 2)
            {
                video_blit_bmp(dst_health_2, src_health_1, health_graph_data);
                video_blit_bmp(dst_health_3, src_health_1, health_graph_data);
            }
            
            if (player.health == 1)
            {
                video_blit_bmp(dst_health_3, src_health_1, health_graph_data);
            }

            
            //siempre tenemos al jugador idenpendientemente del nivel
            move(&player);     
            video_blit_bmp(player.rect, player_src, graphics_data);
            
            


        }
        
        if (score >= 175)
        {
            video_blit_bmp(dst, end_game, transition_data);
            state_3 = 0;
            state_2 = 0;
            state_1 = 0;
            state_0 = 0;
            state_game_over = 0;
            if (key.enter)
            {
                state_0 = 1;
                score = 0;
            }
        }


        if (state_game_over == 1)
        {
            video_draw_bmp(rect1, game_over_data);
            state_2 = 0;
            state_1 = 0;
            state_0 = 0;
            if (key.enter)
            {
                state_0 = 1;
                state_game_over = 0;
            }
            
        }
        
        
        


        
    }


    return 0;
}

