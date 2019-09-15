#pragma once
#include <QAbstractTableModel>

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

	int rowCount(const QModelIndex& parent) const;
	int columnCount(const QModelIndex& parent) const;
	QVariant data(const QModelIndex& index, int role) const;
};

