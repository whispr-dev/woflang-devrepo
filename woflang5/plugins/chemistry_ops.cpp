#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <regex>
#include <numeric>

namespace woflang {

/**
 * @brief Helper functions and data for chemistry operations
 */
namespace chemistry_helpers {
    // Structure to hold element data
    struct Element {
        std::string symbol;           // Element symbol
        std::string name;             // Element name
        double atomic_weight;         // Atomic weight in g/mol
        int atomic_number;            // Atomic number
        std::string category;         // Element category
        double electronegativity;     // Electronegativity (Pauling scale)
        int group;                    // Group in periodic table
        int period;                   // Period in periodic table
        std::string electron_config;  // Electron configuration
    };
    
    // Map of element symbols to element data
    const std::map<std::string, Element> ELEMENTS = {
        {"H", {"H", "Hydrogen", 1.008, 1, "Nonmetal", 2.20, 1, 1, "1s1"}},
        {"He", {"He", "Helium", 4.0026, 2, "Noble Gas", -1, 18, 1, "1s2"}},
        {"Li", {"Li", "Lithium", 6.94, 3, "Alkali Metal", 0.98, 1, 2, "1s2 2s1"}},
        {"Be", {"Be", "Beryllium", 9.0122, 4, "Alkaline Earth Metal", 1.57, 2, 2, "1s2 2s2"}},
        {"B", {"B", "Boron", 10.81, 5, "Metalloid", 2.04, 13, 2, "1s2 2s2 2p1"}},
        {"C", {"C", "Carbon", 12.011, 6, "Nonmetal", 2.55, 14, 2, "1s2 2s2 2p2"}},
        {"N", {"N", "Nitrogen", 14.007, 7, "Nonmetal", 3.04, 15, 2, "1s2 2s2 2p3"}},
        {"O", {"O", "Oxygen", 15.999, 8, "Nonmetal", 3.44, 16, 2, "1s2 2s2 2p4"}},
        {"F", {"F", "Fluorine", 18.998, 9, "Halogen", 3.98, 17, 2, "1s2 2s2 2p5"}},
        {"Ne", {"Ne", "Neon", 20.180, 10, "Noble Gas", -1, 18, 2, "1s2 2s2 2p6"}},
        {"Na", {"Na", "Sodium", 22.990, 11, "Alkali Metal", 0.93, 1, 3, "1s2 2s2 2p6 3s1"}},
        {"Mg", {"Mg", "Magnesium", 24.305, 12, "Alkaline Earth Metal", 1.31, 2, 3, "1s2 2s2 2p6 3s2"}},
        {"Al", {"Al", "Aluminum", 26.982, 13, "Post-Transition Metal", 1.61, 13, 3, "1s2 2s2 2p6 3s2 3p1"}},
        {"Si", {"Si", "Silicon", 28.085, 14, "Metalloid", 1.90, 14, 3, "1s2 2s2 2p6 3s2 3p2"}},
        {"P", {"P", "Phosphorus", 30.974, 15, "Nonmetal", 2.19, 15, 3, "1s2 2s2 2p6 3s2 3p3"}},
        {"S", {"S", "Sulfur", 32.06, 16, "Nonmetal", 2.58, 16, 3, "1s2 2s2 2p6 3s2 3p4"}},
        {"Cl", {"Cl", "Chlorine", 35.45, 17, "Halogen", 3.16, 17, 3, "1s2 2s2 2p6 3s2 3p5"}},
        {"Ar", {"Ar", "Argon", 39.948, 18, "Noble Gas", -1, 18, 3, "1s2 2s2 2p6 3s2 3p6"}},
        {"K", {"K", "Potassium", 39.098, 19, "Alkali Metal", 0.82, 1, 4, "1s2 2s2 2p6 3s2 3p6 4s1"}},
        {"Ca", {"Ca", "Calcium", 40.078, 20, "Alkaline Earth Metal", 1.00, 2, 4, "1s2 2s2 2p6 3s2 3p6 4s2"}},
        {"Fe", {"Fe", "Iron", 55.845, 26, "Transition Metal", 1.83, 8, 4, "1s2 2s2 2p6 3s2 3p6 3d6 4s2"}},
        {"Cu", {"Cu", "Copper", 63.546, 29, "Transition Metal", 1.90, 11, 4, "1s2 2s2 2p6 3s2 3p6 3d10 4s1"}},
        {"Zn", {"Zn", "Zinc", 65.38, 30, "Transition Metal", 1.65, 12, 4, "1s2 2s2 2p6 3s2 3p6 3d10 4s2"}},
        {"Ag", {"Ag", "Silver", 107.87, 47, "Transition Metal", 1.93, 11, 5, "1s2 2s2 2p6 3s2 3p6 3d10 4s2 4p6 4d10 5s1"}},
        {"Au", {"Au", "Gold", 196.97, 79, "Transition Metal", 2.54, 11, 6, "1s2 2s2 2p6 3s2 3p6 3d10 4s2 4p6 4d10 4f14 5s2 5p6 5d10 6s1"}},
        {"Hg", {"Hg", "Mercury", 200.59, 80, "Transition Metal", 2.00, 12, 6, "1s2 2s2 2p6 3s2 3p6 3d10 4s2 4p6 4d10 4f14 5s2 5p6 5d10 6s2"}},
        {"Pb", {"Pb", "Lead", 207.2, 82, "Post-Transition Metal", 1.87, 14, 6, "1s2 2s2 2p6 3s2 3p6 3d10 4s2 4p6 4d10 4f14 5s2 5p6 5d10 6s2 6p2"}},
        {"U", {"U", "Uranium", 238.03, 92, "Actinide", 1.38, -1, 7, "1s2 2s2 2p6 3s2 3p6 3d10 4s2 4p6 4d10 4f14 5s2 5p6 5d10 5f3 6s2 6p6 6d1 7s2"}}
        // More elements could be added here
    };
    
