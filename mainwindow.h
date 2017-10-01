#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QProcess>
#include <QDebug>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

 public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onActKnopf_trigged(bool onOff);
	void createActions();

private:
	Ui::MainWindow *ui;
	QAction *actRpc1, *actRpc2, *actRpc3;
	QActionGroup *actGrp;
};

#endif // MAINWINDOW_H
