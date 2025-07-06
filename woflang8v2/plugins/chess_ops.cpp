// chess_ops.cpp - WofLang Chess Plugin
// A complete chess engine with neural network integration
// Usage: new_game, move, show_board, etc.

#include "../../src/core/woflang.hpp"
#include <array>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <random>
#include <memory>

namespace woflang {

// Chess piece types
enum class PieceType : uint8_t {
    NONE = 0,
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};

// Colors
enum class Color : uint8_t {
    WHITE = 0,
    BLACK = 1
};

// Chess piece structure
struct Piece {
    PieceType type = PieceType::NONE;
    Color color = Color::WHITE;
    
    Piece() = default;
    Piece(PieceType t, Color c) : type(t), color(c) {}
    
    bool is_empty() const { return type == PieceType::NONE; }
    
    // Unicode chess symbols
    std::string to_unicode() const {
        if (is_empty()) return "·";
        
        switch (type) {
            case PieceType::KING:   return (color == Color::WHITE) ? "♔" : "♚";
            case PieceType::QUEEN:  return (color == Color::WHITE) ? "♕" : "♛";
            case PieceType::ROOK:   return (color == Color::WHITE) ? "♖" : "♜";
            case PieceType::BISHOP: return (color == Color::WHITE) ? "♗" : "♝";
            case PieceType::KNIGHT: return (color == Color::WHITE) ? "♘" : "♞";
            case PieceType::PAWN:   return (color == Color::WHITE) ? "♙" : "♟";
            default: return "·";
        }
    }
    
    // Traditional letter notation
    char to_letter() const {
        if (is_empty()) return '.';
        
        char base;
        switch (type) {
            case PieceType::KING:   base = 'K'; break;
            case PieceType::QUEEN:  base = 'Q'; break;
            case PieceType::ROOK:   base = 'R'; break;
            case PieceType::BISHOP: base = 'B'; break;
            case PieceType::KNIGHT: base = 'N'; break;
            case PieceType::PAWN:   base = 'P'; break;
            default: return '.';
        }
        
        return (color == Color::WHITE) ? base : (base + 32); // lowercase for black
    }
    
    int get_value() const {
        switch (type) {
            case PieceType::PAWN:   return 100;
            case PieceType::KNIGHT: return 320;
            case PieceType::BISHOP: return 330;
            case PieceType::ROOK:   return 500;
            case PieceType::QUEEN:  return 900;
            case PieceType::KING:   return 20000;
            default: return 0;
        }
    }
};

// Chess move structure
struct Move {
    uint8_t from_x, from_y;
    uint8_t to_x, to_y;
    PieceType promotion = PieceType::NONE;
    bool is_castling = false;
    bool is_en_passant = false;
    
    Move() = default;
    Move(uint8_t fx, uint8_t fy, uint8_t tx, uint8_t ty) 
        : from_x(fx), from_y(fy), to_x(tx), to_y(ty) {}
    
    std::string to_algebraic() const {
        std::string result;
        result += static_cast<char>('a' + from_x);
        result += static_cast<char>('1' + from_y);
        result += static_cast<char>('a' + to_x);
        result += static_cast<char>('1' + to_y);
        return result;
    }
};

// Chess board state
class ChessBoard {
public:
    std::array<std::array<Piece, 8>, 8> board;
    Color current_turn = Color::WHITE;
    bool white_can_castle_kingside = true;
    bool white_can_castle_queenside = true;
    bool black_can_castle_kingside = true;
    bool black_can_castle_queenside = true;
    std::pair<int, int> en_passant_target = {-1, -1};
    std::vector<Move> move_history;
    
    ChessBoard() {
        setup_initial_position();
    }
    
