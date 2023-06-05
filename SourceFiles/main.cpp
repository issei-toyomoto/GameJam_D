#include "main.h"
#include "PadInput.h"

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

    // FPS計測
    LONGLONG nowTime = GetNowHiPerformanceCount(), oldTime = nowTime, fpsCheckTime = GetNowHiPerformanceCount();
    double deltaTime = 0, nextTime = 0;
    int fpsCounter = 0, fps = 0;

    // タイトル シーンオブジェクト作成
    SceneManager* sceneMng = new SceneManager((AbstractScene*) new Title());

    // ゲームループし、シーンマネジャーでシーンの更新
    while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) {
        ClearDrawScreen(); // 画面の初期化

        // シーンマネジャーでシーンの描画開始
        sceneMng->Draw();

        // FPS 表示
        SetFontSize(16);
        DrawFormatString(20, 10, 0xffffff, "FPS : %d", fps);

        PAD_INPUT::UpdateKey(); //コントローラー入力更新
        
        ScreenFlip(); // 裏画面の内容を表画面に反映する

        /********************************
        * FPS計測
        ********************************/
        // １ループ時点のシステム時間を取得
        oldTime = nowTime;
        nowTime = GetNowHiPerformanceCount();
        // １ループの時間経過を求める
        deltaTime = (nowTime - oldTime) / 1000000.0F;
        // １秒間のFPSを計測する、１秒ごとに初期化する
        fpsCounter++;
        if (nowTime - fpsCheckTime > 1000000) { // 1000000(240FPS) 500000(120FPS) 250000(60FPS)
            fps = fpsCounter;
            fpsCounter = 0;
            fpsCheckTime = nowTime;
        };
        //Main::SetFPS(fps);
        // FPS 60 固定
        nextTime = GetNowCount();
        nextTime += 16.6666666666667;
        if (nextTime > GetNowCount()) {
            WaitTimer(nextTime - GetNowCount());
        };

    };

    DxLib_End(); // DXライブラリ使用の終了処理
    return 0;    // プログラムの終了
};