#ifndef TIMER_RW_CONCURRENT_UNORDERED_MAP_H
#define TIMER_RW_CONCURRENT_UNORDERED_MAP_H

#include <unordered_map>
#include <shared_mutex>
#include <typeinfo>
#include <iostream>
/*
template<typename K, typename V>
class RwConcurrentUnorderedMap {
private:
    std::unordered_map<K, V> map;
    std::shared_timed_mutex mutex;
public:
    V& at(const K& k) {
        std::shared_lock<std::shared_timed_mutex> readLock(mutex);
        return map.at(k);
    }

    void emplace(const K& k, const V& v) {
        std::lock_guard<std::shared_timed_mutex> writeLock(mutex);
        map.emplace(k, v);
    }

    typename std::unordered_map<K, V>::size_type size() {
        return map.size();
    }

    void iterate() {
        std::shared_lock<std::shared_timed_mutex> readLock(mutex);
        for (auto it = map.cbegin(); it != map.end(); it++) {
            std::cout << typeid(it).name() << std::endl;
            //it->second;
        }
    }

    void iterateLocked(void (*f)(V)) {
        std::lock_guard<std::shared_timed_mutex> iterateLock(mutex);
        for (auto it = map.cbegin(); it != map.cend(); it++) {
            (*f)(it->second);
        }
    }

    std::unique_lock<std::shared_timed_mutex>& lockForIterate() {
        std::unique_lock<std::shared_timed_mutex> iterateLock(mutex);
        return iterateLock;
    }

    void unlockForIterate(std::unique_lock<std::shared_timed_mutex>& iterateLock) {
        iterateLock.unlock();
    }
};

#endif //TIMER_RW_CONCURRENT_UNORDERED_MAP_H
*/