// Basert på og utvidet fra testkode fra https://arduinomodules.info/ky-035-analog-hall-magnetic-sensor-module/

#define VERDIER 15      // Mengden verdier løpendeVerdier bruker

int sensorPin = A0;          // Pinnen magnetsensoren er kobla til (analog)
int verdi;                   // Verdien fra magnetometeret
int løpendeVerdier[VERDIER]; // Løpende liste med de {VERDIER} siste verdiene for gjennomsnitt

void setup() {
  pinMode(A0, INPUT);   // Setter A0 til å lese input med pinMode
  Serial.begin(9600);   // Starter Serial

  // Fyller løpendeVerdier med 0 til å starte med
  for (int i = 0; i < VERDIER; i++)
    løpendeVerdier[i] = 0;
}

void loop() {
  verdi = analogRead(sensorPin);  // Leser sensorverdi
  leggtil(verdi);                 // Legger til verdien i løpendeVerdier
  Serial.println(snitt());        // Skriver ut gjennomsnittet til Serial
  //Serial.println(verdi);          // Skriver sensorverdi rett til Serial

  delay(100); // Gjør en måling per 100 ms
}

void leggtil(int tall) {
  // Legger til et tall i løpendeVerdier ved å flytte alle verdiene 1 bak
  // og legge til parameteren tall på slutten
  // Sletter den første verdien
  for (int i = 1; i < VERDIER; i++)
    løpendeVerdier[i-1] = løpendeVerdier[i];
  løpendeVerdier[VERDIER-1] = tall;
}

int snitt() {
  // Summerer løpendeVerdier og deler på {VERDIER} (og floorer/truncer) for gjennomsnitt
  int total = 0;
  for (int i = 0; i < VERDIER; i++)
    total += løpendeVerdier[i];
  return (int) total / VERDIER; // (int) konverterer fra float til int, truncer sånn at desimaldelen er borte
}
