
void keyboard_update(ALLEGRO_EVENT *event);
void initialize_objects();
int between(int lo, int hi);

void initialize_objects()
{

    ball.pos.x = between(0,BUFFER_W);
    ball.pos.y = between(0,BUFFER_H / 2);
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

    for (int row = 0; row < BRICKS_ROWS; row++) 
    {
        for (int i = 0; i < BRICKS_IN_ROW; i++)
        {
            brick[row][i].pos.x = i * (BUFFER_W / BRICKS_IN_ROW);
            brick[row][i].pos.y = row * BRICK_H;
            brick[row][i].pos.dx = 0;
            brick[row][i].pos.dy = 0;
            brick[row][i].width = BRICK_W;
            brick[row][i].height = BRICK_H;
            brick[row][i].enabled = true;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        shots[i].pos.x = 0;
        shots[i].pos.y = (SHIP_HEIGHT + BALL_D);
        shots[i].pos.dx = 0;
        shots[i].pos.dy = -3;
        shots[i].enabled = false;
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
        if (event->keyboard.keycode == ALLEGRO_KEY_SPACE){
            key[event->keyboard.keycode] = 0;
        }
        else {
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
        }
        break;

    case ALLEGRO_EVENT_KEY_UP:
        if (event->keyboard.keycode == ALLEGRO_KEY_SPACE){
            key[event->keyboard.keycode] = KEY_RELEASED;
        }
        else {
            key[event->keyboard.keycode] &= KEY_RELEASED;
        }    
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        done = true;
        break;
    }
}