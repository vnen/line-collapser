
#include "Timer.h"
#include "Tetraminos.h"

#include <string>
#include <cstdlib>
#include <math.h>


int main (int argc, char* args[])
{
	//Namespace padrao
	using namespace line_collapser;
	
	//Funo de inicializao
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

	//Criao de tetraminos
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
	//Se  a primeira iterao
	bool first = true;
	
	//Tetramino atual
	int actual = 0;
	
	//Prximo Tetramino
	int next = 1;
	
	//Se est retirando linhas
	bool collapsing = false;
	
	//Contagem para marcar o tempo da animao
	int counting = 0;

	//Contagem de tempo para a fixao do tetramino
	Timer bottom;

	//Backup das linhas para animao
	BLOCK_COLOR backup[4][MATRIX_WIDTH];

	//O 1 elemento  a quantidade de linhas completas
	//Os outros so os ndices das linhas
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
			//Se o usurio tentar fechar a janela
			case SDL_QUIT:
				//Marca a flag para encerramento do loop
				quit = true;
				break;
			//Se o usurio pressionou alguma tecla
			case SDL_KEYDOWN:
				if(    (eventQ.key.keysym.sym == SDLK_F4)		//Se foi pressionado F4
				   &&  (eventQ.key.keysym.mod & KMOD_LALT)		//e estava com Alt esquerda pressionada
				   && !(eventQ.key.keysym.mod & KMOD_CTRL)		//e no estava com Ctrl pressionada
				   && !(eventQ.key.keysym.mod & KMOD_SHIFT))	//e no estava com Shift pressionada
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

				//Se foi pressionado espao, rotaciona (sentido anti-horrio)
				if (eventQ.key.keysym.sym == SDLK_SPACE)
				{
					tetras[actual]->rotate();
				}
				break;

			//Se o usurio deixou de prssionar alguma tecla
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



		//Controle dos movimentos e lgica



		//Se for a primeira iterao
		if (first)
		{
			//Tenta colocar o primeiro tetramino na matriz
			//Se no for possvel, h algo de errado e encerra o programa
			if (!tetras[actual]->put_in_matrix(true))
				quit = true;
			//A partir de agora, no ser mais a primeira iterao
			first = false;

			//No  necessrio fazer mais nada, j que acabamos de colocar o tetramino
			//A lgica s ser testada na prxima iterao

		}//if (first)

		//Caso no seja a primeira iterao e no esteja retirando linhas
		else if (!collapsing)
		{
			//A cada 0.1 segundo
			if (frame % (GAME_FPS/10) == 0)
			{
				//Se est pressionado para a esquerda, efetua o movimento
				if (moving_left)
					tetras[actual]->move_left();
				//Se est pressionado para a direita, efetua o movimento
				if(moving_right)
					tetras[actual]->move_right();
			}// if (cada 0.1 segundo)

			//A cada 0.05 segundo e se est pressionando para baixo
			if ((moving_down && (frame % (GAME_FPS/20)) == 0))
			{
				//Efetua o movimento para baixo
				bool scoring = tetras[actual]->move_down();
				
				//Se foi possvel mover, incrementa a pontuao
				if (scoring) score++;
				//Se no  mais possvel mover, cancela as prximas tentativas
				else moving_down = false;

			}//if cada 0.05 segundo && moving_down

			//Caso contrrio e estiver no tempo adequado ao nvel
			else if ( (((frame % ((11 - level)*4)) == 0)))
			{
				//Tenta mover para baixo e caso no consiga
				if (!tetras[actual]->move_down())
				{
					//Inicia o contador, se ainda no estiver iniciado
					if(!bottom.isStarted())
						bottom.start();
				}
			}//if (est na hora de mover para baixo)
			
			//Se j tentou mover para baixo por tempo suficiente (750ms)
			if (bottom.isStarted() && bottom.getTicks() > 750)
			{	

				//Para o contador
				bottom.stop();

				//Reseta o tetramino atual
				tetras[actual]->reset();

				//Checa por linhas completas
				fullLines = check_lines();

				//Se h linhas completas
				if (fullLines[0] > 0)
				{
					//Inicia a retirada de linhas
					collapsing = true;

					//Verifica quantas linhas esto completas
					//e aplica a pontuao correspondente
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

					//Atualiza o contador de linhas e o nvel
					line += fullLines[0];
					level = (int)1 + floor((double)line / 10);
					//O nvel , no mximo, 10
					level = level < 10 ? level : 10;

				} //if (tem linhas completas)
				//Caso no haja
				else
					//Libera a memria que no ser mais usada
					free(fullLines);

				//Caso esteja retirando as linhas
				if (collapsing)
				{
					//Faz o backup das linhas que sero retiradas, para efeito de animao
					//Percorre cada uma das colunas da matriz
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						//Pra cada linha que precisar ser retirada
						for (int j = 0; j < fullLines[0]; j++)
						{
							//Copia para o backup a posio da matriz correspondente
							backup[j][i] = game_matrix[fullLines[j+1]][i];

							// fullLines comea em 1, pq fullLines[0]  a quantidade de linhas completas

						}//for linhas completas
					}//for colunas

				}//if (collapsing)

				//Caso no precise retirar linhas
				else
				{
					//O tetramino prximo passa a ser o atual
					actual = next;
					//O prximo tetramino  gerado "aleatoriamente"
					next = get_next();

					//Tenta colocar o prximo tetramino na matriz
					if (!tetras[actual]->put_in_matrix(true))
					{
						//Se no for possvel, game over
						//(no precisa fechar to brusco assim)
						quit = true;
					}//if (no d pra colocar a prxima na matriz)

				}//if (no precisa retirar linhas)

			}//if (no d pra mover para baixo)

		}// if(!collapsing)

		//Caso esteja retirando linhas
		if (collapsing)
		{
			{
				//Incrementa a contagem
				counting++;

				//Animao
					/* A contagem indica em que passo estamos da animao
					 * A cada 6 passos alterna-se entre mostrar e apagar a linha
					 * Para mostrar a linha usamos o backup feito anteriormente 
					 * A ltima etapa  com a linha apagada
					 */

					if (counting <= 6 || (counting > 12 && counting <= 18) || (counting > 24 && counting <= 30) ||
						(counting > 36 && counting <= 42) || (counting > 48 && counting <= 54))
					//Apaga
					//Esta funo  quase idntica ao backup, a diferena  que apaga da matriz, ao invs de copiar
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = NONE;
						}//for (cada coluna)
					}//for (cada linha completa)

					/* Acho importante comentar que os valores do 'if' de mostrar e de apagar so iguais
					 * O que altera so os operadores de comparao
					 */
					if ((counting > 6 && counting <= 12) || (counting > 18 && counting <= 24) ||
						(counting > 30 && counting <= 36) || (counting > 42 && counting <= 48))
					//Desfaz o apagar
					//Esta funo  quase idntica ao backup, a diferena  que copia do backup para a matriz, ao invs do contrrio
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = backup[j][i];
						}//for (cada coluna)
					}//for (cada linha completa)


				//Se a contagem passou do ltimo passo
				if (counting > 54)
				{
					//Para cada linha completa
					for (int i = 0; i < fullLines[0]; i++)
					{
						//Retira a linha
						collapse_line(fullLines[i+1]);
					}//for (cada linha completa)

					//No est mais retirando a linha
					collapsing = false;

					//O prximo tetramino passa a ser o atual
					actual = next;

					//O prximo tetramino  gerado "aleatoriamente"
					next = get_next();

					//Se no for possvel colocar na matriz, game over
					//(no precisa fechar to brusco assim)
					if (!tetras[actual]->put_in_matrix(true))
					{
						quit = true;
					}
					//Libera a memria que no ser mais utilizada
					free(fullLines);

					//Zera a contagem de passos da animao
					counting = 0;
				}
			}
		}
							

		//Renderizao
		//Aplica a imagem de fundo
		apply_surface(0, 0, background, screen);

		//Desenha o prximo Tetramino
		tetras[next]->draw_in_next();

		//Escreve a pontuao
		print_score (score);

		//Escreve a quantidade de  linhas
		print_line (line);

		//Escreve o nvel atual
		print_level (level);

		//Desenha a matriz
		paint_matrix();

		//Atualiza a tela e checa por erros
		if (SDL_Flip(screen) == -1)
		{
			quit = true;
		}

		//Mantm a framerate
		if (fpscap.getTicks() < 1000 / GAME_FPS)
			SDL_Delay ( (1000 / GAME_FPS) - fpscap.getTicks());

	}//while do loop principal

	//Funo de finalizao
	end_app();

	return 0;
}
