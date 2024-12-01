# 🚀 DigiSpark CIMI (Command Injection Malware Install)
![1](LOGO.png)
Este script foi desenvolvido para ser executado em dispositivos baseados em DigiSpark, utilizando a biblioteca `DigiKeyboard` para enviar comandos diretamente ao sistema. A principal funcionalidade é automatizar a injeção de comandos via CMD no Windows, com a execução de scripts e gerenciamento de janelas do sistema.

## ⚙️ Como funciona:

- O script inicializa o dispositivo DigiSpark, configura um LED para indicar o status e, em seguida, executa uma série de comandos no terminal CMD.
- Ele abre o prompt de comando com permissões de administrador e executa um comando customizado (como `echo Hello World!`).
- Durante a execução, o LED pode ser usado para indicar erros ou o status da operação.

## ✍️ Como modificar o comando que ele dá no CMD:

Para alterar o comando que é enviado ao CMD, basta modificar a linha no código onde o comando é enviado:
```cpp
noSafePrint("echo Hello World!");  // Comando original
```
Troque `"echo Hello World!"` pelo comando desejado. Exemplo:
```cpp
noSafePrint("dir C:\\");  // Para listar os arquivos na raiz do C:
```

### 🔧 Exemplo de comandos:
- `echo Hello World!` - Exibe "Hello World!" no CMD.
- `dir C:\\` - Lista os arquivos e diretórios na raiz do disco C.
- `shutdown /s /f /t 0` - Desliga o computador imediatamente.

## 💡 Indicadores de Status do LED

- **Erro (Falha na execução):** O LED pisca 2 vezes para indicar que houve uma falha ao enviar o comando.
- **Início de execução:** O LED permanece aceso enquanto o script está sendo executado.
- **Finalização:** O LED é apagado quando o script termina a execução.

### Tabela de indicadores:

| Indicador     | Ação                                       | Significado                  |
| ------------- | ------------------------------------------ | ---------------------------- |
| 🟢 LED aceso  | `digitalWrite(1, HIGH)`                    | Processo iniciado            |
| 🔴 LED piscando | `handleError()`                            | Erro detectado (falha no comando) |
| ⚪ LED apagado | `digitalWrite(1, LOW)`                     | Processo finalizado          |

## 🔄 Como modificar a execução

1. **Comandos**: Mude o comando a ser executado diretamente no código onde está sendo chamado `noSafePrint()`.
2. **Atrasos**: Ajuste os atrasos para garantir que os comandos sejam enviados corretamente. O código utiliza diferentes constantes para isso:
   - `SHORT_DELAY` - Atrazo pequeno (50ms)
   - `MEDIUM_DELAY` - Atrazo médio (100ms)
   - `LONG_DELAY` - Atrazo longo (500ms)
   - `VERY_LONG_DELAY` - Atrazo muito longo (1000ms)

## 🛠️ Dependências

- [DigiKeyboard](https://github.com/micronucleus/digispark) - Biblioteca necessária para interação com o teclado.

## 📞 Contato

- Telegram: [@lalaio1](https://t.me/lalaio1)
- GitHub: [lalaio1](https://github.com/lalaio1)
- IDE: [Arduino IDE](https://docs.arduino.cc/software/ide/)

---

👨‍💻 **Desenvolvedor**: lalaio1 | 2024
```
