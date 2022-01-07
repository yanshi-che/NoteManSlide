#pragma once

#include "dxlib/DxLib.h"
#include <memory>

#include "Game_File_MusicData.h"
#include "Game_File_MusicFileIO.h"
#include "Game_Draw_DrawFactory.h"

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
				WholeQUONTIZE, //�S�̂̕ύX
				WholeQUARTER, // �S������
				WholeEIGHTH, // �W������
				WholeTRIPLET, // �R�A��
				WholeSIXTEENTH, // �P�U������
				WholeSEXTOLET, // �U�A��
				WholeTHIRTYSECOND, // �R�Q������
				PartQUONTIZE, //�ꕔ�̕ύX
				PartQUARTER, // �S������
				PartEIGHTH, // �W������
				PartTRIPLET, // �R�A��
				PartSIXTEENTH, // �P�U������
				PartSEXTOLET, // �U�A��
				PartTHIRTYSECOND, // �R�Q������

			};
			enum quontize {
				quarterNote = 1, // �S������
				eighthNote = 2, // �W������
				tripletNote = 3, // �R�A��
				sixteenthNote = 4, // �P�U������
				sextoletNote = 6, // �U�A��
				thirtySecondNote = 8, // �R�Q������
			};
			static std::unique_ptr<File::Game_File_MusicData> musicData;
			static Game_Draw_DrawFactory* drawFactory;
			static void MenuItemSelectCallBack(const TCHAR* itemName, int itemID);//���j���[���I�����ꂽ��Ă΂��֐�
		public:
			Game_Draw_MenuDraw();
			static void setMusicData(std::unique_ptr<File::Game_File_MusicData> md);
			static void setDrawFactory(Game_Draw_DrawFactory* df);
		};

	}
}