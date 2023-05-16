#ifndef GAME_HEADER_H_INCLUDED
#define GAME_HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
//definition of window's width and height
static const int width = 400;
static const int height = 600;

static const int ballsize = 5; // definition of ballsize

float SPEED = 140;  // Definition of ball's speed

// player's size and speed
const int player_width = 80;
const int player_height = 7;
const int player_margin = 570;
const float player_move_speed = 150.0f;

// size of bricks
const int bricks_width = 29;
const int bricks_height = 29;

const int row = 5;
const int col = 10;

// count of the destroyed bricks
size_t countDestroyed=0;

bool served = false;


SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
//property of ball
typedef struct Ball{
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    int size;
} Ball;
Ball ball;

//property of player (racket)
typedef struct Player{
    int score;
    float xposition;
} Player;
Player racket;

//property of bricks
typedef struct Bricks{
    int x;
    int y;
    int w;
    int h;
    bool destroyed;
}Bricks;
Bricks bricks[50];

bool CoinFlip(void){
    return rand() % 2 == 1 ? true : false;
}

Ball MakeBall(int size){
    Ball ball = {
        .x = 197,
        .y = 450,
        .size = size,
        .xSpeed = SPEED * (CoinFlip() ? 1 : -1 ),
        .ySpeed = SPEED * (CoinFlip() ? 1 : -1 ),
    };
    return ball;
}

void UpdateBall(Ball *ball, float elapsed ){


    if(!served){
        ball->x = 197;
        ball->y = 450;
        return;
    }

    // Speed of xy direction
    ball->x += ball->xSpeed * elapsed;
    ball->y += ball->ySpeed * elapsed;

    // bounce from the left side
    if(ball->x < 0){
        ball->xSpeed = SDL_fabs(ball->xSpeed);
    }
    // bounce from the right side
    if(ball->x > width - ballsize){
        ball->xSpeed = -SDL_fabs(ball->xSpeed);
    }
    // bounce from the top
    if(ball->y < 0){
        ball->ySpeed = SDL_fabs(ball->xSpeed);
    }
    // bounce from the under
    if(ball->y > height - ballsize){
        UpdateScore(1, 10);
        served = false;
    }

}

void RenderBall(const Ball *ball){
    int size = ball->size;
    //position of the ball
    SDL_Rect rect = {
        .x = ball->x,
        .y = ball->y,
        .w = size,
        .h = size,

    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//ball color
    SDL_RenderFillRect(renderer, &rect);
}

Player MakePlayer(void){
    Player player = {
        .xposition = 140,
    };
    return player;
}
void UpdatePLayer(float elapsed){
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    //starting if press space button
    if(keyboardState[SDL_SCANCODE_SPACE]){
        served = true;
    }
    //ending if press space button
    if(keyboardState[SDL_SCANCODE_ESCAPE]){
        served = false;
    }
    //shutdown if press x button
    if(keyboardState[SDL_SCANCODE_X]){
        Shutdown();
    }
    // move to left
    if(keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT]){
        racket.xposition -= player_move_speed * elapsed;
    }
    // move to right
    if(keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT]){
        racket.xposition += player_move_speed * elapsed;
    }
    // restrict racket in width of the window
    if(racket.xposition < 0){
        racket.xposition = 0;
    }
    if(racket.xposition >= 320){
        racket.xposition = 320;
    }

    // Check if the ball overlaps with racket
    SDL_Rect ballRect = {
        .x = ball.x,
        .y = ball.y,
        .w = ball.size,
        .h = ball.size,
    };

    SDL_Rect racketRect = {
        .x = racket.xposition,
        .y = player_margin,
        .w = player_width,
        .h = player_height,
    };

    if(SDL_HasIntersectionF(&ballRect, &racketRect)){
        ball.ySpeed = -SDL_fabs(ball.ySpeed);

        if(ball.x < (racket.xposition+35)){
            ball.xSpeed = -SDL_fabs(ball.xSpeed);
        }
        if(ball.x > (racket.xposition+35)){
            ball.xSpeed = SDL_fabs(ball.xSpeed);
        }

    }

}
void RenderPlayer(void){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect racketRect = {
        .y = player_margin,
        .x = (int) (racket.xposition) ,
        .w = player_width,
        .h = player_height,
    };

    SDL_RenderFillRect(renderer, &racketRect);
}


