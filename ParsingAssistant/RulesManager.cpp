#include "RulesManager.h"
#include <QVBoxLayout>

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