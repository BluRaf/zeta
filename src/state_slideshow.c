#include "ralph.h"
#include "gamestate.h"
#include "state_slideshow.h"

/* TODO: Resource management*/
ALLEGRO_BITMAP * slides[2];
char* slides_paths[] = {
    "data/img/warn.png",
    "data/img/kadm_dark.png"
};

float shadow = 0.0f;
float sub = 0.02f;
int current_slide = 0;

struct state_s state_slideshow = {
    .init = state_slideshow_init,
    .update = state_slideshow_update,
    .draw = state_slideshow_draw,
    .destroy = state_slideshow_destroy,
    .next = NULL,
    .status = 0
};

int state_slideshow_init(struct state_s *state)
{
    /* This is where fun begins */
    ALLEGRO_PATH *path, *path_slide;
    path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

    for (int i = 0; i < 2; i++) {
        path_slide = al_clone_path(path);
        al_join_paths(path_slide, al_create_path(slides_paths[i]));
        slides[i] = al_load_bitmap(al_path_cstr(path_slide, ALLEGRO_NATIVE_PATH_SEP));
        al_destroy_path(path_slide);
    }

    al_destroy_path(path);

    return state->status;
}

int state_slideshow_update(struct state_s *state)
{
    if (shadow >= 0.0f) {
        if (shadow >= 1.0f) {
            sub *= -1.0f;
            al_rest(3.0f);
        }
        shadow += sub;
        state->status = 0;
    }
    else {
        if (current_slide < 1) current_slide++;
        else state->status = STATE_DONE;

        shadow = 0.0f;
        sub = 0.02f;
    }

    return state->status;
}

int state_slideshow_draw(struct state_s *state)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_tinted_bitmap(slides[current_slide], al_map_rgba_f(shadow, shadow, shadow, shadow),
                          (al_get_bitmap_width(al_get_target_bitmap())-al_get_bitmap_width(slides[current_slide]))/2,
                          (al_get_bitmap_height(al_get_target_bitmap())-al_get_bitmap_height(slides[current_slide]))/2,
                          0);
//    al_draw_scaled_bitmap(slides[current_slide], 0, 0, 42, 62, (al_get_display_width(target.screen)-42)/2, (al_get_display_height(target.screen)-62)/2, 42*2, 62*2, 0);

    al_flip_display();

    return state->status;
}

int state_slideshow_destroy(struct state_s *state)
{
    /* TODO: unload assets */
    for (int i = 0; i < 2; i++) {
        al_destroy_bitmap(slides[i]);
    }
    return state->status;
}
