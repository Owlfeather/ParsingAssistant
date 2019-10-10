#pragma once
#include <QAbstractListModel>
#include <iostream>

using namespace std;

#include "Alg_Elements.h"

class Comment
{
public:
	Comment() {}
	Comment(string inp_text, TypeOfComment inp_type, RuleNum inp_r_num)
		: text(inp_text), type(inp_type), r_num(inp_r_num) {}

	const TypeOfComment GetType() { return type; }
	const string& GetText() { return text; }
	const RuleNum GetRuleNum() { return r_num; }

private:
	string text;
	TypeOfComment type;
	RuleNum r_num;
};

class LogComments :
	public QAbstractListModel
{
	Q_OBJECT
public:
	LogComments() {}
	Comment* GetRow(unsigned i) { return records[i]; }
	void AddRecordLine(const string& inp_s, TypeOfComment inp_t, RuleNum inp_r = {-7, -7})
	{ 
		int row = records.size();
		Comment* new_comment = new Comment(inp_s, inp_t, inp_r);

		beginInsertRows(QModelIndex(), row, row);
		records.push_back(new_comment);
		beginInsertRows(QModelIndex(), row, row);

	}

	//const unsigned & CurRow() { return cur_row; }
	const int Size() { return records.size(); }
	//Comment* operator[] (int i) { return records[i]; }
	//void Inc() { cur_row++; }


private:

	vector<Comment*> records;
	//unsigned cur_row;

	int rowCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
};


