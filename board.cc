#include <iostream>
#include <vector>
#include <string>

class Board;

class Position {
    const std::vector<char> repr_x = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    const std::vector<char> repr_y = {'1', '2', '3', '4', '5', '6', '7', '8'};
    int x, y;
public:
    Position(int x_arg, int y_arg): x(x_arg), y(y_arg) {}
    std::string to_string() {
        return std::string(1, repr_x[x]) + std::string(1, repr_y[y]);
    }
    void reflect() {
        y = 7-y;
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
};

class Piece {
public:
    bool is_white;
    Position position;
    const int value = 0;
    Piece(bool is_white_arg, Position position_arg): is_white(is_white_arg), position(position_arg) {}
    virtual std::vector<Position> get_moves(Board board);
    virtual std::string to_string() {
        return "Y";
    }
};

class Pawn : public Piece {
public:
    const int value = 1;
    Pawn(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♙" : "♟";
    }
};

class Rook : public Piece {
public:
    const int value = 5;
    Rook(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♖" : "♜";
    }
};

class Knight : public Piece {
public:
    const int value = 3;
    Knight(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♘" : "♞";
    }
};

class Bishop : public Piece {
public:
    const int value = 3;
    Bishop(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♗" : "♝";
    }
};

class King : public Piece {
public:
    const int value = 4;
    King(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♔" : "♚";
    }
};

class Queen : public Piece {
public:
    const int value = 9;
    Queen(bool is_white_arg, Position position_arg): Piece(is_white_arg, position_arg) {}
    virtual std::vector<Position> get_moves(Board board) override;
    std::string to_string() override {
        return is_white ? "♕" : "♛";
    }
};

class Board {
public:
    std::vector<Pawn> pawn_list;
    std::vector<Rook> rook_list;
    std::vector<Knight> knight_list;
    std::vector<Bishop> bishop_list;
    std::vector<King> king_list;
    std::vector<Queen> queen_list;
    std::vector<Piece*> piece_list;
    std::vector<std::vector<Piece*>> board_matrix;
    enum PIECE_COUNT {
        NUM_PAWNS = 8,
        NUM_ROOKS = 2,
        NUM_KNIGHTS = 2,
        NUM_BISHOPS = 2,
        NUM_KINGS = 1,
        NUM_QUEENS = 1
    };  
    Board() {
        std::vector<Piece*> null_row(8, nullptr);
        for(int i = 0; i < 8; i++){
            board_matrix.push_back(null_row);
        }
        std::vector<Position> white_pawn_positions = {};
        for(int i=0; i < 8; i++){
            white_pawn_positions.push_back(Position(i,1));
        }
        for(Position p: white_pawn_positions){
            pawn_list.push_back(Pawn(true, p));
            p.reflect();
            pawn_list.push_back(Pawn(false, p));
        }
        std::vector<Position> white_rook_positions = {Position(0,0),Position(7,0)};
        for(Position p: white_rook_positions){
            rook_list.push_back(Rook(true, p));
            p.reflect();
            rook_list.push_back(Rook(false, p));
        }
        std::vector<Position> white_knight_positions = {Position(1,0),Position(6,0)};
        for(Position p: white_knight_positions){
            knight_list.push_back(Knight(true, p));
            p.reflect();
            knight_list.push_back(Knight(false, p));
        }
        std::vector<Position> white_bishop_positions = {Position(2,0),Position(5,0)};
        for(Position p: white_bishop_positions){
            bishop_list.push_back(Bishop(true, p));
            p.reflect();
            bishop_list.push_back(Bishop(false, p));
        }
        std::vector<Position> white_king_positions = {Position(3,0)};
        for(Position p: white_king_positions){
            king_list.push_back(King(true, p));
            p.reflect();
            king_list.push_back(King(false, p));
        }
        std::vector<Position> white_queen_positions = {Position(4,0)};
        for(Position p: white_queen_positions){
            queen_list.push_back(Queen(true, p));
            p.reflect();
            queen_list.push_back(Queen(false, p));
        }
        for(int i = 0; i < NUM_PAWNS; i++){
            Position p = white_pawn_positions[i];
            piece_list.push_back(&pawn_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&pawn_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
        for(int i = 0; i < NUM_ROOKS; i++){
            Position p = white_rook_positions[i];
            piece_list.push_back(&rook_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&rook_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
        for(int i = 0; i < NUM_KNIGHTS; i++){
            Position p = white_knight_positions[i];
            piece_list.push_back(&knight_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&knight_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
        for(int i = 0; i < NUM_BISHOPS; i++){
            Position p = white_bishop_positions[i];
            piece_list.push_back(&bishop_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&bishop_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
        for(int i = 0; i < NUM_QUEENS; i++){
            Position p = white_queen_positions[i];
            piece_list.push_back(&queen_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&queen_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
        for(int i = 0; i < NUM_KINGS; i++){
            Position p = white_king_positions[i];
            piece_list.push_back(&king_list[2*i]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
            p.reflect();
            piece_list.push_back(&king_list[2*i+1]);
            board_matrix[p.get_x()][p.get_y()] = piece_list.back();
        }
    }
    std::string to_string() {
        std::string s;
        for(int j = 7; j >= 0; j--){
            for(int i = 0; i < 8; i++){
                Piece* ptr = board_matrix[i][j];
                if(ptr){
                    s += ptr -> to_string();
                }
                else{
                    s += " ";
                }
            }
            s += '\n';
        }
        return s;
    }
};

std::vector<Position> Piece::get_moves(Board board) {
    return {};
}
std::vector<Position> Pawn::get_moves(Board board) {
    return {};
}
std::vector<Position> Rook::get_moves(Board board) {
    return {};
}
std::vector<Position> Knight::get_moves(Board board) {
    return {};
}
std::vector<Position> Bishop::get_moves(Board board) {
    return {};
}
std::vector<Position> King::get_moves(Board board) {
    return {};
}
std::vector<Position> Queen::get_moves(Board board) {
    return {};
}

int main() {
    Board board = Board();
    std::cout<< board.to_string() <<'\n';
}