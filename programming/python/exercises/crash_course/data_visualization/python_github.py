#!/usr/bin/python3
# Analyzer GitHub repositories whose primary language is Python.

import json
import requests

from plotly.graph_objs import Bar
from plotly import offline

# Get data on popular Python repositories using the GitHub API.
github_api_url = ('https://api.github.com/search/repositories'
                  '?q=language:python'
                  '&sort=stars')
headers = {'Accept': 'application.vnd.github.v3+json'}
api_response = requests.get(github_api_url, headers=headers)
if api_response.status_code != 200:
    print('API request failed.')
    quit()


# Process the data from the API response to extract and format the data that we
# intend to use in our plot.
class Repository:
    """Class to represent simplified data about a GitHub repository."""
    def __init__(self, name, stars, owner, description, url):
        self.name = name
        self.stars = stars
        self.owner = owner
        self.description = description
        self.url = url


repositories = []
for repository in api_response.json()['items']:
    repositories.append(
        Repository(name=repository['name'],
                   stars=repository['stargazers_count'],
                   owner=repository['owner']['login'],
                   description=repository['description'],
                   url=repository['html_url']))

# Make a bar plot of popular Python GitHub repositories.
repo_links = [
    f"<a href='{repository.url}'>{repository.name}</a>"
    for repository in repositories
]
repo_stars = [repository.stars for repository in repositories]
repo_tooltips = [
    f'{repository.owner}<br />{repository.description}'
    for repository in repositories
]

offline.plot(
    {
        'data': [{
            'type': 'bar',
            'x': repo_links,
            'y': repo_stars,
            'hovertext': repo_tooltips,
            'marker': {
                'color': 'rgb(60, 100 ,150)',
                'line': {
                    'width': 1.5,
                    'color': 'rgb(25, 25, 25)',
                },
            },
            'opacity': 0.6,
        }],
        'layout': {
            'title': 'Most-Starred Python Projects on GitHub',
            'titlefont': {
                'size': 28,
            },
            'xaxis': {
                'title': 'Repository',
                'titlefont': {
                    'size': 24,
                },
                'tickfont': {
                    'size': 14,
                },
            },
            'yaxis': {
                'title': '# of Stars',
                'titlefont': {
                    'size': 24,
                },
                'tickfont': {
                    'size': 14,
                },
            },
        }
    },
    filename='python_repos.html',
)
