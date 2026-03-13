/*
    Wander29/qt-multithreading-control-example
    (c) 2026 Ludovico Venturi - ludo.venturi@gmail.com

    This file is part of Wander29/qt-multithreading-control-example

    Wander29/qt-multithreading-control-example is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Wander29/qt-multithreading-control-example is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wander29/qt-multithreading-control-example. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QThread>

class Worker;

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  private slots:
  void onStartButtonClicked();
  void onStopButtonClicked();
  void onProgressUpdated(int value);
  void onComputationFinished(const QString &result);
  void onComputationError(const QString &error);

  private:
  void setupUI();
  void connectSignals();

  QProgressBar *progressBar;
  QPushButton *startButton;
  QPushButton *stopButton;
  QLabel *statusLabel;

  QThread *workerThread;
  Worker *worker;
};


#endif // MAINWINDOW_H
