
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

#include "hellrun.h"
#include "stats_window.h"
#include <vector>

class MainWindow : public QWidget {
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	std::vector<HellRun*>& getRuns();

private slots:
	void clickedEpic(QString text);
	void clickedAdd();
	void fixSize();
	void clickedStats();



private:
	StatsWindow* statsWindow;
	std::vector<HellRun*> run_log;
	HellRun* currRun;

	// Layouts
	QVBoxLayout* overallLayout;

		QMessageBox* invalidRun;
		QMessageBox* invalidNumber;
		QWidget* topWidget;
			QHBoxLayout* optionsLayout;
				// Group Boxes
				QGroupBox* difficultyBox;
				QVBoxLayout* difficultyLayout;
				QRadioButton* hardcore;
				QRadioButton* insane;

				QGroupBox* eyeBox;
				QVBoxLayout* eyeLayout;
				QComboBox* eyeList;
				QLabel* eyeLabel;

				QGroupBox* orbBox;
				QVBoxLayout* orbLayout;
				QComboBox* orbList;
				QLabel* orbLabel;

				QGroupBox* runBox;
				QVBoxLayout* hellNumberLayout;
				QLabel* hellNumberLabel;
				QLineEdit* hellNumberInput;

		QWidget* middleWidget;	
			QVBoxLayout* optionsLayout2;
				QGroupBox* epicBox;
				QVBoxLayout* epicLayout;
				QComboBox* numEpicsList;
				QLineEdit* epicNameInput;
				QLineEdit* epicNameInput2;
				QLineEdit* epicNameInput3;
				QLineEdit* epicNameInput4;
				QLineEdit* epicNameInput5;
				QLabel* epicInputLabel;

		QWidget* bottomWidget;
			QVBoxLayout* buttonLayout;
				QPushButton* addRun;
				QPushButton* statistics;
				QPushButton* quitButton;


};