#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "Make_File_BaseFile.h"
#include "Make_File_MusicData.h"
#include "Make_Singleton_NoteManager.h"
#include "Make_Note_NormalNoteContainer.h"
#include "Make_Note_LongNoteContainer.h"
#include "Make_Global.h"

using namespace boost;

namespace Make{
	namespace File {
		struct MusicData { //json�t�@�C���������ݗp�̍\����
			std::string name;
			std::string artist;
			std::uint8_t level;
			std::uint16_t bpm;
			std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			float totalMinutes;//�Ȃ̍Đ�����(��)
			std::uint16_t beginDelay;//�Ȃ��n�܂�܂ł̂���
			std::uint8_t amountOfLane;
			MusicData(std::string name,std::string artist,std::uint8_t level,std::uint16_t bpm,std::uint16_t barLength,float totalMinutes, std::uint16_t beginDelay,std::uint8_t amountOfLane);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m);//valu_from�p�̃I�[�o���[�h�֐�

		struct NoteData { //json�t�@�C���������ݗp�̍\����
			float time;//�m�[�c�̎���
			std::uint8_t noteType;//�m�[�c�̎�� 1�Ȃ�Normal 2�Ȃ�Long 3�Ȃ�Slide
			std::uint8_t laneIndex;//�m�[�c�������郌�[��
			std::uint16_t longNoteGroupIndex;//�e�����O�m�[�c��������O���[�v
			std::uint16_t noteIndex;//���̃��[���ŉ��Ԗڂ̃m�[�c��
			std::uint8_t rightOrLeft;//1�Ȃ�E 2�Ȃ獶
			std::uint8_t sildeLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			std::uint8_t sildeLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			NoteData(float time, std::uint8_t noteType, std::uint8_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint8_t rightOrLeft, std::uint8_t sildeLaneIndexStart, std::uint8_t sildeLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteData& n);//valu_from�p�̃I�[�o���[�h�֐�

		class Make_File_JsonIO : public Make_File_BaseFile
		{
		private:
			void getFilePath(char (&filePath)[MAX_PATH]);
		public:
			void saveNewJson(Make_File_MusicData* const p_musicData);
		};
	}
}

