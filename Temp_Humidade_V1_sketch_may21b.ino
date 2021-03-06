// Arduino - Sensor DHT - Umidade e Temperatura
// Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
 
#include <Adafruit_Sensor.h>                       // Biblioteca DHT Sensor Adafruit 
#include <DHT.h>
#include <DHT_U.h>
 
#define DHTTYPE DHT22                             // Sensor DHT22 ou AM2302
 
#define DHTPIN 2                                   // Pino do Arduino conectado no Sensor(Data) 
DHT_Unified dht(DHTPIN, DHTTYPE);                  // configurando o Sensor DHT - pino e tipo
uint32_t delayMS;                                  // variável para atraso no tempo

String temperatura = "";
String umidade = "";
 
void setup()
{
  Serial.begin(9600);                             // monitor serial 9600 bps
  dht.begin();                                    // inicializa a função
  
  Serial.println("Usando o Sensor DHT");
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);           // imprime os detalhes do Sensor de Temperatura
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println(" *C");
  Serial.println("------------------------------------");
 
  dht.humidity().getSensor(&sensor);            // imprime os detalhes do Sensor de Umidade
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Valor max:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Valor min:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolucao:   "); Serial.print(sensor.resolution); Serial.println("%");
  Serial.println("------------------------------------");
  //delayMS = sensor.min_delay / 1000;            // define o atraso entre as leituras

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
}
 
void loop()
{
  digitalWrite(13, LOW);                        // led apagado
  
  delay(9800);                                 //intervalo de 10 segundos entre cada medição
  sensors_event_t event;                        // inicializa o evento da Temperatura
  
  dht.temperature().getEvent(&event);           // faz a leitura da Temperatura
  if (isnan(event.temperature))                 // se algum erro na leitura
  {
    temperatura = "";                           //zera o valor da variável
    Serial.println("Erro na leitura da Temperatura!");
  }
  else                                         
  {
    temperatura = "Temperatura: " + (String)event.temperature + " *C";
  }
  dht.humidity().getEvent(&event);              // faz a leitura de umidade
  if (isnan(event.relative_humidity))           // se algum erro na leitura
  {
    umidade = "";                               //zera o valor da variável
    Serial.println("Erro na leitura da Umidade!");
  }
  else
  {
    umidade = "Umidade: " + (String)event.relative_humidity + " %";
  }

  if ((temperatura != "") && (umidade != ""))
  {
    Serial.println(temperatura + " - " + umidade);
  }
  
  digitalWrite(13, HIGH);                       // pisca o led para sinalizar uma coleta de temperatura e umidade
  delay(200);                                   // 200ms on
  
}
