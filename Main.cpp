#include <iostream>
#include "Game_SceneManager.h"
#include "Game_Global.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);
	SetGraphMode(Game::Global::WINDOW_WIDTH,Game::Global::WINDOW_HEIGHT,Game::Global::WINDOW_COLORBIT); //�X�N���[���̑傫���̐ݒ�

	SetDrawScreen(DX_SCREEN_BACK);//����ʂŉ�ʐ���
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Game::Game_SceneManager sm;

	sm.initialize();
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		sm.update();
		sm.draw();
	}

	sm.finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}
