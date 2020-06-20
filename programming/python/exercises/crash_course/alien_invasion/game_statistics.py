#!/usr/bin/python3
# game_statistics.py
# Class to keep track of statistics for the alien invasion game.


class GameStatistics:
    def __init__(self, game):
        """Initialize the game statistics."""
        self.game = game
        self.reset()

    def reset(self):
        """Reset the game statistics."""
        self.num_lives_left = self.game.settings.num_lives_start
