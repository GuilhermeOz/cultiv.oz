int ReleVasoGrande = 7;         //variável que indica que conectamos o pino do relê na porta digital 7
int ReleVasoMedio = 6;         //variável que indica que conectamos o pino do relê na porta digital 6
int ReleVasoPequeno = 5;         //variável que indica que conectamos o pino do relê na porta digital 5
int SensorSoloGrande = A0;  //variável que indica que conectamos o pino do sensor de umidade na porta analógica A0
int SensorSoloMedio = A1;  //variável que indica que conectamos o pino do sensor de umidade na porta analógica A1

int contador = 0;

//Variável para definirmos o valor máximo molhado. 
//Para verificar o seu valor, digite após o símbolo "=" o valor máximo quando o sensor estiver dentro do vaso ou água.
int valorUmidadeSoloGrande = 430; //vou calibrar ainda
int valorUmidadeSoloMedio = 430; //vou calibrar ainda

  
//Digite aqui o valor máximo quando o sensor estiver dentro do vaso ou água.
int valorMaximoMolhado = 430;

// A função setup é executada uma vez só
void setup() {

  //inicia a leitura da porta Serial
  Serial.begin(9600);
  
  pinMode(ReleVasoGrande, OUTPUT);        //Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(SensorSoloGrande, INPUT);   //Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.
 
  pinMode(ReleVasoMedio, OUTPUT);        //Define o pino do relê como saída, pois iremos enviar um comando pra ele.
  pinMode(SensorSoloMedio, INPUT);   //Define o pino do sensor de umidade como entrada, pois iremos ler o resultado dele.

  pinMode(ReleVasoPequeno, OUTPUT);        //Define o pino do relê como saída, pois iremos enviar um comando pra ele.
 

}

// A função loop fica sendo executada de maneira contínua
void loop() {

  // espera 10 segundos e liga torneira
  delay(10000);
  ligarTorneira(ReleVasoPequeno);

 // espera 10 segundos e desliga a torneira
  delay(10000);
  desligarTorneira(ReleVasoPequeno);

  //leitura do sensor solo grande
  lerSensorSolo(SensorSoloGrande, valorUmidadeSoloGrande, ReleVasoGrande);

  //leitura do sensor solo médio
  lerSensorSolo(SensorSoloMedio, valorUmidadeSoloMedio, ReleVasoMedio);

  if (contador == 60){
    ligarTorneira(ReleVasoPequeno);
  }

  //aguarda 60 segundos
  delay (60000);

  contador = contador + 1;    

}

void lerSensorSolo(int parametroSensorSolo, int parametroValorUmidade, int parametroRele){

  int valorSensorSolo;
 
  valorSensorSolo = analogRead(parametroSensorSolo);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.println("valor Sensor solo: ");
  Serial.println(valorSensorSolo);
  Serial.println("");  

  //se a leitura do solo for maior que o valor máximo molhado (450), significa que está seco
  if (valorSensorSolo > parametroValorUmidade){
    //ligar relê da torneira
    ligarTorneira(parametroRele);

    Serial.println("seco, ligar torneira");
    Serial.println("");  
  }
  //se a leitura do solo for menor que o valor máximo molhado (350), significa que está molhado
  else if (valorSensorSolo < parametroValorUmidade){
    //desligar relê da torneira
    desligarTorneira(parametroRele);

    Serial.println("molhado, desligar torneira");
    Serial.println("");  
  }
}

void ligarTorneira(int parametroReleTorneira){

  digitalWrite(parametroReleTorneira, HIGH);
  delay (4000);
  
}

void desligarTorneira(int parametroReleTorneira){

  digitalWrite(parametroReleTorneira, LOW);
    
}
