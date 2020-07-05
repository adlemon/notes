from django.contrib.auth.decorators import login_required
from django.http import Http404
from django.shortcuts import render, redirect

from .models import Topic, Entry
from .forms import TopicForm, EntryForm


def check_request_for_topic_allowed(request, topic):
    if request.user != topic.owner:
        raise Http404


def index(request):
    """Renders the Home Page for the Learning Log."""
    return render(request, 'learning_logs/index.html')


@login_required
def topics(request):
    """Renders the page listing all topics."""
    topics = Topic.objects.filter(owner=request.user).order_by('date_added')
    context = {'topics': topics}
    return render(request, 'learning_logs/topics.html', context)


@login_required
def topic(request, topic_id):
    """Renders the details page for an individual topic."""
    topic = Topic.objects.get(id=topic_id)
    check_request_for_topic_allowed(request, topic)
    entries = topic.entry_set.order_by('-date_added')
    context = {'topic': topic, 'entries': entries}
    return render(request, 'learning_logs/topic.html', context)


@login_required
def new_topic(request):
    """Renders a page to add a new topic or adds a new topic to the database."""
    if request.method == 'POST':
        # If data is being submitted using POST, then validate the data and add
        # a new topic to the database.
        form = TopicForm(data=request.POST)
        if form.is_valid():
            new_topic = form.save(commit=False)
            new_topic.owner = request.user
            new_topic.save()
            return redirect('learning_logs:topics')
    else:
        # If data is not being submitted using POST, then render a blank form to
        # collect data about a new topic.
        form = TopicForm()

    # Display the form (either blank or with the data that was already been
    # entered) if we did not receive a valid form.
    context = {'form': form}
    return render(request, 'learning_logs/new_topic.html', context)


@login_required
def new_entry(request, topic_id):
    """Renders a page to add a new entry or adds a new entry to the database."""
    topic = Topic.objects.get(id=topic_id)
    check_request_for_topic_allowed(request, topic)

    if request.method == 'POST':
        # If data is being submitted using POST, then validate the data and add
        # a new entry to the database.
        form = EntryForm(data=request.POST)
        if form.is_valid():
            new_entry = form.save(commit=False)
            new_entry.topic = topic
            new_entry.save()
            return redirect('learning_logs:topic', topic_id=topic.id)
    else:
        # If data is not being submitted using POST, then render a blank form to
        # collect data about a new topic.
        form = EntryForm()

    # Display the form (either blank or with the data that was already been
    # entered) if we did not receive a valid form.
    context = {'topic': topic, 'form': form}
    return render(request, 'learning_logs/new_entry.html', context)


@login_required
def edit_entry(request, entry_id):
    """Edit an existing entry."""
    entry = Entry.objects.get(id=entry_id)
    topic = entry.topic
    check_request_for_topic_allowed(request, topic)

    if request.method == 'POST':
        # Update the database after an edit is posted.
        form = EntryForm(instance=entry, data=request.POST)
        if form.is_valid():
            form.save()
            return redirect('learning_logs:topic', topic_id=topic.id)
    else:
        # Populate the existing text after the initial request to edit an entry.
        form = EntryForm(instance=entry)

    context = {'entry': entry, 'topic': topic, 'form': form}
    return render(request, 'learning_logs/edit_entry.html', context)
