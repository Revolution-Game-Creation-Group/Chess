// Bryan Liu (chl312), Dept. of Computing, Imperial College London
// Rook.cpp - implementation of Rook extending Piece (info in Rook.hpp)

#include "Rook.hpp"

Rook::Rook (string fileRank, bool isWhitePlayer)
  : Piece (fileRank, isWhitePlayer) {

}

Rook* Rook::clone () {
  return new Rook (this -> getFileRank(), this -> isWhitePlayer());
}

/* A Rook's move is valid iff:
   - Destination is on the same file/rank (note: mutually exclusive)
   - There are no other pieces in intermediate spaces
   - Piece at destination, if exist, is not a friendly
     (or there are no piece at destination)

   Rook.isValidMove() post-cond: return 0 iff move is valid
                                 respective error code otherwise
*/
int Rook::isValidMove (string destFileRank, map<string, Piece*>* board) {

  if (isSameFile(destFileRank) && isSameRank(destFileRank)) {
    return ChessErrHandler::DEST_EQ_SOURCE;
  }

  if (!(isSameFile (destFileRank) || isSameRank (destFileRank))) {
    return ChessErrHandler::ILLEGAL_MOVE_PATTERN;
  }

  /* Obstruction for a Rook only occurs if it is on its intended way
     Lazy boolean evalution of C++ ensure !no_Obstruction is evaluated only
      after satisfying isSame_, prevents breaking pre-cond of no_Obstruction
  */
  if ((isSameFile (destFileRank) && 
       !noVerticalObstruction (destFileRank, board)) ||
      (isSameRank (destFileRank) &&
       !noHorizontalObstruction (destFileRank, board))) {
    return ChessErrHandler::OBSTRUCTION_EN_ROUTE;
  }
  
  if (destExistFriendlyPiece (destFileRank, board)) {
    return ChessErrHandler::FRIENDLY_AT_DEST;
  }
  
  return ChessErrHandler::NO_ERROR;
}

string Rook::toString () {
  
  string name (playerToString());
  name.append(" Rook");
  return name;  
}
