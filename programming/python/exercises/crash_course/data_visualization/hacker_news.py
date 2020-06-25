#!/usr/bin/python3
# hacker_news.py

import json
import requests

# Define base URLs for Hacker News.
base_query_url = 'https://hacker-news.firebaseio.com/v0'
base_story_url = 'https://news.ycombinator.com'

# Get the IDs of the top stories on Hacker News.
top_stories_response = requests.get(f'{base_query_url}/topstories.json')
if top_stories_response.status_code != 200:
    print('Failed to fetch top stories.')
    quit()


# Get additional data about each of the top stories.
class Story:
    """Class to represent simplified data about a Hacker News story."""
    def __init__(self, title, discussion_link, num_comments):
        self.title = title
        self.discussion_link = discussion_link
        self.num_comments = num_comments


stories = []
for story_id in top_stories_response.json()[:10]:
    story_response = requests.get(f'{base_query_url}/item/{story_id}.json')
    if story_response.status_code != 200:
        print(f'Unable to fetch data about story ID: {story_id}')
        continue

    story_response_json = story_response.json()
    try:
        stories.append(
            Story(
                title=story_response_json['title'],
                discussion_link=f'{base_story_url}/item?id={story_id}',
                num_comments=story_response_json.get('descendants', 0),
            ))
    except:
        print(f'Failed to parse response for story ID: {story_id}')
        print(f'{json.dumps(story_response_json, indent=4)}')

# Print the top stories in descending order of number of comments.
stories.sort(key=lambda s: -s.num_comments)
for i, story in enumerate(stories):
    if i > 0:
        print()
    print(f'Title: {story.title}')
    print(f'Discussion Link: {story.discussion_link}')
    print(f'# of Comments: {story.num_comments}')
