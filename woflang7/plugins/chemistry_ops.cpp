// ==================================================
// FIXED: chemistry_ops.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <regex>
#include <numeric>
#include <set>
#include <sstream>

namespace woflang {

namespace chemistry_helpers {
    // Structure to hold element data
    struct Element {
        std::string symbol;
        std::string name;
        double atomic_weight;
        int atomic_number;
        std::string category;
        double electronegativity;
        int group;
        int period;
        std::string electron_config;
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
    };
    
    // Physical constants
    const double AVOGADRO_NUMBER = 6.02214076e23;
    const double GAS_CONSTANT = 8.31446;
    const double BOLTZMANN_CONSTANT = 1.380649e-23;
    const double ATMOSPHERIC_PRESSURE = 101325;
    
    // Structure to hold a chemical formula and its components
    struct Formula {
        std::string original;
        std::map<std::string, int> elements;
    };
    
    // Parse a chemical formula to extract element symbols and counts
    Formula parse_formula(const std::string& formula_str) {
        Formula result;
        result.original = formula_str;
        
        std::regex element_pattern("([A-Z][a-z]?)([0-9]*)");
        
        auto begin = std::sregex_iterator(formula_str.begin(), formula_str.end(), element_pattern);
        auto end = std::sregex_iterator();
        
        for (std::sregex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i;
            std::string element = match[1].str();
            
            int count = 1;
            if (match[2].length() > 0) {
                count = std::stoi(match[2].str());
            }
            
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
            if (ELEMENTS.find(element) == ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + element);
            }
            
            weight += ELEMENTS.at(element).atomic_weight * count;
        }
        
        return weight;
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

class ChemistryOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // ----- Element Operations -----
        
        // element_info: Get information about an element
        interp.register_op("element_info", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("element_info requires an element symbol");
            }
            
            auto element = stack.top(); stack.pop();
            
            if (!element.is_string()) {
                throw std::runtime_error("Element symbol must be a string");
            }
            
            std::string symbol = element.to_string();
            
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            const auto& elem = chemistry_helpers::ELEMENTS.at(symbol);
            
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
            
