fractal_ops.cpp (Fixed)
cpp#include "../../src/core/woflang.hpp"
#include <iostream>
#include <cmath>

class FractalOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        interp.register_op("mandelbrot", [](WoflangInterpreter& interp) {
            // Takes real, imag, and max_iter from stack, checks membership
            if (interp.stack.size() < 3) { 
                std::cout << "mandelbrot: real imag max_iter\n"; 
                return; 
            }
            
            // Pop values in reverse order (top of stack first)
            auto max_iter_val = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto imag_val = interp.stack.back(); 
            interp.stack.pop_back();
            
            auto real_val = interp.stack.back(); 
            interp.stack.pop_back();
            
            // Type checking
            if (max_iter_val.type != WofType::Integer) {
                std::cout << "mandelbrot: max_iter must be an integer\n";
                return;
            }
            
            // Extract values
            int max_iter = static_cast<int>(std::get<int64_t>(max_iter_val.value));
            
            double imag = 0.0;
            if (imag_val.type == WofType::Double) {
                imag = std::get<double>(imag_val.value);
            } else if (imag_val.type == WofType::Integer) {
                imag = static_cast<double>(std::get<int64_t>(imag_val.value));
            } else {
                std::cout << "mandelbrot: imag must be
            interp.stack.push_back(real_val);
                interp.stack.push_back(imag_val);
                interp.stack.push_back(max_iter_val);
                return;
            }
            
            // Extract values
            double real = real_val.as_numeric();
            double imag = imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            // Check if the point is in the Mandelbrot set
            bool in_set = is_in_mandelbrot(real, imag, max_iter);
            
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
            std::string ascii_art = generate_mandelbrot_ascii(
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
                std::cout << "julia: Need z_real z_imag c_real c_imag max_iterations\n";
                return;
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
                std::cout << "julia: All arguments must be numbers\n";
                interp.stack.push_back(z_real_val);
                interp.stack.push_back(z_imag_val);
                interp.stack.push_back(c_real_val);
                interp.stack.push_back(c_imag_val);
                interp.stack.push_back(max_iter_val);
                return;
            }
            
            // Extract values
            double z_real = z_real_val.as_numeric();
            double z_imag = z_imag_val.as_numeric();
            double c_real = c_real_val.as_numeric();
            double c_imag = c_imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            // Check if the point is in the Julia set
            bool in_set = is_in_julia(z_real, z_imag, c_real, c_imag, max_iter);
            
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
            std::string ascii_art = generate_sierpinski_carpet(n);
            
            // Print the ASCII art
            std::cout << "Sierpinski Carpet (level " << n << "):" << std::endl;
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
            std::string ascii_art = generate_koch_snowflake(n);
            
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
            std::string ascii_art = generate_cantor_set(n);
            
            // Print the ASCII art
            std::cout << "Cantor Set (level " << n << "):" << std::endl;
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
            std::ostringstream ascii_art;
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
                std::cout << "hausdorff: Need fractal_type (string)\n";
                return;
            }
            
            auto fractal_val = interp.stack.back(); interp.stack.pop_back();
            
            if (fractal_val.type != WofType::String && fractal_val.type != WofType::Symbol) {
                std::cout << "hausdorff: Fractal type must be a string or symbol\n";
                interp.stack.push_back(fractal_val);
                return;
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
                std::cout << "hausdorff: Unknown fractal type '" << fractal << "'\n";
                std::cout << "Supported fractals: sierpinski, sierpinski_carpet, koch, cantor, dragon, mandelbrot\n";
                interp.stack.push_back(fractal_val);
                return;
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
    }
};

} // namespace woflang

// Plugin registration function
WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::FractalOpsPlugin plugin;
    plugin.register_ops(interp);
}