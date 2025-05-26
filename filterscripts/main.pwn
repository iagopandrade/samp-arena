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

#define FILTERSCRIPT

#include <open.mp>

#include "arena"

main() {
    print("| Filterscript de arena | open.mp | 2025 -");
	print("| -----------------------------------");
	print("| Autor: iagopandrade");
	print("| -----------------------------------");
	print("| Compilado: 25/05/2025 às 23:15:00");
    print("| Repositório: https://github.com/iagopandrade/arena-samp");
}

public OnFilterScriptInit() {
    print("[Sistema de arenas] Filterscript carregado.");

    InitializeArenas();
    print("Arenas carregadas.");
    return 1;
}

public OnFilterScriptExit() {
    print("[Sistema de arenas] Filterscript descarregado.");
    return 1;
}

public OnPlayerConnect(playerid) {
	g_PlayerArena[playerid] = -1;
	return 1;
}

public OnPlayerDisconnect(playerid, reason) {
	ResetPlayerData(playerid);
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[]) {
    if (strcmp(cmdtext, "/a51", true) == 0) {
        SetPlayerArena(playerid, 0);
        return 1;
    }
    
    if (strcmp(cmdtext, "/arenas", true) == 0) {
        ShowArenaInfoDialog(playerid);
        return 1;
    }

    if (strcmp(cmdtext, "/sairarena", true) == 0) {
        if (g_PlayerArena[playerid] == -1) {
            SendClientMessage(playerid, -1, "Voce nao esta em nenhuma arena para sair.");
            return 1;
        }
        new arenaID = g_PlayerArena[playerid];
        RemovePlayerFromArena(playerid, arenaID);
        return 1;
    }
    return 0;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
    if (dialogid == DIALOG_ARENAS) {
        if (response) {
            switch(listitem) {
                case 0: SetPlayerArena(playerid, 0);
            }
        }
        return 1;
    }
    return 0;
}