#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include "board.h"

std::pair<Position,Position> minimax(Board board);

int main() {
    Board board;
    std::cout<< board.to_string() <<'\n';
    srand(time(0));
    for(int i = 0; i<=1000; i++){
        std::vector<std::pair<Position, Position>> moves = board.get_all_valid_moves();
        if(moves.size() == 0 && board.is_check()){
            std::cout<<"CHECKMATE!!!"<<'\n';
            break;
        }
        else if(moves.size() == 0 && !board.is_check()){
            std::cout<<"STALEMATE!!!"<<'\n';
            break;
        }
        else{
            std::pair<Position, Position> move = minimax(board);
            std::string player = board.white_to_play ? "WHITE PLAY:" : "BLACK PLAY:";
            std::cout<<player<<move.first.to_string()<<"->"<<move.second.to_string()<<'\n';
            board.move(move.first, move.second);
        }
        std::cout<< board.to_string() <<'\n';
    }
}