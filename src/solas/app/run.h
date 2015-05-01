//
//  solas/app/run.h
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
#ifndef SOLAS_APP_RUN_H_
#define SOLAS_APP_RUN_H_

#include "solas/app/runner_factory.h"
#include "solas/app/runner_options.h"

namespace solas {
namespace app {

int Run(int argc, char **argv);

template <typename Runnable>
inline int Run(int argc, char **argv,
               const RunnerOptions& options = RunnerOptions()) {
  RunnerFactory::Shared().set<Runnable>(options);
  return Run(argc, argv);
}

}  // namespace app
}  // namespace solas

#endif  // SOLAS_APP_RUN_H_
