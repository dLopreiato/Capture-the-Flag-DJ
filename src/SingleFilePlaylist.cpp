#include "SingleFilePlaylist.h"

SingleFilePlaylist::SingleFilePlaylist(irrklang::ISoundEngine* engine, char* filename) :
    engine_(engine),  filename_(filename) {
}

SingleFilePlaylist::~SingleFilePlaylist() {
}

Music* SingleFilePlaylist::GetNextMusic() {
    return new Music(engine_->play2D(filename_, false, true, true));
}