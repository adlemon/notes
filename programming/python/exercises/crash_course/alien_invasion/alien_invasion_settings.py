#!/usr/bin/python3
# alien_invasion_settings.py
# Defines a class containing all the adjustable settings for the Alien Invasion
# game.


class AlienInvasionSettings:
    """A class to store all the configurable settings for the Alien Invasion game."""
    def __init__(self):
        """Initializes settings with default values."""
        # Display settings.
        self.display_width = 1000
        self.display_height = 600
        self.bg_color = (230, 230, 230)  # light gray

        # Ship settings.
        self.ship_speed = 2
        self.num_lives_start = 3

        # Bullet settings.
        self.bullet_speed = 3.0
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = (60, 60, 60)  # dark gray
        self.max_bullets = 1000

        # Alien settings.
        self.alien_speed = 1.0
        self.alien_vertical_speed = 50.0
        self.alien_direction = +1
