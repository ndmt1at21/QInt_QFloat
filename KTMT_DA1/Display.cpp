#include "Display.h"
#include "Graphics//Button.h"
#include <vector>
#include <string>
#include "Graphics/Rect.h"
#include "QInt.h"
#include "QFloat.h"

void Display::run(std::wstring opt) {
	++check;
	if (!storeInputNumber.empty()) {
		storeOpr_Opt.push_back(storeInputNumber);
		storeOpr_Opt.push_back(opt);
	}
	else
		storeOpr_Opt.push_back(opt);
	storeInputNumber.clear();
}

void Display::Run(std::wstring opt) {
	if (opt == L"del")
	{
		if (!storeInputNumber.empty())
			storeInputNumber.pop_back();
	}

	if (opt == L"+" || opt == L"mult" || opt == L"div" || opt == L"mod" || opt == L"and" || opt == L"or" || opt == L"xor" || opt == L"Lsh" || opt == L"Rsh")
	{
		run(opt);
		beforeIsNum = false;
		beforeIsOpt = true;
	}

}
void Display::Calc(std::wstring opt, MODE _sys) {
	std::string opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[0]);
	QInt Opr1(opr1, _sys);

	std::string opr2 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[2]);
	QInt Opr2(opr2, _sys);

	std::string tmp;
	QInt result;
	if (opt == L"+")
		result = Opr1 + Opr2;
	if (opt == L"-")
		result = Opr1 - Opr2;
	if (opt == L"mult")
		result = Opr1 * Opr2;
	if (opt == L"div")
		result = Opr1 / Opr2;
	if (opt == L"mod")
		result = Opr1 % Opr2;
	if (opt == L"and")
		result = Opr1 & Opr2;
	if (opt == L"or")
		result = Opr1 | Opr2;
	if (opt == L"xor")
		result = Opr1 ^ Opr2;
	if (_sys == hex)
		tmp = result.to_hex();
	if (_sys == dec)
		tmp = result.to_dec();
	if (_sys == bin)
		tmp = result.to_bin();
	m_result = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
}
void Display::getChar(wchar_t character) {
	storeInputNumber += character;
}
void Display::Lsh_Rsh(std::wstring opt, MODE mode) {
	std::string opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[0]);
	QInt Opr1(opr1, mode);

	std::string opr2 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[2]);
	std::stringstream stream(opr2);

	uint Opr2;
	stream >> Opr2;
	std::string tmp;
	QInt result;
	if (opt == L"Lsh")
		result = Opr1 << Opr2;
	if (opt == L"Rsh")
		result = Opr1 >> Opr2;
	if (mode == hex)
		tmp = result.to_hex();
	if (mode == dec)
		tmp = result.to_dec();
	if (mode == bin)
		tmp = result.to_bin();
	m_result = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
}
void Display::Not(MODE mode) {
	std::string opr1;
	if (storeOpr_Opt.size() == 1) {
		opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[0]);
		storeOpr_Opt.clear();
	}
	else
		opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
	QInt Opr1(opr1, mode);

	std::string tmp;
	QInt result = ~(Opr1);
	switch (mode) {
	case dec:
		tmp = result.to_dec();
		break;
	case hex:
		tmp = result.to_hex();
		break;
	case bin:
		tmp = result.to_bin();
		break;
	}

	storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
}

void Display::DrawLine(mt::Rectangle line, int x, int y) {
	line.setPosition(mt::Vector2i(x, y));
	line.setFillAttribute(mt::Vector2i(mt::PIXEL_THREEQUARTERS, mt::Color::BG_BLUE | mt::Color::FG_BLUE));
	draw(&line);
}

