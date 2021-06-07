#include "RulesEditorManager.h"
#include <QSizePolicy>

QVBoxLayout* RulesEditorManager::DrawBasicForms()
{ 
	QVBoxLayout* returned_layout = new QVBoxLayout;
	rule_boxes.clear();
	returned_layout->addWidget(AddRule());
	return returned_layout;
}


QWidget* RulesEditorManager::AddRule()
{
	rule_boxes.resize(rule_boxes.size() + 1);
	unsigned nev_rule = rule_boxes.size() - 1;

	rule_boxes[nev_rule] = new RuleBox;
	rule_boxes[nev_rule]->ClearRuleBox();

	for (int i = 0; i < 4; i++) {
		if (i == 0) {
			QLabel* number = new QLabel;
			number->setText(QString::number(nev_rule + 1));
			rule_boxes[nev_rule]->AddWidget(number);
		}
		else if (i == 2) {
			QLabel* is = new QLabel("::=");
			rule_boxes[nev_rule]->AddWidget(is);
		}
		else {
			QLineEdit* edit_form = new QLineEdit;
			if (i == 1) {
				edit_form->setText(QString::fromLocal8Bit("<Аксиома>"));
			}
			else {
				edit_form->setText(QString::fromLocal8Bit("<Символ>"));
			}
			rule_boxes[nev_rule]->AddWidget(edit_form);
			rule_boxes[nev_rule]->AddLineEdit(edit_form);
		}
	}
	rule_boxes[nev_rule]->SetRuleBox();
	return rule_boxes[nev_rule];
}

void RulesEditorManager::DeleteRuleBox(RuleBox* deleted_rulebox)
{
	for (int i = 0; i < rule_boxes.size(); i++) {
		if (rule_boxes[i] == deleted_rulebox) {
			rule_boxes[i]->setVisible(false);
			rule_boxes.erase(rule_boxes.begin() + i);
		}
	}
}

void RulesEditorManager::CorrectNumOfRuleBoxes()
{
	int counted = 0;
	for (int i = 0; i < rule_boxes.size(); i++) {
		rule_boxes[i]->SetNumLabel(i+1);
		rule_boxes[i]->repaint();
	}
}

void RulesEditorManager::AddSymbToRuleBox(RuleBox* edited_rulebox)
{
	for (int i = 0; i < rule_boxes.size(); i++) {
		if (rule_boxes[i] == edited_rulebox) {
			QLineEdit* added_form = new QLineEdit;
			rule_boxes[i]->AddWidget(added_form);
			rule_boxes[i]->AddLineEdit(added_form);
			rule_boxes[i]->ResetRuleBox();
			rule_boxes[i]->repaint();
		}
	}
}

void RulesEditorManager::DeleteSymbFromRuleBox(RuleBox* edited_rulebox)
{
	for (int i = 0; i < rule_boxes.size(); i++) {
		if (rule_boxes[i] == edited_rulebox) {
			if (!(rule_boxes[i]->LastWidgetIsLineEdit())) {
				// удалить разделитель
				rule_boxes[i]->DeleteLastWidget();
				rule_boxes[i]->repaint();
			} 
			else if (rule_boxes[i]->GetLineEditsNumber() > 2) {
				rule_boxes[i]->DeleteLastLineEdit();
				rule_boxes[i]->repaint();
			}
		}
	}
}

void RulesEditorManager::AddSeparatorToRuleBox(RuleBox* edited_rulebox)
{
	for (int i = 0; i < rule_boxes.size(); i++) {
		if (rule_boxes[i] == edited_rulebox) {
			if (rule_boxes[i]->LastWidgetIsLineEdit()) {
				QLabel* added_separator = new QLabel("|");
				rule_boxes[i]->AddWidget(added_separator);
				rule_boxes[i]->ResetRuleBox();
				rule_boxes[i]->repaint();
			}
		}
	}
}

bool RulesEditorManager::FoundEmptyEditLines()
{
	for (RuleBox* rule_box : rule_boxes) {
		if (rule_box->HasEmptyLineEdit())
			return true;
	}
	return false;
}

