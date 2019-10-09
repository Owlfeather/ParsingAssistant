#pragma once
//#include "Alg_Elements.h"
#include "LogTable.h"
#include"LogComments.h"

class ParseAlgorithm {

protected:

	vector<ItemRule> rules;
	ItemString parsing_str;
	ParseLog parsing_log;


	LogTable* table_model;
	LogComments* comments_model;
	string comment_line;
	

public:

	ParseAlgorithm() 
	{ 
		table_model = new LogTable; 
		comments_model = new LogComments;
	}
	ParseAlgorithm(ItemString& inp_str) {
		parsing_str = inp_str;
		table_model = new LogTable;
		comments_model = new LogComments;
	}

	ItemRule& GetRule(unsigned i) { return rules[i]; }
	unsigned RulesSize() { return rules.size(); }
	void SetLogTableType(TypeOfAlg type_alg);
	LogTable* GetTable() { return table_model; }
	LogComments* GetComments() { return comments_model; }
	vector<ItemRule>& GetRules() { return rules; }


	//void SetParsingStr(ItemString inp_str) { parsing_str = inp_str; }

	virtual void SetParsingStr(ItemString inp_str) = 0;
	virtual void SetRulesOfAlg() = 0;
	virtual bool DoParse() = 0;
};


