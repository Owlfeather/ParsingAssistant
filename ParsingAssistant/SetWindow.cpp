#include "SetWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QMouseEvent>

#define RUS( str ) codec->toUnicode(str)


SetWindow::SetWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	t_win = new TestWindow();
	t_win->hide();

	//connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));
	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));
	connect(ui.btnStart, SIGNAL(clicked()), this, SLOT(onStartClicked()));

}

SetWindow::~SetWindow()
{
}

void SetWindow::onStartClicked()
{
	TypeOfAlg a_type;
	if (ui.radioButtonLtoR->isChecked()) {
		a_type = TypeOfAlg::LTOR;
	}
	else if (ui.radioButton_TtoD->isChecked()) {
		a_type = TypeOfAlg::TTOD;
	}
	else a_type = TypeOfAlg::LTOR;

	setTestWinParams();
	t_win->show();
	hide();
}

void SetWindow::closeEvent(QCloseEvent* event)
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
		hide();
	}
	else
	{
		event->ignore();

	}
}

void SetWindow::setTestWinParams()
{
	TypeOfAlg a_type;
	if (ui.radioButtonLtoR->isChecked()) {
		a_type = TypeOfAlg::LTOR;
	}
	else if (ui.radioButton_TtoD->isChecked()) {
		a_type = TypeOfAlg::TTOD;
	}
	else a_type = TypeOfAlg::LTOR;

	t_win->setTestParams(ui.spinBox->value(), a_type);
}

void SetWindow::onBackClicked()
{
	hide();
	emit sWindowClosed();
}
