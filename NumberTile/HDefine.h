#ifndef HDEFINE_H
#define HDEFINE_H

// Tile
#define TILE_COUNT 8

#define LIFE_MAX_TIME 5000
#define LIFE_ADD_INTERVAL_INIT 1000
#define LIFE_ADD_INTERVAL_REDUCE_SIZE 2
#define LIFE_ADD_INTERVAL_MIN 150
#define LIFE_REDUCE_INTERVAL 1000

#define CANCEL_COMBO_INTERVAL 1500
#define FEVER_INTERVAL 5000
#define READY_COUNT_MAX 3

// Score
#define DEFAULT_SCORE 100
#define FEVER_SCORE DEFAULT_SCORE * 2


#define COMBO_FOR_FEVER 30

// WINDOW OS
#define DESKTOP_OS_WIDTH 300
#define DESKTOP_OS_HEIGHT 600

// Sound Setting

#define SOUND_VOUME_DEFAULT 0.5
#define SOUND_URL_TILE_TOUCH_FAIL "qrc:/sound/tile_touch_fail.WAV"
#define SOUND_URL_TILE_TOUCH_SUCCESS "qrc:/sound/tile_touch_success.WAV"

// font file path
#define FONT_NORMAL_PATH ":/font/nanumgothiccoding.ttf"
#define FONT_BOLD_PATH ":/font/nanumgothiccodingbold.ttf"
#define FONT_NUMBER_PATH ":/font/numberFont.ttf"

#endif // HDEFINE_H


