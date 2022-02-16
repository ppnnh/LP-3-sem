#pragma once

#include <fstream>
#include <iostream>
#include <locale>
#include <cwchar>
#include <string>
#include <ctime>
#include <chrono>
#include <string.h>
#include <stack>
#include <queue>
#include <iomanip>

#include "Functions.h"			//	вспомогатоельные функции
#include "Error.h"				//	обработка ошибок
#include "Parm.h"				//	обработка параметров
#include "LT.h"					//  таблица лексем
#include "IT.h"					//  таблица ид
#include "PolishNotation.h"		//  Польская запись
#include "In.h"					//	ввод исходного файла
#include "Log.h"				//	работа с протоколом
#include "FST.h"				//  КА
#include "Analysis.h"			//  лексический анализ
#include "GRB.h"				//  грамматика Грейбах
#include "MFST.h"				//  МКА

#define	DEBUGGING 0				//  для показа отладочной информации