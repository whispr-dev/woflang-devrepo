// plugins/fractal_ops.cpp - Enhanced with color support

#include "../../src/core/woflang.hpp"
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <complex>
#include <cstring>
#include <functional>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ========== Color palette system ==========
struct RGB {
    uint8_t r, g, b;
    RGB(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0) : r(red), g(green), b(blue) {}
};

// Beautiful pastel palette inspired by sunset/aurora
static std::vector<RGB> generate_pastel_palette(int size) {
    std::vector<RGB> palette;
    palette.reserve(size);
    
    for (int i = 0; i < size; ++i) {
        double t = double(i) / (size - 1);  // 0.0 to 1.0
        
        // Multi-phase color flow: deep blue -> purple -> pink -> orange -> yellow
        RGB color;
        if (t < 0.2) {
            // Deep blue to purple
            double phase = t / 0.2;
            color.r = uint8_t(20 + 60 * phase);    // 20 -> 80
            color.g = uint8_t(10 + 30 * phase);    // 10 -> 40  
            color.b = uint8_t(80 + 100 * phase);   // 80 -> 180
        } else if (t < 0.4) {
            // Purple to pink
            double phase = (t - 0.2) / 0.2;
            color.r = uint8_t(80 + 120 * phase);   // 80 -> 200
            color.g = uint8_t(40 + 60 * phase);    // 40 -> 100
            color.b = uint8_t(180 - 30 * phase);   // 180 -> 150
        } else if (t < 0.6) {
            // Pink to coral
            double phase = (t - 0.4) / 0.2;
            color.r = uint8_t(200 + 40 * phase);   // 200 -> 240
            color.g = uint8_t(100 + 80 * phase);   // 100 -> 180
            color.b = uint8_t(150 - 50 * phase);   // 150 -> 100
        } else if (t < 0.8) {
            // Coral to orange
            double phase = (t - 0.6) / 0.2;
            color.r = uint8_t(240 + 15 * phase);   // 240 -> 255
            color.g = uint8_t(180 + 60 * phase);   // 180 -> 240
            color.b = uint8_t(100 - 70 * phase);   // 100 -> 30
        } else {
            // Orange to bright yellow
            double phase = (t - 0.8) / 0.2;
            color.r = 255;                          // Stay at 255
            color.g = uint8_t(240 + 15 * phase);   // 240 -> 255
            color.b = uint8_t(30 + 50 * phase);    // 30 -> 80
        }
        
        palette.push_back(color);
    }
    
    return palette;
}

// Convert RGB to ANSI 256-color code (approximate)
static int rgb_to_ansi256(const RGB& color) {
    // Simple 6x6x6 color cube mapping
    int r = (color.r * 5) / 255;
    int g = (color.g * 5) / 255;
    int b = (color.b * 5) / 255;
    return 16 + 36 * r + 6 * g + b;
}

// ========== Enhanced Mandelbrot renderer ==========
const char* mandel_charset = ".:;irsXA253hMHGS#9B&@";

static std::string generate_mandelbrot_ascii(double x_min, double x_max, double y_min, double y_max,
                                             int width, int height, int max_iter, bool use_color = false) {
    std::stringstream ss;
    std::vector<RGB> palette = generate_pastel_palette(max_iter + 1);
    
    double dx = (x_max - x_min) / width;
    double dy = (y_max - y_min) / height;
    int num_chars = std::strlen(mandel_charset);
    
    for (int y = 0; y < height; ++y) {
        double imag = y_max - y * dy;
        for (int x = 0; x < width; ++x) {
            double real = x_min + x * dx;
            std::complex<double> c(real, imag);
            std::complex<double> z(0.0, 0.0);
            int iter = 0;
            
            for (; iter < max_iter; ++iter) {
                z = z * z + c;
                if (std::norm(z) > 4.0) break;
            }
            
            int char_idx = (iter * (num_chars - 1)) / max_iter;
            char display_char = mandel_charset[char_idx];
            
            if (use_color && iter < max_iter) {
                // Use ANSI 256-color codes for beautiful gradients
                int color_code = rgb_to_ansi256(palette[iter]);
                ss << "\033[38;5;" << color_code << "m" << display_char << "\033[0m";
            } else {
                ss << display_char;
            }
        }
        ss << '\n';
    }
    return ss.str();
}

// Generate PPM image file (portable pixmap - simple but widely supported)
static void generate_mandelbrot_ppm(const std::string& filename, double x_min, double x_max, 
                                   double y_min, double y_max, int width, int height, int max_iter) {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "[ERROR] Could not create " << filename << std::endl;
        return;
    }
    
    // PPM header
    file << "P3\n" << width << " " << height << "\n255\n";
    
    std::vector<RGB> palette = generate_pastel_palette(max_iter + 1);
    double dx = (x_max - x_min) / width;
    double dy = (y_max - y_min) / height;
    
    for (int y = 0; y < height; ++y) {
        double imag = y_max - y * dy;
        for (int x = 0; x < width; ++x) {
            double real = x_min + x * dx;
            std::complex<double> c(real, imag);
            std::complex<double> z(0.0, 0.0);
            int iter = 0;
            
            for (; iter < max_iter; ++iter) {
                z = z * z + c;
                if (std::norm(z) > 4.0) break;
            }
            
            RGB color = (iter < max_iter) ? palette[iter] : RGB(0, 0, 0);  // Black for set points
            file << int(color.r) << " " << int(color.g) << " " << int(color.b) << " ";
        }
        file << "\n";
    }
    
    file.close();
    std::cout << "[SUCCESS] Beautiful pastel Mandelbrot saved to " << filename << std::endl;
}

