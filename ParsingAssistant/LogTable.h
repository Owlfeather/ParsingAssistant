#pragma once
#include <QAbstractTableModel>
#include <iostream>

using namespace std;

#include "Alg_Elements.h"

class LogTable :
	public QAbstractTableModel
{
	Q_OBJECT
public:
	void SetRowCount(unsigned inp_row_count);
	void SetColomnCount(unsigned inp_col_count);


private:
	unsigned row_count;
	unsigned colomn_count;

	///
	vector<RecordLine*> records;
	void AddRecordLine(RecordLine* inp_rec) { records.push_back(inp_rec); }
	int Size() { return records.size(); }
	///

	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
};

