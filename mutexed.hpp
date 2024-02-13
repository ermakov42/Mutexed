#pragma once

#include <mutex>

namespace mutexed {

template<typename T>
class Mutexed {
  class LockedPtr {
    public:
      LockedPtr(T* data, std::mutex& mutex): data_(data), guard_(mutex) {}
    
      LockedPtr(const LockedPtr&) = delete;
      LockedPtr(LockedPtr&&) = delete;

      T& operator*() {
        return *data_;
      }

      T* operator->() {
        return data_;
      }

    private:
      T* data_;
      std::lock_guard<std::mutex> guard_;
  };

  public:
    template <typename... Args>
    explicit Mutexed(Args&&... args) : object_(std::forward<Args>(args)...) {}

    LockedPtr Lock() {
      return LockedPtr(&object_, mutex_);
    }

  private:
    T object_;
    std::mutex mutex_;
};

} // namespace mutexed
