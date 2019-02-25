#include "ralph.h"
#include "utils.h"

void ralph_init(const char *game_name, const char *game_org)
{
    al_set_app_name(game_name);
    al_set_org_name(game_org);

    /* Allegro initialisation */
    if (!al_init()) die("Allegro cannot be initialised!");

    /* Get used Allegro version */
    uint32_t liballeg_ver_value = al_get_allegro_version();
    int liballeg_ver[4];
    liballeg_ver[0] = liballeg_ver_value >> 24;
    liballeg_ver[1] = (liballeg_ver_value >> 16) & 255;
    liballeg_ver[2] = (liballeg_ver_value >> 8) & 255;
    liballeg_ver[3] = liballeg_ver_value & 255;
    log_info("Using Allegro %d.%d.%d[%d]", liballeg_ver[0], liballeg_ver[1], liballeg_ver[2], liballeg_ver[3]);

    for (int i=0; i<7; i++)
        log_debug("path %d: %s", i, al_path_cstr(al_get_standard_path(i), ALLEGRO_NATIVE_PATH_SEP));

    /* Addon initialisation */
    if (!al_init_image_addon()) die("Allegro image addon cannot be initialised!");
}


ALLEGRO_EVENT_QUEUE* ralph_init_event()
{
    /* Event pipeline */
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
    if (queue == NULL) {
        die("Failed to create event queue!");
    }
    return queue;
}

void ralph_event_add_display(ALLEGRO_EVENT_QUEUE *queue, struct ralph_render_target *target)
{
    al_register_event_source(queue, al_get_display_event_source((*target).display));
}


ALLEGRO_TIMER* ralph_event_add_timer(ALLEGRO_EVENT_QUEUE *queue, float time)
{
    /* Frame timer */
    ALLEGRO_TIMER * new_timer = al_create_timer(time);
    if (new_timer == NULL) {
        die("Failed to create timer %f!", time);
    }

    al_register_event_source(queue, al_get_timer_event_source(new_timer));
    return new_timer;
}


void ralph_destroy_render(struct ralph_render_target target)
{
    al_destroy_bitmap(target.buffer);
    al_destroy_display(target.display);
}


struct ralph_render_target ralph_init_render(int width, int height, char flags, unsigned int scale)
{
    struct ralph_render_target target;

    /* Scale calculation */
    if (scale < 1) scale = 1;
    target.draw_rect.w = width * scale;
    target.draw_rect.h = height * scale;
    log_debug("Requested: %dx%d @ %dx%d", target.draw_rect.w, target.draw_rect.h, 0, 0);


    /* Display creation */
    if (flags & RALPH_TARGET_FULLSCREEN) al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    target.display = al_create_display(target.draw_rect.w, target.draw_rect.h);
    if (target.display == NULL) {
        die("Failed to create display!");
    }

    /* Buffer creation */
    target.buffer = al_create_bitmap(width, height);
    if (target.buffer == NULL) {
        die("Failed to create rendering buffer!");
    }
    log_debug("Internal: %dx%d @ %dx%d", width, height, 0, 0);

    /* Recalculate drawing scale to fit whole buffer on screen */
    unsigned int sx = al_get_display_width(target.display) / width;
    unsigned int sy = al_get_display_height(target.display) / height;
    scale = stb_min(sx, sy);

    /* Recalculate */
    target.draw_rect.w = width * scale;
    target.draw_rect.h = height * scale;
    target.draw_rect.x = (al_get_display_width(target.display) - target.draw_rect.w) / 2;
    target.draw_rect.y = (al_get_display_height(target.display) - target.draw_rect.h) / 2;

    log_debug("Scaled: %dx%d @ %dx%d", target.draw_rect.w, target.draw_rect.h, target.draw_rect.x, target.draw_rect.y);

    /* Clear window */
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    return target;
}
