#pragma once

#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int state = 0;
    int ctrl_state;
    int img_title;
    int font[2][4];
    int bgm, se_cursor, se_select;
public:
    // コンストラクタ
    Title();

    // デストラクタ
    ~Title();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;
};