// ==================================================
// FIXED: fractal_ops.cpp
// ==================================================
#include "../../src/core/woflang.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <complex>
#include <cstring>
#include <functional>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace woflang {

namespace fractal_helpers {
    // Check if a point is in the Mandelbrot set
    bool is_in_mandelbrot(double real, double imag, int max_iter) {
        std::complex<double> c(real, imag);
        std::complex<double> z(0.0, 0.0);
        
        for (int i = 0; i < max_iter; ++i) {
            z = z * z + c;
            
            if (std::norm(z) > 4.0) {
                return false;
            }
        }
        
        return true;
    }
    
    // Check if a point is in a Julia set
    bool is_in_julia(double z_real, double z_imag, double c_real, double c_imag, int max_iter) {
        std::complex<double> z(z_real, z_imag);
        std::complex<double> c(c_real, c_imag);
        
        for (int i = 0; i < max_iter; ++i) {
            z = z * z + c;
            
            if (std::norm(z) > 4.0) {
                return false;
            }
        }
        
        return true;
    }
    
    // Generate ASCII art of the Mandelbrot set
    std::string generate_mandelbrot_ascii(double x_min, double x_max, double y_min, double y_max,
                                        int width, int height, int max_iter) {
        std::stringstream ss;
        
        double dx = (x_max - x_min) / width;
        double dy = (y_max - y_min) / height;
        
        const char* chars = " .,-:;i+hHM#@";
        int num_chars = std::strlen(chars);
        
        for (int y = 0; y < height; ++y) {
            double imag = y_max - y * dy;
            
            for (int x = 0; x < width; ++x) {
                double real = x_min + x * dx;
                
                std::complex<double> c(real, imag);
                std::complex<double> z(0.0, 0.0);
                
                int iter = 0;
                for (; iter < max_iter; ++iter) {
                    z = z * z + c;
                    
                    if (std::norm(z) > 4.0) {
                        break;
                    }
                }
                
                if (iter == max_iter) {
                    ss << chars[num_chars - 1];
                } else {
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
        int size = 1 << n;
        std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));
        
        std::function<void(int, int, int)> draw_carpet = [&](int x, int y, int size) {
            if (size == 1) {
                grid[y][x] = '*';
                return;
            }
            
            int new_size = size / 3;
            
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (i == 1 && j == 1) {
                        continue;
                    }
                    
                    draw_carpet(x + j * new_size, y + i * new_size, new_size);
                }
            }
        };
        
        draw_carpet(0, 0, size);
        
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
        int size = 60;
        std::vector<std::vector<char>> grid(size, std::vector<char>(size, ' '));
        
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
        
        std::function<void(double, double, double, double, int)> koch = 
            [&](double x1, double y1, double x2, double y2, int depth) {
                if (depth == 0) {
                    draw_line(x1, y1, x2, y2);
                    return;
                }
                
                double dx = (x2 - x1) / 3.0;
                double dy = (y2 - y1) / 3.0;
                
                double x3 = x1 + dx;
                double y3 = y1 + dy;
                
                double x4 = x1 + dx * 1.5 - dy * std::sqrt(3) / 2.0;
                double y4 = y1 + dy * 1.5 + dx * std::sqrt(3) / 2.0;
                
                double x5 = x1 + dx * 2.0;
                double y5 = y1 + dy * 2.0;
                
                koch(x1, y1, x3, y3, depth - 1);
                koch(x3, y3, x4, y4, depth - 1);
                koch(x4, y4, x5, y5, depth - 1);
                koch(x5, y5, x2, y2, depth - 1);
            };
        
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
        
        int width = 80;
        
        std::function<void(int, int, int)> cantor = [&](int left, int right, int level) {
            if (level <= 0) {
                return;
            }
            
            for (int i = 0; i < left; ++i) {
                ss << ' ';
            }
            
            for (int i = left; i < right; ++i) {
                ss << '*';
            }
            
            ss << '\n';
            
            int length = right - left;
            int segment = length / 3;
            
            cantor(left, left + segment, level - 1);
            cantor(right - segment, right, level - 1);
        };
        
        cantor(0, width, n);
        
        return ss.str();
    }
}

