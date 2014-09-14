#ifndef INCLUDED_KEYBOARD_CONTROLLER
#define INCLUDED_KEYBOARD_CONTROLLER
#define DEFAULT_PAUSE_KEY       sf::Keyboard::Space
#define DEFAULT_NEXT_SONG_KEY   sf::Keyboard::Return
#define DEFAULT_LOW_VOLUME_KEY  sf::Keyboard::Z
#include "SFML\Graphics.hpp"
#include "MusicManager.h"
#include <vector>

class KeyboardController {
public:
    KeyboardController(sf::Window* eventWindow, MusicManager* musicManager);
    //void SetPauseButton(sf::Keyboard::Key key);
    //void SetLowVolumeButton(sf::Keyboard::Key key);

    /* Binds a key to a given playlist id. */
    void AddPlaylistKey(PlaylistID playlistID, sf::Keyboard::Key keyboardKey);

    /* Must be run while the window is open to poll for keyboard input. */
    void Update();
private:
    sf::Window* eventWindow_;
    MusicManager* musicManager_;
    sf::Keyboard::Key pauseButton_;
    sf::Keyboard::Key lowVolumeButton_;
    bool pauseStatus_;
    bool lowVolumeStatus_;
    std::vector<std::pair<PlaylistID, sf::Keyboard::Key>> playlistKey_;
};

#endif