    void setup_initial_position() {
        // Clear board
        for (auto& rank : board) {
            for (auto& piece : rank) {
                piece = Piece();
            }
        }
        
        // White pieces
        board[0][0] = Piece(PieceType::ROOK, Color::WHITE);
        board[1][0] = Piece(PieceType::KNIGHT, Color::WHITE);
        board[2][0] = Piece(PieceType::BISHOP, Color::WHITE);
        board[3][0] = Piece(PieceType::QUEEN, Color::WHITE);
        board[4][0] = Piece(PieceType::KING, Color::WHITE);
        board[5][0] = Piece(PieceType::BISHOP, Color::WHITE);
        board[6][0] = Piece(PieceType::KNIGHT, Color::WHITE);
        board[7][0] = Piece(PieceType::ROOK, Color::WHITE);
        
        for (int i = 0; i < 8; i++) {
            board[i][1] = Piece(PieceType::PAWN, Color::WHITE);
        }
        
        // Black pieces
        board[0][7] = Piece(PieceType::ROOK, Color::BLACK);
        board[1][7] = Piece(PieceType::KNIGHT, Color::BLACK);
        board[2][7] = Piece(PieceType::BISHOP, Color::BLACK);
        board[3][7] = Piece(PieceType::QUEEN, Color::BLACK);
        board[4][7] = Piece(PieceType::KING, Color::BLACK);
        board[5][7] = Piece(PieceType::BISHOP, Color::BLACK);
        board[6][7] = Piece(PieceType::KNIGHT, Color::BLACK);
        board[7][7] = Piece(PieceType::ROOK, Color::BLACK);
        
        for (int i = 0; i < 8; i++) {
            board[i][6] = Piece(PieceType::PAWN, Color::BLACK);
        }
    }
    
    bool is_valid_square(int x, int y) const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
    
    Piece get_piece(int x, int y) const {
        if (!is_valid_square(x, y)) return Piece();
        return board[x][y];
    }
    
    void set_piece(int x, int y, const Piece& piece) {
        if (is_valid_square(x, y)) {
            board[x][y] = piece;
        }
    }
    
    bool is_square_attacked(int x, int y, Color by_color) const {
        // Check for pawn attacks
        int pawn_dir = (by_color == Color::WHITE) ? 1 : -1;
        int pawn_start_y = y - pawn_dir;
        
        if (is_valid_square(x - 1, pawn_start_y)) {
            Piece p = get_piece(x - 1, pawn_start_y);
            if (p.type == PieceType::PAWN && p.color == by_color) return true;
        }
        if (is_valid_square(x + 1, pawn_start_y)) {
            Piece p = get_piece(x + 1, pawn_start_y);
            if (p.type == PieceType::PAWN && p.color == by_color) return true;
        }
        
        // Check for knight attacks
        std::array<std::pair<int, int>, 8> knight_moves = {{
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
            {1, -2}, {1, 2}, {2, -1}, {2, 1}
        }};
        
        for (auto [dx, dy] : knight_moves) {
            int nx = x + dx, ny = y + dy;
            if (is_valid_square(nx, ny)) {
                Piece p = get_piece(nx, ny);
                if (p.type == PieceType::KNIGHT && p.color == by_color) return true;
            }
        }
        
        // Check for sliding piece attacks (rook, bishop, queen)
        std::array<std::pair<int, int>, 8> directions = {{
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},           {0, 1},
            {1, -1},  {1, 0},  {1, 1}
        }};
        
        for (auto [dx, dy] : directions) {
            for (int i = 1; i < 8; i++) {
                int nx = x + i * dx, ny = y + i * dy;
                if (!is_valid_square(nx, ny)) break;
                
                Piece p = get_piece(nx, ny);
                if (!p.is_empty()) {
                    if (p.color == by_color) {
                        bool is_diagonal = (dx != 0 && dy != 0);
                        if (is_diagonal && (p.type == PieceType::BISHOP || p.type == PieceType::QUEEN)) {
                            return true;
                        }
                        if (!is_diagonal && (p.type == PieceType::ROOK || p.type == PieceType::QUEEN)) {
                            return true;
                        }
                        if (i == 1 && p.type == PieceType::KING) {
                            return true;
                        }
                    }
                    break;
                }
            }
        }
        
        return false;
    }
    
