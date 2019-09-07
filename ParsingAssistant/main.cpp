#include "ParsingAssistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ParsingAssistant w;
	w.show();
	return a.exec();
}
