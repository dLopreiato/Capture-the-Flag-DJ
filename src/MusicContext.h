#ifndef INCLUDED_MUSIC_CONTEXT
#define INCLUDED_MUSIC_CONTEXT

struct MusicContext {

    /* Constructs a MusicContext object of 0 everything. */
    MusicContext() {
        song = 0;
        measure = 0;
        meter = 0;
        beat = 0;
    }

    /* Constructs a copy of a MusicContext object. */
    MusicContext(MusicContext& copy) {
        song = copy.song;
        measure = copy.measure;
        meter = copy.meter;
        beat = copy.beat;
    }

    /* Defines how many songs have been played. */
    unsigned int song;

    /* Defines how many measures in the song have been played. */
    unsigned int measure;

    /* Defines how many beats to a measure. */
    unsigned int meter;

    /* Defines how many beats in the song have been played. */
    unsigned int beat;
};

#endif