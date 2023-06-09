/********************************
* ヘルプ
* 担当：島袋
********************************/
#include "main.h"

Help::Help() {
    // 初期化処理
    state = 0;
    ctrl_state = 0;

    AnimImg = LoadGraph("images/readyback.png");
    Anim = 0;
    Start = false;

    // 画像読み込み
    if ((img_title = LoadGraph("Resources/Images/title.png")) == -1) {};
    if ((img_ctrl = LoadGraph("Resources/Images/controller.png")) == -1) {};
    if ((img_help[0] = LoadGraph("Resources/Images/help.png")) == -1) {};
    if ((img_help[1] = LoadGraph("Resources/Images/help1.png")) == -1) {};
    if ((img_help[2] = LoadGraph("Resources/Images/help2.png")) == -1) {};
    if ((img_help[3] = LoadGraph("Resources/Images/help3.png")) == -1) {};
    if ((img_help[4] = LoadGraph("Resources/Images/help4.png")) == -1) {};
    if ((img_help[5] = LoadGraph("images/flower.png")) == -1) {};
    if ((img_help[6] = LoadGraph("images/kusa.png")) == -1) {};

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
    se_cursor = LoadSoundMem("Resources/Sounds/se_cursor.wav");
    se_select = LoadSoundMem("Resources/Sounds/se_select.wav");
    ChangeVolumeSoundMem(130, se_cursor);
    ChangeVolumeSoundMem(150, se_select);

    // サウンド処理
    if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);
};

Help::~Help() {
    // 終了処理
    img_title = 0;
    img_ctrl = 0;

    // フォント削除
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            DeleteFontToHandle(font[i][j]);
        };
    };

    // サウンド削除
    StopSoundMem(se_cursor);
    DeleteSoundMem(se_cursor);
    StopSoundMem(se_select);
    DeleteSoundMem(se_select);
};

AbstractScene* Help::Update() {

    if (!Start)
    {
        if (InputControl::OnButton(XINPUT_BUTTON_X) || CheckHitKey(KEY_INPUT_X))
        {
            if (CheckSoundMem(se_cursor) == 0) PlaySoundMem(se_cursor, DX_PLAYTYPE_BACK, TRUE);
            if (state >= 1) {
                state = 0;
            }
            else {
                state++;
            };
        };
        if (InputControl::OnButton(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_ESCAPE)) {
            if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);
            return new Title();
        }
        else if (InputControl::OnButton(XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_SPACE)) {
            if (CheckSoundMem(se_select) == 0) PlaySoundMem(se_select, DX_PLAYTYPE_BACK, TRUE);
            Start = true;
        };
    }
    else
    {
        Anim++;
        if (30 < Anim)return new GameMain();
    }

    return this;
};

void Help::Draw() const {

    // 背景表示
    DrawGraph(0, 0, img_title, TRUE);

    // タイトル表示
    DrawStringToHandle(180, 40, "ヘルプ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_128], 0xffffff);

    // 説明表示
    DrawStringToHandle(700, 130, "Xボタンで説明を切りかえ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    // 戻る表示
    DrawStringToHandle(370, 670, "Bボタンでゲーム開始、Aボタンでもどる", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

    if (state == 0) {

        // サブタイトル表示
        DrawStringToHandle(735, 40, "操作説明", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_64], 0xffffff);

        // コントローラー画像表示
        DrawExtendGraph(330, 290, 630, 490, img_ctrl, TRUE);

        // B Btn
        DrawLine(587, 368, 700, 368, 0x000000);
        DrawStringToHandle(700, 345, "Bボタン：カマでこうげき", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

        // A Btn
        DrawLine(566, 392, 700, 392, 0x000000);
        DrawStringToHandle(700, 380, "Aボタン：花をつむ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

        // Left Stick
        DrawLine(436, 421, 436, 550, 0x000000);
        DrawStringToHandle(280, 550, "左スティック：プレイヤーと、選たくカーソルの移動", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

        // Back Btn
        DrawLine(447, 350, 700, 276, 0x000000);
        DrawStringToHandle(700, 255, "BACKボタン：ゲームを終わる", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);

        // Start Btn
        DrawLine(510, 350, 700, 300, 0x000000);
        DrawStringToHandle(700, 290, "STARTボタン：ポーズ", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    }
    else if (state == 1) {

        // サブタイトル表示
        DrawStringToHandle(730, 40, "ゲーム説明", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_64], 0xffffff);

        // ゲーム説明表示
        DrawStringToHandle(330, 240, "Bで刈る", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_32], 0xffffff);
        DrawStringToHandle(850, 240, "Aで取る", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_32], 0xffffff);

        DrawExtendGraph(170, 280, 170 + 200, 280 + 200, img_help[1], TRUE);
        DrawExtendGraph(390, 280, 390 + 200, 280 + 200, img_help[2], TRUE);
        DrawExtendGraph(690, 280, 690 + 200, 280 + 200, img_help[3], TRUE);
        DrawExtendGraph(910, 280, 910 + 200, 280 + 200, img_help[4], TRUE);

        DrawExtendGraph(300, 520, 300 + 50, 520 + 50, img_help[5], TRUE);
        DrawExtendGraph(300, 580, 300 + 50, 580 + 50, img_help[6], TRUE);

        DrawStringToHandle(370, 530, "刈ったら：-300点　取ったら：300点", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_32], 0xffffff);
        DrawStringToHandle(370, 590, "刈ったら：100点　（動く草：500点）", 0x000000, font[FONT_TYPE_DEFAULT][FONT_SIZE_32], 0xffffff);

        // 説明内容
        //DrawStringToHandle(120, 220, "このゲームは、カマをふり回す危険な主人公を操作して草をかったり、", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
        //DrawStringToHandle(250, 270, "お花をつんだりする非常にほのぼのしたゲームです。", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
        //DrawStringToHandle(210, 320, "草をかりながら花をつんで、ポイントをかせいでください。", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
        //DrawStringToHandle(100, 370, "落下してくるリンゴは４種類です。", 0x000000, font[FONT_TYPE_LOAD_1][FONT_SIZE_32], 0xffffff);
    };

    // BGM 再生
    if (CheckSoundMem(Resources::Get(SND, BGM, TITLE)) == 0) {
        PlaySoundMem(Resources::Get(SND, BGM, TITLE), DX_PLAYTYPE_LOOP, TRUE);
    };

    if (Start)
    {
        //画像フェードイン
        DrawGraph(SCREEN_WIDTH - (SCREEN_WIDTH / 30.f) * Anim, 0, AnimImg, true);
    }
};