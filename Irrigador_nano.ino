// Definição dos pinos
const int sensorUmidadeAnalogico = A0;  // Pino analógico para o sensor de umidade (A0)
const int sensorUmidadeDigital = 8;     // Pino digital para o sensor de umidade (D0)
const int rele = 7;                     // Pino digital para o relé
int valorUmidade;                       // Variável para armazenar o valor da umidade
int limiteUmidade = 500;                // Limite de umidade para leitura analógica (ajustável)

// Variável de controle para escolher entre leitura analógica e digital
bool usarAnalogico = true;              // Se true, usa o sensor analógico; se false, usa o digital

void setup() {
  // Configuração dos pinos
  pinMode(sensorUmidadeDigital, INPUT);  // Pino do sensor digital (D0) como entrada
  pinMode(rele, OUTPUT);                 // Pino do relé como saída
  digitalWrite(rele, HIGH);              // Inicialmente desliga o relé (bomba de água)
  Serial.begin(9600);                    // Inicializa a comunicação serial para depuração
}

void loop() {
  if (usarAnalogico) {
    // Leitura do sensor de umidade (A0) - modo analógico
    valorUmidade = analogRead(sensorUmidadeAnalogico);
    Serial.print("Umidade do Solo (A0): ");
    Serial.println(valorUmidade);  // Exibe o valor lido

    // Verifica o nível de umidade no modo analógico
    if (valorUmidade < limiteUmidade) {
      // Se a umidade estiver abaixo do limite, liga a bomba
      digitalWrite(rele, LOW);   // Ativa o relé (liga a bomba de água)
      Serial.println("Solo seco - Irrigando...");
    } else {
      // Se a umidade estiver acima do limite, desliga a bomba
      digitalWrite(rele, HIGH);  // Desativa o relé (desliga a bomba de água)
      Serial.println("Solo úmido - Sem irrigação.");
    }
  } else {
    // Leitura do sensor de umidade (D0) - modo digital
    int estadoUmidade = digitalRead(sensorUmidadeDigital);

    if (estadoUmidade == LOW) {
      // Se o estado for LOW, o solo está seco
      digitalWrite(rele, LOW);   // Ativa o relé (liga a bomba de água)
      Serial.println("Solo seco - Irrigando...");
    } else {
      // Se o estado for HIGH, o solo está úmido
      digitalWrite(rele, HIGH);  // Desativa o relé (desliga a bomba de água)
      Serial.println("Solo úmido - Sem irrigação.");
    }
  }

  // Aguarda 1 segundo antes da próxima leitura
  delay(1000);
}
