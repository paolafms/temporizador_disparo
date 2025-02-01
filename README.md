# Sistema de Temporização para Acionamento de LEDs com Raspberry Pi Pico W:
- Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando um Raspberry Pi Pico W. O sistema é controlado por um botão (pushbutton) e utiliza a função add_alarm_in_ms() da Pico SDK para gerenciar os atrasos entre os estados dos LEDs.

# Requisitos de Hardware:
- Microcontrolador: Raspberry Pi Pico W.
- LEDs: 03 LEDs (azul, vermelho e verde).
- Resistores: 03 resistores de 330 Ω.
- Botão: 01 botão (pushbutton).
.
# Conexões:
LED Verde: GPIO 11.
LED Azul: GPIO 12.
LED Vermelho: GPIO 13.
Botão A: GPIO 5.

# Funcionalidades:
Acionamento dos LEDs:
- Quando o botão é pressionado, todos os três LEDs são ligados (nível alto).
- Após 3 segundos, dois LEDs são desligados, deixando apenas dois LEDs acesos.
- Após mais 3 segundos, outro LED é desligado, deixando apenas um LED aceso.
- Após mais 3 segundos, o último LED é desligado.
- O botão só pode alterar o estado dos LEDs quando o último LED for desligado.

# Temporização:
- O temporizador é ajustado para um atraso de 3 segundos (3000ms) entre as mudanças de estado dos LEDs.

# Debounce do Botão:
- O código implementa uma rotina de debounce em software para evitar leituras múltiplas causadas pelo efeito bouncing do botão.
