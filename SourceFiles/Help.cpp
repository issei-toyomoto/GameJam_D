/********************************
* ヘルプ
* 担当：島袋
********************************/
#include "main.h"
#include "PadInput.h"

Help::Help() {
    // 初期化処理
    state = 0;
    ctrl_state = 0;

    // 画像読み込み
    if ((img_title = LoadGraph("Resources/Images/title.png")) == -1) {};
    if ((img_ctrl = LoadGraph("Resources/Images/controller.png")) == -1) {};

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

Help::~Help() {
    // 終了処理
};

AbstractScene* Help::Update() {

    if (InputControl::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_ESCAPE)) {
        if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);
        return new Title();
    };

    return this;
};

void Help::Draw() const {
    // 背景表示
    DrawGraph(0, 0, img_title, TRUE);

    // コントローラー画像表示
    DrawExtendGraph(330, 290, 630, 490, img_ctrl, TRUE);
    //DrawExtendGraph(400, 500, 500, 600, image.controller_s, TRUE);

    // B Btn
    DrawLine(587, 368, 700, 368, 0x000000);
    DrawStringToHandle(700, 345, "Bボタン：決定", 0x000000, font[1][2], 0xffffff);

    // A Btn
    DrawLine(566, 392, 700, 392, 0x000000);
    DrawStringToHandle(700, 380, "Aボタン：もどる", 0x000000, font[1][2], 0xffffff);

    // Left Stick
    DrawLine(436, 421, 436, 550, 0x000000);
    DrawStringToHandle(280, 550, "左スティック：プレイヤーと、選たくカーソルの移動", 0x000000, font[1][2], 0xffffff);

    // Back Btn
    DrawLine(447, 350, 700, 276, 0x000000);
    DrawStringToHandle(700, 255, "BACKボタン：ゲームを終わる", 0x000000, font[1][2], 0xffffff);

    // Start Btn
    DrawLine(510, 350, 700, 300, 0x000000);
    DrawStringToHandle(700, 290, "STARTボタン：ポーズ", 0x000000, font[1][2], 0xffffff);

    // タイトル表示
    //DrawStringToHandle(400, 150, "ヘルプ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

};