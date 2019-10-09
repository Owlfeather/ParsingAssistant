#include "LogComments.h"

int LogComments::rowCount(const QModelIndex& parent) const
{
	return records.size();
}

QVariant LogComments::data(const QModelIndex& index, int role) const
{

	if (role == Qt::DisplayRole) {
		
		QString unswer = QString::fromLocal8Bit(records[index.row()]->c_str());
		return QVariant(unswer);
	}
	return QVariant();
}

