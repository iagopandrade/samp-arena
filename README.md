# arena-samp

A ideia era ser um sistema de arenas dinâmicas, onde o administrador poderia configurar: modo de jogo, tipo de armas, tempo, quantidade de jogadores, etc. Porém, estou priorizando outros assuntos e não consegui terminei o código.

## Comandos:  
```
/arenas
```

```
/sairaarena
```

```
/a51
```  

## Funções:  


```pawn 
// Coloca o jogador na arena
SetPlayerArena(int playerid, int arenaID);
```   

```pawn
// Remove o jogador da arena
RemovePlayerFromArena(int playerid, int arenaID);
```

```pawn
// // Exibe uma dialog com nome e quantidade de jogadores na arena
ShowArenaInfoDialog(int playerid, int arenaID);
```

```pawn
// Conta quantos jogadores estao em uma arena
CountPlayersInArena(int playerid, int arenaID);
```

```pawn
// Configura as arenas
InitializeArenas(int playerid, int arenaID);
```