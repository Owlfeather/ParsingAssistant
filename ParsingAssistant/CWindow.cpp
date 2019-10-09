#include "CWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>


#define RUS( str ) codec->toUnicode(str)

CWindow::CWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	connect(ui.btnStep, SIGNAL(clicked()), this, SLOT(onStepClicked()));
	connect(ui.btnShowAll, SIGNAL(clicked()), this, SLOT(onShowAllClicked()));

	scrollbar_table = new QScrollBar;
	ui.tableView->setVerticalScrollBar(scrollbar_table);
	scrollbar_comments = new QScrollBar;
	ui.listView->setVerticalScrollBar(scrollbar_comments);

	rules_manager = new RulesManager;
	//scrollbar->setRange(0, 100);
	//QObject::connect(ui.tableView, SIGNAL(valueChanged(int)), scrollbar, SLOT(setValue(int)));

	//QObject::connect(spinBox, SIGNAL(valueChanged(int)), scrollbar, SLOT(setValue(int)));
	//scrollbar.setvertical
	//ui.tableView->setAutoScroll(true);
	//ui.tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

CWindow::~CWindow()
{
}

void CWindow::RenderCWin(ModeOfCWin type)
{

	switch (type)
	{
	case ModeOfCWin::CWBEGIN: // окно только открыто, показываем меню
		{

			ui.grboxParse->setVisible(false);
			ui.grboxTest->setVisible(false);
			ui.btnRepeat->setDisabled(true);
			ui.btnStep->setVisible(false);

			ui.lineInpStr->setFocus();
			ui.lineInpStr->grabKeyboard();
		
			QTextCodec * codec = QTextCodec::codecForName("Windows-1251");
			switch (alg_type)
			{
			case TypeOfAlg::LTOR:
			{ ui.lblName->setText(RUS("Левосторонний восходящий разбор")); break; }
			case TypeOfAlg::TTOD:
			{ ui.lblName->setText(RUS("Левосторонний нисходящий разбор")); break; }
			default:
				break;
			}
		break;
		}
	case ModeOfCWin::CWPARSE:
		{
			ui.grboxParse->setVisible(true);
			ui.btnParse->setDisabled(true);
			cur_rule = {-10, 0};
			prev_rule = { -10, 0 };
			cur_table_row = 0;
			cur_comment_row = 0;
			break;
		}
	case ModeOfCWin::CWPARSESTARTED:
		{
			ui.btnStep->setVisible(true);
			ui.btnStart->setDisabled(true);
			ui.lineInpStr->setDisabled(true);
			ui.tableView->setModel(algorithm->GetTable());
			ui.tableView->resizeColumnsToContents();
			ui.listView->setModel(algorithm->GetComments());
			HideRows();


			//rollback = false;
			break;
		}
	case ModeOfCWin::CWPARSEENDED:
		{
			ui.btnRepeat->setEnabled(true);
			ui.btnStep->setEnabled(false);
			break;
		}
	}

}

void CWindow::SetAlgorithm(TypeOfAlg inp_alg_type)
{
	alg_type = inp_alg_type;

	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		{
			LtoR_MethodAlg * cur_alg = new LtoR_MethodAlg;
			algorithm = cur_alg;
			algorithm->SetLogTableType(TypeOfAlg::LTOR);
			break;
		}
	case TypeOfAlg::TTOD:
		{
			TtoD_MethodAlg* cur_alg = new TtoD_MethodAlg;
			algorithm = cur_alg;
			algorithm->SetLogTableType(TypeOfAlg::TTOD);
			break;
		}
	}
	algorithm->SetRulesOfAlg();
	DrawRules();
}

/*
void CWindow::DrawRules()
{
	QVBoxLayout* vbox = new QVBoxLayout;
	//QWidget* gbox = new QWidget;
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");

	std::vector<QLabel *> buf;
	std::vector<QHBoxLayout *> array_h_layouts;
	std::vector<QLabel*> separators;
	separators.resize(1);
	ItemRule cur_rule;
	QString text;
	unsigned rules_size = algorithm->RulesSize(); // размер строк правил

	array_h_layouts.resize(rules_size); //число правил
	drawed_rules.resize(rules_size); ///число правил

	cur_rule = algorithm->GetRule(0);
	int size = cur_rule.RightSize() + 1; // число вариантов раскрытия первого правила

	for (int i = 0; i < size; i++) {

		cur_rule = algorithm->GetRule(i);
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
				drawed_rules[i].push_back(buf[j]);
				array_h_layouts[i]->addWidget(buf[j]);

				text = "::=";
				separators.resize(separators.size() + 1);
				unsigned last_sep_num = separators.size() - 1;
				separators[last_sep_num] = new QLabel;
				separators[last_sep_num]->setText(text);
				array_h_layouts[i]->addWidget(separators[separators.size() - 1]);
			}
			else {
				text = QString::fromLocal8Bit((string(cur_rule.GetRight(j-1))).c_str());
				buf[j]->setText(text);
				drawed_rules[i].push_back(buf[j]);
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
		ui.ruleBox->setLayout(vbox);
		++size;
	}

}
*/

