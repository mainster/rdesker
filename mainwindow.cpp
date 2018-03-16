#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdbQtStd/globals.h"

QDataStream &operator<<(QDataStream &out, const Credential &c) {
	out << c.mDomain << c.mSep
		 << c.mUser << c.mSep
		 << c.mPass;
	return out;
}
QDataStream &operator>>(QDataStream &in, Credential &c) {
	in		>> c.mDomain >> c.mSep
			>> c.mUser >> c.mSep
			>> c.mPass;
	return in;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	qRegisterMetaType<Credential>("Credential");
	qRegisterMetaTypeStreamOperators<Credential>("Credential");

	QSETTINGS_INIT
	QSETTINGS;

//	Credential cr = Credential(tr("DEL-BdASSO"), tr("vitddiano"), tr("chefo"));
//	QVariant var;
//	var.fromValue(cr);

	cred = Credential(tr("DEL-BASSO"), tr("vitaliano"), tr("chefe"));
	createLists();
	createActions();

	ui->actWOL->setDisabled(true);
	ui->actConnect->setDisabled(true);

	connectSlots();
}
MainWindow::~MainWindow() {
	delete ui;
}

/* ======================================================================== */
/*									    Init methodes										    */
/* ======================================================================== */
void MainWindow::createLists() {
	QSETTINGS

	QStringList clients = QStringList()
								 << tr("SBS2011:3389")
								 << tr("PC-Vitaliano:6389")
								 << tr("PC-Mitarbeiter:5389")
								 << tr("PC-Karin:7389")
								 << tr("NB-Werkstatt-2:4389")
								 << tr("NB-Meister")
								 << tr("PC-Buchhaltung");

	QList<Credential> credentials = QList<Credential>()
											  << Credential(tr("DEL-BASSO"), tr("vitaliano"), tr("chefe"))
											  << Credential(tr("DEL-BASSO"), tr("karin"), tr("cleohundi290409"))
											  << Credential(tr("DEL-BASSO"), tr("torsten"), tr("torsten"))
											  << Credential(tr("DEL-BASSO"), tr("manuel"), tr("Themegrepper09||@!"))
											  << Credential(tr("DEL-BASSO"), tr("admin"), tr("#delB@550#!"))
											  << Credential(tr("DEL-BASSO"), tr("mitarbeiter"), tr("mitarbiter"));

	ui->listClient->insertItems(0, clients);

	foreach (Credential c, credentials)
		ui->listCreds->addItem(c.getDomUserPass('\t'));

	return;

	config.beginWriteArray("clients");
	for (int i = 0; i < clients.size(); ++i) {
		 config.setArrayIndex(i);
		 config.setValue(tr("client"),clients.at(i));
	}
	config.endArray();

	int i = 0;
	config.beginWriteArray("clients");
	foreach (Credential c, credentials) {
		config.setArrayIndex(i++);
		config.setValue(tr("credent"), c.getDomUserPass('\t'));
	}
	config.endArray();


	QVariant var = config.value("credentials");
	Credential cr;

	if (var.isValid()) {
		cr = var.value<Credential>();
		INFO << cr.mDomain << cr.mUser
			  << cr.mPass << cr.mSep;
	}
	else {
		cr = Credential(tr("DEL-BdASSO"), tr("vitddiano"), tr("chefo"));
		config.setValue("credentials",  qVariantFromValue(cr));
	}

	config.sync();



//	config.beginWriteArray("credentials");
//	for (int i = 0; i < credentials.size(); ++i) {
//		config.setArrayIndex(i);
//		QVariant var;
//		var.setValue(credentials.at(i));
//		config.setValue(tr("credent"), var);
//	}
//	config.endArray();




	return;




	config.beginWriteArray("clarray");
	foreach (Credential c, credentials) {
		config.setArrayIndex(i++);
//		config.setValue(tr("Credential"), QVariant::fromValue(c));
	}
	config.endArray();


}
void MainWindow::clearList() {
	INFO << "void ListWidgetTest::clearList()";
	ui->listClient->clear();
	INFO << "clearList: ui->listWidget->count() is " << ui->listClient->count();
}
void MainWindow::onSelectionChanged() {
	bool state = false;

	(ui->listClient->selectedItems().length() *
	 ui->listCreds->selectedItems().length() > 0) ?
	state = true : state = false;

	ui->actWOL->setEnabled(state);
	ui->actConnect->setEnabled(state);
}
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


	/* ======================================================================== */
	/*                             Action grouping                              */
	/* ======================================================================== */
	/*!
	 * Create action group for main toolbar actions.
	 */
	actGrp = new QActionGroup(this);
	PONAM(actGrp)->setExclusive(false);

	QList<QAction *> acts;
	acts << PONAM(actRpc1) << PONAM(actRpc2) << PONAM(actRpc3);


	//	foreach (QAction *act, acts)
	//		actGrTbMain->addAction(act);

	/*!
	 * Connect action group triggered signal to a save-action-state slot.
	 */
	//	connect(actGrTbMain, &QActionGroup::triggered, this, &MainWindow::onActionGroupTrigd);

}
void MainWindow::onActConnectTriggered(bool trigged) {
	Q_UNUSED(trigged);
	bool ok;

	QString command = "rdesktop";
	QString targetIP = tr("remote.del-basso.de");
	int targetPort =
		ui->listClient->selectedItems()[0]->text().split(':').last().toInt(&ok);

	Credential cred = Credential(ui->listCreds->selectedItems()[0]->text(), '\t');
	QStringList args = QStringList()
							 << tr("-d%1").arg(cred.getDom())
							 << tr("-u%1").arg(cred.getUser())
							 << tr("-p%1").arg(cred.getPass())
							 << tr("-g1280x768")
							 << tr("-a16")
							 << tr("-kde");
//							 << tr("-z");

	if (ok)
		args << tr("%1:%2").arg(targetIP).arg(targetPort);
	else
		args << tr("%1").arg(targetIP);

	INFO << tr("%1 %2").arg(command).arg(args.join(" "));

//	QThread

	QProcess process;
	process.start(command, args);
	process.waitForFinished(-1);

//	process.waitForStarted(2000);

//	if (process.exitCode() != 0) {
//		INFO << " Error " << process.exitCode() << process.readAllStandardError();
//	} else {
//		INFO << " Ok " << process.readAllStandardError()
//			  << process.readAllStandardError()
//			  << process.readAll();
//	}
}
void MainWindow::onActionGroupTrigd(QAction *sender) {
	QSETTINGS;

	if (sender->isCheckable()) {
		/*!
		 * If action group is exclusive, clear all action config flags.
		 */
		if (sender->actionGroup()->isExclusive())
			foreach (QAction *act, sender->actionGroup()->actions())
				config.setValue(objectName() + tr("/") + act->objectName(), false);

		config.setValue(objectName() + tr("/") + sender->objectName(),
							 sender->isChecked());
		config.sync();
	}
}
void MainWindow::onActTry(bool triiggd) {
	Q_UNUSED(triiggd)
}
void MainWindow::connectSlots() {
	QObject::connect(ui->listClient, &QListWidget::itemSelectionChanged,
						  this, &MainWindow::onSelectionChanged);
	QObject::connect(ui->actConnect, &QAction::triggered,
						  this, &MainWindow::onActConnectTriggered);
	QObject::connect(ui->actTry, &QAction::triggered,
						  this, &MainWindow::onActTry);
}
bool MainWindow::restoreActionObjects() {
	QSETTINGS;

	actGrTbMain->blockSignals(true);
	actGrTbMenu->blockSignals(true);
	//	actGrFilterWidg->blockSignals(true);

	foreach (QAction *a, QList<QAction *>()
				<< actGrTbMain->actions()
				<< actGrTbMenu->actions()
				/*	<< actGrFilterWidg->actions()*/) {
		if (! config.allKeys().join(',').contains(a->objectName()))
			continue;

		if (config.value(objectName() + tr("/") + a->objectName(), false).toBool()) {
			if (! a->isChecked())
				a->trigger();
		}
	}

	actGrTbMain->blockSignals(false);
	actGrTbMenu->blockSignals(false);
	return true;
	//	actGrFilterWidg->blockSignals(false);

	//	if (! browser->mTabs.hasSelected())
	//		emit browser->someHasBeenSelected(false);
	//	return true;

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

