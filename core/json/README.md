



## 1) Particule System Json config

### Fields 

| name        |   type    |         description         |        exemple        |
| :---------- | :-------: | :-------------------------: | :-------------------: |
| count       |    int    |       nbr of particle       |     `count: 2000`     |
| masse       |    int    |      masse of particle      |      `masse: 1`       |
| color       |  string   |      color of particle      |   `color: "green"`    |
| lifeTime    |    obj    |     value for life Time     | [LifeTime](#lifetime) |
| force       | obj/array |       value for force       |    [Force](#force)    |
| pos         | obj/array |     value for spawn Pos     |      [Pos](#pos)      |
| type        |  string   |        particleType         |   `type: "points"`    |
| -           |     -     |           System            |           -           |
| mousePos    |   bool    | particle spawn at Mouse Pos |   `mousePos: false`   |
| mouseForce  |   bool    | particle get Mouse velocity |  `mouseForce: false`  |
| targetMouse |   bool    |  particle target Mouse Pos  | `targetMouse: false`  |

--- 
### `LifeTime` 
```json
"lifeTime": {  
    "init": 6000,  
    "rangeMin": 3000,  
    "rangeMax": 3000  
}, 
```
---

### `Force` 
```json
"force": {  
    "init": [0, 9.81],  
    "rangeMin": 3,  
    "rangeMax": 3  
}, 
"force": [0, 9.81],  
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
