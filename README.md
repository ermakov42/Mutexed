# Mutexed

A simple secure API for mutual exclusion that will ensure that a shared object cannot be accessed without owning a mutex.

To do this, we will link an object shared between threads and a mutex that will protect it using the `Mutexed<T>` class.

The `Mutexed` class has a single `Lock` method that returns a pointer to the protected object to the user.
