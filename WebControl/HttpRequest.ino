void httpRequest()
{
  // Conectar ao HTTP server
  EthernetClient client;
  client.setTimeout(10000); // definindo tempo limite

  // Se o cliente retornar algo diferente a conexão será falha
  if (!client.connect("apiarduinowebcontrol.herokuapp.com", 80))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  Serial.println(F("conectado!"));

  // enviando requisição Http
  client.println(F("GET /CRUD/alternative/arduino.php?arduinoid=1081723258&getLights=true HTTP/1.0"));
  client.println(F("Host: apiarduinowebcontrol.herokuapp.com"));
  client.println(F("Connection: close"));

  // Verificar se ouve alguma falha na requisição
  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    client.stop();
    return;
  }

  // checando o status do HTTP
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));

  /*
    Códigos de status de respostas HTTP

    Respostas de informação (100-199),
    Respostas de sucesso (200-299),
    Redirecionamentos (300-399)
    Erros do cliente (400-499)
    Erros do servidor (500-599).

  */

  // Deve ser "HTTP/1.0 200 OK" ou "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0)
  {
    Serial.print(F("Resposta inesperada: "));
    Serial.println(status);
    client.stop();
    return;
  }

  // Ignorar cabeçalhos HTTP
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Resposta inválida"));
    client.stop();
    return;
  }

  const size_t capacity = 2049;
  DynamicJsonDocument doc(capacity);

  // Analisar objeto JSON
  DeserializationError error = deserializeJson(doc, client);
  if (error)
  {
    Serial.print(F("deserializeJson() falhou: "));
    Serial.println(error.f_str());
    client.stop();
    return;
  }

  // extraindo valores

  // lighs
  Serial.println(F("Response:"));
  Serial.println(doc["light_1"].as<long>());
  Serial.println(doc["light_2"].as<long>());
  Serial.println(doc["light_3"].as<long>());
  Serial.println(doc["light_4"].as<long>());
  Serial.println(doc["light_5"].as<long>());
  Serial.println(doc["light_6"].as<long>());
  Serial.println(doc["light_7"].as<long>());
  Serial.println(doc["light_8"].as<long>());
  Serial.println(doc["light_9"].as<long>());
  Serial.println(doc["light_10"].as<long>());

  int light_1 = doc["light_1"];
  char *light_2 = doc["light_2"].as<long>();
  char *light_3 = doc["light_3"].as<long>();
  char *light_4 = doc["light_4"].as<long>();
  char *light_5 = doc["light_5"].as<long>();
  char *light_6 = doc["light_6"].as<long>();
  char *light_7 = doc["light_7"].as<long>();
  char *light_8 = doc["light_8"].as<long>();
  char *light_9 = doc["light_9"].as<long>();
  char *light_10 = doc["light_10"].as<long>();

  if (light_1 == 1)
  {
    digitalWrite(22, HIGH);
  }
  else
  {
    // DESLIGAR LAMPADA
    digitalWrite(22, LOW);
  }

  if (light_2 == 1)
  {
    digitalWrite(24, HIGH);
  }
  else
  {
    // DESLIGAR LAMPADA
    digitalWrite(24, LOW);
  }

  if (light_3 == 1)
  {
    digitalWrite(26, HIGH);
  }
  else
  {
    // DESLIGAR LAMPADA
    digitalWrite(26, LOW);
  }

  if (light_4 == 1)
  {
    digitalWrite(25, HIGH);
  }
  else
  {
    // DESLIGAR LAMPADA
    digitalWrite(25, LOW);
  }

  // Disconnect
  client.stop();
}
