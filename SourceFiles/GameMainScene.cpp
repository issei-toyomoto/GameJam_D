#include "common.h"
#include "main.h"
#include "Result.h"
#include "PadInput.h"

#include "Player.h"
#include "RunWeed.h"
#include "UI.h"

#include<math.h>


//#define DEBUG

GameMain::GameMain() {
    // 初期化処理
    state = 0;
    ZeroCnt = 0;

    runweed = new RunWeed * [5];
    for (int i = 0; i < 5; i++)
    {
        runweed[i] = nullptr;
    }

    Time[0] = 0;
    Time[1] = 0;
    Time[2] = 0;

    BackImg = LoadGraph("images/back.png");
    FlowerImg = LoadGraph("images/flower.png");
    WeedImg = LoadGraph("images/kusa.png");
    AnimImg = LoadGraph("images/readyback.png");
    
    ui.switchcount();


    // サウンド処理
    StopSoundMem(Resources::Get(SND, BGM, TITLE));

    se_select = LoadSoundMem("Resources/Sounds/se_select.wav");
    ChangeVolumeSoundMem(150, se_select);
    if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);

    bgm_main = LoadSoundMem("Resources/Sounds/bgm_main.wav");
    ChangeVolumeSoundMem(130, bgm_main);
    PlaySoundMem(bgm_main, DX_PLAYTYPE_LOOP, TRUE);

    GrassSe = LoadSoundMem("Resources/Sounds/se_kusa.wav"); 
    ChangeVolumeSoundMem((255 / 100) * 80, GrassSe);

    se_damage = LoadSoundMem("Resources/Sounds/se_damage.wav");
    ChangeVolumeSoundMem((255 / 100) * 80, se_damage);

};

GameMain::~GameMain() {
    // 終了処理
    StopSoundMem(bgm_main);
    DeleteSoundMem(bgm_main);
    StopSoundMem(se_select);
    DeleteSoundMem(se_select);

    PlaySoundMem(Resources::Get(SND, BGM, MAIN), DX_PLAYTYPE_LOOP, TRUE);
};

AbstractScene* GameMain::Update() { // ここで値の更新など、処理

    if (!Clear && !Pause)
    {
        player.Update();
        for (int i = 0; i < 5; i++)
        {
            if (runweed[i] != nullptr)runweed[i]->Update(player.GetX(), player.GetY());
        }
    }
    ui.Update();

    //花、草を刈った時のスコア処理
    for (int i = 0; i < 3; i++)
    {
        int PosX = player.AtkPos('X', 32 * i);
        int PosY = player.AtkPos('Y', 32 * i);

        int AtkX = (PosX - MARGIN_X) / BLOCK_SIZE;
        int AtkY = (PosY - UI_SIZE - MARGIN_Y) / BLOCK_SIZE;
        if (AtkX >= 0 && AtkY >= 0) {
            if (Grass[AtkY][AtkX] == FLOWER) {
                score -= FLOWER_AtkSCORE;
                Grass[AtkY][AtkX] = 0;
                ZeroCnt++;
                StopSoundMem(se_damage);
                PlaySoundMem(se_damage, DX_PLAYTYPE_BACK);
            }
            if (Grass[AtkY][AtkX] == WEED) {
                score += WEED_AtkSCORE;
                Grass[AtkY][AtkX] = 0;
                ZeroCnt++;
                StopSoundMem(GrassSe);
                PlaySoundMem(GrassSe, DX_PLAYTYPE_BACK);
            }
        }

        //逃げる草との当たり判定
        for (int i = 0; i < 5; i++)
        {
            if (runweed[i] != nullptr)
            {
                //プレイヤー間のX軸、Y軸との距離を取る
                float DisX = fabsf(runweed[i]->GetX() - PosX);
                float DisY = fabsf(runweed[i]->GetY() - PosY);

                float Dis = (float)sqrt(DisX * DisX + DisY * DisY);

                if (Dis <= BLOCK_SIZE / 2) 
                {
                    score += 300;
                    runweed[i] = nullptr;
                    StopSoundMem(GrassSe);
                    PlaySoundMem(GrassSe, DX_PLAYTYPE_BACK);
                }
            }
        }
    }
    SortGrass();

    //花を摘む
    if (InputControl::OnButton(XINPUT_BUTTON_A) && !Clear)
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

    //ステージクリア時処理
    if (!Clear && ((ZeroCnt == (FLOWER_NUM * StageNum) + (WEED_NUM * StageNum) && runweed[0] == nullptr) || ui.GetTime() == 0)) {
        Time[StageNum - 1] = ui.GetTime();
        StageNum++;
        ZeroCnt = 0;
        Anim = 0;
        Clear = true;
        ui.switchcount();
    }
    
    //ステージクリアアニメーション・処理
    if (Clear)
    {
        Anim++;
        if (StageNum == 1 && 90 + 25 * 3 < Anim)
        {
            ui.switchcount();
            Clear = false;
        }

        else if (StageNum == 2 && 180 + 25 * 3 < Anim)
        {
            ui.switchcount();
            Clear = false;
        }

        else if (StageNum == 3 && 180 + 25 * 3 < Anim)
        {
            ui.switchcount();
            Clear = false;
        }

        else if (3 < StageNum && 90 < Anim)
        {
            return new Result(score, Time);
        }

        if (Anim == 30)
        {
            SetStage(StageNum);
            ui.SetTime(30 + (30 * StageNum));
            player.Reset();
        }
    }

#ifdef DEBUG

    if (InputControl::OnButton(XINPUT_BUTTON_X)) 
    {
        ui.SetTime(1);
    }

#endif // DEBUG
    if (InputControl::OnButton(XINPUT_BUTTON_START) && !Clear) 
    {
        Pause = !Pause;
        ui.switchcount();
    }

    return this;    //シーン継続
};

