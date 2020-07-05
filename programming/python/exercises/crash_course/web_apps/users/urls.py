"""Defines URL patterns for user management."""

from django.urls import path, include

from . import views

app_name = 'users'
urlpatterns = [
    # Include default auth URLs.
    path('', include('django.contrib.auth.urls')),
    # Registration for new users.
    path('register/', views.register, name='register'),
]
