#pragma once

#include <shared_mutex>

static std::shared_mutex stdout_mtx;
static std::shared_mutex file_mutex;
static  std::shared_mutex fight_mutex;