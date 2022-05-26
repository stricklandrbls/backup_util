#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include <variant>
#include <memory>
#include "Terminal.hpp"

#define CONFIG_PATH "/etc/backup-util/config.json"

#define TEST

using smart_string = std::unique_ptr<std::string>;