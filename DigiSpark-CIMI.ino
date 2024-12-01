#include <DigiKeyboard.h>

// -=== Definição de constantes 
#define SHORT_DELAY 50  // -= Atrazo pequeno (0.05s)
#define MEDIUM_DELAY 100  // -= Atrazo Medio (0.1s)
#define LONG_DELAY 500  // -= Atrazo Longo (0.5s)
#define VERY_LONG_DELAY 1000  // -= Atrazo Longo (1s)

// -==== Função Liga led mantem Ligado 
void initializeLED() {
  pinMode(1, OUTPUT);  // -= Pino 1 (LED interno) Saida
  digitalWrite(1, HIGH);  // -= Deixa o led ligado 
}

// -===== Função pra tratar erros: o LED pisca, mas fica ligado depois
void handleError() {
  for (int i = 0; i < 2; i++) {  // -= Pisca o LED 2 vezes
    digitalWrite(1, LOW);  // -= Apaga o LED
    delay(200);  // -= Atrazo de 200ms
    digitalWrite(1, HIGH);  // -= Acende o LED
    delay(200);  // -= Atrazo de 200ms
  }
}

// -===== Função de atraso segura pra usar com DigiKeyboard
void safeDelay(unsigned int ms) {
  unsigned long start = millis();  // -= Marca o tempo de inicio
  while (millis() - start < ms) {  // -= Continua até o tempo de atraso ser alcançado
    DigiKeyboard.update();  // -= Atualiza o estado do DigiKeyboard
    DigiKeyboard.delay(10);  // -= Atrazo pequeno pra evitar travamentos
  }
}

// Função simplificada e mais segura pra mandar comandos do teclado
bool safeSendKeyStroke(uint8_t keyStroke, uint8_t modifiers = 0) {
  for (uint8_t retry = 0; retry < 3; retry++) {  // -= Tenta até 3 vezes
    DigiKeyboard.sendKeyStroke(keyStroke, modifiers);  // -= Envia o comando do teclado
    safeDelay(MEDIUM_DELAY);  // -= Espera um pouco pra garantir que enviou

    // -= Se deu certo, retorna verdadeiro
    if (keyStroke != 0) return true;
  }

  // -= Se falhar todas as tentativas, chama a função de erro
  handleError();
  return false;
}

// Função segura pra imprimir texto
void safePrint(const char* text) {
  uint8_t len = strlen(text);  // -= Pega o tamanho do texto
  for (uint8_t i = 0; i < len; i++) {  // -= Vai letra por letra
    DigiKeyboard.print(text[i]);  // -= Imprime a letra
    safeDelay(SHORT_DELAY);  // -= Pequeno atrazo entre as letras
  }
}

// Função pra imprimir o texto direto, sem atraso
void Command(const char* text) {
  DigiKeyboard.print(text);  // -= Imprime o texto direto
}

void setup() {
  // -= Liga o LED pra ficar aceso
  initializeLED();

  // -= Desabilita interrupções pra evitar problemas
  cli();

  // -= Configura o DigiKeyboard
  DigiKeyboard.update();
  safeDelay(LONG_DELAY);  // -= Espera o tempo necessário pra inicializar
  safeSendKeyStroke(0);  // -= Envia um comando vazio

  // -= Abre a janela "Executar"
  safeSendKeyStroke(KEY_R, MOD_GUI_LEFT);  // -= Pressiona "Win + R"
  safeDelay(MEDIUM_DELAY);

  // -= Abre o CMD
  safePrint("cmd");  // -= Digita "cmd"
  safeDelay(MEDIUM_DELAY);
  safeSendKeyStroke(KEY_ENTER, MOD_CONTROL_LEFT | MOD_SHIFT_LEFT);  // -= "Ctrl + Shift + Enter" pra abrir como admin

  // -= Espera o CMD abrir
  safeDelay(VERY_LONG_DELAY);  // -= Espera até o CMD abrir
  safeSendKeyStroke(KEY_LEFT_ARROW);  // -= Pressiona a tecla de tabulação pra mudar foco
  safeDelay(MEDIUM_DELAY);
  safeSendKeyStroke(KEY_ENTER);  // -= Aperta Enter pra confirmar

  // -= Executa o comando
  safeDelay(LONG_DELAY);
  Command("echo Hello World!");  // -= Envia comando pra mostrar "Hello World!"
  safeDelay(SHORT_DELAY);
  safeSendKeyStroke(KEY_ENTER);  // -= Executa o comando no CMD

  // -= Gerencia a janela
  safeDelay(MEDIUM_DELAY);
  safeSendKeyStroke(KEY_SPACE, MOD_ALT_LEFT);  // -= Pressiona "Alt + Espaço"
  safeDelay(SHORT_DELAY);
  safeSendKeyStroke(KEY_N);  // -= Minimiza a janela

  // -= Reabilita interrupções
  sei();

  // -= Desliga o LED apos finalizar as operações
  digitalWrite(1, LOW);  // -= Apaga o LED
}

void loop() {
  // -= Evita travamentos do sistema
  DigiKeyboard.update();
}
