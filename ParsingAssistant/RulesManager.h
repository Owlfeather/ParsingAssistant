#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include "Alg_Elements.h"
#include <QVBoxLayout>

class RulesManager :
	public QWidget
{
	Q_OBJECT
//public:
	//std::vector<std::vector<QLabel*>> my_rules;
public:
	//std::vector<std::vector<QLabel *>> my_rules;
	~RulesManager() 
	{ 
		for (int i = 0; i < my_rules.size(); i++) {
			my_rules[i].clear();
		}
	}
	void SetSize(unsigned size) { my_rules.resize(size); }
	void AddRule(unsigned i, QLabel* rule) { my_rules[i].push_back(rule); }
	QLayout* DrawRules(const std::vector<ItemRule>& rules);
	void ColorRule(const RuleNum r_num, Color inp_color);
	//void DeleteRules() { my_rules.clear(); }

	std::vector<QLabel*>& operator[] (int i) { return my_rules[i]; }
	void Neutralize();

private:
	std::vector<std::vector<QLabel*>> my_rules;
	RuleNum colored_rule;

	//void Neutralize();

};