void CWindow::DrawRules()
{
	QVBoxLayout* rule_lay = new QVBoxLayout;

	rules_manager->setLayout(rules_manager->DrawRules((algorithm->GetRules())));
	rule_lay->addWidget(rules_manager);
	ui.ruleBox->setLayout(rule_lay);
}

void CWindow::ChangeColor(unsigned i, unsigned j, Color inp_color)
{ /*
	QColor color;
	QPalette palette;

	switch (inp_color)
	{
	case Color::RED:
	{
		color = Qt::red;
		palette = drawed_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		drawed_rules[i][j]->setPalette(palette);
		drawed_rules[i][0]->setPalette(palette);

	}
		break;
	
	case Color::BLACK:
	{
		color = Qt::black;
		palette = drawed_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		drawed_rules[i][j]->setPalette(palette);
		drawed_rules[i][0]->setPalette(palette);
	}
		break;
	case Color::GREEN:
	{
		color = Qt::green;
		palette = drawed_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		drawed_rules[i][j]->setPalette(palette);
		drawed_rules[i][0]->setPalette(palette);
	}
	}
	*/
}


void CWindow::HideRows()
{
	unsigned size = ui.tableView->model()->rowCount();

	for (unsigned i = 1; i <= size; i++) {
		ui.tableView->hideRow(size - i);
	}

	size = algorithm->GetComments()->Size();
	for (unsigned j = 1; j <= size; j++) {
		ui.listView->setRowHidden(j, true);
	}

}

void CWindow::onParseModeClicked()
{
	RenderCWin(ModeOfCWin::CWPARSE);
}

void CWindow::onStartClicked()
{
	if (ui.lineInpStr->text().isEmpty()) {
		QMessageBox messageBox;
		messageBox.critical(0, QString::fromLocal8Bit("Ошибка: пустая строка"), 
							   QString::fromLocal8Bit("Введите строку для разбора!"));
		messageBox.setFixedSize(500, 200);
	}
	else {
		algorithm->SetParsingStr(ItemString(ui.lineInpStr->text().toLocal8Bit().constData()));
		algorithm->DoParse();
		/// ЛОГ СФОРМИРОВАН
		RenderCWin(ModeOfCWin::CWPARSESTARTED);


	}
}

