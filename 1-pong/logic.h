void test_ball_collision(BOUNCER *ball_ptr, SHIP *ship_ptr);
int check_collision(BOUNCER *ball_ptr, SHIP *ship_ptr);

void check_all_bricks(BOUNCER *ball_ptr, SHIP *brick_ptr);
int check_brick_collision(BOUNCER *ball_ptr, SHIP *brick_ptr);

int between(int lo, int hi);
float between_f(float lo, float hi);

// --- Lógica de detección de colisiones ------------------------------------------
//
// --- Colisiones entre Ball contra Ship y las Paredes ----------------------------
//
void test_ball_collision(BOUNCER *ball_ptr, SHIP *ship_ptr)
{
    // Si la bola llega al borde inferior, restar una vida y reiniciar
    if (ball_ptr->pos.y > BUFFER_H - (BALL_RADIUS * 2))
    {
        audio_play_explode(0);
        // ball_ptr->pos.x -= (ball_ptr->pos.y - (BUFFER_H - (BALL_RADIUS * 2)));
        // ball_ptr->vy *= -1;
        ball_ptr->pos.x = BUFFER_W / 2;
        ball_ptr->pos.y = BUFFER_H / 2;
        ship_ptr->lives--;
        frames = 0;
        return;
    }

    // Condición de Rebote contra la pared izquierda
    if (ball_ptr->pos.x < 0)
    {
        ball_ptr->pos.x *= -1;
        ball_ptr->vx *= -1;
        audio_play_shot();
        return;
    }

    // Condición de Rebote contra la pared derecha
    if (ball_ptr->pos.x > BUFFER_W - (BALL_RADIUS * 2))
    {
        ball_ptr->pos.x -= (ball_ptr->pos.x - (BUFFER_W - (BALL_RADIUS * 2)));
        ball_ptr->vx *= -1;
        audio_play_shot();
        return;
    }

    // Condición de Rebote contra la pared superior
    if (ball_ptr->pos.y < 0)
    {
        ball_ptr->pos.y *= -1;
        ball_ptr->vy *= -1;
        audio_play_shot();
        return;
    }

    // Condición de Rebote contra Ship
    int diff;
    if (diff = check_collision(ball_ptr, ship_ptr))
    {
        if (diff < 20){
            ball_ptr->vx *= -1;        
        }
        audio_play_shot();
        ball_ptr->vy *= -1;        
        return;
    }
}    

int check_collision(BOUNCER *ball_ptr, SHIP *ship_ptr)
{
    if ( ball_ptr->pos.x > ship_ptr->pos.x && 
         ball_ptr->pos.x < (ship_ptr->pos.x + SHIP_WIDTH) && 
         (ball_ptr->pos.y + BALL_D) > ship_ptr->pos.y
        ) 
    {
        return abs(ball_ptr->pos.x - ship_ptr->pos.x);
    }
    return 0;
}


// --- Colisiones entre Bricks y Ball --------------------------
//
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


// --- Funciones auxiliares de cálculo ------------------------------
//
int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}

float between_f(float lo, float hi)
{
    return lo + ((float)rand() / (float)RAND_MAX) * (hi - lo);
}