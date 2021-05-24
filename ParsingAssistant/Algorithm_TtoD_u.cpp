#include "Algorithm_TtoD_u.h"

void TtoD_MethodAlg_u::SetRulesOfAlg()
{
	//__________________________________________Создание нетерминалов

	ItemSymb c_integer(string("<Целое>"), false, true);
	ItemSymb c_unsigned_int(string("<ЦБЗ>"), false);
	ItemSymb c_number(string("<Цифра>"), false);
	ItemSymb c_sign(string("<Знак>"), false);

	vector<ItemSymb> buf_symb;					// переменная-шаблон для варианта раскрытия правила
	vector<ItemString> buf_str;					// переменная-шаблон для хранения всех вариантов раскрытия правила (правая часть правила)

	buf_symb = { c_sign, c_unsigned_int };		// <знак><цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 1

	buf_symb = { c_unsigned_int };				// <цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 2

	ItemRule rule(c_integer, buf_str);			// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	buf_symb = { c_number, c_unsigned_int };	// <цифра><цбз>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 1

	buf_symb.pop_back();						// <цифра>
	buf_str.push_back(ItemString(buf_symb));	// записали вариант 2

	rule.SetRule(c_unsigned_int, buf_str);		// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила

	//__________________________________________Создание терминалов

	for (int i = 0; i < 10; i++) {
		buf_symb = { ItemSymb(to_string(i)) };
		buf_str.push_back(ItemString(buf_symb));   // новый вариант
	}

	rule.SetRule(c_number, buf_str);			// ПРАВИЛО
	buf_str.clear();							// чистка вариантов
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	buf_symb = { ItemSymb(string("+")) };
	buf_str.push_back(ItemString(buf_symb));	// +

	buf_symb = { ItemSymb(string("-")) };
	buf_str.push_back(ItemString(buf_symb));	// -

	rule.SetRule(c_sign, buf_str);				// ПРАВИЛО
	rules.push_back(rule);						// добавление нового правила
	//----------------------------------------------------

	cout << endl << "Правила для разбора сверху вниз сформированы:" << endl << endl;
	for (unsigned i = 0; i < rules.size(); i++) {
		rules[i].PrintRule();
		cout << endl;
	}
}

