#pragma once

//スクリーンサイズ(縦・横)
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define SCREEN_COLOR_BIT_16 16

//マップブロック数(縦・横)
#define MAP_HEIGHT 12
#define MAP_WIDTH 25

//UI枠のサイズ
#define UI_SIZE 100

//ブロック1つのサイズ(正方形)
#define BLOCK_SIZE 50

//フィールドの余白
#define MARGIN_X SCREEN_WIDTH % BLOCK_SIZE / 2
#define MARGIN_Y (SCREEN_HEIGHT - 100) % BLOCK_SIZE / 2

//花、草のマップ上での数
#define FLOWER_NUM 30
#define WEED_NUM 10