bool Display::OnUserCreate() // dùng cho load tài nguyên
{
	//Load button
	for (int i = 0; i < but.size(); ++i) {
		mButton[but[i]] = new mt::Sprite(L"Asset/Button/" + but[i] + L".spr");
		mButton_h[but[i]] = new mt::Sprite(L"Asset/Button/" + but[i] + L"s.spr");
	}

	//Load Number system
	for (int i = 0; i < numsys.size(); ++i) {
		mNumSys[numsys[i]] = new mt::Sprite(L"Asset/NumSys/" + numsys[i] + L".spr");
	}

	int width = mButton[L"+"]->getWidth();
	int heigth = mButton[L"+"]->getHeight();

	{	//Set Number system
		int h = 40;
		for (int i = 0; i < numsys.size(); ++i) {
			mNumSys[numsys[i]]->setPosition(mt::Vector2i(0, h));
			h += heigth + 1;
		}
	}

	{	//Set button
		int h = 62;
		int j = 3;
		for (int i = 0; i < but.size(); i++)
		{
			if (i % 6 == 0 && i != 0)
			{
				h += heigth + 1;
				j = 3;
			}

			mButton[but[i]]->setPosition(mt::Vector2i(j * (width + 1), h));
			mButton_h[but[i]]->setPosition(mt::Vector2i(j * (width + 1), h));
			j++;
		}
	}

	return true;
}

