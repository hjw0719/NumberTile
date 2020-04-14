#ifndef UTIL_H
#define UTIL_H

#define PAGE_SIZE_WIDTH 300
#define PAGE_SIZE_HEIGHT 500

enum ETileState
{
    vacancy = 0,
    occupy
};

struct Tile
{
    int number = 0;
    ETileState eState = vacancy;
    Tile()
    {
        number = 0;
        eState = vacancy;
    }
};

class Util
{
public:
    Util();
};

#endif // UTIL_H
