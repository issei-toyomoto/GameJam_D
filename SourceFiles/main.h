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
#include "InputRanking.h"
