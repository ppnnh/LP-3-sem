#pragma once

#define ID_MAXSIZE			5				// ������������ ���������� �������� � ��������������
#define ID_MAXSIZE_INTEGRAL	20				// ������������ ���������� �������� ��� ���������� ���������������
#define TI_MAXSIZE			4096			// ������������ ���������� ��-�� � ������� ��������������� 
#define TI_INT_DEFAULT		0x00000000		// �������� �� ��������� ��� ���� integer 
#define TI_STR_DEFAULT		0x00			// �������� �� ��������� ��� ���� string 
#define TI_NULLIDX			0xffffffff		// ��� �������� ������� ���������������
#define TI_STR_MAXSIZE		255
#define SIZE_INTEGRAL_ID	2				// ������ ������� ����������� ���������������
#define IND_MAIN			"main"
#define NEW_TABLE			"---------------------------------------------------------------------------------"

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2 };					// ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, O = 5 };		// ���� ���������������: ����������, �������, ��������, �������, ��������

	struct Entry		// ������ ������� ���������������
	{
		int	idxfirstLE;									// ������ ������ ������ � ������� ������
		char id[ID_MAXSIZE_INTEGRAL];					// ������������� (������������� ��������� �� ID_MAXSIZE)
		char parentBlockName[ID_MAXSIZE_INTEGRAL];		// ��� ������������� �����
		IDDATATYPE iddatatype;							// ��� ������
		IDTYPE idtype;									// ��� ��������������

		union
		{
			int vint;							// �������� integer
			struct
			{
				char len;						// ��������� �������� � string
				char str[TI_STR_MAXSIZE - 1];	// ������� string
			} vstr[TI_STR_MAXSIZE];				// �������� string
		} value;								// �������� ��������������
	};

	struct IdTable // ��������� ������� ���������������
	{
		int maxsize;										// ������� ������� ��������������� < TI_MAXSIZE
		int current_size;									// ������� ������ ������� ��������������� < maxsize
		int current_literals = 0;							// ������� ���-�� ���������
		Entry* table;										// ������ ����� ������� ���������������
	};

	IdTable Create(int size);								// ������� ������� ��
	void Add(IdTable& idtable, Entry entry);				// �������� ������ � ������� ��
	Entry GetEntry(IdTable& idtable, int n);				// �������� ������ ������� ��
	int IsId(IdTable& idtable, char id[ID_MAXSIZE]);		// �������: ����� ������( ���� ����), TI_NULLIDX(���� ���)
	void Delete(IdTable& idtable);							// ������� ������� ������
	void PrintIdTable(IdTable& idtable, wchar_t ITfile[]);
	int IsLiteral(IdTable& idtable, char str[TI_STR_MAXSIZE - 1]);
	int IsLiteral(IdTable& idtable, int n);
};