#pragma once

#include "dxlib/DxLib.h"
#include "boost/json.hpp"
#include <memory>
#include <utility>

#include "Make_Global.h"
#include "Make_File_MusicData.h"
#include "Make_File_MusicFileIO.h"
#include "Make_File_JsonIO.h"
#include "Make_File_SaveFileIO.h"
#include "Make_Draw_LineContainer.h"
#include "Make_Singleton_BeatLineManager.h"

using namespace boost;

namespace Make {
	namespace Draw {
		class Make_Draw_MenuDraw
		{
		private:
			enum MenuID {
				File = 1000,
				NewFile,
				Open,
				Save,
				Export,
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
				Slide,
			};
			static std::shared_ptr<File::Make_File_MusicData> p_musicData;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//���j���[���I�����ꂽ��Ă΂��֐�
			static void setMusicDataFromNewFile(const std::shared_ptr<File::Make_File_MusicData> md);
			static void setMusicDataFromSaveFile(std::unique_ptr<File::Make_File_MusicData> md, const json::value val);
		public:
			Make_Draw_MenuDraw();
		};

	}
}