
void ship_draw(SHIP *ship_ptr);
void ship_update(SHIP *ship_ptr);

void ball_update(BOUNCER *ball_ptr);
void ball_draw(BOUNCER *ball);

void brick_draw(SHIP *brick_ptr);
void game_update(BOUNCER *ball_ptr, SHIP *ship_ptr);

void shots_update(BOUNCER *shots_ptr, SHIP *ship_ptr);
void shots_draw(BOUNCER *shots_ptr);

// --- Update y Render de Objetos ---------------------------------------------------
//

// --- Ship ---------------------------------------------
//
void ship_draw(SHIP *ship_ptr)
{
    if(ship.lives < 0)
        return;    
    al_draw_bitmap(sprites.ship_img, ship_ptr->pos.x, ship_ptr->pos.y, 0);
}

void ship_update(SHIP *ship_ptr)
{

    if(ship_ptr->lives < 0)
        return;

    if (key[ALLEGRO_KEY_LEFT]) {
        ship_ptr->vx = (-1)*ship_ptr->pos.dx;
    }
        
    if (key[ALLEGRO_KEY_RIGHT]) {
        ship_ptr->vx = ship_ptr->pos.dx;
    }

    if (key[ALLEGRO_KEY_UP]) {
        ship_ptr->pos.dx *= 1.1;
    }
    if (key[ALLEGRO_KEY_DOWN]) {
        ship_ptr->pos.dx *= 0.9;
    }

    if (ship_ptr->pos.x < 0)
    {
        ship_ptr->pos.x *= (-1);
        ship_ptr->vx = ship_ptr->pos.dx;
        audio_play_shot();
    }

    if (ship_ptr->pos.x > BUFFER_W - SHIP_WIDTH)
    {
        ship_ptr->pos.x -= (ship_ptr->pos.x - (BUFFER_W - SHIP_WIDTH)) * 2;
        ship_ptr->vx = (-1)*ship_ptr->pos.dx;
        audio_play_shot();
    }

    ship_ptr->pos.x += ship_ptr->vx;
    ship_ptr->vx *= 0.8;
}

// --- Ball ---------------------------------------------
//
void ball_draw(BOUNCER *ball_ptr)
{                  
    al_draw_bitmap(sprites.ball_img[0], ball_ptr->pos.x, ball_ptr->pos.y, 0);
}

void ball_update(BOUNCER *ball_ptr)
{
    ball_ptr->pos.x += ball_ptr->vx;
    ball_ptr->pos.y += ball_ptr->vy;
}

// --- Bricks ---------------------------------------------
//
void brick_draw(SHIP *brick_ptr)
{
    for (int i = 0; i < BRICKS_IN_ROW; i++)
    {
        if (brick_ptr[i].enabled)
        {
            al_draw_bitmap(sprites.bricks_img[i%4], brick_ptr[i].pos.x, brick_ptr[i].pos.y, 0);

        }
    }
}
// --- Shots ---------------------------------------------
//
void shots_update(BOUNCER *shots_ptr, SHIP *ship_ptr)
{
    for (int i = 0; i < 10; i++)
    {
        if (shots_ptr[i].enabled)
        {
            shots_ptr[i].pos.y += shots_ptr[i].vy;
            if (shots_ptr[i].pos.y < BALL_D)
            {
                shots_ptr[i].enabled = false;
            }
        }
    }    

    if (key[ALLEGRO_KEY_SPACE]) {

        for (int i = 0; i < 10; i++)
        {
            if (!shots_ptr[i].enabled)
            {
                shots_ptr[i].pos.x = ship_ptr->pos.x + SHIP_WIDTH / 2;
                shots_ptr[i].pos.y = (BUFFER_H - BALL_D - BRICK_H);
                shots_ptr[i].pos.dx = 0;
                shots_ptr[i].vy = -5;
                shots_ptr[i].enabled = true;
                return;
            }
        }
    }


}

void shots_draw(BOUNCER *shots_ptr)
{
   for (int i = 0; i < 10; i++)
    {
        if (shots_ptr[i].enabled)
        {
            al_draw_bitmap(sprites.ball_img[1], shots_ptr[i].pos.x, shots_ptr[i].pos.y, 0);
        }
    }    
}

// --- Game ----------------------------------------------
//
void game_update(BOUNCER *ball_ptr, SHIP *ship_ptr) 
{
    if(ship_ptr->lives < 0) {

        al_draw_text(
            font,
            al_map_rgb_f(1,1,1),
            BUFFER_W / 2, BUFFER_H / 2,
            ALLEGRO_ALIGN_CENTER,
            "G A M E  O V E R"
        );

        ball_ptr->vx = 0;
        ball_ptr->vy = 0;        
    }

}