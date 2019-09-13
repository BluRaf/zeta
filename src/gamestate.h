struct gamestate {
    int (*init)(struct gamestate *state);
    int (*update)(struct gamestate *state);
    int (*draw)(struct gamestate *state);
    int (*destroy)(struct gamestate *state);
    struct gamestate* next;
    int status;
};
