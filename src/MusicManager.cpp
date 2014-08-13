#include "MusicManager.h"
#include <assert.h>
#define FULL_VOLUME 1.0f
#define LOW_VOLUME 0.3f
#define MUTE_VOLUME 0.0f

MusicManager::MusicManager() : currentMusic_(nullptr), currentPauseFader_(MUTE_VOLUME),
    currentTalkFader_(FULL_VOLUME), defaultFadeDuration_(sf::milliseconds(1300)),
    goalPauseFader_(MUTE_VOLUME), goalTalkFader_(FULL_VOLUME), musicContext_(), nextPlaylist_(0),
    paused_(true), playlists_(), previousMusic_(nullptr) {

}

MusicManager::~MusicManager() {

}

void MusicManager::Update() {
    assert(nextPlaylist_ != 0);
    // check if the current song has ended
        // move current to previous
        // get new current

    // check if previous song has ended
        // delete it

    // adjust pause fade

    // pause the song if it has faded completely down

    // adjust talk fade

    // adjust the final fades of the songs

}

const MusicContext* MusicManager::GetContext() {
    return &musicContext_;
}

void MusicManager::SetPause(bool paused) {
    paused_ = paused;
    goalPauseFader_ = (paused) ? (MUTE_VOLUME) : (FULL_VOLUME);
    if (paused) {
        // update the pause marker
        currentMusic_->UpdatePauseMarker();
    }
    else {
        // set the song back to where we started pausing ONLY IF THE SONG HAS BEEN 100% FADED
        if (currentPauseFader_ <= MUTE_VOLUME) {
            currentMusic_->SetToPauseMarker();
            currentMusic_->music->play();
        }
    }
}

void MusicManager::SetLowVolume(bool lowVolume) {
    goalTalkFader_ = (lowVolume) ? (LOW_VOLUME) : (FULL_VOLUME);
}

void MusicManager::NextSong() {
    // stop music in previous song area if any is playing
    if (previousMusic_ != nullptr) {
        previousMusic_->music->stop();
        // delete previous song meta data
        delete previousMusic_->music;
        delete previousMusic_;
        previousMusic_ = nullptr;
    }
    // make previousSong what currentSong is
    previousMusic_ = currentMusic_;
    // make currentSong whatever comes next from the next playlist, and start it
    currentMusic_ = playlists_[nextPlaylist_]->GetNextMusic();
    currentMusic_->music->setVolume(MUTE_VOLUME);
    currentMusic_->music->setPlayingOffset(currentMusic_->fadeInOffset);
    currentMusic_->music->play();
    currentMusic_->wasStarted = true;
}

void MusicManager::SetNextPlaylist(PlaylistID playlistId) {
    nextPlaylist_ = playlistId;
}

PlaylistID MusicManager::AddPlaylist(IPlaylist* playlist) {
    playlists_.push_back(playlist);

    // note that this makes every id to be 1 more than its index
    int thisIndex = playlists_.size();

    if (thisIndex == 0) {
        nextPlaylist_ = thisIndex;
        NextSong();
    }

    return thisIndex;
}