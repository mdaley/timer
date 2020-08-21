#ifndef TIMER_RWCONCURRENTUNORDEREDMAP_H
#define TIMER_RWCONCURRENTUNORDEREDMAP_H

#include <unordered_map>
#include <shared_mutex>

template<typename K, typename V>
class RwConcurrentUnorderedMap {
private:
    std::unordered_map<K, V> map;
    std::shared_timed_mutex mutex;
public:
    V at(K k) {
        std::shared_lock<std::shared_timed_mutex> readLock(mutex);
        return map.at(k);
    }

    void emplace(K k, V v) {
        std::lock_guard<std::shared_timed_mutex> writeLock(mutex);
        map.emplace(k, v);
    }

    typename std::unordered_map<K, V>::size_type size() {
        return map.size();
    }
};

#endif //TIMER_RWCONCURRENTUNORDEREDMAP_H
