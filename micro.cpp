#include <WiFi.h> // Pour ESP32 (ou utilisez <ESP8266WiFi.h> pour ESP8266)
// Configuration Wi-Fi
const char* ssid = "Votre_SSID";          // Nom de votre réseau Wi-Fi
const char* password = "Votre_MotDePasse"; // Mot de passe Wi-Fi
// Pin du relais (connectée à une broche numérique du microcontrôleur)
const int relayPin = 5; // Utilisez une broche disponible (par ex., GPIO 5 sur ESP32)
// Initialisation de l'état du relais
bool relayState = false;
// Configuration du serveur
WiFiServer server(80); // Port 80 pour le serveur HTTP
void setup() {
  // Configuration du relais en sortie
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Éteindre le relais par défaut
  // Initialisation de la connexion Wi-Fi
  Serial.begin(115200);
  Serial.print("Connexion à ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  // Attente de la connexion Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");}
  Serial.println("\nWi-Fi connecté.");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
  // Démarrer le serveur
  server.begin();}
void loop() {
  // Vérifier si un client se connecte
  WiFiClient client = server.available();
  if (!client) {
    return;}
  Serial.println("Nouveau client connecté.");
  String request = client.readStringUntil('\r'); // Lire la requête HTTP
  Serial.println(request);
  client.flush();
  // Analyser la commande (état = 1 ou 0 dans l'URL)
  if (request.indexOf("/switch?state=1") != -1) {
    relayState = true; // Allumer le relais
    digitalWrite(relayPin, HIGH);
  } else if (request.indexOf("/switch?state=0") != -1) {
    relayState = false; // Éteindre le relais
    digitalWrite(relayPin, LOW);}
  // Réponse au client HTTP
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.println(relayState ? "Relais allumé" : "Relais éteint");
  delay(1);
  Serial.println("Client déconnecté.");}
