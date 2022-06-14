
typedef struct POSITION
{
    float x, y;
    float dx, dy;
} POSITION;

typedef struct BOUNCER
{
    POSITION pos;
    float vx, vy;
    int enabled;
    int radius;
} BOUNCER;

typedef struct SHIP
{
    POSITION pos;
    float vx, vy;
    int width;
    int height;
    int enabled;
    int lives;
} SHIP;
