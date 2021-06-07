#include "AnsTable.h"

int AnsTable::rowCount(const QModelIndex& parent) const
{
	return records.size();
}

int AnsTable::columnCount(const QModelIndex& parent) const
{
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		return 2;
	case TypeOfAlg::TTOD:
		return 4;
	case TypeOfAlg::LLK_TTOD:
		return 3;
	case TypeOfAlg::LRK_STACK:
		return 6;
	default:
		return 0;
	}
}

QVariant AnsTable::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		//QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
		// ������� ���� �� ��������� �����. QString::number ����������� ����� � �����

		QString unswer = (records[index.row()][index.column()]);
		return QVariant(unswer);
	}
	return QVariant();
}

QVariant AnsTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Vertical) {
		return section + 6;
	}
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
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
	case TypeOfAlg::LLK_TTOD:
		switch (section) {
		case 0:
			return QString::fromLocal8Bit("������");
		case 1:
			return QString::fromLocal8Bit("����");
		case 2:
			return QString::fromLocal8Bit("�������");
		}
		break;
	case TypeOfAlg::LRK_STACK:
		switch (section) {
		case 0:
			return QString::fromLocal8Bit("����");
		case 1:
			return QString::fromLocal8Bit("�����. ������");
		case 2:
			return QString::fromLocal8Bit("���������");
		case 3:
			return QString::fromLocal8Bit("��������");
		case 4:
			return QString::fromLocal8Bit("������");
		case 5:
			return QString::fromLocal8Bit("���������");
		}
		break;
	}

	return QVariant();
}

void AnsTable::Create()
{
	records.clear();
	for (int i = 0; i < 10; i++) {
		vector<QString> record = {"",""};
		records.push_back(record);
	}
}

bool AnsTable::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role == Qt::EditRole) {
		if (!checkIndex(index))
			return false;
		//save value from editor to member records
		records[index.row()][index.column()] = value.toString();
		//for presentation purposes only: build and emit a joined string
		QString result;
		for (int row = 0; row < 10; row++) {
			for (int col = 0; col < columnCount(QModelIndex()); col++)
				result += records[row][col] + ' ';
		}
		emit editCompleted(result);
		return true;
	}
	return false;
}

Qt::ItemFlags AnsTable::flags(const QModelIndex& index) const
{
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