// === Enhanced Mandelbrot ops ===
static void op_mandelbrot_ascii(std::stack<woflang::WofValue>& stack) {
    // Default values:
    double x_min = -2.0, x_max = 1.0, y_min = -1.0, y_max = 1.0;
    int width = 40, height = 20, max_iter = 20;

    // 7 args expected: width height x_min x_max y_min y_max max_iter
    if (stack.size() >= 7) {
        max_iter = static_cast<int>(stack.top().d); stack.pop();
        y_max = stack.top().d; stack.pop();
        y_min = stack.top().d; stack.pop();
        x_max = stack.top().d; stack.pop();
        x_min = stack.top().d; stack.pop();
        height = static_cast<int>(stack.top().d); stack.pop();
        width = static_cast<int>(stack.top().d); stack.pop();
    }

    std::cout << "[DEBUG] Mandelbrot args: width=" << width << " height=" << height
        << " x_min=" << x_min << " x_max=" << x_max
        << " y_min=" << y_min << " y_max=" << y_max
        << " max_iter=" << max_iter << std::endl;

    // Generate colored ASCII
    std::string ascii_art = generate_mandelbrot_ascii(
        x_min, x_max, y_min, y_max, width, height, max_iter, true
    );

    std::cout << "Mandelbrot Set (Pastel Colors):\n" << ascii_art << std::endl;

    woflang::WofValue result; result.d = 1.0; stack.push(result);
}

// New operation for high-res image generation
static void op_mandelbrot_image(std::stack<woflang::WofValue>& stack) {
    // Default values for high-res image
    double x_min = -2.0, x_max = 1.0, y_min = -1.0, y_max = 1.0;
    int width = 800, height = 600, max_iter = 100;

    // 7 args expected: width height x_min x_max y_min y_max max_iter
    if (stack.size() >= 7) {
        max_iter = static_cast<int>(stack.top().d); stack.pop();
        y_max = stack.top().d; stack.pop();
        y_min = stack.top().d; stack.pop();
        x_max = stack.top().d; stack.pop();
        x_min = stack.top().d; stack.pop();
        height = static_cast<int>(stack.top().d); stack.pop();
        width = static_cast<int>(stack.top().d); stack.pop();
    }

    std::cout << "[DEBUG] Generating high-res Mandelbrot image: " << width << "x" << height 
              << " with " << max_iter << " iterations" << std::endl;

    generate_mandelbrot_ppm("mandelbrot_pastel.ppm", x_min, x_max, y_min, y_max, width, height, max_iter);

    woflang::WofValue result; result.d = 1.0; stack.push(result);
}

// === Existing fractal ops (unchanged) ===
static bool is_menger_square(int x, int y, int level) {
    while (level > 0) {
        if (x % 3 == 1 && y % 3 == 1)
            return false;
        x /= 3;
        y /= 3;
        level--;
    }
    return true;
}

static void op_menger_square(std::stack<woflang::WofValue>& stack) {
    if (stack.empty())
        throw std::runtime_error("menger_square: stack underflow (need depth)");
    int level = int(stack.top().d); stack.pop();
    if (level < 0 || level > 5)
        throw std::runtime_error("menger_square: level must be 0 <= n <= 5");
    int size = std::pow(3, level);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x)
            std::cout << (is_menger_square(x, y, level) ? "█" : " ");
        std::cout << "\n";
    }
    woflang::WofValue result; result.d = 1.0; stack.push(result);
}

static std::string generate_sierpinski_carpet(int n) {
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
                if (i == 1 && j == 1) continue;
                draw_carpet(x + j * new_size, y + i * new_size, new_size);
            }
        }
    };
    draw_carpet(0, 0, size);
    std::stringstream ss;
    ss << "Sierpinski Carpet (level " << n << "):" << std::endl;
    for (const auto& row : grid) {
        for (char c : row) ss << c;
        ss << '\n';
    }
    return ss.str();
}

static void op_sierpinski_carpet(std::stack<woflang::WofValue>& stack) {
    int n = 3;
    if (!stack.empty()) {
        auto n_val = stack.top(); stack.pop();
        n = static_cast<int>(n_val.d);
        n = std::max(1, std::min(n, 4));
    }
    std::string ascii_art = generate_sierpinski_carpet(n);
    std::cout << ascii_art;
    woflang::WofValue result; result.d = 1.0; stack.push(result);
}

// === Plugin registration ===
extern "C" void init_plugin(woflang::WoflangInterpreter::OpTable* op_table) {
    (*op_table)["mandelbrot_ascii"] = op_mandelbrot_ascii;      // Now with ANSI colors!
    (*op_table)["mandelbrot_image"] = op_mandelbrot_image;      // High-res PPM image
    (*op_table)["menger_square"] = op_menger_square;
    (*op_table)["sierpinski_carpet"] = op_sierpinski_carpet;
}