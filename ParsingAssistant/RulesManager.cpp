#include "RulesManager.h"
#include <QVBoxLayout>
#include <QModelIndex>
#include <QAbstractItemModel>

QLayout* RulesManager::DrawRules(const std::vector<ItemRule>& rules)
{
	QVBoxLayout* returned_l = new QVBoxLayout;
	QVBoxLayout* vbox = new QVBoxLayout;
	//QWidget* gbox = new QWidget;
	//QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

	std::vector<QLabel*> buf;
	std::vector<QHBoxLayout*> array_h_layouts;
	std::vector<QLabel*> separators;
	separators.resize(1);
	ItemRule cur_rule;
	QString text;
	unsigned rules_size = rules.size(); // размер строк правил

	array_h_layouts.resize(rules_size); //число правил
	my_rules.resize(rules_size); ///число правил

	cur_rule = rules[0];
	int size = cur_rule.RightSize() + 1; // число вариантов раскрытия первого правила

	//for (int i = 0; i < size; i++) {
	for (int i = 0; i < rules_size; i++) {

		cur_rule = rules[i];
		size = cur_rule.RightSize() + 1;

		array_h_layouts[i] = new QHBoxLayout;
		buf.clear();
		buf.resize(size);

		//drawed_rules[i].resize(size);

		for (int j = 0; j < size; j++) {
			buf[j] = new QLabel;

			if (j == 0) {
				text = QString::fromLocal8Bit((string(cur_rule.GetLeft())).c_str());
				buf[j]->setText(text);
				my_rules[i].push_back(buf[j]);
				array_h_layouts[i]->addWidget(buf[j]);

				text = "::=";
				separators.resize(separators.size() + 1);
				unsigned last_sep_num = separators.size() - 1;
				separators[last_sep_num] = new QLabel;
				separators[last_sep_num]->setText(text);
				array_h_layouts[i]->addWidget(separators[separators.size() - 1]);
			}
			else {
				text = QString::fromLocal8Bit((string(cur_rule.GetRight(j - 1))).c_str());
				buf[j]->setText(text);
				my_rules[i].push_back(buf[j]);
				array_h_layouts[i]->addWidget(buf[j]);

				if (j != size - 1) {
					text = "|";
					separators.resize(separators.size() + 1);
					unsigned last_sep_num = separators.size() - 1;
					separators[last_sep_num] = new QLabel;
					separators[last_sep_num]->setText(text);
					array_h_layouts[i]->addWidget(separators[separators.size() - 1]);
				}
			}
		}

		array_h_layouts[i]->insertStretch(array_h_layouts[i]->count(), 1);
		vbox->addLayout(array_h_layouts[i]);
		returned_l->addLayout(vbox);
		++size;
	}
	colored_rule = { 0, 0 };
	return returned_l;
}

void RulesManager::ColorRule(const RuleNum r_num, Color inp_color)
{
	//Neutralize();
	colored_rule = r_num;
	colored_rule.sec_num++;

	int i = r_num.fir_num;
	int j = r_num.sec_num + 1;
	QColor color;
	QPalette palette;
	switch (inp_color)
	{
	case Color::RED:
	{
		color = Qt::red;
		palette = my_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		my_rules[i][j]->setPalette(palette);
		my_rules[i][0]->setPalette(palette);

	}
	break;

	case Color::BLACK:
	{
		color = Qt::black;
		palette = my_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		my_rules[i][j]->setPalette(palette);
		my_rules[i][0]->setPalette(palette);
	}
	break;
	case Color::GREEN:
	{
		color = QColor(90, 200, 71);
		palette = my_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		my_rules[i][j]->setPalette(palette);
		my_rules[i][0]->setPalette(palette);
	}
	}
}

void RulesManager::Neutralize()
{
	QColor color;
	QPalette palette;
	color = Qt::black;
	palette = my_rules[colored_rule.fir_num][colored_rule.sec_num]->palette();
	palette.setColor(QPalette::WindowText, color);
	my_rules[colored_rule.fir_num][colored_rule.sec_num]->setPalette(palette);
	my_rules[colored_rule.fir_num][0]->setPalette(palette);

}

int RelTable::rowCount(const QModelIndex& parent) const
{
	//return relation_table->size();
	return 5;
}

int RelTable::columnCount(const QModelIndex& parent) const
{
	return 5;
}

QVariant RelTable::data(const QModelIndex& index, int role) const
{
	if (role == Qt::TextAlignmentRole)
		return Qt::AlignCenter;

	if (role == Qt::DisplayRole) {
		QString unswer;
///*
		switch (relation_table->at(index.row())[index.column()])
		{case TypeOfRelation::CARRY:
			unswer = "<";
			break;
		case TypeOfRelation::CONV:
			unswer = ">";
			break;
		case TypeOfRelation::CONV_BR:
			unswer = "=";
			break;
		case TypeOfRelation::ERROR:
			unswer = "?";
			break;
		case TypeOfRelation::EXIT:
			unswer = "B";
			break;
		}
//*/
		return QVariant(unswer);
		//return QVariant(QString("*"));
	}
	//return QVariant(unswer);
	return QVariant();
}

QVariant RelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
	/*
	if (role != Qt::DisplayRole) {
		return QVariant();
	}

	if (orientation == Qt::Vertical) {
		return section;
	}
	switch (section) {
	case 0:
		return QString::fromLocal8Bit("+");
	case 1:
		return QString::fromLocal8Bit("*");
	case 2:
		return QString::fromLocal8Bit("(");
	case 3:
		return QString::fromLocal8Bit(")"); 
	case 4:
		return QString::fromLocal8Bit("end");
		break;
	}
	//return QVariant();
	///*
	if (orientation == Qt::Horizontal) {
		return section;
	}
	switch (section) {
	case 0:
		return QString::fromLocal8Bit("beg");
	case 1:
		return QString::fromLocal8Bit("+");
	case 2:
		return QString::fromLocal8Bit("*");
	case 3:
		return QString::fromLocal8Bit("(");
	case 4:
		return QString::fromLocal8Bit(")");
	}
	*/

	{
		if (orientation == Qt::Horizontal)
		{
			if (role == Qt::DisplayRole)
				switch (section)
				{
				case 0: return "+";									 break;
				case 1: return "*";									 break;
				case 2: return "(";									 break;
				case 3: return ")";									 break;
				case 4: return  QString::fromWCharArray(L"\u2BC7");  break;
				}
		}
		else if (orientation == Qt::Vertical)
		{
			if (role == Qt::DisplayRole)
				switch (section)
				{
				//case 0: return QString::fromLocal8Bit(2BC8);	break;
				//case 0: return	QString::fromUtf8("\u2BC8");	break;
				case 0: return	QString::fromWCharArray(L"\u2BC8");	break;
				case 1: return "+";									break;
				case 2: return "*";									break;
				case 3: return "(";									break;
				case 4: return ")";									break;
				}
		}

		return QVariant();
	}
}

void RulesManager::ShowRelationOnTable(const RuleNum r_num)
{
	//view_relation->setFocus
	selected_relation = r_num;
	QModelIndex index = view_relation->model()->index(r_num.fir_num, r_num.sec_num);
	view_relation->selectionModel()->select(index, QItemSelectionModel::Select);

}

void RulesManager::ClearRelSelection()
{
	QModelIndex index = view_relation->model()->index(selected_relation.fir_num, selected_relation.sec_num);
	//index.s = selected_relation.fir_num;
	//index.column = selected_relation.sec_num;
	view_relation->selectionModel()->select(index, QItemSelectionModel::Deselect);
}