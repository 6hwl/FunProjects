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
#include <QComboBox>
#include <QStringList>
#include <QFont>
#include <QFontMetrics>
#include <QSizePolicy>
#include <QTimer>

#include <vector>
#include "hellrun.h"
#include "hellstats.h"
#include "parselog.h"
#include "arraylist.h"

class StatsWindow : public QWidget {
	Q_OBJECT
public:
	StatsWindow(ArrayList<HellRun*>& runs);
	~StatsWindow();
	void updateWindow();
	void updateRuns(ArrayList<HellRun*>& runs);

private slots:
	void clickedUpdate();



private:
	HellStats* stats;
	ArrayList<HellRun*> _runs; // takes pointers from run_log in main_window.cpp

	QHBoxLayout* overallLayout;
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