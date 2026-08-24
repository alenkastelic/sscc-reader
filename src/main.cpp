#include "ssccreader/sscc_validator.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace
{
const std::vector<std::string> scanned_examples = {
    "00034260311130776594",
    "02044260311130776512",
    "00034260311130776144",
    "00034260311130776570",
    "0003426031113077646",
    "00034260321130774636"};

void print_line(const std::string &text = "")
{
    std::cout << text << '\n';
}

void print_result(
    const std::string &label,
    const std::string &input,
    const ssccreader::ValidationResult &result)
{
    print_line(label);
    print_line("  Code: " + input);

    if (result.IsValid())
    {
        print_line("  Result: VALID");
        print_line();
        return;
    }

    print_line("  Result: INVALID");
    for (const ssccreader::ValidationError &error : result.Errors())
    {
        print_line("  - " + error.Message());
    }
    print_line();
}

int run_interactive(const ssccreader::SSCCValidator &validator)
{
    std::cout << "Enter scanned code: " << std::flush;

    std::string input;
    if (!std::getline(std::cin, input))
    {
        std::cerr << "Unable to read the SSCC number.\n";
        return 2;
    }

    const ssccreader::ValidationResult result = validator.validate(input);
    print_result("Validation result:", input, result);
    return 0;
}

int run_examples(const ssccreader::SSCCValidator &validator)
{
    print_line("Validating the scanned sscc examples");
    print_line("========================================");
    print_line();
    for (std::size_t i = 0; i < scanned_examples.size(); i++)
    {
        const ssccreader::ValidationResult result = validator.validate(scanned_examples[i]);
        print_result(
            "Example " + std::to_string(i + 1),
            scanned_examples[i],
            result);
    }

    return 0;
}
}

int main(int argc, char *argv[])
{
    const ssccreader::SSCCValidator validator;

    if (argc == 1)
    {
        return run_interactive(validator);
    }

    if (argc == 2 && std::string(argv[1]) == "--examples")
    {
        return run_examples(validator);
    }

    std::cerr << "Usage: " << argv[0] << " [--examples]\n";
    return 2;
}
