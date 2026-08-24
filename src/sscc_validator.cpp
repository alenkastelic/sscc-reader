#include "ssccreader/sscc_validator.hpp"

#include <algorithm>
#include <string>

namespace ssccreader
{
const std::size_t SSCCValidator::expected_input_length = 20;
const std::string SSCCValidator::expected_application_identifier = "00";
const std::string SSCCValidator::expected_company_prefix = "34260311";

ValidationResult SSCCValidator::validate(const std::string &input) const
{
    std::vector<ValidationError> validation_errors;

    if (input.empty())
    {
        ValidationError validation_error(ValidationErrorType::EmptyInput, "Input is empty.");
        validation_errors.push_back(validation_error);
    }

    if (input.size() != expected_input_length)
    {
        ValidationError validation_error(
            ValidationErrorType::InvalidLength,
            "The code must contain exactly " +
                std::to_string(expected_input_length) +
                " characters (AI + SSCC), but contains " +
                std::to_string(input.size()) +
                ".");
        validation_errors.push_back(validation_error);
    }

    if (!std::all_of(input.begin(), input.end(), is_digit))
    {
        ValidationError validation_error(
            ValidationErrorType::InvalidCharacters,
            "Only digits from 0 to 9 are allowed.");
        validation_errors.push_back(validation_error);
    }

    if (!validation_errors.empty())
    {
        return ValidationResult(validation_errors);
    }

    const std::string application_identifier = input.substr(0, 2);
    if (application_identifier != expected_application_identifier)
    {
        ValidationError validation_error(
            ValidationErrorType::InvalidApplicationIdentifier,
            "Invalid Application Identifier (AI): received '" +
                application_identifier +
                "', expected '00' for SSCC.");
        validation_errors.push_back(validation_error);
    }

    const std::string sscc_code = input.substr(2);
    const std::string company_prefix = sscc_code.substr(1, expected_company_prefix.size());
    if (company_prefix != expected_company_prefix)
    {
        ValidationError validation_error(
            ValidationErrorType::InvalidCompanyPrefix,
            "Invalid company prefix: received '" +
                company_prefix +
                "', expected '" +
                expected_company_prefix +
                "' for TSX GmbH.");
        validation_errors.push_back(validation_error);
    }

    const char expected_check_digit = calculate_check_digit(sscc_code.substr(0, sscc_code.size() - 1));
    const char check_digit = sscc_code.back();
    if (check_digit != expected_check_digit)
    {
        ValidationError validation_error(
            ValidationErrorType::InvalidCheckDigit,
            "Invalid check digit: received '" +
                std::string(1, check_digit) +
                "', the calculated correct digit is '" +
                std::string(1, expected_check_digit) +
                "'.");
        validation_errors.push_back(validation_error);
    }

    return ValidationResult(validation_errors);
}

bool SSCCValidator::is_digit(char value)
{
    return value >= '0' && value <= '9';
}

char SSCCValidator::calculate_check_digit(const std::string &value)
{
    int sum = 0;

    for (std::size_t i = 0; i < value.size(); ++i)
    {
        const int digit = value[i] - '0';
        const std::size_t position_from_right = value.size() - i;
        sum += position_from_right % 2 == 1 ? digit * 3 : digit;
    }

    return (char)('0' + (10 - sum % 10) % 10);
}
}
