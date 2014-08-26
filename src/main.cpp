#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "MusicManager.h"
#include "Music.h"
#include "JsonPlaylist.h"
#define CALM_PLAYLIST "calm.json"
#define LOUD_PLAYLIST "loud.json"
#define DROP_PLAYLIST "drop.json"

int main()
{
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
    
    //start up visual portion of program
    sf::Window window(sf::VideoMode(800, 600), "CTF Controls");
    bool pauseStatus = false;
    bool lowVolStatus = false;

    applicationSound.SetPause(pauseStatus);

    sf::Time elapsedTime;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Space: pauseStatus = !pauseStatus;
                    applicationSound.SetPause(pauseStatus);
                    break;
                case sf::Keyboard::Return: applicationSound.NextSong();
                    break;
                case sf::Keyboard::Q: applicationSound.SetNextPlaylist(calmID);
                    break;
                case sf::Keyboard::W: applicationSound.SetNextPlaylist(dropID);
                    break;
                case sf::Keyboard::E: applicationSound.SetNextPlaylist(loudID);
                    break;
                case sf::Keyboard::Z: lowVolStatus = !lowVolStatus;
                    applicationSound.SetLowVolume(lowVolStatus);
                    break;
                }
            }
        }

        // update the sound portion
        if (applicationRefreshTime < applicationClock.getElapsedTime()) {
            elapsedTime = applicationClock.restart();

            applicationSound.Update(elapsedTime);
        }
    }

    return 0;
}