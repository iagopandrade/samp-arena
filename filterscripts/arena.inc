/*
 * Copyright (c) 2025 iagopandrade
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if defined _arena_included
    #endinput
#endif
#define _arena_included

#define MAX_ARENAS 5

enum {
    DIALOG_ARENAS,
    DIALOG_INFORMACOES_ARENAS
};

enum ArenaData {
    Float:x,            
    Float:y,            
    Float:z,            
    Float:rotation,     
    virtualWorld,       
    interior,           
    name[32],         
	atalho[16], 
    maxPlayers,       
    weaponList[10]
};
new g_Arenas[MAX_ARENAS][ArenaData];
new g_PlayerArena[MAX_PLAYERS];

SetPlayerArena(playerid, arenaID) {
    if (arenaID < 0 || arenaID >= MAX_ARENAS) 
        return 0;

	if (g_PlayerArena[playerid] == arenaID)
		return SendClientMessage(playerid, -1, "Voce ja esta nessa arena.");
		
    g_PlayerArena[playerid] = arenaID;

    SetPlayerPos(playerid, g_Arenas[arenaID][x], g_Arenas[arenaID][y], g_Arenas[arenaID][z]);
    SetPlayerVirtualWorld(playerid, g_Arenas[arenaID][virtualWorld]);
    SetPlayerInterior(playerid, g_Arenas[arenaID][interior]);
    SendClientMessageToAll(-1, "%s entrou na arena: %s (%d/%d).", GetPlayerNameEx(playerid), g_Arenas[arenaID][name], CountPlayersInArena(arenaID), g_Arenas[arenaID][maxPlayers]);
    return 1;
}

RemovePlayerFromArena(playerid, arenaID) {
    if (arenaID < 0 || arenaID >= MAX_ARENAS) return 0;

    new arenaid = g_PlayerArena[playerid];
    g_PlayerArena[playerid] = -1;

    SendClientMessageToAll(-1, "%s saiu da arena: %s (%d/%d).", GetPlayerNameEx(playerid), g_Arenas[arenaid][name], CountPlayersInArena(arenaid), g_Arenas[arenaid][maxPlayers]);

	SetPlayerPos(playerid, 0.0, 0.0, 0.0);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerInterior(playerid, 0);
    SendClientMessage(playerid, -1, "Voce saiu da arena.");
    return 1;
}

ShowArenaInfoDialog(playerid) {
    new string[1024];
    new temp[128];   

    format(string, sizeof(string), "Arena\tAtalho\tPlayers\n");

    for (new i = 0; i < MAX_ARENAS; i++) {

        new currentPlayers = CountPlayersInArena(i);
        new arenaMaxPlayers = g_Arenas[i][maxPlayers];

        if (arenaMaxPlayers <= 0) 
            arenaMaxPlayers = 1;

        format(temp, sizeof(temp), "%s\t%s\t%d/%d\n", 
            g_Arenas[i][name], g_Arenas[i][atalho], currentPlayers, arenaMaxPlayers);
        strcat(string, temp, sizeof(string));
    }

    ShowPlayerDialog(playerid, DIALOG_ARENAS, DIALOG_STYLE_TABLIST_HEADERS, "Arenas Deadmatch", string, "Selecionar", "Cancelar");
    return 1;
}

CountPlayersInArena(arenaID) {
    new count = 0;
    for (new i = 0; i < MAX_PLAYERS; i++) {
        if (IsPlayerConnected(i) && g_PlayerArena[i] == arenaID) {
            count++;
        }
    }
    return count;
}

InitializeArenas() {
    // Area 51
    g_Arenas[0][x] = 177.1232;
    g_Arenas[0][y] = 2010.7736;
    g_Arenas[0][z] = 18.0724;
    g_Arenas[0][rotation] = 90.0;
    g_Arenas[0][virtualWorld] = 0;
    g_Arenas[0][interior] = 0;
    g_Arenas[0][maxPlayers] = 10; 
    strcopy(g_Arenas[0][name], "Area 51"); 
    strcopy(g_Arenas[0][atalho], "/a51");
    g_Arenas[0][weaponList][0] = 24; 
    g_Arenas[0][weaponList][1] = 31; 
    g_Arenas[0][weaponList][2] = 34;
}

ResetPlayerData(playerid) {
    static const playerdefault[ArenaData];
    g_Arenas[playerid] = playerdefault;
}

GetPlayerNameEx(playerid) {
	new PlayerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, PlayerName, sizeof(PlayerName));
	return PlayerName;
}