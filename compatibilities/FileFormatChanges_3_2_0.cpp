#include "FileFormatChanges_3_2_0.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>

#include "FileFormat.h"


std::string NDE::FileFormatChanges_3_2_0::Version = NDE::VERSION_3_2_0;

NDE::TResult<std::string> NDE::FileFormatChanges_3_2_0::ApplyChanges(const std::string& jsonSetup_) const
{
  rj::Document jsonSetupDoc;
  if (!jsonSetupDoc.Parse(jsonSetup_).HasParseError())
  {
    rj::Document newJsonSetupDoc;
    auto& allocator = newJsonSetupDoc.GetAllocator();

    newJsonSetupDoc.CopyFrom(jsonSetupDoc, allocator);


    //TODO


    // Update version //
    newJsonSetupDoc["version"].SetString(Version, allocator);
    newJsonSetupDoc["$schema"].SetString("./NDE-FileFormat-Schema-3.2.0.json", allocator);

    rj::StringBuffer buffer;
    rj::Writer<rj::StringBuffer> writer(buffer);
    newJsonSetupDoc.Accept(writer);

    return NDE::TResult<std::string>(buffer.GetString(), { ResultDetails("domainSetupVersionUpgraded", Version) });
  }

  return NDE::TResult<std::string>(TError("jsonParseError"));
}
