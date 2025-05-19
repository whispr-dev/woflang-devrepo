#include "../../src/core/woflang.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <complex>

namespace woflang {

/**
 * @brief Helper functions for fractal operations
 */
namespace fractal_helpers {
    // Check if a point is in the Mandelbrot set
    bool is_in_mandelbrot(double real, double imag, int max_iter) {
        std::complex<double> c(real, imag);
        std::complex<double> z(0.0, 0.0);
        
        for (int i = 0; i < max_iter; ++i) {
            z = z * z + c;
            
            // If the point escapes, it's not in the set
            if (std::norm(z) > 4.0) {
                return false;
            }
        }
        
        // If it hasn't escaped after max_iter, consider it in the set
        return true;
    }
    
    // Check if a point is in a Julia set
    bool is_in_julia(double z_real, double z_imag, double c_real, double c_imag, int max_iter) {
        std::complex<double> z(z_real, z_imag);
        std::complex<double> c(c_real, c_imag);
        
        for (int i = 0; i < max_iter; ++i) {
            z = z * z + c;
            
            // If the point escapes, it's not in the set
            if (std::norm(z) > 4.0) {
                return false;
            }
        }
        
        // If it hasn't escaped after max_iter, consider it in the set
        return true;
    }
    
    // Generate ASCII art of the Mandelbrot set
    std::string generate_mandelbrot_ascii(double x_min, double x_max, double y_min, double y_max,
                                        int width, int height, int max_iter) {
        std::stringstream ss;
        
        // Size of each cell in the complex plane
        double dx = (x_max - x_min) / width;
        double dy = (y_max - y_min) / height;
        
        // Characters to represent the set (from least to most iterations)
        const char* chars = " .,-:;i+hHM#@";
        int num_chars = std::strlen(chars);
        
        for (int y = 0; y < height; ++y) {
            double imag = y_max - y * dy;
            
            for (int x = 0; x < width; ++x) {
                double real = x_min + x * dx;
                
                // Check if the point is in the set
                std::complex<double> c(real, imag);
                std::complex<double> z(0.0, 0.0);
                
                int iter = 0;
                for (; iter < max_iter; ++iter) {
                    z = z * z + c;
                    
                    if (std::norm(z) > 4.0) {
                        break;
                    }
                }
                
                // Choose a character based on the number of iterations
                if (iter == max_iter) {
                    ss << chars[num_chars - 1];  // In the set
                } else {
                    // Map iterations to character index
                    int char_idx = static_cast<int>(static_cast<double>(iter) / max_iter * (num_chars - 1));
                    ss << chars[char_idx];
                }
            }
            
            ss << '\n';
        }
        
        return ss.str();
    }
    
    // Generate ASCII art of the Sierpinski carpet
    std::string generate_sierpinski_carpet(int n) {
        int size = 1 << n;  // 2^n
        std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));
        
        // Helper function to recursively draw the carpet
        std::function<void(int, int, int)> draw_carpet = [&](int x, int y, int size) {
            if (size == 1) {
                grid[y][x] = '*';
                return;
            }
            
            int new_size = size / 3;
            
            // Draw the 8 outer squares (skip the middle)
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == 1 && j == 1) {
                        continue;  // Skip the middle square
                    }
                    
