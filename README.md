# Tetris 3D
### IN DEVELOPMENT

Object-oriented Tetris 3D.

Uses GLUT and has VS Code `tasks.json` configurations.

Works on MacOS and Linux.

## To-do

* [X] detectar quando chegou ao fim dos movimentos da peca
* [ ] implementar sequência de pecas - mudar seed do rand
* [ ] * [ ] implementar mudanca de nível
* [ ] fazer uma previsao de qual sera o movimento final da peca se ela apenas for deixada ali caindo
* [ ] fazer uma tecla que faz a Piece avancar até o fim dos movimentos
* [ ] fazer um andar inteiro desaparecer quando for completo (funcoes de checagem para ver se um andar foi completo)
* [ ] fazer o resto dos andares cair depois que um andar desaparecer
* [ ] contar o numero de pontos de acordo com cada nivel
* [ ] mudar a velocidade vertical da peca a cada nivel
* Parametros: Au niveau 0 on peut faire 5-6 déplacements latéraux avant que
la pièce tombe d'un rang, au niveau 9 on ne peut plus faire que 1-2 mouvements latéraux. Le niveau 15
équivaut au niveau de la vitesse à tout le temps appuyer sur la flèche du bas, il n'y a plus de
déplacements latéraux possibles directement. 
* [ ] mostrar a proxima peca na direita 
* [ ] inserir texto
* [ ] fazer tela de entrada na RenderScene1()
* [ ] transformar main.cpp em Game.cpp (organizar em formato de classe)


## Instructions

After unziping/cloning this repository, press Ctrl+Shift+B (Cmd+Shift+B on MacOS) to build.
Then, to run, type and run this in the integrated terminal:

```
./build/tetris3d.app
```


## PARA RELATORIO

- polimorfismo no vetor de Piece pieces, que é um vetor heterogeneo composto por varios tipos de pecas (O_piece, I_piece etc.
