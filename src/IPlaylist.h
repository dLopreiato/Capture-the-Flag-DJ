#ifndef INCLUDED_IPLAYLIST
#define INCLUDED_IPLAYLIST
#include "Music.h"

class IPlaylist {
public:
    /* Returns the next Music to be played. */
    virtual Music* GetNextMusic() = 0;
};

#endif