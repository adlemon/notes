from django.contrib.auth import login
from django.contrib.auth.forms import UserCreationForm
from django.shortcuts import render, redirect


def register(request):
    """Register a new user."""
    if request.method == 'POST':
        # Process a completed registration form.
        form = UserCreationForm(data=request.POST)
        if form.is_valid():
            new_user = form.save()
            login(request, new_user)
            return redirect('learning_logs:index')
    else:
        # Create a blank registration form.
        form = UserCreationForm()

    # Display a blank or invalid form.
    context = {'form': form}
    return render(request, 'registration/register.html', context)
