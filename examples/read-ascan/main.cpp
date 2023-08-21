#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <optional>
#include <algorithm>
#include <string>

#include <hdf5.h>
#include <rapidjson/schema.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace rj = rapidjson;
namespace fs = std::filesystem;

// forwards
struct Color {
  uint8_t R, G, B;
};

struct BeamDescription
{
  double Velocity{};
  double SkewAngle{};
  double RefractedAngle{};
  std::optional<double> UCoordinateOffset{};
  std::optional<double> VCoordinateOffset{};
  std::optional<double> UltrasoundOffset{};
};

struct DimensionAxis
{
  std::string Name;
  uint64_t Quantity{};
  std::optional<double> Resolution{};
  std::optional<double> Offset{};

};

struct AmplitudeRange
{
  double PercentMin{};
  double PercentMax{};
  int64_t SamplingMin{};
  int64_t SamplingMax{};
};

struct AscanData
{
  AmplitudeRange AmplitudeRng;

  std::optional<double> Velocity{};
  std::optional<double> SkewAngle{};
  std::optional<double> RefractedAngle{};

  std::vector<DimensionAxis> AmplitudeAxes;
  std::vector<int16_t> Amplitudes;

  std::vector<DimensionAxis> StatusAxes;
  std::vector<uint8_t> Statuses;

  std::optional<std::vector<BeamDescription>> BeamDescriptions;
};

std::string ReadJsonSetup(hid_t fileId_);
rj::ParseErrorCode validate(const std::string& jsonSetup_, std::ifstream& fileStream_);
void ParseAscanStatuses(const rj::Value& jsonAscanData_, const AscanData& ascanData_);
AscanData ReadAscanData(hid_t fileId_, const rj::Value& ascanDataset_);
void ExportEndView(const fs::path& pathName_, const std::string& groupName_, const AscanData& ascanData_);


// Run create-file example before to create a .nde file.
// 
// launch.vs.json
// "args": [
//   "../../scenarios/general-mapping/oneline-scan-plate-paut-linear.nde",
//   "-e"
// ]

int main(int argc_, char** argv_)
{
  if (argc_ == 1) {
   return EXIT_FAILURE;
  }

  std::string inputPathFilename = argv_[1];
  inputPathFilename.erase(remove(inputPathFilename.begin(), inputPathFilename.end(), '\"'), inputPathFilename.end());
  if (!fs::exists(inputPathFilename)) {
    return EXIT_FAILURE;
  }

  bool exportImage{ true };
  if (argc_ > 2)
  {
    std::string arg = argv_[2];
    exportImage = arg.find("-e") != std::string::npos;
  }

  hid_t fileId = H5Fopen(inputPathFilename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);

  // Read JSON metadata
  rj::Document jsonDoc;
  std::string jsonSetup = ReadJsonSetup(fileId);

  // Schema validation
  //fs::path rootPath = fs::current_path() / "../..";
  //fs::path schemaPathFilename = rootPath / "schemas/NDE-FileFormat-Schema-3.0.0-Beta.json";
  //fs::path schemaPathFilename = "C:\\Dev\\nde-format\\schemas\\NDE-FileFormat-Schema-3.1.0.json";
  fs::path schemaPathFilename = "C:\\Dev\\nde-format\\schemas\\NDE-FileFormat-Schema-3.2.0.json";

  auto file = std::ifstream(schemaPathFilename);
  if (validate(jsonSetup, file))
  {
    // Read data
    jsonDoc.Parse(jsonSetup.c_str());
    for (const auto& group : jsonDoc["groups"].GetArray())
    {
      if (group["dataset"].HasMember("ascan"))
      {
        auto& ascanDataset = group["dataset"]["ascan"];

        const AscanData& ascanData = ReadAscanData(fileId, ascanDataset);
        ParseAscanStatuses(ascanDataset, ascanData);

        if (exportImage) {
          ExportEndView(fs::path(inputPathFilename).parent_path(), group["name"].GetString(), ascanData);
        }
      }
    }

    herr_t errorCode = H5Fclose(fileId);
    return EXIT_SUCCESS;
  }

  return EXIT_FAILURE;
}

