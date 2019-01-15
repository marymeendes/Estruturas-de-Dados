gcc -o teste lista.c dijkstra.c main.c -Wall
./teste

Exemplo:
Entradas
0 1 2 3 -1
1 10
3 6
-1 -1
2 4
-1 -1
1 1
3 2
-1 -1
0 4
2 2
-1 -1
Resultado
Matriz de adjacência
0 10 0 6
0 0 4 0
0 1 0 2
4 0 2 0

Vertice|Distancia|Predecessor|Explorado
0 | 0 | -1 | 1
1 | 9 | 2 | 1
2 | 8 | 3 | 1
3 | 6 | 0 | 1
  

