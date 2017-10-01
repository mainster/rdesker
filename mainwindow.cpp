#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	actRpc1 = new QAction(parent);
	connect(actKnopf, &QAction::triggered, this, &MainWindow::onActKnopf_triggered);
}

MainWindow::~MainWindow() {
	delete ui;
}

/* ======================================================================== */
/*									    Init methodes										    */
/* ======================================================================== */
void MainWindow::createActions() {
	/* ======================================================================== */
	/*                          Create QAction objects                          */
	/* ======================================================================== */
	/*!
	 * Create main toolbar actions.
	 */
	actRpc1 = new QAction(QIcon(":/images/splashScreen.png"), tr("actRpc1"), this);
	actRpc2 = new QAction(QIcon(":/images/search.png"), tr("actRpc2"), this);
	actRpc3 = new QAction(QIcon(":/images/settings.png"), tr("actRpc3"), this);
}
bool MainWindow::restoreActionObjects() {
	QSETTINGS;

	actGrTbMain->blockSignals(true);
	actGrTbMenu->blockSignals(true);
	actGrFilterWidg->blockSignals(true);

	foreach (QAction *a, QList<QAction *>()
				<< actGrTbMain->actions()
				<< actGrTbMenu->actions()
				<< actGrFilterWidg->actions()) {
		if (! config.allKeys().join(',').contains(a->objectName()))
			continue;
		if (config.value(objectName() + tr("/") + a->objectName(), false).toBool()) {
			if (! a->isChecked())
				a->trigger();
		}
	}

	actGrTbMain->blockSignals(false);
	actGrTbMenu->blockSignals(false);
	actGrFilterWidg->blockSignals(false);

	if (! browser->mTabs.hasSelected())
		emit browser->someHasBeenSelected(false);
	return true;

	//	QList<QAction *> acts = findChildren<QAction *>(QRegularExpression("act*"));

	//	foreach (QAction *act, acts)
	//		if (act->objectName().isEmpty())
	//			acts.removeOne(act);
	//	qSort(acts.begin(), acts.end());

	//	foreach (QAction *act, acts) {
	//		if (! config.allKeys().join(',').contains( act->objectName() )) {
	//			WARN << tr("act->objectName() %1 not found!").arg(act->objectName());
	//			continue;
	//		}

	//		bool test = config.value(objectName() + tr("/") + act->objectName()).toBool();
	//		act->setChecked( test );
	//		INFO << act->objectName() << tr("set checked: ") << test;
	//	}
	//	/**** Restore visibility flag for the SQL command interface
	//	\*/
	//	try {
	//		if (!config.value(objectName() + tr("/actShowSqlQuery"), true).toBool()) {
	//			inpFrm->setQueryBoxVisible( true );
	//			actShowSqlQuery->setChecked( false );
	//		}
	//		else {
	//			<->setQueryBoxVisible( false );
	//			actShowSqlQuery->setChecked( true );
	//		}
	//	}
	//	catch (...) {
	//		CRIT << tr("!");
	//	}

	//	/**** Recall dock states
	//	 \*/
	//	if (actInpForm->isChecked()) {
	//		inpFrm->show();
	//		Qt::DockWidgetArea dwa = static_cast<Qt::DockWidgetArea>(
	//											 config.value(inpFrm->objectName() + tr("/DockWidgetArea"),
	//															  Qt::BottomDockWidgetArea).toUInt());
	//		/*!
	//		 * Produces unexpected behavior
	//		 * this->addDockWidget(dwa, inpFrm, Qt::Vertical);
	//		 */
	//		INFO << dwa;
	//	}
	//	else inpFrm->hide();
	//	//		this->addDockWidget(dwa, inpFrm, Qt::Vertical);

	//	return true;
}
void MainWindow::onActKnopf_trigged(bool onOff) {
	QStringList argo, list;
	argo.clear();
	list.clear();

	QProcess process;
	process.start("bash -c \"ls /home/\"");
	process.waitForFinished(-1);
	QByteArray out = process.readAllStandardOutput();
	qDebug() << out;

}

