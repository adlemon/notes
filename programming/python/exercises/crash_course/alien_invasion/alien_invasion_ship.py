#!/usr/bin/python3
# alien_invasion_ship.py
# Class to represent the player's ship in the Alien Invasion game.

import pygame


class AlienInvasionShip:
    """Class to represent the player's ship in the Alien Invasion game."""
    def __init__(self, alien_invasion_game):
        """Initialize the player's ship."""
        self.alien_invasion_game = alien_invasion_game

        self.image = pygame.image.load('images/ship.bmp')
        self.rect = self.image.get_rect()
        self.width = self.rect.width
        self.height = self.rect.height

        self.reset()

    def reset(self):
        """Reset the ship."""
        self.rect.midbottom = self.alien_invasion_game.display.get_rect(
        ).midbottom
        self.x = float(self.rect.x)

        self.left_thruster_on = self.right_thruster_on = False
        self.velocity = 0

    def _bound_to_range(self, val, min_val, max_val):
        if val < min_val:
            return min_val
        if val > max_val:
            return max_val
        return val

    def _update_velocity(self):
        self.velocity = ((self.right_thruster_on - self.left_thruster_on) *
                         self.alien_invasion_game.settings.ship_speed)

    def update(self):
        """Update the position of the ship."""
        self._update_velocity()
        self.x = self._bound_to_range(
            self.x + self.velocity,
            0,
            self.alien_invasion_game.display.get_rect().right - self.width,
        )
        self.rect.x = int(self.x)

    def draw(self):
        """Draw the player's ship."""
        self.alien_invasion_game.display.blit(self.image, self.rect)
