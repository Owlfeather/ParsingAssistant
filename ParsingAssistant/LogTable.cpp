#include "LogTable.h"
#include <QColor>
#include <QBrush>

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
		// ������� ���� �� ��������� �����. QString::number ����������� ����� � �����

		QString unswer = QString::fromLocal8Bit(records[index.row()]->GetLine()[index.column()].c_str());
		return QVariant(unswer);
	}
	///
	if (role == Qt::BackgroundColorRole) {
		if (records[index.row()]->GetRuleNum().fir_num == -2) {		
			return QVariant(QBrush(QColor(255, 217, 217)));
		}
		else if (records[index.row()]->GetRuleNum().fir_num == -3) {
			return QVariant(QBrush(QColor(217, 255, 196)));
		}
		else if (records[index.row()]->GetRuleNum().fir_num == -4) {
			return QVariant(QBrush(QColor(255, 215, 174)));
		}
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
			return QString::fromLocal8Bit("������");
		case 1:
			return QString::fromLocal8Bit("�������");
		}
		break;
	case TypeOfAlg::TTOD:
		switch (section) {
		case 0:
			return QString::fromLocal8Bit("����������");
		case 1:
			return QString::fromLocal8Bit("������");
		case 2:
			return QString::fromLocal8Bit("����");
		case 3:
			return QString::fromLocal8Bit("�������");
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