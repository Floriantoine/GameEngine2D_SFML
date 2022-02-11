# MyHunter_Sfml

[![CodeFactor](https://www.codefactor.io/repository/github/floriantoine/myhunter_sfml/badge)](https://www.codefactor.io/repository/github/floriantoine/myhunter_sfml)

### Creation d'un engine de jeu video en SFML
### qui a pour but de developer un jeu du type Hunter, Comme le Duck Hunt
![Drag Racing](https://miro.medium.com/max/1000/1*CHpGqF5_AjZCgQokepOIHQ.jpeg)


Pour ce faire je develop un system d'ECS - Des Managers et Factory.


## `Build & Lancement`

- `git clone git@github.com:Floriantoine/MyHunter_Sfml.git`
- `./build.sh` or `./build.sh -t` (Build Test)
- `cd build`
- `./core/r-type_client` ( Attention ! Actuellement il est important de lancer le projet du dossier build ! )
- `./test/r-type-test` ( start Test )

---
---

# 1) Système de particule 
Je travail actuellement sur le développement de l'engine via un système de particule.

Pour configurer les particules aller voir ce [Readme](./core/json/README.md), les fichiers de config sont present dans le dossier:  
`core/json/particles/`

une Fois le Game lancé et une config load, vous aurez la possibilité de modifier en live la configuration de l'engine via la fenêtre créé avec `Imgui`.

## 2) Event

## Key 
voici un rapide résumé des touches
> `o` = Mode resize  `(indisponible)`  
> `e`/`q` = rotate `(indisponible)`  
> `x` = change Particle Form   
> `r` = load `Particles.json`   
> `d` = load default Particles config `Default.json`     

---

## Mouse

> `click` = fix Sprite `(indisponible)`  


---
---
---

# remerciement

> Merci a `adrienlucbert` pour sont aide dans la réalisation des > concepts, t'elle que l'ECS ou encore different manager !  
> Merci a `agarof` pour m'avoir montré Imgui et pour m'aider a debug
