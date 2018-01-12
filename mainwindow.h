#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QActionGroup>
#include <QtWidgets>
#include <QProcess>
#include <QDebug>
#include <QObject>
#include <QProcess>
#include <QDataStream>

#include "mdbQtStd/globals.h"

namespace Ui {
	class MainWindow;
}


struct Credential {
	Credential() { }
	~Credential() { }
	Credential(const Credential &) { }

	Credential(QString Domain, QString User, QString Pass) :
		mDomain(Domain), mUser(User), mPass(Pass) { }
	Credential(QString DUP, QChar sep) :
		mDomain(DUP.split(sep)[0]),
		mUser(DUP.split(sep)[1]),
		mPass(DUP.split(sep)[2]) { }

	QString getDom() {
		return QString(mDomain);
	}
	QString getUser() {
		return QString(mUser);
	}
	QString getPass() {
		return QString(mPass);
	}
	QString getDomUserPass(QChar sep = ':') {
		mSep = sep;
		return QString(mDomain + sep + mUser + sep + mPass);
	}

//	 protected:
	QString mDomain, mUser, mPass;
	QChar mSep;
};
Q_DECLARE_METATYPE(Credential);

//typedef struct Credential Credential;


class MainWindow : public QMainWindow {
	Q_OBJECT

 public:

	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

 public slots:
//	friend QDataStream &operator>>(QDataStream &in, MainWindow::Credential &c);
	void onActTry(bool triiggd);

protected:
	void connect();
	bool restoreActionObjects();
	void createLists();
	void connectSlots();

 protected slots:
	void onActionGroupTrigd(QAction *sender);
	void onSelectionChanged();
	void clearList();

 private slots:
	void createActions();
	void onActConnectTriggered(bool trigged);

 private:
	Ui::MainWindow *ui;
	QAction *actRpc1, *actRpc2, *actRpc3;
	QActionGroup *actGrTbMain, *actGrTbMenu, *actGrp;
};

//Q_DECLARE_METATYPE(MainWindow::Credential);

class WorkerThread : public QThread {
	Q_OBJECT
	void run() override {
		QString result;
		/* ... here is the expensive or blocking operation ... */
		emit resultReady(result);
	}
 signals:
	void resultReady(const QString &s);
};

#endif // MAINWINDOW_H
