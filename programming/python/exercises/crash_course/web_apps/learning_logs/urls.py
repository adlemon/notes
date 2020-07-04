"""Defines URL patterns for learning logs."""

from django.urls import path

from . import views

app_name = 'learning_logs'
urlpatterns = [
    # Home Page.
    path('', views.index, name='index'),
    # List of Topics.
    path('topics/', views.topics, name='topics'),
    # Details page for an individual Topic.
    path('topics/<int:topic_id>/', views.topic, name='topic'),
]
