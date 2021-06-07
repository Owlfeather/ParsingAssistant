#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include <QLineEdit.h>
#include "Alg_Elements_u.h"
#include "RuleBox.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>


class RulesEditorManager :
	public QWidget
{
	Q_OBJECT
public:

	QVBoxLayout* DrawBasicForms();
	QWidget* AddRule();
	void DeleteRuleBox(RuleBox* deleted_rulebox);
	void CorrectNumOfRuleBoxes();
	void AddSymbToRuleBox(RuleBox* edited_rulebox);
	void DeleteSymbFromRuleBox(RuleBox* edited_rulebox);
	void AddSeparatorToRuleBox(RuleBox* edited_rulebox);
	bool FoundEmptyEditLines();
	void ShowLoadedRules(std::vector<ItemRule>& rules, QLayout* main_layout);
	void WriteInRules(std::vector<ItemRule>& rules);
	void MarkNonterminalsInRules(std::vector<ItemRule>& rules);
	void DefineDirectionOfRecursion(std::vector<ItemRule>& rules);
	void MarkAxiomInLoadedRules(std::vector<ItemRule>& rules);
	QString GetRulesText(std::vector<ItemRule>& rules);
	QString GetRecTypeInString();
	std::vector<QString> GetNonterminals(std::vector<ItemRule>& rules);
	void SetAxiomInRules(std::vector<ItemRule>& rules, QString axiom);
	bool NoRules();
	const DirectionOfRecursion GetRecDirection() { return rec_direction; }
	bool RepetitionsInTheLeftPartsOfRules(std::vector<ItemRule>& rules);
	bool RepetitionsInTheRightPartsOfRules(std::vector<ItemRule>& rules);


private:
	std::vector<RuleBox*> rule_boxes;
	DirectionOfRecursion rec_direction;

};





