#include "CWindow.h"
#include <QTextCodec>

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
	DrawRules();

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnParse, SIGNAL(clicked()), this, SLOT(onParseModeClicked()));
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
			//
		}
	default:
		break;
	}
}

void CWindow::SetType(unsigned inp_alg_type)
{
	alg_type = inp_alg_type;
}

void CWindow::DrawRules()
{
	QVBoxLayout* vbox = new QVBoxLayout;

	std::vector<QLabel *> buf;
	std::vector<QHBoxLayout *> array_h_layouts;

	array_h_layouts.resize(3); //число правил

	drawed_rules.resize(3); ///число правил

	int size = 3;
	for (int i = 0; i < 3; i++) {
		array_h_layouts[i] = new QHBoxLayout;
		buf.clear();
		buf.resize(size);

		//drawed_rules[i].resize(size);

		for (int j = 0; j < size; j++) {
			buf[j] = new QLabel;
			buf[j]->setText("***");

			drawed_rules[i].push_back(buf[j]);

			array_h_layouts[i]->addWidget(buf[j]);
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

void CWindow::onBackClicked()
{
	ui.btnParse->setDisabled(false);
	close();
	emit cWindowClosed();
}
