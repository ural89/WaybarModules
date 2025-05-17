#include "modules/device_battery.hpp"
#include <fmt/args.h>
#include <json/value.h>
#include <iostream>
#include <string>
DeviceBattery::DeviceBattery(const std::string& id, const Json::Value& config)
  : ALabel(config, "device-battery-module", id, "{text}", 5) {  thread_ = [this] {
    dp.emit();
    thread_.sleep_for(interval_);
  };
}
auto DeviceBattery::update()->void
{
 std::cout << "Battery module updating\n";

  auto format = format_;
  auto state = getState(fake_percent);
  if (!state.empty() && config_["format-" + state].isString()) {
    format = config_["format-" + state].asString();
  }

  auto icons = std::vector<std::string>{state};

  fmt::dynamic_format_arg_store<fmt::format_context> store;
  store.push_back(fmt::arg("percent", fake_percent));
  store.push_back(fmt::arg("icon", getIcon(fake_percent, icons)));

  label_.set_markup(fmt::vformat(format, store));
  ALabel::update();
}
