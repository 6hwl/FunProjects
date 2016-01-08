#include "stats_window.h"
#include <iostream>

using namespace std;

StatsWindow::StatsWindow(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics) {
	_runs = runs;
	_epics = epics;
	updateEpics();
	stats = new HellStats(_runs);

	overallLayout = new QVBoxLayout();
	setWindowTitle("Hell Recorder - Statistics");
	setLayout(overallLayout);


	QStringList categories;
	categories << "Run" << "Mode" << "Epic";

	// Configuring the table that displays data of all hell runs
	
	hellTable = new QTableWidget(this);
	headerview = hellTable->horizontalHeader();
	hellTable->verticalHeader()->setVisible(false);

	hellTable->setColumnCount(3);
	hellTable->setRowCount(stats->getEpics());
	hellTable->setHorizontalHeaderLabels(categories);
	headerview->setResizeMode(QHeaderView::ResizeToContents);
	headerview->setStretchLastSection(true);

	hellTable->setMinimumHeight(250);

	overallLayout->addWidget(hellTable);


	// Setting up sorting options for the epics listed in the table...

	// Hardcore/Insane filtering
	middleLayout = new QHBoxLayout();
	overallLayout->addLayout(middleLayout);

	difficultyLayout = new QVBoxLayout();
	difficultyBox = new QGroupBox("Difficulty Options");
	middleLayout->addWidget(difficultyBox);
	difficultyBox->setLayout(difficultyLayout);

	allButton = new QRadioButton("All epics");
	hardcoreButton = new QRadioButton("Hardcore epics");
	insaneButton = new QRadioButton("Insane epics");

	allButton->setChecked(true);

	connect(allButton, SIGNAL(clicked()), this, SLOT(clickedAll()));
	connect(hardcoreButton, SIGNAL(clicked()), this, SLOT(clickedHardcore()));
	connect(insaneButton, SIGNAL(clicked()), this, SLOT(clickedInsane()));

	difficultyLayout->addWidget(allButton);
	difficultyLayout->addWidget(hardcoreButton);
	difficultyLayout->addWidget(insaneButton);

	// Epic run/name sorting options
	sortLayout = new QVBoxLayout();
	sortBox = new QGroupBox("Sorting Options");
	middleLayout->addWidget(sortBox);
	sortBox->setLayout(sortLayout);

	byRunButton = new QRadioButton("By run");
	byNameButton = new QRadioButton("By name");

	byRunButton->setChecked(true);

	connect(byRunButton, SIGNAL(clicked()), this, SLOT(clickedRun()));
	connect(byNameButton, SIGNAL(clicked()), this, SLOT(clickedName()));

	sortLayout->addWidget(byRunButton);
	sortLayout->addWidget(byNameButton);



	bottomLayout = new QHBoxLayout();
	overallLayout->addLayout(bottomLayout);


	// Setting up general stats group
	generalStatsLayout = new QVBoxLayout();
	generalStatsBox = new QGroupBox();
	generalStatsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	bottomLayout->addWidget(generalStatsBox);

	numHells = new QLabel();
	numHardcore = new QLabel();
	numInsane = new QLabel();

	generalStatsLayout->addWidget(numHells);
	generalStatsLayout->addWidget(numHardcore);
	generalStatsLayout->addWidget(numInsane);

	generalStatsBox->setLayout(generalStatsLayout);


	// Epic stats box
	epicStatsLayout = new QVBoxLayout();
	epicStatsBox = new QGroupBox();
	epicStatsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	bottomLayout->addWidget(epicStatsBox);

	numEpics = new QLabel();
	hardcoreEpics = new QLabel();
	insaneEpics = new QLabel();

	epicStatsLayout->addWidget(numEpics);
	epicStatsLayout->addWidget(hardcoreEpics);
	epicStatsLayout->addWidget(insaneEpics);

	epicStatsBox->setLayout(epicStatsLayout);

	// Other stats box
	otherStatsLayout = new QVBoxLayout();
	otherStatsBox = new QGroupBox();
	otherStatsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	bottomLayout->addWidget(otherStatsBox);

	numInvites = new QLabel();
	numEyes = new QLabel();
	numOrbs = new QLabel();

	otherStatsLayout->addWidget(numInvites);
	otherStatsLayout->addWidget(numEyes);
	otherStatsLayout->addWidget(numOrbs);

	otherStatsBox->setLayout(otherStatsLayout);


	// Update button
	updateButton = new QPushButton("Update Table");
	overallLayout->addWidget(updateButton);

	connect(updateButton, SIGNAL(clicked()), this, SLOT(clickedUpdate()));

	// Close button
	closeButton = new QPushButton("Close");
	overallLayout->addWidget(closeButton);

	connect(closeButton, SIGNAL(clicked()), this, SLOT(clickedClose()));



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

	int totalEpics = stats->getEpics();
	int hardcoreEpics_counter = stats->getHardcoreEpics();
	QString epics = QString::fromStdString("Total # of epics: " + intToString(totalEpics));
	QString hardcoreEpics = QString::fromStdString("Epics from hardcore: " + intToString(hardcoreEpics_counter));
	QString insaneEpics = QString::fromStdString("Epics from insane: " + intToString(totalEpics - hardcoreEpics_counter));

	QString eyes = QString::fromStdString("Demon eyes obtained: " + intToString(stats->getEyes()));
	QString orbs = QString::fromStdString("Hell orbs obtained: " + intToString(stats->getOrbs()));
	QString invites = QString::fromStdString("Demon invitations obtained: " + intToString(stats->getInvites()));

	numHells->setText(hells);
	numHardcore->setText(hardcores);
	numInsane->setText(insanes);

	numEpics->setText(epics);
	this->hardcoreEpics->setText(hardcoreEpics);
	this->insaneEpics->setText(insaneEpics);

	numEyes->setText(eyes);
	numOrbs->setText(orbs);
	numInvites->setText(invites);

	
	// Updating the QTableWidget (hellTable)
	clearTable();
	updateEpics();

	if (byRunButton->isChecked())
		clickedRun();
	else
		clickedName();

}

