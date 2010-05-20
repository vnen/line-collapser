#include "includes.h"
#include "Timer.h"
#include "Tetramino.h"
#include "Tetraminos.h"


int main (int argc, char* args[])
{
	//Namespace padr�o
	using namespace line_collapser;
	
	//Fun��o de inicializa��o
	//Se ocorreu algum erro encerra o programa
	int errorlevel = init();
	if (errorlevel != 0)
	{
		if(SDL_WasInit(SDL_INIT_EVERYTHING) != 0)
		{ //Se o SDL foi inicializado, o encerra
			SDL_Quit();

			if(TTF_WasInit() == 1)
			{ //Se o SDL_ttf foi inicializado, o encerra
				TTF_Quit();
			}
		}

		return errorlevel;
	}

	//Timer para controlar a velocidade dos blocos (na verdade a frame rate)
	Timer fpscap;
	unsigned int frame = 0;

	//Cria��o de tetraminos
	Tetramino* tetras[7];
	tetras[0] = new I();
	tetras[1] = new O();
	tetras[2] = new L();
	tetras[3] = new J();
	tetras[4] = new S();
	tetras[5] = new Z();
	tetras[6] = new T();
	
	/********************/
	//***** Dados ******//
	/********************/
	//Se � a primeira itera��o
	bool first = true;
	
	//Tetramino atual
	int actual = 0;
	
	//Pr�ximo Tetramino
	int next = 1;
	
	//Se est� retirando linhas
	bool collapsing = false;
	
	//Contagem para marcar o tempo da anima��o
	int counting = 0;

	//Backup das linhas para anima��o
	BLOCK_COLOR backup[4][MATRIX_WIDTH];

	//O 1� elemento � a quantidade de linhas completas
	//Os outros s�o os �ndices das linhas
	int* fullLines;

	//Indicadores para controle pelo jogador
	bool moving_down = false;
	bool moving_left = false;
	bool moving_right = false;




	//Loop principal
	bool quit = false;
	while (!quit)
	{
		fpscap.start();
		frame++;

		//Trata todos os eventos gerados
		while (SDL_PollEvent (&eventQ))
		{
			//Captura o tipo de evento
			switch (eventQ.type)
			{
			//Se o usu�rio tentar fechar a janela
			case SDL_QUIT:
				//Marca a flag para encerramento do loop
				quit = true;
				break;
			//Se o usu�rio pressionou alguma tecla
			case SDL_KEYDOWN:
				if(    (eventQ.key.keysym.sym == SDLK_F4)		//Se foi pressionado F4
				   &&  (eventQ.key.keysym.mod & KMOD_LALT)		//e estava com Alt esquerda pressionada
				   && !(eventQ.key.keysym.mod & KMOD_CTRL)		//e n�o estava com Ctrl pressionada
				   && !(eventQ.key.keysym.mod & KMOD_SHIFT))	//e n�o estava com Shift pressionada	
				{
					quit = true;								//Marca a flag para encerramento do loop
				}
				if (eventQ.key.keysym.sym == SDLK_ESCAPE)		//Se foi pressionado Esc
				{
					quit = true;								//Marca a flag para encerramento do loop
				}

				//Se foi pressionado para a esquerda, habilitar a flag
				if(eventQ.key.keysym.sym == SDLK_LEFT)
				{
					moving_left = true;
				}
				//Se foi pressionado para a direita, habilitar a flag
				if(eventQ.key.keysym.sym == SDLK_RIGHT)
				{
					moving_right = true;
				}
				//Se foi pressionado para baixo, habilitar a flag
				if(eventQ.key.keysym.sym == SDLK_DOWN)
				{
					moving_down = true;
				}

				//Se foi pressionado espa�o, rotaciona (sentido anti-hor�rio)
				if (eventQ.key.keysym.sym == SDLK_SPACE)
				{
					tetras[actual]->rotate();
				}
				break;

			//Se o usu�rio deixou de prssionar alguma tecla
			case SDL_KEYUP:
				//Se deixou de pressionar para a esquerda, desabilitar a flag
				if(eventQ.key.keysym.sym == SDLK_LEFT)
				{
					moving_left = false;
				}
				//Se deixou de pressionar para a direita, desabilitar a flag
				if(eventQ.key.keysym.sym == SDLK_RIGHT)
				{
					moving_right = false;
				}
				//Se deixou de pressionar para baixo, desabilitar a flag
				if(eventQ.key.keysym.sym == SDLK_DOWN)
				{
					moving_down = false;
				}
			default:
				break;
			}//switch de eventos
		}//while de eventos



		//Controle dos movimentos e l�gica



		//Se for a primeira itera��o
		if (first)
		{
			//Tenta colocar o primeiro tetramino na matriz
			//Se n�o for poss�vel, h� algo de errado e encerra o programa
			if (!tetras[actual]->put_in_matrix(true))
				quit = true;
			//A partir de agora, n�o ser� mais a primeira itera��o
			first = false;

			//N�o � necess�rio fazer mais nada, j� que acabamos de colocar o tetramino
			//A l�gica s� ser testada na pr�xima itera��o

		}//if (first)

		//Caso n�o seja a primeira itera��o e n�o esteja retirando linhas
		else if (!collapsing)
		{
			//A cada 0.1 segundo
			if (frame % (GAME_FPS/10) == 0)
			{
				//Se est� pressionado para a esquerda, efetua o movimento
				if (moving_left)
					tetras[actual]->move_left();
				//Se est� pressionado para a direita, efetua o movimento
				if(moving_right)
					tetras[actual]->move_right();
			}// if (cada 0.1 segundo)

			//A cada 0.05 segundo e se est� pressionando para baixo
			if ((moving_down && (frame % (GAME_FPS/20)) == 0))
			{
				//Efetua o movimento para baixo
				bool scoring = tetras[actual]->move_down();
				
				//Se foi poss�vel mover, incrementa a pontua��o
				if (scoring) score++;

			}//if cada 0.05 segundo && moving_down

			//Caso contr�rio e estiver no tempo adequado ao n�vel
			else if ( (((frame % ((11 - level)*4)) == 0)))
			{
				//Tenta mover para baixo e caso n�o consiga
				if (!tetras[actual]->move_down())
				{	
					//Reseta o tetramino atual
					tetras[actual]->reset();

					//Checa por linhas completas
					fullLines = check_lines();

					//Se h� linhas completas
					if (fullLines[0] > 0)
					{
						//Inicia a retirada de linhas
						collapsing = true;

						//Verifica quantas linhas est�o completas
						//e aplica a pontua��o correspondente
						switch(fullLines[0])
						{
						case 1:
							score += 100;
							break;
						case 2:
							score += 200;
							break;
						case 3:
							score += 400;
							break;
						case 4:
							score += 800;
							break;
						default:
							break;
						}//switch (linhas completas)

						//Atualiza o contador de linhas e o n�vel
						line += fullLines[0];
						level = 1 + floor((double)line / 10);
						//O n�vel �, no m�ximo, 10
						level = level < 10 ? level : 10;

					} //if (tem linhas completas)
					//Caso n�o haja
					else
						//Libera a mem�ria que n�o ser� mais usada
						free(fullLines);

					//Caso esteja retirando as linhas
					if (collapsing)
					{
						//Faz o backup das linhas que ser�o retiradas, para efeito de anima��o
						//Percorre cada uma das colunas da matriz
						for (int i = 0; i < MATRIX_WIDTH; i++)
						{
							//Pra cada linha que precisar ser retirada
							for (int j = 0; j < fullLines[0]; j++)
							{
								//Copia para o backup a posi��o da matriz correspondente
								backup[j][i] = game_matrix[fullLines[j+1]][i];

								// fullLines come�a em 1, pq fullLines[0] � a quantidade de linhas completas

							}//for linhas completas
						}//for colunas

					}//if (collapsing)

					//Caso n�o precise retirar linhas
					else
					{
						//O tetramino pr�ximo passa a ser o atual
						actual = next;
						//O pr�ximo tetramino � gerado "aleatoriamente"
						next = get_next();

						//Tenta colocar o pr�ximo tetramino na matriz
						if (!tetras[actual]->put_in_matrix(true))
						{
							//Se n�o for poss�vel, game over
							//(n�o precisa fechar t�o brusco assim)
							quit = true;
						}//if (n�o d� pra colocar a pr�xima na matriz)

					}//if (n�o precisa retirar linhas)

				}//if (n�o d� pra mover para baixo)
			
			}//if (est� na hora de mover para baixo)

		}// if(!collapsing)

		//Caso esteja retirando linhas
		else //if (collapsing)
		{
			{
				//Incrementa a contagem
				counting++;

				//Anima��o
					/* A contagem indica em que passo estamos da anima��o
					 * A cada 6 passos alterna-se entre mostrar e apagar a linha
					 * Para mostrar a linha usamos o backup feito anteriormente 
					 * A �ltima etapa � com a linha apagada
					 */

					if (counting <= 6 || (counting > 12 && counting <= 18) || (counting > 24 && counting <= 30) ||
						(counting > 36 && counting <= 42) || (counting > 48 && counting <= 54))
					//Apaga
					//Esta fun��o � quase id�ntica ao backup, a diferen�a � que apaga da matriz, ao inv�s de copiar
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = NONE;
						}//for (cada coluna)
					}//for (cada linha completa)

					/* Acho importante comentar que os valores do 'if' de mostrar e de apagar s�o iguais
					 * O que altera s�o os operadores de compara��o 
					 */
					if ((counting > 6 && counting <= 12) || (counting > 18 && counting <= 24) ||
						(counting > 30 && counting <= 36) || (counting > 42 && counting <= 48))
					//Desfaz o apagar
					//Esta fun��o � quase id�ntica ao backup, a diferen�a � que copia do backup para a matriz, ao inv�s do contr�rio
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = backup[j][i];
						}//for (cada coluna)
					}//for (cada linha completa)


				//Se a contagem passou do �ltimo passo
				if (counting > 54)
				{
					//Para cada linha completa
					for (int i = 0; i < fullLines[0]; i++)
					{
						//Retira a linha
						collapse_line(fullLines[i+1]);
					}//for (cada linha completa)

					//N�o est� mais retirando a linha
					collapsing = false;

					//O pr�ximo tetramino passa a ser o atual
					actual = next;

					//O pr�ximo tetramino � gerado "aleatoriamente"
					next = get_next();

					//Se n�o for poss�vel colocar na matriz, game over
					//(n�o precisa fechar t�o brusco assim)
					if (!tetras[actual]->put_in_matrix(true))
					{
						quit = true;
					}
					//Libera a mem�ria que n�o ser� mais utilizada
					free(fullLines);

					//Zera a contagem de passos da anima��o
					counting = 0;
				}
			}
		}
							

		//Renderiza��o
		//Aplica a imagem de fundo
		apply_surface(0, 0, background, screen);

		//Desenha o pr�ximo Tetramino
		tetras[next]->draw_in_next();

		//Escreve a pontua��o
		print_score (score);

		//Escreve a quantidade de  linhas
		print_line (line);

		//Escreve o n�vel atual
		print_level (level);

		//Desenha a matriz
		paint_matrix();

		//Atualiza a tela e checa por erros
		if (SDL_Flip(screen) == -1)
		{
			quit = true;
		}

		//Mant�m a framerate
		if (fpscap.getTicks() < 1000 / GAME_FPS)
			SDL_Delay ( (1000 / GAME_FPS) - fpscap.getTicks());

	}//while do loop principal

	//Fun��o de finaliza��o
	end_app();

	return 0;
}