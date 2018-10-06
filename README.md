# autoino
Automação residencial com Arduino

Comecei este no em setembro de 2018 com intuito de automatizar meu apartamento com o menor custo possível e a maior modularidade possível.

Eram necessidades primárias:
- funcionar com app "Home" do iPhone
- interruptores da parede deveriam continuar onde está e funcionando igualmente
- os circuitos devem funcionar SEM a automação instalada, com o mínimo esforço

Com esses pontos colocados, parti para "mãos-a-obra".

(ATENÇÃO: CORRENTE ELÉTRICA MATA)

## Layout básico

Um circuito para acender uma lâmpada no teto parte do seguinte esquema:

   FASE (parede) - INTERRUPTOR (parede) - RETORNO (parede para teto) - LÂMPADA (teto) - NEUTRO (teto)

Para inserir um relé neste circuito, e este acender e apagar a lâmpada juntamente com o interruptor, deve-se utilizar um "circuito paralelo":

   FASE (parede) - INTERRUPTOR PARALELO (parede) = RETORNO PARALELO (parede para relé) = RELÉ (para o teto) - LÂMPADA (teto) - neutro (teto)

Assim tanto o interruptor da parede e o relé podem acender ou apagar a lâmpada, em qualquer ordem.

### Sensor de tensão

Não se sabe qual posição do relé se liga a lâmpada: pode ser no NO ou no NC. Depende da posição do interruptor paralelo, o que é desconhecido. Se deve então inserir no circuito um "sensor de tensão": ele indicará se a lâmpada está acesa ou apagada.

### Dimerizando

Tenho dois circuitos com lâmpadas incandecentes que podem ser "dimerizadas" (variar a intensidade). Claro que quero dimerizar em um esquema automatizado.

Não dá pra "dimerizar em paralelo", pois mesmo com uso de um potenciômetro comum ele não reflete a posição do "potenciômetro virtual" da automação. Pode-se usar um Encoder, mas ele vai alterar o "potenciômetro virtual" na automação.

Ao dimerizar um circuito, perde-se a "independência" desse circuito. Paciência.

(a ser continuado)