std::string ReadJsonSetup(hid_t fileId_)
{
  hid_t propId = H5Pcreate(H5P_DATASET_ACCESS);
  hid_t dsetId = H5Dopen(fileId_, "/Domain/Setup", propId);
  hid_t dataType = H5Dget_type(dsetId);
  std::vector<char> json(H5Tget_size(dataType));
  herr_t errorCode = H5Dread(dsetId, dataType, H5S_ALL, H5S_ALL, H5P_DEFAULT, json.data());
  errorCode = H5Dclose(dsetId);

  return std::string(json.begin(), json.end());
}


rj::ParseErrorCode validate(const std::string& jsonSetup_, std::ifstream& fileStream_)
{
  rj::Document setupJsonDoc;
  if (setupJsonDoc.Parse(jsonSetup_.c_str()).HasParseError()) {
    return setupJsonDoc.GetParseError();
  }

  rj::Document schemaJsonDoc;
  rj::IStreamWrapper isw(fileStream_);
  if (schemaJsonDoc.ParseStream(isw).HasParseError()) {
    return schemaJsonDoc.GetParseError();
  }

  auto schemaDoc = rj::SchemaDocument(schemaJsonDoc);
  auto schemaValidator = rj::SchemaValidator(schemaDoc);
  if (!setupJsonDoc.Accept(schemaValidator))
  {
    // Input JSON is invalid according to the schema
    // Output diagnostic information
    rj::StringBuffer error;
    schemaValidator.GetInvalidSchemaPointer().StringifyUriFragment(error);
    printf("Invalid schema: %s\n", error.GetString());
    printf("Invalid keyword: %s\n", schemaValidator.GetInvalidSchemaKeyword());
    error.Clear();
    schemaValidator.GetInvalidDocumentPointer().StringifyUriFragment(error);
    printf("Invalid document: %s\n", error.GetString());

    return rj::kParseErrorValueInvalid;
  }

  return rj::kParseErrorNone;
}

