String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_CadenaCruda = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name='viewport' content='width=device-width, initial-scale=1.0'/>
<meta charset='utf-8'>
<style>
body {font-size:100%;}
#main {display: table; margin: auto; padding: 0 10px 0 10px; }
h2 {text-align:center; }
h1 {text-align:center; }
p { text-align:center; }
button {width: 100%; padding: 15px 32px; text-align: center; font-size:
16px;}
.azulEncendido {
background-color: blue;
color: white;
}
.azulApagado {
background-color: black;
color: red;
}
.amarilloEncendido {
background-color: yellow;
color: black;
}
.amarilloApagado {
background-color: red;
color: yellow;
}

table {
margin-left: auto;
margin-right: auto;
}
</style>
<script>
function ledAzul(val) {
window.location.href = '/LEDAzul='+val;
}
function ledAmarillo(val) {
window.location.href = '/LEDAmarillo='+val;
}
</script>
<title>Intensidad</title>
</head>
<body>
<div id='main'>
<h2>CONTROL DE LED MEDIANTE BOTONES</h2>
<table >
<tr>
<td><br></td>
</tr>
<tr>
<td><button class='amarilloEncendido'
onclick='ledAmarillo(true)'>ENCENDER AMARILLO</button></td>
<td><button class='amarilloApagado' onclick='ledAmarillo(false)'>APAGAR
AMARILLO</button></td>
</tr>
<table>
</div>
</body>
</html>
)=====";
#include "ESP8266WiFi.h"
const char* ssid="*****";
const char* password="*****";

#define DHTPIN4 4 //Led Amarillo
WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);
pinMode(DHTPIN4, OUTPUT); // Inicia LED amarillo apagado
digitalWrite(DHTPIN4, LOW);
// Conectar a la red Wi fi
Serial.println();
Serial.println();
Serial.print("Conectando a ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi conectada");
// Start the server
server.begin();
Serial.println("Servidor iniciado ");
// Print the IP address
Serial.print("Use esta URL : ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}

void loop() {
// Verifica si un cliente se ha conectado

WiFiClient client = server.available();
if (!client) {
return;
}
// Espera hasta que el cliente envíe algún dato
while(!client.available()){
delay(1);
}
// Lee la primera línea de respuesta
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
//int value = LOW;
if (request.indexOf("/LEDAmarillo=true") != -1) {
digitalWrite(DHTPIN4, HIGH); //Amarillo encendido
}
if (request.indexOf("/LEDAmarillo=false") != -1){
digitalWrite(DHTPIN4, LOW); //Amarillo apagado
}
client.flush();
client.print( header );
client.print( html_CadenaCruda );
client.print(" ");
delay(1);
}