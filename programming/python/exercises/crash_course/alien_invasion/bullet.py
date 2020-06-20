#!/usr/bin/python3
# bullet.py
# Class to represent a bullet in the alien invasion game.

import pygame


class Bullet(pygame.sprite.Sprite):
    """Class to represent a bullet in the alien invasion game."""
    def __init__(self, game):
        """Initialize a bullet."""
        super().__init__()
        self.game = game

        # Create a bullet at the ship's location.
        self.rect = pygame.Rect(
            0,
            0,
            self.game.settings.bullet_width,
            self.game.settings.bullet_height,
        )
        self.rect.midbottom = game.ship.rect.midtop

        self.y = float(self.rect.y)

    def update(self):
        """Move the bullet."""
        self.y -= self.game.settings.bullet_speed
        self.rect.y = int(self.y)

    def draw(self):
        """Draw the bullet on the display."""
        pygame.draw.rect(
            self.game.display,
            self.game.settings.bullet_color,
            self.rect,
        )
