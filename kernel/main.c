#include <drivers/pit.h>

#include <printf.h>

#include <video.h>
#include <input.h>

#include <collision.h>

#include <files.h>


typedef struct 
{
    vec2_t pos, vel;
    rect_t rect;
} SS_Generic;


typedef SS_Generic Ball;


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


const int BALL_SPEED = 1;
const int PLAYER_SPEED = 1;



int main(int argc, char const *argv[])
{

    files_init();

    Ball ball = {{10,15}, {BALL_SPEED, 1 * BALL_SPEED}, {0,0,50,50}};
    Ball player = {{500,300}, {0, 0}, {0,0,50,50}};

    rect_t rect1 = {500, 500, 360, 180};
    video_draw_bmp(rect1, game_over_data);
    video_refresh();
    sleep(1000000);
    
    while (1)
    {
        
        video_refresh();

        Input key = input_read();
   

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
        

        if (check_wall_collision(ball.rect) == CollisionType_Left || 
            check_wall_collision(ball.rect) == CollisionType_Right) {
            ball.vel.x = -ball.vel.x;
        }
        
        if (check_wall_collision(ball.rect) == CollisionType_Top || 
            check_wall_collision(ball.rect) == CollisionType_Bottom) // Bottom pierde vida
        {
            ball.vel.y = -ball.vel.y;
        }


        move(&ball);
        move(&player);     
		video_fill_rect(ball.rect, 0x0033FF66);
		video_fill_rect(player.rect, 0x00ffFF66);

    }
    


    return 0;
}


