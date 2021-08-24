#pragma once

#include <stivale2.h>
#include <string.h>


typedef uint32_t    color_t;

typedef struct {
    int x, y, w, h;
} rect_t;

typedef struct 
{
    int x, y;
} vec2_t;


static const int width = 640;
static const int height = 480;


int video_init(struct stivale2_struct_tag_framebuffer *frame_str_tag);

void video_refresh();

void video_fill_rect(const rect_t rect, const color_t color);

void video_draw_rect(const rect_t rect, const color_t color);

void video_draw_bmp(const rect_t rect, const color_t *data);

void video_blit_bmp(const rect_t dst, const rect_t src, const color_t *data);


