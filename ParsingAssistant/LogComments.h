#pragma once
#include <QAbstractListModel>
#include <iostream>

using namespace std;

#include "Alg_Elements.h"

class LogComments :
	public QAbstractListModel
{
	Q_OBJECT
public:
	
	//void AppendLine(string* line);
	string* GetRow(unsigned i) { return records[i]; }
	void AddRecordLine(const string & inp_rec) 
	{ 
		int row = records.size();
		string* new_str = new string(inp_rec);

		beginInsertRows(QModelIndex(), row, row);
		records.push_back(new_str);
		beginInsertRows(QModelIndex(), row, row);

	}
	int Size() { return records.size(); }
private:

	vector<string*> records;

	int rowCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
};

