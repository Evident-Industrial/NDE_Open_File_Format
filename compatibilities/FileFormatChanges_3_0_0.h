#pragma once
#include "FileFormatChanges.h"

namespace NDE
{
  class FileFormatChanges_3_0_0 : public FileFormatChange
  {
  public:
    FileFormatChanges_3_0_0(const fs::path& pathFilename_)
      : FileFormatChange(pathFilename_)
    {
    }

    TResult<std::string> ApplyChanges(const std::string& jsonSetup_) const;
    
    static std::string Version;
  };
}
