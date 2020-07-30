#pragma once
#include <qwidget.h>
#include <qlabel.h>
#include "Alg_Elements.h"
#include <QVBoxLayout>
#include <QTableView>

class RelTable :
	public QAbstractTableModel
{
	Q_OBJECT
public:
	RelTable() = delete;
	RelTable(vector<vector<TypeOfRelation>>* rel_tab) : relation_table(rel_tab) {}
	~RelTable() {}

private:

	///
	vector<vector<TypeOfRelation>>* relation_table;

	///

	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	QVariant row(int section, Qt::Orientation orientation, int role) const;

};


class RulesManager :
	public QWidget
{
	Q_OBJECT
public:
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
	void ShowRelationOnTable(const RuleNum r_num);
	void SetViewRelation(QTableView* view_rel) { view_relation = view_rel; }
	void SetRelModel() 
	{ 
		view_relation->setModel(relation_table);
		view_relation->resizeColumnsToContents();
		view_relation->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		view_relation->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		view_relation->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		QRect rect;
		rect.setWidth(100);
		rect.setHeight(100);
		view_relation->setGeometry(rect);
		view_relation->setSelectionMode(QAbstractItemView::NoSelection);
	}


	std::vector<QLabel*>& operator[] (int i) { return my_rules[i]; }
	void Neutralize();
	void ClearRelSelection();

	void SetRelationTable(RelTable* rel_table) { relation_table = rel_table; }
	void SetStringOfIds(QLabel* str) { string_of_ids = str; }
	void TextStringOfIds(string text)
	{
		QString qtext;
		string_of_ids->setWordWrap(true);
		qtext = QString::fromLocal8Bit(text.c_str());
		string_of_ids->clear();
		string_of_ids->setText(qtext);
	}

private:
	std::vector<std::vector<QLabel*>> my_rules;
	RuleNum colored_rule;
	RuleNum selected_relation;
	QTableView* view_relation;
	RelTable* relation_table;
	QLabel* string_of_ids;
};




