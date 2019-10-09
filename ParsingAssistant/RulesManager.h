#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include "Alg_Elements.h"

class RulesManager :
	public QWidget
{
	Q_OBJECT

public:
	void SetSize(unsigned size) { drawed_rules.resize(size); }
	void AddRule(unsigned i, QLabel* rule) { drawed_rules[i].push_back(rule); }
	void DrawRules(const std::vector<ItemRule>& rules);

	std::vector<QLabel*>& operator[] (int i) { return drawed_rules[i]; }

private:
	std::vector<std::vector<QLabel*>> drawed_rules;
};

