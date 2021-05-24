#pragma once
#pragma once

#include <QWidget>
#include "ui_EdWindow.h"

class EdWindow : public QWidget
{
	Q_OBJECT

public:
	EdWindow(QWidget* parent = Q_NULLPTR);
	~EdWindow();

private:
	Ui::EdWindow ui;

signals:
	void edWindowClosed();

private slots:
	void onBackClicked();
	//void onClosedClicked();

protected:
	void closeEvent(QCloseEvent* event);
};

