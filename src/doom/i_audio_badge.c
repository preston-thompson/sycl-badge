#include "i_sound.h"

const int snd_samplerate = 11025;

void I_InitSound(void) {}

int I_StartSound(int id, int channel, int vol, int sep)
{
    (void)id;
    (void)vol;
    (void)sep;
    return channel;
}

void I_SetMusicVolume(int volume) { (void)volume; }
void I_PauseSong(int handle) { (void)handle; }
void I_ResumeSong(int handle) { (void)handle; }
void I_PlaySong(int handle, int looping) { (void)handle; (void)looping; }
void I_StopSong(int handle) { (void)handle; }
