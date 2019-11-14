﻿#include "CWindow.h"
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
	i_win = new IWindow;

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	connect(ui.btnStep, SIGNAL(clicked()), this, SLOT(onStepClicked()));
	connect(ui.btnShowAll, SIGNAL(clicked()), this, SLOT(onShowAllClicked()));
	connect(ui.btnRepeat, SIGNAL(clicked()), this, SLOT(onRepeatClicked()));
	connect(ui.btnNewParse, SIGNAL(clicked()), this, SLOT(onNewParseClicked()));
	connect(ui.btnInform, SIGNAL(clicked()), this, SLOT(onInformClicked()));



	scrollbar_table = new QScrollBar;
	ui.tableView->setVerticalScrollBar(scrollbar_table);
	scrollbar_comments = new QScrollBar;
	ui.listView->setVerticalScrollBar(scrollbar_comments);

	rules_manager = new RulesManager;
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
			ui.btnShowAll->setDisabled(true);

			//ui.lineInpStr->setFocus();
			//ui.lineInpStr->grabKeyboard();
		
			QTextCodec * codec = QTextCodec::codecForName("Windows-1251");
			switch (alg_type)
			{
			case TypeOfAlg::LTOR:
			{ ui.lblName->setText(RUS("Левосторонний восходящий разбор")); break; }
			case TypeOfAlg::TTOD:
			{ ui.lblName->setText(RUS("Левосторонний нисходящий разбор")); break; }
			case TypeOfAlg::LLK_TTOD:
			{ ui.lblName->setText(RUS("Левосторонний нисходящий разбор для LLk грамматики")); break; }
			case TypeOfAlg::LRK_STACK:
			{ ui.lblName->setText(RUS("Разбор стековым методом для LRk грамматики")); break; }
			default:
				break;
			}
		break;
		}
	case ModeOfCWin::CWPARSE:
		{
			ui.grboxParse->setVisible(true);
			ui.btnParse->setDisabled(true);

			ui.lineInpStr->setFocus();
			ui.lineInpStr->grabKeyboard();

			algorithm->GetTable()->ResetRow();
			algorithm->GetComments()->ResetRow();

			break;
		}
	case ModeOfCWin::CWPARSESTARTED:
		{
			ui.btnStep->setVisible(true);
			ui.btnStep->setDisabled(false);
			ui.btnStart->setDisabled(true);
			ui.lineInpStr->setDisabled(true);
			ui.btnShowAll->setDisabled(false);
			ui.tableView->setModel(algorithm->GetTable());
			ui.tableView->resizeColumnsToContents();
			//ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

			//int size = 0;
			switch (alg_type)
			{
			case TypeOfAlg::LTOR:
				//size = 2;
				ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
				break;
			case TypeOfAlg::TTOD:
				ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
				ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

				break;
			case TypeOfAlg::LLK_TTOD:
				//size = 3;

			case TypeOfAlg::LRK_STACK:
				//size = 6;
				ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
				//ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
				//ui.tableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
				break;
			}

			
			ui.listView->setModel(algorithm->GetComments());
			HideRows();


			break;
		}
	case ModeOfCWin::CWPARSEENDED:
		{
			ui.btnRepeat->setEnabled(true);
			ui.btnStep->setEnabled(false);
			ui.btnShowAll->setDisabled(true);
			rules_manager->Neutralize();

			break;
		}
	case ModeOfCWin::CWRESET:
	{
		ui.btnParse->setDisabled(false);
		ui.btnStep->setDisabled(true);
		ui.btnStep->setVisible(false);
		ui.btnRepeat->setDisabled(true);
		ui.btnStart->setDisabled(false);
		ui.lineInpStr->setDisabled(false);
		ui.btnShowAll->setDisabled(true);

		ui.lineInpStr->clear();
		ui.lineInpStr->setDisabled(false);
		ui.lineInpStr->setFocus();
		ui.lineInpStr->grabKeyboard();

		ui.tableView->setModel(0);
		ui.listView->setModel(0);

		algorithm->GetTable()->ResetRow();
		algorithm->GetComments()->ResetRow();
		rules_manager->Neutralize();

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
	case TypeOfAlg::LLK_TTOD:
	{
		TtoD_LLk_MethodAlg* cur_alg = new  TtoD_LLk_MethodAlg;
		algorithm = cur_alg;
		algorithm->SetLogTableType(TypeOfAlg::LLK_TTOD);
		break;
	}
	case TypeOfAlg::LRK_STACK:
	{
		Stack_LRk_MethodAlg* cur_alg = new  Stack_LRk_MethodAlg;
		algorithm = cur_alg;
		algorithm->SetLogTableType(TypeOfAlg::LRK_STACK);
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

	if (alg_type == TypeOfAlg::LRK_STACK) {
		QTableView* relation_view = new QTableView;
		//relation_view->setBaseSize({ 100, 200 });
		relation_view->setMinimumSize({ 245, 216 });

		QHBoxLayout* rule_tab_l = new QHBoxLayout;
		rule_tab_l->addStretch(50);
		rule_tab_l->addWidget(relation_view);
		rule_tab_l->addStretch(50);
		rule_lay->addLayout(rule_tab_l);
		///////
		QVBoxLayout* parsed_str_l = new QVBoxLayout;
		QLabel* my_string = new QLabel;
		rules_manager->SetStringOfIds(my_string);
		my_string->setText(QString::fromLocal8Bit("Введите строку"));
		parsed_str_l->addWidget(my_string);
		rule_lay->addLayout(parsed_str_l);
		////////


		//rule_lay->addWidget(relation_view);
		rules_manager->SetViewRelation(relation_view);

		RelTable* table = new RelTable(dynamic_cast<Stack_LRk_MethodAlg*>(algorithm)->GetRelationTable());

		relation_view->horizontalHeader()->setStyleSheet("font: bold 14px;");
		relation_view->verticalHeader()->setStyleSheet("font: bold 14px;");

		rules_manager->SetRelationTable(table);
		rules_manager->SetRelModel();
	}
	ui.ruleBox->setLayout(rule_lay);
}

//void CWindow::ChangeColor(unsigned i, unsigned j, Color inp_color)
/*{ 
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
	
}*/


void CWindow::HideRows()
{
	unsigned size = ui.tableView->model()->rowCount();

	for (unsigned i = 1; i <= size; i++) {
		ui.tableView->hideRow(size - i);
	}

	if ((alg_type == TypeOfAlg::TTOD)
		|| (alg_type == TypeOfAlg::LLK_TTOD))
	{
		ui.tableView->showRow(0);
		algorithm->GetTable()->IncRow();
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

		if (alg_type == TypeOfAlg::LRK_STACK) {
			rules_manager->TextStringOfIds("Строка: "+algorithm->GetParsingString());
		}

	}
}

void CWindow::onNewParseClicked()
{
	RenderCWin(ModeOfCWin::CWRESET);
	algorithm->ResetLogs();

	if (alg_type == TypeOfAlg::LRK_STACK) {
		rules_manager->TextStringOfIds("");
	}

}

void CWindow::onInformClicked()
{
	i_win->SetAlgorithmInfo(alg_type);
	i_win->show();
}

void CWindow::closeEvent(QCloseEvent* event)
{
	i_win->hide();
}

void CWindow::onRepeatClicked()
{
	HideRows();
	rules_manager->Neutralize();
	ui.btnStep->setDisabled(false);
	ui.btnShowAll->setDisabled(false);
	algorithm->GetComments()->ResetRow();
	algorithm->GetTable()->ResetRow();
}

void CWindow::onBackClicked()
{

	qDeleteAll(ui.ruleBox->children());
	rules_manager = new RulesManager;

	////////////////////////////////
	ui.btnParse->setDisabled(false);
	ui.btnStep->setDisabled(false);
	ui.btnRepeat->setDisabled(true);
	ui.btnStart->setDisabled(false);
	ui.lineInpStr->setDisabled(false);
	ui.btnShowAll->setDisabled(true);
	ui.lineInpStr->clear();
	ui.tableView->setModel(0);

	ui.listView->setModel(0);

	algorithm->GetTable()->ResetRow();
	algorithm->GetComments()->ResetRow();
	////////////////////////////////

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
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
	{
		if (algorithm->GetComments()->NotEnd()) {

			ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);

			scrollbar_comments->setMaximum(1000);
			scrollbar_comments->setValue(1000);

			///УПРАВЛЕНИЕ БЛОКАМИ///
			Comment* cur_comment = algorithm->GetComments()->GetRow(algorithm->GetComments()->GetNextRow());

			switch (cur_comment->GetType())
			{
			case TypeOfComment::INFO:
			{
				rules_manager->Neutralize();
				break;
			}
			case TypeOfComment::WRONG_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::RED);
				break;
			}
			case TypeOfComment::CORRECT_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);

				algorithm->GetComments()->IncRow();
				ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);

				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				break;
			}
			case TypeOfComment::DEAD_END:
			{
				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);
				break;
			}
			case TypeOfComment::PARSE_CORRECT:
			case TypeOfComment::PARSE_INCORRECT:
			{
				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				RenderCWin(ModeOfCWin::CWPARSEENDED);
				break;
			}
			}

			algorithm->GetComments()->IncRow();
		}
			

		break;
	}
	case TypeOfAlg::TTOD:
	{
		if (algorithm->GetComments()->NotEnd()) {

			ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);

			scrollbar_comments->setMaximum(1000);
			scrollbar_comments->setValue(1000);

			///УПРАВЛЕНИЕ БЛОКАМИ///
			Comment* cur_comment = algorithm->GetComments()->GetRow(algorithm->GetComments()->GetNextRow());

			switch (cur_comment->GetType())
			{
			case TypeOfComment::INFO:
			{
				rules_manager->Neutralize();
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);
				break;
			}
			case TypeOfComment::WRONG_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::RED);
				break;
			}
			case TypeOfComment::CORRECT_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);

				algorithm->GetComments()->IncRow();
				ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);

				for (int i = 0; i < 3; i++){
					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					//ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);
				}

				break;
			}
			case TypeOfComment::DEAD_END:
			{
				rules_manager->Neutralize();

				algorithm->GetComments()->IncRow();
				ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);

				//for(int i = 0; i < 2; i++){
					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);
			//	}
				break;
			}
			case TypeOfComment::HYPOTHESIS:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);

				algorithm->GetComments()->IncRow();
				ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);

				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				//ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				break;
			}
			case TypeOfComment::PARSE_INCORRECT:

				for (int i = 0; i < 2; i++) {
					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);
				}

			case TypeOfComment::PARSE_CORRECT:
			{
			//	ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
			//	ui.tableView->selectRow(algorithm->GetTable()->GetNextRow());
			//	algorithm->GetTable()->IncRow();
			//	scrollbar_table->setMaximum(200);
			//	scrollbar_table->setValue(200);

				RenderCWin(ModeOfCWin::CWPARSEENDED);
				break;
			}
			}

			algorithm->GetComments()->IncRow();
		}


		break;
	}
	case TypeOfAlg::LLK_TTOD:
	{
		if (algorithm->GetComments()->NotEnd()) {

			ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);

			scrollbar_comments->setMaximum(1000);
			scrollbar_comments->setValue(1000);

			///УПРАВЛЕНИЕ БЛОКАМИ///
			Comment* cur_comment = algorithm->GetComments()->GetRow(algorithm->GetComments()->GetNextRow());

			switch (cur_comment->GetType())
			{
			case TypeOfComment::INFO:
			{
				rules_manager->Neutralize();
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);
				break;
			}
			
			case TypeOfComment::CORRECT_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);


				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				break;
			}
			
			case TypeOfComment::HYPOTHESIS:
			{
				rules_manager->Neutralize();

				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				break;
			}
			case TypeOfComment::PARSE_INCORRECT:

					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);


			case TypeOfComment::PARSE_CORRECT:
			{

				RenderCWin(ModeOfCWin::CWPARSEENDED);
				break;
			}
			}

			algorithm->GetComments()->IncRow();
		}


		break;
	}
	case TypeOfAlg::LRK_STACK:
	{
		if (algorithm->GetComments()->NotEnd()) {

			ui.listView->setRowHidden(algorithm->GetComments()->GetNextRow(), false);

			scrollbar_comments->setMaximum(1000);
			scrollbar_comments->setValue(1000);

			///УПРАВЛЕНИЕ БЛОКАМИ///
			Comment* cur_comment = algorithm->GetComments()->GetRow(algorithm->GetComments()->GetNextRow());

			switch (cur_comment->GetType())
			{
			case TypeOfComment::INFO:
			{
				rules_manager->Neutralize();
				scrollbar_comments->setMaximum(1000);
				scrollbar_comments->setValue(1000);
				break;
			}

			case TypeOfComment::CORRECT_RULE:
			{
				rules_manager->Neutralize();
				rules_manager->ClearRelSelection();
				//rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);
				rules_manager->ShowRelationOnTable(cur_comment->GetRuleNum());

			//	ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
			//	algorithm->GetTable()->IncRow();
			//	scrollbar_table->setMaximum(200);
			//	scrollbar_table->setValue(200);

				if (cur_comment->GetText().find("Перенос") != string::npos) {
					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);
				}

				break;
			}

			case TypeOfComment::HYPOTHESIS:
			{
				rules_manager->Neutralize();

			//	ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
			//	algorithm->GetTable()->IncRow();
			//	scrollbar_table->setMaximum(200);
			//	scrollbar_table->setValue(200);

				break;
			}
			case TypeOfComment::ACTION:
			{
				rules_manager->Neutralize();
				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);

				if (cur_comment->GetText().find("Результат") != string::npos) {
					rules_manager->ColorRule(cur_comment->GetRuleNum(), Color::GREEN);
				}

				break;
			}
			case TypeOfComment::PARSE_INCORRECT:

				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);


			case TypeOfComment::PARSE_CORRECT:
			{
				ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
				algorithm->GetTable()->IncRow();
				scrollbar_table->setMaximum(200);
				scrollbar_table->setValue(200);
				RenderCWin(ModeOfCWin::CWPARSEENDED);
				break;
			}
			}

			algorithm->GetComments()->IncRow();
		}


		break;
	}
	}
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
	RenderCWin(ModeOfCWin::CWPARSEENDED);
}