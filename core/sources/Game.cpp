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
        std::cout << "Something went wrong... " << "\n" << &SDL_GetErrorMsg;
    }
    window = SDL_CreateWindow("Basic gameussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

}


void Game::run() {

    initSystem();
}

void Game::loop() {

}

