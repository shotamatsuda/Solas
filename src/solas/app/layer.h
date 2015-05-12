//
//  solas/app/layer.h
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

#pragma once
#ifndef SOLAS_APP_LAYER_H_
#define SOLAS_APP_LAYER_H_

#include <cassert>

#include "solas/app/composite.h"

namespace solas {
namespace app {

template <typename View>
class Layer : public Composite {
 public:
  // Constructors
  using Composite::Composite;

  // Aggregation
  View& view() const;
};

#pragma mark -

#pragma mark Aggregation

template <typename View>
View& Layer<View>::view() const {
  Composite *current = parent();
  assert(current);
  while (current->parent()) {
    current = current->parent();
  }
  return static_cast<View&>(*current);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_LAYER_H_
