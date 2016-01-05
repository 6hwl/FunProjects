#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "main_window.h"
#include "stats_window.h"
#include "parselog.h"
#include "binsearch.h"

using namespace std;

MainWindow::MainWindow() {

	parse(run_log, epics, "log.txt");
	/*
	cout << run_log[0]->getRunNum() << endl;
	cout << run_log[0]->getDifficulty() << endl;
	cout << run_log[0]->getEyes() << endl;
	cout << run_log[0]->getOrbs() << endl;
	cout << run_log[0]->getEpics().at(0) << endl;
	*/
	

	int prevRun = 0;
	dryStreak = 0;
	// If statement to prevent segfault/accessing bad memory/index
	if (run_log.size() != 0) {
		prevRun = run_log[run_log.size()-1]->getRunNum(); // Get run number from last run of vector
		int index = run_log.size()-1;
		while (index > -1) {
			if (run_log[index]->getDropped())
				break;
			else dryStreak++;
			index--;
		}
	}

	QString currRunNumber = QString::fromStdString(intToString(prevRun + 1));
	QString currDryStreak = QString::fromStdString("Dry Streak: " + intToString(dryStreak));

	currRun = new HellRun(prevRun + 1); // Defaults to next run after previous





	// Set main window's overall layout
	overallLayout = new QVBoxLayout();
	setWindowTitle("Hell Recorder");

	topWidget = new QWidget;
	optionsLayout = new QHBoxLayout(topWidget);
	//topWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	middleWidget = new QWidget;
	optionsLayout2 = new QHBoxLayout(middleWidget);
	//middleWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	bottomWidget = new QWidget;
	buttonLayout = new QVBoxLayout(bottomWidget);
	//bottomWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	overallLayout->addWidget(topWidget);
	overallLayout->addWidget(middleWidget);
	overallLayout->addWidget(bottomWidget);


	// Configuring hell run number options

	hellNumberLayout = new QVBoxLayout();
	runBox = new QGroupBox("Current Run");

	optionsLayout->addWidget(runBox);

	hellNumberLabel = new QLabel("Current Hell Run:");
	hellNumberInput = new QLineEdit(currRunNumber);
	hellNumberInput->setMaximumWidth(80);
	hellNumberInput->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	hellNumberLayout->addWidget(hellNumberInput, 0, Qt::AlignTop);

	dryStreakLabel = new QLabel(currDryStreak);
	hellNumberLayout->addWidget(dryStreakLabel, 0, Qt::AlignTop);

	runBox->setLayout(hellNumberLayout);


	// Configuring insane/hardcore options

	difficultyLayout = new QVBoxLayout();
	difficultyBox = new QGroupBox("Difficulty");

	optionsLayout->addWidget(difficultyBox);

	hardcore = new QRadioButton("Hardcore");
	insane  = new QRadioButton("Insane");

	hardcore->setChecked(true);

	difficultyLayout->addWidget(hardcore, 0, Qt::AlignTop);
	difficultyLayout->addWidget(insane, 0, Qt::AlignTop);

	difficultyBox->setLayout(difficultyLayout);


	// Configuring QComboBox lists
	QStringList numberList;
	numberList << "0" << "1" << "2" << "3" << "4" << "5";
	QFont myFont;
	QFontMetrics fontmetric(myFont);
	//int pixelWidth = fontmetric.width("5");

	// Configuring demon invites dropped options (post-All in One patch)
	invitesLayout = new QVBoxLayout();
	invitesBox = new QGroupBox("Demon Invitations");

	optionsLayout->addWidget(invitesBox);

	invitesList = new QComboBox();
	invitesList->addItems(numberList); // numberList defined in demon eye section
	invitesList->setMaximumWidth(45);
	invitesList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	invitesLayout->addWidget(invitesList, 0, Qt::AlignTop);
	invitesBox->setLayout(invitesLayout);

	

	// Configuring demon eye options
	eyeBox = new QGroupBox("Demon Eyes");
	eyeLayout = new QVBoxLayout();

	optionsLayout->addWidget(eyeBox);

	eyeList = new QComboBox();
	eyeList->addItems(numberList);
	eyeList->setMaximumWidth(45);

	eyeLayout->addWidget(eyeList, 0, Qt::AlignTop);
	eyeBox->setLayout(eyeLayout);


	// Configuring hell orb options
	
	orbBox = new QGroupBox("Hell Orbs");
	orbLayout = new QVBoxLayout();

	optionsLayout2->addWidget(orbBox);

	orbList = new QComboBox();
	orbList->addItems(numberList); // numberList defined when doing demon eye options
	orbList->setMaximumWidth(45);
	orbList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	orbLayout->addWidget(orbList, 0, Qt::AlignTop);

	orbBox->setLayout(orbLayout);


	// Configuring got epic/no epic options

	epicLayout = new QVBoxLayout();
	epicBox = new QGroupBox("Number of Epics");

	optionsLayout2->addWidget(epicBox);

	numEpicsList = new QComboBox();
	numEpicsList->addItems(numberList); // numberList defined in demon eye section
	numEpicsList->setMaximumWidth(45);
	//numEpicsList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	epicInputLabel = new QLabel("Enter epic name:");
	epicNameInput = new QLineEdit();
	epicNameInput2 = new QLineEdit();
	epicNameInput3 = new QLineEdit();
	epicNameInput4 = new QLineEdit();
	epicNameInput5 = new QLineEdit();

	epicInputLabel->setEnabled(false);
	epicNameInput->setEnabled(false);
	epicNameInput2->hide();
	epicNameInput3->hide();
	epicNameInput4->hide();
	epicNameInput5->hide();

	epicLayout->addWidget(numEpicsList);
	epicLayout->addWidget(epicInputLabel);
	epicLayout->addWidget(epicNameInput);
	epicLayout->addWidget(epicNameInput2);
	epicLayout->addWidget(epicNameInput3);
	epicLayout->addWidget(epicNameInput4);
	epicLayout->addWidget(epicNameInput5);


	connect(numEpicsList, SIGNAL(activated(QString)), this, SLOT(clickedEpic(QString)), Qt::UniqueConnection);

	epicBox->setLayout(epicLayout);


	// Add and stats options
	addRun = new QPushButton("Add Run");

	buttonLayout->addWidget(addRun);

	connect(addRun, SIGNAL(clicked()), this, SLOT(clickedAdd()), Qt::UniqueConnection);



	// Configuring hell statistics
	statsWindow = new StatsWindow(run_log, epics);
	statistics = new QPushButton("Statistics");
	buttonLayout->addWidget(statistics);

	connect(statistics, SIGNAL(clicked()), this, SLOT(clickedStats()));


	// Configuring quit button
	quitButton = new QPushButton("Quit");
	buttonLayout->addWidget(quitButton);

	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));




	// Error windows for invalid hell information
	invalidRun = new QMessageBox();
	invalidNumber = new QMessageBox();
	dupeRunNumber = new QMessageBox();

	invalidRun->setWindowTitle("ERROR");
	invalidRun->setText("Please enter a number");

	invalidNumber->setWindowTitle("ERROR");
	invalidNumber->setText("Invalid number");

	dupeRunNumber->setWindowTitle("ERROR");


	setLayout(overallLayout);

}

