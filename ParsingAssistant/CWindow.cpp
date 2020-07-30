#include "CWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QMouseEvent>


#define RUS( str ) codec->toUnicode(str)

CWindow::CWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	i_win = new InfWindow;

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
	connect(ui.btnStep, SIGNAL(clicked()), this, SLOT(onStepClicked()));
	connect(ui.btnShowAll, SIGNAL(clicked()), this, SLOT(onShowAllClicked()));
	connect(ui.btnRepeat, SIGNAL(clicked()), this, SLOT(onRepeatClicked()));
	connect(ui.btnNewParse, SIGNAL(clicked()), this, SLOT(onNewParseClicked()));
	connect(ui.btnInform, SIGNAL(clicked()), this, SLOT(onInformClicked()));
	connect(ui.btnGenCor, SIGNAL(clicked()), this, SLOT(onGenCorClicked()));
	connect(ui.btnGenIncor, SIGNAL(clicked()), this, SLOT(onGenIncorClicked()));
	connect(ui.btnGenRand, SIGNAL(clicked()), this, SLOT(onGenRandClicked()));




	scrollbar_table = new QScrollBar;
	ui.tableView->setVerticalScrollBar(scrollbar_table);
	scrollbar_comments = new QScrollBar;
	ui.listView->setVerticalScrollBar(scrollbar_comments);

	rules_manager = new RulesManager;
	string_generator = new TestStringGenerator;
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
			ui.btnRepeat->setDisabled(true);
			ui.btnStep->setVisible(false);
			ui.btnShowAll->setDisabled(true);

		
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
			ui.genBox->setDisabled(true);

			switch (alg_type)
			{
			case TypeOfAlg::LTOR:
				ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
				break;
			case TypeOfAlg::TTOD:
				ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
				ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

				break;
			case TypeOfAlg::LLK_TTOD:

			case TypeOfAlg::LRK_STACK:
				ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
				
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


void CWindow::DrawRules()
{
	QVBoxLayout* rule_lay = new QVBoxLayout;

	rules_manager->setLayout(rules_manager->DrawRules((algorithm->GetRules())));
	rule_lay->addWidget(rules_manager);

	if (alg_type == TypeOfAlg::LRK_STACK) {
		QTableView* relation_view = new QTableView;
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


		rules_manager->SetViewRelation(relation_view);

		RelTable* table = new RelTable(dynamic_cast<Stack_LRk_MethodAlg*>(algorithm)->GetRelationTable());

		relation_view->horizontalHeader()->setStyleSheet("font: bold 14px;");
		relation_view->verticalHeader()->setStyleSheet("font: bold 14px;");

		rules_manager->SetRelationTable(table);
		rules_manager->SetRelModel();
	}
	ui.ruleBox->setLayout(rule_lay);
}


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
	ui.genBox->setDisabled(false);
}

void CWindow::onInformClicked()
{
	i_win->SetAlgorithmInfo(alg_type);
	i_win->show();
}

void CWindow::onGenCorClicked()
{
	ui.lineInpStr->clear();
	QString generated_string;
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
	case TypeOfAlg::TTOD:
		generated_string = string_generator->correctNumber();
		break;
	case TypeOfAlg::LLK_TTOD:
	case TypeOfAlg::LRK_STACK:
		generated_string = string_generator->expression();
		break;
	}
	ui.lineInpStr->setText(generated_string);
}

void CWindow::onGenIncorClicked()
{
	ui.lineInpStr->clear();
	QString generated_string;
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
	case TypeOfAlg::TTOD:
		generated_string = string_generator->incorrectNumber();
		break;
	case TypeOfAlg::LLK_TTOD:
	case TypeOfAlg::LRK_STACK:
		generated_string = string_generator->incorrectExpression();
		break;
	}
	ui.lineInpStr->setText(generated_string);
}

void CWindow::onGenRandClicked()
{
	bool variants[] = { true, false };
	bool variant = variants[QRandomGenerator::global()->bounded(2)];
	if (variant) {
		onGenCorClicked();
	}
	else {
		onGenIncorClicked();
	}
}

void CWindow::closeEvent(QCloseEvent* event)
{
	i_win->hide();
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("Выход"));
	msgBox.setText(RUS("Завершить приложение?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("Да"), QMessageBox::YesRole);
	msgBox.addButton(RUS("Нет"), QMessageBox::NoRole);

	msgBox.exec();

	if (msgBox.clickedButton() == pButtonYes) 
	{  
		hide();
	}
	else 
	{ 
		event->ignore();

	}
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
	ui.genBox->setDisabled(false);
	ui.lineInpStr->clear();
	ui.tableView->setModel(0);

	ui.listView->setModel(0);

	algorithm->GetTable()->ResetRow();
	algorithm->GetComments()->ResetRow();
	////////////////////////////////

	//close();
	hide();
	emit cWindowClosed();
}


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

					ui.tableView->showRow(algorithm->GetTable()->GetNextRow());
					algorithm->GetTable()->IncRow();
					scrollbar_table->setMaximum(200);
					scrollbar_table->setValue(200);
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
				rules_manager->ShowRelationOnTable(cur_comment->GetRuleNum());

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