void TtoD_MethodAlg_u::SetRulesOfAlg(unsigned code_of_rules) {
	if (code_of_rules == 0) { // ЛогичВыр
		ItemSymb c_Log_ex(string("<ЛогичВыр>"), false, true);
		ItemSymb c_logex(string("<ЛВыражение>"), false);
		ItemSymb c_intersection(string("<Пересечение>"), false);
		ItemSymb c_operand(string("<Операнд>"), false);
		ItemSymb c_and(string("^"));
		ItemSymb c_or(string("v"));
		ItemSymb c_left(string("("));
		ItemSymb c_right(string(")"));
		ItemSymb c_id(string("<Ид>"));

		vector<ItemSymb> buf_symb;
		vector<ItemString> buf_str;

		buf_symb = { c_logex };
		buf_str = { buf_symb };
		rules.push_back(ItemRule(c_Log_ex, buf_str));

		buf_str.clear();
		buf_symb = { c_logex, c_or, c_intersection };
		buf_str.push_back(buf_symb);
		buf_symb = { c_intersection };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_logex, buf_str));

		buf_str.clear();
		buf_symb = { c_intersection, c_and, c_operand };
		buf_str.push_back(buf_symb);
		buf_symb = { c_operand };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_intersection, buf_str));

		buf_str.clear();
		buf_symb = { c_left, c_logex, c_right };
		buf_str.push_back(buf_symb);
		buf_symb = { c_id };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_operand, buf_str));


	}
	else if (code_of_rules == 1) { // <ЛВыражение> // ПОМЕНЯЛА ТОЛЬКО ЗДЕСЬ
		ItemSymb c_logex(string("<ЛВыражение>"), false, true);
		ItemSymb c_intersection(string("<Пересечение>"), false);
		ItemSymb c_operand(string("<Операнд>"), false);
		ItemSymb c_and(string("^"));
		ItemSymb c_or(string("v"));
		ItemSymb c_left(string("("));
		ItemSymb c_right(string(")"));
		ItemSymb c_id(string("<Ид>"));

		vector<ItemSymb> buf_symb;
		vector<ItemString> buf_str;

		buf_str.clear();
		buf_symb = { c_intersection, c_or, c_logex };
		buf_str.push_back(buf_symb);
		buf_symb = { c_intersection };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_logex, buf_str));

		buf_str.clear();
		buf_symb = { c_operand, c_and,  c_intersection };
		buf_str.push_back(buf_symb);
		buf_symb = { c_operand };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_intersection, buf_str));

		buf_str.clear();
		buf_symb = { c_left, c_logex, c_right };
		buf_str.push_back(buf_symb);
		buf_symb = { c_id };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_operand, buf_str));
	}
	else if (code_of_rules == 2) { // <Оператор W> Pascal
		ItemSymb c_ax(string("<Оператор W>"), false, true);
		ItemSymb c_operator(string("<Оператор>"), false);
		ItemSymb c_sost_operator(string("<Составной оператор>"), false);
		ItemSymb c_operatory(string("<Операторы>"), false);
		ItemSymb c_tz(string(";"));
		ItemSymb c_uslovie(string("<Условие>"));
		ItemSymb c_prisv(string("<Присваивание>"));

		vector<ItemSymb> buf_symb;
		vector<ItemString> buf_str;

		buf_str.clear();
		buf_symb = { c_ax };
		buf_str.push_back(buf_symb);
		buf_symb = { c_prisv };
		buf_str.push_back(buf_symb);
		buf_symb = { c_sost_operator };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_operator, buf_str));

		buf_str.clear();
		buf_symb = { ItemSymb(string("w")), ItemSymb(string("h")), ItemSymb(string("i")), ItemSymb(string("l")), ItemSymb(string("e")), ItemSymb(string(" ")),
					c_uslovie, ItemSymb(string(" ")), ItemSymb(string("d")), ItemSymb(string("o")), ItemSymb(string(" ")), c_operator };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_ax, buf_str));

		buf_str.clear();
		buf_symb = { ItemSymb(string("b")), ItemSymb(string("e")), ItemSymb(string("g")), ItemSymb(string("i")), ItemSymb(string("n")), ItemSymb(string(" ")),
					c_operatory, ItemSymb(string(" ")), ItemSymb(string("e")), ItemSymb(string("n")), ItemSymb(string("d")), };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_sost_operator, buf_str));

		buf_str.clear();
		buf_symb = { c_operatory, c_tz, ItemSymb(string(" ")), c_operator };
		buf_str.push_back(buf_symb);
		buf_symb = { c_operator };
		buf_str.push_back(buf_symb);

		rules.push_back(ItemRule(c_operatory, buf_str));
	}
}

void TtoD_MethodAlg_u::SetParsingStr(ItemString inp_str)
{
	parsing_str = inp_str;
}

ResultOfStringReceiving TtoD_MethodAlg_u::SetParsingStr(string inp_str, bool contains_complex_nonterminals)
{
	if (contains_complex_nonterminals) {
		unsigned table[5][4] = { {0, 1, 2, 5},
								 {5, 0, 0, 0},
								 {3, 4, 5, 6},
								 {3, 4, 5, 0},
								 {5, 3, 3, 3} };
		unsigned error = 5, empty = 6, i = 0;
		string working_str = inp_str;
		unsigned str_size = working_str.size();
		char current_state = 0;
		char control_char;
		unsigned char_signal, next_state;
		string complex_terminal;

		while (i < str_size) {
			control_char = working_str[i];
			if (control_char == '$') { char_signal = 1; }
			else if (control_char == '<') { char_signal = 2; }
			else if (control_char == '>') { char_signal = 3; }
			else { char_signal = 0; }

			next_state = table[current_state][char_signal];

			if (next_state == error) {
				return ResultOfStringReceiving::FAILURE;
			}
			if (next_state == empty) {
				return ResultOfStringReceiving::EMPTY_BRACKETS;
			}
			if (next_state == 2) {
				complex_terminal.clear();
			}
			if (((current_state == 0) && (next_state == 0))
				|| ((current_state == 1) && (next_state == 0))) {
				parsing_str.AddSymb(working_str[i]);
			}
			if (next_state == 3) {
				complex_terminal.push_back(working_str[i]);
			}
			if ((current_state == 3) && (next_state == 0)) {
				parsing_str.AddSymb("<" + complex_terminal + ">");
			}

			current_state = next_state;
			i++;
		}
		if ((current_state == 0) && (parsing_str.Length() != 0)) {
			return ResultOfStringReceiving::SUCCESS;
		}
		else {
			return ResultOfStringReceiving::FAILURE;
		}
	}
	else {
		parsing_str = inp_str;
	}
}

