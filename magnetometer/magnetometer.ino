// Basert på og kraftig utvidet fra testkode fra https://arduinomodules.info/ky-035-analog-hall-magnetic-sensor-module/
// 

#define VERDIER  15     // Mengden verdier løpendeVerdier bruker
#define BASELINE 525    // Verdien magnetometeret oppgir uten magneter
#define TIMEOUT  500    // Tiden i millisekunder en verdi må holdes for å fastsettes

#define NIVAA1 100      // Threashold for å rapportere 1 (avstand fra baseline)
#define NIVAA2 200      // Threashold for 2
#define DELAY  100      // Delay mellom hver loop

int sensorPin = A0;          // Pinnen magnetsensoren er kobla til (analog)
int verdi;                   // Verdien fra magnetometeret
int lopendeVerdier[VERDIER]; // Løpende liste med de {VERDIER} siste verdiene for å regne gjennomsnitt
int tid;             // Tiden den har rapportert en verdi (må bli over TIMEOUT)
int rapportertverdi; // Verdien den nærmer seg nå

void setup() {
  pinMode(A0, INPUT);   // Setter A0 til å lese input med pinMode
  Serial.begin(9600);   // Starter Serial

  tid = 0;
  rapportertverdi = 0;

  // Fyller løpendeVerdier med 0 til å starte med
  for (int i = 0; i < VERDIER; i++)
    lopendeVerdier[i] = 0;
}

void loop() {
  verdi = analogRead(sensorPin);  // Leser sensorverdi
  leggtil(verdi);                 // Legger til verdien i løpendeVerdier
  //Serial.println(snitt());        // Skriver ut gjennomsnittet til Serial
  //Serial.println(verdi);          // Skriver sensorverdi rett til Serial


  if (snitt >= BASELINE + NIVAA1 and snitt < BASELINE + NIVAA2) {
    if (rapportertverdi != 1)
      tid = 0;
    rapportertverdi = 1;
  }
  else if (snitt >= BASELINE + NIVAA2) {
    if (rapportertverdi != 2)
      tid = 0;
    rapportertverdi = 2;
  }
  else if (snitt <= BASELINE - NIVAA1 and snitt > BASELINE - NIVAA2) {
    if (rapportertverdi != -1)
      tid = 0;
    rapportertverdi = -1;
  }
  else if (snitt <= BASELINE - NIVAA2) {
    if (rapportertverdi != -2)
      tid = 0;
    rapportertverdi = -2;
  }
  else {
    rapportertverdi = 0;
    tid = 0;
  }
  tid += DELAY;

  // Sensoren har bestemt en verdi!
  if (tid >= TIMEOUT) {
    Serial.print("SENSOREN HAR BESTEMT SEG: ");
    Serial.println(rapportertverdi);
  }

  delay(DELAY); // Gjør en måling per {DELAY} ms
}

void leggtil(int tall) {
  // Legger til et tall i løpendeVerdier ved å flytte alle verdiene 1 bak
  // og legge til parameteren tall på slutten
  // Sletter den første verdien
  for (int i = 1; i < VERDIER; i++)
    lopendeVerdier[i-1] = lopendeVerdier[i];
  lopendeVerdier[VERDIER-1] = tall;
}

int snitt() {
  // Summerer løpendeVerdier og deler på {VERDIER} (og konverterer til int) for gjennomsnitt
  int total = 0;
  for (int i = 0; i < VERDIER; i++)
    total += lopendeVerdier[i];
  return (int) total / VERDIER; // (int) konverterer fra float til int
}
