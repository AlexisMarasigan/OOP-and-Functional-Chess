class Color:
    WHITE = 'white'
    BLACK = 'black'

class Square:
    columns = 'abcdefgh'

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.piece = None

    def __repr__(self):
        return f"{Square.columns[self.x]}{self.y + 1}"

class Piece:
    def __init__(self, color):
        self.color = color

    def is_valid_move(self, start_square, end_square):
        raise NotImplementedError("Must be implemented by subclass")

class Pawn(Piece):
    def __str__(self):
        return '♙' if self.color == Color.WHITE else '♟'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for Pawn
        return True

class Rook(Piece):
    def __str__(self):
        return '♖' if self.color == Color.WHITE else '♜'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for Rook
        return True

class Knight(Piece):
    def __str__(self):
        return '♘' if self.color == Color.WHITE else '♞'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for Knight
        return True

class Bishop(Piece):
    def __str__(self):
        return '♗' if self.color == Color.WHITE else '♝'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for Bishop
        return True

class Queen(Piece):
    def __str__(self):
        return '♕' if self.color == Color.WHITE else '♛'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for Queen
        return True

class King(Piece):
    def __str__(self):
        return '♔' if self.color == Color.WHITE else '♚'

    def is_valid_move(self, start_square, end_square):
        # Simplified move logic for King
        return True

class Board:
    def __init__(self):
        self.board = {Square.columns[x] + str(y + 1): Square(x, y) for x in range(8) for y in range(8)}
        self.setup_board()

    def setup_board(self):
        for i in range(8):
            self.board[f"{Square.columns[i]}2"].piece = Pawn(Color.WHITE)
            self.board[f"{Square.columns[i]}7"].piece = Pawn(Color.BLACK)

        self.board["a1"].piece = Rook(Color.WHITE)
        self.board["h1"].piece = Rook(Color.WHITE)
        self.board["a8"].piece = Rook(Color.BLACK)
        self.board["h8"].piece = Rook(Color.BLACK)

        self.board["b1"].piece = Knight(Color.WHITE)
        self.board["g1"].piece = Knight(Color.WHITE)
        self.board["b8"].piece = Knight(Color.BLACK)
        self.board["g8"].piece = Knight(Color.BLACK)

        self.board["c1"].piece = Bishop(Color.WHITE)
        self.board["f1"].piece = Bishop(Color.WHITE)
        self.board["c8"].piece = Bishop(Color.BLACK)
        self.board["f8"].piece = Bishop(Color.BLACK)

        self.board["d1"].piece = Queen(Color.WHITE)
        self.board["d8"].piece = Queen(Color.BLACK)

        self.board["e1"].piece = King(Color.WHITE)
        self.board["e8"].piece = King(Color.BLACK)

    def get_square(self, name):
        return self.board[name]

    def is_valid_move(self, start_pos, end_pos):
        start_square = self.board[start_pos]
        end_square = self.board[end_pos]
        piece = start_square.piece
        if piece is None:
            return False
        return piece.is_valid_move(start_square, end_square)

    def move_piece(self, start_pos, end_pos):
        start_square = self.board[start_pos]
        end_square = self.board[end_pos]
        piece = start_square.piece
        if piece and self.is_valid_move(start_pos, end_pos):
            end_square.piece = piece
            start_square.piece = None

    def print_board(self, current_turn):
        if current_turn == Color.WHITE:
            rows = range(7, -1, -1)
            cols = range(8)
        else:
            rows = range(8)
            cols = range(7, -1, -1)

        print("  a b c d e f g h")
        for y in rows:
            print(f"{y + 1} ", end='')
            for x in cols:
                square = self.board[Square.columns[x] + str(y + 1)]
                piece = square.piece
                if piece:
                    print(piece, end=' ')
                else:
                    print('.', end=' ')
            print(f" {y + 1}")
        print("  a b c d e f g h")

class Move:
    def __init__(self, start_pos, end_pos, piece, captured_piece=None):
        self.start_pos = start_pos
        self.end_pos = end_pos
        self.piece = piece
        self.captured_piece = captured_piece

    def __repr__(self):
        return f"{self.piece}{self.start_pos}->{self.end_pos}"

class Game:
    def __init__(self):
        self.board = Board()
        self.current_turn = Color.WHITE
        self.moves = []

    def setup_board(self):
        self.board.setup_board()

    def make_move(self, start_pos, end_pos):
        if self.board.is_valid_move(start_pos, end_pos):
            start_square = self.board.board[start_pos]
            end_square = self.board.board[end_pos]
            move = Move(start_pos, end_pos, start_square.piece, end_square.piece)
            self.board.move_piece(start_pos, end_pos)
            self.moves.append(move)
            self.current_turn = Color.BLACK if self.current_turn == Color.WHITE else Color.WHITE
            return True
        return False

    def undo_move(self):
        if not self.moves:
            return False
        last_move = self.moves.pop()
        start_square = self.board.board[last_move.start_pos]
        end_square = self.board.board[last_move.end_pos]
        start_square.piece = last_move.piece
        end_square.piece = last_move.captured_piece
        self.current_turn = Color.BLACK if self.current_turn == Color.WHITE else Color.WHITE
        return True

    def print_board(self):
        self.board.print_board(self.current_turn)

    def play(self):
        print("Welcome to Chess!")
        self.print_board()
        while True:
            command = input(f"{self.current_turn}'s turn. Enter your move (e.g., e2 e4) or 'undo': ").strip()
            if command.lower() == 'undo':
                if self.undo_move():
                    print("Move undone.")
                else:
                    print("No moves to undo.")
            elif len(command.split()) == 2:
                start_pos, end_pos = command.split()
                if self.make_move(start_pos, end_pos):
                    print(f"Moved from {start_pos} to {end_pos}.")
                else:
                    print("Invalid move. Try again.")
            else:
                print("Invalid command. Try again.")
            self.print_board()

if __name__ == "__main__":
    game = Game()
    game.play()

