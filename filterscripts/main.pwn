/* 
 * Copyright 2025 iagopandrade
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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