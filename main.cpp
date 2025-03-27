#include "Game.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    Game game;
    game.run();  // �Q�[�������s

    DxLib_End();
    return 0;
}