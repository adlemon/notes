#!/usr/bin/python3
# bullet.py
# Class to represent a bullet in the Alien Invasion game.

import pygame


class AlienInvasionBullet(pygame.sprite.Sprite):
    """Class to represent a bullet in the Alien Invasion game."""
    def __init__(self, alien_invasion_game):
        """Initialize a bullet."""
        super().__init__()
        self.alien_invasion_game = alien_invasion_game

        # Create a bullet the ship's location.
        self.rect = pygame.Rect(
            0,
            0,
            self.alien_invasion_game.settings.bullet_width,
            self.alien_invasion_game.settings.bullet_height,
        )
        self.rect.midbottom = alien_invasion_game.ship.rect.midtop

        self.y = float(self.rect.y)

    def update(self):
        """Move the bullet."""
        self.y -= self.alien_invasion_game.settings.bullet_speed
        self.rect.y = int(self.y)

    def draw(self):
        """Draw the bullet on the display."""
        pygame.draw.rect(
            self.alien_invasion_game.display,
            self.alien_invasion_game.settings.bullet_color,
            self.rect,
        )