void TtoD_MethodAlg_u::SetStartTarget()
{
	for (ItemRule rule : rules) {
		if (rule.GetLeft().IsAxiom()) {
			target_str.AddSymb(rule.GetLeft());
			return;
		}
	}
}

bool TtoD_MethodAlg_u::NonTerminalLeftInTarget()
{
	if (target_str[0].IsTerm()) {
		return false;
	}
	else {
		return true;
	}
}

RuleNum TtoD_MethodAlg_u::FindSuitableRule(const RuleNum rulenum)
{
	if (rulenum == RuleNum{0, -1}) {
		ItemSymb nonterminal = target_str[0];
		for (int i = 0; i < rules.size(); i++) {
			if (nonterminal == rules[i].GetLeft()) {
				return RuleNum{ i, 0 };
			}
			else {
				return RuleNum{ -1, -1 };
			}
		}
	}
	else {
		if (rulenum.sec_num < rules[rulenum.fir_num].RightSize() - 1) {
			return RuleNum{ rulenum.fir_num, rulenum.sec_num + 1 };
		}
		else {
			return RuleNum{ -1, -1 };
		}
	}

}

void TtoD_MethodAlg_u::TransformAccordingRule(const RuleNum& rule)
{
	ItemString option_str = rules[rule.fir_num][rule.sec_num];
	target_str.DeleteSymb(0, 1);
	for (int i = option_str.Length() - 1; i > -1; i--) {
		target_str.AddSymb(option_str[i], 0);
	}
}

bool TtoD_MethodAlg_u::RuleIsLastPossible(const RuleNum& rule)
{
	if (rule.sec_num == rules[rule.fir_num].RightSize() - 1) {
		return true;
	}
	else {
		return false;
	}
}

void TtoD_MethodAlg_u::MarkSourceStepAsWrongHypo()
{
	dynamic_cast<TtoD_Line_u*>(parsing_log[rollback_step])->MarkAsWrongHypo();
}

bool TtoD_MethodAlg_u::TerminalsMatched()
{
	if (ParsingStrIsEmpty()) {
		return false;
	} 
	else {
		if (parsing_str[0] == target_str[0]) {
			return true;
		}
		else {
			return false;
		}
	}
}

void TtoD_MethodAlg_u::RecognizeAndClearTerminals()
{
	recognized_str.AddSymb(parsing_str[0]);
	parsing_str.DeleteSymb(0, 1);
	target_str.DeleteSymb(0, 1);
}

int TtoD_MethodAlg_u::CheckForRollback()
{
	int i = parsing_log.Size() - 1;
	while (i > -1) {
		if (dynamic_cast<TtoD_Line_u*>(parsing_log[i])->GetStatus() == TypeOfTtoDLine::HYPOTHESIS) {
			return i;
		}
		i--;
	}
	return -1;
}

RuleNum TtoD_MethodAlg_u::RollbackAndGetCurRule()
{
	TtoD_Line_u source_step = *dynamic_cast<TtoD_Line_u*>(parsing_log[rollback_step]);

	recognized_str = RestoreStringFromLog(source_step.GetRecString());
	parsing_str = RestoreStringFromLog(source_step.GetCurString());
	target_str = RestoreStringFromLog(source_step.GetTargString());

	return (source_step.GetRuleNum());
}

