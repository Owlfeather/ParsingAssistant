#include "MainMenu.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>

// Преобразуем входную последовательность символов в кодировку UNICODE
#define RUS( str ) codec->toUnicode(str)


MainMenu::MainMenu(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	c_win = new CWindow;
	e_win = new EdWindow;
	e_win->hide();
	s_win = new SetWindow;
	s_win->hide();
	//i_win = new IWindow;

	connect(c_win, &CWindow::cWindowClosed, this, &MainMenu::show);
	connect(e_win, &EdWindow::edWindowClosed, this, &MainMenu::show);
	connect(s_win, &SetWindow::sWindowClosed, this, &MainMenu::show);

	connect(ui.btnExit, SIGNAL(clicked()), this, SLOT(onExitClicked()));
	connect(ui.btnHelp, SIGNAL(clicked()), this, SLOT(onHelpClicked()));
	connect(ui.btnEditor, SIGNAL(clicked()), this, SLOT(onEditorClicked()));
	connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(onTestClicked()));

	connect(ui.btnLtoR, SIGNAL(clicked()), this, SLOT(onLtoRClicked()));
	connect(ui.btnTtoD, SIGNAL(clicked()), this, SLOT(onTtoDClicked()));
	connect(ui.btnLLkTtoD, SIGNAL(clicked()), this, SLOT(onLLkTtoDClicked()));
	connect(ui.btnLRkStack, SIGNAL(clicked()), this, SLOT(onLRkStackClicked()));

	QPixmap picture(":/ParsingAssistant/LogoPNG.png");
	ui.label->setPixmap(picture);
	ui.label->resize(400, 400);
	//connect()
}

void MainMenu::onExitClicked()
{
	/*
	QTextCodec * codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("Выход"));
	msgBox.setText(RUS("Завершить приложение?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("Да"), QMessageBox::YesRole);
	msgBox.addButton(RUS("Нет"), QMessageBox::NoRole);

	msgBox.exec();

	if (msgBox.clickedButton() == pButtonYes) { exit(0); }
	else { show(); }
	*/
	close();
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

void MainMenu::onEditorClicked()
{
	e_win->show();
	hide();
}

void MainMenu::onTestClicked()
{
	s_win->show();
	hide();
}


void MainMenu::closeEvent(QCloseEvent* event)
{
	QTextCodec* codec = QTextCodec::codecForName("Windows-1251");
	QMessageBox msgBox;
	msgBox.setWindowTitle(RUS("Выход"));
	msgBox.setText(RUS("Завершить приложение?"));
	QAbstractButton* pButtonYes = msgBox.addButton(RUS("Да"), QMessageBox::YesRole);
	msgBox.addButton(RUS("Нет"), QMessageBox::NoRole);

	msgBox.exec();

	if (msgBox.clickedButton() == pButtonYes)
	{
		//exit(0); 
		//hide();
		delete c_win->GetIWin();
		delete c_win;
		exit(0);
	
	}
	else
	{
		//show(); 
		//return;
		event->ignore();

	}


	//delete c_win->GetIWin();
	//delete c_win;
}


