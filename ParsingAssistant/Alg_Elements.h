#pragma once
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

struct RuleNum { int fir_num; int sec_num; };

//-----------------------------------------------------------------


class RecordLine {

protected:

	string cur_string;
	RuleNum rule_num;

public:

	virtual void PrintLine() = 0;

	string GetCurString() { return cur_string; }
	RuleNum GetRuleNum() { return rule_num; }
};


//-----------------------------------------------------------------

class LtoR_Line : public RecordLine {

public:

	void SetLine(const string & inp_str, const RuleNum & inp_rnum);
	void PrintLine() override;
};

//-----------------------------------------------------------------

class TtoD_Line : public RecordLine {

	string recognized;
	string target;
	unsigned type;

public:

	void SetLine(const string & rec_str, const string & pars_str, const string & targ_str, unsigned type_of_line, const RuleNum & inp_rnum);
	void PrintLine() override;

	void MarkRollback() { rule_num.sec_num++; }
	string MakePrintable(string & str_with_seps);
	string GetRecString() { return recognized; }
	string GetTargString() { return target; }
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

	RecordLine * &operator[] (int i) { return records[i]; }
};

//-----------------------------------------------------------------
/*
class ParseAlgorithm {

protected:

	vector<ItemRule> rules;
	ItemString parsing_str;
	ParseLog parsing_log;

	LogTable * table_model;

public:

	ParseAlgorithm() { table_model = new LogTable; }
	ParseAlgorithm(ItemString& inp_str) {
		parsing_str = inp_str;
		table_model = new LogTable;
	}

	ItemRule & GetRule(unsigned i) { return rules[i]; }
	unsigned RulesSize() { return rules.size(); }
	void SetLogTable(unsigned type_alg);
	LogTable * GetTable() { return table_model; }

	//void SetParsingStr(ItemString inp_str) { parsing_str = inp_str; }

	virtual void SetParsingStr(ItemString inp_str) = 0;
	virtual void SetRulesOfAlg() = 0;
	virtual bool DoParse() = 0;
};
*/

//-----------------------------------------------------------------
