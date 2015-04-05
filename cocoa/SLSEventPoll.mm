//
//  SLSEventPoll.mm
//
//  MIT License
//
//  Copyright (C) 2014-2015 Shota Matsuda
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//

#if __has_feature(objc_arc)
#error This file must be compiled without ARC. Use -fno-objc-arc flag.
#endif

#import "SLSEventPoll.h"

#include <algorithm>
#include <mutex>
#include <vector>

namespace {

static bool CompareTimestamp(SLSEvent *a, SLSEvent *b) {
  return [a timestamp] < [b timestamp];
}

}  // namespace

@interface SLSEventPoll () {
 @private
  std::vector<SLSEvent *> _events;
  std::mutex _mutex;
}

@end

@implementation SLSEventPoll

- (void)dealloc {
  std::unique_lock<std::mutex> lock(_mutex);
  for (SLSEvent *event : _events) {
    [event release];
  }
  lock.unlock();
  [super dealloc];
}

#pragma mark Counting Events

- (NSUInteger)count {
  std::lock_guard<std::mutex> lock(_mutex);
  return _events.size();
}

#pragma mark Adding and Removing Events

- (void)addEvent:(SLSEvent *)event {
  std::lock_guard<std::mutex> lock(_mutex);
  const auto other = std::find_if(
      _events.begin(), _events.end(), [event](SLSEvent *other) {
    return [event type] == [other type];
  });
  if (other != _events.end()) {
    if ([event timestamp] > [*other timestamp]) {
      [*other release];
      _events.erase(other);
    } else {
      return;
    }
  }
  const auto bound = std::lower_bound(
      _events.begin(), _events.end(), event, CompareTimestamp);
  _events.emplace(bound, [event retain]);
}

- (void)addEventsFromArray:(NSArray *)array {
  for (SLSEvent *event : array) {
    [self addEvent:event];
  }
}

- (void)removeEvent:(SLSEvent *)event {
  std::lock_guard<std::mutex> lock(_mutex);
  auto itr = std::find(_events.begin(), _events.end(), event);
  if (itr != _events.end()) {
    [*_events.erase(itr) release];
  }
}

- (void)removeEventsInArray:(NSArray *)array {
  for (SLSEvent *event : array) {
    [self removeEvent:event];
  }
}

- (NSArray *)removeAllEvents {
  std::lock_guard<std::mutex> lock(_mutex);
  NSArray *array = [NSArray arrayWithObjects:_events.data()
                                       count:_events.size()];
  for (SLSEvent *event : _events) {
    [event release];
  }
  _events.clear();
  return array;
}

@end
