#include "utils.h"
#include "ralph.h"
#include "gamestate.h"
#include "state_slideshow.h"


#define GAME_WIDTH 240
#define GAME_HEIGHT 320
#define FPS 60


struct ralph_render_target target;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *frame_timer = NULL;


int main(int argc, char *argv[])
{
    int done = 0;

    struct state_s *state = &state_slideshow;

    ralph_init("Zeta", "BluRaf");

    event_queue = ralph_init_event();

    target = ralph_init_render(GAME_WIDTH, GAME_HEIGHT, RALPH_TARGET_FULLSCREEN, 3);

    ralph_event_add_display(event_queue, &target);
    frame_timer = ralph_event_add_timer(event_queue, 1.0/FPS);
    al_start_timer(frame_timer);

    while (!done) {
        log_debug("Initializing state 0x%x", state);
        state->init(state);
        while (state->status != STATE_DONE) {
            al_wait_for_event(event_queue, &event);
            switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = 1;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_set_target_bitmap(target.buffer);
                al_clear_to_color(al_map_rgb(0, 0, 0));

                state->draw(state);

                al_set_target_backbuffer(target.display);
                /*al_clear_to_color(al_map_rgb(0, 0, 0));*/
                al_draw_scaled_bitmap(target.buffer, 0, 0, GAME_WIDTH, GAME_HEIGHT,
                                      target.draw_rect.x, target.draw_rect.y,
                                      target.draw_rect.w, target.draw_rect.h,
                                      0);
                al_flip_display();
                break;
            default:
                break;
            }
            state->update(state);
        }
        log_debug("Destroying state 0x%x", state);
        state->destroy(state);

        if (   (state->next != state)
            && (state->next != NULL)) {
            log_debug("Next state: 0x%x", state->next);
            state = state->next;
        }
        else {
            done = 1;
        }
    }

    al_destroy_timer(frame_timer);
    ralph_destroy_render(target);
    al_destroy_event_queue(event_queue);

    return 0;
}