Bricks MakeBricks(void){
    SDL_Rect ballRect = {   .x = ball.x,    .y = ball.y,    .w = ball.size, .h = ball.size, };
    for(size_t i = 0 ; i < (col*row) ; i++ ){
        Bricks bricks[i];
    }
    for(size_t i = 0 ; i < (col*row) ; i++ ){
         for(size_t j = 0 ; j < row ; j++){
            for(size_t k = 0 ; k < col ; k++ ){
                bricks[10*j+k].x = 39*k+10;
                bricks[10*j+k].y = 39*j+10;
                bricks[10*j+k].w = bricks_width;
                bricks[10*j+k].h = bricks_height;
            }
        }
    }
    return bricks[50];
}

void UpdateBricks(float elapsed){


    // Check if the ball overlaps with bricks
    SDL_Rect ballRect = {   .x = ball.x,    .y = ball.y,    .w = ball.size, .h = ball.size, };

    SDL_Rect brickRect[50];


    for(size_t i = 0 ; i < (col*row) ; i++ ){
        if(bricks[i].destroyed==true){
                    if(bricks[49].destroyed == true){
                        brickRect[49].x = -5;
                        brickRect[49].y = -5;
                        brickRect[49].w = 0;
                        brickRect[49].h = 0;
                    }else{
                    for(size_t j = 0 ; j < row ; j++){
                        for(size_t k = 0 ; k < col ; k++ ){
                            brickRect[10*j+k].x = -5;
                            brickRect[10*j+k].y = -5;
                            brickRect[10*j+k].w = 0;
                            brickRect[10*j+k].h = 0;
                    }
                }
            }

        }else{
                for(size_t j = 0 ; j < row ; j++){
                    for(size_t k = 0 ; k < col ; k++ ){
                        if(bricks[10*j+k].destroyed==false){
                            brickRect[10*j+k].x = bricks[10*j+k].x;
                            brickRect[10*j+k].y = bricks[10*j+k].y;
                            brickRect[10*j+k].w = bricks_width;
                            brickRect[10*j+k].h = bricks_height;
                        }
                    }
                }
        }

    }

    for(size_t i = 0 ; i < (col*row) ; i++ ){
        if(i==49){
            if(SDL_HasIntersectionF(&ballRect, &brickRect[49])){
                // bounce from left of the Brick
                if(ball.x < brickRect[49].x){
                    ball.xSpeed = -SDL_fabs(ball.xSpeed);
                }
                // bounce from right of the Brick
                else if(ball.x > brickRect[49].x + 27){
                    ball.xSpeed = SDL_fabs(ball.xSpeed);
                }
                // bounce from top of the Brick
                if(ball.y < (brickRect[49].y) ){
                    ball.ySpeed = -SDL_fabs(ball.ySpeed);
                }
                // bounce from under of the Brick
                else if(ball.y >=(brickRect[49].y + 27)){
                    ball.ySpeed = SDL_fabs(ball.ySpeed);
                }
                bricks[49].destroyed=true;
                UpdateScore(2,5);
                i==50;
            }
        }
        else if( i < 49){
            if(SDL_HasIntersectionF(&ballRect, &brickRect[i])){
                // bounce from left of the Brick
                if(ball.x < brickRect[i].x){
                    ball.xSpeed = -SDL_fabs(ball.xSpeed);
                }
                // bounce from right of the Brick
                else if(ball.x > brickRect[i].x + 27){
                    ball.xSpeed = SDL_fabs(ball.xSpeed);
                }
                // bounce from top of the Brick
                if(ball.y < (brickRect[i].y) ){
                    ball.ySpeed = -SDL_fabs(ball.ySpeed);
                }
                // bounce from under of the Brick
                else if(ball.y >=(brickRect[i].y + 27)){
                    ball.ySpeed = SDL_fabs(ball.ySpeed);
                }

                bricks[i].destroyed=true;
                countDestroyed += 1;
                UpdateScore(2,5);
            }
        }
    }
    //text in title if all bricks are broken
    if(countDestroyed >= (col*row)){
        char *fmt = "CONGRATULATIONS!! All bricks are broken";
        int len = snprintf(NULL, 0 ,fmt, racket.score, countDestroyed);
        char buf[ len + 1];
        snprintf(buf, len + 1 , fmt, racket.score, countDestroyed);

        SDL_SetWindowTitle(window, buf);
    }


}
void RenderBricks(void){

    SDL_Rect ballRect = {   .x = ball.x,    .y = ball.y,    .w = ball.size, .h = ball.size, };

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_Rect brickRect[50];

    for(size_t i = 0 ; i < (col*row) ; i++ ){
        if(bricks[i].destroyed==true){
                    if(bricks[49].destroyed == true){
                        brickRect[49].x = -5;
                        brickRect[49].y = -5;
                        brickRect[49].w = 0;
                        brickRect[49].h = 0;
                    }else{
                    for(size_t j = 0 ; j < row ; j++){
                        for(size_t k = 0 ; k < col ; k++ ){
                            brickRect[10*j+k].x = -5;
                            brickRect[10*j+k].y = -5;
                            brickRect[10*j+k].w = 0;
                            brickRect[10*j+k].h = 0;
                    }
                }
            }

        }else{
            for(size_t i = 0 ; i < (col*row) ; i++ ){
                for(size_t j = 0 ; j < row ; j++){
                    for(size_t k = 0 ; k < col ; k++ ){
                        if(bricks[10*j+k].destroyed==false){
                            brickRect[10*j+k].x = bricks[10*j+k].x;
                            brickRect[10*j+k].y = bricks[10*j+k].y;
                            brickRect[10*j+k].w = bricks_width;
                            brickRect[10*j+k].h = bricks_height;
                        }
                    }
                }
            }
        }

    }


    for( size_t i = 0 ; i < col*row ; i++){
        if(bricks[i].destroyed == false){
        SDL_RenderFillRect(renderer, &brickRect[i]);
        }

    }

}

