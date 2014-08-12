#ifndef INCLUDED_IPLAYLIST
#define INCLUDED_IPLAYLIST
#include "MusicMetadata.h"

class IPlaylist {
public:
    /* Returns the next Music to be played. */
    virtual MusicMetadata* GetNextMusic() = 0;
};

#endif