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
    # Page for adding a new Topic.
    path('new_topic/', views.new_topic, name='new_topic'),
    # Page for adding a new Entry.
    path('new_entry/<int:topic_id>/', views.new_entry, name='new_entry'),
    # Page for editing an existing Entry.
    path('edit_entry/<int:entry_id>/', views.edit_entry, name='edit_entry'),
]
