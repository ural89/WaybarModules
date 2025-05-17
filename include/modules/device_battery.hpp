#pragma once

#include <string>
#include <json/value.h>
#include "ALabel.hpp"
#include "util/sleeper_thread.hpp"


class DeviceBattery : public waybar::ALabel {
 public:
  DeviceBattery(const std::string& id, const Json::Value& config);
  void update() override;

 private:
  int fake_percent = 42;
  waybar::util::SleeperThread thread_;
};