class FractalOpsPlugin : public WoflangPlugin {
public:
    void register_ops(WoflangInterpreter& interp) override {
        // mandelbrot: Check if a point is in the Mandelbrot set
        interp.register_op("mandelbrot", [](std::stack<WofValue>& stack) {
            if (stack.size() < 3) {
                throw std::runtime_error("mandelbrot requires real, imag, max_iter");
            }
            
            auto max_iter_val = stack.top(); stack.pop();
            auto imag_val = stack.top(); stack.pop();
            auto real_val = stack.top(); stack.pop();
            
            if (!max_iter_val.is_numeric() || !imag_val.is_numeric() || !real_val.is_numeric()) {
                throw std::runtime_error("mandelbrot requires numeric arguments");
            }
            
            double real = real_val.as_numeric();
            double imag = imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            bool in_set = fractal_helpers::is_in_mandelbrot(real, imag, max_iter);
            
            stack.push(WofValue(in_set ? 1.0 : 0.0));
            
            std::cout << "Point (" << real << ", " << imag << ") is " 
                     << (in_set ? "IN" : "NOT IN") << " the Mandelbrot set" << std::endl;
        });
        
        // mandelbrot_ascii: Generate ASCII art of the Mandelbrot set
        interp.register_op("mandelbrot_ascii", [](std::stack<WofValue>& stack) {
            double x_min = -2.0;
            double x_max = 1.0;
            double y_min = -1.5;
            double y_max = 1.5;
            int width = 60;
            int height = 30;
            int max_iter = 30;
            
            if (stack.size() >= 7) {
                auto max_iter_val = stack.top(); stack.pop();
                auto height_val = stack.top(); stack.pop();
                auto width_val = stack.top(); stack.pop();
                auto y_max_val = stack.top(); stack.pop();
                auto y_min_val = stack.top(); stack.pop();
                auto x_max_val = stack.top(); stack.pop();
                auto x_min_val = stack.top(); stack.pop();
                
                if (x_min_val.is_numeric()) x_min = x_min_val.as_numeric();
                if (x_max_val.is_numeric()) x_max = x_max_val.as_numeric();
                if (y_min_val.is_numeric()) y_min = y_min_val.as_numeric();
                if (y_max_val.is_numeric()) y_max = y_max_val.as_numeric();
                if (width_val.is_numeric()) width = static_cast<int>(width_val.as_numeric());
                if (height_val.is_numeric()) height = static_cast<int>(height_val.as_numeric());
                if (max_iter_val.is_numeric()) max_iter = static_cast<int>(max_iter_val.as_numeric());
            }
            
            std::string ascii_art = fractal_helpers::generate_mandelbrot_ascii(
                x_min, x_max, y_min, y_max, width, height, max_iter);
            
            std::cout << "Mandelbrot Set ASCII Art:" << std::endl;
            std::cout << ascii_art;
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // julia: Check if a point is in a Julia set for a given constant c
        interp.register_op("julia", [](std::stack<WofValue>& stack) {
            if (stack.size() < 5) {
                throw std::runtime_error("julia requires z_real, z_imag, c_real, c_imag, max_iter");
            }
            
            auto max_iter_val = stack.top(); stack.pop();
            auto c_imag_val = stack.top(); stack.pop();
            auto c_real_val = stack.top(); stack.pop();
            auto z_imag_val = stack.top(); stack.pop();
            auto z_real_val = stack.top(); stack.pop();
            
            if (!max_iter_val.is_numeric() || !c_real_val.is_numeric() || 
                !c_imag_val.is_numeric() || !z_real_val.is_numeric() || !z_imag_val.is_numeric()) {
                throw std::runtime_error("julia requires numeric arguments");
            }
            
            double z_real = z_real_val.as_numeric();
            double z_imag = z_imag_val.as_numeric();
            double c_real = c_real_val.as_numeric();
            double c_imag = c_imag_val.as_numeric();
            int max_iter = static_cast<int>(max_iter_val.as_numeric());
            
            bool in_set = fractal_helpers::is_in_julia(z_real, z_imag, c_real, c_imag, max_iter);
            
            stack.push(WofValue(in_set ? 1.0 : 0.0));
            
            std::cout << "Point z = (" << z_real << ", " << z_imag << ") with c = (" 
                     << c_real << ", " << c_imag << ") is " 
                     << (in_set ? "IN" : "NOT IN") << " the Julia set" << std::endl;
        });
                
        // sierpinski_carpet: Generate ASCII art of the Sierpinski carpet
        interp.register_op("sierpinski_carpet", [](std::stack<WofValue>& stack) {
            int n = 3;
            
            if (!stack.empty()) {
                auto n_val = stack.top(); stack.pop();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    n = std::max(1, std::min(n, 4));
                }
            }
            
            std::string ascii_art = fractal_helpers::generate_sierpinski_carpet(n);
            
            std::cout << ascii_art;
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // koch: Generate ASCII art approximation of the Koch snowflake
        interp.register_op("koch", [](std::stack<WofValue>& stack) {
            int n = 3;
            
            if (!stack.empty()) {
                auto n_val = stack.top(); stack.pop();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    n = std::max(1, std::min(n, 5));
                }
            }
            
            std::string ascii_art = fractal_helpers::generate_koch_snowflake(n);
            
            std::cout << ascii_art;
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // cantor: Generate ASCII art of the Cantor set
        interp.register_op("cantor", [](std::stack<WofValue>& stack) {
            int n = 5;
            
            if (!stack.empty()) {
                auto n_val = stack.top(); stack.pop();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    n = std::max(1, std::min(n, 6));
                }
            }
            
            std::string ascii_art = fractal_helpers::generate_cantor_set(n);
            
            std::cout << ascii_art;
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // dragon: Generate the Dragon curve (simple ASCII approximation)
        interp.register_op("dragon", [](std::stack<WofValue>& stack) {
            int n = 10;
            
            if (!stack.empty()) {
                auto n_val = stack.top(); stack.pop();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    n = std::max(1, std::min(n, 15));
                }
            }
            
            std::string directions;
            
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
            
            int width = 80;
            int height = 40;
            std::vector<std::vector<char>> grid(height, std::vector<char>(width, ' '));
            
            int x = width / 2;
            int y = height / 2;
            grid[y][x] = '*';
            
            int dir = 0;
            
            for (char c : directions) {
                if (c == 'L') {
                    dir = (dir + 3) % 4;
                } else {
                    dir = (dir + 1) % 4;
                }
                
                switch (dir) {
                    case 0: x++; break;
                    case 1: y++; break;
                    case 2: x--; break;
                    case 3: y--; break;
                }
                
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    grid[y][x] = '*';
                }
            }
            
            std::stringstream ascii_art;
            ascii_art << "Dragon Curve (level " << n << "):" << std::endl;
            
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    ascii_art << grid[y][x];
                }
                ascii_art << "\n";
            }
            
            std::cout << ascii_art.str();
            
            stack.push(WofValue(1.0)); // Success indicator
        });
        
        // hausdorff: Calculate the Hausdorff dimension of a fractal
        interp.register_op("hausdorff", [](std::stack<WofValue>& stack) {
            if (stack.empty()) {
                throw std::runtime_error("hausdorff requires a fractal name");
            }
            
            auto fractal_val = stack.top(); stack.pop();
            
            if (!fractal_val.is_string()) {
                throw std::runtime_error("hausdorff requires a string fractal name");
            }
            
            std::string fractal = fractal_val.to_string();
            double dimension = 0.0;
            
            if (fractal == "sierpinski" || fractal == "sierpinski_triangle") {
                dimension = std::log(3) / std::log(2);
                std::cout << "Sierpinski Triangle Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "sierpinski_carpet") {
                dimension = std::log(8) / std::log(3);
                std::cout << "Sierpinski Carpet Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "koch" || fractal == "koch_curve") {
                dimension = std::log(4) / std::log(3);
                std::cout << "Koch Curve Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "cantor" || fractal == "cantor_set") {
                dimension = std::log(2) / std::log(3);
                std::cout << "Cantor Set Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "dragon" || fractal == "dragon_curve") {
                dimension = 2.0;
                std::cout << "Dragon Curve Hausdorff dimension: " << dimension << std::endl;
            } else if (fractal == "mandelbrot") {
                dimension = 2.0;
                std::cout << "Mandelbrot Set boundary Hausdorff dimension: " << dimension << std::endl;
            } else {
                throw std::runtime_error("Unknown fractal type: " + fractal);
            }
            
            stack.push(WofValue(dimension));
        });
        
        // fractal_info: Educational information about fractals
        interp.register_op("fractal_info", [](std::stack<WofValue>&) {
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
        interp.register_op("sierpinski", [](std::stack<WofValue>& stack) {
            int n = 4;
            
            if (!stack.empty()) {
                auto n_val = stack.top(); stack.pop();
                
                if (n_val.is_numeric()) {
                    n = static_cast<int>(n_val.as_numeric());
                    n = std::max(1, std::min(n, 6));
                }
            }
            
            std::stringstream ascii_art;
            ascii_art << "Sierpinski Triangle (level " << n << "):\n";
            
            int size = 1 << n;
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
            
            std::cout << ascii_art.str();
            
            stack.push(WofValue(1.0)); // Success indicator
        });
    }
};

} // namespace woflang

WOFLANG_PLUGIN_EXPORT void register_plugin(woflang::WoflangInterpreter& interp) {
    static woflang::FractalOpsPlugin plugin;
    plugin.register_ops(interp);
}