    // Physical constants
    const double AVOGADRO_NUMBER = 6.02214076e23;  // Avogadro's number
    const double GAS_CONSTANT = 8.31446;           // Gas constant (J/mol·K)
    const double BOLTZMANN_CONSTANT = 1.380649e-23; // Boltzmann constant (J/K)
    const double ATMOSPHERIC_PRESSURE = 101325;    // Standard atmospheric pressure (Pa)
    
    // Structure to hold a chemical formula and its components
    struct Formula {
        std::string original;                // Original formula string
        std::map<std::string, int> elements; // Element symbols to counts
    };
    
    // Parse a chemical formula to extract element symbols and counts
    Formula parse_formula(const std::string& formula_str) {
        Formula result;
        result.original = formula_str;
        
        // Regular expression to match element symbols and counts
        // Matches: Element symbol (1-2 letters, first uppercase) followed by optional number
        std::regex element_pattern("([A-Z][a-z]?)([0-9]*)");
        
        // Iterate through matches
        auto begin = std::sregex_iterator(formula_str.begin(), formula_str.end(), element_pattern);
        auto end = std::sregex_iterator();
        
        for (std::sregex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i;
            std::string element = match[1].str();
            
            // If count is omitted, default to 1
            int count = 1;
            if (match[2].length() > 0) {
                count = std::stoi(match[2].str());
            }
            
            // Add to the elements map
            if (result.elements.find(element) == result.elements.end()) {
                result.elements[element] = count;
            } else {
                result.elements[element] += count;
            }
        }
        
        return result;
    }
    
    // Calculate the molecular weight of a formula
    double molecular_weight(const Formula& formula) {
        double weight = 0.0;
        
        for (const auto& [element, count] : formula.elements) {
            // Check if the element exists in our database
            if (ELEMENTS.find(element) == ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + element);
            }
            
            weight += ELEMENTS.at(element).atomic_weight * count;
        }
        
