//--- Variables Globales -----------------------------------------------------------
//
BOUNCER ball;
BOUNCER *ball_ptr = &ball;

SHIP ship;
SHIP *ship_ptr = &ship;

SHIP brick[BRICKS_IN_ROW];
SHIP *brick_ptr = brick;

float dx = 0;
bool done = false;
bool redraw = true;
long frames = 0;
long lives = 3;

