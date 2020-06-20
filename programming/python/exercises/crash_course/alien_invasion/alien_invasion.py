#!/usr/bin/python3
# alien_invasion.py
# Play an Alien Invasion game.

import sys
import time

import pygame

import alien
import bullet
import game_stats
import settings
import ship


class AlienInvasion:
    """An Alien Invasion game."""
    def __init__(self):
        """Initialize game resources."""
        pygame.init()

        self.settings = settings.Settings()

        self.display = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
        self.settings.display_width = self.display.get_rect().width
        self.settings.display_height = self.display.get_rect().height
        pygame.display.set_caption('Alien Invasion')

        self.stats = game_stats.Stats(self)

        self.ship = ship.Ship(self)
        self.bullets = pygame.sprite.Group()
        self.aliens = pygame.sprite.Group()
        self._reset_game()

    def _reset_game(self):
        self.ship.reset()
        self.bullets.empty()
        self.aliens.empty()
        self._create_aliens()
        time.sleep(0.5)

    def _create_aliens(self):
        """Create the aliens."""
        alien_width, alien_height = alien.Alien(self).rect.size
        ship_height = self.ship.height

        num_columns = ((self.settings.display_width - 2 * alien_width) //
                       (2 * alien_width))
        num_rows = (
            (self.settings.display_height - 3 * alien_height - ship_height) //
            (2 * alien_height))

        for row in range(num_rows):
            for col in range(num_columns):
                a = alien.Alien(self)
                a.x = (2 * col + 1) * alien_width
                a.y = (2 * row + 1) * alien_height
                a.rect.x = a.x
                a.rect.y = a.y
                self.aliens.add(a)

    def _quit(self):
        sys.exit()

    def _fire_bullet(self):
        if len(self.bullets) < self.settings.max_bullets:
            self.bullets.add(bullet.Bullet(self))

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
        """Update bullet positions."""
        self.bullets.update()
        for b in self.bullets.copy():
            if b.rect.bottom < 0:
                self.bullets.remove(b)

    def _process_bullet_hits(self):
        """Remove any bullets and aliens that are colliding."""
        pygame.sprite.groupcollide(groupa=self.bullets,
                                   dokilla=True,
                                   groupb=self.aliens,
                                   dokillb=True)

    def _is_ship_colliding_with_alien(self):
        """Check whether the ship is colliding with an alien."""
        return (pygame.sprite.spritecollideany(self.ship, self.aliens) is
                not None)

    def _is_alien_at_bottom(self):
        """Check whether at least one alien has reached the bottom of the screen."""
        display_rect = self.display.get_rect()
        for alien in self.aliens.sprites():
            if alien.rect.bottom >= display_rect.bottom:
                return True
        return False

    def _should_aliens_change_direction(self):
        for alien in self.aliens.sprites():
            if not alien.is_on_screen():
                return True
        return False

    def _change_aliens_direction(self):
        for alien in self.aliens.sprites():
            alien.rect.y += self.settings.alien_vertical_speed
        self.settings.alien_direction *= -1

    def _update_aliens(self):
        if self._should_aliens_change_direction():
            self._change_aliens_direction()
        self.aliens.update()

    def _update_display(self):
        self.display.fill(self.settings.bg_color)
        self.ship.draw()
        for b in self.bullets.sprites():
            b.draw()
        self.aliens.draw(self.display)

        # Update the display.
        pygame.display.flip()

    def _process_lost_turn(self):
        """Reset the game after a lost turn."""
        self.stats.num_lives_left -= 1
        self._reset_game()

    def run(self):
        """Run the Alien Invasion game."""
        while True:
            self._handle_events()

            if self.stats.num_lives_left > 0:
                self.ship.update()
                self._update_bullets()
                self._update_aliens()
                self._process_bullet_hits()
                if not self.aliens:
                    self.bullets.empty()
                    self._create_aliens()
                if (self._is_ship_colliding_with_alien()
                        or self._is_alien_at_bottom()):
                    self._process_lost_turn()

            self._update_display()


if __name__ == '__main__':
    AlienInvasion().run()
