# Trabalho 3 de Computação Gráfica
### Leonardo Militz
# LM - Bike Dude
Um programa para visualizar um stickman pedalando em uma bicicleta. O cenário é gerado de forma aleatória e se move com parallax.

## Instruções de Uso
- Tecla **1** do teclado para visualizar os cálculos utilizados.
- Setas direcionais esquerda e direita do teclado para diminuir e aumentar a velocidade da bicicleta.

## Desenho
Foi atualizado no canvas 2D as funções de desenho para que possa ser selecionada a grossura das linhas com glLineWidth. Todas as partes do stickman, bicicleta e cenário foram desenhadas de forma organizada em classes separadas.

### Stickman
- Utilizada uma curva de Bézier para desenhar as costas do stickman.
- As pernas são conectadas de forma matemáticamente correta com os pedais da bicicleta, fazendo o tamanho da perna como um todo sempre ser fixo; para tal, foi utilizado intersecção de circulos para calcular a posição dos joelhos. 

### Bicicleta
- Os raios da bicicleta rotacionam constantemente.
- Desenhada de forma que se pareça o máximo com uma bicicleta real.
- Os pedais rotacionam constantemente.

### Cenário
- Montanhas desenhadas utilizando Curvas de bézier; os seus pontos são posicionados de forma aleatória, para que as montanhas sempre apareçam de forma diferente.
- Prédios desenhados com largura, altura, cor, números de janelas e espaçamentos aleatórios. 
- Grama desenhada com largura, altura e cor aleatória. Existe uma chance de 20% de uma grama aparecer "crescida" ao spawnar, tornando o cenário mais rico.
- Céu desenhado utilizando degradê de azul claro para branco.
- Foi utilizado parallax para dar uma sensação de distância entre o chão, prédios e as montanhas.

### Velocidade de Movimento dos Componentes
Todas as velocidades do programa escalam com o FPS do programa, fazendo que a velocidade seja constante independentemente de qual máquina rodar. O FPS máximo tem cap no refresh rate da tela do usuário.W

## Interação com o Usuário e UI
###  UI
- Usa-se uma tooltip com propriedade hover para mostras as instruções para o usuário.
- Há um FPS counter no canto inferior esquerdo da tela.

### Interação com o Usuário
- O usuário pode apertar as setas direcionais do teclado para aumentar e diminuir a velocidade da bicicleta.
- O usuário pode apertar a tecla "1" para que sejam mostradas as joints do stickman, os circulos do cálculo de intersecção, e os pontos que geram as Curvas de Bézier.

### Cenário Responsivo
Todos elementos gráficos são criados com base na largura e altura da tela, permitindo que qualquer resize não "estrague" o programa visualmente.