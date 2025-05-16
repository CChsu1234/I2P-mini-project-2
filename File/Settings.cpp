#include <cstdio>

#include "Settings.hpp"

Settings::Settings(void) {
    FILE *fr = fopen("Resource/settings.txt", "r");

    int temp_sfx;
    int temp_bgm;
    fscanf(fr, "%d\n%d\n", &temp_bgm, &temp_sfx);

    bgm_volume = temp_bgm * 0.01;
    if (bgm_volume > 1.0) {
        bgm_volume = 1.0;
    }
    if (bgm_volume < 0) {
        bgm_volume = 0;
    }
    sfx_volume = temp_sfx * 0.01;
    if (sfx_volume > 1.0) {
        sfx_volume = 1.0;
    }
    if (sfx_volume < 0) {
        sfx_volume = 0;
    }
    AudioHelper::BGMVolume = bgm_volume;
    AudioHelper::SFXVolume = sfx_volume;
    fclose(fr);
}
void Settings::Save(void) {
    FILE *fw = fopen("Resource/settings.txt", "w");
    
    bgm_volume = AudioHelper::BGMVolume;
    sfx_volume = AudioHelper::SFXVolume;
    int temp_bgm = bgm_volume * 100;
    int temp_sfx = sfx_volume * 100;

    fprintf(fw, "%d\n%d\n", temp_bgm, temp_sfx);

    fclose(fw);
}
