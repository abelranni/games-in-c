void test_ball_collision(BOUNCER *b, float x, float y);
int check_collision(float bx, float by, float x, float y);

void check_all_bricks(BOUNCER *ball_ptr, SHIP *brick_ptr);
int check_brick_collision(BOUNCER *ball_ptr, SHIP *brick_ptr);

// --- Lógica de detección de colisiones ------------------------------------------
//
void test_ball_collision(BOUNCER *ball_ptr, float x, float y)
{
    if (ball_ptr->pos.x < 0)
    {
        ball_ptr->pos.x *= -1;
        ball_ptr->pos.dx *= -1;
        audio_play_shot();
    }
    if (ball_ptr->pos.x > BUFFER_W - (BALL_RADIUS * 2))
    {
        ball_ptr->pos.x -= (ball_ptr->pos.x - (BUFFER_W - (BALL_RADIUS * 2)));
        ball_ptr->pos.dx *= -1;
        audio_play_shot();
    }
    if (ball_ptr->pos.y < 0)
    {
        ball_ptr->pos.y *= -1;
        ball_ptr->pos.dy *= -1;
        audio_play_shot();
    }
    if (ball_ptr->pos.y > BUFFER_H - (BALL_RADIUS * 2))
    {
        if (check_collision(ball_ptr->pos.x, ball_ptr->pos.y, x, y))
        {
            audio_play_shot();
        }
        else
        {
            audio_play_explode(0);
        }
        ball_ptr->pos.x -= (ball_ptr->pos.y - (BUFFER_H - (BALL_RADIUS * 2)));
        ball_ptr->pos.dy *= -1;
    }
}

int check_collision(float bx, float by, float x, float y)
{
    if (bx > x && bx < x + 100 && by > y && by < y + 50)
    {
        return 1;
    }
    return 0;
}

void check_all_bricks(BOUNCER *ball_ptr, SHIP *brick_ptr)
{

    for (int i = 0; i < 10; i++)
    {
        if (brick_ptr[i].enabled)
        {
            if (check_brick_collision(ball_ptr, &(brick_ptr[i])))
            {
                brick_ptr[i].enabled = false;
            }
        }
    }
}

int check_brick_collision(BOUNCER *ball_ptr, SHIP *brick_ptr)
{
    if (ball_ptr->pos.x > brick_ptr->pos.x &&
        ball_ptr->pos.x < brick_ptr->pos.x + brick_ptr->width &&
        ball_ptr->pos.y < brick_ptr->pos.y + brick_ptr->height)
    {
        return 1;
    }
    return 0;
}