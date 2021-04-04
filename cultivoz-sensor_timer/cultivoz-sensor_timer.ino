#include <TimeLib.h>

#define LIGADO 1
#define DESLIGADO 0
#define RELEVASOGRANDE 7             // indica que conectaremos o pino do relê na porta digital 7
#define RELEVASOMEDIO 6             // indica que conectaremos o pino do relê na porta digital 6
#define RELEVASOPEQUENO 5          // indica que conectaremos o pino do relê na porta digital 5
#define SENSORSOLOGRANDE A0       // indica que conectaremos o pino do sensor de umidade na porta analógica A0
#define SENSORSOLOMEDIO A1       // indica que conectaremos o pino do sensor de umidade na porta analógica A1
#define MUITOSECO 0,25
#define UMIDO 50,75
#define MUITOUMIDO 75,100
int const SECO = 581;
int const MOLHADO = 277;

int IntervaloVasoPequeno = 10; // variável que indica, em segundos, o intervalo desejado para a torneira do vaso pequeno
time_t TimerVasoPequeno;      // variável tipo time_t que marca o tempo p/ a rega do vaso pequeno 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variável para definirmos o valor máximo molhado.       ESSE TRECHO AINDA PRECISA SER TRABALHADO                       ///
// Para verificar o seu valor, digite após o símbolo "=" o valor máximo quando o sensor estiver dentro do vaso ou água. ///
int valorUmidadeSoloGrande = 430; // vou calibrar ainda                                                                ///
int valorUmidadeSoloMedio = 69; // alteração de teste para funcionar já parametrizando um valor em %                  ///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Digite aqui o valor máximo quando o sensor estiver dentro do vaso ou água.
int valorMaximoMolhado = 430;

// A função setup é executada uma vez só
void setup() {

  pinMode(RELEVASOGRANDE, OUTPUT);        // Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(SENSORSOLOGRANDE, INPUT);      // Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.
 
  pinMode(RELEVASOMEDIO, OUTPUT);      // Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(SENSORSOLOMEDIO, INPUT);    // Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.

  pinMode(RELEVASOPEQUENO, OUTPUT); // Define o pino do relê como saída, pois iremos enviar um comando pra ele.
 
  digitalWrite(RELEVASOPEQUENO,DESLIGADO); // Define que o sistema inicia com o a torneira do vaso pequeno deligada - altere para LIGADO se quiser o contrário

  TimerVasoPequeno = now();  // inicia timer do vaso pequeno em 0s
  Serial.begin(9600);
}

// A função loop fica sendo executada de maneira contínua
void loop() {

  // leitura do sensor solo grande
 //  lerSensorSolo(SensorSoloGrande, valorUmidadeSoloGrande, ReleVasoGrande);


     Serial.println(lerSensorSolo(SENSORSOLOMEDIO));
     Serial.println(analogRead(SENSORSOLOMEDIO));

  // checagem do sensor vaso médio em relação ao nível de umidade desejado e acionamento do relé em função disso
 //  digitalWrite(RELEVASOMEDIO,checkSensor(SENSORSOLOMEDIO, valorUmidadeSoloMedio));
     digitalWrite(RELEVASOMEDIO,!(checkSensorRange(SENSORSOLOMEDIO, MUITOUMIDO)));

  if (now() == (TimerVasoPequeno+IntervaloVasoPequeno)) { 
     digitalWrite(RELEVASOPEQUENO,!(digitalRead(RELEVASOPEQUENO)));
     TimerVasoPequeno = now();
  }
}

int lerSensorSolo(int parametroSensorSolo) {
    return map(analogRead(parametroSensorSolo),SECO,MOLHADO,0,100);  
}
 
boolean checkSensor(int parametroSensorSolo, int parametroValorUmidade){ // checa se o sensor escolhido apresenta um indice de umidade menor que o valor definido em %
    return (lerSensorSolo(parametroSensorSolo) <= parametroValorUmidade);
}

boolean checkSensorRange(int parametroSensorSolo, int min, int max){ // checa se o sensor escolhido apresenta um indice de umidade definido em um intervalo
    int valorSensorSolo = lerSensorSolo(parametroSensorSolo); 
    return (valorSensorSolo >= min && valorSensorSolo <= max);
}
