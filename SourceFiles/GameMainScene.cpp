#include "common.h"
#include "main.h"
#include "Result.h"
#include "PadInput.h"

#include "Player.h"
#include "UI.h"

#include<math.h>


#define DEBUG

GameMain::GameMain() {
    // 初期化処理
    state = 0;
    ZeroCnt = 0;

    BackImg = LoadGraph("images/back.png");
    FlowerImg = LoadGraph("images/flower.png");
    WeedImg = LoadGraph("images/kusa.png");
    
    SetStage(StageNum);
};

GameMain::~GameMain() {
    // 終了処理
};

AbstractScene* GameMain::Update() { // ここで値の更新など、処理


    player.Update();


    //花、草を刈った時のスコア処理
    for (int i = 0; i < 3; i++)
    {
        int AtkX = (player.AtkPos('X', 32 * i) - MARGIN_X) / BLOCK_SIZE;
        int AtkY = (player.AtkPos('Y', 32 * i) - UI_SIZE - MARGIN_Y) / BLOCK_SIZE;
        if (AtkX >= 0 && AtkY >= 0) {
            if (Grass[AtkY][AtkX] == FLOWER) {
                score -= FLOWER_AtkSCORE;
                Grass[AtkY][AtkX] = 0;
                ZeroCnt++;
            }
            if (Grass[AtkY][AtkX] == WEED) {
                score += WEED_AtkSCORE;
                Grass[AtkY][AtkX] = 0;
                ZeroCnt++;
            }
        }
    }

    if (InputControl::OnButton(XINPUT_BUTTON_A))
    {
        float Px = player.GetX();
        float Py = player.GetY();

        int MapX = (Px - MARGIN_X) / BLOCK_SIZE;
        int MapY = (Py - UI_SIZE - MARGIN_Y) / BLOCK_SIZE;

        if (0 <= MapX && 0 <= MapY)
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    float DisX = abs(Px - ((MapX + i) * BLOCK_SIZE + MARGIN_X + BLOCK_SIZE / 2));
                    float DisY = abs(Py - ((MapY + j) * BLOCK_SIZE + UI_SIZE + MARGIN_Y + BLOCK_SIZE / 2));

                    DisX *= DisX;
                    DisY *= DisY;

                    float Dis = (float)sqrt(DisX + DisY);

                    if (Dis <= BLOCK_SIZE * 1 && Grass[MapY + j][MapX + i] == 2)
                    {
                        score += 500;
                        Grass[MapY + j][MapX + i] = 0;
                        ZeroCnt++;
                        i = 2;
                        break;
                    }
                }
            }
        }

    }

    if (ZeroCnt == (FLOWER_NUM * StageNum) + (WEED_NUM * StageNum)) {
        StageNum++;
        ZeroCnt = 0;
        if (StageNum > 3) {
            return new Result(score);
        }
    }
    

    if (InputControl::OnButton(XINPUT_BUTTON_START))return new Result(score);
    if (ui.Update() == -1) {
        return nullptr;
    };

    return this;    //シーン継続
};

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);
    DrawGraph(0, 0, BackImg, true);
    DrawBox(0, 0, 1280, 100, GetColor(0, 0, 0), TRUE);

    DrawFormatString(20, 100, GetColor(255, 0, 0), "ZeroCnt:%d == %d", ZeroCnt, (FLOWER_NUM * StageNum) + (WEED_NUM * StageNum));

    //花、草表示処理
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (Grass[i][j] == WEED) {
                DrawGraph(MARGIN_X + (j * BLOCK_SIZE), MARGIN_Y + UI_SIZE + (i * BLOCK_SIZE), WeedImg, true);
            }

            if (Grass[i][j] == FLOWER) {
                DrawGraph(MARGIN_X + (j * BLOCK_SIZE), MARGIN_Y + UI_SIZE + (i * BLOCK_SIZE), FlowerImg, true);
            }
        }
    }

    
   #ifdef DEBUG
    int margin = (SCREEN_HEIGHT - 100) % BLOCK_SIZE / 2;
    for (int i = 100 + margin; i < 720; i += BLOCK_SIZE)
    {
        DrawLine(margin, i, 1280 - margin, i, 0xffffff);
        if ((i - 100) / BLOCK_SIZE % 5 == 0)DrawLine(margin, i, 1280 - margin, i, 0xff0000);
    }

    margin = SCREEN_WIDTH % BLOCK_SIZE / 2;
    for (int i = margin; i < 1280; i += BLOCK_SIZE)
    {
        DrawLine(i, 100 + margin, i, 720 - margin, 0xffffff);
        if (i / BLOCK_SIZE % 5 == 0)DrawLine(i, 100 + margin, i, 720 - margin, 0xff0000);
    }

#endif
    
    player.Draw();

    ui.Draw(score,StageNum); 
};

void GameMain::SetStage(int stage) 
{

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            Grass[i][j] = 0;
            GrassTmp[i][j] = 0;
        }
    }

    for (int i = 0; i < FLOWER_NUM * stage; i++) {
        y = GetRand(MAP_HEIGHT - 1);
        x = GetRand(MAP_WIDTH - 1);
        if (Grass[y][x] == 0) {
            Grass[y][x] = FLOWER;
        }
        else {
            i--;
        }
        
    }
   
    for (int i = 0; i < WEED_NUM * stage; i++) {
        y = GetRand(MAP_HEIGHT - 1);
        x = GetRand(MAP_WIDTH - 1);
        if (Grass[y][x] == 0) {
            Grass[y][x] = WEED;
        }
        else {
            i--;
        }

    }
   
}