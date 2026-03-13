This is a Qt multithreading example demonstrating worker thread lifecycle management with Start/Stop controls using `QAtomicInt` for thread-safe flag checking.

It has been tested with `Qt 5.15`.

## Key concepts

-   Use a worker and run it inside its own thread

```{cpp}
  workerThread = new QThread(this);
  worker = new Worker();
  worker->moveToThread(workerThread);
```

- Use `QAtomicInt` flag:
  - `loadAcquire` for reading; prevents later code from starting before 
  - `storeRelease` for writing; prevents earlier operations from being reordered after the store

```{cpp}
void Worker::doHeavyComputation() {
  ...
  for (int i = 0; i <= totalIterations && !stopRequested.loadAcquire(); ++i) 
  {...}
}
```

```{cpp}
void Worker::requestStop() {
  stopRequested.storeRelease(1);
}
```

## Sample Animation

![](https://s13.gifyu.com/images/bmhvo.webp)