#include "Tetramino.h"

namespace line_collapser
{
	//Construtor
	Tetramino::Tetramino()
	{
		//Zera os atributos
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->matrix[i][j] = 0;
		this->x = -1;
		this->y =  3;

		this->reseted = true;

		this->cor = NONE;

	}//Tetramino::Tetramino()





	//Coloca o tetramino na matiz do jogo
	//devolve 'false' se tentar colocar em posi��o j� ocupada
	//se force for 'true' coloca na posi��o, mesmo se j� ocupada e ignora se tiver algo pra fora da matriz
	bool Tetramino::put_in_matrix(bool force)
	{
		bool flag = true;

		if (!force)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
					if (((this->x + i) < 0) || ((this->y + j) < 0))
					{
						if (matrix[i][j] == 1)
						{
							return false;
						}//if
					}//if
					//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
					if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					{
						if (matrix[i][j] == 1)
						{
							return false;
						}//if
					}//if

					if (this->matrix[i][j] == 1)
					{
						if (game_matrix[this->x + i][this->y + j] != NONE)
						{
							return false;
						}//if
					}//if
				}//for
		}//if !force

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
				if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						flag = false;
					}//if
					game_matrix[this->x + i][this->y + j] = this->cor;
				}//if
			}//for

		this->reseted = false;
		return flag;

	}//bool put_in_matrix();





	//Move para baixo
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool Tetramino::move_down()
	{
		//Se estiver resetado, n�o � poss�vel mover (ele ainda n�o est� na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//Sequ�ncia:
			//Tirar da matriz do jogo (se ainda n�o foi colocado)
			//Incrementar a posi��o vertical (x)
			//Verificar se h� colis�es usando 'put_in_matrix(false)'
			//Se houver
				//Decrementar a posi��o vertical (x)
				//Recoloca na matriz
				//Retorna 'false'
			//Se n�o houver
				//J� colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contr�rio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
				if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		//Incrementar a posi��o vertical (x)
		this->x++;

		//Verificar se h� colis�es usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Decrementar a posi��o vertical (x)
			this->x--;

			//Recoloca na matriz
			//(sem for�ar. Tecnicamente, o espa�o foi completamente esvaziado,
			//ent�o mesmo sem for�ar a fun��o deve ter sucesso, caso contr�rio h� um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se n�o houver
		else
		{
			//J� colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_down();





	//Move para a esquerda
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool Tetramino::move_left()
	{
		//Se estiver resetado, n�o � poss�vel mover (ele ainda n�o est� na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//Sequ�ncia:
			//Tirar da matriz do jogo (se ainda n�o foi colocado)
			//Decrementar a posi��o horizontal (y)
			//Verificar se h� colis�es usando 'put_in_matrix(false)'
			//Se houver
				//Incrementar a posi��o vertical (y)
				//Recoloca na matriz
				//Retorna 'false'
			//Se n�o houver
				//J� colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contr�rio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
				if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		//Decrementar a posi��o horizontal (y)
		this->y--;

		//Verificar se h� colis�es usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Incrementar a posi��o horizontal (y)
			this->y++;

			//Recoloca na matriz
			//(sem for�ar. Tecnicamente, o espa�o foi completamente esvaziado,
			//ent�o mesmo sem for�ar a fun��o deve ter sucesso, caso contr�rio h� um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se n�o houver
		else
		{
			//J� colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_left()





	//Move para a direita
	//Devolve 'false' se nao pode se mover nesta dire��o
	bool Tetramino::move_right()
	{
		//Se estiver resetado, n�o � poss�vel mover (ele ainda n�o est� na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//Sequ�ncia:
			//Tirar da matriz do jogo (se ainda n�o foi colocado)
			//Incrementar a posi��o horizontal (y)
			//Verificar se h� colis�es usando 'put_in_matrix(false)'
			//Se houver
				//Decrementar a posi��o vertical (y)
				//Recolocar na matriz
				//Retorna 'false'
			//Se n�o houver
				//J� colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contr�rio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
				if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		//Incrementar a posi��o horizontal (y)
		this->y++;

		//Verificar se h� colis�es usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Decrementar a posi��o horizontal (y)
			this->y--;

			//Recolocar na matriz
			//(sem for�ar. Tecnicamente, o espa�o foi completamente esvaziado,
			//ent�o mesmo sem for�ar a fun��o deve ter sucesso, caso contr�rio h� um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se n�o houver
		else
		{
			//J� colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_right()





	//Gira no sentido anti-hor�rio
	//Devolve 'false' se nao pode rotacionar
	bool Tetramino::rotate()
	{
		//Se estiver resetado, n�o � poss�vel girar (ele ainda n�o est� na matriz)
		if (this->reseted) return false;

		//Sequ�ncia:
			/* Criar uma c�pia da matriz
			 * Tirar da matriz do jogo (se ainda n�o foi colocado)
			 * Se o Tetramino estiver no estado final
			 *		Criar uma c�pia das coordenadas
			 *		Dar um reset()
			 *		Atualizar as coordenadas e o estado reseted
			 * Se n�o estiver
			 *		Rotacionar a matriz original
			 * Verificar se h� colis�es usando 'put_in_matrix(false)'
			 * Se houver:
			 *		Copiar da matriz-c�pia para a original (desfazendo a rota��o)
			 *		Recolocar na matriz
			 *		Retornar 'false'
			 * Se n�o houver:
			 *		J� colocou usando 'put_in_matrix(false)'
			 *		Atualizar o estado atual
			 *		Retornar 'true'
			 */

		unsigned short int backup[4][4];
		int i;
		int j;

		//Fazendo backup e aproveitando o la�o para
		//tirar da matriz do jogo que � o contr�rio de 'put_in_matrix()'
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				backup[i][j] = this->matrix[i][j];

				//Se x + i ou y + i  � negativo, ainda est� fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i � maior do que o limite, tamb�m est� fora da matriz
				if (((this->x + i) >= MATRIX_HEIGHT) || ((this->y + j) >= MATRIX_WIDTH))
					continue;

				if (this->matrix[i][j] == 1)
				{
					if (game_matrix[this->x + i][this->y + j] != NONE)
					{
						game_matrix[this->x + i][this->y + j] = NONE;
					}//if
				}//if
			}//for

		//Se o Tetramino estiver no estado final
		if (this->state == this->max_states)
		{
			// Criar uma c�pia das coordenadas
			i = this->x;
			j = this->y;

			// Dar um reset()
			this->reset();

			//Atualizar as coordenadas  e o estado reseted
			this->x = i;
			this->y = j;
			this->reseted = false;
		}//if
		
		//Se n�o estiver
		else
		{
		/* Rotacionar a matriz original 
		 * Fazemos com as formulas:
		 * x' = x * cos(theta) - y * sin(theta)
		 * y' = x * sin(theta) + y * cos(theta)
		 * Com theta = 90� (pi/2):
		 * x' = -y
		 * y' = x
		 */
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				this->matrix[i][j] = backup[3-j][i];
			}//for
		}//else

		//Verificar se h� colis�es usando 'put_in_matrix(false)'
		bool flag = this->put_in_matrix(false);
		if (!flag)
		//Se houver
		{
			//Copiar da matriz-c�pia para a original (desfazendo a rota��o)
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					this->matrix[i][j] = backup[i][j];
				}//for

			//Recolocar na matriz
			//(sem for�ar. Tecnicamente, o espa�o foi completamente esvaziado,
			//ent�o mesmo sem for�ar a fun��o deve ter sucesso, caso contr�rio h� um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retornar 'false'
			return false;
		}//if

		//Se n�o houver
		else
		{
			//J� colocou usando 'put_in_matrix(false)'
			//Atualizar o estado atual
			//Se j� chegou ao limite, volta pro inicial
			if (this->state == this->max_states)
				this->state = 1;
			//Se ainda n�o chegou, incrementa
			else
				this->state = this->state + 1;

			//Retornar 'true'
			return true;
		}
	}//bool Tetramino::rotate()

}//namespace