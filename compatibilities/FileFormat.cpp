#include "FileFormat.h"

#include <fstream>

#include <rapidjson/schema.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include "FileFormatChanges_2_2_13.h"
#include "FileFormatChanges_3_0_0.h"
#include "FileFormatChanges_3_1_0.h"
#include "FileFormatChanges_3_2_0.h"

namespace rj = rapidjson;

namespace NDE
{
  void Parse(int result[3], const std::string& input_)
  {
    std::istringstream parser(input_);
    parser >> result[0];
    for (int idx{ 1 }; idx < 3; idx++)
    {
      parser.get();
      parser >> result[idx];
    }
  }

  bool IsLess(const std::string& a_, const std::string& b_)
  {
    int parsedA[3], parsedB[3];
    Parse(parsedA, a_);
    Parse(parsedB, b_);
    return std::lexicographical_compare(parsedA, parsedA + 3, parsedB, parsedB + 3);
  }

  TSchemaValidators FindSchemaValidators(const fs::path& schemasPath_)
  {
    TSchemaValidators schemaValidators;
    for (const auto& schemaPathFilename : fs::directory_iterator(schemasPath_))
    {
      if (fs::is_regular_file(schemaPathFilename) && schemaPathFilename.path().extension() == ".json")
      {
        if (schemaPathFilename.path().filename().string().find("NDE-FileFormat-Schema-") == 0)
        {
          rj::Document schemaJsonDoc;
          std::ifstream fileStream(schemaPathFilename.path());
          rj::IStreamWrapper isw(fileStream);
          if (!schemaJsonDoc.ParseStream(isw).HasParseError())
          {
            if (auto schemaVersion = rj::Pointer("/properties/version/enum").Get(schemaJsonDoc))
            {
              if (schemaVersion->GetArray().Size() == 1) {
                schemaValidators.emplace_back(schemaVersion->GetArray()[0].GetString(), schemaPathFilename.path());
              }
            }
          }
        }
      }
    }

    std::sort(schemaValidators.begin(), schemaValidators.end(),
      [](const std::pair<std::string, fs::path>& a, const std::pair<std::string, fs::path>& b) {
      return IsLess(a.first, b.first);
      });

    return schemaValidators;
  }

  TResult<bool> Validate(const std::string& jsonSetup_, const fs::path& schemaPathFilename_)
  {
    std::ifstream ifs(schemaPathFilename_);
    return FileFormatChange::Validate(jsonSetup_, ifs);
  }

  TResult<std::string> Upgrade(const fs::path& schemasPath_, const std::string& jsonSetup_)
  {
    rj::Document jsonSetupDoc;
    jsonSetupDoc.Parse(jsonSetup_);
    std::string fileVersion = jsonSetupDoc["version"].GetString();

    FileFormatChanges fileFormatChanges;
    const TSchemaValidators& schemaValidators = FindSchemaValidators(schemasPath_);
    for (const auto& schemaValidator : schemaValidators)
    {
      std::string schemaVersion = schemaValidator.first;
      if (std::lexicographical_compare(fileVersion.begin(), fileVersion.end(), schemaVersion.begin(), schemaVersion.end()))
      {
        if (schemaVersion == NDE::FileFormatChanges_2_2_13::Version)
        {
          fileFormatChanges.push_back(std::make_unique<NDE::FileFormatChanges_2_2_13>(schemaValidator.second));
        }
        else if (schemaVersion == NDE::FileFormatChanges_3_0_0::Version)
        {
          fileFormatChanges.push_back(std::make_unique<NDE::FileFormatChanges_3_0_0>(schemaValidator.second));
        }
        else if (schemaVersion == NDE::FileFormatChanges_3_1_0::Version)
        {
          fileFormatChanges.push_back(std::make_unique<NDE::FileFormatChanges_3_1_0>(schemaValidator.second));
        }
        else if (schemaVersion == NDE::FileFormatChanges_3_2_0::Version)
        {
          fileFormatChanges.push_back(std::make_unique<NDE::FileFormatChanges_3_2_0>(schemaValidator.second));
        }

        //Upgrade Next versions here...
      }
    }

    if (fileFormatChanges.size() > 0) {
      return fileFormatChanges.ApplyChanges(jsonSetup_);
    }

    auto schemaValidatorItr = std::find_if(schemaValidators.begin(), schemaValidators.end(), [&]
      (const TSchemaValidator& schemaValidator_){ return schemaValidator_.first == fileVersion; });

    if (schemaValidatorItr != schemaValidators.end())
    {
      std::ifstream stream((*schemaValidatorItr).second);
      TResult<bool> fileResult = FileFormatChange::Validate(jsonSetup_, stream);

      if (fileResult.IsError()) {
        return TResult<std::string>(jsonSetup_, { fileResult.Error() });
      }
      else {
        return TResult<std::string>(jsonSetup_);
      }
    }

    return TResult<std::string>(jsonSetup_, { ResultDetails("domainSetupSchemaNotFound", fileVersion) });
  }
}
