#include "KeyboardController.h"

KeyboardController::KeyboardController(sf::Window* eventWindow, MusicManager* musicManager) :
    eventWindow_(eventWindow), musicManager_(musicManager), pauseStatus_(false),
    lowVolumeStatus_(false) {

}

void KeyboardController::AddPlaylistKey(PlaylistID playlistID, sf::Keyboard::Key keyboardKey) {
    playlistKey_.push_back(std::pair<PlaylistID, sf::Keyboard::Key>(playlistID, keyboardKey));
}

void KeyboardController::Update() {
    sf::Event event;
    while (eventWindow_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            eventWindow_->close();
        }
        if (event.type == sf::Event::KeyReleased) {
            for (unsigned int i = 0; i < playlistKey_.size(); i++) {
                if (event.key.code == playlistKey_[i].second)
                    musicManager_->SetNextPlaylist(playlistKey_[i].first);
            }
            switch (event.key.code) {
            case DEFAULT_PAUSE_KEY: pauseStatus_ = !pauseStatus_;
                musicManager_->SetPause(pauseStatus_);
                break;
            case DEFAULT_NEXT_SONG_KEY: musicManager_->NextSong();
                break;
            case DEFAULT_LOW_VOLUME_KEY: lowVolumeStatus_ = !lowVolumeStatus_;
                musicManager_->SetLowVolume(lowVolumeStatus_);
                break;
            }
        }
    }
}