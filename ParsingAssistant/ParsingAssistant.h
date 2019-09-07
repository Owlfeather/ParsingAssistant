#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ParsingAssistant.h"
#include "ui_MainMenu.h"

class ParsingAssistant : public QMainWindow
{
	Q_OBJECT

public:
	ParsingAssistant(QWidget *parent = Q_NULLPTR);

private:
	Ui::MainWindow ui;
};