AscanData ReadAscanData(hid_t fileId_, const rj::Value& ascanDataset_)
{
  AscanData ascanData;

  auto& amplitude = ascanDataset_["amplitude"];
  ascanData.AmplitudeRng.PercentMin = amplitude["dataValue"]["min"].GetDouble();
  ascanData.AmplitudeRng.PercentMax = amplitude["dataValue"]["max"].GetDouble();
  ascanData.AmplitudeRng.SamplingMin = amplitude["dataSampling"]["min"].GetInt64();
  ascanData.AmplitudeRng.SamplingMax = amplitude["dataSampling"]["max"].GetInt64();

  for (const auto& dimension : amplitude["dimensions"].GetArray())
  {
    DimensionAxis dimAxis;
    dimAxis.Name = dimension["axis"].GetString();

    if (dimAxis.Name == "UCoordinate")
    {
      if (dimension.HasMember("offset")) {
        dimAxis.Offset = dimension["offset"].GetDouble();
      }

      dimAxis.Quantity = dimension["quantity"].GetUint64();
      dimAxis.Resolution = dimension["resolution"].GetDouble();
      ascanData.AmplitudeAxes.push_back(dimAxis);
      ascanData.StatusAxes.push_back(dimAxis);
    }
    else if (dimAxis.Name == "VCoordinate")
    {
      dimAxis.Quantity = dimension["quantity"].GetUint64();
      dimAxis.Offset = dimension["offset"].GetDouble();
      dimAxis.Resolution = dimension["resolution"].GetDouble();
      ascanData.AmplitudeAxes.push_back(dimAxis);
      ascanData.StatusAxes.push_back(dimAxis);

      ascanData.Velocity = ascanDataset_["velocity"].GetDouble();
      ascanData.SkewAngle = ascanDataset_["skewAngle"].GetDouble();
      ascanData.RefractedAngle = ascanDataset_["refractedAngle"].GetDouble();
    }
    else if (dimAxis.Name == "Ultrasound")
    {
      if (dimension.HasMember("offset")) {
        dimAxis.Offset = dimension["offset"].GetDouble();
      }

      dimAxis.Quantity = dimension["quantity"].GetUint64();
      dimAxis.Resolution = dimension["resolution"].GetDouble();
      ascanData.AmplitudeAxes.push_back(dimAxis);
    }
    else if (dimAxis.Name == "Beam")
    {
      std::vector<BeamDescription> beamDescriptions;
      for (const auto& beam : dimension["beams"].GetArray())
      {
        BeamDescription beamDescription;
        beamDescription.Velocity = beam["velocity"].GetDouble();
        beamDescription.SkewAngle = beam["skewAngle"].GetDouble();
        beamDescription.RefractedAngle = beam["refractedAngle"].GetDouble();
        beamDescription.UCoordinateOffset = beam["uCoordinateOffset"].GetDouble();
        beamDescription.VCoordinateOffset = beam["vCoordinateOffset"].GetDouble();
        beamDescription.UltrasoundOffset = beam["ultrasoundOffset"].GetDouble();
        beamDescriptions.push_back(beamDescription);
      }

      dimAxis.Quantity = dimension["beams"].GetArray().Size();
      ascanData.BeamDescriptions.emplace(beamDescriptions);
      ascanData.AmplitudeAxes.push_back(dimAxis);
      ascanData.StatusAxes.push_back(dimAxis);
    }
  }

  // Open amplitude dataset
  std::string dsetJsonPath = amplitude["path"].GetString();
  hid_t propId = H5Pcreate(H5P_DATASET_ACCESS);
  hid_t dsetId = H5Dopen(fileId_, dsetJsonPath.c_str(), propId);

  hid_t dspaceId = H5Dget_space(dsetId);
  int rank = H5Sget_simple_extent_ndims(dspaceId);
  std::vector<uint64_t> dimensions(rank);
  H5Sget_simple_extent_dims(dspaceId, dimensions.data(), nullptr);

  // Read amplitude dataset
  ascanData.Amplitudes.resize(H5Sget_simple_extent_npoints(dspaceId));
  herr_t errorCode = H5Dread(dsetId, H5Dget_type(dsetId), dspaceId, dspaceId, H5P_DEFAULT, ascanData.Amplitudes.data());
  errorCode = H5Sclose(dspaceId);
  errorCode = H5Dclose(dsetId);

  // Open status dataset
  dsetJsonPath = ascanDataset_["status"]["path"].GetString();
  propId = H5Pcreate(H5P_DATASET_ACCESS);
  dsetId = H5Dopen(fileId_, dsetJsonPath.c_str(), propId);

  dspaceId = H5Dget_space(dsetId);
  rank = H5Sget_simple_extent_ndims(dspaceId);
  dimensions = std::vector<uint64_t>(rank);
  H5Sget_simple_extent_dims(dspaceId, dimensions.data(), nullptr);

  // Read status dataset
  ascanData.Statuses.resize(H5Sget_simple_extent_npoints(dspaceId));
  errorCode = H5Dread(dsetId, H5Dget_type(dsetId), dspaceId, dspaceId, H5P_DEFAULT, ascanData.Statuses.data());
  errorCode = H5Sclose(dspaceId);
  errorCode = H5Dclose(dsetId);

  return ascanData;
}