void CWindow::onBackClicked()
{
	cur_rule.fir_num = -10; // знак того, что разбор не начат
	prev_rule.fir_num = -10;
	cur_table_row = 0; // ни одна строка не видна
	cur_comment_row = 0;
	qDeleteAll(ui.ruleBox->children());
	rules_manager = new RulesManager;

	//rules_manager->DeleteRules();
	//drawed_rules.clear();
	//delete algorithm;
	ui.btnParse->setDisabled(false);
	ui.btnStep->setDisabled(false);
	ui.btnRepeat->setDisabled(true);
	ui.btnStart->setDisabled(false);
	ui.lineInpStr->setDisabled(false);
	ui.lineInpStr->clear();
	ui.tableView->setModel(0);

	ui.listView->setModel(0);

	close();
	emit cWindowClosed();
}
// НЕ ТОТ ПОРЯДОК ПРОСМОТРА
/* //НЕ ТОТ ПОРЯДОК ПРОСМОТРА
void CWindow::onStepClicked()
{
	//
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:

		RuleNum last_rule;

		if (prev_rule.fir_num != -10) {											// если в предыдущий шаг какое-то правило было закрашено зелёным - 
			ChangeColor(prev_rule.fir_num, prev_rule.sec_num, Color::BLACK);	// покрасить его обратно в чёрный
			prev_rule.fir_num = -10;
		}

		if (cur_rule.fir_num == -10) // если начало поиска правил - смотрим с самого последнего правила
		{
			cur_rule.fir_num = algorithm->RulesSize() - 1;
			cur_rule.sec_num = algorithm->GetRule(cur_rule.fir_num).RightSize();
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED);
		}
		else {

			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::BLACK);	// если не начало поиска - красим обратно в чёрный предыдущее
			if (cur_rule.sec_num != 1) {	// идём дальше по правилам
				cur_rule.sec_num--;	
			}
			else {
				if (cur_rule.fir_num != 0) {
					cur_rule.fir_num--;
					cur_rule.sec_num = algorithm->GetRule(cur_rule.fir_num).RightSize();
				}
				else {
					ui.tableView->showRow(0);
					ui.tableView->selectRow(0);
					RenderCWin(ModeOfCWin::CWPARSEENDED);
					break;
				}
			}
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED); // закрашиваем красным следующее рассматриваемое правило
		}

		last_rule = algorithm->GetTable()->GetRow(cur_row)->GetRuleNum(); // last_rule - последнее искомое правило

		if ((last_rule.fir_num == cur_rule.fir_num) && (last_rule.sec_num == cur_rule.sec_num - 1)) // если правило нашлось
		{
			ui.tableView->showRow(cur_row);
			ui.tableView->selectRow(cur_row);

			scrollbar->setMaximum(200);
			emit scrollbar->setValue(200);

			if (cur_row != ui.tableView->model()->rowCount() - 1) {
				cur_row++;
				//проверка на тупик
				
				if (cur_rule.fir_num == 0) {
					ui.tableView->showRow(cur_row);
					ui.tableView->selectRow(cur_row);

					scrollbar->setMaximum(200);
					emit scrollbar->setValue(200);

					if (algorithm->GetTable()->GetRow(cur_row)->GetRuleNum().sec_num == -3) {
						RenderCWin(ModeOfCWin::CWPARSEENDED);
								break;
					}
					else {
						cur_row++;
						if (algorithm->GetTable()->GetRow(cur_row)->GetRuleNum().sec_num == -4) {
							ui.tableView->showRow(cur_row);
							ui.tableView->selectRow(cur_row);
							RenderCWin(ModeOfCWin::CWPARSEENDED);
							break;
						}
					}
				}
			}
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::GREEN);
			prev_rule = cur_rule;
			cur_rule.fir_num = -10; // начать смотреть правила сначала
		}
		
		break;

	case TypeOfAlg::TTOD:
		break;
	}
}
*/  //
// НЕКОРРЕКТНЫЙ ВЫВОД
/*
void CWindow::onStepClicked()
{
	//
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:

		RuleNum last_rule;

		if (prev_rule.fir_num != -10) {											// если в предыдущий шаг какое-то правило было закрашено зелёным - 
			ChangeColor(prev_rule.fir_num, prev_rule.sec_num, Color::BLACK);	// покрасить его обратно в чёрный
			prev_rule.fir_num = -10;
		}

		if (cur_rule.fir_num == -10) // если начало поиска правил - смотрим с первого правила
		{
			cur_rule.fir_num = 0;
			cur_rule.sec_num = 1;
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED);
		}
		else {

			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::BLACK);	// если не конец поиска - красим обратно в чёрный предыдущее
			if (cur_rule.sec_num != algorithm->GetRule(cur_rule.fir_num).RightSize()) {	// идём дальше по правилам
				cur_rule.sec_num++;
			}
			else {
				if (cur_rule.fir_num != algorithm->RulesSize()-1) {
					cur_rule.fir_num++;
					cur_rule.sec_num = 1;
				}
				else {
					ui.tableView->showRow(0);
					ui.tableView->selectRow(0);
					RenderCWin(ModeOfCWin::CWPARSEENDED);
					break;
				}
			}
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED); // закрашиваем красным следующее рассматриваемое правило

		}

		last_rule = algorithm->GetTable()->GetRow(cur_table_row)->GetRuleNum(); // last_rule - последнее искомое правило

		if ((last_rule.fir_num == cur_rule.fir_num) && (last_rule.sec_num == cur_rule.sec_num - 1)) // если правило нашлось
		{
			ui.tableView->showRow(cur_table_row);
			ui.tableView->selectRow(cur_table_row);

			scrollbar_table->setMaximum(200);
			emit scrollbar_table->setValue(200);

			if (cur_table_row != ui.tableView->model()->rowCount() - 1) {
				cur_table_row++;
				//проверка на тупик

				if (cur_rule.fir_num == 0) {
					ui.tableView->showRow(cur_table_row);
					ui.tableView->selectRow(cur_table_row);

					scrollbar_table->setMaximum(200);
					emit scrollbar_table->setValue(200);

					if (algorithm->GetTable()->GetRow(cur_table_row)->GetRuleNum().sec_num == -3) {
						RenderCWin(ModeOfCWin::CWPARSEENDED);
						break;
					}
					else {
						cur_table_row++;
						if (algorithm->GetTable()->GetRow(cur_table_row)->GetRuleNum().sec_num == -4) {
							ui.tableView->showRow(cur_table_row);
							ui.tableView->selectRow(cur_table_row);
							RenderCWin(ModeOfCWin::CWPARSEENDED);
							break;
						}
					}
				}
			}
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::GREEN);
			prev_rule = cur_rule;
			cur_rule.fir_num = -10; // начать смотреть правила сначала

			for (unsigned i = 0; i < 3; i++) {
				cur_comment_row++;
				ui.listView->setRowHidden(cur_comment_row, false);
				scrollbar_comments->setMaximum(200);
				scrollbar_comments->setValue(200);
			}


		}
		else {
			if (cur_comment_row != algorithm->GetComments()->Size()) {
				cur_comment_row++;
				ui.listView->setRowHidden(cur_comment_row, false);
				scrollbar_comments->setMaximum(200);
				scrollbar_comments->setValue(200);
			}
		}

		break;

	case TypeOfAlg::TTOD:
		break;
	}
}
*/ 

void CWindow::onStepClicked()
{
	rules_manager->ColorRule({ 0, 0 }, Color::RED);
}

void CWindow::onShowAllClicked()
{
	unsigned size = ui.tableView->model()->rowCount();

	for (unsigned i = 1; i <= size; i++) {
		ui.tableView->showRow(size - i);
	}
	size = algorithm->GetComments()->Size();
	for (unsigned j = 1; j <= size; j++) {
		ui.listView->setRowHidden(j, false);
	}
}