MainWindow::~MainWindow() {
	
	for (int i = 0; i < run_log.size(); i++) {
		delete run_log[i];
	}
	
	delete invalidRun;
	delete invalidNumber;
	delete dupeRunNumber;
	delete currRun;
	delete statsWindow;
	delete optionsLayout;
	delete topWidget;
	delete optionsLayout2;
	delete middleWidget;
	delete buttonLayout;
	delete bottomWidget;
	delete overallLayout;
}

ArrayList<HellRun*>& MainWindow::getRuns() {
	return run_log;
}



void MainWindow::clickedEpic(QString text) {
	if (text == "1") {
		epicInputLabel->setEnabled(true);
		epicNameInput->setEnabled(true);
		epicNameInput2->hide();
		epicNameInput3->hide();
		epicNameInput4->hide();
		epicNameInput5->hide();
	} else if (text == "2") {
		epicInputLabel->setEnabled(true);
		epicNameInput->setEnabled(true);
		epicNameInput2->show();
		epicNameInput3->hide();
		epicNameInput4->hide();
		epicNameInput5->hide();
	} else if (text == "3") {
		epicInputLabel->setEnabled(true);
		epicNameInput->setEnabled(true);
		epicNameInput2->show();
		epicNameInput3->show();
		epicNameInput4->hide();
		epicNameInput5->hide();
	} else if (text == "4") {
		epicInputLabel->setEnabled(true);
		epicNameInput->setEnabled(true);
		epicNameInput2->show();
		epicNameInput3->show();
		epicNameInput4->show();
		epicNameInput5->hide();
	} else if (text == "5") {
		epicInputLabel->setEnabled(true);
		epicNameInput->setEnabled(true);
		epicNameInput2->show();
		epicNameInput3->show();
		epicNameInput4->show();
		epicNameInput5->show();
	} else {
		epicInputLabel->setEnabled(false);
		epicNameInput->setEnabled(false);
		epicNameInput2->hide();
		epicNameInput3->hide();
		epicNameInput4->hide();
		epicNameInput5->hide();
	}
	QTimer::singleShot(100, this, SLOT(fixSize()));
	
}

void MainWindow::fixSize() {
	resize(sizeHint());
}


