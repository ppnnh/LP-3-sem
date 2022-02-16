#include "stdafx.h"

#define GRB_ERROR_SERIES 600

namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Rule::Chain::Chain(short symbolCount, GRBALPHABET s, ...)
	{
		this->size = symbolCount;
		this->chainOfTerm_nTerm = new GRBALPHABET[symbolCount];
		int* ptr = (int*)&s;
		for (int i = 0; i < symbolCount; i++)
		{
			this->chainOfTerm_nTerm[i] = (GRBALPHABET)ptr[i];
		}
	}

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
	{
		this->nn = pnn;
		this->iderror = piderror;
		this->size = psize;
		this->chains = new Chain[psize];
		Chain* p = &c;
		for (int i = 0; i < size; i++)
		{
			this->chains[i] = p[i];
		}
	}

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	{
		this->startN = pstartN;
		this->stbottomT = pstbottom;
		this->size = psize;
		this->rules = new Rule[psize];
		Rule* p = &r;
		for (int i = 0; i < size; i++)
		{
			rules[i] = p[i];
		}
	}

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, k = 0;
		while (k < this->size && rules[k].nn != pnn)
		{
			k++;
		}
		if (k < this->size)
		{
			rc = k;
			prule = rules[k];
		}
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < this->size)
		{
			rc = rules[n];
		}
		return rc;
	}
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < this->size; i++)
		{
			b[i] = Chain::alphabet_to_char(this->chainOfTerm_nTerm[i]);
		}
		b[this->size] = 0x00;
		return b;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(this->nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		this->chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < this->size && this->chains[j].chainOfTerm_nTerm[0] != t)
		{
			++j;
		}
		rc = (j < this->size ? j : -1);
		if (rc >= 0)
		{
			pchain = chains[rc];
		}
		return rc;
	}

	Greibach greibach(NS('S'), TS('$'),
		5,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0, //структура программы
			3, // S -> tfi(F){N};S | tfi(){N};S  | m{N};
			Rule::Chain(11, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(5, TS('m'), TS('{'), NS('N'), TS('}'), TS(';'))
		),

		Rule(
			NS('F'), GRB_ERROR_SERIES + 1, //параметры
			2, // F -> ti | ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))

		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 2, //выражения
			6, // N -> dti;N | dti=E;N | i=E;N | dtfi(F);N | pE;N | rE;
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('r'), NS('E'), TS(';'))
		),

		Rule(
			NS('W'), GRB_ERROR_SERIES + 3, //параметры в передаваемую функцию
			4, // W -> i | l | i,W | l,W | 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),

		Rule(
			NS('E'), GRB_ERROR_SERIES + 2, //выражения
			8, // E -> i | l | (E) | i(W) | ivE | lvE | (E)vE | i(W)vE
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('v'), NS('E')),
			Rule::Chain(3, TS('l'), TS('v'), NS('E')),
			Rule::Chain(5, TS('('), NS('E'), TS(')'), TS('v'), NS('E')),
			Rule::Chain(6, TS('i'), TS('('), NS('W'), TS(')'), TS('v'), NS('E'))
		)
	);

	Greibach getGreibach()
	{
		return greibach;
	}
}