#!/usr/bin/python3
# button.py
# Class to manage a button for the alien invasion game.

import pygame


class Button:
    """Class to manage a button for the alien invasion game."""
    def __init__(self, game, msg):
        """Initialize the button."""
        self.game = game

        self.width = 200
        self.height = 50
        self.bg_color = (0, 255, 0)
        self.text_color = (255, 255, 255)
        self.font = pygame.font.SysFont(name=None, size=48)

        self.rect = pygame.Rect(
            0,  # top
            0,  # left
            self.width,  # width
            self.height,  # height
        )
        self.rect.center = self.game.display.get_rect().center

        self._make_msg(msg)

    def _make_msg(self, msg):
        """Render the image used to display msg as text."""
        self.msg_image = self.font.render(
            msg,  # text
            True,  # antialias
            self.text_color,  # color
            self.bg_color,  # background
        )
        self.msg_image_rect = self.msg_image.get_rect()
        self.msg_image_rect.center = self.rect.center

    def draw(self):
        self.game.display.fill(self.bg_color, self.rect)
        self.game.display.blit(self.msg_image, self.msg_image_rect)
