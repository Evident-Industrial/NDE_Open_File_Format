#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

#include <hdf5.h>
#include <rapidjson/schema.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace rj = rapidjson;
namespace fs = std::filesystem;

// Run create-file example before to create a .nde file.

int main()
{
  fs::path currentPath = fs::current_path(); 

  while (currentPath.filename() != "build") {
    currentPath = currentPath.parent_path(); 
  }
  fs::path scenariosPathName = currentPath.parent_path() / "scenarios";
  fs::path inputPathFilename = scenariosPathName / "general-mapping" / "oneline-scan-plate-paut-linear.nde";

  // Open file and JSON dataset
  hid_t fileId = H5Fopen(inputPathFilename.string().c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  hid_t propId = H5Pcreate(H5P_DATASET_ACCESS);
  hid_t dsetId = H5Dopen(fileId, "/Domain/Setup", propId);

  // Read JSON dataset
  hid_t dataType = H5Dget_type(dsetId);
  std::vector<char> json(H5Tget_size(dataType));
  herr_t errorCode = H5Dread(dsetId, dataType, H5S_ALL, H5S_ALL, H5P_DEFAULT, json.data());
  errorCode = H5Dclose(dsetId);
  std::string jsonSetup(json.begin(), json.end());

  rj::Document jsonDoc;
  jsonDoc.Parse(jsonSetup.c_str());
  std::string version = jsonDoc["version"].GetString();

  for (const auto& group : jsonDoc["groups"].GetArray())
  {
    // Read phased array configuration
    if (group.HasMember("paut"))
    {
      auto& paut = group["paut"];
      for (const auto& beam : paut["beams"].GetArray())
      {
        double refractedAngle = beam["refractedAngle"].GetDouble();
        refractedAngle = 0.0;
      }

      for (const auto& gate : paut["gates"].GetArray())
      {
        double gateStart{};
        if (gate.HasMember("start"))
        {
          gateStart = gate["start"].GetDouble();
        }
        else if (gate.HasMember("starts"))
        {
          gateStart = gate["starts"].GetArray()[0].GetDouble();
        }

        gateStart = 0.0;
      }

      // Probe and acquisition unit
      if (paut.HasMember("pulseEcho"))
      {
        uint64_t probeId = paut["pulseEcho"]["probeId"].GetUint64();
        if (jsonDoc.HasMember("probes"))
        {
          if (const auto probe = std::find_if(jsonDoc["probes"].GetArray().Begin(), jsonDoc["probes"].GetArray().End(),
            [&](auto& probe_) { return probe_["id"].GetUint64() == probeId; }))
          {
            std::string model = (*probe)["model"].GetString();
            if (probe->HasMember("phasedArrayLinear"))
            {
              auto& firstElement = (*probe)["phasedArrayLinear"]["elements"].GetArray()[0];
              uint64_t acquisitionUnitId = firstElement["acquisitionUnitId"].GetUint64();
              std::string connectorName = firstElement["connectorName"].GetString();
              uint64_t pinId = firstElement["pinId"].GetUint64();

              if (jsonDoc.HasMember("acquisitionUnits"))
              {
                if (const auto acquisitionUnit = std::find_if(jsonDoc["acquisitionUnits"].GetArray().Begin(), jsonDoc["acquisitionUnits"].GetArray().End(),
                  [&](auto& acquisitionUnit_) { return acquisitionUnit_["id"].GetUint64() == acquisitionUnitId; }))
                {
                  std::string platform = (*acquisitionUnit)["platform"].GetString();
                  double acqRate = (*acquisitionUnit)["acquisitionRate"].GetDouble();
                  acqRate = 0.0;
                }
              }
            }

            // Wedge position and specimen material
            if (probe->HasMember("wedgeAssociation"))
            {
              uint64_t wedgeId = (*probe)["wedgeAssociation"]["wedgeId"].GetUint64();
              if (jsonDoc.HasMember("wedges"))
              {
                if (const auto wedge = std::find_if(jsonDoc["wedges"].GetArray().Begin(), jsonDoc["wedges"].GetArray().End(),
                  [&](auto& wedge_) { return wedge_["id"].GetUint64() == wedgeId; }))
                {
                  double uCoordinateOffset = (*wedge)["positioning"]["uCoordinateOffset"].GetDouble();
                  double vCoordinateOffset = (*wedge)["positioning"]["vCoordinateOffset"].GetDouble();
                  double skewAngle = (*wedge)["positioning"]["skewAngle"].GetDouble();

                  uint64_t specimenId = (*wedge)["positioning"]["specimenId"].GetUint64();
                  if (jsonDoc.HasMember("specimens"))
                  {
                    if (const auto specimen = std::find_if(jsonDoc["specimens"].GetArray().Begin(), jsonDoc["specimens"].GetArray().End(),
                      [&](auto& specimen_) { return specimen_["id"].GetUint64() == specimenId; }))
                    {
                      if (specimen->HasMember("plateGeometry"))
                      {
                        std::string materialName = (*specimen)["plateGeometry"]["material"]["name"].GetString();
                        materialName.clear();
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }

      // Data encoding and motion device
      if (jsonDoc.HasMember("dataEncodings"))
      {
        uint64_t dataEncodingId = paut["dataEncodingId"].GetUint64();
        if (const auto dataEncoding = std::find_if(jsonDoc["dataEncodings"].GetArray().Begin(), jsonDoc["dataEncodings"].GetArray().End(),
          [&](auto& dataEncoding_) { return dataEncoding_["id"].GetUint64() == dataEncodingId; }))
        {
          if (dataEncoding->HasMember("discreteGrid"))
          {
            auto& discreteGrid = (*dataEncoding)["discreteGrid"];
            for (const auto& dimension : discreteGrid["dimensions"].GetArray())
            {
              std::string axisName = dimension["axis"].GetString();
              uint64_t quantity = dimension["quantity"].GetUint64();
              double resolution = dimension["resolution"].GetDouble();
              double offset = dimension["offset"].GetDouble();

              if (jsonDoc.HasMember("motionDevices"))
              {
                uint64_t motionDeviceId = dimension["motionDeviceId"].GetUint64();
                if (const auto motionDevice = std::find_if(jsonDoc["motionDevices"].GetArray().Begin(), jsonDoc["motionDevices"].GetArray().End(),
                  [&](auto& motionDevice_) { return motionDevice_["id"].GetUint64() == motionDeviceId; }))
                {
                  if (motionDevice->HasMember("encoder"))
                  {
                    double stepResolution = (*motionDevice)["encoder"]["stepResolution"].GetDouble();
                    stepResolution = 0.0;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  errorCode = H5Fclose(fileId);

  return EXIT_SUCCESS;
}
