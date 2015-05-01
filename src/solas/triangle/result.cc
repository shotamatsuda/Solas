//
//  solas/triangle/result.cc
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

#include "solas/triangle/result.h"

#include <cstdlib>
#include <cstring>
#include <memory>

#include "solas/triangle/lib.h"

namespace solas {
namespace triangle {

Result::Result() : data_(std::make_unique<struct triangulateio>()) {
  std::memset(data_.get(), 0, sizeof(*data_));
}

Result::~Result() {
  std::free(data_->pointlist);
  std::free(data_->pointmarkerlist);
  std::free(data_->pointattributelist);
  std::free(data_->trianglelist);
  std::free(data_->triangleattributelist);
  std::free(data_->trianglearealist);
  std::free(data_->neighborlist);
  std::free(data_->segmentlist);
  std::free(data_->segmentmarkerlist);
  std::free(data_->holelist);
  std::free(data_->regionlist);
  std::free(data_->edgelist);
  std::free(data_->edgemarkerlist);
  std::free(data_->normlist);
}

}  // namespace triangle
}  // namespace solas
