# Tetris 3D
### IN DEVELOPMENT

Object-oriented Tetris 3D.

Uses GLUT and has VS Code `tasks.json` configurations.

Works on MacOS and Linux.

## To-do

* [X] GAME: Vetor de Pieces
* [X] getCubes para pegar posicao inicial da peca
* [X] 1/2: fazer método isSafe (MATRIX)
ESTÁ BUGADO: fala que as pecas iniciais da O_piece estão ocupadas. Investigar o porquê. (linha 135 da main.cpp)
* [ ] se for safe: inicializa a Piece
* **Inicializar significa:**
* [ ] Passar para Cubes a cor da peca, setá-los como occupied
* [ ] dar Start na Piece

* [ ] COMANDO: implementar escuta de teclas
* [ ] ex: rotate_x(...)
* [ ] checar se a posicao é segura com isSafe()
* [ ] se for, reseta os cubes atualmente ocupados pela peca (usar getCubes() )
* [ ] passa para os novos Cubes a cor da peca e os seta como occupied

### DEPOIS:
* [ ] implementar timer que a cada XXX segundos faz um translate_y
* [ ] detectar quando chegou ao fim dos movimentos da peca
* [ ] fazer uma previsao de qual sera o movimento final da peca se ela apenas for deixada ali caindo
* [ ] fazer uma tecla que faz a Piece avancar até o fim dos movimentos
* [ ] fazer um andar inteiro desaparecer quando for completo (funcoes de checagem para ver se um andar foi completo)
* [ ] fazer o resto dos andares cair depois que um andar desaparecer
* [ ] contar o numero de pontos de acordo com cada nivel
* [ ] mudar a velocidade vertical da peca a cada nivel
* [ ] mostrar a proxima peca na direita 
* [ ] inserir texto?
* [ ] fazer tela de entrada na RenderScene1()


## Instructions

After unziping/cloning this repository, press Ctrl+Shift+B (Cmd+Shift+B on MacOS) to build.
Then, to run, type and run this in the integrated terminal:

```
./build/tetris3d.app
```


## PARA RELATORIO

- polimorfismo no vetor de Piece pieces, que é um vetor heterogeneo composto por varios tipos de pecas (O_piece, I_piece etc.