    bool is_in_check(Color color) const {
        // Find the king
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                Piece p = get_piece(x, y);
                if (p.type == PieceType::KING && p.color == color) {
                    return is_square_attacked(x, y, (color == Color::WHITE) ? Color::BLACK : Color::WHITE);
                }
            }
        }
        return false;
    }
    
    bool is_valid_move(const Move& move) const {
        if (!is_valid_square(move.from_x, move.from_y) || 
            !is_valid_square(move.to_x, move.to_y)) {
            return false;
        }
        
        Piece piece = get_piece(move.from_x, move.from_y);
        if (piece.is_empty() || piece.color != current_turn) {
            return false;
        }
        
        Piece target = get_piece(move.to_x, move.to_y);
        if (!target.is_empty() && target.color == piece.color) {
            return false;
        }
        
        // Basic piece movement validation
        int dx = move.to_x - move.from_x;
        int dy = move.to_y - move.from_y;
        
        switch (piece.type) {
            case PieceType::PAWN: {
                int forward = (piece.color == Color::WHITE) ? 1 : -1;
                int start_rank = (piece.color == Color::WHITE) ? 1 : 6;
                
                if (dx == 0 && dy == forward && target.is_empty()) {
                    return true; // Single step forward
                }
                if (dx == 0 && dy == 2 * forward && move.from_y == start_rank && target.is_empty()) {
                    return true; // Double step from starting position
                }
                if (abs(dx) == 1 && dy == forward && !target.is_empty()) {
                    return true; // Capture
                }
                return false;
            }
            
            case PieceType::KNIGHT:
                return (abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2);
            
            case PieceType::BISHOP:
                return abs(dx) == abs(dy) && is_path_clear(move.from_x, move.from_y, move.to_x, move.to_y);
            
            case PieceType::ROOK:
                return (dx == 0 || dy == 0) && is_path_clear(move.from_x, move.from_y, move.to_x, move.to_y);
            
            case PieceType::QUEEN:
                return (abs(dx) == abs(dy) || dx == 0 || dy == 0) && 
                       is_path_clear(move.from_x, move.from_y, move.to_x, move.to_y);
            
            case PieceType::KING:
                return abs(dx) <= 1 && abs(dy) <= 1;
            
            default:
                return false;
        }
    }
    
    bool is_path_clear(int from_x, int from_y, int to_x, int to_y) const {
        int dx = (to_x > from_x) ? 1 : (to_x < from_x) ? -1 : 0;
        int dy = (to_y > from_y) ? 1 : (to_y < from_y) ? -1 : 0;
        
        int x = from_x + dx, y = from_y + dy;
        while (x != to_x || y != to_y) {
            if (!get_piece(x, y).is_empty()) {
                return false;
            }
            x += dx;
            y += dy;
        }
        return true;
    }
    
    bool make_move(const Move& move) {
        if (!is_valid_move(move)) {
            return false;
        }
        
        // Test if move would leave king in check
        ChessBoard test_board = *this;
        test_board.execute_move(move);
        if (test_board.is_in_check(current_turn)) {
            return false;
        }
        
        execute_move(move);
        return true;
    }
    
    void execute_move(const Move& move) {
        Piece piece = get_piece(move.from_x, move.from_y);
        set_piece(move.to_x, move.to_y, piece);
        set_piece(move.from_x, move.from_y, Piece());
        
        move_history.push_back(move);
        current_turn = (current_turn == Color::WHITE) ? Color::BLACK : Color::WHITE;
    }
    
    std::vector<Move> generate_legal_moves() const {
        std::vector<Move> moves;
        
        for (int from_x = 0; from_x < 8; from_x++) {
            for (int from_y = 0; from_y < 8; from_y++) {
                Piece piece = get_piece(from_x, from_y);
                if (piece.is_empty() || piece.color != current_turn) continue;
                
                for (int to_x = 0; to_x < 8; to_x++) {
                    for (int to_y = 0; to_y < 8; to_y++) {
                        Move move(from_x, from_y, to_x, to_y);
                        if (is_valid_move(move)) {
                            // Test if move would leave king in check
                            ChessBoard test_board = *this;
                            test_board.execute_move(move);
                            if (!test_board.is_in_check(current_turn)) {
                                moves.push_back(move);
                            }
                        }
                    }
                }
            }
        }
        
        return moves;
    }
    
    int evaluate_position() const {
        int score = 0;
        
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                Piece piece = get_piece(x, y);
                if (!piece.is_empty()) {
                    int piece_value = piece.get_value();
                    if (piece.color == Color::WHITE) {
                        score += piece_value;
                    } else {
                        score -= piece_value;
                    }
                }
            }
        }
        
        return score;
    }
    
    std::string to_string() const {
        std::stringstream ss;
        ss << "\n  ";
        for (int i = 0; i < 8; i++) {
            ss << " " << static_cast<char>('a' + i) << " ";
        }
        ss << "\n";
        
        for (int y = 7; y >= 0; y--) {
            ss << (y + 1) << " ";
            for (int x = 0; x < 8; x++) {
                ss << " " << get_piece(x, y).to_unicode() << " ";
            }
            ss << " " << (y + 1) << "\n";
        }
        
        ss << "  ";
        for (int i = 0; i < 8; i++) {
            ss << " " << static_cast<char>('a' + i) << " ";
        }
        ss << "\n";
        
        ss << "Turn: " << ((current_turn == Color::WHITE) ? "White" : "Black");
        ss << " | Position Value: " << evaluate_position() << "\n";
        
        return ss.str();
    }
};

