#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Game_File_BaseFile.h"
#include "Game_File_MusicData.h"
#include "Game_Singleton_NoteManager.h"
#include "Game_Note_NormalNoteContainer.h"
#include "Game_Note_LongNoteContainer.h"
#include "Game_Global.h"

using namespace boost;

namespace Game{
	namespace File {
		struct MusicData { //json�t�@�C���������ݗp�̍\����
			std::uint16_t bpm;
			std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			double totalMinutes;//�Ȃ̍Đ�����(��)
			double beginDelay;//�Ȃ��n�܂�܂ł̂���
			std::uint8_t amountOfLane;
			MusicData(std::uint16_t bpm,std::uint16_t barLength,double totalMinutes,double beginDelay,std::uint8_t amountOfLane);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m);//valu_from�p�̃I�[�o���[�h�֐�

		struct NoteData { //json�t�@�C���������ݗp�̍\����
			double time;//�m�[�c�̎���
			std::uint8_t noteType;//�m�[�c�̎�� 1�Ȃ�Normal 2�Ȃ�Long
			std::uint8_t laneIndex;//�m�[�c�������郌�[��
			bool longNoteType;//�����O�m�[�c�̎�� true�Ȃ�n�_�I�_�@false�Ȃ�r��
			std::uint16_t longNoteGroupIndex;//�e�����O�m�[�c��������O���[�v
			std::uint16_t noteIndex;//���̃��[���ŉ��Ԗڂ̃m�[�c��
			NoteData(double time, std::uint8_t noteType, std::uint8_t laneIndex, bool longNoteType, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteData& n);//valu_from�p�̃I�[�o���[�h�֐�

		class Game_File_JsonIO : public Game_File_BaseFile
		{
		private:
			void getFilePath(char (&filePath)[MAX_PATH]);
		public:
			void saveNewJson(Game_File_MusicData* p_musicData);
		};
	}
}

