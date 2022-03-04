



> ## 1) Particule System Json config
> 
> - ### A. Components 
>    
>   | name     |   type    |     description     |        exemple        | random |
>   | :------- | :-------: | :-----------------: | :-------------------: | :----: |
>   | Damage   |    int    |       Damage        |      `Damage: 1`      | yes    |
>   | Color    |  string   |        Color        |   `color: "green"`    | no     |
>   | Force    | obj/array |   Force             |    [Force](#force)    | yes    |
>   | Health   | int/obj   |   Health            |    [Health](#Health)  | yes    |
>   | Masse    |    int    |        Masse        |      `masse: 1`       | yes    |
>   | Pos      | obj/array | value for spawn Pos |      [Pos](#pos)      | yes    |
>   | RectangleShape | bool | Give Rectangle Shape |    --               | no     |
>   | Size     |   int/obj | Size                |    --                 | yes    |
>   | Speed    |   int/obj | Speed               |    --                 | yes    |
>   | SpawnPos |   int/obj | Spawn Pos           |    --                 | yes    |
>   | Sprite   | string/obj| Add texture         |    --                 | no     |
>   | TargetEntity |   int | Target Entity       |    --                 | no     |
>   | Orbit    |   int | Orbit around Entity     |    --                 | no     |

> - ### B. System Activator 
> 
>   | name             | type  |         description         |       exemple        |
>   | :--------------- | :---: | :-------------------------: | :------------------: |
>   | -                |   -   |      System Activator       |          -           |
>   | DiesLeavesScreen | bool  |   Dies if leaving Screen    | `DiesLeavesScreen: true` |
>   | Gravity          | bool  |   Apply Gravity             | `Gravity: true` |
>   | KeyMovement          | bool  |   Move with Key           | `KeyMovement: true` |
>   | LifeTime |    bool    | Loose Life with Time | |          |
>   | MouseForce |    bool    | Give Mouse Force | |          |
>   | ParticleIdentity |    string    | Identify Particle | `ParticleIdentity: 'quads'`|          |
>   | isSolidBlock |    bool    | Have Collision | |          |
>   | SpawnMousePos    | bool  | Spawn at Mouse Pos (need *`SpawnPos`*)         |  `SpawnMousePos: true`   |
>   | LinearMovement |    bool    | Linear Shift | |          |
>   | PresseSpaceMakeEntity |    string    | Trigger Space / Create Entity | |          |
>   | HaveCollisionDamage |    bool    | Collision do Damage (need *`Health`*)  | |          |

--- 

### `Health` 
```json
"Health": {  
    "init": 6000,  
    "rangeMin": 3000,  
    "rangeMax": 3000  
}, 
```
---

### `Force` 
```json
"Force": {  
    "init": [0, 9.81],  
    "rangeMin": 3,  
    "rangeMax": 3  
}, 
"Force": [0, 9.81],  
```

---
### `Pos` 
```json
"Pos": {  
    "init": [200, 200],  
    "rangeMin": 100,  
    "rangeMax": 100  
}, 
"Pos": [200, 200],  
```
---

## 2) System

>   | name      |     description     |
> |:--: | :--: |
> |-- | -- |


