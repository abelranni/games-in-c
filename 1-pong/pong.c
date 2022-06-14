// Para compilar por comando usando gcc:
// gcc pong.c -o pong.exe -lallegro -lallegro_font -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec
#include "base.h"

int main()
{
    main_init();
    initialize_objects();

    while (1)
    {
        al_wait_for_event(queue, &event);
        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (frames > 30){
                ball_update(ball_ptr);
                ship_update(ship_ptr);
                shots_update(shots_ptr, ship_ptr);
                test_ball_collision(ball_ptr, ship_ptr);
                check_all_bricks(ball_ptr, brick_ptr);
            }
            redraw = true;
            frames++;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            dx += event.mouse.dx * 0.1;
            al_set_mouse_xy(disp, BUFFER_W / 2, BUFFER_W / 2);
            break;
        }

        if (done) break;
        
        keyboard_update(&event);

        if (redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0, 0, 0));
            ball_draw(ball_ptr);
            ship_draw(ship_ptr);
            brick_draw(brick_ptr);
            shots_draw(shots_ptr);
            game_update(ball_ptr, ship_ptr);
            disp_post_draw();
            redraw = false;
        }
    }
    main_destroy();
    return 0;
}
