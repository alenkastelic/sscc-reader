#include "ssccreader/sscc_validator.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace {

using ssccreader::SSCCValidator;
using ssccreader::ValidationErrorType;

void expect_error_types(
    const std::string& input,
    const std::vector<ValidationErrorType>& expected_types)
{
    SSCCValidator validator;
    const ssccreader::ValidationResult result = validator.validate(input);

    EXPECT_EQ(result.IsValid(), expected_types.empty());
    ASSERT_EQ(result.Errors().size(), expected_types.size());

    for (std::size_t i = 0; i < expected_types.size(); ++i) {
        EXPECT_EQ(result.Errors()[i].Type(), expected_types[i]);
    }
}

}

TEST(SSCCValidatorTests, Example1IsValid)
{
    expect_error_types("00034260311130776594", {});
}

TEST(SSCCValidatorTests, Example2HasThreeErrors)
{
    expect_error_types(
        "02044260311130776512",
        {
            ValidationErrorType::InvalidApplicationIdentifier,
            ValidationErrorType::InvalidCompanyPrefix,
            ValidationErrorType::InvalidCheckDigit
        });
}

TEST(SSCCValidatorTests, Example3HasInvalidCheckDigit)
{
    expect_error_types(
        "00034260311130776144",
        {ValidationErrorType::InvalidCheckDigit});
}

TEST(SSCCValidatorTests, Example4IsValid)
{
    expect_error_types("00034260311130776570", {});
}

TEST(SSCCValidatorTests, Example5HasInvalidLength)
{
    expect_error_types(
        "0003426031113077646",
        {ValidationErrorType::InvalidLength});
}

TEST(SSCCValidatorTests, Example6HasInvalidCompanyPrefix)
{
    expect_error_types(
        "00034260321130774636",
        {ValidationErrorType::InvalidCompanyPrefix});
}

TEST(SSCCValidatorTests, EmptyInputReturnsEmptyAndLengthErrors)
{
    expect_error_types(
        "",
        {
            ValidationErrorType::EmptyInput,
            ValidationErrorType::InvalidLength
        });
}

TEST(SSCCValidatorTests, InvalidCharactersAndLengthReturnBothErrors)
{
    expect_error_types(
        "not-an-sscc",
        {
            ValidationErrorType::InvalidLength,
            ValidationErrorType::InvalidCharacters
        });
}

TEST(SSCCValidatorTests, InvalidCharactersReturnError)
{
    expect_error_types(
        "0003426031113077657X",
        {ValidationErrorType::InvalidCharacters});
}

TEST(SSCCValidatorTests, InvalidApplicationIdentifierReturnsError)
{
    expect_error_types(
        "01034260311130776570",
        {ValidationErrorType::InvalidApplicationIdentifier});
}

TEST(SSCCValidatorTests, InvalidCompanyPrefixReturnsError)
{
    expect_error_types(
        "00044260311130776579",
        {ValidationErrorType::InvalidCompanyPrefix});
}

TEST(SSCCValidatorTests, InvalidCheckDigitReturnsError)
{
    expect_error_types(
        "00034260311130776571",
        {ValidationErrorType::InvalidCheckDigit});
}
