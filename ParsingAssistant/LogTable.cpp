#include "LogTable.h"

void LogTable::SetRowCount(unsigned inp_row_count)
{
	row_count = inp_row_count;
}

void LogTable::SetColomnCount(unsigned inp_col_count)
{
	colomn_count = inp_col_count;
}

int LogTable::rowCount(const QModelIndex& parent) const
{
	return row_count;
	//return 0;
}

int LogTable::columnCount(const QModelIndex& parent) const
{
	return colomn_count;
	//return 3;
}

QVariant LogTable::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
		// строкой выше мы формируем ответ. QString::number преобразует число в текст
		return QVariant(unswer);
	}
	return QVariant();
}
