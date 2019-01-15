Código foi feito por Mariana Mendes da Silva.

Objetivo: Implementar uma tabela hash de tamanho 7 com encadeamento interior 
que é dividida em uma zona de endereçamento de tamanho 4 (p) e uma zona de 
colisões de tamanho 3 (s).

Para executar o programa basta abrir o terminal na pasta onde estão os códigos-fonte
e digitar: 

"gcc -o teste cliente.c lista.c compartimento_hash.c main.c -Wall" [ENTER]
"./teste" [ENTER]
Obs.: "teste" pode ser mudado o nome de preferência e o comando deve ser escrito
sem aspas.

A execução do programa acarretará também na execução de diversos de testes de caso.
Para visualizar o estado da tabela ao término da execução do programa, basta
executar também um código auxiliar que lê e imprime os dados de um arquivo de registros.

Para tal, faça como a seguir:

No terminal, digite: 

"gcc -o t cliente.c lista.c testeLeRegistro.c -Wall" [ENTER]
"./t" [ENTER]
"tabHash.dat" [ENTER]

Obs.: "t" pode ser substituído por qualquer nome de preferência, o comando deve
ser escrito sem aspas e tabHash.dat é o arquivo final que conterá o tabela hash.
 