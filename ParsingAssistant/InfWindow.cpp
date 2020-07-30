#include "InfWindow.h"
#include <QTextCodec>
#include <QString>
#include <QMessageBox>
#include <QColorDialog>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QVBoxLayout>


InfWindow::InfWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(onClosedClicked()));

}

InfWindow::~InfWindow()
{
}


void InfWindow::SetHelpInfo()
{
	setWindowTitle(QString::fromLocal8Bit("Помощь"));
	QFile file(":/ParsingAssistant/help.htm");

	if ((file.exists()) && (file.open(QIODevice::ReadOnly)))
	{
		QString html(file.readAll());
		ui.textBrowser->setHtml(html);
		ui.textBrowser->show();
		file.close();
	}
}

void InfWindow::SetAlgorithmInfo(TypeOfAlg alg_type)
{
	QFile* file;
	switch (alg_type)
	{
	case TypeOfAlg::LTOR:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"слева направо\""));
		file = new QFile(":/ParsingAssistant/LtoR.htm");
		break;
	case TypeOfAlg::TTOD:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"сверху вниз\""));
		file = new QFile(":/ParsingAssistant/TtoD.htm");
		break;
	case TypeOfAlg::LLK_TTOD:
		setWindowTitle(QString::fromLocal8Bit("Разбор \"слева направо\" для LLk грамматик"));
		file = new QFile(":/ParsingAssistant/LLk.htm");
		break;
	case TypeOfAlg::LRK_STACK:
		setWindowTitle(QString::fromLocal8Bit("Разбор стековым методом для LRk грамматик"));
		file = new QFile(":/ParsingAssistant/LRk.htm");
		break;
	}

	if ((file->exists()) && (file->open(QIODevice::ReadOnly)))
	{
		QString html(file->readAll());
		ui.textBrowser->setHtml(html);
		ui.textBrowser->show();
		file->close();
	}
	delete file;
}

void InfWindow::onClosedClicked()
{
	hide();
}
