#include "MainMenu.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QPushButton>

// Преобразуем входную последовательность символов в кодировку UNICODE
#define RUS( str ) codec->toUnicode(str)

//#define LTOR 0
//#define TTOD 1

//#define CWBEGIN 0
//#define CWPARSE 1
//#define CWTEST 2

MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	c_win = new CWindow;
	connect(c_win, &CWindow::cWindowClosed, this, &MainMenu::show);

	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));

	connect(ui.btnLtoR, SIGNAL(clicked()), this, SLOT(onLtoRClicked()));
	connect(ui.btnTtoD, SIGNAL(clicked()), this, SLOT(onTtoDClicked()));

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

void MainMenu::onLtoRClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::LTOR);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	close();
}

void MainMenu::onTtoDClicked()
{
	c_win->SetAlgorithm(TypeOfAlg::TTOD);
	c_win->RenderCWin(ModeOfCWin::CWBEGIN);
	c_win->show();
	close();
}

