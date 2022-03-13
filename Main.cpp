#include <fstream>

#include "boost/json.hpp"
#include "MainSceneManager.h"
#include "Global.h"
#include "Config_Config.h"

using namespace boost;

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

void configInit() {
	//�t�@�C���̓ǂݍ��ݗp
	std::string s = "";
	std::string line = "";
	//json�쐬�p�̕ϐ�
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
	bool isFail = false;
	std::ifstream readfile(".\\config\\config.json");
	if (!readfile) {
		isFail = true;
		return;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	val = json::parse(s, sp);
	obj = val.at("Config").as_object();
	double hiSpeed = obj.at("hiSpeed").as_double();
	double judgeCorrection = obj.at("judge").as_double();
	Config::g_hiSpeed += hiSpeed - Config::g_hiSpeed;
	Config::g_judgeCorrection += judgeCorrection - Config::g_judgeCorrection;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT,Global::WINDOW_COLORBIT); //�X�N���[���̑傫���̐ݒ�
	SetMainWindowText("NoteManSlide");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);//����ʂŉ�ʐ���
	const int backImgHandle = LoadGraph(".\\image\\background\\backImg.jpg");
	const int bgmHandle = LoadSoundMem(".\\bgm\\bgm.mp3");

	SetBackgroundColor(30,30,30);
	MainSceneManager mng = MainSceneManager(backImgHandle,bgmHandle);
	Fps fps;

	configInit();

	mng.initialize();
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fps.Update();
		fps.Draw();
		mng.update();
		mng.draw();
		ScreenFlip();
		fps.Wait();
	}

	mng.finalize();

	DeleteGraph(backImgHandle);
	DeleteSoundMem(bgmHandle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}
