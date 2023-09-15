#include "FileFormatChanges_3_1_0.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>

#include "FileFormat.h"


std::string NDE::FileFormatChanges_3_1_0::Version = NDE::VERSION_3_1_0;

NDE::TResult<std::string> NDE::FileFormatChanges_3_1_0::ApplyChanges(const std::string& jsonSetup_) const
{
  rj::Document jsonSetupDoc;
  if (!jsonSetupDoc.Parse(jsonSetup_).HasParseError())
  {
    rj::Document newJsonSetupDoc;
    auto& allocator = newJsonSetupDoc.GetAllocator();

    newJsonSetupDoc.CopyFrom(jsonSetupDoc, allocator);

    for (auto& group : newJsonSetupDoc["groups"].GetArray())
    {
      if (group.HasMember("dataset")) {
        group["dataset"].RemoveMember("gateCscans");
      }

      if (group.HasMember("paut"))
      {
        for (auto& beam : group["paut"]["beams"].GetArray())
        {
          if (beam.HasMember("tcg"))
          {
            if (beam["tcg"]["points"].GetArray().Size() > 0 &&
               !beam["tcg"].HasMember("enabled"))
            {
              beam["tcg"].AddMember("enabled", true, allocator);
            }
          }
        }

        if (group["paut"].HasMember("softwareProcess") && group["paut"]["softwareProcess"].HasMember("tcg"))
        {
          if (group["paut"]["softwareProcess"]["tcg"].HasMember("points"))
          {
            if (group["paut"]["softwareProcess"]["tcg"]["points"].GetArray().Size() == 0)
            {
              group["paut"]["softwareProcess"].RemoveMember("tcg");
            }
          }
          else {
            group["paut"]["softwareProcess"].RemoveMember("tcg");
          }
        }
      }
    }

    // Update version //
    newJsonSetupDoc["version"].SetString(Version, allocator);
    newJsonSetupDoc["$schema"].SetString("./NDE-FileFormat-Schema-3.1.0.json", allocator);

    rj::StringBuffer buffer;
    rj::Writer<rj::StringBuffer> writer(buffer);
    newJsonSetupDoc.Accept(writer);

    return NDE::TResult<std::string>(buffer.GetString(), { ResultDetails("domainSetupVersionUpgraded", Version) });
  }

  return NDE::TResult<std::string>(TError("jsonParseError"));
}
