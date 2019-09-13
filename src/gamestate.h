#define STATE_DONE 2

struct state_s {
    int (*init)(struct state_s *state);
    int (*update)(struct state_s *state);
    int (*draw)(struct state_s *state);
    int (*destroy)(struct state_s *state);
    struct state_s* next;
    int status;
};
