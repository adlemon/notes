#!/usr/bin/python3
# settings.py
# Class for settings for an alien invasion game.


class Settings:
    """A class to store the settings for the alien invasion game."""
    def __init__(self):
        """Initialized settings."""
        # Display settings.
        self.display_width = 1000
        self.display_height = 600
        self.bg_color = (230, 230, 230)  # light gray

        # Ship settings.
        self.initial_ship_speed = 2
        self.num_lives_start = 3

        # Bullet settings.
        self.initial_bullet_speed = 10.0
        self.bullet_width = 3
        self.bullet_height = 15
        self.bullet_color = (60, 60, 60)  # dark gray
        self.max_bullets = 1000

        # Alien settings.
        self.initial_alien_speed = 1.0
        self.alien_vertical_speed = 5.0

        # Level settings.
        self.reset_level_settings()
        self.level_speed_increase_factor = 1.5
        self.level_score_increase_factor = 1.1

    def reset_level_settings(self):
        """Reset settings that vary by level to their initial values."""
        self.ship_speed = self.initial_ship_speed
        self.bullet_speed = self.initial_bullet_speed
        self.alien_speed = self.initial_alien_speed
        self.alien_direction = +1
        self.points_per_alien = 50

    def increase_level(self):
        """Update settings that vary by level when starting a new level."""
        self.ship_speed *= self.level_speed_increase_factor
        self.bullet_speed *= self.level_speed_increase_factor
        self.alien_speed *= self.level_speed_increase_factor
        self.alien_direction = +1
        self.points_per_alien = int(self.points_per_alien *
                                    self.level_score_increase_factor)
