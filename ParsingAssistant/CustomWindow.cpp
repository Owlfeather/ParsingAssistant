#include "CustomWindow.h"
#include <QTextCodec>

// ����������� ������� ������������������ �������� � ��������� UNICODE
#define RUS( str ) codec->toUnicode(str)

CustomWindow::CustomWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//connect()
}