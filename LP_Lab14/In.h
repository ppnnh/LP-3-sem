#pragma once
#define IN_MAX_LEN_TEXT 1024 * 1024	// ������������ ������ ��������� ���� = 1MB
#define IN_CODE_ENDL '\n'	// ������ ����� ������
#define IN_SEPARATOR '|'	// ������ ����������
// ������� �������� ������� ����������, ������ = ��� (Windows-1251) �������
// �������� IN::F - ����������� ������, IN::� - ����������� ������, IN::I -������������ (�� �������), IN::L - ����������� ������ //	���� 0 <= �������� < 256 - �� �������� ������ ��������
#define IN_CODE_TABLE {\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::S, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::L,		IN::L, IN::L, IN::L, IN::L, IN::L, IN::L, IN::F, IN::L, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,		IN::T, IN::T, IN::T, IN::L, IN::F, IN::L, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::L, IN::F, IN::L, IN::F, IN::F, \
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,		IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,		IN::T, IN::T, IN::T, IN::L, IN::L, IN::L, IN::F, IN::F, \
																														\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F,		IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,		IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T,		IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T  \
}

namespace In
{
	struct IN							// �������� ������
	{
		enum { T = 1024, F = 2048, I = 4096, L = 8192, S = 16384 };	//  T - ���������� ������, F - ������������, I - ������������, L - ����������� ������, S - ������(���������), ����� ��������
		int size = 0;										//	������ ��������� ����
		int lines = 0;										//	���������� �����
		int ignor = 0;										//	���������� ����������������� ��������
		unsigned char* text;								//	�������� ��� (Windoius -	1251)
		int code[256] = IN_CODE_TABLE;						//	������� ��������: T, F,	I, L �����	��������
	};
	IN getin(wchar_t infile[], wchar_t ITfile[], wchar_t LTfile[], LT::LexTable& lexTable, IT::IdTable& idTable);	// ������ � ��������� ������� �����
}