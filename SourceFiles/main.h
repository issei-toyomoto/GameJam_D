#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GAME_NAME "ゲーム名未決定"

#include <stdio.h>
#include <math.h>
#include <string>
using std::string;
using std::to_string;
#include <time.h>
#include "SceneManager.h"

#include "PadInput.h"

#include "DxLib.h"

// 各シーンのヘッダーファイル
#include "Title.h"
#include "GameMainScene.h"
#include "Result.h"
#include "Help.h"
#include "Ranking.h"

#define IMG 0
#define SND 1

#define BGM 0
#define SE 1

#define TITLE 0
#define MAIN 1

class Resources {
private:
    static int bgm_title;
    static int bgm_main;
    static int se_cursor;
    static int se_select;
public:
    int Get(int media, int type, int getNum) {
        if (media == 1) {
            if (type == 0) {
                if (getNum == 0) {
                    return bgm_title;
                } else if (getNum == 1) {
                    return bgm_main;
                }
            }
            else if (type == 1) {

            };
        }
    };
    void Set(int media, int type, int getNum, int data) {
        if (media == 1) {
            if (type == 0) {
                if (getNum == 0) {
                    bgm_title = data;
                }
                else if (getNum == 1) {
                    bgm_main = data;
                }
            }
            else if (type == 1) {

            };
        }
    };
};