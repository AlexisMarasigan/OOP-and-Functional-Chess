import unittest
from chess import Color, Game

class TestGame(unittest.TestCase):
    def test_play_move(self):
        game = Game()
        self.assertTrue(game.play_move("e2", "e4"))
        self.assertFalse(game.play_move("e2", "e5"))

    def test_turn_switching(self):
        game = Game()
        game.play_move("e2", "e4")
        self.assertEqual(game.current_turn, Color.BLACK)
        game.play_move("e7", "e5")
        self.assertEqual(game.current_turn, Color.WHITE)

class TestFamousGames(unittest.TestCase):
    def test_scholars_mate(self):
        game = Game()
        game.play_move("e2", "e4")
        game.play_move("e7", "e5")
        game.play_move("d1", "h5")
        game.play_move("b8", "c6")
        game.play_move("f1", "c4")
        game.play_move("g8", "f6")
        game.play_move("h5", "f7")
        self.assertTrue(game.board.is_checkmate(Color.BLACK))

    def test_fools_mate(self):
        game = Game()
        game.play_move("f2", "f3")
        game.play_move("e7", "e5")
        game.play_move("g2", "g4")
        game.play_move("d8", "h4")
        self.assertTrue(game.board.is_checkmate(Color.WHITE))

if __name__ == "__main__":
    unittest.main()
