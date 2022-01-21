#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Game_Global.h"
#include "Game_File_MusicData.h"
#include "Game_File_MusicFileIO.h"
#include "Game_Draw_LineContainer.h"
#include "Game_Singleton_RaneDraw.h"
#include "Game_Singleton_BeatLineDraw.h"

namespace Game {
	namespace Draw {
		class Game_Draw_MenuDraw
		{
		private:
			enum MenuID {
				File = 1000,
				NewFile,
				Open,
				Save,
				Exit,
				Test,
				Play,
				Stop,
				WholeQUONTIZE, //�S�̂̃N�I���^�C�Y�̕ύX
				WholeQUARTER,
				WholeEIGHTH,
				WholeTRIPLET,
				WholeSIXTEENTH,
				WholeTHIRTYSECOND,
				PartQUONTIZE, //�ꕔ�̃N�I���^�C�Y�̕ύX
				PartQUARTER,
				PartEIGHTH,
				PartTRIPLET,
				PartSIXTEENTH,
				PartTHIRTYSECOND,
				NoteType,//�m�[�c�̎�ނ̕ύX
				Normal,
				Long,
			};
			static std::unique_ptr<File::Game_File_MusicData> musicData;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//���j���[���I�����ꂽ��Ă΂��֐�
		public:
			Game_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
		};

	}
}