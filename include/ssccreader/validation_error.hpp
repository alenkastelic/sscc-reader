#pragma once

#include <string>

namespace ssccreader
{

enum class ValidationErrorType
{
    EmptyInput,
    InvalidLength,
    InvalidCharacters,
    InvalidApplicationIdentifier,
    InvalidCompanyPrefix,
    InvalidCheckDigit
};

class ValidationError
{
  public:
    ValidationError(ValidationErrorType type, const std::string &message) : type(type), message(message)
    {
    }

    ValidationErrorType Type() const
    {
        return type;
    }

    const std::string &Message() const
    {
        return message;
    }

  private:
    ValidationErrorType type;
    std::string message;
};
}
