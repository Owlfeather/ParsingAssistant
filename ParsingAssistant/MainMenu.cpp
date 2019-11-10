#include "MainMenu.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QPushButton>

// Преобразуем входную последовательность символов в кодировку UNICODE
#define RUS( str ) codec->toUnicode(str)


MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	c_win = new CWindow;
	//i_win = new IWindow;

	connect(c_win, &CWindow::cWindowClosed, this, &MainMenu::show);

	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));
	connect(ui.btnHelp, SIGNAL(clicked()), this, SLOT(onHelpClicked()));

	connect(ui.btnLtoR, SIGNAL(clicked()), this, SLOT(onLtoRClicked()));
	connect(ui.btnTtoD, SIGNAL(clicked()), this, SLOT(onTtoDClicked()));
	connect(ui.btnLLkTtoD, SIGNAL(clicked()), this, SLOT(onLLkTtoDClicked()));
	connect(ui.btnLRkStack, SIGNAL(clicked()), this, SLOT(onLRkStackClicked()));

	//connect()
}

void MainMenu::onExitClicked()
{
	QTextCodec * codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("Выход"));
	msgBox.setText(RUS("Завершить приложение?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("Да"), QMessageBox::YesRole);
	msgBox.addButton(RUS("Нет"), QMessageBox::NoRole);

	msgBox.exec();

	if (msgBox.clickedButton() == pButtonYes) { exit(0); }
	else { show(); }
};

MainMenu::~MainMenu()
{
}

void MainMenu::onLtoRClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::LTOR);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	//close();
	hide();
}

void MainMenu::onTtoDClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::TTOD);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	//close();
	hide();

}

void MainMenu::onLLkTtoDClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::LLK_TTOD);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	//close();
	hide();

}

void MainMenu::onLRkStackClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::LRK_STACK);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	//close();
	hide();

}

void MainMenu::onHelpClicked()
{
	c_win->GetIWin()->SetHelpInfo();
	c_win->GetIWin()->show();

}


void MainMenu::closeEvent(QCloseEvent* event)
{
	delete c_win->GetIWin();
	delete c_win;
}


