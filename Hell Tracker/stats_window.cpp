#include "stats_window.h"

using namespace std;

StatsWindow::StatsWindow(vector<HellRun*>& runs) {
	_runs = runs;
	stats = new HellStats(_runs);

	overallLayout = new QHBoxLayout();

	// Setting up stats group
	statsLayout = new QVBoxLayout();
	statsBox = new QGroupBox("Statistics");

	overallLayout->addWidget(statsBox);

	QString hells = QString::fromStdString("Total number of hell runs: " + intToString(_runs.size()));
	QString hardcores = QString::fromStdString("Number of hardcore runs: " + intToString(stats->getHardcores()));
	QString insanes = QString::fromStdString("Number of insane runs: " + intToString(_runs.size() - stats->getHardcores()));
	QString epics = QString::fromStdString("Total number of epics obtained: " + intToString(stats->getEpics()));
	QString eyes = QString::fromStdString("Total number of demon eyes obtained: " + intToString(stats->getEyes()));
	QString orbs = QString::fromStdString("Total number of hell orbs obtained: " + intToString(stats->getOrbs()));

	numHells = new QLabel(hells);
	numEyes = new QLabel(eyes);
	numOrbs = new QLabel(orbs);
	numEpics = new QLabel(epics);
	numHardcore = new QLabel(hardcores);
	numInsane = new QLabel(insanes);

	statsLayout->addWidget(numHells);
	statsLayout->addWidget(numHardcore);
	statsLayout->addWidget(numInsane);
	statsLayout->addWidget(numEpics);
	statsLayout->addWidget(numOrbs);
	statsLayout->addWidget(numEyes);

	statsBox->setLayout(statsLayout);

	updateButton = new QPushButton("Update");
	overallLayout->addWidget(updateButton);

	connect (updateButton, SIGNAL(clicked()), this, SLOT(clickedUpdate()));


	setLayout(overallLayout);

}

StatsWindow::~StatsWindow() {

}

void StatsWindow::updateWindow() {
	stats->update(_runs);

	QString hells = QString::fromStdString("Total number of hell runs: " + intToString(_runs.size()));
	QString hardcores = QString::fromStdString("Number of hardcore runs: " + intToString(stats->getHardcores()));
	QString insanes = QString::fromStdString("Number of insane runs: " + intToString(_runs.size() - stats->getHardcores()));
	QString epics = QString::fromStdString("Total number of epics obtained: " + intToString(stats->getEpics()));
	QString eyes = QString::fromStdString("Total number of demon eyes obtained: " + intToString(stats->getEyes()));
	QString orbs = QString::fromStdString("Total number of hell orbs obtained: " + intToString(stats->getOrbs()));

	numHells->setText(hells);
	numEyes->setText(eyes);
	numOrbs->setText(orbs);
	numEpics->setText(epics);
	numHardcore->setText(hardcores);
	numInsane->setText(insanes);
}

void StatsWindow::updateRuns(std::vector<HellRun*>& runs) {
	_runs = runs;
}


void StatsWindow::clickedUpdate() {
	updateWindow();
}