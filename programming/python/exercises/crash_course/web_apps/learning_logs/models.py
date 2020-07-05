from django.db import models
from django.contrib.auth.models import User


class Topic(models.Model):
    """Represents a topic that a user is learning about."""
    text = models.CharField(max_length=200)
    date_added = models.DateTimeField(auto_now_add=True)
    owner = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        """Returns a string representation of the Topic."""
        return self.text


class Entry(models.Model):
    """Represents a log entry for a Topic."""
    topic = models.ForeignKey(Topic, on_delete=models.CASCADE)
    text = models.TextField()
    date_added = models.DateTimeField(auto_now_add=True)

    class Meta:
        verbose_name_plural = 'entries'

    def __str__(self):
        """Returns a string representation of the Entry."""
        return f'{self.text[:50]}' + ('...' if len(self.text) > 50 else '')
