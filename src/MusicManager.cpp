#include "MusicManager.h"
#define FULL_VOLUME 1.0f
#define LOW_VOLUME .3f

MusicManager::MusicManager() : currentMusic_(nullptr), defaultFadeDuration_(sf::milliseconds(1300)),
    goalVolumeMultiplier_(FULL_VOLUME), globalVolumeMultiplier_(FULL_VOLUME), musicContext_(),
    nextPlaylist_(0), paused_(true), pauseStateChangeReady_(true), playlists_(),
    previousMusic_(nullptr) {

}

MusicManager::~MusicManager() {

}

void MusicManager::Update() {

}

const MusicContext* MusicManager::GetContext() {
    return &musicContext_;
}

void MusicManager::SetPause(bool paused) {
    if (!paused)
        currentMusic_->music->play();

    /*if (pauseStateChangeReady_) {
        paused_ = paused;
        pauseStateChangeReady_ = false;
    }*/
    // if it can't change state, we'll silently fail
}

void MusicManager::SetLowVolume(bool lowVolume) {
    goalVolumeMultiplier_ = (lowVolume) ? (LOW_VOLUME) : (FULL_VOLUME);
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
    //currentMusic_->music->setVolume(0.0f);
    sf::Time offset = (currentMusic_->fadeInOffset >= defaultFadeDuration_) ?
        (currentMusic_->fadeInOffset - defaultFadeDuration_) : (sf::microseconds(0));
    currentMusic_->music->setPlayingOffset(offset);
    currentMusic_->music->play();
    currentMusic_->wasStarted = true;
}

void MusicManager::SetNextPlaylist(PlaylistID playlistId) {
    nextPlaylist_ = playlistId;
}

PlaylistID MusicManager::AddPlaylist(IPlaylist* playlist) {
    int thisIndex = playlists_.size();
    playlists_.push_back(playlist);

    if (thisIndex == 0)
        nextPlaylist_ = thisIndex;

    return thisIndex;
}