﻿#include "Alg_Elements.h"

#define LTOR 0
#define TTOD 1


//---------------------ItemRule---------------------

void ItemRule::SetRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r) 
{
	left = inp_l;
	right = inp_r;
}

void ItemRule::PrintRule() 
{
	cout << string(left) << " ::= ";
	for (unsigned i = 0; i < right.size(); i++) {
		right[i].PrintString();
		if (right.size() - i != 1) cout << "|";

	}
}

//---------------------LtoR_Line---------------------

void LtoR_Line::SetLine(const string & inp_str, const RuleNum & inp_rnum) 
{
	cur_string = inp_str;
	rule_num = inp_rnum;
}

void LtoR_Line::PrintLine()
{
	string str_for_print;
	for (int i = 0; i < cur_string.size(); i++) {
		if (cur_string[i] != '\n') {
			str_for_print += cur_string[i];
		}
	}

	cout << "Строка: " << str_for_print;
	if (rule_num.fir_num > -1) {
		cout << " Правило: " << rule_num.fir_num + 1 << char(rule_num.sec_num + 224) << endl;
	}
	else
		if (rule_num.sec_num == -3) {
			cout << "       конец!" << endl;
		}
		else if (rule_num.sec_num == -4) {
			cout << "       разбор дальше невозможен!" << endl;
		}
		else {
			cout << "       тупик!" << endl;
		}
}

vector<string> LtoR_Line::GetLine()
{
	vector<string> line;
	string cur_string = GetCurString();
	string str_for_print;

	for (int i = 0; i < cur_string.size(); i++) {
		if (cur_string[i] != '\n') {
			str_for_print += cur_string[i];
		}
	}
	line.push_back(str_for_print);

	RuleNum rule_num = GetRuleNum();

	if (rule_num.fir_num > -1) {
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224));
	}
	else
		if (rule_num.sec_num == -3) {
			line.push_back("Конец разбора");
		}
		else if (rule_num.sec_num == -4) {
			line.push_back("Разбор дальше невозможен!");
		}
		else {
			line.push_back("Тупик!");
		}
	return line;
}



//---------------------ParseLog---------------------

void ParseLog::PrintLogltoR() 
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<LtoR_Line *>(records[i])->PrintLine();
	}
}

void ParseLog::PrintLogTtoD()
{
	cout << endl << endl << "Лог:" << endl;
	for (int i = 0; i < records.size(); i++) {
		dynamic_cast<TtoD_Line *>(records[i])->PrintLine();
	}
}



//---------------------TtoD_Line---------------------

void TtoD_Line::SetLine(const string & rec_str, const string & pars_str, const string & targ_str, unsigned type_of_line, const RuleNum & inp_rnum)
{
	recognized = rec_str;
	cur_string = pars_str;
	target = targ_str;
	type = type_of_line;
	rule_num = inp_rnum;
}

void TtoD_Line::PrintLine()
{
	cout << endl << "Распознано: " << MakePrintable(recognized);
	cout << " Строка: " << MakePrintable(cur_string);
	cout << " Цель: " << MakePrintable(target);
	cout << "   ";
	switch (type)
	{
	case 1:
		cout << "?" << endl;
		break;
	case 2:
		cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224) << " - ?" << endl;
		break;
	case 3:
		if (rule_num.sec_num == 0) {
			cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224);
		}
		else {
			cout << rule_num.fir_num+1 << "a..." << char(rule_num.sec_num + 224);
		}
		cout << " - нет" << endl;
		break;
	case 4:
		cout << rule_num.fir_num+1 << char(rule_num.sec_num + 224) << " - да" << endl;
		break;
	}
	
}

vector<string> TtoD_Line::GetLine()
{
	vector<string> line;
	line.push_back(MakePrintable(recognized));
	line.push_back(MakePrintable(cur_string));
	line.push_back(MakePrintable(target));

	switch (type)
	{
	case 1:
		line.push_back("?");
		break;
	case 2:
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - ?");
		break;
	case 3:
		if (rule_num.sec_num == 0) {
			line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - нет");
		}
		else {
			line.push_back(to_string(rule_num.fir_num + 1) + "а..." + char(rule_num.sec_num + 224) + " - нет");
		}
		break;
	case 4:
		line.push_back(to_string(rule_num.fir_num + 1) + char(rule_num.sec_num + 224) + " - да");
		break;
	}
	return line;
}

string TtoD_Line::MakePrintable(string & str_with_seps)
{
	string str_for_print;
	for (int i = 0; i < str_with_seps.size(); i++) {
		if (str_with_seps[i] != '\n') {
			str_for_print += str_with_seps[i];
		}
	}
	return str_for_print;
}


/*
void ParseAlgorithm::SetLogTable(unsigned type_alg)
{
	table_model->SetRowCount(parsing_log.Size());
	switch (type_alg)
	{
	case LTOR: {
		table_model->SetColomnCount(2);
		break;
		//table_view->headerData(1, "dfrg");
	}
	case TTOD: {
		table_model->SetColomnCount(4);
		break;
	}
	}
}
*/