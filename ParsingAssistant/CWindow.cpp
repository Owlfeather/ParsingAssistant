#include "CWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>




#define RUS( str ) codec->toUnicode(str)

#define LTOR 0
#define TTOD 1

#define CWBEGIN 0
#define CWPARSE 1
#define CWTEST 2

CWindow::CWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	log_table = new LogTable;
	//DrawRules();

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));
}

CWindow::~CWindow()
{
}

void CWindow::RenderCWin(unsigned type)
{

	switch (type)
	{
	case CWBEGIN: // окно только открыто, показываем меню
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
			case LTOR:
			{ ui.lblName->setText(RUS("Левосторонний восходящий разбор")); break; }
			case TTOD:
			{ ui.lblName->setText(RUS("Левосторонний нисходящий разбор")); break; }
			default:
				break;
			}
		break;
		}
	case CWPARSE:
		{
			ui.grboxParse->setVisible(true);
			ui.btnParse->setDisabled(true);
			//ui.ruleBox->close();
			//ui.ruleBox->show();
			//
		}
	}
}

void CWindow::SetAlgorithm(unsigned inp_alg_type)
{
	alg_type = inp_alg_type;

	switch (alg_type)
	{
	case LTOR: 
		{
			LtoR_MethodAlg * cur_alg = new LtoR_MethodAlg;
			algorithm = cur_alg;
			break;
		}
	case TTOD:
		{
			TtoD_MethodAlg* cur_alg = new TtoD_MethodAlg;
			algorithm = cur_alg;
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

void CWindow::ChangeColor(unsigned i, unsigned j)
{
	drawed_rules[i][j]->setStyleSheet("color: red");
}


void CWindow::onParseModeClicked()
{

	RenderCWin(CWPARSE);
}

void CWindow::onStartClicked()
{
	if (ui.lineInpStr->text().isEmpty()) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "An error has occured !");
		messageBox.setFixedSize(500, 200);
	}
	else {
		algorithm->SetParsingStr(ItemString(ui.lineInpStr->text().toLocal8Bit().constData()));
		ui.btnStart->setDisabled(true);
		ui.lineInpStr->setDisabled(true);
		algorithm->DoParse();
		/// ЛОГ СФОРМИРОВАН
		//log_table = new LogTable;
		
		algorithm->SetLogTable(alg_type);
		ui.tableView->setModel(algorithm->GetTable());
	}
}

void CWindow::onBackClicked()
{
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
