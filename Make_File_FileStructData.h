#pragma once

#include <boost/json.hpp>
#include <cstdint>
#include <string>
#include <vector>

using namespace boost;

namespace Make{
	namespace File {
		struct MusicData { //�t�@�C���������ݗp�̍\����
			std::string name;
			std::string artist;
			std::uint16_t level;
			double bpm;
			std::uint16_t barLength;//�ȑS�̂̏��ߐ�
			double totalMinutes;//�Ȃ̍Đ�����(��)
			double beginDelay;//�Ȃ��n�܂�܂ł̂���
			MusicData(std::string name, std::string artist, std::uint16_t level, double bpm, std::uint16_t barLength, double totalMinutes, double beginDelay);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const MusicData& m);//valu_from�p�̃I�[�o���[�h�֐�

		MusicData tag_invoke(const json::value_to_tag<MusicData>&, const json::value& jv);//json�t�@�C���p�[�X�p�I�[�o�[���[�h�֐�

		struct NoteDataForJson { //json�t�@�C���������ݗp�̍\����
			double time;//�m�[�c�̎���
			std::uint16_t noteType;//�m�[�c�̎�� 1�Ȃ�Normal 2�Ȃ�Long 3�Ȃ�Slide
			std::uint16_t laneIndex;//�m�[�c�������郌�[��
			std::uint16_t longNoteGroupIndex;//�e�����O�m�[�c��������O���[�v
			std::uint16_t noteIndex;//���̃��[���ŉ��Ԗڂ̃m�[�c��
			std::uint16_t rightOrLeft;//1�Ȃ�E 2�Ȃ獶
			std::uint16_t directionRightOrLeft;//1�Ȃ�E 2�Ȃ獶
			std::uint16_t slideLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			std::uint16_t slideLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			NoteDataForJson(double time, std::uint16_t noteType, std::uint16_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t noteIndex, std::uint16_t rightOrLeft, std::uint16_t directionRightOrLeft, std::uint16_t slideLaneIndexStart, std::uint16_t slideLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForJson& n);//valu_from�p�̃I�[�o���[�h�֐�

		struct BarLineData {
			std::uint16_t barID;
			std::uint16_t quontize;
			BarLineData(std::uint16_t barID,std::uint16_t quontize);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const BarLineData& b);//valu_from�p�̃I�[�o���[�h�֐�
		std::vector<BarLineData> tag_invoke(const json::value_to_tag<std::vector<BarLineData>>&, const json::value& jv);//json�t�@�C���p�[�X�p�I�[�o�[���[�h�֐�

		struct NoteDataForSave { //save�t�@�C���������ݗp�̍\����
			std::uint16_t barID;
			std::uint16_t beatID;
			std::uint16_t noteType;//�m�[�c�̎�� 1�Ȃ�Normal 2�Ȃ�Long 3�Ȃ�Slide
			std::uint16_t laneIndex;//�m�[�c�������郌�[��
			std::uint16_t longNoteGroupIndex;//�e�����O�m�[�c��������O���[�v
			std::uint16_t rightOrLeft;//1�Ȃ�E 2�Ȃ獶
			std::uint16_t directionRightOrLeft;//1�Ȃ�E 2�Ȃ獶
			std::uint16_t slideLaneIndexStart;//�X���C�h�m�[�c�̊J�n���[��
			std::uint16_t slideLaneIndexEnd;//�X���C�h�m�[�c�̏I�����[��
			NoteDataForSave(std::uint16_t barID, std::uint16_t beatID, std::uint16_t noteType, std::uint16_t laneIndex, std::uint16_t longNoteGroupIndex, std::uint16_t rightOrLeft, std::uint16_t directionRightOrLeft, std::uint16_t slideLaneIndexStart, std::uint16_t slideLaneIndexEnd);
		};

		void tag_invoke(const json::value_from_tag&, json::value& jv, const NoteDataForSave& n);//valu_from�p�̃I�[�o���[�h�֐�
		std::vector<NoteDataForSave> tag_invoke(const json::value_to_tag<std::vector<NoteDataForSave>>&, const json::value& jv);//json�t�@�C���p�[�X�p�I�[�o�[���[�h�֐�
	}
}

