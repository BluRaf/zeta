#include "ralph.h"
#include "gamestate.h"
#include "gamestate_intro.h"


/* TODO: Resource management*/
ALLEGRO_BITMAP *warning, *kadm;


int gamestate_intro_update(struct gamestate *state) {
    /* This is where fun begins */
    ALLEGRO_PATH *path;
    path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
/*    if (warning == NULL) {
        ALLEGRO_PATH *path_warn = al_clone_path(path);
        al_join_paths(path_warn, al_create_path("data/img/warn.png"));
        warning = al_load_bitmap(al_path_cstr(path_warn));
    }*/
    if (kadm == NULL) {
        ALLEGRO_PATH *path_kadm = al_clone_path(path);
        al_join_paths(path_kadm, al_create_path("data/img/kadm_dark.png"));
        kadm = al_load_bitmap(al_path_cstr(path_kadm, ALLEGRO_NATIVE_PATH_SEP));
    }
    return state->done;
}


void gamestate_intro_draw(struct gamestate *state) {
    static float shadow = 0.0f;
    static float sub = 0.02f;
    if (shadow >= 0.0f) {
        if (shadow >= 1.0f) {
            sub *= -1.0f;
            al_rest(3.0f);
            al_flip_display();
        }
        shadow += sub;
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_tinted_bitmap(kadm, al_map_rgba_f(shadow, shadow, shadow, shadow), 
                              (al_get_bitmap_width(al_get_target_bitmap())-42)/2, (al_get_bitmap_height(al_get_target_bitmap())-62)/2, 0);
//        al_draw_scaled_bitmap(kadm, 0, 0, 42, 62, (al_get_display_width(target.screen)-42)/2, (al_get_display_height(target.screen)-62)/2, 42*2, 62*2, 0);
        state->done = 0;
    }
    else {
        al_rest(1.0f);
        state->done = 1;
    }
}
