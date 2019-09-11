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

	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
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
	default:
		break;
	}
}

void CWindow::SetType(unsigned inp_alg_type)
{
	alg_type = inp_alg_type;
}

void CWindow::onBackClicked()
{
	//w.show();
	//hide();
	close();
	emit mainMenu();
}
