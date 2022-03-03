# `GameEngine2D_SFML`

[![CodeFactor](https://www.codefactor.io/repository/github/floriantoine/myhunter_sfml/badge)](https://www.codefactor.io/repository/github/floriantoine/myhunter_sfml)

### - Creation of a SFML `Game Engine` 
### - The goal is to use my own Engin to create a `Hunter-like` game, like Duck Hunt
![Drag Racing](https://miro.medium.com/max/1000/1*CHpGqF5_AjZCgQokepOIHQ.jpeg)

## `Description`
- To do this I develop an ECS system - Managers and Factory.

---

> ## `Build & Launch`
> 
> 1. `git clone git@github.com:Floriantoine/MyHunter_Sfml.git`
> 1. `./build.sh` or `./build.sh -t` (Build Test)
> 1. `cd build`
> 1. `./core/my_game` ( Warning ! Currently it is important to launch the project from the build folder!)
> 1. `./test/my_game_test` ( start Unit Test )

---

## 1) Advancement 
- I am currently working on the development of the ECS via a particle system.

- To configure the particles go to [Readme](./core/json/README.md), config files are present in the folder: `core/json/particles/`.

- Once the Game is launched and a config load, you will be able to modify the configuration of the ECS components in live, with `Imgui` window.

- You can `create` a new `Entity` and apply components.
  
- You can use the `Implot` graphs to see live performance of different systems.

## 2) Event

- key bind
    > `r` = load `Particles.json`  
    
    > `d` = load default Particles config `Default.json`     

---

> # Acknowledgment
> 
> - Thanks to `adrienlucbert` for his help in the realization of the different concepts and systems, such as the ECS. 
> - Thanks to `agarof` for showing me Imgui and helping to debug