void TtoD_MethodAlg_u::WriteToLog(const RuleNum cur_rule_num,
	const TypeOfTtoDLine inp_status, const int inp_source_s)
{
	TtoD_Line_u* buf_line;
	buf_line = new TtoD_Line_u();

	string rec_str = MakeStrForLog(recognized_str);
	string pars_str = MakeStrForLog(parsing_str);
	string targ_str = MakeStrForLog(target_str);

	buf_line->SetLine(rec_str, cur_rule_num, pars_str, targ_str, inp_status, inp_source_s);
	parsing_log.AddRecordLine(buf_line);
	///table_model->AppendLine(buf_line);
}

ItemString TtoD_MethodAlg_u::RestoreStringFromLog(const string& log_str)
{
	ItemString restored_str;
	char* arr_of_char = new char[log_str.size() + 1];
	copy(log_str.begin(), log_str.end(), arr_of_char);
	arr_of_char[log_str.size()] = '\0';
	char* context;
	bool added = false;

	char* item;
	item = strtok_s(arr_of_char, "\n", &context);
	while (item != NULL)
	{
		for (int i = 0; i < rules.size(); i++) {
			if (string(item) == string(rules[i].GetLeft())) {
				added = true;
				restored_str.AddSymb(rules[i].GetLeft());
			}
		}
		if (!added) {
			restored_str.AddSymb(ItemSymb(string(item)));
		}
		item = strtok_s(NULL, "\n", &context);
		added = false;
	}

	return restored_str;
}

string TtoD_MethodAlg_u::MakeStrForLog(const ItemString& orig_str)
{
	string str_with_separators;
	ItemString or_str = orig_str;

	for (int i = 0; i < or_str.Length(); i++) {
		str_with_separators += string(or_str[i]) + '\n';
	}
	return str_with_separators;
}

void TtoD_MethodAlg_u::MarkLastStepInLogAs(TypeOfTtoDLine mark_status)
{
	switch (mark_status)
	{
	case HYPOTHESIS:
		break;
	case WRONG_HYPO:
		break;
	case LAST_HYPO:
		break;
	case MISTAKE:
		break;
	case RECOGNIZED:
		break;
	case PARSED_END_TtoD:
		dynamic_cast<TtoD_Line_u*>(parsing_log[parsing_log.Size() - 1])->MarkAsParsedEnd();
		break;
	case NOT_PARSED_END_TtoD:
		dynamic_cast<TtoD_Line_u*>(parsing_log[parsing_log.Size() - 1])->MarkAsNotParsedEnd();
		break;
	}
}



bool TtoD_MethodAlg_u::DoParse()
{
	bool parsing_is_over = false;
	ClearRollbackFlag();
	SetStartTarget();
	RuleNum next_rule = { 0, -1 },
			rule;


	while (!parsing_is_over) {
		if (TargetStrIsEmpty()) {
			if ((ParsingStrIsEmpty()) && (TargetStrIsEmpty())) {
				WriteToLog(rule, TypeOfTtoDLine::PARSED_END_TtoD);
				parsing_is_over = true;
			}
			else {
				WriteToLog(rule, TypeOfTtoDLine::MISTAKE);
				rollback_step = CheckForRollback();
				if (RollbackIsPossible()) {
					SetRollbackFlag();
					next_rule = RollbackAndGetCurRule();
				}
				else {
					MarkLastStepInLogAs(TypeOfTtoDLine::NOT_PARSED_END_TtoD);
					parsing_is_over = true;
				}
			}
		}
		else {
			if (NonTerminalLeftInTarget()) {
				rule = FindSuitableRule(next_rule);
				if (rule.IsFound()) {
					if (ParsingIsOnRollbackBranch()) {
						WriteToLog(rule, HYPOTHESIS, rollback_step);
						if (RuleIsLastPossible(rule)) {
							WriteToLog(rule, TypeOfTtoDLine::LAST_HYPO, rollback_step);
						}
						else {
							WriteToLog(rule, HYPOTHESIS, rollback_step);
						}
						MarkSourceStepAsWrongHypo();
						ClearRollbackFlag();
					}
					else {
						WriteToLog(rule);
					}
					TransformAccordingRule(rule);
				}
			}
			else { // слева терминал
				if (TerminalsMatched()) {
					WriteToLog(rule, TypeOfTtoDLine::RECOGNIZED);
					RecognizeAndClearTerminals();
					ClearRollbackFlag();
				}
				else {
					WriteToLog(rule, TypeOfTtoDLine::MISTAKE);
					rollback_step = CheckForRollback();
					if (RollbackIsPossible()) {
						SetRollbackFlag();
						next_rule = RollbackAndGetCurRule();
					}
					else {
						MarkLastStepInLogAs(TypeOfTtoDLine::NOT_PARSED_END_TtoD);
						parsing_is_over = true;
					}
				}
			}
		}
		if (!ParsingIsOnRollbackBranch()) {
			next_rule = { 0, -1 };
		}
	}

	cout << endl << "***РАЗМЕР_ЛОГА=" << parsing_log.Size();

	parsing_log.PrintLogTtoD_u();

	return false;
}