void RulesEditorManager::ShowLoadedRules(std::vector<ItemRule>& rules, QLayout* main_layout)
{
	//очистка экрана
	for (RuleBox* rule_box : rule_boxes) {
		rule_box->setVisible(false);
	}
	rule_boxes.clear();

	for (int i = 0; i < rules.size(); i++) {
		
		rule_boxes.resize(rule_boxes.size() + 1);
		unsigned nev_rule = rule_boxes.size() - 1;

		rule_boxes[nev_rule] = new RuleBox;
		rule_boxes[nev_rule]->ClearRuleBox();

		QLabel* number = new QLabel;
		number->setText(QString::number(nev_rule + 1));
		rule_boxes[nev_rule]->AddWidget(number);

		QLineEdit* left_edit_form = new QLineEdit;
		left_edit_form->setText(rules[i].GetLeft().to_QString());
		rule_boxes[nev_rule]->AddWidget(left_edit_form);
		rule_boxes[nev_rule]->AddLineEdit(left_edit_form);

		QLabel* is = new QLabel("::=");
		rule_boxes[nev_rule]->AddWidget(is);
		
		ItemString right_option;
		for (int j = 0; j < rules[i].RightSize(); j++) {
			right_option = rules[i][j];
			for (int k = 0; k < right_option.Length(); k++) {
				QLineEdit* right_edit_form = new QLineEdit;
				right_edit_form->setText(rules[i][j][k].to_QString());
				rule_boxes[nev_rule]->AddWidget(right_edit_form);
				rule_boxes[nev_rule]->AddLineEdit(right_edit_form);
			}
			if (j != (rules[i].RightSize() - 1)) {
				QLabel* is = new QLabel("|");
				rule_boxes[nev_rule]->AddWidget(is);
			}
		}
		rule_boxes[nev_rule]->ResetRuleBox();
		rule_boxes[nev_rule]->repaint();
	}

	for (RuleBox* rule_box : rule_boxes) {
		rule_box->setVisible(true);
	}


	for (int i = 0; i < rule_boxes.size(); i++) {
		main_layout->addWidget(rule_boxes[i]);

	}
}

void RulesEditorManager::WriteInRules(std::vector<ItemRule>& rules)
{
	// точно известно, что все поля для ввода заполнены
	rules.clear();
	for (int i = 0; i < rule_boxes.size(); i++) {
		std::vector<QWidget*> widgets = rule_boxes[i]->GetLineOfWidgets();
		QLineEdit* line_edit = qobject_cast<QLineEdit*>(widgets[1]);
		rules.resize(rules.size() + 1);
		rules[i].SetLeft(ItemSymb(line_edit->text()));
		ItemString option;
		for (int j = 3; j < widgets.size(); j++) {
			QString class_name = widgets[j]->metaObject()->className();
			if (class_name == "QLineEdit") {
				line_edit = qobject_cast<QLineEdit*>(widgets[j]);
				option.AddSymb(line_edit->text());
			}
			else if (class_name == "QLabel") {
				rules[i].AddOption(option);
				option.DeleteSymb(0, option.Length());
			}
		}
		if (option.Length() != 0) {
			rules[i].AddOption(option);
			option.DeleteSymb(0, option.Length());
		}
	}
}

void RulesEditorManager::MarkNonterminalsInRules(std::vector<ItemRule>& rules)
{
	std::vector<ItemSymb> nonterminals;
	for (int i = 0; i < rules.size(); i++) {
		rules[i].SetLeftAsNonterminal();
		nonterminals.push_back(rules[i].GetLeft());
	}
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].RightSize(); j++) {
			for (int k = 0; k < rules[i][j].Length(); k++) {
				for (int t = 0; t < nonterminals.size(); t++) {
					if (rules[i][j][k] == nonterminals[t]) {
						rules[i][j][k].SetAsNonterminal();
					}
				}
			}
		}
	}
}

void RulesEditorManager::DefineDirectionOfRecursion(std::vector<ItemRule>& rules)
{
	rec_direction = NOT_DEFINED_REC;
	ItemSymb nonterminal;
	for (int i = 0; i < rules.size(); i++) {
		nonterminal = rules[i].GetLeft();
		for (int j = 0; j < rules[i].RightSize(); j++) {
			for (int k = 0; k < rules[i][j].Length(); k++) {
				if (rules[i][j][k] == nonterminal) {
					if ((rec_direction == NOT_DEFINED_REC) || (rec_direction == NESTED_REC)) {
						if (k == 0) {
							rec_direction = LTOR_REC;
						} 
						else if (k == (rules[i][j].Length() - 1)) {
							rec_direction = RTOL_REC;
						}
						else {
							rec_direction = NESTED_REC;
						}
					}
					else if (rec_direction == LTOR_REC) {
						if (k == (rules[i][j].Length() - 1)) {
							rec_direction = MIXED_ERROR;
						}
					}
					else if (rec_direction == RTOL_REC) {
						if (k == 0) {
							rec_direction = MIXED_ERROR;
						}
					}
				}
			}
		}
	}
}

