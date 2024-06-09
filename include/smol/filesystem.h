#pragma once

#include "filesystem/path.h"
#include <system_error>

namespace smol::filesystem
{
auto create_directory(const path &p_path, std::error_code &p_ec) noexcept -> bool;
auto current_path() -> path;
auto current_path(const path &p_path, std::error_code &p_ec) -> void;
auto remove(const path &p_path, std::error_code& p_ec) noexcept -> bool;
} // namespace filesystem
