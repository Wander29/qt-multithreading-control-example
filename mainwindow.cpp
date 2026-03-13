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

#include "mainwindow.h"
#include "worker.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), workerThread(nullptr), worker(nullptr) {
  setupUI();
  connectSignals();
  setWindowTitle("Qt Multithreading Example");
  setGeometry(100, 100, 500, 200);
}

MainWindow::~MainWindow() {
  if (workerThread) {
    workerThread->quit();
    workerThread->wait();
    delete workerThread;
  }
}

void MainWindow::setupUI() {
  QWidget *centralWidget = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

  // Text area
  QLabel * textAreaLabel = new QLabel("Test yourself: write into the text area while computing!", this);
  mainLayout->addWidget(textAreaLabel);
  QTextEdit * textEdit = new QTextEdit(this);
  textEdit->setPlainText(
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
      "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
      "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
      "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
      "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
      );
  mainLayout->addWidget(textEdit);

  // Status label
  statusLabel = new QLabel("Ready", this);
  mainLayout->addWidget(statusLabel);

  // Progress bar
  progressBar = new QProgressBar(this);
  progressBar->setMinimum(0);
  progressBar->setMaximum(100);
  progressBar->setValue(0);
  mainLayout->addWidget(progressBar);

  // Buttons layout
  QHBoxLayout *buttonLayout = new QHBoxLayout();

  startButton = new QPushButton("Start Computation", this);
  stopButton = new QPushButton("Stop", this);
  stopButton->setEnabled(false);

  buttonLayout->addWidget(startButton);
  buttonLayout->addWidget(stopButton);
  mainLayout->addLayout(buttonLayout);

  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);
}

void MainWindow::connectSignals() {
  connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
  connect(stopButton, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);
}

void MainWindow::onStopButtonClicked() {
  worker->requestStop();
}

void MainWindow::onStartButtonClicked() {
  // Create worker and thread
  workerThread = new QThread(this);
  worker = new Worker();
  worker->moveToThread(workerThread);

  // Connect signals
  connect(workerThread, &QThread::started, worker, &Worker::doHeavyComputation);
  connect(worker, &Worker::progressUpdated, this, &MainWindow::onProgressUpdated);
  connect(worker, &Worker::computationFinished, this, &MainWindow::onComputationFinished);
  connect(worker, &Worker::computationError, this, &MainWindow::onComputationError);
  connect(worker, &Worker::computationFinished, workerThread, &QThread::quit);
  connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
  connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);

  // Disable start button during computation
  startButton->setEnabled(false);
  stopButton->setEnabled(true);
  statusLabel->setText("Computing...");
  progressBar->setValue(0);

  // Start the thread
  workerThread->start();
}

void MainWindow::onProgressUpdated(int value) {
  progressBar->setValue(value);
  statusLabel->setText(QString("Progress: %1%").arg(value));
}

void MainWindow::onComputationFinished(const QString &result) {
  statusLabel->setText(result);
  startButton->setEnabled(true);
  stopButton->setEnabled(false);
}

void MainWindow::onComputationError(const QString &error) {
  statusLabel->setText("Error: " + error);
  startButton->setEnabled(true);
  stopButton->setEnabled(false);
}