/// /////////////////////////////////////////////////////

RecursiveState TtoD_MethodAlg_u::Recursive(const ItemString& pars_s, const ItemString& targ_s, const ItemString& rec_s)
{
	cout << endl << "Новый вызов**************************************************************************" << endl;
	ItemString parsing_str, target_str, recognized_str;
	parsing_str = pars_s;
	target_str = targ_s;
	recognized_str = rec_s;

	if ((parsing_str.Length() == 0) && (target_str.Length() == 0)) {
		return RecursiveState::END;
	}

	ItemSymb parsing_element = target_str[0];
	cout << endl << "Элемент " << string(parsing_element) << endl;
	cout << endl << "Разбираемая строка " << string(parsing_str) << endl;


	if (parsing_element.IsTerm()) {
		cout << "---Терминал" << endl;
		if (TerminalsMatched(parsing_str, target_str)) {

			cout << "----Совпадение" << endl;
			recognized_str.AddSymb(parsing_str[0]);
			parsing_str.DeleteSymb(0, 1);
			target_str.DeleteSymb(0, 1);

			//bool result = Recursive(parsing_str, target_str, recognized_str);
			return RecursiveState::FIT;
		}
		else {
			cout << "----Несовпадение" << endl;
			return RecursiveState::NOT_FIT;
		}
	}
	else {
		cout << "---Нетерминал" << endl;
		int rule_first_num = FindRuleFirNum(parsing_element);
		if (rule_first_num == -1) {
			return RecursiveState::NOT_FIT;
		}
		ItemString cur_target_str = target_str;
		ItemString cur_parsing_str = parsing_str;

		if (target_str.Length() != 0) {
			for (int i = 0; i < rules[rule_first_num].RightSize(); i++) {
				//TransformAccordingRule({ rule_first_num , i });
				cout << "----Раскрытие по правилу" << endl;
				cout << "----Было : " << string(target_str) << endl;
				target_str = TransformAccordingRule({ rule_first_num , i }, cur_target_str);
				cout << "----Стало : " << string(target_str) << endl;

				RecursiveState result = Recursive(cur_parsing_str, target_str, recognized_str);
				if (result == RecursiveState::FIT) {
					cout << "----------------------------------Сократилось : " << string(target_str) << endl;
					recognized_str.AddSymb(parsing_str[0]);
					parsing_str.DeleteSymb(0, 1);
					target_str.DeleteSymb(0, 1);
					RecursiveState res = Recursive(parsing_str, target_str, recognized_str);
					if (res == RecursiveState::END) {
						return RecursiveState::END;
					}
				}
				else if (result == RecursiveState::END) {
					return RecursiveState::END;
				}
				/*bool result = Recursive(parsing_str, target_str, recognized_str);
				while (result) {
					result = Recursive(parsing_str, target_str, recognized_str);
				}*/
			}
		}
		return RecursiveState::NOT_FIT;
	}
}

