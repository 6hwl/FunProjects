#include <iostream>
#include <QApplication>

#include "hellrun.h"
#include "main_window.h"

using namespace std;

int main(int argc, char* argv[]) {
	QApplication hell(argc, argv);

	MainWindow mainWindow;

  	mainWindow.show();

	return hell.exec();
}