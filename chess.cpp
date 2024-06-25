#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// Define the board size
const int BOARD_SIZE = 8;

// Enum for piece types
enum PieceType
{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Enum for piece colors
enum PieceColor
{
    NONE,
    WHITE,
    BLACK
};

// Class representing a chess piece
class Piece
{
public:
    PieceType type;
    PieceColor color;

    Piece(PieceType type = EMPTY, PieceColor color = NONE)
        : type(type), color(color) {}
};

// Class representing the chess board
class Board
{
public:
    std::vector<std::vector<Piece>> squares;

    Board() : squares(BOARD_SIZE, std::vector<Piece>(BOARD_SIZE)) {}

    void initialize()
    {
        // Initialize pieces for a standard chess game
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            squares[1][i] = Piece(PAWN, WHITE);
            squares[6][i] = Piece(PAWN, BLACK);
        }
        // Add other pieces...
        squares[0][0] = squares[0][7] = Piece(ROOK, WHITE);
        squares[7][0] = squares[7][7] = Piece(ROOK, BLACK);
        squares[0][1] = squares[0][6] = Piece(KNIGHT, WHITE);
        squares[7][1] = squares[7][6] = Piece(KNIGHT, BLACK);
        squares[0][2] = squares[0][5] = Piece(BISHOP, WHITE);
        squares[7][2] = squares[7][5] = Piece(BISHOP, BLACK);
        squares[0][3] = Piece(QUEEN, WHITE);
        squares[7][3] = Piece(QUEEN, BLACK);
        squares[0][4] = Piece(KING, WHITE);
        squares[7][4] = Piece(KING, BLACK);
    }

    void display()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                char pieceChar = '.';
                switch (squares[i][j].type)
                {
                case PAWN:
                    pieceChar = 'P';
                    break;
                case KNIGHT:
                    pieceChar = 'N';
                    break;
                case BISHOP:
                    pieceChar = 'B';
                    break;
                case ROOK:
                    pieceChar = 'R';
                    break;
                case QUEEN:
                    pieceChar = 'Q';
                    break;
                case KING:
                    pieceChar = 'K';
                    break;
                default:
                    break;
                }
                if (squares[i][j].color == BLACK)
                {
                    pieceChar = tolower(pieceChar);
                }
                std::cout << pieceChar << ' ';
            }
            std::cout << std::endl;
        }
    }

    bool isValidMove(Piece piece, int fromX, int fromY, int toX, int toY)
    {
        if (fromX == toX && fromY == toY)
            return false; // Can't move to the same square
        if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE)
            return false; // Move is outside the board
        if (squares[toX][toY].color == piece.color)
            return false; // Can't capture own piece

        switch (piece.type)
        {
        case PAWN:
            return isValidPawnMove(piece, fromX, fromY, toX, toY);
        case KNIGHT:
            return isValidKnightMove(fromX, fromY, toX, toY);
        case BISHOP:
            return isValidBishopMove(fromX, fromY, toX, toY);
        case ROOK:
            return isValidRookMove(fromX, fromY, toX, toY);
        case QUEEN:
            return isValidQueenMove(fromX, fromY, toX, toY);
        case KING:
            return isValidKingMove(fromX, fromY, toX, toY);
        default:
            return false;
        }
    }

private:
    bool isValidPawnMove(Piece piece, int fromX, int fromY, int toX, int toY)
    {
        int direction = (piece.color == WHITE) ? 1 : -1;
        int startRow = (piece.color == WHITE) ? 1 : 6;

        // Move forward
        if (fromY == toY)
        {
            if (toX == fromX + direction && squares[toX][toY].type == EMPTY)
            {
                return true;
            }
            // Double move from start position
            if (fromX == startRow && toX == fromX + 2 * direction && squares[toX][toY].type == EMPTY && squares[fromX + direction][toY].type == EMPTY)
            {
                return true;
            }
        }

        // Capture
        if (toX == fromX + direction && (toY == fromY + 1 || toY == fromY - 1) && squares[toX][toY].type != EMPTY && squares[toX][toY].color != piece.color)
        {
            return true;
        }

        return false;
    }

    bool isValidKnightMove(int fromX, int fromY, int toX, int toY)
    {
        int dx = std::abs(fromX - toX);
        int dy = std::abs(fromY - toY);
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }

    bool isValidBishopMove(int fromX, int fromY, int toX, int toY)
    {
        if (std::abs(fromX - toX) != std::abs(fromY - toY))
            return false;
        int dx = (toX > fromX) ? 1 : -1;
        int dy = (toY > fromY) ? 1 : -1;
        for (int x = fromX + dx, y = fromY + dy; x != toX; x += dx, y += dy)
        {
            if (squares[x][y].type != EMPTY)
                return false;
        }
        return true;
    }

    bool isValidRookMove(int fromX, int fromY, int toX, int toY)
    {
        if (fromX != toX && fromY != toY)
            return false;
        if (fromX == toX)
        {
            int dy = (toY > fromY) ? 1 : -1;
            for (int y = fromY + dy; y != toY; y += dy)
            {
                if (squares[fromX][y].type != EMPTY)
                    return false;
            }
        }
        else
        {
            int dx = (toX > fromX) ? 1 : -1;
            for (int x = fromX + dx; x != toX; x += dx)
            {
                if (squares[x][fromY].type != EMPTY)
                    return false;
            }
        }
        return true;
    }

    bool isValidQueenMove(int fromX, int fromY, int toX, int toY)
    {
        return isValidBishopMove(fromX, fromY, toX, toY) || isValidRookMove(fromX, fromY, toX, toY);
    }

    bool isValidKingMove(int fromX, int fromY, int toX, int toY)
    {
        int dx = std::abs(fromX - toX);
        int dy = std::abs(fromY - toY);
        return dx <= 1 && dy <= 1;
    }
};

// Function to get input move from the player
std::pair<std::pair<int, int>, std::pair<int, int>> getMove()
{
    int fromX, fromY, toX, toY;
    std::cout << "Enter move (fromX fromY toX toY): ";
    std::cin >> fromX >> fromY >> toX >> toY;
    return {{fromX, fromY}, {toX, toY}};
}

// Function to move a piece
void movePiece(Board &board, std::pair<int, int> from, std::pair<int, int> to)
{
    board.squares[to.first][to.second] = board.squares[from.first][from.second];
    board.squares[from.first][from.second] = Piece();
}

// Main game loop
int main()
{
    Board board;
    board.initialize();

    PieceColor currentPlayer = WHITE;
    while (true)
    {
        board.display();
        auto move = getMove();
        std::pair<int, int> from = move.first;
        std::pair<int, int> to = move.second;

        Piece piece = board.squares[from.first][from.second];
        if (piece.color != currentPlayer)
        {
            std::cout << "Invalid move: not your piece" << std::endl;
            continue;
        }

        if (!board.isValidMove(piece, from.first, from.second, to.first, to.second))
        {
            std::cout << "Invalid move" << std::endl;
            continue;
        }

        movePiece(board, from, to);

        // Switch player
        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
    }

    return 0;
}
