#include "FileFormatChanges_2_2_13.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>

#include "FileFormat.h"


std::string NDE::FileFormatChanges_2_2_13::Version = NDE::VERSION_2_2_13;

NDE::TResult<std::string> NDE::FileFormatChanges_2_2_13::ApplyChanges(const std::string& jsonSetup_) const
{
  rj::Document jsonSetupDoc;
  if (!jsonSetupDoc.Parse(jsonSetup_).HasParseError())
  {
    // Add $schema //
    if (!jsonSetupDoc.HasMember("$schema"))
    {
      jsonSetupDoc.AddMember("$schema", "./NDE-FileFormat-Schema-2.2.13.json", jsonSetupDoc.GetAllocator());
    }

    // Rename nominalThickness to nominalHeight //
    for (rj::SizeType probeIdx{}; probeIdx < jsonSetupDoc["probes"].GetArray().Size(); probeIdx++)
    {
      std::string probeIdxPath("/probes/" + std::to_string(probeIdx));
      if (auto fluidColumn = rj::Pointer(probeIdxPath + "/fluidColumn").Get(jsonSetupDoc))
      {
        auto nominalThickness = fluidColumn->FindMember("nominalThickness");
        if (nominalThickness != fluidColumn->MemberEnd()) {
          nominalThickness->name.SetString("nominalHeight", jsonSetupDoc.GetAllocator());
        }
      }
    }

    // Add motionDevices //
    if (!jsonSetupDoc.HasMember("motionDevices"))
    {
      rj::Value motionDevices(rj::kArrayType);
      rj::Value motionDevice(rj::kObjectType);
      motionDevice.AddMember("id", 0, jsonSetupDoc.GetAllocator());
      rj::Value quadratureEncoder(rj::kObjectType);
      motionDevice.AddMember("quadratureEncoder", quadratureEncoder, jsonSetupDoc.GetAllocator());
      motionDevices.PushBack(motionDevice, jsonSetupDoc.GetAllocator());
      jsonSetupDoc.AddMember("motionDevices", motionDevices, jsonSetupDoc.GetAllocator());
    }

    std::vector<std::string> dataGroupSuffixes{ "/ultrasound/linearPulseEcho"/*, "/ultrasound/sectorialPulseEcho"*/ };
    for (rj::SizeType dataGroupIdx{}; dataGroupIdx < jsonSetupDoc["dataGroups"].GetArray().Size(); dataGroupIdx++)
    {
      std::string dataGroupIdxPath("/dataGroups/" + std::to_string(dataGroupIdx));
      for (const auto& dataGroupSuffix : dataGroupSuffixes)
      {
        std::string dataGroupPath(dataGroupIdxPath + dataGroupSuffix);
        if (auto dataGroup = rj::Pointer(dataGroupPath).Get(jsonSetupDoc))
        {
          rj::Document jsonDoc;

          // Replace amplitudeAxis with amplitudePercentAxis //
          if ((*dataGroup).HasMember("amplitudeAxis"))
          {
            jsonDoc.CopyFrom((*dataGroup)["amplitudeAxis"]["percent"], jsonSetupDoc.GetAllocator());
            dataGroup->AddMember("amplitudePercentAxis", jsonDoc, jsonSetupDoc.GetAllocator());
            dataGroup->RemoveMember("amplitudeAxis");
          }

          if ((*dataGroup).HasMember("beams"))
          {
            for (auto& beam : (*dataGroup)["beams"].GetArray())
            {
              // Add pulsers and receivers //
              if (beam.HasMember("pulsers") && beam["pulsers"].GetArray().Size() == 0)
              {
                rj::Value pulser(rj::kObjectType);
                pulser.AddMember("id", 0, jsonSetupDoc.GetAllocator());
                pulser.AddMember("elementId", 0, jsonSetupDoc.GetAllocator());
                beam["pulsers"].PushBack(pulser, jsonSetupDoc.GetAllocator());
              }

              if (beam.HasMember("receivers") && beam["receivers"].GetArray().Size() == 0)
              {
                rj::Value receiver(rj::kObjectType);
                receiver.AddMember("id", 0, jsonSetupDoc.GetAllocator());
                receiver.AddMember("elementId", 0, jsonSetupDoc.GetAllocator());
                beam["receivers"].PushBack(receiver, jsonSetupDoc.GetAllocator());
              }
            }
          }

          // Rename averaging to averagingFactor //
          if ((*dataGroup).HasMember("averaging"))
          {
            jsonDoc.CopyFrom((*dataGroup)["averaging"], jsonSetupDoc.GetAllocator());
            dataGroup->AddMember("averagingFactor", jsonDoc, jsonSetupDoc.GetAllocator());
            dataGroup->RemoveMember("averaging");
          }

          // Rename filterTypes //
          if ((*dataGroup).HasMember("digitalBandPassFilter"))
          {
            std::string filterType = (*dataGroup)["digitalBandPassFilter"]["filterType"].GetString();
            if (filterType == "Low-pass") {
              (*dataGroup)["digitalBandPassFilter"]["filterType"].SetString("LowPass", jsonSetupDoc.GetAllocator());
            }
            else if (filterType == "High-pass") {
              (*dataGroup)["digitalBandPassFilter"]["filterType"].SetString("HighPass", jsonSetupDoc.GetAllocator());
            }
            else if (filterType == "Band-pass") {
              (*dataGroup)["digitalBandPassFilter"]["filterType"].SetString("BandPass", jsonSetupDoc.GetAllocator());
            }
          }

          // Default timeSelection to Crossing //
          if ((*dataGroup).HasMember("gates"))
          {
            for (auto& gate : (*dataGroup)["gates"].GetArray())
            {
              if (gate.HasMember("timeSelection"))
              {
                std::string timeSelection = gate["timeSelection"].GetString();
                if (timeSelection.empty())
                {
                  gate["timeSelection"].SetString("Crossing", jsonSetupDoc.GetAllocator());
                }
              }
            }
          }

          // Rename statuses: Synced to Synched //
          if ((*dataGroup).HasMember("datasets"))
          {
            for (auto& dataset : (*dataGroup)["datasets"].GetArray())
            {
              if (dataset.HasMember("ascan"))
              {
                if (dataset["ascan"].HasMember("statuses"))
                {
                  for (auto& status : dataset["ascan"]["statuses"].GetArray())
                  {
                    std::string statusName = status.GetString();
                    if (statusName == "Synced")
                    {
                      status.SetString("Synched", jsonSetupDoc.GetAllocator());
                    }
                  }
                }
              }

              if (dataset.HasMember("cscan"))
              {
                if (dataset["cscan"].HasMember("statuses"))
                {
                  for (auto& status : dataset["cscan"]["statuses"].GetArray())
                  {
                    std::string statusName = status.GetString();
                    if (statusName == "Synced")
                    {
                      status.SetString("Synched", jsonSetupDoc.GetAllocator());
                    }
                  }
                }
              }
            }
          }
        }
      }
    }

    // Update version //
    jsonSetupDoc["version"].SetString(Version, jsonSetupDoc.GetAllocator());

    rj::StringBuffer buffer;
    rj::Writer<rj::StringBuffer> writer(buffer);
    jsonSetupDoc.Accept(writer);

    return NDE::TResult<std::string>(buffer.GetString(), { ResultDetails("domainSetupVersionUpgraded", Version) });
  }

  return NDE::TResult<std::string>(TError("jsonParseError"));
}
