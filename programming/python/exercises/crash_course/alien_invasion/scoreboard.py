#!/usr/bin/python3
# scoreboard.py
# Class to manage the scoreboard for the alien invasion game.

import pygame
from ship import Ship


class Scoreboard:
    """Class to manage the scoreboard for the alien invasion game."""
    def __init__(self, game):
        self.game = game

        self.text_color = (30, 30, 30)
        self.font = pygame.font.SysFont(
            None,  # name
            48,  # size
        )

        self.render_score()
        self.render_level()
        self.render_ships()
        if self.game.stats.high_score is not None:
            self.render_high_score()

    def render_score(self):
        """Render an image to the display the (current) score."""
        self.score_image = self.font.render(
            f'{round(self.game.stats.score, -1):,}',  # text
            True,  # antialias
            self.text_color,  # color
            self.game.settings.bg_color,  # background
        )

        self.score_rect = self.score_image.get_rect()
        self.score_rect.right = self.game.display.get_rect().right - 20
        self.score_rect.top = 20

    def render_level(self):
        """Render an image to display the level."""
        self.level_image = self.font.render(
            str(self.game.stats.level),  # text
            True,  # antialias
            self.text_color,  # color
            self.game.settings.bg_color,  # background
        )

        self.level_rect = self.level_image.get_rect()
        self.level_rect.right = self.score_rect.right
        self.level_rect.top = self.score_rect.bottom + 10

    def render_ships(self):
        """Render images to show the number of remaining ships."""
        self.ships = pygame.sprite.Group()
        for i in range(self.game.stats.num_lives_left):
            ship = Ship(self.game)
            ship.rect.x = 10 + i * ship.rect.width
            ship.rect.y = 10
            self.ships.add(ship)

    def render_high_score(self):
        """Render an image to display the high score."""
        self.high_score_image = self.font.render(
            f'{round(self.game.stats.score, -1):,}',  # text
            True,  # antialias
            self.text_color,  # color
            self.game.settings.bg_color,  # background
        )

        self.high_score_rect = self.high_score_image.get_rect()
        self.high_score_rect.centerx = self.game.display.get_rect().centerx
        self.high_score_rect.top = self.score_rect.top

    def draw(self):
        """Draw the scoreboard on the display."""
        self.game.display.blit(self.score_image, self.score_rect)
        self.game.display.blit(self.level_image, self.level_rect)
        self.ships.draw(self.game.display)
        if self.game.stats.high_score:
            self.game.display.blit(self.high_score_image, self.high_score_rect)
