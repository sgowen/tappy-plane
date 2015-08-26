#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>
#include "sfx.h"
#include "filesystem.h"

SFX_s SFX[NUMSFX];

bool soundEnabled;

void initSound()
{
    int i;
    for (i = 0; i < NUMSFX; i++)
    {
        SFX[i].used = false;
    }

    if (csndInit() == 0)soundEnabled = true;
    else soundEnabled = false;
}

void exitSound(void)
{
    int i;
    for (i = 0; i < NUMSFX; i++)
    {
        if (SFX[i].used)
        {
            if (SFX[i].data)
            {
                linearFree(SFX[i].data);
                SFX[i].data = NULL;
            }
            SFX[i].used = false;
        }
    }
    if (soundEnabled)csndExit();
}

void initSFX(SFX_s* s)
{
    if (!s)return;

    s->data = NULL;
    s->size = 0;
    s->used = true;
}

void loadSFX(SFX_s* s, char* filename, u32 format)
{
    if (!s)return;

    initSFX(s);

    s->data = bufferizeFile(filename, &s->size, true, true);
    s->format = format;
}

SFX_s* createSFX(char* filename, u32 format)
{
    int i;
    for (i = 0; i < NUMSFX; i++)
    {
        if (!SFX[i].used)
        {
            loadSFX(&SFX[i], filename, format);

            if (!SFX[i].data)return NULL;
            return &SFX[i];
        }
    }
    return NULL;
}

int channel;
int musicChannel = -1;

void playSFXOnChannel(SFX_s* s, int channel)
{
    if (!s || !s->used || !s->data || !soundEnabled)return;

    csndPlaySound(channel + 8, s->format, 22050, 1.0, 0.0, (u32*) s->data, (u32*) s->data, s->size);
}

void playSFX(SFX_s* s)
{
    channel++;
    channel %= 8;
    if (channel == musicChannel)
    {
        channel++;

        if (channel > 7)
        {
            channel = 0;
        }
    }

    playSFXOnChannel(s, channel);
}

void playMusic(SFX_s* s)
{
    if (musicChannel == -1)
    {
        playSFX(s);

        musicChannel = channel;
    }
    else
    {
        playSFXOnChannel(s, musicChannel);
    }
}