void StatsWindow::updateRuns(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics) {
	_runs = runs;
	_epics = epics;
	updateEpics();
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

void StatsWindow::removeEdit() {
	for (int i = 0; i < hellTable->rowCount(); i++) {
		hellTable->item(i, 0)->setFlags(hellTable->item(i, 0)->flags() ^ Qt::ItemIsEditable);
		hellTable->item(i, 1)->setFlags(hellTable->item(i, 1)->flags() ^ Qt::ItemIsEditable);
		hellTable->item(i, 2)->setFlags(hellTable->item(i, 2)->flags() ^ Qt::ItemIsEditable);
	}
}

void StatsWindow::updateEpics() {
	epic_container.clear();
	for (int i = 0; i < _epics.size(); i++) {
		ArrayList<string> epics = _epics[i]->getEpics();
		for (int j = 0; j < epics.size(); j++) {
			Epic epic;
			epic.runNumber = _epics[i]->getRunNum();
			epic.name = epics[j];
			epic.difficulty = _epics[i]->getDifficulty();
			epic_container.insert(epic_container.size(), epic);
		}
	}
}


void StatsWindow::insertAll() {
	for (int i = 0; i < epic_container.size(); i++) {
		Epic epic = epic_container[i];
		string difficulty = "";
		if (epic.difficulty == false) difficulty = "Hardcore";
		else difficulty = "Insane";

		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(intToString(epic.runNumber)));
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		hellTable->setItem(i, 0, item);

		item = new QTableWidgetItem(QString::fromStdString(difficulty));
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		hellTable->setItem(i, 1, item);

		item = new QTableWidgetItem(QString::fromStdString(epic.name));
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		hellTable->setItem(i, 2, item);
	}
}

void StatsWindow::insertHardcore() {
	int tableIndex = 0;
	for (int i = 0; i < epic_container.size(); i++) {
		Epic epic = epic_container[i];
		string difficulty = "";
		if (epic.difficulty == false) { // false indicates hardcore
			QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(intToString(epic.runNumber)));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 0, item);

			item = new QTableWidgetItem(QString::fromStdString("Hardcore"));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 1, item);

			item = new QTableWidgetItem(QString::fromStdString(epic.name));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 2, item);

			tableIndex++;
		}
	}
}

void StatsWindow::insertInsane() {
	int tableIndex = 0;
	for (int i = 0; i < epic_container.size(); i++) {
		Epic epic = epic_container[i];
		string difficulty = "";
		if (epic.difficulty == true) { // true indicates insane
			QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(intToString(epic.runNumber)));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 0, item);

			item = new QTableWidgetItem(QString::fromStdString("Insane"));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 1, item);

			item = new QTableWidgetItem(QString::fromStdString(epic.name));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			hellTable->setItem(tableIndex, 2, item);

			tableIndex++;
		}
	}
}


void StatsWindow::clickedAll() {
	clearTable();
	hellTable->setRowCount(stats->getEpics());
	insertAll();
}

void StatsWindow::clickedHardcore() {
	clearTable();
	hellTable->setRowCount(stats->getHardcoreEpics());
	insertHardcore();
}

void StatsWindow::clickedInsane() {
	clearTable();
	hellTable->setRowCount(stats->getEpics() - stats->getHardcoreEpics());
	insertInsane();
}

void StatsWindow::clickedRun() {
	numCompare comparator;
	mergeSort(epic_container, comparator);
	
	if (allButton->isChecked())
		clickedAll();
	else if (hardcoreButton->isChecked())
		clickedHardcore();
	else
		clickedInsane();
}

void StatsWindow::clickedName() {
	strCompare comparator;
	mergeSort(epic_container, comparator);
	
	if (allButton->isChecked())
		clickedAll();
	else if (hardcoreButton->isChecked())
		clickedHardcore();
	else
		clickedInsane();
}


void StatsWindow::clickedClose() {
	this->hide();
}