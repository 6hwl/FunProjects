#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "main_window.h"
#include "stats_window.h"
#include "parselog.h"

using namespace std;

MainWindow::MainWindow() {

	parse(run_log, "log.txt");
	/*
	cout << run_log[0]->getRunNum() << endl;
	cout << run_log[0]->getDifficulty() << endl;
	cout << run_log[0]->getEyes() << endl;
	cout << run_log[0]->getOrbs() << endl;
	cout << run_log[0]->getEpics().at(0) << endl;
	*/
	

	int prevRun = 0;
	// If statement to prevent segfault/accessing bad memory/index
	if (run_log.size() != 0)
		prevRun = run_log[run_log.size()-1]->getRunNum(); // Get run number from last run of vector

	QString result = QString::fromStdString(intToString(prevRun + 1));

	currRun = new HellRun(prevRun + 1); // Defaults to next run after previous

	//cout << run_log.size() << " was the number of hells" << endl;


	// Set main window's overall layout
	overallLayout = new QVBoxLayout();
	setWindowTitle("Hell Recorder");

	topWidget = new QWidget;
	optionsLayout = new QHBoxLayout(topWidget);
	//topWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

	middleWidget = new QWidget;
	optionsLayout2 = new QVBoxLayout(middleWidget);
	//middleWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

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
	hellNumberInput = new QLineEdit(result);
	hellNumberInput->setMaximumWidth(80);
	hellNumberInput->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	//hellNumberLayout->addWidget(hellNumberLabel);
	hellNumberLayout->addWidget(hellNumberInput);

	runBox->setLayout(hellNumberLayout);


	// Configuring insane/hardcore options

	difficultyLayout = new QVBoxLayout();
	difficultyBox = new QGroupBox("Difficulty");

	optionsLayout->addWidget(difficultyBox);

	hardcore = new QRadioButton("Hardcore");
	insane  = new QRadioButton("Insane");

	hardcore->setChecked(true);

	difficultyLayout->addWidget(hardcore);
	difficultyLayout->addWidget(insane);

	difficultyBox->setLayout(difficultyLayout);


	// Configuring demon eye options
	QStringList numberList;
	numberList << "0" << "1" << "2" << "3" << "4" << "5";
	QFont myFont;
	QFontMetrics fontmetric(myFont);
	//int pixelWidth = fontmetric.width("5");

	eyeBox = new QGroupBox("Demon Eyes");
	eyeLayout = new QVBoxLayout();

	optionsLayout->addWidget(eyeBox);

	eyeList = new QComboBox();
	eyeList->addItems(numberList);
	eyeList->setMaximumWidth(45);
	//eyeList->resize(0, 1);
	//eyeList->setStyleSheet("padding: 0");
	//eyeList->view()->setMinimumWidth(1);
	eyeLayout->addWidget(eyeList);

	eyeBox->setLayout(eyeLayout);


	// Configuring hell orb options
	
	orbBox = new QGroupBox("Hell Orbs");
	orbLayout = new QVBoxLayout();

	optionsLayout->addWidget(orbBox);

	orbList = new QComboBox();
	orbList->addItems(numberList); // numberList defined when doing demon eye options
	orbList->setMaximumWidth(45);
	orbList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	//orbList->resize(0, 1);
	//orbList->setStyleSheet("padding: 0");
	//orbList->view()->setMinimumWidth(1);
	orbLayout->addWidget(orbList);

	orbBox->setLayout(orbLayout);
	



	// Configuring got epic/no epic options

	epicLayout = new QVBoxLayout();
	epicBox = new QGroupBox("Number of Epics");

	optionsLayout2->addWidget(epicBox);

	numEpicsList = new QComboBox();
	numEpicsList->addItems(numberList);
	numEpicsList->setMaximumWidth(45);
	eyeList->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

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


	// Error windows for invalid hell information
	invalidRun = new QMessageBox();
	invalidNumber = new QMessageBox();

	invalidRun->setWindowTitle("ERROR");
	invalidRun->setText("Please enter a number");
	invalidNumber->setWindowTitle("ERROR");
	invalidNumber->setText("Invalid number");


	// Configuring hell statistics
	statsWindow = new StatsWindow(run_log);
	statistics = new QPushButton("Statistics");
	buttonLayout->addWidget(statistics);

	connect(statistics, SIGNAL(clicked()), this, SLOT(clickedStats()));


	// Configuring quit button
	quitButton = new QPushButton("Quit");
	buttonLayout->addWidget(quitButton);

	connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));


	setLayout(overallLayout);

}

MainWindow::~MainWindow() {}

vector<HellRun*>& MainWindow::getRuns() {
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
		currRun->setRunNum(runNumber);

		if (insane->isChecked())
			currRun->setDifficulty(true);

		currRun->setEyes(atoi(eyeList->currentText().toStdString().c_str()));
		currRun->setOrbs(atoi(orbList->currentText().toStdString().c_str()));

		string numEpics = numEpicsList->currentText().toStdString();
		string epicInput = epicNameInput->text().toStdString();
		string epicInput2 = epicNameInput2->text().toStdString();
		string epicInput3 = epicNameInput3->text().toStdString();
		string epicInput4 = epicNameInput4->text().toStdString();
		string epicInput5 = epicNameInput5->text().toStdString();

		if (numEpics != "0")
			currRun->setDropped(true);
		if (numEpics == "1") {
			currRun->addEpic(epicInput);
		} else if (numEpics == "2") {
			currRun->addEpic(epicInput);
			currRun->addEpic(epicInput2);
		} else if (numEpics == "3") {
			currRun->addEpic(epicInput);
			currRun->addEpic(epicInput2);
			currRun->addEpic(epicInput3);
		} else if (numEpics == "4") {
			currRun->addEpic(epicInput);
			currRun->addEpic(epicInput2);
			currRun->addEpic(epicInput3);
			currRun->addEpic(epicInput4);
		} else if (numEpics == "5") {
			currRun->addEpic(epicInput);
			currRun->addEpic(epicInput2);
			currRun->addEpic(epicInput3);
			currRun->addEpic(epicInput4);
			currRun->addEpic(epicInput5);
		}

		run_log.push_back(currRun);

		// To let the user know which run was just added
		string newTitle = "Hell Recorder - " + input + ordIndicator(input) + " run added!";
		setWindowTitle(QString::fromStdString(newTitle));
		// Output data
		output(run_log, "log.txt");
		// Update statsWindow run_log container
		statsWindow->updateRuns(run_log);

		// Updating information and fields to be able to add a new hell run
		currRun = new HellRun(runNumber + 1);
		hellNumberInput->setText(QString::fromStdString(intToString(runNumber + 1)));
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

		QTimer::singleShot(100, this, SLOT(fixSize()));



	}
}


void MainWindow::clickedStats() {
	statsWindow->updateRuns(run_log);
	statsWindow->updateWindow();
	statsWindow->show();
}



