#include "LogComments.h"
#include <QColor>
#include <QBrush>


int LogComments::rowCount(const QModelIndex& parent) const
{
	return records.size();
}

QVariant LogComments::data(const QModelIndex& index, int role) const
{
	
	if (role == Qt::DisplayRole) {
		
		QString unswer = QString::fromLocal8Bit(records[index.row()]->GetText().c_str());
		/*
		switch (records[index.row()]->GetType())
		{
		case TypeOfComment::CORRECT_RULE:
			unswer += " CORRECT_RULE";
			break;
		case TypeOfComment::DEAD_END:
			unswer += " DEAD_END";
			break;
		case TypeOfComment::INFO:
			unswer += " INFO";
			break;
		case TypeOfComment::PARSE_CORRECT:
			unswer += " PARSE_CORRECT";
			break;
		case TypeOfComment::PARSE_INCORRECT:
			unswer += " PARSE_INCORRECT";
			break;
		case TypeOfComment::WRONG_RULE:
			unswer += " WRONG_RULE";
			break;
		case TypeOfComment::HYPOTHESIS:
			unswer += " HYPOTHESIS";
			break;
		case TypeOfComment::ACTION:
			unswer += " ACTION";
			break;
		}

		unswer += QString::fromLocal8Bit(" Правило: ") + QString::fromLocal8Bit(to_string(records[index.row()]->GetRuleNum().fir_num).c_str())
			+ ", " + QString::fromLocal8Bit(to_string(records[index.row()]->GetRuleNum().sec_num).c_str());
	//*/
		return QVariant(unswer);
	}

	if (role == Qt::BackgroundColorRole) {
		QColor color;

		switch (records[index.row()]->GetType())
		{
		case TypeOfComment::CORRECT_RULE:
			color = QColor(217, 255, 196);
			break;
		case TypeOfComment::DEAD_END:
			color = QColor(255, 155, 155);
			break;
		case TypeOfComment::INFO:
			color = QColor(255, 243, 189);
			break;
		case TypeOfComment::PARSE_CORRECT:
			color = QColor(217, 255, 196);
			break;
		case TypeOfComment::PARSE_INCORRECT:
			color = QColor(255, 125, 125);
			break;
		case TypeOfComment::WRONG_RULE:
			color = QColor(255, 255, 255);
			break;
		case TypeOfComment::HYPOTHESIS:
			color = QColor(255, 255, 255);
			break;
		case TypeOfComment::ACTION:
			color = QColor(255, 255, 255);
			break;
		}

		return QVariant(QBrush(color));
	}


	return QVariant();
}