        return weight;
    }
    
    // Format a formula with proper subscripts for counts
    std::string format_formula(const Formula& formula) {
        std::string result;
        
        for (const auto& [element, count] : formula.elements) {
            result += element;
            if (count > 1) {
                result += std::to_string(count);
            }
        }
        
        return result;
    }
    
    // Balance a simple chemical equation
    std::vector<int> balance_equation(const std::string& equation_str) {
        // Split by the arrow
        size_t arrow_pos = equation_str.find("->");
        if (arrow_pos == std::string::npos) {
            throw std::runtime_error("Invalid equation format. Use -> for the reaction arrow.");
        }
        
        std::string reactants_str = equation_str.substr(0, arrow_pos);
        std::string products_str = equation_str.substr(arrow_pos + 2);
        
        // Split reactants and products by +
        auto split = [](const std::string& s) {
            std::vector<std::string> result;
            size_t start = 0;
            size_t end = s.find('+');
            
            while (end != std::string::npos) {
                std::string token = s.substr(start, end - start);
                token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
                result.push_back(token);
                
                start = end + 1;
                end = s.find('+', start);
            }
            
            std::string token = s.substr(start);
            token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
            token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
            result.push_back(token);
            
            return result;
        };
        
        std::vector<std::string> reactants = split(reactants_str);
        std::vector<std::string> products = split(products_str);
        
        // Parse each formula
        std::vector<Formula> reactant_formulas;
        for (const auto& r : reactants) {
            reactant_formulas.push_back(parse_formula(r));
        }
        
        std::vector<Formula> product_formulas;
        for (const auto& p : products) {
            product_formulas.push_back(parse_formula(p));
        }
        
        // Collect all unique elements
        std::set<std::string> all_elements;
        for (const auto& formula : reactant_formulas) {
            for (const auto& [element, _] : formula.elements) {
                all_elements.insert(element);
            }
        }
        for (const auto& formula : product_formulas) {
            for (const auto& [element, _] : formula.elements) {
                all_elements.insert(element);
            }
        }
        
        // Create the matrix for the linear system
        int num_species = reactants.size() + products.size();
        int num_elements = all_elements.size();
        
        // Need to check if the system is solvable
        if (num_species <= num_elements) {
            throw std::runtime_error("Cannot balance this equation: too few species");
        }
        
        // Build the matrix: each row represents an element conservation constraint
        std::vector<std::vector<int>> matrix(num_elements, std::vector<int>(num_species - 1, 0));
        std::vector<int> rhs(num_elements, 0);
        
        int row = 0;
        for (const auto& element : all_elements) {
            // Reactants (positive coefficients)
            for (size_t i = 0; i < reactant_formulas.size(); i++) {
                int count = 0;
                if (reactant_formulas[i].elements.find(element) != reactant_formulas[i].elements.end()) {
                    count = reactant_formulas[i].elements[element];
                }
                
                if (i == 0) {
                    rhs[row] -= count; // Move first reactant to RHS
                } else {
                    matrix[row][i - 1] = count;
                }
            }
            
            // Products (negative coefficients)
            for (size_t i = 0; i < product_formulas.size(); i++) {
                int count = 0;
                if (product_formulas[i].elements.find(element) != product_formulas[i].elements.end()) {
                    count = product_formulas[i].elements[element];
                }
                
                matrix[row][reactant_formulas.size() - 1 + i] = -count;
            }
            
            row++;
        }
        
        // Solve the system using a simple Gaussian elimination
        // This is a simplified approach and might not work for all equations
        
        // Apply Gaussian elimination to get an upper triangular matrix
        for (int i = 0; i < num_elements; i++) {
            // Find the pivot
            int pivot_row = i;
            while (pivot_row < num_elements && matrix[pivot_row][i] == 0) {
                pivot_row++;
            }
            
            if (pivot_row == num_elements) {
                // No non-zero pivot found
                continue;
            }
            
            // Swap rows if needed
            if (pivot_row != i) {
                std::swap(matrix[i], matrix[pivot_row]);
                std::swap(rhs[i], rhs[pivot_row]);
            }
            
            // Eliminate below
            for (int j = i + 1; j < num_elements; j++) {
                if (matrix[j][i] == 0) continue;
                
                int factor = matrix[j][i] / matrix[i][i];
                for (int k = i; k < num_species - 1; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
                rhs[j] -= factor * rhs[i];
            }
        }
        
        // Back substitution
        std::vector<double> solution(num_species - 1, 0);
        for (int i = num_elements - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < num_species - 1; j++) {
                sum += matrix[i][j] * solution[j];
            }
            
            if (matrix[i][i] == 0) {
                // Underdetermined system, set a free variable to 1
                solution[i] = 1;
            } else {
                solution[i] = (rhs[i] - sum) / matrix[i][i];
            }
        }
        
        // First coefficient (reactant) is always 1
        solution.insert(solution.begin(), 1);
        
        // Find the smallest scale factor to make all coefficients integers
        std::vector<double> abs_solution;
        for (double val : solution) {
            abs_solution.push_back(std::abs(val));
        }
        
        double min_val = *std::min_element(abs_solution.begin(), abs_solution.end());
        if (min_val < 1e-10) min_val = 1.0; // Avoid division by very small values
        
        // Try to find a scale factor to make all values integers
        double scale = 1.0;
        bool all_ints = false;
        
        for (int attempt = 1; attempt <= 10000 && !all_ints; attempt++) {
            all_ints = true;
            for (double val : solution) {
                double scaled_val = val * attempt / min_val;
                if (std::abs(scaled_val - std::round(scaled_val)) > 1e-5) {
                    all_ints = false;
                    break;
                }
            }
            
            if (all_ints) {
                scale = attempt / min_val;
            }
        }
        
        // Scale and round to get integer coefficients
        std::vector<int> coefficients;
        for (double val : solution) {
            int coef = static_cast<int>(std::round(val * scale));
            coefficients.push_back(coef);
        }
        
        // If all coefficients share a common factor, divide by it
        int gcd_val = coefficients[0];
        for (size_t i = 1; i < coefficients.size(); i++) {
            gcd_val = std::gcd(gcd_val, coefficients[i]);
        }
        
        if (gcd_val > 1) {
            for (int& coef : coefficients) {
                coef /= gcd_val;
            }
        }
        
        return coefficients;
    }
    
