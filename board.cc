#include <iostream>
#include <vector>
#include <string>

class Board;

class Position {
    std::vector<char> repr_x = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    std::vector<char> repr_y = {'1', '2', '3', '4', '5', '6', '7', '8'};
    int x, y;
public:
    Position(int x_arg, int y_arg): x(x_arg), y(y_arg) {}
    bool operator == (const Position &p) {
        if(x == p.x && y == p.y){
            return true;
        }
        return false;
    }
    std::string to_string() {
        return std::string(1, repr_x[x]) + std::string(1, repr_y[y]);
    }
    bool in_board(){
        return (x>=0 && x<8) && (y>=0 && y<8);
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
    void move(Position p1){
        if(!p1.in_board()){
            std::cout<<"Invalid move: out of board bounds";
            return;
        }
        position = p1;
    }
    std::vector<Position> get_valid_moves(Board board){
        std::vector<Position> valid_moves;
        std::vector<Position> moves = get_moves(board);
        for(Position move: moves){
            Board board_copy = board;
            if(!board_copy.is_check(is_white)){
                valid_moves.push_back(move);
            }
        }
        return valid_moves;
    }
    void kill(){
        position = Position(-1, -1);
    }
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
    bool white_to_play;
    enum PIECE_COUNT {
        NUM_PIECES = 32,
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
        white_to_play = true;
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
    void move(Position p1, Position p2) {
        Piece* ptr1 = board_matrix[p1.get_x()][p1.get_y()];
        Piece* ptr2 = board_matrix[p2.get_x()][p2.get_y()];
        if(!ptr1){
            std::cout<<"Invalid move: inital position is empty";
            return;
        }
        else if(ptr1->is_white ^ white_to_play){
            std::cout<<"Invalid move: Opponent's piece is being moved";
            return;
        }
        else{
            if(!ptr2){
                ptr1->move(p2);
            }
            else if(ptr2 && !(ptr2->is_white ^ white_to_play)){
                std::cout<<"Invalid move: Self piece being captured";
                return;
            }
            else{
                for(int i = 0; i < NUM_PIECES; i++){
                    Piece* ptr = piece_list[i];
                    if(ptr && (ptr->position == p2)){
                        ptr->kill();
                        piece_list[i] = nullptr;
                        break;
                    }
                }
                board_matrix[p2.get_x()][p2.get_y()] = nullptr;
                ptr1->move(p2);
            }
        }
        white_to_play ^= 1;
    }
    std::vector<std::pair<Position, Position>> get_all_moves(bool is_white){
        std::vector<std::pair<Position, Position>> all_moves;
        for(Piece* ptr: piece_list){
            if(ptr->position.in_board() && ptr->is_white == is_white){
                Position current_position = ptr->position;
                std::vector<Position> moves = ptr->get_moves(*this);
                for(Position move: moves){
                    all_moves.push_back(std::make_pair(current_position, move));
                }
            }
        }
        return all_moves;
    }
    std::vector<std::pair<Position, Position>> get_all_valid_moves(bool is_white){
        std::vector<std::pair<Position, Position>> all_valid_moves;
        for(Piece* ptr: piece_list){
            if(ptr->position.in_board() && ptr->is_white == is_white){
                Position current_position = ptr->position;
                std::vector<Position> moves = ptr->get_valid_moves(*this);
                for(Position move: moves){
                    all_valid_moves.push_back(std::make_pair(current_position, move));
                }
            }
        }
        return all_valid_moves;
    }
    std::vector<std::pair<Position, Position>> get_all_valid_moves(){
        get_all_valid_moves(white_to_play);
    }
    bool is_check(bool is_white) {
        // Check if white player is under check if is_white == true else vice-versa
        std::vector<std::pair<Position, Position>> all_moves = get_all_moves(!is_white);
        Position king_position(-1,-1);
        for(King king: king_list){
            if(king.is_white == is_white){
                king_position = king.position;
                break;
            }
        }
        for(std::pair<Position,Position> move: all_moves){
            if(king_position == move.second){
                return true;
            }
        }
        return false;
    }
    bool is_check(){
        is_check(white_to_play);
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