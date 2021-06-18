#pragma once

#define MAKE_NO_COPY(class_name)   class_name(const class_name&) = delete;      \
  class_name& operator=(const class_name&) = delete;

#define MAKE_SIMPLE_MOVE(class_name) class_name(class_name&& other) noexcept { move(std::move(other)); } \
class_name& operator=(class_name&& other) noexcept { if(this == &other) {return *this;} move(std::move(other)); return *this; }

#define MAKE_DEFAULT_MOVE(class_name) class_name(class_name&& other) noexcept = default; class_name& operator=(class_name&& other) noexcept = default;