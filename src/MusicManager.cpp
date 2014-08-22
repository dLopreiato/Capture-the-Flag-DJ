#include "MusicManager.h"
#include <assert.h>
#define FULL_VOLUME 1.0f
#define LOW_VOLUME 0.3f
#define MUTE_VOLUME 0.0f

MusicManager::MusicManager() : currentMusic_(nullptr), currentPauseFader_(MUTE_VOLUME),
    currentTalkFader_(FULL_VOLUME), currentTimeFader_(FULL_VOLUME),
    defaultFadeDuration_(sf::milliseconds(1300)), goalPauseFader_(MUTE_VOLUME),
    goalTalkFader_(FULL_VOLUME), musicContext_(), nextPlaylist_(0), paused_(true), playlists_(),
    previousMusic_(nullptr), previousTimeFader_(FULL_VOLUME) {

}

MusicManager::~MusicManager() {

}

void MusicManager::Update(sf::Time elapsedTime) {
    assert(playlists_[0] != nullptr);
    assert(goalPauseFader_ <= FULL_VOLUME);
    assert(goalPauseFader_ >= MUTE_VOLUME);

    // check if the current song needs to start fading and a new one should start playing
    if (currentMusic_->GetTimeToEnd() <= defaultFadeDuration_) {
        NextSong();
    }

    // check if previous song has ended
    if (previousMusic_ != nullptr && (previousMusic_->IsFinished() || previousTimeFader_ <= 0.0f)) {
        // delete it
        ClearPrevious();
    }

    // adjust pause fade
    currentPauseFader_ = AdjustFader(currentPauseFader_, goalPauseFader_, elapsedTime,
        MUTE_VOLUME, FULL_VOLUME);

    // pause the song if it has faded completely down
    if (currentPauseFader_ <= MUTE_VOLUME) {
        currentMusic_->Pause();
        currentMusic_->SetToPauseMarker();
    }

    // adjust talk fade
    currentTalkFader_ = AdjustFader(currentTalkFader_, goalTalkFader_, elapsedTime,
        LOW_VOLUME, FULL_VOLUME);

    // adjust individual time fades
    currentTimeFader_ = AdjustFader(currentTimeFader_, FULL_VOLUME, elapsedTime,
        MUTE_VOLUME, FULL_VOLUME);
    if (previousMusic_ != nullptr) {
        previousTimeFader_ = AdjustFader(previousTimeFader_, MUTE_VOLUME, elapsedTime,
            MUTE_VOLUME, FULL_VOLUME);
    }
    
    // set the final fades of the songs
    currentMusic_->SetVolume(currentPauseFader_ * currentTalkFader_ * currentTimeFader_);
    if (previousMusic_ != nullptr) {
        previousMusic_->SetVolume(currentPauseFader_ * currentTalkFader_ * previousTimeFader_);
    }
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
            currentMusic_->Play();
        }
    }
}

void MusicManager::SetLowVolume(bool lowVolume) {
    goalTalkFader_ = (lowVolume) ? (LOW_VOLUME) : (FULL_VOLUME);
}

void MusicManager::NextSong() {
    // stop music in previous song area if any is playing
    ClearPrevious();
    // make previousSong what currentSong is
    previousMusic_ = currentMusic_;
    // make currentSong whatever comes next from the next playlist, and start it
    currentMusic_ = playlists_[nextPlaylist_]->GetNextMusic();
    StartCurrent();
    currentTimeFader_ = MUTE_VOLUME;
    previousTimeFader_ = FULL_VOLUME;
}

void MusicManager::SetNextPlaylist(PlaylistID playlistId) {
    nextPlaylist_ = playlistId;
}

PlaylistID MusicManager::AddPlaylist(IPlaylist* playlist) {
    // note that this makes every id to be 1 more than its index
    int thisIndex = playlists_.size();
    playlists_.push_back(playlist);

    if (thisIndex == 0) {
        nextPlaylist_ = thisIndex;
        NextSong();
    }

    return thisIndex;
}

void MusicManager::ClearPrevious() {
    if (previousMusic_ != nullptr) {
        delete previousMusic_;
        previousMusic_ = nullptr;
    }
}

void MusicManager::StartCurrent() {
    assert(currentMusic_ != nullptr);
    currentMusic_->SetVolume(MUTE_VOLUME);
    currentMusic_->Play();
}

float MusicManager::AdjustFader(float currentVolume, float goalVolume, sf::Time elapsedTime,
    float lowestVolume, float highestVolume) {

    assert(defaultFadeDuration_.asMilliseconds() != 0);

    // if it needs to change
    if (currentVolume != goalVolume) {
        if (currentVolume > goalVolume) {
            // needs to fade down
            currentVolume -= (highestVolume - lowestVolume)
                * (elapsedTime.asSeconds() / defaultFadeDuration_.asSeconds());
        }
        else {
            // needs to fade up
            currentVolume += (highestVolume - lowestVolume)
                * (elapsedTime.asSeconds() / defaultFadeDuration_.asSeconds());
        }

        // keep within bounds
        if (currentVolume > highestVolume)
            currentVolume = highestVolume;

        if (currentVolume < lowestVolume)
            currentVolume = lowestVolume;
    }

    return currentVolume;
}