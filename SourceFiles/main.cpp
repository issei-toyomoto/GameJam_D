#include "DxLib.h"
#include "main.h"
#include "Fps.h"
#include "PadInput.h"
#include "common.h"
#include"SceneManager.h"
#include"GameMainScene.h"

int Resources::snd_bgm[5];
int Resources::snd_se[5];

/********************************
* メインプログラム 開始
********************************/
int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {

    SetMainWindowText(GAME_NAME);                  // ウィンドウタイトルを設定
    SetMainWindowClassName(GAME_NAME);             // 他のDxLibと競合しないようにウィンドウクラスを設定
    ChangeWindowMode(TRUE);                        // ウインドウモードで起動
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ
    if (DxLib_Init() == -1) return -1;             // DXライブラリの初期化処理
    SetDrawScreen(DX_SCREEN_BACK);                 // 描画先画面を裏にする（ダブルバッファリング）

    // タイトル シーンオブジェクト作成
    SceneManager* sceneMng = new SceneManager((AbstractScene*) new Title());

    Fps fps;

    // 一部のリソースをstaticとして読み込み
    int bgm_title, bgm_main, se_select;
    if ((bgm_title = LoadSoundMem("Resources/Sounds/bgm_title.wav")) == -1) return -1;
    if ((bgm_main = LoadSoundMem("Resources/Sounds/bgm_main.wav")) == -1) return -1;
    if ((se_select = LoadSoundMem("Resources/Sounds/se_select.wav")) == -1) return -1;
    Resources::Set(SND, BGM, TITLE, 0);

    // ゲームループし、シーンマネジャーでシーンの更新
    while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr) && !(InputControl::OnButton(XINPUT_BUTTON_BACK))) {
        ClearDrawScreen(); // 画面の初期化

        // シーンマネジャーでシーンの描画開始
        sceneMng->Draw();

        fps.Update();
        //fps.Draw();
        InputControl::Update(); //コントローラー入力更新
        
        ScreenFlip(); // 裏画面の内容を表画面に反映する
        fps.Wait();		//待機

    };

    DxLib_End(); // DXライブラリ使用の終了処理
    return 0;    // プログラムの終了
};