/********************************
* タイトル
* 担当：島袋
********************************/
#include "main.h"

Title::Title() {
    // 初期化処理
    state = 0;
    ctrl_state = 0;

    // 画像読み込み
    if ((img_title = LoadGraph("Resources/Images/title.png")) == -1) {};

    // フォント読み込み
    font[0][0] = CreateFontToHandle(NULL, 128, -1, DX_FONTTYPE_NORMAL);
    font[0][1] = CreateFontToHandle(NULL, 64, -1, DX_FONTTYPE_NORMAL);
    font[0][2] = CreateFontToHandle(NULL, 32, -1, DX_FONTTYPE_NORMAL);
    font[0][3] = CreateFontToHandle(NULL, 16, -1, DX_FONTTYPE_NORMAL);
    LPCSTR font_path = "Resources/Fonts/syokakiutage.ttf"; // 読み込むフォントファイルのパス
    if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) < 0) {
        // フォント読込エラー処理
        MessageBox(NULL, "フォント読込失敗", "", MB_OK);
    };
    font[1][0] = CreateFontToHandle("しょかきうたげ（無料版）", 128, 9, DX_FONTTYPE_EDGE);
    font[1][1] = CreateFontToHandle("しょかきうたげ（無料版）", 64, 9, DX_FONTTYPE_EDGE);
    font[1][2] = CreateFontToHandle("しょかきうたげ（無料版）", 32, 9, DX_FONTTYPE_EDGE);
    font[1][3] = CreateFontToHandle("しょかきうたげ（無料版）", 16, 9, DX_FONTTYPE_EDGE);

    // サウンド読み込み
    bgm = LoadSoundMem("Resources/Sounds/bgm_title.wav");
    se_cursor = LoadSoundMem("Resources/Sounds/se_cursor.wav");
    se_select = LoadSoundMem("Resources/Sounds/se_select.wav");
    ChangeVolumeSoundMem(255, bgm);
    ChangeVolumeSoundMem(130, se_cursor);
    ChangeVolumeSoundMem(150, se_select);
};

Title::~Title() {
    // 終了処理
    img_title = 0;

    // フォント削除
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            DeleteFontToHandle(font[i][j]);
        };
    };

    // サウンド削除
    StopSoundMem(bgm);
    DeleteSoundMem(bgm);
    StopSoundMem(se_cursor);
    DeleteSoundMem(se_cursor);
    StopSoundMem(se_select);
    DeleteSoundMem(se_select);
};

AbstractScene* Title::Update() {

    /********************************
    * ゲームモードセレクト処理
    ********************************/
    // キーボードのボタンが戻ったら操作受付
    if (((InputControl::TipLeftLStick(STICKL_Y) <= 0.1) && (InputControl::TipLeftLStick(STICKL_Y) >= -0.1)) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && !CheckHitKey(KEY_INPUT_SPACE)) {
        ctrl_state = 0;
    };
    if (((InputControl::TipLeftLStick(STICKL_Y) >= 0.5) && ctrl_state == 0) || InputControl::OnButton(XINPUT_BUTTON_DPAD_UP) || (CheckHitKey(KEY_INPUT_UP) && ctrl_state == 0)) {
        // カーソル上
        PlaySoundMem(se_cursor, DX_PLAYTYPE_BACK, TRUE);
        if (state <= 0) {
            state = 3;
        }
        else {
            state -= 1;
        };
        ctrl_state = 1;
    }
    else if (((InputControl::TipLeftLStick(STICKL_Y) <= -0.5) && ctrl_state == 0) || InputControl::OnButton(XINPUT_BUTTON_DPAD_DOWN) || (CheckHitKey(KEY_INPUT_DOWN) && ctrl_state == 0)) {
        // カーソル下
        PlaySoundMem(se_cursor, DX_PLAYTYPE_BACK, TRUE);
        if (state >= 3) {
            state = 0;
        }
        else {
            state += 1;
        };
        ctrl_state = 1;
    };

    if (InputControl::OnButton(XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE)) {
        if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);
        if (state == 0) {
            // スタート選択
            return new GameMain();
        }
        else if (state == 1) {
            // ヘルプ選択
            return new Help();
        }
        else if (state == 2) {
            // ランキング選択
            //return new Ranking();
        }
        else if (state == 3) {
            // 終わる選択
            //return new End();
            return nullptr;
        };
    };

    return this;
};

void Title::Draw() const {
    // 背景表示
    DrawGraph(0, 0, img_title, TRUE);

    // タイトル表示
    DrawStringToHandle(400, 150, GAME_NAME, 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_64], 0xffffff);

    // バージョン表示（仮）
    DrawStringToHandle(20, 690, "v6.06", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_16], 0xffffff);

    // ゲームモードセレクトの項目
    DrawStringToHandle(630, 350, "スタート", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 400, "ヘルプ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 450, "ランキング", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    DrawStringToHandle(630, 500, "終わる", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    DrawStringToHandle(380, 670, "左スティックで選たく、Bボタンで決定", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    // ゲームモードセレクトのカーソル処理
    if (state == 0) {
        DrawStringToHandle(570, 350, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 1) {
        DrawStringToHandle(570, 400, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 2) {
        DrawStringToHandle(570, 450, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 3) {
        DrawStringToHandle(570, 500, "→", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    };

    // BGM 再生
    if (CheckSoundMem(bgm) == 0) {
        PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
    };

    DrawFormatString(20, 600, GetColor(255, 255, 255), "%.1f", InputControl::TipLeftLStick(STICKL_Y));
};