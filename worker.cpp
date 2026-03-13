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

#include "worker.h"
#include <QThread>
#include <cmath>

Worker::Worker()
  : stopRequested(0)
{}

void Worker::doHeavyComputation() {
  try {
    int totalIterations = 100;

    for (int i = 0; i <= totalIterations && !stopRequested.loadAcquire(); ++i) {
      // Simulate heavy computation
      int result = performLongCalculation(1000000);

      // Emit progress update
      emit progressUpdated(i);

      // Simulate work duration
      QThread::msleep(50);
    }

    emit computationFinished("Computation completed successfully!");
  } catch (const std::exception &e) {
    emit computationError(QString::fromStdString(e.what()));
  }
}

int Worker::performLongCalculation(int iterations) {
  int sum = 0;
  for (int i = 0; i < iterations; ++i) {
    sum += static_cast<int>(std::sqrt(i));
  }
  return sum;
}

void Worker::requestStop() {
  stopRequested.storeRelease(1);
}
