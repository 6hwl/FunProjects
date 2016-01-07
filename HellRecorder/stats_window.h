#ifndef STATS_WINDOW_H
#define STATS_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QCoreApplication>
#include <QGroupBox>
#include <QMessageBox>
#include <QStringList>
#include <QFont>
#include <QFontMetrics>
#include <QSizePolicy>
#include <QTableWidget>
#include <QHeaderView>
#include <QTreeView>
#include <QStandardItemModel>
#include <QTimer>

#include <vector>
#include "hellrun.h"
#include "hellstats.h"
#include "parselog.h"
#include "arraylist.h"
#include "msort.h"

class StatsWindow : public QWidget {
	Q_OBJECT
public:
	StatsWindow(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics);
	~StatsWindow();
	void updateWindow();
	void updateRuns(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics);
	void clearTable();
	void removeEdit();
	void updateEpics();
	void insertAll();
	void insertHardcore();
	void insertInsane();
	//QSize sizeHint(QStandardItemModel* model);

private slots:
	void clickedUpdate();
	void fixSize();

	void clickedAll();
	void clickedHardcore();
	void clickedInsane();

	void clickedRun();
	void clickedName();

	void clickedClose();




private:
	HellStats* stats;
	ArrayList<HellRun*> _runs; // takes pointers from run_log in main_window.cpp
	ArrayList<HellRun*> _epics; // takes pointers from epics in main_window.cpp
	ArrayList<Epic> epic_container; // Holds structs that are of type Epic (see in hellrun.cpp)

	QVBoxLayout* overallLayout;
	QHBoxLayout* middleLayout;
	QHBoxLayout* bottomLayout;

	QVBoxLayout* difficultyLayout;
	QVBoxLayout* sortLayout;

	QTableWidget* hellTable;
	QStandardItemModel* model;
	QHeaderView* headerview;
	QPushButton* updateButton;
	QPushButton* closeButton;

	QVBoxLayout* generalStatsLayout;
	QVBoxLayout* epicStatsLayout;
	QVBoxLayout* otherStatsLayout;

	//Group Boxes
	QGroupBox* generalStatsBox;
	QGroupBox* epicStatsBox;
	QGroupBox* otherStatsBox;
	QGroupBox* difficultyBox;
	QGroupBox* sortBox;

	//Radio Buttons
	QRadioButton* hardcoreButton;
	QRadioButton* insaneButton;
	QRadioButton* allButton;

	QRadioButton* byRunButton;
	QRadioButton* byNameButton;


	// Labels
	QLabel* numHells;
	QLabel* numHardcore;
	QLabel* numInsane;

	QLabel* numEpics;
	QLabel* hardcoreEpics;
	QLabel* insaneEpics;

	QLabel* numEyes;
	QLabel* numOrbs;
	QLabel* numInvites;





};

#endif