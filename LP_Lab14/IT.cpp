#include "stdafx.h"

namespace IT
{

	IdTable Create(int size)
	{
		if (size <= TI_MAXSIZE)
		{
			IdTable idtable;
			idtable.maxsize = size;
			idtable.current_size = 0;
			idtable.table = new Entry[TI_MAXSIZE];
			return idtable;
		}
		else
		{
			throw ERROR_THROW(130)
		}
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n < idtable.maxsize && n >= 0)
		{
			return idtable.table[n];
		}
		else
		{
			throw ERROR_THROW(123)
		}
	}

	void Delete(IdTable& idtable)
	{
		delete idtable.table;
		idtable.table = nullptr;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.current_size < idtable.maxsize)
		{
			idtable.table[idtable.current_size] = entry;

			switch (entry.iddatatype)
			{
			case IT::IDDATATYPE::INT:
				idtable.table[idtable.current_size].value.vint = TI_INT_DEFAULT;
				break;

			case IT::IDDATATYPE::STR:
				idtable.table[idtable.current_size].value.vstr->str[0] = TI_STR_DEFAULT;
				idtable.table[idtable.current_size].value.vstr->len = 0;
				break;
			}

			idtable.current_size++;
		}
		else
		{
			throw ERROR_THROW(124);
		}
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE_INTEGRAL])
	{
		for (int i = idtable.current_size - 1; i >= 0; i--)
		{
			if (strcmp(idtable.table[i].id, id) == 0)
			{
				return i;
			}
		}

		return TI_NULLIDX;
	}

	int IsLiteral(IdTable& idtable, char str[TI_STR_MAXSIZE - 1])
	{
		for (int i = idtable.current_size - 1; i >= 0; i--)
		{
			if (idtable.table[i].idtype == IT::IDTYPE::L)
			{
				if (strlen(str) - 2 != idtable.table[i].value.vstr->len)
				{
					continue;
				}

				bool isEqual = true;

				for (size_t j = 0; j < idtable.table[i].value.vstr->len; j++)
				{
					if (str[j + 1] != idtable.table[i].value.vstr->str[j])
					{
						isEqual = false;
						break;
					}
				}

				if (isEqual)
				{
					return i;
				}
			}
		}

		return TI_NULLIDX;
	}

	int IsLiteral(IdTable& idtable, int n)
	{
		for (int i = 0; i < idtable.current_size; i++)
		{
			if (idtable.table[i].idtype == IT::IDTYPE::L && idtable.table[i].value.vint == n)
			{
				return i;
			}
		}

		return TI_NULLIDX;
	}

	void PrintIdTable(IdTable& idtable, wchar_t ITfile[])
	{
		std::ofstream fout(ITfile);

		if (fout.is_open())
		{
			for (int i = 0; i < idtable.current_size; i++)
			{
				fout << i << "\t";

				switch (idtable.table[i].idtype)
				{
				case IT::IDTYPE::V:
					if (idtable.table[i].iddatatype == 1)
					{
						fout << idtable.table[i].parentBlockName << idtable.table[i].id << " - id, integer, V, значение: " << idtable.table[i].value.vint << std::endl;
					}
					else
					{
						fout << idtable.table[i].parentBlockName << idtable.table[i].id << " - id, string, V, значение: [" << (int)idtable.table[i].value.vstr->len << "]" << idtable.table[i].value.vstr->str << std::endl;
					}
					break;

				case IT::IDTYPE::F:
					if (idtable.table[i].iddatatype == 1)
					{
						fout << idtable.table[i].id << " - id, integer, F" << std::endl;
					}
					else
					{
						fout << idtable.table[i].id << " - id, string, F" << std::endl;
					}
					break;

				case IT::IDTYPE::P:
					if (idtable.table[i].iddatatype == 1)
					{
						fout << idtable.table[i].parentBlockName << idtable.table[i].id << " - id, integer, P, значение: " << idtable.table[i].value.vint << std::endl;
					}
					else
					{
						fout << idtable.table[i].parentBlockName << idtable.table[i].id << " - id, string, P, значение: [" << (int)idtable.table[i].value.vstr->len << "]" << idtable.table[i].value.vstr->str << std::endl;
					}
					break;

				case IT::IDTYPE::L:
					if (idtable.table[i].iddatatype == INT)
					{
						fout << "L" << idtable.table[i].idxfirstLE << " - L, integer, значение: " << idtable.table[i].value.vint << std::endl;
					}
					else
					{
						fout << "L" << idtable.table[i].idxfirstLE << " - L, string, значение: [" << (int)idtable.table[i].value.vstr->len << "]" << idtable.table[i].value.vstr->str << std::endl;
					}
					break;

				case IT::IDTYPE::O:
					fout << idtable.table[i].id << std::endl;
					break;

				default:
					break;
				}
			}
		}
		else
		{
			throw ERROR_THROW(132);
		}

		fout.close();
	}
}