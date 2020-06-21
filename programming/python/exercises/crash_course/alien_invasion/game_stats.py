#!/usr/bin/python3
# game_stats.py
# Class to keep track of statistics for the alien invasion game.


class GameStats:
    def __init__(self, game):
        """Initialize the game statistics."""
        self.game = game
        self.reset()
        self.high_score = None

    def reset(self):
        """Reset the game statistics."""
        self.game_active = False
        self.num_lives_left = self.game.settings.num_lives_start
        self.level = 1
        self.score = 0

    def lose_turn(self):
        """Update the game statistics after a lost turn."""
        self.num_lives_left -= 1
        if self.num_lives_left <= 0:
            self.game_active = False
