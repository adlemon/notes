# Create a new virtual environment called `ll_env`.
python -m venv ll_env

# Activate the virtual environment called `ll_env`.
source ll_env/bin/activate

# Stop using the current virtual environment.
deactivate

# Install Django.
pip install django

# Create a new Django project called `learning_log`.
django-admin startproject learning_log .

# Create a SQLite database to store the application's data.
python manage.py migrate

# View the project in its current state.
python manage.py runserver

# Create an app for the `learning_logs` project.
# Note that the Django project is called `learning_log` (without an `s` at the
# end), while the app is called `learning_logs` (with an `s` at the end).
python manage.py startapp learning_logs

# Update the SQLite database to include new models.
python manage.py makemigrations learning_logs
python manage.py migrate

# Create a superuser for the project.
python manage.py createsuperuser

# Start the Django shell (for testing, troubleshooting, etc.).
python manage.py shell
