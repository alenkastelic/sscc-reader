#pragma once

#include "ssccreader/validation_result.hpp"

#include <cstddef>
#include <string>

namespace ssccreader
{
class SSCCValidator
{
  public:
    ValidationResult validate(const std::string &input) const;

  private:
    static const std::size_t expected_input_length;
    static const std::string expected_application_identifier;
    static const std::string expected_company_prefix;

    static bool is_digit(char value);
    static char calculate_check_digit(const std::string &value);
};
}
