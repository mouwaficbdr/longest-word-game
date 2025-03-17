#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

// Fonction pour initialiser Winsock
void init_winsock() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Erreur Winsock\n");
        exit(EXIT_FAILURE);
    }
}

// Fonction pour démarrer le client
void start_client(const char* server_ip, int port) {
    SOCKET client_socket;
    struct sockaddr_in server_addr;

    // Création du socket client
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Erreur socket\n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);  // IP du serveur (localhost ici)
    server_addr.sin_port = htons(port);

    // Connexion au serveur
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Erreur connexion : %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    printf("Connecté au serveur sur le port %d\n", port);

    // Envoi d'un message au serveur
    const char* message = "Hello, serveur!";
    if (send(client_socket, message, strlen(message), 0) == SOCKET_ERROR) {
        printf("Erreur envoi : %d\n", WSAGetLastError());
    }

    // Fermeture du socket client
    closesocket(client_socket);
    WSACleanup();
}

int main() {
    // Initialisation de Winsock
    init_winsock();

    // L'adresse IP du serveur (localhost pour test sur la même machine)
    const char* server_ip = "127.0.0.1";

    // Port du serveur (celui trouvé par la fonction find_free_port)
    int port = 5000;  // Remplace cette valeur par celle renvoyée par find_free_port()

    // Démarrage du client
    start_client(server_ip, port);

    return 0;
}
