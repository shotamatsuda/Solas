//
//  solas/app/runner_factory.cc
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

#include "solas/app/runner_factory.h"

#include "solas/utility/singleton.h"

namespace solas {
namespace app {

namespace {

static utility::Singleton<RunnerFactory> instance;

}  // namespace

RunnerFactory& RunnerFactory::Shared() {
  return *instance;
}

}  // namespace app
}  // namespace solas