void RulesEditorManager::MarkAxiomInLoadedRules(std::vector<ItemRule>& rules)
{
	ItemSymb axiom;

	for (ItemRule rule : rules) {
		if (rule.GetLeft().IsAxiom()) {
			axiom = rule.GetLeft();
		}
	}

	for (unsigned i = 0; i < rules.size(); i++) {
		for (unsigned j = 0; j < rules[i].RightSize(); j++) {
			for (unsigned k = 0; k < rules[i][j].Length(); k++) {
				if (rules[i][j][k] == axiom) {
					rules[i][j][k].SetAsAxiom();
				}
			}
		}
	}
}

QString RulesEditorManager::GetRulesText(std::vector<ItemRule>& rules)
{
	string st;
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

	for (int i = 0; i < rules.size(); i++) {
		st.append((string(rules[i].GetLeft())));
		//st.append("_" + string(rules[i].GetLeft().IsAxiom() ? "ax" : "not")); /// отладочная печать, не удалять
		st.append(" ::= ");
		for (int j = 0; j < rules[i].RightSize(); j++) {
			ItemString str = rules[i].GetRightOption(j);
			int size = str.Length();
			for (int k = 0; k < size; k++) {
				st.append((string(str[k])));
				//st.append("_" + string(str[k].IsAxiom() ? "ax" : "not")); /// отладочная печать, не удалять
				//st.append("_" + string(str[k].IsTerm() ? "t" : "n")); /// отладочная печать, не удалять
			}
			if (j != rules[i].RightSize() - 1) {
				st.append(" | ");
			}
		}
		st.append("\n");
	}
	return codec->toUnicode(st.c_str());
}

QString RulesEditorManager::GetRecTypeInString()
{
	QString rec_type = "";
	switch (rec_direction)
	{
	case NOT_DEFINED_REC:
		rec_type = QString::fromLocal8Bit("Не установлено");
		break;
	case LTOR_REC:
		rec_type = QString::fromLocal8Bit("Левосторонняя");
		break;
	case RTOL_REC:
		rec_type = QString::fromLocal8Bit("Правосторонняя");
		break;
	case NESTED_REC:
		rec_type = QString::fromLocal8Bit("Вложенная");
		break;
	case MIXED_ERROR:
		rec_type = QString::fromLocal8Bit("Ошибка");
		break;
	}
	return rec_type;
}

std::vector<QString> RulesEditorManager::GetNonterminals(std::vector<ItemRule>& rules)
{
	std::vector<QString> nonterminals;
	for (int i = 0; i < rules.size(); i++) {
		nonterminals.push_back(rules[i].GetLeft().to_QString());
	}
	return nonterminals;
}

void RulesEditorManager::SetAxiomInRules(std::vector<ItemRule>& rules, QString axiom)
{
	ItemSymb axiom_symb(axiom);
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].RightSize(); j++) {
			if (rules[i].GetLeft() == axiom_symb) {
				rules[i].SetLeftAsAxiom();
			}
			for (int k = 0; k < rules[i][j].Length(); k++) {
				if (rules[i][j][k] == axiom_symb) {
					rules[i][j][k].SetAsAxiom();
				}
			}
		}
	}
}

bool RulesEditorManager::NoRules()
{
	if (rule_boxes.size() == 0)
		return true;
	else
		return false;
}

bool RulesEditorManager::RepetitionsInTheLeftPartsOfRules(std::vector<ItemRule>& rules)
{
	ItemSymb left;
	for (int i = 0; i < rules.size(); i++) {
		left = rules[i].GetLeft();
		for (int j = i + 1; j < rules.size(); j++) {
			if (left == rules[j].GetLeft()) {
				return true;
			}
		}
	}
	return false;
}

bool RulesEditorManager::RepetitionsInTheRightPartsOfRules(std::vector<ItemRule>& rules)
{
	ItemString right_option;
	for (int i = 0; i < rules.size(); i++) {
		for (int j = 0; j < rules[i].RightSize(); j++) {
			right_option = rules[i][j];

			for (int k = 0; k < rules.size(); k++) {
				for (int t = 0; t < rules[k].RightSize(); t++) {
					if ((rules[k][t] == right_option) && ((i != k) || (j != t))) {
						return true;
					}
				}
			}

		}
	}
	return false;
}
