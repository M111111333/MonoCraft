#pragma once
#include "DxLib.h"

class Button
{
public:
    Button(int x, int y, int w, int h, const char* label);

    void Update();           // 状態更新（毎フレーム呼ぶ）
    void Draw();             // 描画
    bool IsClicked() { return clicked; }       

private:
    int x, y, w, h;
    const char* label;

    bool clicked;
    bool isHover;
    int prevMouseInput;

};