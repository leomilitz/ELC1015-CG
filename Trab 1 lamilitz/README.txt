Trabalho 1 de Computação Gráfica - Leonardo Militz

LM - Image Viewer

O programa é um visualizador de multiplas imagens simultâneas, com possibilidade manipulação de 
cor, escala, rotação, e com visualização de um histograma de cores.

----------------------------------------------

Funções Implementadas:

- Carrega três imagens diferentes (A, B, C) no formato BMP, e converte de BGR para RGB. Podem
  ser carregadas até quatro imagens simultâneas.

- Diversos controle de cor funcionando de forma simultânea:
	* Botões RGBL: Ligar ou desligar os canais RGB e a luminância de forma mútua; por exemplo,
 	  se o canal verde for desligado a imagem fica roxa. A luminância acompanha o estado dos
          canais corretamente.
	* Invert: inverte a cor da imagem. 
	* BGR <-> RGB: Converte a imagem de formato RGB para BGR.
	* Brightness: Controla o brilho da imagem, para mais claro ou para mais escuro.
	* Contrast: Controla o contraste da imagem, para menor contraste ou para maior.

- Controles da disposição dos pixels da imagem:
	* Flip Hor.: Faz o flip horizontal da imagem.
	* Flip Ver.: Faz o flip vertical da imagem.
	* Rotate Left: Gira a imagem 90 graus para a esquerda.
	* Rotate Right: Gira a imagem 90 graus para a direita.
	* Scale 200%: Escala de 2x na imagem.
	* Scale 50%: Escala de 1/2x na imagem. Pode ser aplicada duas vezes, fazendo uma
	  escala de 1/4x.

- Histograma de cores que mostra a recorrencia das cores nos canais RGB e luminância da imagem
  selecionada.

- Experiência de Usuário:
	* Imagem selecionada sempre estará na frente das outras;
	* Imagem selecionada pode ser arrastada pela tela de forma suave;
	* outline com fading para a imagem selecionada ou para imagens em que o mouse está
	  em cima (hover);
	* A troca de imagens é sincronizada com a UI, então os sliders, botões toggle e o 
	  histograma irão acompanhar a troca de imagem corretamente;
	* O histograma é sincronizado com as manipulações de cor e de escala, então esse tipo
	  de operação irá ser visível no histograma de forma dinâmica;
	* Display do nome da imagem selecionada;
	* Pode-se deletar a imagem selecionada para adicionar outra;
	* Pode-se abrir as imagens com os botões 1, 2 e 3 do teclado;

- Interface de Usuário:
	* Botões: Classe genérica de botão com cinco cores diferentes e estados diferentes em
	  relação ao mouse. Foram usadas funções lambda como callback para cada botão, de forma
	  que ele possa ser implementado genericamente para qualquer interface Canvas2D.
	* Sliders: Classe genérica de slider, retorna um valor inteiro e mostra graficamente a
	  em que o botão está. Também são usadas funções callback para que o elemento alvo da tela
	  (neste caso, a imagem) seja sincronizado junto com o valor retornado do slider.
	* Scaling da Tela: Todos elementos da interface são sincronizados com o tamanho da tela,
	  então mesmo que o usuário queira mudar o tamanho da tela, a interface de usuário irá
	  acompanhar a escala corretamente.