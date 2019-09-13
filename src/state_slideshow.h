#ifndef STATE_SLIDESHOW_H
#define STATE_SLIDESHOW_H

int state_slideshow_init(struct state_s *state);
int state_slideshow_update(struct state_s *state);
int state_slideshow_draw(struct state_s *state);
int state_slideshow_destroy(struct state_s *state);

struct state_s state_slideshow;

#endif
