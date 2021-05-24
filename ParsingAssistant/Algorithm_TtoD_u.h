#pragma once
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "Basic_Algorithm_u.h"


class TtoD_MethodAlg_u : public ParseAlgorithm {

	ItemString target_str;
	ItemString recognized_str;
	bool rollback_flag;
	int rollback_step;

public:

	void SetRulesOfAlg() override;
	bool DoParse() override;
	void SetParsingStr(ItemString inp_str) override;

	void DoParseNew();

	void SetRulesOfAlg(unsigned code_of_rules);
	ResultOfStringReceiving SetParsingStr(string inp_str, bool contains_complex_nonterminals);


private:


	//RuleNum FindRuleNum();
	//bool FindCorrectTerm(const RuleNum& rulenum);
	//void RemoveMatchingSymbs();


	//void TransformAccordingRule(const RuleNum& rulenum);
	//RuleNum Rollback();

	//-----------parsing-------------------------
	void SetStartTarget();
	bool NonTerminalLeftInTarget();
	RuleNum FindSuitableRule(const RuleNum rulenum);
	void TransformAccordingRule(const RuleNum& rule);
	bool ParsingIsOnRollbackBranch() { return rollback_flag; }
	bool RuleIsLastPossible(const RuleNum& rule);
	void MarkSourceStepAsWrongHypo();
	bool TerminalsMatched();
	void RecognizeAndClearTerminals();

	bool ParsingStrIsEmpty() { return (parsing_str.Length() == 0); }
	bool TargetStrIsEmpty() { return (target_str.Length() == 0); }

	//-----------rollback------------------------
	void ClearRollbackFlag() { rollback_flag = false; }
	void SetRollbackFlag() { rollback_flag = true; }
	int CheckForRollback();
	bool RollbackIsPossible() { return (rollback_step != -1); }
	RuleNum RollbackAndGetCurRule();
	
	//-----------logging-------------------------
	void WriteToLog(const RuleNum cur_rule_num,
		const TypeOfTtoDLine inp_status = TypeOfTtoDLine::HYPOTHESIS,
		const int inp_source_s = -1);
	ItemString RestoreStringFromLog(const string& log_str);
	string MakeStrForLog(const ItemString& orig_str);
	void MarkLastStepInLogAs(TypeOfTtoDLine mark_status); 

	//-----------recursive-------------------------
	//void DoParseNew();
	RecursiveState Recursive(const ItemString& pars_s, const ItemString& targ_s, const ItemString& rec_s);
	int FindRuleFirNum(ItemSymb parsing_element);
	const ItemSymb FindAxiom();
	ItemString TransformAccordingRule(const RuleNum& rule, ItemString targ_s);
	bool TerminalsMatched(ItemString pars_s, ItemString targ_s);

	//-----------recursive--another-------------------

	RecAnswer RecProcess(const ItemString& pars_s, const ItemString& targ_s, const ItemString& rec_s, const ItemString& full_targ);
	void WriteToLogRec(const ItemString& rec_s, const ItemString& pars_s, const ItemString& targ_s, RuleNum rule, TypeOfTtoDLine type);
};

