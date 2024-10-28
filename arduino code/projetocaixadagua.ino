#include <max6675.h>

// Definindo os pinos do sensor de ultrassom
const int trigPin = 9;
const int echoPin = 10;

// Definindo os pinos do sensor de temperatura MAX6675
const int thermoDO = 2;
const int thermoCS = 3;
const int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(500);
}

void loop() {
  // Medir a distância
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2.0) / 29.1;

  // Medir a temperatura
  double temperature = thermocouple.readCelsius();
  
  // Definir a pureza como 0
  double pureza = 0;

  // Enviar dados via Serial em formato JSON
  Serial.print("{\"distancia\":");
  Serial.print(distance);
  Serial.print(", \"temperatura\":");
  Serial.print(temperature);
  Serial.print(", \"pureza\":");
  Serial.print(pureza);
  Serial.println("}");

  // Esperar 1 minuto (60000 milissegundos) antes da próxima leitura
  delay(60000);
}
