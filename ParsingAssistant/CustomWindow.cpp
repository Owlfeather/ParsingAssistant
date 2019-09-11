#include "CustomWindow.h"
#include <QTextCodec>

// Преобразуем входную последовательность символов в кодировку UNICODE
#define RUS( str ) codec->toUnicode(str)

CustomWindow::CustomWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//connect()
}