int TtoD_MethodAlg_u::FindRuleFirNum(ItemSymb parsing_element)
{
	for (unsigned i = 0; i < rules.size(); i++) {
		if (parsing_element == rules[i].GetLeft()) {
			return i;
		}
	}
	return -1;
}

const ItemSymb TtoD_MethodAlg_u::FindAxiom()
{
	for (ItemRule rule : rules) {
		if (rule.GetLeft().IsAxiom()) {
			return rule.GetLeft();
		}
	}
}

ItemString TtoD_MethodAlg_u::TransformAccordingRule(const RuleNum& rule, ItemString targ_s)
{

	ItemString option_str = rules[rule.fir_num][rule.sec_num];
	ItemString new_target_str = targ_s;

	new_target_str.DeleteSymb(0, 1);
	for (int i = option_str.Length() - 1; i > -1; i--) {
		new_target_str.AddSymb(option_str[i], 0);
	}
	return new_target_str;

}

bool TtoD_MethodAlg_u::TerminalsMatched(ItemString pars_s, ItemString targ_s)
{
	if ((pars_s.Length() != 0) && (targ_s.Length() != 0)) {
		return ((pars_s[0] == targ_s[0]) ? true : false);
	}
	else {
		return false;
	}

}///---------------------------------------------------------------------------------------