    // Calculate pH from hydrogen ion concentration
    double pH_from_concentration(double h_concentration) {
        return -std::log10(h_concentration);
    }
    
    // Calculate hydrogen ion concentration from pH
    double concentration_from_pH(double pH) {
        return std::pow(10, -pH);
    }
}

/**
 * @brief Chemistry operations plugin for Woflang
 * 
 * This plugin provides various chemistry-related operations.
 */
class ChemistryOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Element Operations -----
        
        // element_info: Get information about an element
        interp.register_op("element_info", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("element_info requires an element symbol");
            }
            
            auto element = interp.stack.back(); interp.stack.pop_back();
            
            if (element.type != WofType::String && element.type != WofType::Symbol) {
                throw std::runtime_error("Element symbol must be a string or symbol");
            }
            
            std::string symbol = std::get<std::string>(element.value);
            
            // Check if the element exists
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            const auto& elem = chemistry_helpers::ELEMENTS.at(symbol);
            
            // Print the element information
            std::cout << "Element: " << elem.name << " (" << elem.symbol << ")\n";
            std::cout << "  Atomic Number: " << elem.atomic_number << "\n";
            std::cout << "  Atomic Weight: " << elem.atomic_weight << " g/mol\n";
            std::cout << "  Category: " << elem.category << "\n";
            
            if (elem.electronegativity > 0) {
                std::cout << "  Electronegativity: " << elem.electronegativity << " (Pauling)\n";
            }
            
            if (elem.group > 0) {
                std::cout << "  Group: " << elem.group << "\n";
            }
            
            std::cout << "  Period: " << elem.period << "\n";
            std::cout << "  Electron Configuration: " << elem.electron_config << "\n";
            
            // Push the atomic weight onto the stack (most commonly used value)
            interp.stack.emplace_back(elem.atomic_weight);
        });
        
        // atomic_weight: Get the atomic weight of an element
        interp.register_op("atomic_weight", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("atomic_weight requires an element symbol");
            }
            
            auto element = interp.stack.back(); interp.stack.pop_back();
            
            if (element.type != WofType::String && element.type != WofType::Symbol) {
                throw std::runtime_error("Element symbol must be a string or symbol");
            }
            
            std::string symbol = std::get<std::string>(element.value);
            
            // Check if the element exists
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            // Get the atomic weight
            double weight = chemistry_helpers::ELEMENTS.at(symbol).atomic_weight;
            
            // Push the atomic weight onto the stack
            interp.stack.emplace_back(weight);
            
            std::cout << "Atomic weight of " << symbol << ": " << weight << " g/mol\n";
        });
        
        // atomic_number: Get the atomic number of an element
        interp.register_op("atomic_number", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("atomic_number requires an element symbol");
            }
            
            auto element = interp.stack.back(); interp.stack.pop_back();
            
            if (element.type != WofType::String && element.type != WofType::Symbol) {
                throw std::runtime_error("Element symbol must be a string or symbol");
            }
            
            std::string symbol = std::get<std::string>(element.value);
            
            // Check if the element exists
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            // Get the atomic number
            int number = chemistry_helpers::ELEMENTS.at(symbol).atomic_number;
            
            // Push the atomic number onto the stack
            interp.stack.emplace_back(static_cast<int64_t>(number));
            
            std::cout << "Atomic number of " << symbol << ": " << number << "\n";
        });
        
        // ----- Molecular Operations -----
        
        // molecular_weight: Calculate the molecular weight of a chemical formula
        interp.register_op("molecular_weight", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("molecular_weight requires a chemical formula");
            }
            
            auto formula_val = interp.stack.back(); interp.stack.pop_back();
            
            if (formula_val.type != WofType::String && formula_val.type != WofType::Symbol) {
                throw std::runtime_error("Chemical formula must be a string or symbol");
            }
            
            std::string formula_str = std::get<std::string>(formula_val.value);
            
            try {
                // Parse the formula
                auto formula = chemistry_helpers::parse_formula(formula_str);
                
                // Calculate the molecular weight
                double weight = chemistry_helpers::molecular_weight(formula);
                
                // Push the molecular weight onto the stack
                interp.stack.emplace_back(weight);
                
                std::cout << "Molecular weight of " << formula_str << ": " << weight << " g/mol\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("molecular_weight error: ") + e.what());
            }
        });
        
        // parse_formula: Parse a chemical formula and display its components
        interp.register_op("parse_formula", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("parse_formula requires a chemical formula");
            }
            
            auto formula_val = interp.stack.back(); interp.stack.pop_back();
            
            if (formula_val.type != WofType::String && formula_val.type != WofType::Symbol) {
                throw std::runtime_error("Chemical formula must be a string or symbol");
            }
            
            std::string formula_str = std::get<std::string>(formula_val.value);
            
            try {
                // Parse the formula
                auto formula = chemistry_helpers::parse_formula(formula_str);
                
                // Print the components
                std::cout << "Formula: " << formula_str << "\n";
                std::cout << "Components:\n";
                
                for (const auto& [element, count] : formula.elements) {
                    std::cout << "  " << element << ": " << count << "\n";
                    
                    // Push the element and count onto the stack
                    interp.stack.emplace_back(element, WofType::String);
                    interp.stack.emplace_back(static_cast<int64_t>(count));
                }
                
                // Push the number of components
                interp.stack.emplace_back(static_cast<int64_t>(formula.elements.size()));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("parse_formula error: ") + e.what());
            }
        });
        
        // balance_equation: Balance a chemical equation
        interp.register_op("balance_equation", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("balance_equation requires a chemical equation");
            }
            
            auto equation_val = interp.stack.back(); interp.stack.pop_back();
            
            if (equation_val.type != WofType::String && equation_val.type != WofType::Symbol) {
                throw std::runtime_error("Chemical equation must be a string or symbol");
            }
            
            std::string equation_str = std::get<std::string>(equation_val.value);
            
            try {
                // Attempt to balance the equation
                std::vector<int> coefficients = chemistry_helpers::balance_equation(equation_str);
                
                // Split the equation into reactants and products
                size_t arrow_pos = equation_str.find("->");
                std::string reactants_str = equation_str.substr(0, arrow_pos);
                std::string products_str = equation_str.substr(arrow_pos + 2);
                
                // Split by +
                auto split = [](const std::string& s) {
                    std::vector<std::string> result;
                    size_t start = 0;
                    size_t end = s.find('+');
                    
                    while (end != std::string::npos) {
                        std::string token = s.substr(start, end - start);
                        token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                        token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
                        result.push_back(token);
                        
                        start = end + 1;
                        end = s.find('+', start);
                    }
                    
                    std::string token = s.substr(start);
                    token.erase(0, token.find_first_not_of(" \t\n\r\f\v"));
                    token.erase(token.find_last_not_of(" \t\n\r\f\v") + 1);
                    result.push_back(token);
                    
                    return result;
                };
                
                std::vector<std::string> reactants = split(reactants_str);
                std::vector<std::string> products = split(products_str);
                
                // Construct the balanced equation
                std::string balanced = "";
                
                // Add reactants with coefficients
                for (size_t i = 0; i < reactants.size(); i++) {
                    if (i > 0) {
                        balanced += " + ";
                    }
                    
                    if (coefficients[i] > 1) {
                        balanced += std::to_string(coefficients[i]) + " ";
                    }
                    
                    balanced += reactants[i];
                }
                
                balanced += " -> ";
                
                // Add products with coefficients
                for (size_t i = 0; i < products.size(); i++) {
                    if (i > 0) {
                        balanced += " + ";
                    }
                    
                    if (coefficients[i + reactants.size()] > 1) {
                        balanced += std::to_string(coefficients[i + reactants.size()]) + " ";
                    }
                    
                    balanced += products[i];
                }
                
                // Print the balanced equation
                std::cout << "Balanced equation: " << balanced << "\n";
                
                // Push the balanced equation onto the stack
                interp.stack.emplace_back(balanced);
                
                // Also push the coefficients
                for (int coef : coefficients) {
                    interp.stack.emplace_back(static_cast<int64_t>(coef));
                }
                
                // Push the number of coefficients
                interp.stack.emplace_back(static_cast<int64_t>(coefficients.size()));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("balance_equation error: ") + e.what());
            }
        });
        
        // ----- Physical Chemistry Operations -----
        
        // ideal_gas_law: Calculate using the ideal gas law (PV = nRT)
        interp.register_op("ideal_gas_law", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 3) {
                throw std::runtime_error("ideal_gas_law requires 3 values (any 3 of P, V, n, T)");
            }
            
            // Get the three known values and their names
            std::vector<std::pair<std::string, double>> values;
            
            for (int i = 0; i < 3; i++) {
                if (interp.stack.size() < 2) {
                    throw std::runtime_error("ideal_gas_law requires pairs of (name, value)");
                }
                
                auto value = interp.stack.back(); interp.stack.pop_back();
                auto name = interp.stack.back(); interp.stack.pop_back();
                
                if (!value.is_numeric()) {
                    throw std::runtime_error("Values must be numeric");
                }
                
                if (name.type != WofType::String && name.type != WofType::Symbol) {
                    throw std::runtime_error("Names must be strings or symbols");
                }
                
                std::string name_str = std::get<std::string>(name.value);
                double val = value.as_numeric();
                
                values.emplace_back(name_str, val);
            }
            
            // Check if we have valid parameters
            std::set<std::string> valid_params = {"P", "V", "n", "T"};
            std::set<std::string> provided_params;
            
            for (const auto& [name, _] : values) {
                if (valid_params.find(name) == valid_params.end()) {
                    throw std::runtime_error("Invalid parameter: " + name + ". Must be P, V, n, or T");
                }
                
                provided_params.insert(name);
            }
            
            // Determine which parameter to calculate
            std::string missing_param;
            for (const auto& param : valid_params) {
                if (provided_params.find(param) == provided_params.end()) {
                    missing_param = param;
                    break;
                }
            }
            
            if (missing_param.empty()) {
                throw std::runtime_error("Must provide exactly 3 of the 4 parameters (P, V, n, T)");
            }
            
            // Get the values of the provided parameters
            double P = 0, V = 0, n = 0, T = 0;
            for (const auto& [name, value] : values) {
                if (name == "P") P = value;
                else if (name == "V") V = value;
                else if (name == "n") n = value;
                else if (name == "T") T = value;
            }
            
            // Calculate the missing parameter
            double result = 0;
            if (missing_param == "P") {
                result = n * chemistry_helpers::GAS_CONSTANT * T / V;
                std::cout << "Pressure (P): " << result << " Pa\n";
            } else if (missing_param == "V") {
                result = n * chemistry_helpers::GAS_CONSTANT * T / P;
                std::cout << "Volume (V): " << result << " m³\n";
            } else if (missing_param == "n") {
                result = P * V / (chemistry_helpers::GAS_CONSTANT * T);
                std::cout << "Amount of substance (n): " << result << " mol\n";
            } else if (missing_param == "T") {
                result = P * V / (n * chemistry_helpers::GAS_CONSTANT);
                std::cout << "Temperature (T): " << result << " K\n";
            }
            
            // Push the result onto the stack
            interp.stack.emplace_back(result);
            
            // Also push the name of the calculated parameter
            interp.stack.emplace_back(missing_param, WofType::String);
        });
        
        // pH: Calculate pH from hydrogen ion concentration or vice versa
        interp.register_op("pH", [](WoflangInterpreter& interp) {
            if (interp.stack.size() < 2) {
                throw std::runtime_error("pH requires a value and direction (to_pH or to_conc)");
            }
            
            auto direction = interp.stack.back(); interp.stack.pop_back();
            auto value = interp.stack.back(); interp.stack.pop_back();
            
            if (!value.is_numeric()) {
                throw std::runtime_error("Value must be numeric");
            }
            
            if (direction.type != WofType::String && direction.type != WofType::Symbol) {
                throw std::runtime_error("Direction must be a string or symbol");
            }
            
            double val = value.as_numeric();
            std::string dir_str = std::get<std::string>(direction.value);
            
            if (dir_str == "to_pH") {
                // Convert hydrogen ion concentration to pH
                double pH = chemistry_helpers::pH_from_concentration(val);
                interp.stack.emplace_back(pH);
                std::cout << "pH: " << pH << "\n";
            } else if (dir_str == "to_conc") {
                // Convert pH to hydrogen ion concentration
                double conc = chemistry_helpers::concentration_from_pH(val);
                interp.stack.emplace_back(conc);
                std::cout << "H⁺ concentration: " << conc << " mol/L\n";
            } else {
                throw std::runtime_error("Direction must be 'to_pH' or 'to_conc'");
            }
        });
        
        // ----- Constants -----
        
        // avogadro: Push Avogadro's number
        interp.register_op("avogadro", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(chemistry_helpers::AVOGADRO_NUMBER);
            std::cout << "Avogadro's number: " << chemistry_helpers::AVOGADRO_NUMBER << " mol⁻¹\n";
        });
        
        // gas_constant: Push the gas constant
        interp.register_op("gas_constant", [](WoflangInterpreter& interp) {
            interp.stack.emplace_back(chemistry_helpers::GAS_CONSTANT);
            std::cout << "Gas constant: " << chemistry_helpers::GAS_CONSTANT << " J/(mol·K)\n";
        });
        
        // ----- Educational Operations -----
        
        // list_elements: List available elements
        interp.register_op("list_elements", [](WoflangInterpreter& interp) {
            std::cout << "Available elements:\n";
            
            // Group by period
            std::map<int, std::vector<std::string>> elements_by_period;
            
            for (const auto& [symbol, elem] : chemistry_helpers::ELEMENTS) {
                elements_by_period[elem.period].push_back(symbol);
            }
            
            // Print elements by period
            for (const auto& [period, symbols] : elements_by_period) {
                std::cout << "Period " << period << ": ";
                
                for (size_t i = 0; i < symbols.size(); i++) {
                    std::cout << symbols[i];
                    if (i < symbols.size() - 1) {
                        std::cout << ", ";
                    }
                }
                
                std::cout << "\n";
            }
        });
        
        // periodic_table: Display a simple ASCII periodic table
        interp.register_op("periodic_table", [](WoflangInterpreter& interp) {
            std::cout << "Periodic Table of Elements (ASCII):\n\n";
            
            // Create a simple ASCII representation
            std::cout << "1  H                                                  He\n";
            std::cout << "2  Li Be                               B  C  N  O  F  Ne\n";
            std::cout << "3  Na Mg                               Al Si P  S  Cl Ar\n";
            std::cout << "4  K  Ca ... ... ... ... ... ... ... ...              \n";
            std::cout << "...\n";
            std::cout << "6  ... ... ... ... ... ... ... ... ... Au ... Hg ... Pb\n";
            std::cout << "7  ... ... ... ... ... ... ... ... ... ... ... ... U \n\n";
            
            std::cout << "Use 'element_info' for detailed information about specific elements.\n";
        });
        
        // chemistry_tutorial: Display a basic chemistry tutorial
        interp.register_op("chemistry_tutorial", [](WoflangInterpreter& interp) {
            std::cout << "=== Basic Chemistry Tutorial ===\n\n";
            
            std::cout << "1. Atoms and Elements:\n";
            std::cout << "   An atom is the smallest unit of matter that retains the properties of an element.\n";
            std::cout << "   Each element has a unique atomic number and atomic weight.\n\n";
            
            std::cout << "2. Molecules and Compounds:\n";
            std::cout << "   Molecules form when atoms bond together.\n";
            std::cout << "   Compounds are molecules containing different elements.\n\n";
            
            std::cout << "3. Chemical Reactions:\n";
            std::cout << "   Chemical reactions occur when bonds between atoms break or form.\n";
            std::cout << "   Balanced equations show the conservation of mass.\n\n";
            
            std::cout << "4. Stoichiometry:\n";
            std::cout << "   Stoichiometry is the calculation of reactants and products in chemical reactions.\n";
            std::cout << "   The mole is a unit that helps relate mass to number of particles.\n\n";
            
            std::cout << "5. Solutions and Concentration:\n";
            std::cout << "   pH measures the acidity or alkalinity of a solution.\n";
            std::cout << "   Molarity is the number of moles of solute per liter of solution.\n\n";
            
            std::cout << "6. Gas Laws:\n";
            std::cout << "   The ideal gas law (PV = nRT) relates pressure, volume, amount, and temperature.\n";
            std::cout << "   R is the gas constant: " << chemistry_helpers::GAS_CONSTANT << " J/(mol·K)\n\n";
            
            std::cout << "Use 'element_info', 'molecular_weight', 'balance_equation', and other operations for more.\n";
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::ChemistryOpsPlugin plugin;
    plugin.register_ops(interp);
}