void MainWindow::clickedAdd() {
	string input = hellNumberInput->text().toStdString();
	if (input == "") {
		invalidRun->exec();
	} else if (!isNumber(input) || input == "0") {
		invalidNumber->exec();
	} else {
		// Update the current hell run and push_back in runs vector
		istringstream toInt(input);
		int runNumber;
		toInt >> runNumber;

		if (binarySearch(run_log, 0, run_log.size() - 1, runNumber) != -1) {
			QString text = QString::fromStdString("Run #" + input + " already exists");
			dupeRunNumber->setText(text);
			dupeRunNumber->exec();
		} else {
			currRun->setRunNum(runNumber);

			if (insane->isChecked())
				currRun->setDifficulty(true);

			currRun->setEyes(atoi(eyeList->currentText().toStdString().c_str()));
			currRun->setOrbs(atoi(orbList->currentText().toStdString().c_str()));
			currRun->setInvites(atoi(invitesList->currentText().toStdString().c_str()));

			string numEpics = numEpicsList->currentText().toStdString();
			string epicInput = epicNameInput->text().toStdString();
			string epicInput2 = epicNameInput2->text().toStdString();
			string epicInput3 = epicNameInput3->text().toStdString();
			string epicInput4 = epicNameInput4->text().toStdString();
			string epicInput5 = epicNameInput5->text().toStdString();

			if (numEpics == "1") {
				if (isValid(epicInput)) currRun->addEpic(epicInput);
			} else if (numEpics == "2") {
				if (isValid(epicInput)) currRun->addEpic(epicInput);
				if (isValid(epicInput2)) currRun->addEpic(epicInput2);
			} else if (numEpics == "3") {
				if (isValid(epicInput)) currRun->addEpic(epicInput);
				if (isValid(epicInput2)) currRun->addEpic(epicInput2);
				if (isValid(epicInput3)) currRun->addEpic(epicInput3);
			} else if (numEpics == "4") {
				if (isValid(epicInput)) currRun->addEpic(epicInput);
				if (isValid(epicInput2)) currRun->addEpic(epicInput2);
				if (isValid(epicInput3)) currRun->addEpic(epicInput3);
				if (isValid(epicInput4)) currRun->addEpic(epicInput4);
			} else if (numEpics == "5") {
				if (isValid(epicInput)) currRun->addEpic(epicInput);
				if (isValid(epicInput2)) currRun->addEpic(epicInput2);
				if (isValid(epicInput3)) currRun->addEpic(epicInput3);
				if (isValid(epicInput4)) currRun->addEpic(epicInput4);
				if (isValid(epicInput5))currRun->addEpic(epicInput5);
			}

			if (currRun->getEpics().size() > 0)
				currRun->setDropped(true);


			// If the current run dropped an epic, add to epics vector

			if (currRun->getDropped()) {
				epics.insert(epics.size(), currRun);
				dryStreak = 0;
			} else {
				dryStreak++;
			}

			bool inMiddle = true;
			// If run number is less than the last element's, insert in the middle
			// Will throw exception if getRunNum done when run_log is empty, thus the first if here
			if (run_log.size() != 0) {
				if (runNumber < run_log[run_log.size()-1]->getRunNum()) {
					int index = getInsertionIndex(run_log, 0, run_log.size()-1, runNumber);
					cout << index << endl;
					run_log.insert(index, currRun);
				} else {
					inMiddle = false;
				}
			}

			// Accommodating for the case that run_log is empty (initially),
			// or if the run number of the current run is greater than the current last
			if (inMiddle == false || run_log.size() == 0) {
				run_log.insert(run_log.size(), currRun);
			}

			// To let the user know which run was just added
			string newTitle = "Hell Recorder - " + input + ordIndicator(input) + " run added!";
			setWindowTitle(QString::fromStdString(newTitle));
			// Output data
			output(run_log, "log.txt");

			// Update statsWindow _runs and _epics containers
			statsWindow->updateRuns(run_log, epics);

			// Updating information and fields to be able to add a new hell run
			currRun = new HellRun(runNumber + 1);
			hellNumberInput->setText(QString::fromStdString(intToString(runNumber + 1)));
			dryStreakLabel->setText(QString::fromStdString("Dry streak: " + intToString(dryStreak)));
			epicNameInput->setText("");
			epicNameInput2->setText("");
			epicNameInput3->setText("");
			epicNameInput4->setText("");
			epicNameInput5->setText("");

			epicNameInput->setEnabled(false);
			epicNameInput2->hide();
			epicNameInput3->hide();
			epicNameInput4->hide();
			epicNameInput5->hide();

			numEpicsList->setCurrentIndex(0);
			eyeList->setCurrentIndex(0);
			orbList->setCurrentIndex(0);
			invitesList->setCurrentIndex(0);

			QTimer::singleShot(100, this, SLOT(fixSize()));
		}
	}
}


void MainWindow::clickedStats() {
	statsWindow->updateRuns(run_log, epics);
	statsWindow->updateWindow();
	statsWindow->show();
}



