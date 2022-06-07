
void ship_draw(SHIP *ship_ptr);
void ship_update(SHIP *ship_ptr);

void ball_update(BOUNCER *ball_ptr);
void ball_draw(BOUNCER *ball);

void brick_draw(SHIP *brick_ptr);

// --- Update y Render de Objetos ---------------------------------------------------
//

// --- Ship ---------------------------------------------
//
void ship_draw(SHIP *ship_ptr)
{
    // al_draw_filled_rectangle(ship_ptr->pos.x,
    //                          ship_ptr->pos.y,
    //                          ship_ptr->pos.x + ship_ptr->width,
    //                          ship_ptr->pos.y + ship_ptr->height,
    //                          al_map_rgb_f(1, 0, 1));
    al_draw_bitmap(sprites.ship_img, ship_ptr->pos.x, ship_ptr->pos.y, 0);

}

void ship_update(SHIP *ship_ptr)
{

    if (key[ALLEGRO_KEY_LEFT])
        ship_ptr->pos.x -= ship_ptr->pos.dx;
        
    if (key[ALLEGRO_KEY_RIGHT])
        ship_ptr->pos.x += ship_ptr->pos.dx;

    if (ship_ptr->pos.x < 0)
    {
        ship_ptr->pos.x *= -1;
        dx *= -1;
        audio_play_shot();
    }

    if (ship_ptr->pos.x > BUFFER_W - SHIP_WIDTH)
    {
        ship_ptr->pos.x -= (ship_ptr->pos.x - (BUFFER_W - SHIP_WIDTH)) * 2;
        dx *= -1;
        audio_play_shot();
    }

    ship_ptr->pos.x += dx;
    dx *= 0.9;
}

// --- Ball ---------------------------------------------
//
void ball_draw(BOUNCER *ball_ptr)
{
    // al_draw_filled_circle(ball_ptr->pos.x,
    //                       ball_ptr->pos.y,
    //                       ball_ptr->radius,
    //                       al_map_rgb_f(1, 0, 1));                          
    al_draw_bitmap(sprites.ball_img, ball_ptr->pos.x, ball_ptr->pos.y, 0);
}

void ball_update(BOUNCER *ball_ptr)
{
    ball_ptr->pos.x += ball_ptr->pos.dx;
    ball_ptr->pos.y += ball_ptr->pos.dy;
}

// --- Bricks ---------------------------------------------
//
void brick_draw(SHIP *brick_ptr)
{
    for (int i = 0; i < 10; i++)
    {
        if (brick_ptr[i].enabled)
        {
            // al_draw_filled_rectangle(brick_ptr[i].pos.x,
            //                          brick_ptr[i].pos.y,
            //                          brick_ptr[i].pos.x + brick_ptr[i].width,
            //                          brick_ptr[i].pos.y + brick_ptr[i].height,
            //                          al_map_rgb_f(0, 1, 0));

            al_draw_bitmap(sprites.bricks_img[i%2], brick_ptr[i].pos.x, brick_ptr[i].pos.y, 0);

        }
    }
}