//逃げる草の配列を整理
void GameMain::SortGrass() 
{
    for (int i = 0; i < 5 - 1; i++)
    {
        if (runweed[i] == nullptr)
        {
            runweed[i] = runweed[i + 1];
            runweed[i + 1] = nullptr;
        }
    }
}

void GameMain::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);
    DrawGraph(0, 0, BackImg, true);
    DrawBox(0, 0, 1280, 100, GetColor(0, 0, 0), TRUE);

    //DrawFormatString(20, 100, GetColor(255, 0, 0), "ZeroCnt:%d == %d", ZeroCnt, (FLOWER_NUM * StageNum) + (WEED_NUM * StageNum));

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

    for (int i = 0; i < 5; i++)
    {
        if (runweed[i] != nullptr)runweed[i]->Draw();
    }

    int stnum = StageNum;
    if (Clear && Anim <= 30)stnum--;
    ui.Draw(score,stnum); 

    //ステージ開始・クリアアニメーション
    if (Clear)
    {
        //文字サイズを設定
        int fonty = 100;
        SetFontSize(fonty);

        int fontx = 0;

        int fade = 0;
        //ステージ1
        if (StageNum == 1) 
        {
            fade = 60 + 25 * 3;
            if (fade < Anim)
            {
                //GO!
                DrawGraph(-(SCREEN_WIDTH / 30) * (Anim - fade), 0, AnimImg, true);
                fontx = GetDrawStringWidth("GO!", 3) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "GO!", 0xff0000);
            }
            else
            {
                DrawGraph(0, 0, AnimImg, true);
                //ステージ数表示
                fontx = GetDrawStringWidth("STAGE 1", 7) / 2;
                if (Anim < 60)
                {
                    DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "STAGE 1", 0xff0000);
                }
                else
                {
                    //カウントダウン
                    fontx = GetDrawStringWidth("3", 7) / 2;
                    if ((Anim - 60) / 25 == 0) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "3", 0x00ff00);
                    if ((Anim - 60) / 25 == 1) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "2", 0xffff00);
                    if ((Anim - 60) / 25 == 2) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "1", 0xff0000);
                }
            }
        }

        //ステージ2
        if (StageNum == 2)
        {
            fade = 150 + 25 * 3;
            if (Anim < 30)
            {
                //背景画像フェードイン
                DrawGraph(SCREEN_WIDTH - (SCREEN_WIDTH / 30) * Anim, 0, AnimImg, true);
            }
            else if (Anim < 90) 
            {
                //FINISH!
                DrawGraph(0, 0, AnimImg, true);
                fontx = GetDrawStringWidth("FINISH!", 7) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "FINISH!", 0xff0000);
            }
            else if (fade < Anim)
            {
                //GO!
                DrawGraph(-(SCREEN_WIDTH / 30) * (Anim - fade), 0, AnimImg, true);
                fontx = GetDrawStringWidth("GO!", 3) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "GO!", 0xff0000);
            }
            else
            {
                DrawGraph(0, 0, AnimImg, true);
                //ステージ数表示
                fontx = GetDrawStringWidth("STAGE 2", 7) / 2;
                if (Anim < 150)
                {
                    DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "STAGE 2", 0xff0000);
                }
                else
                {
                    //カウントダウン
                    fontx = GetDrawStringWidth("3", 7) / 2;
                    if ((Anim - 150) / 25 == 0) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "3", 0x00ff00);
                    if ((Anim - 150) / 25 == 1) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "2", 0xffff00);
                    if ((Anim - 150) / 25 == 2) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "1", 0xff0000);
                }
            }
        }

        //ステージ3
        if (StageNum == 3)
        {
            fade = 150 + 25 * 3;
            if (Anim < 30)
            {
                //背景画像フェードイン
                DrawGraph(SCREEN_WIDTH - (SCREEN_WIDTH / 30) * Anim, 0, AnimImg, true);
            }
            else if (Anim < 90)
            {
                //FINISH!
                DrawGraph(0, 0, AnimImg, true);
                fontx = GetDrawStringWidth("FINISH!", 7) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "FINISH!", 0xff0000);
            }
            else if (fade < Anim)
            {
                //GO!
                DrawGraph(-(SCREEN_WIDTH / 30) * (Anim - fade), 0, AnimImg, true);
                fontx = GetDrawStringWidth("GO!", 3) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "GO!", 0xff0000);
            }
            else
            {
                DrawGraph(0, 0, AnimImg, true);
                //ステージ数表示
                fontx = GetDrawStringWidth("STAGE 2", 7) / 2;
                if (Anim < 150)
                {
                    DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "STAGE 3", 0xff0000);
                }
                else
                {
                    //カウントダウン
                    fontx = GetDrawStringWidth("3", 7) / 2;
                    if ((Anim - 150) / 25 == 0) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "3", 0x00ff00);
                    if ((Anim - 150) / 25 == 1) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "2", 0xffff00);
                    if ((Anim - 150) / 25 == 2) DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "1", 0xff0000);
                }
            }
        }

        //終了
        if (3 < StageNum)
        {
            fade = 150 + 25 * 3;
            if (Anim < 30)
            {
                //背景画像フェードイン
                DrawGraph(SCREEN_WIDTH - (SCREEN_WIDTH / 30) * Anim, 0, AnimImg, true);
            }
            else if (Anim <= 90)
            {
                //FINISH!
                DrawGraph(0, 0, AnimImg, true);
                fontx = GetDrawStringWidth("FINISH!", 7) / 2;
                DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - fonty / 2, "FINISH!", 0xff0000);
            }
        }
    }

    //ポーズ画面
    if (Pause)
    {
        SetFontSize(100);
        int fontx = GetDrawStringWidth("PAUSE", 5) / 2;
        DrawString(SCREEN_WIDTH / 2 - fontx, SCREEN_HEIGHT / 2 - 100 / 2, "PAUSE", 0x0000ff);
    }
};

//ステージ初期化
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

    int weed = 0;
    if (stage == 2)weed = 3;
    else if (stage == 3)weed = 5;

    for (int i = 0; i < weed; i++)
    {
        int Y = GetRand(MAP_HEIGHT - 1);
        int X = GetRand(MAP_WIDTH - 1);

        while (Grass[Y][X] != 0)
        {
            Y = GetRand(MAP_HEIGHT - 1);
            X = GetRand(MAP_WIDTH - 1);
        }
        runweed[i] = new RunWeed(MARGIN_X + (BLOCK_SIZE * (X + 0.5)), MARGIN_Y + UI_SIZE + (BLOCK_SIZE * (Y + 0.5)));
    }
   
}