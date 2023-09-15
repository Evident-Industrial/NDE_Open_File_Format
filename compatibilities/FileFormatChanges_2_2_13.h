#pragma once
#include "FileFormatChanges.h"

namespace NDE
{
  class FileFormatChanges_2_2_13 : public FileFormatChange
  {
  public:
    FileFormatChanges_2_2_13(const fs::path& pathFilename_)
      : FileFormatChange(pathFilename_)
    {
    }

    TResult<std::string> ApplyChanges(const std::string& jsonSetup_) const;
    
    static std::string Version;
  };
}
