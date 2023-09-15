#include "FileFormatChanges_3_0_0.h"

#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>

#include "FileFormat.h"


std::string NDE::FileFormatChanges_3_0_0::Version = NDE::VERSION_3_0_0;

NDE::TResult<std::string> NDE::FileFormatChanges_3_0_0::ApplyChanges(const std::string& jsonSetup_) const
{
  rj::Document jsonSetupDoc;
  if (!jsonSetupDoc.Parse(jsonSetup_).HasParseError())
  {
    rj::Document newJsonSetupDoc;
    auto& allocator = newJsonSetupDoc.GetAllocator();

    newJsonSetupDoc.CopyFrom(jsonSetupDoc, allocator);

    if (newJsonSetupDoc.HasMember("$schema")) {
      newJsonSetupDoc.RemoveMember("$schema");
    }

    newJsonSetupDoc.RemoveMember("dataGroups");
    newJsonSetupDoc.RemoveMember("motionDevices");
    newJsonSetupDoc.RemoveMember("processes");

    for (rj::SizeType specimenIdx{}; specimenIdx < newJsonSetupDoc["specimens"].GetArray().Size(); specimenIdx++)
    {
      if (auto attenuationCoefficient = rj::Pointer("/specimens/" + std::to_string(specimenIdx) + "/plateGeometry/material/longitudinalWave/attenuationCoefficient").Get(jsonSetupDoc))
      {
        if (attenuationCoefficient->GetDouble() == 0.0) {
          newJsonSetupDoc["specimens"][specimenIdx]["plateGeometry"]["material"]["longitudinalWave"].RemoveMember("attenuationCoefficient");
        }
      }

      if (auto attenuationCoefficient = rj::Pointer("/specimens/" + std::to_string(specimenIdx) + "/plateGeometry/material/transversalVerticalWave/attenuationCoefficient").Get(jsonSetupDoc))
      {
        if (attenuationCoefficient->GetDouble() == 0.0) {
          newJsonSetupDoc["specimens"][specimenIdx]["plateGeometry"]["material"]["transversalVerticalWave"].RemoveMember("attenuationCoefficient");
        }
      }
    }

    for (auto& acquisitionUnit : newJsonSetupDoc["acquisitionUnits"].GetArray())
    {
      uint64_t id = acquisitionUnit["id"].GetUint64();
      if (acquisitionUnit.HasMember("focusPX"))
      {
        acquisitionUnit.CopyFrom(acquisitionUnit["focusPX"], allocator);
        acquisitionUnit.AddMember("id", id, allocator);
        auto acquisitionRate = acquisitionUnit.FindMember("acquisitionPace");
        acquisitionRate->name.SetString("acquisitionRate", allocator);
        acquisitionUnit.AddMember("platform", "FocusPX", allocator);
        acquisitionUnit.RemoveMember("focusPX");
      }
      else if (acquisitionUnit.HasMember("omniScanX3"))
      {
        acquisitionUnit.CopyFrom(acquisitionUnit["omniScanX3"], allocator);
        acquisitionUnit.AddMember("id", id, allocator);
        auto acquisitionRate = acquisitionUnit.FindMember("acquisitionPace");
        acquisitionRate->name.SetString("acquisitionRate", allocator);
        acquisitionUnit.AddMember("platform", "OmniScanX3", allocator);
        acquisitionUnit.RemoveMember("omniScanX3");
      }

      if (!acquisitionUnit.HasMember("model")) {
        acquisitionUnit.AddMember("model", "Unknown", allocator);
      }

      if (acquisitionUnit.HasMember("serialNumber") && acquisitionUnit["serialNumber"].GetStringLength() == 0) {
        acquisitionUnit.RemoveMember("serialNumber");
      }
    }

    for (auto& probe : newJsonSetupDoc["probes"].GetArray())
    {
      if (probe.HasMember("fluidColumn"))
      {
        auto nominalThickness = probe["fluidColumn"].FindMember("nominalThickness");
        if (nominalThickness != probe["fluidColumn"].MemberEnd()) {
          nominalThickness->name.SetString("nominalHeight", jsonSetupDoc.GetAllocator());
        }
      }
    }

    if (!newJsonSetupDoc["dataEncodings"].Empty())
    {
      newJsonSetupDoc["dataEncodings"][0]["discreteGrid"].RemoveMember("storage");
      newJsonSetupDoc["dataEncodings"][0]["discreteGrid"].RemoveMember("oneLineScan");
      newJsonSetupDoc["dataEncodings"][0]["discreteGrid"].RemoveMember("rasterScan");

      // Erase all elements except the first one
      newJsonSetupDoc["dataEncodings"].Erase(newJsonSetupDoc["dataEncodings"].GetArray().Begin() + 1, newJsonSetupDoc["dataEncodings"].GetArray().End());
    }
    
    //

    rj::Value groups(rj::kArrayType);
    for (rj::SizeType dataGroupIdx{}; dataGroupIdx < jsonSetupDoc["dataGroups"].GetArray().Size() && dataGroupIdx < 1; dataGroupIdx++)
    {
      const auto& dataGroup = jsonSetupDoc["dataGroups"][dataGroupIdx];
      rj::Value group(rj::kObjectType);
      group.AddMember("id", dataGroup["id"].GetUint64(), allocator);
      group.AddMember("name", rj::StringRef(dataGroup["name"].GetString()), allocator);

      if (dataGroup["ultrasound"].HasMember("linearPulseEcho"))
      {
        rj::Document paut;
        const auto& linearPulseEcho = dataGroup["ultrasound"]["linearPulseEcho"];
        paut.CopyFrom(linearPulseEcho, allocator);
        paut.RemoveMember("probeId");
        paut.RemoveMember("probeFirstElementId");
        paut.RemoveMember("probeLastElementId");
        paut.RemoveMember("elementStep");
        paut.RemoveMember("elementAperture");
        paut.RemoveMember("beamRefractedAngle");
        paut.RemoveMember("datasets");
        paut.RemoveMember("amplitudeAxis");
        paut.RemoveMember("amplitudePercentAxis");

        //
        
        paut.AddMember("dataEncodingId", 0, allocator);

        rj::Value pulseEcho(rj::kObjectType);
        pulseEcho.AddMember("probeId", linearPulseEcho["probeId"].GetUint64(), allocator);

        rj::Value LinearFormation(rj::kObjectType);
        LinearFormation.AddMember("probeFirstElementId", linearPulseEcho["probeFirstElementId"].GetUint64(), allocator);
        LinearFormation.AddMember("probeLastElementId", linearPulseEcho["probeLastElementId"].GetUint64(), allocator);
        LinearFormation.AddMember("elementStep", linearPulseEcho["elementStep"].GetDouble(), allocator);
        LinearFormation.AddMember("elementAperture", linearPulseEcho["elementAperture"].GetUint(), allocator);
        LinearFormation.AddMember("beamRefractedAngle", 0.0, allocator);
        pulseEcho.AddMember("linearFormation", LinearFormation, allocator);
        paut.AddMember("pulseEcho", pulseEcho, allocator);

        rj::Value pulse(rj::kObjectType);
        pulse.AddMember("width", linearPulseEcho["pulseWidth"].GetDouble(), allocator);
        pulse.AddMember("voltage", linearPulseEcho["pulseVoltage"].GetDouble(), allocator);
        if (linearPulseEcho.HasMember("pulsePolarity")) {
          pulse.AddMember("polarity", rj::StringRef(linearPulseEcho["pulsePolarity"].GetString()), allocator);
        }
        paut.AddMember("pulse", pulse, allocator);

        paut.RemoveMember("pulsePolarity");
        paut.RemoveMember("pulseWidth");
        paut.RemoveMember("pulseVoltage");

        if (paut.HasMember("digitalBandPassFilter"))
        {
          auto memberItr = paut["digitalBandPassFilter"].FindMember("filterType");
          if (memberItr != paut["digitalBandPassFilter"].MemberEnd())
          {
            if (memberItr->value == "Low-pass") {
              memberItr->value.SetString("LowPass", allocator);
            }
            else if (memberItr->value == "High-pass") {
              memberItr->value.SetString("HighPass", allocator);
            }
            else if (memberItr->value == "Band-pass") {
              memberItr->value.SetString("BandPass", allocator);
            }
          }
        }

        if (paut.HasMember("averaging"))
        {
          auto memberItr = paut.FindMember("averaging");
          if (memberItr != paut.MemberEnd())
          {
            memberItr->name.SetString("averagingFactor", allocator);
          }
        }

        paut.AddMember("highAmplitude", linearPulseEcho["amplitudePercentAxis"]["max"].GetDouble(), allocator);
        paut.AddMember("digitizingFrequency", 100e6, allocator);

        bool memberFound{};
        std::string ascanSynchroMode;
        for (auto itr = paut.MemberBegin(); itr < paut.MemberEnd(); ++itr)
        {
          if (itr->name == "ascanSynchroMode")
          {
            ascanSynchroMode = itr->value.GetString();
            if (memberFound) {
              paut.EraseMember(itr);
            }
            memberFound = true;
          }
        }

        paut["ascanSynchroMode"].SetString(ascanSynchroMode, allocator);
         
        const auto& beam = linearPulseEcho["beams"][0];
        const auto& gates = beam["gates"];
        for (rj::SizeType gateIdx{}; gateIdx < gates.GetArray().Size(); gateIdx++)
        {
          paut["gates"][gateIdx].CopyFrom(linearPulseEcho["gates"][gateIdx], allocator);
          paut["gates"][gateIdx].AddMember("start", gates[gateIdx]["start"].GetDouble(), allocator);
          paut["gates"][gateIdx].AddMember("length", gates[gateIdx]["length"].GetDouble(), allocator);
          paut["gates"][gateIdx].AddMember("threshold", gates[gateIdx]["threshold"].GetDouble(), allocator);

          if (paut["gates"][gateIdx]["timeSelection"].GetStringLength() == 0) {
            paut["gates"][gateIdx]["timeSelection"].SetString("Unselected", allocator);
          }

          std::string synchroMode = paut["gates"][gateIdx]["synchronization"]["mode"].GetString();
          if (synchroMode == "SynchroGateRelative") {
            paut["gates"][gateIdx]["synchronization"]["mode"].SetString("GateRelative");
          }

        }

        std::string tcgSynchroMode("AscanSynchroRelative");
        if (paut.HasMember("tcgSynchroMode")) {
          tcgSynchroMode = paut["tcgSynchroMode"].GetString();
          paut.RemoveMember("tcgSynchroMode");
        }

        if (tcgSynchroMode == "SynchroGateRelative") {
          tcgSynchroMode = "AscanSynchroRelative";
        }

        for (auto& beam : paut["beams"].GetArray())
        {
          beam.AddMember("ascanStart", beam["ultrasoundAxis"]["ascanStart"].GetDouble(), allocator);
          beam.AddMember("ascanLength", beam["ultrasoundAxis"]["ascanLength"].GetDouble(), allocator);
          double resolution = beam["ultrasoundAxis"]["ascanResolution"].GetDouble();

          if (beam.HasMember("tcg"))
          {
            if (beam["tcg"]["points"].GetArray().Size())
            {
              beam["tcg"].AddMember("enabled", true, allocator);
              beam["tcg"].AddMember("synchroMode", tcgSynchroMode, allocator);
            }
            else
            {
              beam.RemoveMember("tcg");
            }
          }

          if (beam.HasMember("pulsers")) {
            if (beam["pulsers"].GetArray().Size() == 0) {
              beam.RemoveMember("pulsers");
            }
            else {
              if (!beam["pulsers"][0].HasMember("delay")) {
                beam.RemoveMember("pulsers");
              }
            }
          }

          if (beam.HasMember("receivers")) {
            if (beam["receivers"].GetArray().Size() == 0) {
              beam.RemoveMember("receivers");
            }
            else {
              if (!beam["receivers"][0].HasMember("delay")) {
                beam.RemoveMember("receivers");
              }
            }
          }

          beam.RemoveMember("xImagingExitPoint");
          beam.RemoveMember("yImagingExitPoint");
          beam.RemoveMember("ultrasoundAxis");
          beam.RemoveMember("pulseWidth");
          beam.RemoveMember("pulseVoltage");
          beam.RemoveMember("gates");
        }

        // softwareProcess

        rj::Value softwareProcess(rj::kObjectType);
        if (paut.HasMember("analysisGain"))
        {
          softwareProcess.AddMember("gain", paut["analysisGain"].GetDouble(), allocator);
          paut.RemoveMember("analysisGain");
        }

        if (paut.HasMember("analysisGates"))
        {
          rj::Value gates(rj::kArrayType);
          gates.CopyFrom(paut["gates"], allocator);
          softwareProcess.AddMember("gates", gates, allocator);
          paut.RemoveMember("analysisGates");

          for (rj::SizeType beamIdx{}; beamIdx < paut["beams"].GetArray().Size(); beamIdx++)
          {
            if (beamIdx == 0)
            {
              for (rj::SizeType gateIdx{}; gateIdx < paut["beams"][beamIdx]["analysisGates"].GetArray().Size(); gateIdx++)
              {
                softwareProcess["gates"][gateIdx].AddMember("start", paut["beams"][beamIdx]["analysisGates"][gateIdx]["start"], allocator);
                softwareProcess["gates"][gateIdx].AddMember("length", paut["beams"][beamIdx]["analysisGates"][gateIdx]["length"], allocator);
                softwareProcess["gates"][gateIdx].AddMember("threshold", paut["beams"][beamIdx]["analysisGates"][gateIdx]["threshold"], allocator);
              }
            }
            
            paut["beams"][beamIdx].RemoveMember("analysisGates");
          }
        }

        if (paut.HasMember("analysisTcgEnabled"))
        {
          rj::Value tcg(rj::kObjectType);
          tcg.AddMember("enabled", paut["analysisTcgEnabled"], allocator);
          paut.RemoveMember("analysisTcgEnabled");

          for (rj::SizeType beamIdx{}; beamIdx < paut["beams"].GetArray().Size(); beamIdx++)
          {
            if (beamIdx == 0) {
              tcg.AddMember("points", paut["beams"][beamIdx]["analysisTcg"]["points"], allocator);
            }

            paut["beams"][beamIdx].RemoveMember("analysisTcg");
          }
          softwareProcess.AddMember("tcg", tcg, allocator);
        }

        if (softwareProcess.MemberCount() > 0) {
          paut.AddMember("softwareProcess", softwareProcess, allocator);
        }

        // Ascan

        rj::Value dataset(rj::kObjectType);
        dataset.AddMember("storageMode", "Paintbrush", allocator);

        
        const auto& datasets = linearPulseEcho["datasets"];
        auto datasetItr = std::find_if(datasets.Begin(), datasets.End(), [&](const auto& dataset) { return dataset.HasMember("ascan"); });
        if (datasetItr != datasets.End())
        {
          rj::Value ascan(rj::kObjectType);
          ascan.AddMember("velocity", linearPulseEcho["velocity"].GetDouble(), allocator);
          ascan.AddMember("skewAngle", beam["skewAngle"].GetDouble(), allocator);
          ascan.AddMember("refractedAngle", beam["refractedAngle"].GetDouble(), allocator);

          rj::Value amplitude(rj::kObjectType);
          const auto& ascanDset = (*datasetItr)["ascan"];
          amplitude.AddMember("path", rj::StringRef(ascanDset["amplitudeDatasetPath"].GetString()), allocator);

          rj::Value dataValue(rj::kObjectType);
          dataValue.AddMember("unit", "Percent", allocator);
          dataValue.AddMember("min", linearPulseEcho["amplitudePercentAxis"]["min"].GetDouble(), allocator);
          dataValue.AddMember("max", linearPulseEcho["amplitudePercentAxis"]["max"].GetDouble(), allocator);
          amplitude.AddMember("dataValue", dataValue, allocator);

          rj::Value dataSampling(rj::kObjectType);
          dataSampling.AddMember("min", ascanDset["amplitudeSamplingAxis"]["min"].GetInt(), allocator);
          dataSampling.AddMember("max", ascanDset["amplitudeSamplingAxis"]["max"].GetInt(), allocator);
          amplitude.AddMember("dataSampling", dataSampling, allocator);

          ascan.AddMember("amplitude", amplitude, allocator);

          rj::Value status(rj::kObjectType);
          status.AddMember("path", rj::StringRef(ascanDset["statusDatasetPath"].GetString()), allocator);

          dataValue = rj::Value(rj::kObjectType);
          dataValue.AddMember("unit", "Bitfield", allocator);
          const auto statuses = ascanDset["statuses"].GetArray();
          for (rj::SizeType statusIdx{}; statusIdx < statuses.Size(); statusIdx++)
          {
            std::string status = std::string(statuses[statusIdx].GetString());
            if (status == "HasData") {
              dataValue.AddMember("hasData", 1 << statusIdx, allocator);
            }
            if (status == "Synched" || status == "Synced") {
              dataValue.AddMember("noSynchro", 1 << statusIdx, allocator);
            }
            if (status == "Saturated") {
              dataValue.AddMember("saturated", 1 << statusIdx, allocator);
            }
          }

          status.AddMember("dataValue", dataValue, allocator);

          ascan.AddMember("status", status, allocator);

          rj::Value dimensions(rj::kArrayType);
          rj::Value scanPattern(rj::kObjectType);
          const auto& discreteGrid = jsonSetupDoc["dataEncodings"][0]["discreteGrid"];
          if (discreteGrid.HasMember("oneLineScan")) {
            scanPattern.CopyFrom(discreteGrid["oneLineScan"], allocator);
          }
          else if (discreteGrid.HasMember("rasterScan")) {
            scanPattern.CopyFrom(discreteGrid["rasterScan"], allocator);
          }

          double offset = scanPattern["uCoordinateAxis"]["origin"].GetDouble();
          double length = scanPattern["uCoordinateAxis"]["length"].GetDouble();
          double resolution = scanPattern["uCoordinateAxis"]["resolution"].GetDouble();
          uint32_t quantity = std::lroundl(length / resolution) + 1;

          rj::Value dim0(rj::kObjectType);
          dim0.AddMember("axis", "UCoordinate", allocator);
          dim0.AddMember("quantity", quantity, allocator);
          dim0.AddMember("resolution", resolution, allocator);
          dim0.AddMember("offset", offset, allocator);
          dimensions.PushBack(dim0, allocator);

          offset = scanPattern["vCoordinateAxis"]["origin"].GetDouble();
          length = scanPattern["vCoordinateAxis"]["length"].GetDouble();
          resolution = scanPattern["vCoordinateAxis"]["resolution"].GetDouble();
          quantity = std::lroundl(length / resolution) + 1;

          rj::Value dim1(rj::kObjectType);
          dim1.AddMember("axis", "VCoordinate", allocator);
          dim1.AddMember("quantity", quantity, allocator);
          dim1.AddMember("resolution", resolution, allocator);
          dim1.AddMember("offset", offset, allocator);
          dimensions.PushBack(dim1, allocator);

          offset = beam["ultrasoundAxis"]["ascanStart"].GetDouble();
          length = beam["ultrasoundAxis"]["ascanLength"].GetDouble();
          double ascanResolution = beam["ultrasoundAxis"]["ascanResolution"].GetDouble();
          quantity = std::lroundl(length / ascanResolution);

          rj::Value dim2(rj::kObjectType);
          dim2.AddMember("axis", "Ultrasound", allocator);
          dim2.AddMember("quantity", quantity, allocator);
          dim2.AddMember("resolution", ascanResolution, allocator);
          dim2.AddMember("offset", offset, allocator);
          dimensions.PushBack(dim2, allocator);

          rj::Value statusDimensions(rj::kArrayType);
          statusDimensions.CopyFrom(dimensions, allocator);
          statusDimensions.PopBack();
          ascan["status"].AddMember("dimensions", statusDimensions, allocator);
          ascan["amplitude"].AddMember("dimensions", dimensions, allocator);

          dataset.AddMember("ascan", ascan, allocator);

          if (!paut.HasMember("ascanCompressionFactor"))
          {
            uint32_t ascanCompressionFactor = std::lroundl(ascanResolution / 10e-9);
            paut.AddMember("ascanCompressionFactor", ascanCompressionFactor, allocator);
          }
        }

        // gateCscans

        rj::Value gateCscans(rj::kArrayType);
        datasetItr = std::find_if(datasets.Begin(), datasets.End(), [&](const auto& dataset) { return dataset.HasMember("cscan"); });
        for (; datasetItr != datasets.End(); datasetItr++)
        {
          rj::Value gateCscan(rj::kObjectType);
          const auto& cscanDset = (*datasetItr)["cscan"];
          uint64_t gateId = cscanDset["gateId"].GetUint64();
          gateCscan.AddMember("gateId", gateId, allocator);
          gateCscan.AddMember("path", rj::StringRef(cscanDset["datasetPath"].GetString()), allocator);

          auto gates = paut["gates"].GetArray();
          auto gateItr = std::find_if(gates.Begin(), gates.End(), [&](const auto& gate) { return gate["id"].GetUint64() == gateId; });
          if (gateItr != gates.End())
          {
            rj::Value dataValue(rj::kObjectType);
            rj::Value crossingTime(rj::kObjectType);
            dataValue.AddMember("unit", "Second", allocator);
            dataValue.AddMember("min", 0.0, allocator);
            dataValue.AddMember("max", (*gateItr)["length"].GetDouble(), allocator);
            crossingTime.AddMember("dataValue", dataValue, allocator);

            rj::Value peakTime(rj::kObjectType);
            peakTime.CopyFrom(crossingTime, allocator);

            gateCscan.AddMember("crossingTime", crossingTime, allocator);
            gateCscan.AddMember("peakTime", peakTime, allocator);

            rj::Value peak(rj::kObjectType);
            dataValue = rj::Value(rj::kObjectType);
            dataValue.AddMember("unit", "Percent", allocator);
            dataValue.AddMember("min", linearPulseEcho["amplitudePercentAxis"]["min"].GetDouble(), allocator);
            dataValue.AddMember("max", linearPulseEcho["amplitudePercentAxis"]["max"].GetDouble(), allocator);
            peak.AddMember("dataValue", dataValue, allocator);

            rj::Value dataSampling(rj::kObjectType);
            dataSampling.AddMember("min", cscanDset["amplitudeSamplingAxis"]["min"].GetInt(), allocator);
            dataSampling.AddMember("max", cscanDset["amplitudeSamplingAxis"]["max"].GetInt(), allocator);
            peak.AddMember("dataSampling", dataSampling, allocator);

            gateCscan.AddMember("peak", peak, allocator);

            rj::Value status(rj::kObjectType);
            dataValue = rj::Value(rj::kObjectType);
            dataValue.AddMember("unit", "Bitfield", allocator);
            const auto statuses = cscanDset["statuses"].GetArray();
            for (rj::SizeType statusIdx{}; statusIdx < statuses.Size(); statusIdx++)
            {
              std::string status = std::string(statuses[statusIdx].GetString());
              if (status == "HasData") {
                dataValue.AddMember("hasData", 1 << statusIdx, allocator);
              }
              if (status == "Synched" || status == "Synced") {
                dataValue.AddMember("noSynchro", 1 << statusIdx, allocator);
              }
              if (status == "Saturated") {
                dataValue.AddMember("saturated", 1 << statusIdx, allocator);
              }
              if (status == "Detected") {
                dataValue.AddMember("noDetection", 1 << statusIdx, allocator);
              }
            }

            status.AddMember("dataValue", dataValue, allocator);
            gateCscan.AddMember("status", status, allocator);
          }

          rj::Value dimensions(rj::kArrayType);
          rj::Value scanPattern(rj::kObjectType);
          const auto& discreteGrid = jsonSetupDoc["dataEncodings"][0]["discreteGrid"];
          if (discreteGrid.HasMember("oneLineScan")) {
            scanPattern.CopyFrom(discreteGrid["oneLineScan"], allocator);
          }
          else if (discreteGrid.HasMember("rasterScan")) {
            scanPattern.CopyFrom(discreteGrid["rasterScan"], allocator);
          }

          double offset = scanPattern["uCoordinateAxis"]["origin"].GetDouble();
          double length = scanPattern["uCoordinateAxis"]["length"].GetDouble();
          double resolution = scanPattern["uCoordinateAxis"]["resolution"].GetDouble();
          uint32_t quantity = std::lroundl(length / resolution) + 1;

          rj::Value dim0(rj::kObjectType);
          dim0.AddMember("axis", "UCoordinate", allocator);
          dim0.AddMember("quantity", quantity, allocator);
          dim0.AddMember("resolution", resolution, allocator);
          dim0.AddMember("offset", offset, allocator);
          dimensions.PushBack(dim0, allocator);

          offset = scanPattern["vCoordinateAxis"]["origin"].GetDouble();
          length = scanPattern["vCoordinateAxis"]["length"].GetDouble();
          resolution = scanPattern["vCoordinateAxis"]["resolution"].GetDouble();
          quantity = std::lroundl(length / resolution) + 1;

          rj::Value dim1(rj::kObjectType);
          dim1.AddMember("axis", "VCoordinate", allocator);
          dim1.AddMember("quantity", quantity, allocator);
          dim1.AddMember("resolution", resolution, allocator);
          dim1.AddMember("offset", offset, allocator);
          dimensions.PushBack(dim1, allocator);

          gateCscan.AddMember("dimensions", dimensions, allocator);
          gateCscans.PushBack(gateCscan, allocator);
        }

        if (gateCscans.Size() > 0) {
          dataset.AddMember("gateCscans", gateCscans, allocator);
        }
        
        group.AddMember("dataset", dataset, allocator);
        group.AddMember("paut", paut, allocator);

        groups.PushBack(group, allocator);
      }
    }

    rj::Value dimensions(rj::kArrayType);
    const auto& discreteGrid = jsonSetupDoc["dataEncodings"][0]["discreteGrid"];
    auto& newDiscreteGrid = newJsonSetupDoc["dataEncodings"][0]["discreteGrid"];
    if (discreteGrid.HasMember("oneLineScan"))
    {
      newDiscreteGrid.AddMember("scanPattern", "OneLineScan", allocator);

      double offset = discreteGrid["oneLineScan"]["uCoordinateAxis"]["origin"].GetDouble();
      double length = discreteGrid["oneLineScan"]["uCoordinateAxis"]["length"].GetDouble();
      double resolution = discreteGrid["oneLineScan"]["uCoordinateAxis"]["resolution"].GetDouble();
      uint32_t quantity = std::lroundl(length / resolution) + 1;

      rj::Value dim0(rj::kObjectType);
      dim0.AddMember("axis", "UCoordinate", allocator);
      dim0.AddMember("quantity", quantity, allocator);
      dim0.AddMember("resolution", resolution, allocator);
      dim0.AddMember("offset", offset, allocator);
      dimensions.PushBack(dim0, allocator);
      
    }
    else if (discreteGrid.HasMember("rasterScan"))
    {
      newDiscreteGrid.AddMember("scanPattern", "RasterScan", allocator);

      double offset = discreteGrid["rasterScan"]["uCoordinateAxis"]["origin"].GetDouble();
      double length = discreteGrid["rasterScan"]["uCoordinateAxis"]["length"].GetDouble();
      double resolution = discreteGrid["rasterScan"]["uCoordinateAxis"]["resolution"].GetDouble();
      uint32_t quantity = std::lroundl(length / resolution) + 1;

      rj::Value dim0(rj::kObjectType);
      dim0.AddMember("axis", "UCoordinate", allocator);
      dim0.AddMember("quantity", quantity, allocator);
      dim0.AddMember("resolution", resolution, allocator);
      dim0.AddMember("offset", offset, allocator);
      dimensions.PushBack(dim0, allocator);

      offset = discreteGrid["rasterScan"]["vCoordinateAxis"]["origin"].GetDouble();
      length = discreteGrid["rasterScan"]["vCoordinateAxis"]["length"].GetDouble();
      resolution = discreteGrid["rasterScan"]["vCoordinateAxis"]["resolution"].GetDouble();
      quantity = std::lroundl(length / resolution) + 1;

      rj::Value dim1(rj::kObjectType);
      dim1.AddMember("axis", "VCoordinate", allocator);
      dim1.AddMember("quantity", quantity, allocator);
      dim1.AddMember("resolution", resolution, allocator);
      dim1.AddMember("offset", offset, allocator);
      dimensions.PushBack(dim1, allocator);
    }
    newDiscreteGrid.AddMember("dimensions", dimensions, allocator);

    newJsonSetupDoc.AddMember("groups", groups, allocator);

    // Update version //
    newJsonSetupDoc["version"].SetString(Version, jsonSetupDoc.GetAllocator());
    newJsonSetupDoc.AddMember("$schema", "./NDE-FileFormat-Schema-3.0.0.json", allocator);

    rj::StringBuffer buffer;
    rj::Writer<rj::StringBuffer> writer(buffer);
    newJsonSetupDoc.Accept(writer);

    return NDE::TResult<std::string>(buffer.GetString(), { ResultDetails("domainSetupVersionUpgraded", Version) });
  }

  return NDE::TResult<std::string>(TError("jsonParseError"));
}
