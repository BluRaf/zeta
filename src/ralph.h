#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "log.h"

#define RALPH_TARGET_SCALED 1<<0
#define RALPH_TARGET_FULLSCREEN 1<<1

#define stb_min(a,b) ((a) < (b) ? (a) : (b))


struct ralph_rect {
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
};


struct ralph_render_target {
    ALLEGRO_BITMAP *buffer;   /* where game draws */
    ALLEGRO_DISPLAY *display; /* where engine outputs what game draw */
    struct ralph_rect draw_rect;   /* where engine will blit game buffer */
};


void ralph_init(const char *game_name, const char *game_org);
ALLEGRO_EVENT_QUEUE* ralph_init_event();
void ralph_event_add_display(ALLEGRO_EVENT_QUEUE *queue, struct ralph_render_target *target);
ALLEGRO_TIMER* ralph_event_add_timer(ALLEGRO_EVENT_QUEUE *queue, float time);
void ralph_destroy_render(struct ralph_render_target target);
struct ralph_render_target ralph_init_render(int width, int height, char flags, unsigned int scale);