void UpdateScore(int _case, int points){


    if(_case == 1){
        racket.score -= points;
            served = false;
    }
    if(_case == 2){
        racket.score += points;
            served = true;
    }

    char *fmt = "Score : %d | Destroyed Bricks : %d";
    int len = snprintf(NULL, 0 ,fmt, racket.score, countDestroyed);
    char buf[ len + 1];
    snprintf(buf, len + 1 , fmt, racket.score, countDestroyed);

    SDL_SetWindowTitle(window, buf);

}

bool Initialize(void)
{
        // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // Create a SDL window
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    ball = MakeBall(ballsize);
    racket = MakePlayer();
    bricks[50] = MakeBricks();
    return true;
}
void Update(float elapsed)
{
        // Clear screen with black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Motion of the ball
    UpdateBall(&ball, elapsed);
        // Render Ball
    RenderBall(&ball);

    //Motion of the racket
    UpdatePLayer(elapsed);
    // Render Racket
    RenderPlayer();

    // Presence of bricks
    UpdateBricks(elapsed);
    // Render Bricks
    RenderBricks();

    SDL_RenderPresent(renderer);
}
void Shutdown(){
    if(renderer){
        SDL_DestroyRenderer(renderer);
    }
    if(window){
            SDL_DestroyWindow(window);
    }
    SDL_Quit();
}

#endif // GAME_HEADER_H_INCLUDED
