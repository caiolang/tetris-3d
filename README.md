# Tetris 3D
### IN DEVELOPMENT

Object-oriented Tetris 3D.

Uses GLUT and has VS Code `tasks.json` configurations.

Works on MacOS and Linux.

## To-do

* [X] GAME: Vetor de Pieces
* [X] get_cubes() para pegar posicao inicial da peca
* [X] fazer método is_safe() (MATRIX)
* [X] se for safe: inicializa a Piece
* **Inicializar significa:**
* [X] Passar para Cubes a cor da peca, setá-los como occupied
* [X] dar Start na Piece

* [X] COMANDO: implementar escuta de teclas
* [ ] REESTRUTURAR OS METODOS DE ROTACAO/TRANSLACAO? VER Matrix::rotate_piece_x
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
* [ ] transformar main.cpp em Game.cpp (organizar em formato de classe)
* [ ] Checar no is_safe() se esta passando dos limites do jogo


## Instructions

After unziping/cloning this repository, press Ctrl+Shift+B (Cmd+Shift+B on MacOS) to build.
Then, to run, type and run this in the integrated terminal:

```
./build/tetris3d.app
```


## PARA RELATORIO

- polimorfismo no vetor de Piece pieces, que é um vetor heterogeneo composto por varios tipos de pecas (O_piece, I_piece etc.