RecAnswer TtoD_MethodAlg_u::RecProcess(const ItemString& pars_s, const ItemString& targ_s, const ItemString& rec_s, const ItemString& full_targ)
{
	cout << endl << "Новый вызов**************************************" << endl;
	ItemString parsing_str, target_str, recognized_str, full_target_str;
	parsing_str = pars_s;
	target_str = targ_s;
	recognized_str = rec_s;
	full_target_str = full_targ;

	if ((parsing_str.Length() == 0) && (full_target_str.Length() == 0)) {
		WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::END_LINE);
		return { RecursiveState::END, parsing_str, recognized_str, full_target_str };
	}
	else if (full_target_str.Length() == 0) {
		WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::MISTAKE);
		return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
	}

	if (target_str.Length() == 1) {

		ItemSymb parsing_element = target_str[0];
		cout << endl << "Элемент " << string(parsing_element) << endl;
		cout << endl << "Разбираемая строка " << string(parsing_str) << endl;

		if (parsing_element.IsTerm()) { // терминал

			cout << "---Терминал" << endl;

			if (TerminalsMatched(parsing_str, target_str)) {

				cout << "----Совпадение" << endl;

				WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::RECOGNIZED);

				recognized_str.AddSymb(parsing_str[0]);
				parsing_str.DeleteSymb(0, 1);
				target_str.DeleteSymb(0, 1);
				full_target_str.DeleteSymb(0, 1);

				return { RecursiveState::FIT, parsing_str, recognized_str, full_target_str };
			}
			else {
				cout << "----Несовпадение" << endl;

				WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::MISTAKE);

				return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
			}

		}
		else { // нетерминал

			cout << "---Нетерминал" << endl;
			int rule_first_num = FindRuleFirNum(parsing_element);
			if (rule_first_num == -1) {
				return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
			}

			ItemString cur_target_str = target_str;
			ItemString cur_parsing_str = parsing_str;
			ItemString cur_fulltarg_str = full_target_str;

			for (int i = 0; i < rules[rule_first_num].RightSize(); i++) {
				
				cout << "----Раскрытие по правилу" << endl;
				cout << "----" << RuleNum{ rule_first_num, i }.GetPrintable() << endl;
				cout << "----Было : " << string(cur_target_str) << endl;
				cout << "----Было : " << string(cur_fulltarg_str) << endl;

				WriteToLogRec(recognized_str, cur_parsing_str, cur_fulltarg_str, { rule_first_num , i }, TypeOfTtoDLine::HYPOTHESIS);
				cout << endl << "В ЛОГ" << endl;

				target_str = TransformAccordingRule({ rule_first_num , i }, cur_target_str);
				full_target_str = TransformAccordingRule({ rule_first_num , i }, cur_fulltarg_str);

				cout << "----Стало : " << string(target_str) << endl;
				cout << "----Стало : " << string(full_target_str) << endl;

				RecAnswer result = RecProcess(cur_parsing_str, target_str, recognized_str, full_target_str);

				if (result.status == RecursiveState::NOT_FIT) {
					// 
					//return { RecursiveState::NOT_FIT, parsing_str, recognized_str };
				} 
				else if (result.status == RecursiveState::FIT) {

					cout << "--------Сократилось : " << string(target_str) << endl;
					recognized_str = result.recognized_str;
					parsing_str = result.parsing_str;
					target_str.DeleteSymb(0, 1);
					full_target_str = result.fulltarg_str;

					if ((parsing_str.Length() == 0) && (full_target_str.Length() == 0)) {
						WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::PARSED_END_TtoD);
						return { RecursiveState::END, parsing_str, recognized_str, full_target_str };
					}
					else if (full_target_str.Length() == 0) {
						WriteToLogRec(recognized_str, parsing_str, full_target_str, { -1, -1 }, TypeOfTtoDLine::MISTAKE);
						return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
					}

					return { RecursiveState::FIT, parsing_str, recognized_str, full_target_str };

					/*RecAnswer res = RecProcess(parsing_str, target_str, recognized_str);
					if (res.status == RecursiveState::END) {
						return{ RecursiveState::END, parsing_str, recognized_str };
					}*/
				}
				else if (result.status == RecursiveState::END) {
					return { RecursiveState::END, parsing_str, recognized_str, full_target_str };
				}
			}

		}
	}
	else if (target_str.Length() > 1){
		
		cout << endl << "Элемент " << string(target_str) << endl;
		cout << endl << "Разбираемая строка " << string(parsing_str) << endl;

		unsigned size = target_str.Length();
		unsigned i = 0;
		ItemString target;

		ItemString full_target = full_target_str;

		while (i < size) {

			target.SetString({ target_str[i] });
			RecAnswer result = RecProcess(parsing_str, target, recognized_str, full_target);

			if (result.status == RecursiveState::END) {
				return { RecursiveState::END, parsing_str, recognized_str, full_target_str };
			}
			else if (result.status == RecursiveState::FIT) {
				recognized_str = result.recognized_str;
				parsing_str = result.parsing_str;

				full_target = result.fulltarg_str;

				//full_target_str.DeleteSymb(0, 1);
				//target_str.DeleteSymb(0, 1);
				i++;
			}
			else if (result.status == RecursiveState::NOT_FIT) {
				return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
			}
		}
		return { RecursiveState::FIT, parsing_str, recognized_str, full_target };

	}
	else if (target_str.Length() == 0) {
		return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
	}
	///////////////////////////////


	return { RecursiveState::NOT_FIT, parsing_str, recognized_str, full_target_str };
}

void TtoD_MethodAlg_u::WriteToLogRec(const ItemString& rec_s, const ItemString& pars_s, const ItemString& targ_s, RuleNum rule, TypeOfTtoDLine type)
{
	TtoD_Line_u* buf_line;
	buf_line = new TtoD_Line_u();

	string spec_rec_str = MakeStrForLog(rec_s);
	string spec_pars_str = MakeStrForLog(pars_s);
	string spec_targ_str = MakeStrForLog(targ_s);

	buf_line->SetLine(spec_rec_str, rule, spec_pars_str, spec_targ_str, type);
	parsing_log.AddRecordLine(buf_line);
	///table_model->AppendLine(buf_line);
}

void TtoD_MethodAlg_u::DoParseNew()
{
	ItemString axiom;
	axiom.AddSymb(FindAxiom());
	//Recursive(parsing_str, axiom, ItemString(""));
	RecProcess(parsing_str, axiom, ItemString(""), axiom);

	cout << endl << "***РАЗМЕР_ЛОГА=" << parsing_log.Size();

	parsing_log.PrintLogTtoD_u();
}


