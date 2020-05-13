#pragma once
#include <iostream>
#include "ndmtEngine.h"
#include <stdlib.h>
#include <locale>
#include <codecvt>
#include "QInt.h"
#include "QFloat.h"
#include <sstream>
#include "Mode.h"


class Display : public mt::ndmtEngine
{
private:
	MODE Sys = MODE::dec; //default

	bool isNegative = false;
	bool justStart = true;
	bool beforeIsOpt = false;
	bool beforeIsNum = false;
	bool isfloat = false;	//see if input num is float or not
	int isCalc = 0;	//see if "=" is clicked or not
	int check = 0;	//if operator is clicked 2 times then calc and store to head of vector
	std::wstring m_result;

	std::vector<std::wstring> storeOpr_Opt;	//Store operands and operator
	std::wstring storeInputNumber; //store each operand and push to calc
	std::map<std::wstring, mt::Sprite*> mShow;

	//Not hover
	std::map<std::wstring, mt::Sprite*> mButton;
	std::map<wchar_t, mt::Sprite*> mNum;
	std::map<std::wstring, mt::Sprite*> mNumSys;

	//Is hover
	std::map<std::wstring, mt::Sprite*> mButton_h;

	std::vector<std::wstring> but = { L"Lsh", L"Rsh", L"or", L"xor", L"not", L"and", L"empty", L"mod", L"CE", L"C", L"del", L"div", L"charA", L"charB", L"7", L"8", L"9", L"mult", L"charC", L"charD", L"4", L"5", L"6", L"-", L"charE", L"charF", L"1", L"2", L"3", L"+", L"empty1", L"empty2", L"empty3", L"0", L"dot", L"=" };
	std::vector<std::wstring> numsys = { L"hex", L"dec", L"bin" };  	//Number system}

	void run(std::wstring str);
	void Run(std::wstring str);
	void Calc(std::wstring opt, MODE _sys);
	void getChar(wchar_t character);
	void Lsh_Rsh(std::wstring opt, MODE mode);
	void Not(MODE mode);

	void DrawLine(mt::Rectangle line, int x, int y);
public:

	bool OnUserCreate(); // dùng cho load tài nguyên
	bool OnUserUpdate(float fElapseTime); // dung update, xu ly
	bool OnUserDestroy();
};

