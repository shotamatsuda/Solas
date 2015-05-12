//
//  solas/app/layer.cc
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

#include "solas/app/layer.h"

#include <cassert>

#include "solas/app/view.h"

namespace solas {
namespace app {

#pragma mark Aggregation

View& Layer::view() {
  assert(parent_);
  Layer *parent = parent_;
  while (parent->parent()) {
    parent = parent->parent();
  }
  return static_cast<View&>(*parent);
}

const View& Layer::view() const {
  assert(parent_);
  const Layer *parent = parent_;
  while (parent->parent()) {
    parent = parent->parent();
  }
  return static_cast<const View&>(*parent);
}

}  // namespace app
}  // namespace solas
