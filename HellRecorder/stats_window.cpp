#include "stats_window.h"
#include <iostream>

using namespace std;

StatsWindow::StatsWindow(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics) {
	_runs = runs;
	_epics = epics;
	stats = new HellStats(_runs);

	overallLayout = new QVBoxLayout();
	setWindowTitle("Hell Recorder - Statistics");
	setLayout(overallLayout);

	tableLayout = new QHBoxLayout();
	overallLayout->addLayout(tableLayout);

	QStringList categories;
	categories << "Epic" << "Run" << "Mode";

	// Configuring the table that displays data of all hell runs
	
	hellTable = new QTableWidget(this);
	headerview = hellTable->horizontalHeader();
	hellTable->verticalHeader()->setVisible(false);

	hellTable->setColumnCount(3);
	hellTable->setRowCount(stats->getEpics());
	hellTable->setHorizontalHeaderLabels(categories);
	//hellTable->setItem(0, 0, new QTableWidgetItem("Infinity Requiem Plate Amice"));
	//hellTable->horizontalHeader()->setStretchLastSection(true);
	headerview->setResizeMode(QHeaderView::ResizeToContents);
	hellTable->setMinimumWidth(headerview->length() + 6);
	

	/*
	model = new QStandardItemModel(_epics.size(), 3);
	model->setHorizontalHeaderLabels(categories);
	hellTable = new QTreeView(this);
	hellTable->setModel(model);
	headerview = hellTable->header();

	hellTable->setMinimumWidth(headerview->length() + 2);
	headerview->setResizeMode(QHeaderView::Stretch);
	*/
	//qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent);


	tableLayout->addWidget(hellTable);




	// Setting up stats group
	statsLayout = new QVBoxLayout();
	statsBox = new QGroupBox("Statistics");

	tableLayout->addWidget(statsBox);

	numHells = new QLabel();
	numInvites = new QLabel();
	numEyes = new QLabel();
	numOrbs = new QLabel();
	numEpics = new QLabel();
	numHardcore = new QLabel();
	numInsane = new QLabel();

	statsLayout->addWidget(numHells);
	statsLayout->addWidget(numHardcore);
	statsLayout->addWidget(numInsane);
	statsLayout->addWidget(numEpics);
	statsLayout->addWidget(numOrbs);
	statsLayout->addWidget(numEyes);
	statsLayout->addWidget(numInvites);

	statsBox->setLayout(statsLayout);

	updateButton = new QPushButton("Update");
	overallLayout->addWidget(updateButton);

	connect (updateButton, SIGNAL(clicked()), this, SLOT(clickedUpdate()));


}

StatsWindow::~StatsWindow() {
	clearTable();
	delete headerview;
	delete hellTable;
	delete stats;
	delete overallLayout;
}

void StatsWindow::updateWindow() {
	// HellStats has update function, refer to hellstats.h
	stats->update(_runs);

	QString hells = QString::fromStdString("Total # of hell runs: " + intToString(_runs.size()));
	QString hardcores = QString::fromStdString("Hardcore runs: " + intToString(stats->getHardcores()));
	QString insanes = QString::fromStdString("Insane runs: " + intToString(_runs.size() - stats->getHardcores()));
	QString epics = QString::fromStdString("Epics obtained: " + intToString(stats->getEpics()));
	QString eyes = QString::fromStdString("Demon eyes obtained: " + intToString(stats->getEyes()));
	QString orbs = QString::fromStdString("Hell orbs obtained: " + intToString(stats->getOrbs()));
	QString invites = QString::fromStdString("Demon invitations obtained: " + intToString(stats->getInvites()));

	numHells->setText(hells);
	numEyes->setText(eyes);
	numOrbs->setText(orbs);
	numEpics->setText(epics);
	numHardcore->setText(hardcores);
	numInsane->setText(insanes);
	numInvites->setText(invites);

	
	// Updating the QTableWidget (hellTable)
	clearTable();
	hellTable->setRowCount(stats->getEpics());
	int epicIndex = 0;
	int maxEpicNameLength = 0;
	//cout << "BUT we here...." << endl;
	// Important note: _epics contains HellRun* that dropped an epic
	for (int i = 0; i < _epics.size(); i++) {
		ArrayList<string> epicNames = _epics[i]->getEpics();
		epicNames = _epics[i]->getEpics();

		string runNumber = intToString(_epics[i]->getRunNum());

		string difficulty = "";
		if (_epics[i]->getDifficulty()) difficulty = "Insane";
		else difficulty = "Hardcore";

		for (int j = 0; j < epicNames.size(); j++) {
			if (j != 0) epicIndex++;
			if ((signed)epicNames[j].length() > maxEpicNameLength) maxEpicNameLength = epicNames[j].length();
			hellTable->setItem(epicIndex, 0, new QTableWidgetItem(QString::fromStdString(epicNames[j])));
			hellTable->setItem(epicIndex, 1, new QTableWidgetItem(QString::fromStdString(runNumber)));
			hellTable->setItem(epicIndex, 2, new QTableWidgetItem(QString::fromStdString(difficulty)));
		}
		//model->setData(model->index(i, 0), (_epics[i]->getEpics())[j])
		epicIndex++;
	}
	QTimer::singleShot(100, this, SLOT(fixSize()));
}

void StatsWindow::updateRuns(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics) {
	_runs = runs;
	_epics = epics;
}


void StatsWindow::clickedUpdate() {
	updateWindow();
}

void StatsWindow::fixSize() {
	hellTable->setMinimumWidth(headerview->length() + 6);
}

void StatsWindow::clearTable() {
	for (int i = 0; i < hellTable->rowCount(); i++) {
		delete hellTable->item(i, 0);
		delete hellTable->item(i, 1);
		delete hellTable->item(i, 2);
	}
}

/*
QSize StatsWindow::sizeHint(QStandardItemModel* model) {
	int width = 0;

	for (int i = 0; i < model->columnCount(); i++) {
		width += 2 + model->columnWidth(i);
	}
	return QSize(width + 16 - 2, 100);

}
*/