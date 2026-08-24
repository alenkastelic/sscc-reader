#pragma once

#include "ssccreader/validation_error.hpp"

#include <vector>

namespace ssccreader
{
class ValidationResult
{
  public:
    ValidationResult(const std::vector<ValidationError> &validation_errors) : errors(validation_errors)
    {
    }

    bool IsValid() const
    {
        return errors.empty();
    }

    const std::vector<ValidationError> &Errors() const
    {
        return errors;
    }

  private:
    std::vector<ValidationError> errors;
};
}
