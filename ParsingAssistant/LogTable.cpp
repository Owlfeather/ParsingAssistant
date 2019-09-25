#include "LogTable.h"

/*
void LogTable::SetRowCount(unsigned inp_row_count)
{
	row_count = inp_row_count;
}

void LogTable::SetColomnCount(unsigned inp_col_count)
{
	colomn_count = inp_col_count;
}
*/

int LogTable::rowCount(const QModelIndex& parent) const
{
	//return row_count;
	return records.size();
}

int LogTable::columnCount(const QModelIndex& parent) const
{
	//return colomn_count;
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		return 2;
	case TypeOfAlg::TTOD:
		return 4;
	}
}

QVariant LogTable::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		//QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
		// строкой выше мы формируем ответ. QString::number преобразует число в текст

		QString unswer = QString::fromLocal8Bit(records[index.row()]->GetLine()[index.column()].c_str());
		return QVariant(unswer);
	}
	return QVariant();
}

QVariant LogTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Vertical) {
		return section;
	}
	switch (alg_type)
	{case TypeOfAlg::LTOR:
		switch (section) {
		case 0:
			return QString::fromLocal8Bit("Строка");
		case 1:
			return QString::fromLocal8Bit("Правило");
		}
		break;
	case TypeOfAlg::TTOD:
		switch (section) {
		case 0:
			return QString::fromLocal8Bit("Распознано");
		case 1:
			return QString::fromLocal8Bit("Строка");
		case 2:
			return QString::fromLocal8Bit("Цель");
		case 3:
			return QString::fromLocal8Bit("Правило");
		}
		break;
	}

	return QVariant();
}

void  LogTable::AppendLine(RecordLine* line)
{
	int row = records.size();

	beginInsertRows(QModelIndex(), row, row);
	records.push_back(line);
	beginInsertRows(QModelIndex(), row, row);
}