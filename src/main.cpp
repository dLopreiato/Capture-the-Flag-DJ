#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "KeyboardController.h"
#include "MusicManager.h"
#include "Music.h"
#include "JsonPlaylist.h"
#define CALM_PLAYLIST   "calm.json"
#define CALM_KEY        sf::Keyboard::Q
#define LOUD_PLAYLIST   "loud.json"
#define LOUD_KEY        sf::Keyboard::E
#define DROP_PLAYLIST   "drop.json"
#define DROP_KEY        sf::Keyboard::W

int main() {
    // start up sound portion of program
    irrklang::ISoundEngine* irrklangEngine = irrklang::createIrrKlangDevice();
    if (!irrklangEngine)
        return 0x01;
     
    sf::Clock applicationClock = sf::Clock();
    sf::Time applicationRefreshTime = sf::milliseconds(100);
    MusicManager applicationSound = MusicManager(sf::milliseconds(500));

    JsonPlaylist calmPlaylist = JsonPlaylist(irrklangEngine, CALM_PLAYLIST);
    PlaylistID calmID = applicationSound.AddPlaylist(&calmPlaylist);

    JsonPlaylist loudPlaylist = JsonPlaylist(irrklangEngine, LOUD_PLAYLIST);
    PlaylistID loudID = applicationSound.AddPlaylist(&loudPlaylist);

    JsonPlaylist dropPlaylist = JsonPlaylist(irrklangEngine, DROP_PLAYLIST);
    PlaylistID dropID = applicationSound.AddPlaylist(&dropPlaylist);
    
    // start up visual portion of program
    sf::Window window(sf::VideoMode(800, 600), "CTF Controls");
    
    // start up controller portion of program
    KeyboardController keyboardController = KeyboardController(&window, &applicationSound);
    keyboardController.AddPlaylistKey(calmID, CALM_KEY);
    keyboardController.AddPlaylistKey(loudID, LOUD_KEY);
    keyboardController.AddPlaylistKey(dropID, DROP_KEY);

    applicationSound.SetPause(false);

    sf::Time elapsedTime;
    while (window.isOpen()) {
        keyboardController.Update();

        // update the sound portion
        if (applicationRefreshTime < applicationClock.getElapsedTime()) {
            elapsedTime = applicationClock.restart();

            applicationSound.Update(elapsedTime);
        }
    }

    return 0;
}