// ==================================================
// fractal_ops.cpp - Fractal Mathematics (Dynamic Loading)
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

extern "C" {

// Helper functions for fractal operations
namespace {
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
        int size = 1;
        for (int i = 0; i < n; ++i) size *= 3;
        
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
}

void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    // mandelbrot: Check if a point is in the Mandelbrot set
    (*op_table)["mandelbrot"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.size() < 3) {
            throw std::runtime_error("mandelbrot requires real, imag, max_iter");
        }
        
        auto max_iter_val = stack.top(); stack.pop();
        auto imag_val = stack.top(); stack.pop();
        auto real_val = stack.top(); stack.pop();
        
        double real = real_val.d;
        double imag = imag_val.d;
        int max_iter = static_cast<int>(max_iter_val.d);
        
        bool in_set = is_in_mandelbrot(real, imag, max_iter);
        
        woflang::WofValue result;
        result.d = in_set ? 1.0 : 0.0;
        stack.push(result);
        
        std::cout << "Point (" << real << ", " << imag << ") is " 
                 << (in_set ? "IN" : "NOT IN") << " the Mandelbrot set" << std::endl;
    };
    
    // mandelbrot_ascii: Generate ASCII art of the Mandelbrot set
    (*op_table)["mandelbrot_ascii"] = [](std::stack<woflang::WofValue>& stack) {
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
            
            x_min = x_min_val.d;
            x_max = x_max_val.d;
            y_min = y_min_val.d;
            y_max = y_max_val.d;
            width = static_cast<int>(width_val.d);
            height = static_cast<int>(height_val.d);
            max_iter = static_cast<int>(max_iter_val.d);
        }
        
        std::string ascii_art = generate_mandelbrot_ascii(
            x_min, x_max, y_min, y_max, width, height, max_iter);
        
        std::cout << "Mandelbrot Set ASCII Art:" << std::endl;
        std::cout << ascii_art;
        
        woflang::WofValue result;
        result.d = 1.0; // Success indicator
        stack.push(result);
    };
    
    // sierpinski_carpet: Generate ASCII art of the Sierpinski carpet
    (*op_table)["sierpinski_carpet"] = [](std::stack<woflang::WofValue>& stack) {
        int n = 3;
        
        if (!stack.empty()) {
            auto n_val = stack.top(); stack.pop();
            n = static_cast<int>(n_val.d);
            n = std::max(1, std::min(n, 4));
        }
        
        std::string ascii_art = generate_sierpinski_carpet(n);
        
        std::cout << ascii_art;
        
        woflang::WofValue result;
        result.d = 1.0; // Success indicator
        stack.push(result);
    };
    
    // sierpinski_triangle: Generate Sierpinski triangle ASCII art
    (*op_table)["sierpinski"] = [](std::stack<woflang::WofValue>& stack) {
        int n = 4;
        
        if (!stack.empty()) {
            auto n_val = stack.top(); stack.pop();
            n = static_cast<int>(n_val.d);
            n = std::max(1, std::min(n, 6));
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
        
        woflang::WofValue result;
        result.d = 1.0; // Success indicator
        stack.push(result);
    };
    
    // cantor: Generate ASCII art of the Cantor set
    (*op_table)["cantor"] = [](std::stack<woflang::WofValue>& stack) {
        int n = 5;
        
        if (!stack.empty()) {
            auto n_val = stack.top(); stack.pop();
            n = static_cast<int>(n_val.d);
            n = std::max(1, std::min(n, 6));
        }
        
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
        
        std::cout << ss.str();
        
        woflang::WofValue result;
        result.d = 1.0; // Success indicator
        stack.push(result);
    };
    
    // hausdorff: Calculate the Hausdorff dimension of a fractal
    (*op_table)["hausdorff"] = [](std::stack<woflang::WofValue>& stack) {
        if (stack.empty()) {
            throw std::runtime_error("hausdorff requires a fractal name");
        }
        
        auto fractal_val = stack.top(); stack.pop();
        
        // For simplicity, we'll use predefined fractal types based on stack value
        double val = fractal_val.d;
        double dimension = 0.0;
        std::string fractal_name;
        
        if (val == 1.0) {
            dimension = std::log(3) / std::log(2);
            fractal_name = "Sierpinski Triangle";
        } else if (val == 2.0) {
            dimension = std::log(8) / std::log(3);
            fractal_name = "Sierpinski Carpet";
        } else if (val == 3.0) {
            dimension = std::log(4) / std::log(3);
            fractal_name = "Koch Curve";
        } else if (val == 4.0) {
            dimension = std::log(2) / std::log(3);
            fractal_name = "Cantor Set";
        } else {
            dimension = 2.0;
            fractal_name = "Mandelbrot Set";
        }
        
        std::cout << fractal_name << " Hausdorff dimension: " << dimension << std::endl;
        
        woflang::WofValue result;
        result.d = dimension;
        stack.push(result);
    };
    
    // fractal_info: Educational information about fractals
    (*op_table)["fractal_info"] = [](std::stack<woflang::WofValue>&) {
        std::cout << "=== Fractal Information ===\n\n";
        std::cout << "Fractals are geometric objects exhibiting self-similarity at different scales.\n";
        std::cout << "They are characterized by non-integer Hausdorff dimensions and infinite detail.\n\n";
        
        std::cout << "Common fractal types available in woflang:\n";
        std::cout << "  - mandelbrot: The Mandelbrot set, one of the most famous fractals\n";
        std::cout << "  - sierpinski: The Sierpinski triangle, formed by removing the middle triangle\n";
        std::cout << "  - sierpinski_carpet: Similar to the triangle, but in 2D\n";
        std::cout << "  - cantor: The Cantor set, formed by repeatedly removing middle thirds\n\n";
        
        std::cout << "Use hausdorff to calculate fractal dimensions:\n";
        std::cout << "  1 hausdorff  # Sierpinski Triangle\n";
        std::cout << "  2 hausdorff  # Sierpinski Carpet\n";
        std::cout << "  3 hausdorff  # Koch Curve\n";
        std::cout << "  4 hausdorff  # Cantor Set\n\n";
    };
}

} // extern "C"