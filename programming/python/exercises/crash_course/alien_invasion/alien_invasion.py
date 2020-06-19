#!/usr/bin/python3
# alien_invasion.py
# Play an Alien Invasion game.

import sys

import pygame

import alien_invasion_settings
import alien_invasion_ship
import alien_invasion_bullet


class AlienInvasion:
    """An Alien Invasion game."""
    def __init__(self):
        """Initialize game resources."""
        pygame.init()

        self.settings = alien_invasion_settings.AlienInvasionSettings()

        self.display = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
        self.settings.display_width = self.display.get_rect().width
        self.settings.display_height = self.display.get_rect().height
        pygame.display.set_caption('Alien Invasion')

        self.ship = alien_invasion_ship.AlienInvasionShip(self)
        self.bullets = pygame.sprite.Group()

    def _quit(self):
        sys.exit()

    def _fire_bullet(self):
        if len(self.bullets) < self.settings.max_bullets:
            self.bullets.add(alien_invasion_bullet.AlienInvasionBullet(self))

    def _handle_key_down_event(self, event):
        if event.key == pygame.K_q:
            self._quit()
        elif event.key == pygame.K_LEFT:
            self.ship.left_thruster_on = True
        elif event.key == pygame.K_RIGHT:
            self.ship.right_thruster_on = True
        elif event.key == pygame.K_SPACE:
            self._fire_bullet()

    def _handle_key_up_event(self, event):
        if event.key == pygame.K_LEFT:
            self.ship.left_thruster_on = False
        elif event.key == pygame.K_RIGHT:
            self.ship.right_thruster_on = False

    def _handle_events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self._quit()
            elif event.type == pygame.KEYDOWN:
                self._handle_key_down_event(event)
            elif event.type == pygame.KEYUP:
                self._handle_key_up_event(event)

    def _update_bullets(self):
        """Update bullet positions and clean up bullets that have moved off-screen."""
        self.bullets.update()
        for bullet in self.bullets.copy():
            if bullet.rect.bottom < 0:
                self.bullets.remove(bullet)

    def _update_display(self):
        self.display.fill(self.settings.bg_color)
        self.ship.draw()
        for bullet in self.bullets.sprites():
            bullet.draw()

        # Update the display.
        pygame.display.flip()

    def run(self):
        """Run the Alien Invasion game."""
        while True:
            self._handle_events()
            self.ship.update()
            self._update_bullets()
            self._update_display()


if __name__ == '__main__':
    AlienInvasion().run()
