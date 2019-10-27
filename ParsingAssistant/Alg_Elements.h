﻿#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Elements.h"
//#include "LogTable.h"

using namespace std;

//-----------------------------------------------------------------

class ItemRule {

	ItemSymb left;
	vector<ItemString> right;

public:

	ItemRule() {}
	ItemRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r) : left(inp_l), right(inp_r) {}

	void SetRule(const ItemSymb & inp_l, const vector <ItemString> & inp_r);
	int RightSize() { return right.size(); }
	ItemSymb GetLeft() { return left; }
	ItemString GetRight(unsigned i) { return right[i]; }
	void PrintRule();

	ItemString &operator[] (const int i) { return right[i]; }
};

//-----------------------------------------------------------------

struct RuleNum { 
	int fir_num; 
	int sec_num; 

	bool operator == (const RuleNum& other_rule) const {
		return this->fir_num == other_rule.fir_num && this->sec_num == other_rule.sec_num;
	}
};

//-----------------------------------------------------------------


class RecordLine {

protected:

	string cur_string;
	RuleNum rule_num;

public:

	virtual void PrintLine() = 0;
	virtual TypeOfAlg GetType() = 0;

	string GetCurString() { return cur_string; }
	RuleNum GetRuleNum() { return rule_num; }

	virtual vector<string>  GetLine() = 0;
};


//-----------------------------------------------------------------

class LtoR_Line : public RecordLine {

public:

	void SetLine(const string & inp_str, const RuleNum & inp_rnum);
	void PrintLine() override;
	vector<string>  GetLine() override;

	TypeOfAlg GetType() override;
};

//-----------------------------------------------------------------

class TtoD_Line : public RecordLine {

	string recognized;
	string target;
	unsigned type;
	TypeOfTtoDLine type_of_line;

public:

	TypeOfAlg GetType() override;

	//void SetLine(const string & rec_str, const string & pars_str, const string & targ_str, unsigned type_of_line, const RuleNum & inp_rnum);
	void SetLine(const string& rec_str, const string& pars_str,
		const string& targ_str, unsigned type_of_l,
		TypeOfTtoDLine line_type, const RuleNum& inp_rnum);
	void PrintLine() override;
	vector<string>  GetLine() override;

	void MarkLastLine() { type_of_line = END_LINE; }
	void MarkRollback() { rule_num.sec_num++; }
	void TypeMarkRollback() { type_of_line = TypeOfTtoDLine::ROLLB_IMPOSS; }
	string MakePrintable(string & str_with_seps);
	string GetRecString() { return recognized; }
	string GetTargString() { return target; }
	TypeOfTtoDLine& GetTypeOfLine() { return type_of_line; }
};

//-----------------------------------------------------------------

class LLk_TtoD_Line : public RecordLine {

	string stack_str;
	//unsigned type;
	//TypeOfTtoDLine type_of_line;

public:

	TypeOfAlg GetType() override;
	vector<string>  GetLine() override;

	void SetLine(const string& pars_str,
		const string& st_str, const RuleNum& inp_rnum);
	void PrintLine() override;

	string GetStackString() { return stack_str; }

	//void MarkRollback() { rule_num.sec_num++; }
	//void TypeMarkRollback() { type_of_line = TypeOfTtoDLine::ROLLB_IMPOSS; }
	//string MakePrintable(string& str_with_seps);
	//string GetRecString() { return recognized; }

	//TypeOfTtoDLine& GetTypeOfLine() { return type_of_line; }
};

//-----------------------------------------------------------------



class ParseLog {
	vector<RecordLine *> records;
public:

	ParseLog() {}

	void AddRecordLine(RecordLine *inp_rec) { records.push_back(inp_rec); }
	int Size() { return records.size(); }
	void PrintLogltoR();
	void PrintLogTtoD();
	void PrintLogLLk();

	void ClearRecords() { records.clear(); }

	RecordLine * &operator[] (int i) { return records[i]; }
};

//-----------------------------------------------------------------

