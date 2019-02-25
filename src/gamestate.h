struct gamestate_calls {
    int (*update)(struct gamestate *state);
    void (*draw)(struct gamestate *state);
};

struct gamestate {
    struct gamestate* next;
    struct gamestate_calls calls;
    int done;
};
