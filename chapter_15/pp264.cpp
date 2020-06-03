#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

// Object to be communicated
struct Message {
  std::string message;
};

struct Controller {
  std::queue<Message> mqueue;     // The queue of messages
  std::condition_variable mcond;  // The variable communicating events
  std::mutex mmutex;              // For synchronizing access to mcond
};

void consumer(Controller& c) {
  while (true) {
    // Acquire mutex
    std::unique_lock lck{c.mmutex};
    // Release lck and wait
    // Re-acquire lck upon wakeup
    // Don't wake up unless mqueue is non-empty
    c.mcond.wait(lck, [&c] { return !c.mqueue.empty(); });
    auto m{c.mqueue.front()};  // Get the message
    c.mqueue.pop();
    lck.unlock();  // Release lck

    // Process m
    std::cout << m.message << '\n';
  }
}

void producer(Controller& c) {
  using namespace std::string_literals;
  int i{};
  while (true) {
    Message m{"Message number #"s + std::to_string(i++)};

    // Protect operations
    std::scoped_lock lck{c.mmutex};
    c.mqueue.push(m);
    c.mcond.notify_one();  // Notify

    // Release lock (at end of scope)
  }
}

////////////////////////////////////////////////////////////////////////////////

int main() {
  Controller c;
  std::thread t1{consumer, std::ref(c)};
  std::thread t2{producer, std::ref(c)};

  t1.join();
  t2.join();
}