#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Definindo endereço MAC
IPAddress ip(192, 168, 1, 211);                    // Definindo endereço IP da rede
IPAddress myDns(8, 8, 8, 8);                       // Definindo DNS usado.
EthernetClient client;
char server[] = "apiarduinowebcontrol.herokuapp.com"; // servidor da API
unsigned long lastConnectionTime = 0;                 // time da ultima conexão
const unsigned long postingInterval = 5;              // intervalo entre requisições

void setup()
{
  // Definindo as portas das leds
  pinMode(22, OUTPUT); // ligh_1
  pinMode(24, OUTPUT); // ligh_2
  pinMode(25, OUTPUT); // ligh_3
  pinMode(26, OUTPUT); // ligh_4
  pinMode(27, OUTPUT); // ligh_5
  pinMode(28, OUTPUT); // ligh_6
  pinMode(29, OUTPUT); // ligh_7
  pinMode(31, OUTPUT); // ligh_8
  pinMode(32, OUTPUT); // ligh_9
  pinMode(33, OUTPUT); // ligh_10

  Serial.begin(9600);

  // Verificar se a configuração do shield está ok
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Falha na configuração da Ethernet usando DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
      Serial.println("Ethernet shield não está conectado");
      while (true)
      {
        delay(1);
      }
    }
    // Verificar se o cabo está conectado.
    if (Ethernet.linkStatus() == LinkOFF)
    {
      Serial.println("Cabo de Ethernet não está conectado.");
    }

    Ethernet.begin(mac, ip, myDns);

    // Retornar o endereço ip local
    Serial.print("Meu endereço IP: ");
    Serial.println(Ethernet.localIP());
  }
  else
  {

    Serial.print("  DHCP atribuído IP ");
    Serial.println(Ethernet.localIP());
  }

  delay(100);
}

void loop()
{
  //Verificar se a conexão está ok
  if (client.available())
  {
    char c = client.read();
    Serial.write(c);
    //retornar pag
  }
  if (millis() - lastConnectionTime > postingInterval)
  {
    extern httpRequest();
  }
}
