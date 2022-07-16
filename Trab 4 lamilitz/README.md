# Trabalho 4 de Computação Gráfica
### Leonardo Militz
# LM - 3D Sweep Generator
Um programa que permite adicionar **N** pontos de controle para gerar uma curva de Bézier, 
em seguida, aplicar ao mesmo tempo um *rotational/transational sweep*  para gerar uma figura 3D. A técnica permite gerar figuras como taças, vasos, garrafas, molas, etc. 

## Instruções de Uso
### Teclado
- Setas para cima e para baixo para controlar a câmera verticalmente.
- Ao posicionar o mouse acima de um ponto de controle da curva, aperte D ou DEL para deletá-lo.

### Mouse
- Segure o botão esquerdo do mouse para rotacionar a figura, ou arrastar os pontos de controle da curva de Bézier.

### Botões / parâmetros
- **Projection Type**: Altera o tipo de projeção para *ortogonal* ou em *perspectiva*.
- **Rotation Mode:** Decide se a curva vai transladar em torno do eixo Y na origem ou se vai rotacionar em torno de si mesma para fazer o *sweep*.
- **+ Face:** Adiciona mais faces a curva, aumentando o número de colunas do *mesh* da figura.
- **- Face:** Diminui faces da curva, diminuindo o número de colunas do *mesh* da figura.
- **+ Pnt**: Aumenta a quantidade de pontos amostrados removidos da curva de Bézier, aumentando o número de linhas do *mesh* da figura.
- **- Pnt**: Diminui a quantidade de pontos amostrados removidos da curva de Bézier, diminuindo o número de linhas do *mesh* da figura.
- **+ Laps:** Adiciona a quantidade de voltas que serão feitas ao aplicar a curva de Bézier. É útil para gerar molas. 
- **- Laps:** Diminui a quantidade de voltas que serão feitas ao aplicar a curva de Bézier.
- **+ TY:** Usado para gerar um *translational sweep* no eixo Y para cima. Útil para gerar molas. 
- **- TY:** Usado para gerar um *translational sweep* no eixo Y para baixo.
- **Add Node:** Adiciona um ponto de controle à curva de Bézier. Podem ser adicionados **N** pontos, mas o parâmetro foi limitado à 6 pontos, já que acima disso só torna mais dificil de modelar a figura.

## Requisitos Implementados
### Obrigatórios
- Mudanças de quaisquer parâmetros da curva refletem instantaneamente na figura 3D gerada.
- Modelagem do objeto com opção de rotação e translação, para geração de objetos como garrafas, donuts e molas.
- Visualização ortográfica e perspectiva (sob vários ângulos) em wireframe, com uso de triângulos.
- Parametrização do número de pontos e faces do objeto gerado.

### Adicionais
- Adição de mais de 4 pontos de controle.
- Rotação da figura seguindo o movimento do mouse corretamente e com velocidade ajustada ao FPS.