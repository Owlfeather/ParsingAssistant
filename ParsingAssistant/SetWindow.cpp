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

	//connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));
	connect(ui.btnBack, SIGNAL(clicked()), this, SLOT(onBackClicked()));

}

SetWindow::~SetWindow()
{
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

void SetWindow::onBackClicked()
{
	hide();
	emit sWindowClosed();
}
