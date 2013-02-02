ReactionTime
============

Qt app to measure a user's average reaction time.

Using ReactionTime
------------------

Using the program is simple.

1. Click Begin
2. Press the spacebar as soon as the millisecond counter starts to count up
3. After ten trials, your average reaction time (in milliseconds) is displayed in green

Details
-------

ReactionTime provides a rough metric of how long it takes for a user to react to an event that happens at a random time.  It's not meant to be a precise measurement, but it can be used to gauge differences between different people, or between the same person at different times.

Between trials, the program pauses for between 2 and 8 seconds, chosen at random.  The random number generator is seeded by the time of day, so concurrent runs of the program will not produce the same delay times.
