#include <iostream>
#include "Make_DrawManager.h"
#include "Make_Global.h"

class Fps {
	int mStartTime;         //����J�n����
	int mCount;             //�J�E���^
	double mFps;             //fps
	static const int N = 60;//���ς����T���v����
	static const int FPS = 60;	//�ݒ肵��FPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
			int t = GetNowCount();
			mFps = 1000.0 / ((t - mStartTime) / (double)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}


	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//������������
		int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
		if (waitTime > 0) {
			Sleep(waitTime);	//�ҋ@
		}
	}
};

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(Make::Global::WINDOW_WIDTH,Make::Global::WINDOW_HEIGHT,Make::Global::WINDOW_COLORBIT); //�X�N���[���̑傫���̐ݒ�
	SetMainWindowText("noteman");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);//����ʂŉ�ʐ���
	SetBackgroundColor(30,30,30);
	Make::Make_DrawManager dm;
	Fps fps;

	dm.initialize();
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fps.Update();
		fps.Draw();
		dm.update();
		dm.draw();
		ScreenFlip();
		fps.Wait();
	}

	dm.finalize();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}
