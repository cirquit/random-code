#! /bin/bash

echo -e "Hi, please type the word: \c "

read word

echo "The word you entered is: $word"

echo -e "Can you please enter two words?"

read word1 word2

echo "Here is your input: \"$word1\" \"$word2\""

echo -e "How do you fell about bash scripting?"

# read stores the replay in the build-in variable

read

echo "You said $REPLY, I'm glad to hear that!"

echo -e "What are you favourite colours?"

# read -a reads into an array

read -a colours

echo "My favourite colours are alos ${colours[0]}, ${colours[1]} and ${colours[2]} :-)"