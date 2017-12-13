#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "wifi.drjslab.org"; // SSID i.e. Service Set Identifier is the name of your WIFI
const char* password = "godsavecommander"; // Your Wifi password, in case you have open network comment the whole statement.
 
int r1=16;
int r2=5;
int r3=4;
int r4=0;// GPIO5 or for NodeMCU you can directly write D1
WiFiServer server(80); // Creates a server that listens for incoming connections on the specified port, here in this case port is 80.
HTTPClient http;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);

  
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP()); //Gets the WiFi shield's IP address and Print the IP address of serial monitor
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<br><br>");
  client.println("<h1>First Board Wifi</h1><br>");
  
  // Match the request



client.println("<table>");

client.println("<tr>");
client.println("<td>");
client.println("Switch No: 1");
client.println("</td>");
client.println("<td>");


client.println("<a href=\"/LED=1\"\"><button>Switch One</button></a><br />"); 
if (request.indexOf("/LED=1") != -1)  {
    int status_set = 1-digitalRead(r1);
    digitalWrite(r1, status_set);
  }
 


client.println("</td>");
client.println("</tr>");
client.println("<tr>");
client.println("<td>");
client.println("Switch No: 2");
client.println("</td>");
client.println("<td>");

client.println("<a href=\"/LED=2\"\"><button>Switch Two</button></a><br />"); 
if (request.indexOf("/LED=2") != -1)  {
    int status_set = 1-digitalRead(r2);
    digitalWrite(r2, status_set);
  }


client.println("</td>");
client.println("</tr>");


client.println("<tr>");
client.println("<td>");
client.println("Switch No: 3");
client.println("</td>");
client.println("<td>");

client.println("<a href=\"/LED=3\"\"><button>Switch Three</button></a><br />"); 
if (request.indexOf("/LED=3") != -1)  {
    int status_set = 1-digitalRead(r3);
    digitalWrite(r3, status_set);
  }
  
client.println("</td>");
client.println("</tr>");

client.println("<tr>");
client.println("<td>");
client.println("Switch No: 4");
client.println("</td>");
client.println("<td>");


client.println("<a href=\"/LED=4\"\"><button>Switch Four</button></a><br />"); 
if (request.indexOf("/LED=4") != -1)  {
    int status_set = 1-digitalRead(r4);
    digitalWrite(r4, status_set);
  }

client.println("</td>");
client.println("</tr>");

client.println("</table>");
  
  client.println("</html>");


  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
