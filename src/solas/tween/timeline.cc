//
//  solas/tween/timeline.cc
//
//  takram design engineering Confidential
//
//  Copyright (C) 2015 Shota Matsuda
//
//  All information contained herein is, and remains the property of takram
//  design engineering and its suppliers, if any. The intellectual and
//  technical concepts contained herein are proprietary to takram design
//  engineering and its suppliers and may be covered by U.S. and Foreign
//  Patents, patents in process, and are protected by trade secret or copyright
//  law. Dissemination of this information or reproduction of this material is
//  strictly forbidden unless prior written permission is obtained from takram
//  design engineering.
//

#include "solas/tween/timeline.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "solas/tween/interval.h"

namespace solas {
namespace tween {

#pragma mark Managing adaptors

template <typename Interval>
void Timeline<Interval>::add(Adaptor adaptor, bool overwrite) {
  assert(adaptor);
  const auto object = adaptor->object_hash();
  const auto target = adaptor->target_hash();
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  if (objects_.find(object) == objects_.end()) {
    auto& targets = objects_.emplace(object, Targets()).first->second;
    targets.emplace(target, adaptor);
  } else {
    auto& targets = objects_.at(object);
    if (overwrite) {
      targets.erase(target);
    }
    targets.emplace(target, adaptor);
  }
}

template <typename Interval>
void Timeline<Interval>::remove(Adaptor adaptor) {
  assert(adaptor);
  const auto object = adaptor->object_hash();
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  if (objects_.find(object) != objects_.end()) {
    auto& targets = objects_.at(object);
    const auto itr = std::find_if(
        targets.begin(), targets.end(),
        [&adaptor](const std::pair<std::size_t, Adaptor>& pair) {
          return pair.second == adaptor;
        });
    if (itr != targets.end()) {
      targets.erase(itr);
      if (targets.empty()) {
        objects_.erase(object);
      }
    }
  }
}

template <typename Interval>
bool Timeline<Interval>::contains(Adaptor adaptor) const {
  assert(adaptor);
  const auto object = adaptor->object_hash();
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  if (objects_.find(object) != objects_.end()) {
    const auto& targets = objects_.at(object);
    const auto itr = std::find_if(
        targets.begin(), targets.end(),
        [&adaptor](const std::pair<std::size_t, Adaptor>& pair) {
          return pair.second == adaptor;
        });
    return itr != targets.end();
  }
  return false;
}

template <typename Interval>
bool Timeline<Interval>::empty() const {
  std::lock_guard<std::recursive_mutex> lock(*mutex_);
  return objects_.empty();
}

#pragma mark Advances the timeline

template <typename Interval>
Interval Timeline<Interval>::advance() {
  std::vector<Adaptor> finished_adaptors;
  std::unique_lock<std::recursive_mutex> lock(*mutex_);
  const auto now = clock_.advance();
  for (auto object_itr = objects_.begin(); object_itr != objects_.end();) {
    auto& targets = object_itr->second;
    for (auto target_itr = targets.begin(); target_itr != targets.end();) {
      const auto adaptor = target_itr->second;
      assert(adaptor);
      if (adaptor->running()) {
        adaptor->update(now, false);
      }
      if (adaptor->finished()) {
        targets.erase(target_itr++);
        finished_adaptors.emplace_back(adaptor);
      } else {
        ++target_itr;
      }
    }
    if (targets.empty()) {
      objects_.erase(object_itr++);
    } else {
      ++object_itr;
    }
  }
  lock.unlock();
  for (auto& adaptor : finished_adaptors) {
    if (adaptor->callback()) {
      adaptor->callback()();
    }
  }
  return now;
}

template class Timeline<Time>;
template class Timeline<Frame>;

}  // namespace tween
}  // namespace solas