            // Push the atomic weight onto the stack
            stack.push(WofValue(elem.atomic_weight));
        });
        
        // atomic_weight: Get the atomic weight of an element
        interp.register_op("atomic_weight", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("atomic_weight requires an element symbol");
            }
            
            auto element = stack.top(); stack.pop();
            
            if (!element.is_string()) {
                throw std::runtime_error("Element symbol must be a string");
            }
            
            std::string symbol = element.to_string();
            
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            double weight = chemistry_helpers::ELEMENTS.at(symbol).atomic_weight;
            
            stack.push(WofValue(weight));
            
            std::cout << "Atomic weight of " << symbol << ": " << weight << " g/mol\n";
        });
        
        // atomic_number: Get the atomic number of an element
        interp.register_op("atomic_number", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("atomic_number requires an element symbol");
            }
            
            auto element = stack.top(); stack.pop();
            
            if (!element.is_string()) {
                throw std::runtime_error("Element symbol must be a string");
            }
            
            std::string symbol = element.to_string();
            
            if (chemistry_helpers::ELEMENTS.find(symbol) == chemistry_helpers::ELEMENTS.end()) {
                throw std::runtime_error("Unknown element: " + symbol);
            }
            
            int number = chemistry_helpers::ELEMENTS.at(symbol).atomic_number;
            
            stack.push(WofValue(static_cast<double>(number)));
            
            std::cout << "Atomic number of " << symbol << ": " << number << "\n";
        });
        
        // ----- Molecular Operations -----
        
        // molecular_weight: Calculate the molecular weight of a chemical formula
        interp.register_op("molecular_weight", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("molecular_weight requires a chemical formula");
            }
            
            auto formula_val = stack.top(); stack.pop();
            
            if (!formula_val.is_string()) {
                throw std::runtime_error("Chemical formula must be a string");
            }
            
            std::string formula_str = formula_val.to_string();
            
            try {
                auto formula = chemistry_helpers::parse_formula(formula_str);
                
                double weight = chemistry_helpers::molecular_weight(formula);
                
                stack.push(WofValue(weight));
                
                std::cout << "Molecular weight of " << formula_str << ": " << weight << " g/mol\n";
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("molecular_weight error: ") + e.what());
            }
        });
        
        // parse_formula: Parse a chemical formula and display its components
        interp.register_op("parse_formula", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("parse_formula requires a chemical formula");
            }
            
            auto formula_val = stack.top(); stack.pop();
            
            if (!formula_val.is_string()) {
                throw std::runtime_error("Chemical formula must be a string");
            }
            
            std::string formula_str = formula_val.to_string();
            
            try {
                auto formula = chemistry_helpers::parse_formula(formula_str);
                
                std::cout << "Formula: " << formula_str << "\n";
                std::cout << "Components:\n";
                
                for (const auto& [element, count] : formula.elements) {
                    std::cout << "  " << element << ": " << count << "\n";
                }
                
                // Push the number of components
                stack.push(WofValue(static_cast<double>(formula.elements.size())));
            } catch (const std::exception& e) {
                throw std::runtime_error(std::string("parse_formula error: ") + e.what());
            }
        });
        
        // ----- Physical Chemistry Operations -----
        
        // ideal_gas_law: Calculate using the ideal gas law (PV = nRT)
        interp.register_op("ideal_gas_law", [](std::stack<WofValue>& stack) {
            if (stack.size() < 6) {
                throw std::runtime_error("ideal_gas_law requires 3 pairs of (name, value)");
            }
            
            std::vector<std::pair<std::string, double>> values;
            
            for (int i = 0; i < 3; i++) {
                auto value = stack.top(); stack.pop();
                auto name = stack.top(); stack.pop();
                
                if (!value.is_numeric()) {
                    throw std::runtime_error("Values must be numeric");
                }
                
                if (!name.is_string()) {
                    throw std::runtime_error("Names must be strings");
                }
                
                std::string name_str = name.to_string();
                double val = value.as_numeric();
                
                values.emplace_back(name_str, val);
            }
            
            std::set<std::string> valid_params = {"P", "V", "n", "T"};
            std::set<std::string> provided_params;
            
            for (const auto& [name, _] : values) {
                if (valid_params.find(name) == valid_params.end()) {
                    throw std::runtime_error("Invalid parameter: " + name + ". Must be P, V, n, or T");
                }
                
                provided_params.insert(name);
            }
            
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
            
            double P = 0, V = 0, n = 0, T = 0;
            for (const auto& [name, value] : values) {
                if (name == "P") P = value;
                else if (name == "V") V = value;
                else if (name == "n") n = value;
                else if (name == "T") T = value;
            }
            
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
            
            stack.push(WofValue(result));
        });
        
        // pH: Calculate pH from hydrogen ion concentration or vice versa
        interp.register_op("pH", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("pH requires a value and direction (to_pH or to_conc)");
            }
            
            auto direction = stack.top(); stack.pop();
            auto value = stack.top(); stack.pop();
            
            if (!value.is_numeric()) {
                throw std::runtime_error("Value must be numeric");
            }
            
            if (!direction.is_string()) {
                throw std::runtime_error("Direction must be a string");
            }
            
            double val = value.as_numeric();
            std::string dir_str = direction.to_string();
            
            if (dir_str == "to_pH") {
                double pH = chemistry_helpers::pH_from_concentration(val);
                stack.push(WofValue(pH));
                std::cout << "pH: " << pH << "\n";
            } else if (dir_str == "to_conc") {
                double conc = chemistry_helpers::concentration_from_pH(val);
                stack.push(WofValue(conc));
                std::cout << "H⁺ concentration: " << conc << " mol/L\n";
            } else {
                throw std::runtime_error("Direction must be 'to_pH' or 'to_conc'");
            }
        });
        
        // ----- Constants -----
        
        // avogadro: Push Avogadro's number
        interp.register_op("avogadro", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(chemistry_helpers::AVOGADRO_NUMBER));
            std::cout << "Avogadro's number: " << chemistry_helpers::AVOGADRO_NUMBER << " mol⁻¹\n";
        });
        
        // gas_constant: Push the gas constant
        interp.register_op("gas_constant", [](std::stack<WofValue>& stack) {
            stack.push(WofValue(chemistry_helpers::GAS_CONSTANT));
            std::cout << "Gas constant: " << chemistry_helpers::GAS_CONSTANT << " J/(mol·K)\n";
        });
        
        // ----- Educational Operations -----
        
        // list_elements: List available elements
        interp.register_op("list_elements", [](std::stack<WofValue>&) {
            std::cout << "Available elements:\n";
            
            std::map<int, std::vector<std::string>> elements_by_period;
            
            for (const auto& [symbol, elem] : chemistry_helpers::ELEMENTS) {
                elements_by_period[elem.period].push_back(symbol);
            }
            
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
        interp.register_op("periodic_table", [](std::stack<WofValue>&) {
            std::cout << "Periodic Table of Elements (ASCII):\n\n";
            
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
        interp.register_op("chemistry_tutorial", [](std::stack<WofValue>&) {
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
            
            std::cout << "Use 'element_info', 'molecular_weight', and other operations for more.\n";
        });
        
        // molarity: Calculate molarity (moles per liter)
        interp.register_op("molarity", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("molarity requires moles and volume (L)");
            }
            
            auto volume = stack.top(); stack.pop();
            auto moles = stack.top(); stack.pop();
            
            if (!moles.is_numeric() || !volume.is_numeric()) {
                throw std::runtime_error("molarity requires numeric values");
            }
            
            double n = moles.as_numeric();
            double v = volume.as_numeric();
            
            if (v <= 0) {
                throw std::runtime_error("Volume must be positive");
            }
            
            double molarity = n / v;
            
            stack.push(WofValue(molarity));
            
            std::cout << "Molarity: " << molarity << " mol/L\n";
        });
        
        // density: Calculate density (mass per volume)
        interp.register_op("density", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("density requires mass and volume");
            }
            
            auto volume = stack.top(); stack.pop();
            auto mass = stack.top(); stack.pop();
            
            if (!mass.is_numeric() || !volume.is_numeric()) {
                throw std::runtime_error("density requires numeric values");
            }
            
            double m = mass.as_numeric();
            double v = volume.as_numeric();
            
            if (v <= 0) {
                throw std::runtime_error("Volume must be positive");
            }
            
            double density = m / v;
            
            stack.push(WofValue(density));
            
            std::cout << "Density: " << density << " g/mL\n";
        });
        
        // Convert between temperature units
        interp.register_op("celsius_to_kelvin", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("celsius_to_kelvin requires a temperature");
            }
            
            auto temp = stack.top(); stack.pop();
            
            if (!temp.is_numeric()) {
                throw std::runtime_error("Temperature must be numeric");
            }
            
            double celsius = temp.as_numeric();
            double kelvin = celsius + 273.15;
            
            stack.push(WofValue(kelvin));
            
            std::cout << celsius << "°C = " << kelvin << " K\n";
        });
        
        interp.register_op("kelvin_to_celsius", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("kelvin_to_celsius requires a temperature");
            }
            
            auto temp = stack.top(); stack.pop();
            
            if (!temp.is_numeric()) {
                throw std::runtime_error("Temperature must be numeric");
            }
            
            double kelvin = temp.as_numeric();
            double celsius = kelvin - 273.15;
            
            stack.push(WofValue(celsius));
            
            std::cout << kelvin << " K = " << celsius << "°C\n";
        });
        
        // Mole calculations
        interp.register_op("moles_to_grams", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("moles_to_grams requires moles and molecular weight");
            }
            
            auto mw = stack.top(); stack.pop();
            auto moles = stack.top(); stack.pop();
            
            if (!moles.is_numeric() || !mw.is_numeric()) {
                throw std::runtime_error("moles_to_grams requires numeric values");
            }
            
            double n = moles.as_numeric();
            double molecular_weight = mw.as_numeric();
            double grams = n * molecular_weight;
            
            stack.push(WofValue(grams));
            
            std::cout << n << " mol × " << molecular_weight << " g/mol = " << grams << " g\n";
        });
        
        interp.register_op("grams_to_moles", [](std::stack<WofValue>& stack) {
            if (stack.size() < 2) {
                throw std::runtime_error("grams_to_moles requires grams and molecular weight");
            }
            
            auto mw = stack.top(); stack.pop();
            auto grams = stack.top(); stack.pop();
            
            if (!grams.is_numeric() || !mw.is_numeric()) {
                throw std::runtime_error("grams_to_moles requires numeric values");
            }
            
            double g = grams.as_numeric();
            double molecular_weight = mw.as_numeric();
            
            if (molecular_weight <= 0) {
                throw std::runtime_error("Molecular weight must be positive");
            }
            
            double moles = g / molecular_weight;
            
            stack.push(WofValue(moles));
            
            std::cout << g << " g ÷ " << molecular_weight << " g/mol = " << moles << " mol\n";
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::ChemistryOpsPlugin plugin;
    plugin.register_ops(interp);
}