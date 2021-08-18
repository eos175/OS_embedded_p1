#pragma once

#include <video.h>
#include <printf.h>
#include <stdbool.h>



/*

TODO(eos175) Si hay algun comentario raro, era para mi anterior 
compañero, he echo tantos juegos q solo estoy copiando archios 
de proyectos anteriores

*/


typedef enum 
{
	CollisionType_None,
	CollisionType_Top,
	// Middle,
	CollisionType_Bottom,
	CollisionType_Left,
	CollisionType_Right
} CollisionType;



// https://developer.mozilla.org/es/docs/Games/Techniques/2D_collision_detection

static inline bool check_collision(const rect_t rect1, const rect_t rect2)
{
    return rect1.x < rect2.x + rect2.w &&
       rect1.x + rect1.w > rect2.x &&
       rect1.y < rect2.y + rect2.h &&
       rect1.h + rect1.y > rect2.y;
}

#define debug_print printf

static inline CollisionType check_wall_collision(const rect_t s)
{
    const int border = 2;

    // debug_print("(%d %d) (%d, %d) (%d, %d)\n", s.x, s.y, s.x + s.w, s.y + s.h, width, height);
    
    if (s.x < border)
        return CollisionType_Left;
        
    if (s.x + s.w + border > width)
        return CollisionType_Right;
        
    if (s.y < border)
        return CollisionType_Top;
        
    if (s.y + s.h + border > height)
        return CollisionType_Bottom;
    
    return CollisionType_None;
}


static inline bool check_border(rect_t rect)
{
    return check_wall_collision(rect) != CollisionType_None;
}