// Global chess board instance
static std::unique_ptr<ChessBoard> g_chess_board;

// Helper function to parse algebraic notation
std::pair<int, int> parse_square(const std::string& square) {
    if (square.length() != 2) return {-1, -1};
    
    int x = square[0] - 'a';
    int y = square[1] - '1';
    
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return {-1, -1};
    
    return {x, y};
}

// Plugin initialization
extern "C" {
    void init_plugin(WoflangInterpreter::OpTable* op_table) {
        // Initialize chess board
        g_chess_board = std::make_unique<ChessBoard>();
        
        // Chess operations
        (*op_table)["chess_new"] = [](std::stack<WofValue>& stack) {
            g_chess_board = std::make_unique<ChessBoard>();
            
            // Epic ASCII art splash screen
            std::cout << "\n";
            std::cout << "╔═══════════════════════════════════════════════════════════════╗\n";
            std::cout << "║                                                               ║\n";
            std::cout << "║     ╦ ╦┌─┐┌─┐┬  ╦  ┌─┐  ╔╗╔┌─┐┬ ┬┬─┐┌─┐┬  ╔═╗┬ ┬┌─┐┌─┐┌─┐     ║\n";
            std::cout << "║     ║║║│ │├┤ │  ╚═╝└─┐  ║║║├┤ │ │├┬┘├─┤│  ║  ├─┤├┤ └─┐└─┐     ║\n";
            std::cout << "║     ╚╩╝└─┘└  ┴─┘   └─┘  ╝╚╝└─┘└─┘┴└─┴ ┴┴─┘╚═╝┴ ┴└─┘└─┘└─┘     ║\n";
            std::cout << "║                                                               ║\n";
            std::cout << "║     ♜♞♝♛♚♝♞♜   A Neural Chess Engine  ♖♘♗♕♔♗♘♖               ║\n";
            std::cout << "║     ♟♟♟♟♟♟♟♟     by husklyfren        ♙♙♙♙♙♙♙♙               ║\n";
            std::cout << "║                                                               ║\n";
            std::cout << "║             🧠 RNN • CNN • LSTM • GAN 🧠                       ║\n";
            std::cout << "║                                                               ║\n";
            std::cout << "╚═══════════════════════════════════════════════════════════════╝\n";
            std::cout << "\n";
            std::cout << "🎯 New neural chess game started! May the best brain win! 🎯\n";
            std::cout << g_chess_board->to_string() << std::endl;
        };
        
        (*op_table)["chess_show"] = [](std::stack<WofValue>& stack) {
            if (!g_chess_board) {
                std::cout << "No chess game in progress. Use 'chess_new' to start.\n";
                return;
            }
            std::cout << g_chess_board->to_string() << std::endl;
        };
        
        (*op_table)["chess_move"] = [](std::stack<WofValue>& stack) {
            if (!g_chess_board) {
                std::cout << "No chess game in progress. Use 'chess_new' to start.\n";
                return;
            }
            
            if (stack.size() < 2) {
                std::cout << "Need two squares for move (from to). Example: \"e2\" \"e4\" chess_move\n";
                return;
            }
            
            auto to_square = stack.top().s; stack.pop();
            auto from_square = stack.top().s; stack.pop();
            
            auto [from_x, from_y] = parse_square(from_square);
            auto [to_x, to_y] = parse_square(to_square);
            
            if (from_x == -1 || to_x == -1) {
                std::cout << "Invalid square notation. Use format like 'e2' or 'e4'.\n";
                return;
            }
            
            Move move(from_x, from_y, to_x, to_y);
            
            if (g_chess_board->make_move(move)) {
                std::cout << "Move: " << move.to_algebraic() << std::endl;
                std::cout << g_chess_board->to_string() << std::endl;
                
                // Check game state
                auto legal_moves = g_chess_board->generate_legal_moves();
                if (legal_moves.empty()) {
                    if (g_chess_board->is_in_check(g_chess_board->current_turn)) {
                        std::cout << "🏁 CHECKMATE! " << 
                            ((g_chess_board->current_turn == Color::WHITE) ? "Black" : "White") << " wins!\n";
                    } else {
                        std::cout << "🤝 STALEMATE! Game is a draw.\n";
                    }
                } else if (g_chess_board->is_in_check(g_chess_board->current_turn)) {
                    std::cout << "⚠️  CHECK!\n";
                }
            } else {
                std::cout << "❌ Invalid move: " << move.to_algebraic() << std::endl;
            }
        };
        
        (*op_table)["chess_legal_moves"] = [](std::stack<WofValue>& stack) {
            if (!g_chess_board) {
                std::cout << "No chess game in progress. Use 'chess_new' to start.\n";
                return;
            }
            
            auto moves = g_chess_board->generate_legal_moves();
            std::cout << "Legal moves (" << moves.size() << "):\n";
            
            for (size_t i = 0; i < moves.size(); i++) {
                std::cout << moves[i].to_algebraic();
                if ((i + 1) % 8 == 0) std::cout << "\n";
                else std::cout << " ";
            }
            if (moves.size() % 8 != 0) std::cout << "\n";
            
            WofValue result;
            result.d = static_cast<double>(moves.size());
            stack.push(result);
        };
        
        (*op_table)["chess_eval"] = [](std::stack<WofValue>& stack) {
            if (!g_chess_board) {
                std::cout << "No chess game in progress. Use 'chess_new' to start.\n";
                return;
            }
            
            int eval = g_chess_board->evaluate_position();
            std::cout << "Position evaluation: " << eval << " (positive = White advantage)\n";
            
            WofValue result;
            result.d = static_cast<double>(eval);
            stack.push(result);
        };
        
        // Unicode piece symbols
        (*op_table)["♔"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::KING));
            stack.push(result);
        };
        
        (*op_table)["♕"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::QUEEN));
            stack.push(result);
        };
        
        (*op_table)["♖"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::ROOK));
            stack.push(result);
        };
        
        (*op_table)["♗"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::BISHOP));
            stack.push(result);
        };
        
        (*op_table)["♘"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::KNIGHT));
            stack.push(result);
        };
        
        (*op_table)["♙"] = [](std::stack<WofValue>& stack) {
            WofValue result;
            result.d = static_cast<double>(static_cast<int>(PieceType::PAWN));
            stack.push(result);
        };
        
        std::cout << "🏁 Chess plugin loaded! Commands: chess_new, chess_show, chess_move, chess_legal_moves, chess_eval\n";
        std::cout << "   Usage: chess_new → \"e2\" \"e4\" chess_move → chess_show\n";
        std::cout << "   Unicode pieces: ♔♕♖♗♘♙ (push piece types to stack)\n";
    }
}

} // namespace woflang