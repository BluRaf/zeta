#ifndef GAMESTATE_INTRO_H
#define GAMESTATE_INTRO_H

int gamestate_intro_init(struct gamestate *state);
int gamestate_intro_update(struct gamestate *state);
int gamestate_intro_draw(struct gamestate *state);
int gamestate_intro_destroy(struct gamestate *state);

struct gamestate gamestate_intro;

#endif
