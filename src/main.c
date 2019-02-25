#include "utils.h"
#include "ralph.h"
#include "gamestate.h"
#include "gamestate_intro.h"


#define GAME_WIDTH 240
#define GAME_HEIGHT 320
#define FPS 60


struct ralph_render_target target;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *frame_timer = NULL;


/* TODO: Proper gamestate management */
struct gamestate gamestate_intro = {
    .next = NULL,
    .calls = {
        .update = gamestate_intro_update,
        .draw = gamestate_intro_draw
    },
    .done = 0
};


int main(int argc, char *argv[])
{
    int done = 0;

    struct gamestate *state = &gamestate_intro;

    ralph_init("Zeta", "BluRaf");

    event_queue = ralph_init_event();

    target = ralph_init_render(GAME_WIDTH, GAME_HEIGHT, RALPH_TARGET_FULLSCREEN, 3);

    ralph_event_add_display(event_queue, &target);
    frame_timer = ralph_event_add_timer(event_queue, 1.0/FPS);
    al_start_timer(frame_timer);

    while (!done) {
        done = state->calls.update(state);
        if ((state->next != state) && (state->next != NULL)) {/* switch to next state */};

        al_wait_for_event(event_queue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = 1;
            break;
        case ALLEGRO_EVENT_TIMER:
            al_set_target_bitmap(target.buffer);
            al_clear_to_color(al_map_rgb(0, 0, 0));

            state->calls.draw(state);

            al_set_target_backbuffer(target.display);
            /*al_clear_to_color(al_map_rgb(0, 0, 0));*/
            al_draw_scaled_bitmap(target.buffer, 0, 0, GAME_WIDTH, GAME_HEIGHT, 
                                  target.draw_rect.x, target.draw_rect.y, target.draw_rect.w, target.draw_rect.h,
                                  0);
            al_flip_display();
            break;
        default:
            break;
        }
    }

    al_destroy_timer(frame_timer);
    ralph_destroy_render(target);
    al_destroy_event_queue(event_queue);

    return 0;
}