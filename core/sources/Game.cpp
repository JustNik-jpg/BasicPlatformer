//
// Created by JustNik on 3 Apr 2022.
//

#include "../headers/Game.h"
#include "iostream"

Game::Game() {

}

Game::~Game() {

}

void Game::initSystem() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized SDL successfully";
    } else {
        std::cout << "Something went wrong when initializing SDL... " << "\n" << &SDL_GetErrorMsg;
    }
    window = SDL_CreateWindow("Basic gameussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    if (!window){
        std::cout << "Something went wrong creating the window... " << "\n" << &SDL_GetErrorMsg;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer){
        std::cout << "Something went wrong creating the renderer... " << "\n" << &SDL_GetErrorMsg;
    }
}


void Game::run() {
    initSystem();
    currentState = GameState::ACTIVE;
    loop();
}

void Game::loop() {
    while (currentState == GameState::ACTIVE) {
        processInput();
        render();
    }
}

void Game::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            default:
                break;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

