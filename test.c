#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT_START 5000  // Port de départ
#define PORT_END 10000   // Plage de ports à tester

// Fonction pour trouver un port libre
int find_free_port() {
    WSADATA wsa;
    SOCKET temp_socket;
    struct sockaddr_in temp_addr;
    int port;

    // Initialisation de Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erreur Winsock\n");
        return -1;
    }

    // Création d'un socket temporaire
    temp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (temp_socket == INVALID_SOCKET) {
        printf("Erreur socket\n");
        WSACleanup();
        return -1;
    }

    // Test des ports
    for (port = PORT_START; port <= PORT_END; port++) {
        temp_addr.sin_family = AF_INET;
        temp_addr.sin_addr.s_addr = INADDR_ANY;
        temp_addr.sin_port = htons(port);

        // Tester si le port est libre
        if (bind(temp_socket, (struct sockaddr*)&temp_addr, sizeof(temp_addr)) == 0) {
            // Si bind réussi, le port est libre
            closesocket(temp_socket);
            WSACleanup();
            return port;  // Port disponible trouvé
        }
    }

    // Aucun port libre
    closesocket(temp_socket);
    WSACleanup();
    return -1;
}

// Fonction de démarrage du serveur
void start_server() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);
    int port;

    // Initialisation Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erreur Winsock\n");
        exit(EXIT_FAILURE);
    }

    // Trouver un port libre
    port = find_free_port();
    if (port == -1) {
        printf("Aucun port libre trouvé\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    printf("Serveur démarrant sur le port : %d\n", port);

    // Création du socket serveur
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Erreur socket\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Écouter sur toutes les interfaces
    server_addr.sin_port = htons(port);

    // Liaison du socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erreur bind : %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Mise en écoute
    if (listen(server_socket, 5) == SOCKET_ERROR) {
        printf("Erreur listen : %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Serveur en attente de connexion...\n");

    // Accepter une connexion client
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_socket == INVALID_SOCKET) {
        printf("Erreur accept : %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Client connecté !\n");

    // Fermeture des sockets
    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
}

// Fonction principale
int main() {
    start_server();
    return 0;
}
