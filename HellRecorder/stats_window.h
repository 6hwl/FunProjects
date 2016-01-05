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

class StatsWindow : public QWidget {
	Q_OBJECT
public:
	StatsWindow(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics);
	~StatsWindow();
	void updateWindow();
	void updateRuns(ArrayList<HellRun*>& runs, ArrayList<HellRun*>& epics);
	void clearTable();
	//QSize sizeHint(QStandardItemModel* model);

private slots:
	void clickedUpdate();
	void fixSize();



private:
	HellStats* stats;
	ArrayList<HellRun*> _runs; // takes pointers from run_log in main_window.cpp
	ArrayList<HellRun*> _epics; // takes pointers from epics in main_window.cpp

	QVBoxLayout* overallLayout;
	QHBoxLayout* tableLayout;

		//QTableWidget* hellTable;
		QTableWidget* hellTable;
		QStandardItemModel* model;
		QHeaderView* headerview;
		QPushButton* updateButton;
		QGroupBox* statsBox;
			QVBoxLayout* statsLayout;
				QLabel* numHells;

				QLabel* numEyes;
				QLabel* numOrbs;

				QLabel* numEpics;

				QLabel* numHardcore;
				QLabel* percentHardcore;
				QLabel* hardcoreEpics;

				QLabel* numInsane;
				QLabel* percentInsane;
				QLabel* insaneEpics;

				QLabel* numInvites;





};

#endif