                    draw_carpet(x + j * new_size, y + i * new_size, new_size);
                }
            }
        };
        
        // Draw the carpet
        draw_carpet(0, 0, size);
        
        // Convert to string
        std::stringstream ss;
        ss << "Sierpinski Carpet (level " << n << "):" << std::endl;
        
        for (const auto& row : grid) {
            for (char c : row) {
                ss << c;
            }
            ss << '\n';
        }
        
        return ss.str();
    }
    
    // Generate ASCII art of the Koch snowflake
    std::string generate_koch_snowflake(int n) {
        int size = 60;  // Width of the canvas
        std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));
        
        // Helper function to draw a line
        auto draw_line = [&](double x1, double y1, double x2, double y2) {
            double dx = x2 - x1;
            double dy = y2 - y1;
            double steps = std::max(std::abs(dx), std::abs(dy));
            
            double x_inc = dx / steps;
            double y_inc = dy / steps;
            
            double x = x1;
            double y = y1;
            
            for (int i = 0; i <= steps; ++i) {
                int ix = static_cast<int>(x);
                int iy = static_cast<int>(y);
                
                if (ix >= 0 && ix < size && iy >= 0 && iy < size) {
                    grid[iy][ix] = '*';
                }
                
                x += x_inc;
                y += y_inc;
            }
        };
        
        // Helper function to recursively draw the Koch curve
        std::function<void(double, double, double, double, int)> koch = 
            [&](double x1, double y1, double x2, double y2, int depth) {
                if (depth == 0) {
                    draw_line(x1, y1, x2, y2);
                    return;
                }
                
                // Calculate the four new points
                double dx = (x2 - x1) / 3.0;
                double dy = (y2 - y1) / 3.0;
                
                double x3 = x1 + dx;
                double y3 = y1 + dy;
                
                double x4 = x1 + dx * 1.5 - dy * std::sqrt(3) / 2.0;
                double y4 = y1 + dy * 1.5 + dx * std::sqrt(3) / 2.0;
                
                double x5 = x1 + dx * 2.0;
                double y5 = y1 + dy * 2.0;
                
                // Recursively draw the four segments
                koch(x1, y1, x3, y3, depth - 1);
                koch(x3, y3, x4, y4, depth - 1);
                koch(x4, y4, x5, y5, depth - 1);
                koch(x5, y5, x2, y2, depth - 1);
            };
        
        // Draw the three sides of the snowflake
        double centerX = size / 2.0;
        double centerY = size / 2.0;
        double radius = size / 3.0;
        
        double x1 = centerX;
        double y1 = centerY - radius;
        
        double x2 = centerX + radius * std::cos(7 * M_PI / 6);
        double y2 = centerY + radius * std::sin(7 * M_PI / 6);
        
        double x3 = centerX + radius * std::cos(11 * M_PI / 6);
        double y3 = centerY + radius * std::sin(11 * M_PI / 6);
        
        koch(x1, y1, x2, y2, n);
        koch(x2, y2, x3, y3, n);
        koch(x3, y3, x1, y1, n);
        
        // Convert to string
        std::stringstream ss;
        ss << "Koch Snowflake (level " << n << "):" << std::endl;
        
        for (const auto& row : grid) {
            for (char c : row) {
                ss << c;
            }
            ss << '\n';
        }
        
        return ss.str();
    }
    
    // Generate ASCII art of the Cantor set
    std::string generate_cantor_set(int n) {
        std::stringstream ss;
        ss << "Cantor Set (level " << n << "):" << std::endl;
        
        int width = 80;  // Width of the canvas
        
        // Helper function to recursively draw the Cantor set
        std::function<void(int, int, int)> cantor = [&](int left, int right, int level) {
            if (level <= 0) {
                return;
            }
            
            // Draw current level
            for (int i = 0; i < left; ++i) {
                ss << ' ';
            }
            
            for (int i = left; i < right; ++i) {
                ss << '*';
            }
            
            ss << '\n';
            
            // Calculate new bounds
            int length = right - left;
            int segment = length / 3;
            
            // Recursively draw the next level
            cantor(left, left + segment, level - 1);
            cantor(right - segment, right, level - 1);
        };
        
        // Draw the Cantor set
        cantor(0, width, n);
        
        return ss.str();
    }
}

/**
 * @brief Fractal operations plugin for Woflang
 * 
 * This plugin provides various fractal-related operations.
 */
class FractalOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // mandelbrot: Check if a point is in the Mandelbrot set
        interp.register_op("mandelbrot", [](WoflangInterpreter& interp) {
            // Takes real, imag, and max_iter from stack
            if (interp.stack.size() < 3) {
                throw std::runtime_error("Stack underflow on mandelbrot");
            }
            
            // Pop values in reverse order
            auto max_iter_val = interp.stack.back(); interp.stack.pop_back();
            auto imag_val = interp.stack.back(); interp.stack.pop_back();
            auto real_val = interp.stack.back(); interp.stack.pop_back();
            
            // Type checking
            if (!max_iter_val.is_numeric() || !imag_val.is_numeric() || !real_val.is_numeric()) {
                throw std::runtime_error("Type error: mandelbrot requires numeric arguments");
            }
            
            // Extract values
            double real = real_val.as_numeric();
            double imag = imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            // Check if the point is in the Mandelbrot set
            bool in_set = fractal_helpers::is_in_mandelbrot(real, imag, max_iter);
            
            // Push the result (1 for in set, 0 for not in set)
            interp.stack.emplace_back(in_set ? 1LL : 0LL);
            
            // Print the result
            std::cout << "Point (" << real << ", " << imag << ") is " 
                     << (in_set ? "IN" : "NOT IN") << " the Mandelbrot set" << std::endl;
        });
        
        // mandelbrot_ascii: Generate ASCII art of the Mandelbrot set
        interp.register_op("mandelbrot_ascii", [](WoflangInterpreter& interp) {
            // Default parameters
            double x_min = -2.0;
            double x_max = 1.0;
            double y_min = -1.5;
            double y_max = 1.5;
            int width = 60;
            int height = 30;
            int max_iter = 30;
            
            // If parameters are provided on the stack, use them
            if (interp.stack.size() >= 7) {
                auto max_iter_val = interp.stack.back(); interp.stack.pop_back();
                auto height_val = interp.stack.back(); interp.stack.pop_back();
                auto width_val = interp.stack.back(); interp.stack.pop_back();
                auto y_max_val = interp.stack.back(); interp.stack.pop_back();
                auto y_min_val = interp.stack.back(); interp.stack.pop_back();
                auto x_max_val = interp.stack.back(); interp.stack.pop_back();
                auto x_min_val = interp.stack.back(); interp.stack.pop_back();
                
                // Check types and update values
                if (x_min_val.is_numeric()) x_min = x_min_val.as_numeric();
                if (x_max_val.is_numeric()) x_max = x_max_val.as_numeric();
                if (y_min_val.is_numeric()) y_min = y_min_val.as_numeric();
                if (y_max_val.is_numeric()) y_max = y_max_val.as_numeric();
                if (width_val.is_numeric()) width = static_cast<int>(width_val.as_numeric());
                if (height_val.is_numeric()) height = static_cast<int>(height_val.as_numeric());
                if (max_iter_val.is_numeric()) max_iter = static_cast<int>(max_iter_val.as_numeric());
            }
            
            // Generate the ASCII art
            std::string ascii_art = fractal_helpers::generate_mandelbrot_ascii(
                x_min, x_max, y_min, y_max, width, height, max_iter);
            
            // Print the ASCII art
            std::cout << "Mandelbrot Set ASCII Art:" << std::endl;
            std::cout << ascii_art;
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art);
        });
        
        // julia: Check if a point is in a Julia set for a given constant c
        interp.register_op("julia", [](WoflangInterpreter& interp) {
            // Need z_real, z_imag, c_real, c_imag, max_iterations
            if (interp.stack.size() < 5) {
                throw std::runtime_error("Stack underflow on julia");
            }
            
            // Pop values in reverse order
            auto max_iter_val = interp.stack.back(); interp.stack.pop_back();
            auto c_imag_val = interp.stack.back(); interp.stack.pop_back();
            auto c_real_val = interp.stack.back(); interp.stack.pop_back();
            auto z_imag_val = interp.stack.back(); interp.stack.pop_back();
            auto z_real_val = interp.stack.back(); interp.stack.pop_back();
            
            // Check types
            if (!max_iter_val.is_numeric() || !c_real_val.is_numeric() || 
                !c_imag_val.is_numeric() || !z_real_val.is_numeric() || !z_imag_val.is_numeric()) {
                throw std::runtime_error("Type error: julia requires numeric arguments");
            }
            
            // Extract values
            double z_real = z_real_val.as_numeric();
            double z_imag = z_imag_val.as_numeric();
            double c_real = c_real_val.as_numeric();
            double c_imag = c_imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            // Check if the point is in the Julia set
            bool in_set = fractal_helpers::is_in_julia(z_real, z_imag, c_real, c_imag, max_iter);
            
            // Push the result (1 for in set, 0 for not in set)
            interp.stack.emplace_back(in_set ? 1LL : 0LL);
            
            // Print the result
            std::cout << "Point z = (" << z_real << ", " << z_imag << ") with c = (" 
                     << c_real << ", " << c_imag << ") is " 
                     << (in_set ? "IN" : "NOT IN") << " the Julia set" << std::endl;
        });
                
        // sierpinski_carpet: Generate ASCII art of the Sierpinski carpet
        interp.register_op("sierpinski_carpet", [](WoflangInterpreter& interp) {
            // Default level
            int n = 3;
            
            // If a level is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto n_val = interp.stack.back(); interp.stack.pop_back();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    // Clamp to reasonable range
                    n = std::max(1, std::min(n, 4));
                }
            }
            
            // Generate the ASCII art
            std::string ascii_art = fractal_helpers::generate_sierpinski_carpet(n);
            
            // Print the ASCII art
            std::cout << ascii_art;
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art);
        });
        
        // koch: Generate ASCII art approximation of the Koch snowflake
        interp.register_op("koch", [](WoflangInterpreter& interp) {
            // Default level
            int n = 3;
            
            // If a level is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto n_val = interp.stack.back(); interp.stack.pop_back();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    // Clamp to reasonable range
                    n = std::max(1, std::min(n, 5));
                }
            }
            
            // Generate the ASCII art
            std::string ascii_art = fractal_helpers::generate_koch_snowflake(n);
            
            // Print the ASCII art
            std::cout << ascii_art;
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art);
        });
        
        // cantor: Generate ASCII art of the Cantor set
        interp.register_op("cantor", [](WoflangInterpreter& interp) {
            // Default level
            int n = 5;
            
            // If a level is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto n_val = interp.stack.back(); interp.stack.pop_back();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    // Clamp to reasonable range
                    n = std::max(1, std::min(n, 6));
                }
            }
            
            // Generate the ASCII art
            std::string ascii_art = fractal_helpers::generate_cantor_set(n);
            
            // Print the ASCII art
            std::cout << ascii_art;
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art);
        });
        
        // dragon: Generate the Dragon curve (simple ASCII approximation)
        interp.register_op("dragon", [](WoflangInterpreter& interp) {
            // Default level
            int n = 10;
            
            // If a level is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto n_val = interp.stack.back(); interp.stack.pop_back();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    // Clamp to reasonable range
                    n = std::max(1, std::min(n, 15));
                }
            }
            
            // Dragon curve directions (R = right, L = left)
            std::string directions;
            
            // Generate the dragon curve directions
            for (int i = 0; i < n; ++i) {
                std::string new_dirs;
                for (char c : directions) {
                    new_dirs += (c == 'R') ? "R" : "L";
                }
                new_dirs += "R";
                for (auto it = directions.rbegin(); it != directions.rend(); ++it) {
                    new_dirs += (*it == 'R') ? "L" : "R";
                }
                directions = new_dirs;
            }
            
            // Convert directions to a grid
            int width = 80;
            int height = 40;
            std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
            
            // Start in the middle
            int x = width / 2;
            int y = height / 2;
            grid[y][x] = '*';
            
            // Current direction (0 = right, 1 = down, 2 = left, 3 = up)
            int dir = 0;
            
            // Follow the directions
            for (char c : directions) {
                // Turn left or right
                if (c == 'L') {
                    dir = (dir + 3) % 4;  // Turn left = -1 mod 4
                } else {
                    dir = (dir + 1) % 4;  // Turn right = +1 mod 4
                }
                
                // Move in the current direction
                switch (dir) {
                    case 0: x++; break;  // Right
                    case 1: y++; break;  // Down
                    case 2: x--; break;  // Left
                    case 3: y--; break;  // Up
                }
                
                // Mark the new position
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    grid[y][x] = '*';
                }
            }
            
            // Convert grid to ASCII art
            std::stringstream ascii_art;
            ascii_art << "Dragon Curve (level " << n << "):" << std::endl;
            
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    ascii_art << grid[y][x];
                }
                ascii_art << "\n";
            }
            
            // Print the ASCII art
            std::cout << ascii_art.str();
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art.str());
        });
        
        // hausdorff: Calculate the Hausdorff dimension of a fractal
        interp.register_op("hausdorff", [](WoflangInterpreter& interp) {
            if (interp.stack.empty()) {
                throw std::runtime_error("Stack underflow on hausdorff");
            }
            
            auto fractal_val = interp.stack.back(); interp.stack.pop_back();
            
            if (fractal_val.type != WofType::String && fractal_val.type != WofType::Symbol) {
                throw std::runtime_error("Type error: hausdorff requires a string or symbol");
            }
            
            std::string fractal = std::get<std::string>(fractal_val.value);
            double dimension = 0.0;
            
            // Calculate the Hausdorff dimension based on the fractal type
            if (fractal == "sierpinski" || fractal == "sierpinski_triangle") {
                dimension = std::log(3) / std::log(2);  // log_2(3) ≈ 1.585
                std::cout << "Sierpinski Triangle Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "sierpinski_carpet") {
                dimension = std::log(8) / std::log(3);  // log_3(8) ≈ 1.893
                std::cout << "Sierpinski Carpet Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "koch" || fractal == "koch_curve") {
                dimension = std::log(4) / std::log(3);  // log_3(4) ≈ 1.262
                std::cout << "Koch Curve Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "cantor" || fractal == "cantor_set") {
                dimension = std::log(2) / std::log(3);  // log_3(2) ≈ 0.631
                std::cout << "Cantor Set Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "dragon" || fractal == "dragon_curve") {
                dimension = 2.0;  // The Dragon curve is space-filling, so its dimension is 2
                std::cout << "Dragon Curve Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "mandelbrot") {
                dimension = 2.0;  // The Mandelbrot set's boundary has a dimension of 2
                std::cout << "Mandelbrot Set boundary Hausdorff dimension: " << dimension << std::endl;
            } else {
                throw std::runtime_error("Unknown fractal type: " + fractal);
            }
            
            // Push the dimension
            interp.stack.emplace_back(dimension);
        });
        
        // Add educational information about fractals
        interp.register_op("fractal_info", [](WoflangInterpreter& interp) {
            std::cout << "=== Fractal Information ===\n\n";
            std::cout << "Fractals are geometric objects exhibiting self-similarity at different scales.\n";
            std::cout << "They are characterized by non-integer Hausdorff dimensions and infinite detail.\n\n";
            
            std::cout << "Common fractal types available in woflang:\n";
            std::cout << "  - mandelbrot: The Mandelbrot set, one of the most famous fractals\n";
            std::cout << "  - julia: Julia sets, related to the Mandelbrot set\n";
            std::cout << "  - sierpinski: The Sierpinski triangle, formed by removing the middle triangle\n";
            std::cout << "  - sierpinski_carpet: Similar to the triangle, but in 2D\n";
            std::cout << "  - koch: The Koch snowflake, with an infinitely long perimeter\n";
            std::cout << "  - cantor: The Cantor set, formed by repeatedly removing middle thirds\n";
            std::cout << "  - dragon: The Dragon curve, formed by folding a strip of paper\n\n";
            
            std::cout << "Use hausdorff to calculate fractal dimensions.\n";
        });
        
        // sierpinski_triangle: Generate Sierpinski triangle ASCII art
        interp.register_op("sierpinski", [](WoflangInterpreter& interp) {
            // Default level
            int n = 4;
            
            // If a level is provided on the stack, use it
            if (!interp.stack.empty()) {
                auto n_val = interp.stack.back(); interp.stack.pop_back();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    // Clamp to reasonable range
                    n = std::max(1, std::min(n, 6));
                }
            }
            
            std::stringstream ascii_art;
            ascii_art << "Sierpinski Triangle (level " << n << "):\n";
            
            int size = 1 << n;  // 2^n
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    if ((x & y) == 0) {
                        ascii_art << "*";
                    } else {
                        ascii_art << " ";
                    }
                }
                ascii_art << "\n";
            }
            
            // Print the ASCII art
            std::cout << ascii_art.str();
            
            // Push the result as a string
            interp.stack.emplace_back(ascii_art.str());
        });
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::FractalOpsPlugin plugin;
    plugin.register_ops(interp);
}




















