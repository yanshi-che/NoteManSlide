#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <fstream>

#include "boost/json.hpp"
#include "MainSceneManager.h"
#include "Global.h"
#include "Config_Config.h"
#include "Singleton_FpsOperator.h"

using namespace boost;

void configInit() {
	//�t�@�C���̓ǂݍ��ݗp
	std::string s = "";
	std::string line = "";
	//json�쐬�p�̕ϐ�
	json::object obj;
	json::value val;
	json::storage_ptr sp = json::make_shared_resource< json::monotonic_resource >();
	bool isFail = false;
	std::ifstream readfile(".\\data\\config\\config.json");
	if (!readfile) {
		isFail = true;
		Config::g_fps = 60;
	}
	while (std::getline(readfile, line)) {
		s.append(line);
	}

	val = json::parse(s, sp);
	obj = val.at("Config").as_object();
	double hiSpeed = obj.at("hiSpeed").as_double();
	double judgeCorrection = obj.at("judge").as_double();
	std::uint16_t fps = static_cast<std::uint16_t>(obj.at("fps").as_int64());
	Config::g_hiSpeed += hiSpeed - Config::g_hiSpeed;
	Config::g_judgeCorrection += judgeCorrection - Config::g_judgeCorrection;
	Config::g_fps = fps;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(true);
	SetGraphMode(Global::WINDOW_WIDTH,Global::WINDOW_HEIGHT,Global::WINDOW_COLORBIT); //�X�N���[���̑傫���̐ݒ�
	SetMainWindowText("NoteManSlide");
	SetWaitVSyncFlag(false);
	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);//����ʂŉ�ʐ���

	//�o�^����Ă��镈�ʂ��������f�B���N�g���̓ǂݍ���
	std::string path = ".\\data\\bgm";
	std::string bgmPath;

	try {
		for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
			bgmPath = entry.path().string();
		}
	}
	catch (...) {
		DrawBox(30, 200, 710, 500, GetColor(0, 0, 0), true);
		DrawString(80, 300, "bgm�̓ǂݍ��݂Ɏ��s���܂����B\n�f�B���N�g���\���A�܂��̓t�@�C���ɖ�肪����\��������܂��B",GetColor(255,255,255));
		DrawString(80, 420, "5�b��Ƀv���O�������I�����܂�", GetColor(255, 255, 255));
		ScreenFlip();
		Sleep(5000);
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		return 0;				// �\�t�g�̏I��
	}

	const int bgmHandle = LoadSoundMem(bgmPath.c_str());
	ChangeVolumeSoundMem(127, bgmHandle);

	const int backImgHandle = LoadGraph(".\\data\\image\\background\\backImg.jpg");
	MainSceneManager mng = MainSceneManager(backImgHandle,bgmHandle);
	configInit();
	Singleton::Singleton_FpsOperator* fps = Singleton::Singleton_FpsOperator::getInstance();


	mng.initialize();
	// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
	while (ProcessMessage() == 0) {
		fps->update();
		if (fps->wait()) {
			ClearDrawScreen();
			mng.update();
			mng.draw();
			fps->drawFps();
			ScreenFlip();
		}
	}

	mng.finalize();

	fps->destroyInstance();
	fps = nullptr;

	DeleteGraph(backImgHandle);
	DeleteSoundMem(bgmHandle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������


	return 0;				// �\�t�g�̏I��
}
