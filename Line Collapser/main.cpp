#include "includes.h"
#include "Timer.h"
#include "Tetramino.h"
#include "Tetraminos.h"


int main (int argc, char* args[])
{
	//Namespace padrão
	using namespace line_collapser;
	
	//Função de inicialização
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

	//Criação de tetraminos
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
	//Se é a primeira iteração
	bool first = true;
	
	//Tetramino atual
	int actual = 0;
	
	//Próximo Tetramino
	int next = 1;
	
	//Se está retirando linhas
	bool collapsing = false;
	
	//Contagem para marcar o tempo da animação
	int counting = 0;

	//Backup das linhas para animação
	BLOCK_COLOR backup[4][MATRIX_WIDTH];

	//O 1º elemento é a quantidade de linhas completas
	//Os outros são os índices das linhas
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
			//Se o usuário tentar fechar a janela
			case SDL_QUIT:
				//Marca a flag para encerramento do loop
				quit = true;
				break;
			//Se o usuário pressionou alguma tecla
			case SDL_KEYDOWN:
				if(    (eventQ.key.keysym.sym == SDLK_F4)		//Se foi pressionado F4
				   &&  (eventQ.key.keysym.mod & KMOD_LALT)		//e estava com Alt esquerda pressionada
				   && !(eventQ.key.keysym.mod & KMOD_CTRL)		//e não estava com Ctrl pressionada
				   && !(eventQ.key.keysym.mod & KMOD_SHIFT))	//e não estava com Shift pressionada	
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

				//Se foi pressionado espaço, rotaciona (sentido anti-horário)
				if (eventQ.key.keysym.sym == SDLK_SPACE)
				{
					tetras[actual]->rotate();
				}
				break;

			//Se o usuário deixou de prssionar alguma tecla
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



		//Controle dos movimentos e lógica



		//Se for a primeira iteração
		if (first)
		{
			//Tenta colocar o primeiro tetramino na matriz
			//Se não for possível, há algo de errado e encerra o programa
			if (!tetras[actual]->put_in_matrix(true))
				quit = true;
			//A partir de agora, não será mais a primeira iteração
			first = false;

			//Não é necessário fazer mais nada, já que acabamos de colocar o tetramino
			//A lógica só ser testada na próxima iteração

		}//if (first)

		//Caso não seja a primeira iteração e não esteja retirando linhas
		else if (!collapsing)
		{
			//A cada 0.1 segundo
			if (frame % (GAME_FPS/10) == 0)
			{
				//Se está pressionado para a esquerda, efetua o movimento
				if (moving_left)
					tetras[actual]->move_left();
				//Se está pressionado para a direita, efetua o movimento
				if(moving_right)
					tetras[actual]->move_right();
			}// if (cada 0.1 segundo)

			//A cada 0.05 segundo e se está pressionando para baixo
			if ((moving_down && (frame % (GAME_FPS/20)) == 0))
			{
				//Efetua o movimento para baixo
				bool scoring = tetras[actual]->move_down();
				
				//Se foi possível mover, incrementa a pontuação
				if (scoring) score++;

			}//if cada 0.05 segundo && moving_down

			//Caso contrário e estiver no tempo adequado ao nível
			else if ( (((frame % ((11 - level)*4)) == 0)))
			{
				//Tenta mover para baixo e caso não consiga
				if (!tetras[actual]->move_down())
				{	
					//Reseta o tetramino atual
					tetras[actual]->reset();

					//Checa por linhas completas
					fullLines = check_lines();

					//Se há linhas completas
					if (fullLines[0] > 0)
					{
						//Inicia a retirada de linhas
						collapsing = true;

						//Verifica quantas linhas estão completas
						//e aplica a pontuação correspondente
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

						//Atualiza o contador de linhas e o nível
						line += fullLines[0];
						level = 1 + floor((double)line / 10);
						//O nível é, no máximo, 10
						level = level < 10 ? level : 10;

					} //if (tem linhas completas)
					//Caso não haja
					else
						//Libera a memória que não será mais usada
						free(fullLines);

					//Caso esteja retirando as linhas
					if (collapsing)
					{
						//Faz o backup das linhas que serão retiradas, para efeito de animação
						//Percorre cada uma das colunas da matriz
						for (int i = 0; i < MATRIX_WIDTH; i++)
						{
							//Pra cada linha que precisar ser retirada
							for (int j = 0; j < fullLines[0]; j++)
							{
								//Copia para o backup a posição da matriz correspondente
								backup[j][i] = game_matrix[fullLines[j+1]][i];

								// fullLines começa em 1, pq fullLines[0] é a quantidade de linhas completas

							}//for linhas completas
						}//for colunas

					}//if (collapsing)

					//Caso não precise retirar linhas
					else
					{
						//O tetramino próximo passa a ser o atual
						actual = next;
						//O próximo tetramino é gerado "aleatoriamente"
						next = get_next();

						//Tenta colocar o próximo tetramino na matriz
						if (!tetras[actual]->put_in_matrix(true))
						{
							//Se não for possível, game over
							//(não precisa fechar tão brusco assim)
							quit = true;
						}//if (não dá pra colocar a próxima na matriz)

					}//if (não precisa retirar linhas)

				}//if (não dá pra mover para baixo)
			
			}//if (está na hora de mover para baixo)

		}// if(!collapsing)

		//Caso esteja retirando linhas
		else //if (collapsing)
		{
			{
				//Incrementa a contagem
				counting++;

				//Animação
					/* A contagem indica em que passo estamos da animação
					 * A cada 6 passos alterna-se entre mostrar e apagar a linha
					 * Para mostrar a linha usamos o backup feito anteriormente 
					 * A última etapa é com a linha apagada
					 */

					if (counting <= 6 || (counting > 12 && counting <= 18) || (counting > 24 && counting <= 30) ||
						(counting > 36 && counting <= 42) || (counting > 48 && counting <= 54))
					//Apaga
					//Esta função é quase idêntica ao backup, a diferença é que apaga da matriz, ao invés de copiar
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = NONE;
						}//for (cada coluna)
					}//for (cada linha completa)

					/* Acho importante comentar que os valores do 'if' de mostrar e de apagar são iguais
					 * O que altera são os operadores de comparação 
					 */
					if ((counting > 6 && counting <= 12) || (counting > 18 && counting <= 24) ||
						(counting > 30 && counting <= 36) || (counting > 42 && counting <= 48))
					//Desfaz o apagar
					//Esta função é quase idêntica ao backup, a diferença é que copia do backup para a matriz, ao invés do contrário
					for (int i = 0; i < MATRIX_WIDTH; i++)
					{
						for (int j = 0; j < fullLines[0]; j++)
						{
							game_matrix[fullLines[j+1]][i] = backup[j][i];
						}//for (cada coluna)
					}//for (cada linha completa)


				//Se a contagem passou do último passo
				if (counting > 54)
				{
					//Para cada linha completa
					for (int i = 0; i < fullLines[0]; i++)
					{
						//Retira a linha
						collapse_line(fullLines[i+1]);
					}//for (cada linha completa)

					//Não está mais retirando a linha
					collapsing = false;

					//O próximo tetramino passa a ser o atual
					actual = next;

					//O próximo tetramino é gerado "aleatoriamente"
					next = get_next();

					//Se não for possível colocar na matriz, game over
					//(não precisa fechar tão brusco assim)
					if (!tetras[actual]->put_in_matrix(true))
					{
						quit = true;
					}
					//Libera a memória que não será mais utilizada
					free(fullLines);

					//Zera a contagem de passos da animação
					counting = 0;
				}
			}
		}
							

		//Renderização
		//Aplica a imagem de fundo
		apply_surface(0, 0, background, screen);

		//Desenha o próximo Tetramino
		tetras[next]->draw_in_next();

		//Escreve a pontuação
		print_score (score);

		//Escreve a quantidade de  linhas
		print_line (line);

		//Escreve o nível atual
		print_level (level);

		//Desenha a matriz
		paint_matrix();

		//Atualiza a tela e checa por erros
		if (SDL_Flip(screen) == -1)
		{
			quit = true;
		}

		//Mantém a framerate
		if (fpscap.getTicks() < 1000 / GAME_FPS)
			SDL_Delay ( (1000 / GAME_FPS) - fpscap.getTicks());

	}//while do loop principal

	//Função de finalização
	end_app();

	return 0;
}