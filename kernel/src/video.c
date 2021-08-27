#include <video.h>

#include <printf.h>
#include <string.h>


static color_t *frame_buffer;


// -----------------------------------

/*

template <size_t width, size_t height>
struct FrameBuffer {
    ...
}

*/


typedef unsigned int        uint;


static color_t buffer[786432]; // width * height

static inline int pixel_index(uint x, uint y)
{
    return x + (width * y);
}

static inline void set_pixel(uint x, uint y, color_t color)
{
    if (x < (uint)width && y < (uint)height) {  // proteccion ante errores de produ...
        buffer[pixel_index(x, y)] = color;
    }
}

static inline color_t get_pixel(uint x, uint y)
{
    return (x < (uint)width && y < (uint)height) ? buffer[pixel_index(x, y)] : 0;
}



// -----------------------------------

int video_init(struct stivale2_struct_tag_framebuffer *frame_str_tag)
{
    frame_buffer = (color_t *)frame_str_tag->framebuffer_addr;

    int fb_width = frame_str_tag->framebuffer_width;
    int fb_height= frame_str_tag->framebuffer_height;

    printf("INIT SCREEN: %dx%d:%d\n", frame_str_tag->framebuffer_width, frame_str_tag->framebuffer_height, frame_str_tag->framebuffer_bpp);

    // TODO(eos175) esto deberia retornar un error en (width != fb_width)

    if ((width | height) != (fb_width | fb_height)) {

        while (1)
        {
            asm ("hlt");
        }

        return 1;
        
    }

    return 0;
}



void video_refresh()
{
    /*
    TODO(eos175) 
        `memcpy / memset` estan en asm, 
        ademas son constantes conocidos al momento de compilar
        deberia estas mas q optimizado...
    */
    
    const size_t size = (width * height * sizeof(uint32_t)) / sizeof(uint64_t);
    
    /*
    static int k = 5;
    
    k++;
    if (k < 2) {
        memset64(buffer, 0, size); // video_reset()
        return;
    }
    k = 0;
    */

    memcpy64(frame_buffer, buffer, size); // video_draw()
    memset64(buffer, 0, size); // video_reset()
    
}


void video_fill_rect(const rect_t rect, const color_t color)
{
    int w = rect.w;
    int h = rect.h;
    
    for (int i = 0; i < w * h; i++) {
        // TODO(eos175) seria bueno cambiar estos `%, /` por sumas
        int tx = (i % w) + rect.x; 
        int ty = (i / w) + rect.y;
        set_pixel(tx, ty, color);
    }
}

void video_draw_rect(const rect_t rect, const color_t color)
{
    int x = rect.x;
    int y = rect.y;
    int w = rect.w;
    int h = rect.h;

    for (int i = x; i < x + w; i++) {
        set_pixel(i, y, color);
        set_pixel(i, y + h -1, color);
    }

    for (int i = y; i < y + h; i++) {
        set_pixel(x, i, color);
        set_pixel(x + w -1, i, color);
    }
}


static inline int pixel_index2(int x, int y, int width)
{
    return x + (width * y);
}


void video_draw_bmp(const rect_t rect, const color_t *data)
{
    int w = rect.w;
    int h = rect.h;

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            int i = pixel_index2(x, y, w);
            int color = data[i];
            if (color == 0) continue;
            int tx = rect.x + x;
            int ty = rect.y + y;
            set_pixel(tx, ty, color);
        }
    }
}

void video_blit_bmp(const rect_t dst, const rect_t src, const color_t *data)
{
    const color_t *tmp = data + pixel_index2(src.x, src.y, src.w);
    video_draw_bmp(dst, tmp);
}


