#pragma once

#include "Result/Result.h"
#include "Result/ResultDetails.h"

namespace NDE
{
  using TError = ResultDetails;
  using TWarning = ResultDetails;
  using TWarnings = std::vector<TWarning>;

  template <typename T_RESULT>
  using TResult = ONDTLib::Result<T_RESULT, TError, TWarnings>;
}
