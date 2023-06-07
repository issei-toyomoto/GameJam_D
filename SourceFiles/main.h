#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define GAME_NAME "老害予備軍！カマを持った花さかじいさん"

#include <stdio.h>
#include <math.h>
#include <string>
using std::string;
using std::to_string;
#include <time.h>
#include "SceneManager.h"

#include "DxLib.h"

// 各シーンのヘッダーファイル
#include "Title.h"
#include "GameMainScene.h"
#include "Result.h"
#include "Help.h"
#include "Ranking.h"
#include"DrawRanking.h"