std::vector<Color> CreateColorPalette()
{
  std::vector<Color> colors;
  std::vector<Color> everyColors;
  colors.emplace_back(Color{255, 255, 255});
  colors.emplace_back(Color{184, 212, 244});
  colors.emplace_back(Color{113, 170, 233});
  colors.emplace_back(Color{62, 105, 190});
  colors.emplace_back(Color{14, 37, 143});
  colors.emplace_back(Color{27, 72, 129});
  colors.emplace_back(Color{59, 140, 127});
  colors.emplace_back(Color{126, 187, 94});
  colors.emplace_back(Color{211, 223, 45});
  colors.emplace_back(Color{241, 211, 43});
  colors.emplace_back(Color{222, 156, 80});
  colors.emplace_back(Color{209, 121, 87});
  colors.emplace_back(Color{205, 116, 49});
  colors.emplace_back(Color{194, 98, 23});
  colors.emplace_back(Color{167, 50, 26});
  colors.emplace_back(Color{145, 12, 29});

  size_t interpolationPoints = 7;
  double f = 1.0 / interpolationPoints;

  for (size_t colorIdx(0); colorIdx < colors.size() - 1; colorIdx++)
  {
    Color x = colors[colorIdx];
    Color y = colors[colorIdx + 1];

    for (size_t j(0); j < interpolationPoints; j++)
    {
      uint8_t r = static_cast<uint8_t>(x.R + (y.R - x.R) * (j * f));
      uint8_t g = static_cast<uint8_t>(x.G + (y.G - x.G) * (j * f));
      uint8_t b = static_cast<uint8_t>(x.B + (y.B - x.B) * (j * f));

      everyColors.emplace_back(Color{r, g, b});
    }
  }

  return everyColors;
}

void ParseAscanStatuses(const rj::Value& ascanDataset_, const AscanData& ascanData_)
{
  uint8_t hasDataMask{};
  auto& dataValue = ascanDataset_["status"]["dataValue"];

  if (dataValue.HasMember("hasData")) {
    hasDataMask = 1 << dataValue["hasData"].GetUint();
  }

  uint8_t synchedMask{};
  if (dataValue.HasMember("synched")) {
    synchedMask = 1 << dataValue["synched"].GetUint();
  }

  for (uint64_t dim0{}; dim0 < ascanData_.StatusAxes[0].Quantity; dim0++) {
    for (uint64_t dim1{}; dim1 < ascanData_.StatusAxes[1].Quantity; dim1++)
    {
      uint64_t cell = dim1 + dim0 * ascanData_.StatusAxes[1].Quantity;
      bool hasDataStatus = ascanData_.Statuses[cell] & hasDataMask;
      bool synchedStatus = ascanData_.Statuses[cell] & synchedMask;
      hasDataStatus = hasDataStatus = false;
    }
  }
}

void ExportEndView(const fs::path& pathName_, const std::string& groupName_, const AscanData& ascanData_)
{
  uint64_t dimSize1 = ascanData_.AmplitudeAxes[1].Quantity;
  uint64_t dimSize2 = ascanData_.AmplitudeAxes[2].Quantity;
  std::vector<std::vector<uint64_t>> image(dimSize1, std::vector<uint64_t>(dimSize2));

  // Compute linear offset in dim1/dim2 plan at dim0
  uint64_t x = 0;
  for (uint64_t dim1{}; dim1 < dimSize1; dim1++) {
    for (uint64_t dim2{}; dim2 < dimSize2; dim2++) {
      image[dim1][dim2] = dim2 + dim1 * dimSize2 + x * dimSize1 * dimSize2;
    }
  }

  std::string filename = "End view - ScanPos " + std::to_string(x) + " - " + groupName_ + ".ppm";
  fs::path pathFilename = pathName_ / filename;

  std::ofstream imageFile;
  imageFile.open(pathFilename, std::ios::out | std::ios::app);
  imageFile << "P3" << std::endl;
  imageFile << dimSize1 << " " << dimSize2 << std::endl;
  imageFile << "255" << std::endl;

  std::vector<Color> everyColors = CreateColorPalette();

  for (uint64_t dim2{}; dim2 < dimSize2; dim2++) {
    for (uint64_t dim1{}; dim1 < dimSize1; dim1++)
    {
      int16_t samplingAmplitude = std::abs(ascanData_.Amplitudes[image[dim1][dim2]]);
      double percentAmplitude = samplingAmplitude / (32768 / 100.0);

      Color color = everyColors[static_cast<int16_t>(percentAmplitude)];
      imageFile << std::left << std::setw(4) << std::to_string(color.R);
      imageFile << std::left << std::setw(4) << std::to_string(color.G);
      imageFile << std::left << std::setw(4) << std::to_string(color.B);
      imageFile << std::endl;
    }
  }

  imageFile.close();
}
