#include "IWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>


IWindow::IWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));

}

IWindow::~IWindow()
{
}

void IWindow::SetHelpInfo()
{
	setWindowTitle(QString::fromLocal8Bit("Помощь"));
	QFile file(":/ParsingAssistant/help.txt");

	if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
	{
		ui.textEdit->setText(file.readAll());
		file.close();
	}
}

void IWindow::SetAlgorithmInfo(TypeOfAlg alg_type)
{
	QFile * file;
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"слева направо\""));
		file = new QFile(":/ParsingAssistant/LtoR.txt");

		if ((file->exists()) && (file->open(QIODevice::ReadOnly)))
		{
			ui.textEdit->setText(file->readAll());
			file->close();
		}
		delete file;
		break;
	case TypeOfAlg::TTOD:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"сверху вниз\""));
		file = new QFile(":/ParsingAssistant/TtoD.txt");

		if ((file->exists()) && (file->open(QIODevice::ReadOnly)))
		{
			ui.textEdit->setText(file->readAll());
			file->close();
		}
		delete file;
		break;
	case TypeOfAlg::LLK_TTOD:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"слева направо\" для LLk грамматик"));
		file = new QFile(":/ParsingAssistant/LLk.txt");

		if ((file->exists()) && (file->open(QIODevice::ReadOnly)))
		{
			ui.textEdit->setText(file->readAll());
			file->close();
		}
		delete file;
		break;
	case TypeOfAlg::LRK_STACK:
		setWindowTitle(QString::fromLocal8Bit("Разбор стековым методом для LRk грамматик"));
		file = new QFile(":/ParsingAssistant/LRk.txt");

		if ((file->exists()) && (file->open(QIODevice::ReadOnly)))
		{
			ui.textEdit->setText(file->readAll());
			file->close();
		}
		delete file;
		break;
	}
}

void IWindow::onClosedClicked()
{
	hide();
}
