#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <rapidjson/schema.h>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/istreamwrapper.h>

#include "FileResult.h"

namespace rj = rapidjson;
namespace fs = std::filesystem;

namespace NDE
{
  class FileFormatChange
  {
  public:
    FileFormatChange(const fs::path& pathFilename_)
      : m_fileStream(pathFilename_)
    {
    }

    virtual TResult<std::string> ApplyChanges(const std::string& jsonSetup_) const = 0;
    
    static TResult<bool> Validate(const std::string& jsonSetup_, std::ifstream& fileStream_)
    {
      rj::Document setupJsonDoc;
      if (setupJsonDoc.Parse(jsonSetup_.c_str()).HasParseError()) {
        return TResult<bool>(TError(rj::GetParseError_En(setupJsonDoc.GetParseError())));
      }

      rj::Document schemaJsonDoc;
      rj::IStreamWrapper isw(fileStream_);
      if (schemaJsonDoc.ParseStream(isw).HasParseError()) {
        return TResult<bool>(TError(rj::GetParseError_En(schemaJsonDoc.GetParseError())));
      }

      auto schemaDoc = rj::SchemaDocument(schemaJsonDoc);
      auto schemaValidator = rj::SchemaValidator(schemaDoc);
      if (!setupJsonDoc.Accept(schemaValidator))
      {
        std::stringstream streamError;

        rj::StringBuffer error;
        schemaValidator.GetInvalidSchemaPointer().StringifyUriFragment(error);
        streamError << "Schema location: " << error.GetString() << " -> ";
        streamError << "Keyword: " << schemaValidator.GetInvalidSchemaKeyword() << " -> ";

        error = rj::StringBuffer();
        schemaValidator.GetInvalidDocumentPointer().StringifyUriFragment(error);
        streamError << "Json location: " << error.GetString();

        return TResult<bool>(TError("schemaValidationError", streamError.str().c_str()));
      }

      return TResult<bool>(true);
    }

    TResult<bool> Validate(const std::string& jsonSetup_)
    {
      return Validate(jsonSetup_, m_fileStream);
    }

  protected:
    std::ifstream m_fileStream;
  };

  //

  class FileFormatChanges : public std::vector<std::unique_ptr<FileFormatChange>>
  {
  public:
    TResult<std::string> ApplyChanges(const std::string& jsonSetup_)
    {
      TResult<std::string> jsonResult(jsonSetup_);
      for (auto itr = begin(); itr < end() && jsonResult.IsSuccess(); ++itr)
      {
        jsonResult = (*itr)->ApplyChanges(jsonResult.Value());
        if (jsonResult.IsSuccess())
        {
          TResult<bool> fileResult = (*itr)->Validate(jsonResult.Value());
          if (fileResult.IsError()) return TResult<std::string>(fileResult.Error());
        }
      }

      return jsonResult;
    }
  };
}
