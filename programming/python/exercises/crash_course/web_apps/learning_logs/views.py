from django.shortcuts import render

from .models import Topic


def index(request):
    """Renders the Home Page for the Learning Log."""
    return render(request, 'learning_logs/index.html')


def topics(request):
    """Renders the page listing all topics."""
    topics = Topic.objects.order_by('date_added')
    context = {'topics': topics}
    return render(request, 'learning_logs/topics.html', context)


def topic(request, topic_id):
    """Renders the details page for an individual topic."""
    topic = Topic.objects.get(id=topic_id)
    entries = topic.entry_set.order_by('-date_added')
    context = {'topic': topic, 'entries': entries}
    return render(request, 'learning_logs/topic.html', context)
