#include "ralph.h"
#include "gamestate.h"
#include "gamestate_intro.h"

/* TODO: Resource management*/
ALLEGRO_BITMAP *warning, *kadm;

float shadow = 0.0f;
float sub = 0.02f;

struct gamestate gamestate_intro = {
    .init = gamestate_intro_init,
    .update = gamestate_intro_update,
    .draw = gamestate_intro_draw,
    .destroy = gamestate_intro_destroy,
    .next = NULL,
    .status = 0
};

int gamestate_intro_init(struct gamestate *state)
{
    /* This is where fun begins */
    ALLEGRO_PATH *path;
    path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);

/*
    ALLEGRO_PATH *path_warn = al_clone_path(path);
    al_join_paths(path_warn, al_create_path("data/img/warn.png"));
    warning = al_load_bitmap(al_path_cstr(path_warn));
*/

    ALLEGRO_PATH *path_kadm = al_clone_path(path);
    al_join_paths(path_kadm, al_create_path("data/img/kadm_dark.png"));
    kadm = al_load_bitmap(al_path_cstr(path_kadm, ALLEGRO_NATIVE_PATH_SEP));

    return state->status;
}

int gamestate_intro_update(struct gamestate *state)
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
        al_rest(1.0f);
        state->status = 1;
    }

    return state->status;
}

int gamestate_intro_draw(struct gamestate *state)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_tinted_bitmap(kadm, al_map_rgba_f(shadow, shadow, shadow, shadow),
                          (al_get_bitmap_width(al_get_target_bitmap())-42)/2,
                          (al_get_bitmap_height(al_get_target_bitmap())-62)/2,
                          0);
//    al_draw_scaled_bitmap(kadm, 0, 0, 42, 62, (al_get_display_width(target.screen)-42)/2, (al_get_display_height(target.screen)-62)/2, 42*2, 62*2, 0);

    al_flip_display();

    return state->status;
}

int gamestate_intro_destroy(struct gamestate *state)
{
    /* TODO: unload assets */

    return state->status;
}
