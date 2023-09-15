#pragma once
#include <string>
#include <vector>
#include <utility>

#include <filesystem>
#if __cplusplus >= 201703L // c++17
namespace fs = std::filesystem;
#else
namespace fs = std::experimental::filesystem;
#endif

#include "FileResult.h"

namespace NDE
{
  constexpr const char* VERSION_2_2_12  = "2.2.12";
  constexpr const char* VERSION_2_2_13  = "2.2.13";
  constexpr const char* VERSION_3_0_0   = "3.0.0";
  constexpr const char* VERSION_3_0_1   = "3.0.1";
  constexpr const char* VERSION_3_1_0   = "3.1.0";
  constexpr const char* VERSION_3_2_0   = "3.2.0";
  constexpr const char* VERSION_4_0_0   = "4.0.0";

  using TSchemaValidator = std::pair<std::string, fs::path>;
  using TSchemaValidators = std::vector<TSchemaValidator>;

  void Parse(int result[3], const std::string& input_);
  bool IsLess(const std::string& a_, const std::string& b_);

  TSchemaValidators FindSchemaValidators(const fs::path& schemasPath_);  
  TResult<std::string> Upgrade(const fs::path& schemasPath_, const std::string& jsonSetup_);
  TResult<bool> Validate(const std::string& jsonSetup_, const fs::path& schemaPathFilename_);
}
