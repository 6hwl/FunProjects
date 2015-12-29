#include "stats_window.h"

using namespace std;

StatsWindow::StatsWindow(ArrayList<HellRun*>& runs) {
	_runs = runs;
	stats = new HellStats(_runs);

	overallLayout = new QHBoxLayout();
	setWindowTitle("Hell Recorder - Statistics");

	// Setting up stats group
	statsLayout = new QVBoxLayout();
	statsBox = new QGroupBox("Statistics");

	overallLayout->addWidget(statsBox);

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


	setLayout(overallLayout);

}

StatsWindow::~StatsWindow() {
	delete stats;
	delete overallLayout;
}

void StatsWindow::updateWindow() {
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
}

void StatsWindow::updateRuns(ArrayList<HellRun*>& runs) {
	_runs = runs;
}


void StatsWindow::clickedUpdate() {
	updateWindow();
}