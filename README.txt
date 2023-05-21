# BrickBreaker

This Brick Breaker game coded in C using the SDL library.

## How to play

- After open brickBreaker.exe, you face 30 brick, a ball and a racket.
  - When push space button, game start and ball move inside the window.
  - When press D key or right arrow key, racket move to right.
  - When press A key or left arrow key, racket move to left. 
  - When press ESC, the ball placed to first location.
  - When press X key, window shutdown.

## Screen Shots
  <h4>Screen Shot before start</h4>
<img src="image/BrickBreaker1.JPG" style="text-align: center">
  
  <h4>Screen Shot while working</h4>
<img src="image/BrickBreaker2.JPG" style="text-align: center">


## Score
- If the ball collision with brick, score increases by 5 points.
- If the ball go to under of the window, score decreases by 10 points.
- The ball break the first brick, writes text "Score: %d| Destroyed Bricks: %d" in title.
- If you break all bricks, writes text like "CONGRATULATIONS!!! Your Score: %d" in title.

## Racket
- Width of the racket is 80px.
- If the ball collision with racket's left 35px, the ball moves to left.
- If the ball collision with racket's right 35px, the ball moves to right.
- If the ball collision with racket's middle 10px, the ball moves to opposite direction from which it came.

https://github.com/aceliltunc/BrickBreaker