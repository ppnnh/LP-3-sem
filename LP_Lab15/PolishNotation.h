#pragma once
#include "stdafx.h"

namespace PN
{
	struct Data
	{
		int sizeOfArr;
		int* arrOfLex;
	};

	bool PolishNotation(int lextable_pos, LT::LexTable& lexTable, IT::IdTable& idTable);
	Data Create();
}