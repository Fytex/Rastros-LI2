# Rastros-LI2    2020


## What's the language?

This game is developed in C.


## What's this game?

Rastros is a Maths' game created back in 1992. It's a game where both players try to take the *ball* to their own *goal* or put the enemy in the corner (blocking the enemy so when its their turn they don't have a space to play).


## Bot

For the bot we did a very OP late-game however very weak at early. This was all because we had no time for the early since covid-19 changed a lot our time's management and each one's calendars).

Bot will execute the first allowed/possible algorithm in the following order:

  - Brute-Force (Which can only be executed if there are few spaces available and it has to be under 2s in a normal computer)
  - Flood-Fill (This is pretty fast to calculate the shortest path to the bot's base. However this wont work in case there is no path)
  - Euclidean Distance (Just a math's formula to calculate which one of the next 8 available spaces is the nearest to the bot's base)