bool Display::OnUserUpdate(float fElapseTime) // dung update, xu ly
{
	mt::Event event;

	mt::Rectangle BackGround(mt::Vector2i(m_nScreenWidth, m_nScreenHeight));
	BackGround.setPosition(mt::Vector2i(0, 0));
	BackGround.setFillAttribute(mt::Vector2i(mt::PIXEL_THREEQUARTERS, mt::Color::BG_GREY | mt::Color::FG_GREY));
	draw(&BackGround);

	int h = 62;
	int j = 0;
	int width = mButton[L"+"]->getWidth();
	int heigth = mButton[L"+"]->getHeight();

	//	Draw number system
	if (isfloat == false)
		for (int i = 0; i < numsys.size(); ++i) {
			draw(mNumSys[numsys[i]]);
		}
	else
		for (int i = 1; i < numsys.size(); ++i) {
			draw(mNumSys[numsys[i]]);
		}


	// Draw button
	for (int i = 0; i < but.size(); ++i) {
		switch (Sys)
		{
		case hex:
			draw(mButton[but[i]]);
			if (but[i] == L"dot")
				draw(mButton_h[but[i]]);
			break;
		case dec:
			draw(mButton[but[i]]);
			if (but[i] == L"charA" || but[i] == L"charB" || but[i] == L"charC" || but[i] == L"charD" || but[i] == L"charE" || but[i] == L"charF")
				draw(mButton_h[but[i]]);
			if (isfloat == true) {
				if (but[i] == L"mod" || but[i] == L"and" || but[i] == L"or" || but[i] == L"xor" || but[i] == L"not" || but[i] == L"div" || but[i] == L"+" || but[i] == L"-" || but[i] == L"mult" || but[i] == L"div" || but[i] == L"=" || but[i] == L"Lsh" || but[i] == L"Rsh")
					draw(mButton_h[but[i]]);
			}
			break;
		case bin:
			draw(mButton[but[i]]);
			if (but[i] == L"charA" || but[i] == L"charB" || but[i] == L"charC" || but[i] == L"charD" || but[i] == L"charE" || but[i] == L"charF" || but[i] == L"2" || but[i] == L"3" || but[i] == L"4" || but[i] == L"5" || but[i] == L"6" || but[i] == L"7" || but[i] == L"8" || but[i] == L"9")
				draw(mButton_h[but[i]]);
			if (isfloat == true) {
				if (but[i] == L"mod" || but[i] == L"and" || but[i] == L"or" || but[i] == L"xor" || but[i] == L"not" || but[i] == L"div" || but[i] == L"+" || but[i] == L"-" || but[i] == L"mult" || but[i] == L"div" || but[i] == L"=" || but[i] == L"Lsh" || but[i] == L"Rsh")
					draw(mButton_h[but[i]]);
			}
			break;
		default:
			break;
		}
	}

	mt::Rectangle line(mt::Vector2i(1, heigth));
	for (int i = 0; i < numsys.size(); ++i) {
		mt::Button NumSys(mNumSys[numsys[i]]);

		if (NumSys.isClicked()) {
			if (isfloat == false) {
				if (storeOpr_Opt.empty() && storeInputNumber != L"" || storeOpr_Opt.size() == 1) {
					if (storeOpr_Opt.size() == 1) {
						storeInputNumber = storeOpr_Opt[0];
						storeOpr_Opt.clear();
					}
					if (numsys[i] == L"hex") {
						std::string num = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
						QInt Num(num, Sys);
						std::string tmp = Num.to_hex();
						storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
						Sys = hex;
					}
					if (numsys[i] == L"dec") {
						std::string num = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
						QInt Num(num, Sys);
						std::string tmp = Num.to_dec();
						storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
						Sys = dec;
					}
					if (numsys[i] == L"bin") {
						std::string num = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
						QInt Num(num, Sys);
						std::string tmp = Num.to_bin();
						storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
						Sys = bin;
					}
				}
				else if (numsys[i] == L"hex") {
					Sys = hex;
				}
				else if (numsys[i] == L"dec") {
					Sys = dec;
				}
				else if (numsys[i] == L"bin") {
					Sys = bin;
				}
			}
			else {
				if (storeOpr_Opt.empty() && storeInputNumber != L"") {
					if (numsys[i] == L"dec") {
						std::string num = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
						QFloat Num(num, Sys);
						std::string tmp = Num.to_dec(20);
						storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
						Sys = dec;
					}
					if (numsys[i] == L"bin") {
						std::string num = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeInputNumber);
						QFloat Num(num, Sys);
						std::string tmp = Num.to_bin();
						storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
						Sys = bin;
					}
				}
			}
		}
	}
	switch (Sys)
	{
	case hex:
		if (isfloat == false)
			DrawLine(line, width - 1, 39);
		break;
	case dec:
		DrawLine(line, width - 1, 47);
		break;
	case bin:
		DrawLine(line, width - 1, 55);
		break;
	default:
		break;
	}

	// Drawing button is hovered
	for (int i = 0; i < but.size(); ++i) {
		mt::Button isHover(mButton[but[i]]);

		if (isHover.isInside())
		{
			draw(mButton_h[but[i]]);
		}
		if (isHover.isClicked())	//Manage when being clicked
		{
			switch (Sys)
			{
			case hex:
				if (but[i] == L"-") {
					if (storeOpr_Opt.empty() && storeInputNumber.empty()) {
						storeOpr_Opt.push_back(L"0");
						run(L"-");
					}
					else if (beforeIsNum || (!storeInputNumber.empty()) && (!beforeIsOpt)) {
						run(L"-");

						beforeIsOpt = true;
						beforeIsNum = false;
					}
					else if (beforeIsOpt) {
						if (storeOpr_Opt.back() == L"-") {
							storeOpr_Opt.pop_back();
							storeOpr_Opt.push_back(L"+");
						}
						else {
							if (isNegative) {
								storeInputNumber.clear();
								isNegative = false;
							}
							else {
								storeInputNumber += L"-";
								isNegative = true;
							}
						}
					}
				}
				if (!beforeIsNum) {
					if (but[i] == L"0" || but[i] == L"1" || but[i] == L"2" || but[i] == L"3" || but[i] == L"4" || but[i] == L"5" || but[i] == L"6" || but[i] == L"7" || but[i] == L"8" || but[i] == L"9") {
						storeInputNumber += but[i];
						justStart = false;
						beforeIsOpt = false;
					}
					else if (but[i].substr(0, 4) == L"char") {
						getChar(but[i].back());
						beforeIsOpt = false;
					}
				}
				if (but[i] == L"C")
				{
					check = 0;
					storeInputNumber.clear();
					storeOpr_Opt.clear();
					beforeIsNum = false;
				}
				if (but[i] == L"CE")
				{
					if (!storeInputNumber.empty())
						storeInputNumber.clear();
					beforeIsNum = false;
				}
				if (!justStart) {
					if (!beforeIsOpt) {
						Run(but[i]);
					}
					if (!storeInputNumber.empty() && but[i] == L"not" || storeOpr_Opt.size() == 1 && but[i] == L"not")
					{
						Not(hex);
						beforeIsNum = false;
					}
					if (!storeInputNumber.empty() && !storeOpr_Opt.empty() && but[i] == L"=")
					{
						++isCalc;
						storeOpr_Opt.push_back(storeInputNumber);
						storeInputNumber.clear();

						Calc(storeOpr_Opt[1], hex);

						if (storeOpr_Opt[1] == L"Lsh")
						{
							Lsh_Rsh(L"Lsh", hex);
						}
						if (storeOpr_Opt[1] == L"Rsh")
						{
							Lsh_Rsh(L"Rsh", hex);
						}
						beforeIsOpt = false;
						beforeIsNum = true;
					}
				}
				break;
			case dec:
				if (but[i] == L"-") {
					if (storeOpr_Opt.empty() && storeInputNumber.empty()) {
						storeOpr_Opt.push_back(L"0");
						run(L"-");
					}
					else if (beforeIsNum || (!storeInputNumber.empty()) && (!beforeIsOpt)) {
						run(L"-");

						beforeIsOpt = true;
						beforeIsNum = false;
					}
					else if (beforeIsOpt) {
						if (storeOpr_Opt.back() == L"-") {
							storeOpr_Opt.pop_back();
							storeOpr_Opt.push_back(L"+");
						}
						else {
							if (isNegative) {
								storeInputNumber.clear();
								isNegative = false;
							}
							else {
								storeInputNumber += L"-";
								isNegative = true;
							}
						}
					}
				}
				if (!beforeIsNum) {
					if (but[i] == L"0" || but[i] == L"1" || but[i] == L"2" || but[i] == L"3" || but[i] == L"4" || but[i] == L"5" || but[i] == L"6" || but[i] == L"7" || but[i] == L"8" || but[i] == L"9") {
						storeInputNumber += but[i];
						justStart = false;
						beforeIsOpt = false;
					}
					if (!storeInputNumber.empty() && but[i] == L"dot") {
						isfloat = true;
						storeInputNumber += L".";
						beforeIsOpt = false;
					}
				}
				if (but[i] == L"C")
				{
					check = 0;
					storeInputNumber.clear();
					storeOpr_Opt.clear();
					beforeIsNum = false;
				}
				if (but[i] == L"CE")
				{
					if (!storeInputNumber.empty())
						storeInputNumber.clear();
					beforeIsNum = false;
				}
				if (!justStart) {
					if (!beforeIsOpt) {
						Run(but[i]);
					}
					if (!storeInputNumber.empty() && but[i] == L"not" || storeOpr_Opt.size() == 1 && but[i] == L"not")
					{
						Not(dec);
						beforeIsNum = false;
					}
					if (!storeInputNumber.empty() && !storeOpr_Opt.empty() && but[i] == L"=")
					{
						++isCalc;
						storeOpr_Opt.push_back(storeInputNumber);
						storeInputNumber.clear();

						Calc(storeOpr_Opt[1], dec);

						if (storeOpr_Opt[1] == L"Lsh")
						{
							Lsh_Rsh(L"Lsh", dec);
						}
						if (storeOpr_Opt[1] == L"Rsh")
						{
							Lsh_Rsh(L"Rsh", dec);
						}
						beforeIsNum = true;
						beforeIsOpt = false;
					}
				}
				break;
			case bin:
				if (but[i] == L"-") {
					if (storeOpr_Opt.empty() && storeInputNumber.empty()) {
						storeOpr_Opt.push_back(L"0");
						run(L"-");
					}
					else if (beforeIsNum || (!storeInputNumber.empty()) && (!beforeIsOpt)) {
						run(L"-");

						beforeIsOpt = true;
						beforeIsNum = false;
					}
					else if (beforeIsOpt) {
						if (storeOpr_Opt.back() == L"-") {
							storeOpr_Opt.pop_back();
							storeOpr_Opt.push_back(L"+");
						}
						else {
							if (isNegative) {
								storeInputNumber.clear();
								isNegative = false;
							}
							else {
								storeInputNumber += L"-";
								isNegative = true;
							}
						}
					}
				}
				if (!beforeIsNum) {
					if (but[i] == L"0" || but[i] == L"1") {
						storeInputNumber += but[i];
						justStart = false;
						beforeIsOpt = false;
					}
					if (!storeInputNumber.empty() && but[i] == L"dot") {
						isfloat = true;
						storeInputNumber += L".";
						beforeIsOpt = false;
					}
				}
				if (but[i] == L"C")
				{
					check = 0;
					storeInputNumber.clear();
					storeOpr_Opt.clear();
					beforeIsNum = false;
				}
				if (but[i] == L"CE")
				{
					if (!storeInputNumber.empty())
						storeInputNumber.clear();
					beforeIsNum = false;
				}
				if (!justStart) {
					if (!beforeIsOpt) {
						Run(but[i]);
					}
					if (!storeInputNumber.empty() && but[i] == L"not" || storeOpr_Opt.size() == 1 && but[i] == L"not")
					{
						Not(bin);
						beforeIsNum = false;
					}
					if (but[i] == L"=")
					{
						++isCalc;
						storeOpr_Opt.push_back(storeInputNumber);
						storeInputNumber.clear();

						Calc(storeOpr_Opt[1], bin);

						if (storeOpr_Opt[1] == L"Lsh")
						{
							Lsh_Rsh(L"Lsh", bin);
						}
						if (storeOpr_Opt[1] == L"Rsh")
						{
							Lsh_Rsh(L"Rsh", bin);
						}
						beforeIsNum = true;
						beforeIsOpt = false;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	if (check == 1 && !storeOpr_Opt.empty()) {
		mt::Text txt(storeOpr_Opt[0], L"big", 2);// 0 can trai, 1 can mid, 2 can phai
		txt.setPosition(mt::Vector2i(176, 3));
		draw(&txt);
	}
	else if (check > 1) {
		switch (Sys)
		{
		case hex:
			if (storeOpr_Opt.size() > 2)
				Calc(storeOpr_Opt[1], hex);
			if (storeOpr_Opt.size() == 2 && storeOpr_Opt[1] == L"not")
			{
				std::string opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[2]);
				QInt Opr1(opr1, hex);

				std::string tmp;
				QInt result = ~Opr1;
				tmp = result.to_hex();
				storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Lsh")
			{
				Lsh_Rsh(L"Lsh", hex);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Rsh")
			{
				Lsh_Rsh(L"Rsh", hex);
			}
			break;
		case dec:
			if (storeOpr_Opt.size() > 2)
				Calc(storeOpr_Opt[1], dec);
			if (storeOpr_Opt.size() == 2 && storeOpr_Opt[1] == L"not")
			{
				std::string opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[0]);
				QInt Opr1(opr1, dec);

				std::string tmp;
				QInt result = ~Opr1;
				tmp = result.to_dec();
				storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Lsh")
			{
				Lsh_Rsh(L"Lsh", dec);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Rsh")
			{
				Lsh_Rsh(L"Rsh", dec);
			}
			break;
		case bin:
			if (storeOpr_Opt.size() > 2)
				Calc(storeOpr_Opt[1], bin);
			if (storeOpr_Opt.size() == 2 && storeOpr_Opt[1] == L"not")
			{
				std::string opr1 = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(storeOpr_Opt[2]);
				QInt Opr1(opr1, bin);

				std::string tmp;
				QInt result = ~Opr1;
				tmp = result.to_bin();
				storeInputNumber = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(tmp);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Lsh")
			{
				Lsh_Rsh(L"Lsh", bin);
			}
			else if (storeOpr_Opt.size() > 2 && storeOpr_Opt[1] == L"Rsh")
			{
				Lsh_Rsh(L"Rsh", bin);
			}
			break;
		default:
			break;
		}

		if (storeOpr_Opt.size() > 2) {
			std::wstring str = storeOpr_Opt.back();
			storeOpr_Opt.clear();
			storeOpr_Opt.push_back(m_result);
			storeOpr_Opt.push_back(str);

		}
		check = 1;
	}

	if (isCalc > 0) {
		storeOpr_Opt.clear();
		storeOpr_Opt.push_back(m_result);
		storeInputNumber.clear();
		isCalc = 0;
	}

	mt::Text txt1(storeInputNumber, L"big", 2);// 0 can trai, 1 can mid, 2 can phai
	txt1.setPosition(mt::Vector2i(176, 15));
	draw(&txt1);

	return true;
}

bool Display::OnUserDestroy()
{
	return true;
}