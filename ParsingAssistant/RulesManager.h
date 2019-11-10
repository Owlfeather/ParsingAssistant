﻿#pragma once
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

	//void AddRecordLine(RecordLine* inp_rec) { records.push_back(inp_rec); }
	//int Size() { return records.size(); }
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
	void SetViewRelation(QTableView* view_rel) { view_relation = view_rel; }
	//void DeleteRules() { my_rules.clear(); }
	void SetRelModel() 
	{ 
		view_relation->setModel(relation_table);
		view_relation->resizeColumnsToContents();
	}

	std::vector<QLabel*>& operator[] (int i) { return my_rules[i]; }
	void Neutralize();

	void SetRelationTable(RelTable* rel_table) { relation_table = rel_table; }

private:
	std::vector<std::vector<QLabel*>> my_rules;
	RuleNum colored_rule;
	QTableView* view_relation;
	RelTable* relation_table;

	//void Neutralize();

};




