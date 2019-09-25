#include "CWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>




#define RUS( str ) codec->toUnicode(str)



CWindow::CWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//log_table = new LogTable;
	//DrawRules();

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	connect(ui.btnStep, SIGNAL(clicked()), this, SLOT(onStepClicked()));
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
			cur_row = 0;
			break;
			//ui.ruleBox->close();
			//ui.ruleBox->show();
			//
		}
	case ModeOfCWin::CWPARSESTARTED:
		{
			ui.btnStep->setVisible(true);
			ui.btnStart->setDisabled(true);
			ui.lineInpStr->setDisabled(true);
			ui.tableView->setModel(algorithm->GetTable());
			ui.tableView->resizeColumnsToContents();
			HideRows();
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

void CWindow::DrawRules()
{
	QVBoxLayout* vbox = new QVBoxLayout;
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

	//ChangeColor(1, 1);
}

void CWindow::ChangeColor(unsigned i, unsigned j, Color inp_color)
{
	QColor color;
	QPalette palette;

	switch (inp_color)
	{
		//QColor color;
		//QPalette palette;

	case Color::RED:
		//drawed_rules[i][0]->setStyleSheet("color: red; font-family: Century Gothic, interval; font-size: 100%");
		
		//drawed_rules[i][j]->setStyleSheet("color: red");
		//drawed_rules[i][0]->setStyleSheet("color: red");
	{
		color = Qt::red;
		palette = drawed_rules[i][j]->palette();
		palette.setColor(QPalette::WindowText, color);
		drawed_rules[i][j]->setPalette(palette);
		drawed_rules[i][0]->setPalette(palette);

	}
		break;
	
	case Color::BLACK:
		//drawed_rules[i][0]->setStyleSheet("color: black; font-family: Century Gothic, interval; font-size: 100% ");
		
		//drawed_rules[i][j]->setStyleSheet("color: black");
		//drawed_rules[i][0]->setStyleSheet("color: black");
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
}


void CWindow::HideRows()
{
	unsigned size = ui.tableView->model()->rowCount();

	for (unsigned i = 1; i <= size; i++) {
		ui.tableView->hideRow(size - i);
	}
	//ui.tableView->hideRow(size);

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
		//ui.btnStart->setDisabled(true);
		//ui.lineInpStr->setDisabled(true);
		algorithm->DoParse();
		/// ЛОГ СФОРМИРОВАН
		//log_table = new LogTable;
		
		/////////////////////////////////////////////////////
		//algorithm->SetLogTable(alg_type);

		//ui.tableView->setModel(algorithm->GetTable());
		//ui.tableView->resizeColumnsToContents();
		//ui.tableView->setStyleSheet("border: 1px solid;  border-radius: 10px;");
		//ui.tableView->setStyleSheet("QHeaderView::section:checked{border: 1px solid;  border-radius: 10px;}"); 

		/////////////////////////////////////////////////////
		RenderCWin(ModeOfCWin::CWPARSESTARTED);


	}
}

void CWindow::onBackClicked()
{
	cur_rule.fir_num = -10; // знак того, что разбор не начат
	prev_rule.fir_num = -10;
	cur_row = 0; // ни одна строка не видна
	qDeleteAll(ui.ruleBox->children());
	drawed_rules.clear();
	//delete algorithm;
	ui.btnParse->setDisabled(false);
	ui.btnStart->setDisabled(false);
	ui.lineInpStr->setDisabled(false);
	ui.lineInpStr->clear();
	ui.tableView->setModel(0);
	close();
	emit cWindowClosed();
}

void CWindow::onStepClicked()
{
	//
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		if (prev_rule.fir_num != -10) {
			ChangeColor(prev_rule.fir_num, prev_rule.sec_num, Color::BLACK);
			prev_rule.fir_num = -10;
		}
		if (cur_rule.fir_num == -10) // начало разбора
		{
			cur_rule.fir_num = algorithm->RulesSize() - 1;
			cur_rule.sec_num = algorithm->GetRule(cur_rule.fir_num).RightSize();
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED);
		}
		else {
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::BLACK);
			if (cur_rule.sec_num != 1) {
				cur_rule.sec_num--;
			}
			else {
				if (cur_rule.fir_num != 0) {
					cur_rule.fir_num--;
					cur_rule.sec_num = algorithm->GetRule(cur_rule.fir_num).RightSize();
				}
			}
			ChangeColor(cur_rule.fir_num, cur_rule.sec_num, Color::RED);
		}

		if ((algorithm->GetTable()->GetRow(cur_row)->GetRuleNum().fir_num == cur_rule.fir_num) 
			&& (algorithm->GetTable()->GetRow(cur_row)->GetRuleNum().sec_num == cur_rule.sec_num - 1))
		{
			ui.tableView->showRow(cur_row);
			if (cur_row != ui.tableView->model()->rowCount() - 1) {
				cur_row++;
				if (cur_rule.fir_num == 0) {
					ui.tableView->showRow(cur_row);
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
