
void keyboard_update(ALLEGRO_EVENT *event);
void initialize_objects();

void initialize_objects()
{

    ball.pos.x = BUFFER_W / 2;
    ball.pos.y = BUFFER_H / 2;
    ball.pos.dx = BALL_SPEED;
    ball.pos.dy = BALL_SPEED * 2;
    ball.vx = ball.pos.dx;
    ball.vy = ball.pos.dy;
    ball.radius = BALL_RADIUS;

    ship.pos.x = BUFFER_W / 2;
    ship.pos.y = BUFFER_H - SHIP_HEIGHT;
    ship.pos.dx = SHIP_WIDTH / 10;
    ship.pos.dy = 0;
    ship.vx = 0;
    ship.vy = 0;
    ship.width = SHIP_WIDTH;
    ship.height = SHIP_HEIGHT;
    ship.lives = lives;

    for (int i = 0; i < BRICKS_IN_ROW; i++)
    {
        brick[i].pos.x = i * (BUFFER_W / BRICKS_IN_ROW);
        brick[i].pos.y = 0;
        brick[i].pos.dx = 0;
        brick[i].pos.dy = 0;
        brick[i].width = BRICK_W;
        brick[i].height = BRICK_H;
        brick[i].enabled = true;
    }
}

void keyboard_update(ALLEGRO_EVENT *event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        if (key[ALLEGRO_KEY_ESCAPE])
            done = true;
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= KEY_RELEASED;
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }
}