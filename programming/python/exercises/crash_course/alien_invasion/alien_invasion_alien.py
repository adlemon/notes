#!/usr/bin/python3
# alien_invasion_alien.py
# Class to represent an alien in the alien invasion game.

import pygame


class AlienInvasionAlien(pygame.sprite.Sprite):
    """Class to represent an alien in the alien invasion game."""
    def __init__(self, game):
        """Initialize an alien."""
        super().__init__()
        self.game = game

        self.image = pygame.image.load('images/alien.bmp')
        self.rect = self.image.get_rect()
        self.rect.x = self.rect.width
        self.rect.y = self.rect.height

        self.x = float(self.rect.x)

    def is_on_screen(self):
        return (self.rect.left >= 0
                and self.rect.right <= self.game.display.get_rect().right)

    def update(self):
        """Update the alien's position."""
        self.x += (self.game.settings.alien_direction *
                   self.game.settings.alien_speed)
        self.rect.x = int(self.x)
