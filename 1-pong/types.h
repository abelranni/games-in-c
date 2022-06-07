
typedef struct POSITION
{
    float x, y;
    float dx, dy;
} POSITION;

typedef struct BOUNCER
{
    POSITION pos;
    int radius;
} BOUNCER;

typedef struct SHIP
{
    POSITION pos;
    int width;
    int height;
    int enabled;
} SHIP;
