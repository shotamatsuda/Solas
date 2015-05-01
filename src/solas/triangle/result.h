//
//  solas/triangle/result.h
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
#ifndef SOLAS_TRIANGLE_RESULT_H_
#define SOLAS_TRIANGLE_RESULT_H_

#include <memory>

struct triangulateio;

namespace solas {
namespace triangle {

class Result final {
 public:
  // Constructors
  Result();
  ~Result();

  // Disallow copy and assign
  Result(const Result& other) = delete;
  Result& operator=(const Result& other) = delete;

  // Move
  Result(Result&& other) = default;

  // Operators
  struct triangulateio& operator*() { return *get(); }
  struct triangulateio * operator->() { return get(); }
  struct triangulateio * get() { return data_.get(); }

 private:
  std::unique_ptr<struct triangulateio> data_;
};

}  // namespace triangle
}  // namespace solas

#endif  // SOLAS_TRIANGLE_RESULT_H_
