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
	//devolve 'false' se tentar colocar em posiXXo jX ocupada
	//se force for 'true' coloca na posiXXo, mesmo se jX ocupada e ignora se tiver algo pra fora da matriz
	bool Tetramino::put_in_matrix(bool force)
	{
		bool flag = true;

		if (!force)
		{
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++)
				{
					//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
					if (((this->x + i) < 0) || ((this->y + j) < 0))
					{
						if (matrix[i][j] == 1)
						{
							return false;
						}//if
					}//if
					//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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
				//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool Tetramino::move_down()
	{
		//Se estiver resetado, nXo X possXvel mover (ele ainda nXo estX na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//SequXncia:
			//Tirar da matriz do jogo (se ainda nXo foi colocado)
			//Incrementar a posiXXo vertical (x)
			//Verificar se hX colisXes usando 'put_in_matrix(false)'
			//Se houver
				//Decrementar a posiXXo vertical (x)
				//Recoloca na matriz
				//Retorna 'false'
			//Se nXo houver
				//JX colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contrXrio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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

		//Incrementar a posiXXo vertical (x)
		this->x++;

		//Verificar se hX colisXes usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Decrementar a posiXXo vertical (x)
			this->x--;

			//Recoloca na matriz
			//(sem forXar. Tecnicamente, o espaXo foi completamente esvaziado,
			//entXo mesmo sem forXar a funXXo deve ter sucesso, caso contrXrio hX um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se nXo houver
		else
		{
			//JX colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_down();





	//Move para a esquerda
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool Tetramino::move_left()
	{
		//Se estiver resetado, nXo X possXvel mover (ele ainda nXo estX na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//SequXncia:
			//Tirar da matriz do jogo (se ainda nXo foi colocado)
			//Decrementar a posiXXo horizontal (y)
			//Verificar se hX colisXes usando 'put_in_matrix(false)'
			//Se houver
				//Incrementar a posiXXo vertical (y)
				//Recoloca na matriz
				//Retorna 'false'
			//Se nXo houver
				//JX colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contrXrio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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

		//Decrementar a posiXXo horizontal (y)
		this->y--;

		//Verificar se hX colisXes usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Incrementar a posiXXo horizontal (y)
			this->y++;

			//Recoloca na matriz
			//(sem forXar. Tecnicamente, o espaXo foi completamente esvaziado,
			//entXo mesmo sem forXar a funXXo deve ter sucesso, caso contrXrio hX um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se nXo houver
		else
		{
			//JX colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_left()





	//Move para a direita
	//Devolve 'false' se nao pode se mover nesta direXXo
	bool Tetramino::move_right()
	{
		//Se estiver resetado, nXo X possXvel mover (ele ainda nXo estX na matriz)
		if (this->reseted) return false;

		bool flag = true;
		
		//SequXncia:
			//Tirar da matriz do jogo (se ainda nXo foi colocado)
			//Incrementar a posiXXo horizontal (y)
			//Verificar se hX colisXes usando 'put_in_matrix(false)'
			//Se houver
				//Decrementar a posiXXo vertical (y)
				//Recolocar na matriz
				//Retorna 'false'
			//Se nXo houver
				//JX colocou usando 'put_in_matrix(false)'
				//Retorna 'true'

		//Tirar da matriz do jogo (o contrXrio de 'put_in_matrix()')
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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

		//Incrementar a posiXXo horizontal (y)
		this->y++;

		//Verificar se hX colisXes usando 'put_in_matrix(false)'
		flag = this->put_in_matrix(false);

		//Se houver
		if (!flag)
		{
			//Decrementar a posiXXo horizontal (y)
			this->y--;

			//Recolocar na matriz
			//(sem forXar. Tecnicamente, o espaXo foi completamente esvaziado,
			//entXo mesmo sem forXar a funXXo deve ter sucesso, caso contrXrio hX um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retorna 'false'
			return false;
		}//if
		//Se nXo houver
		else
		{
			//JX colocou usando 'put_in_matrix(false)'
			//Retorna 'true'
			return true;
		}//else

	}//bool Tetramino::move_right()





	//Gira no sentido anti-horXrio
	//Devolve 'false' se nao pode rotacionar
	bool Tetramino::rotate()
	{
		//Se estiver resetado, nXo X possXvel girar (ele ainda nXo estX na matriz)
		if (this->reseted) return false;

		//SequXncia:
			/* Criar uma cXpia da matriz
			 * Tirar da matriz do jogo (se ainda nXo foi colocado)
			 * Se o Tetramino estiver no estado final
			 *		Criar uma cXpia das coordenadas
			 *		Dar um reset()
			 *		Atualizar as coordenadas e o estado reseted
			 * Se nXo estiver
			 *		Rotacionar a matriz original
			 * Verificar se hX colisXes usando 'put_in_matrix(false)'
			 * Se houver:
			 *		Copiar da matriz-cXpia para a original (desfazendo a rotaXXo)
			 *		Recolocar na matriz
			 *		Retornar 'false'
			 * Se nXo houver:
			 *		JX colocou usando 'put_in_matrix(false)'
			 *		Atualizar o estado atual
			 *		Retornar 'true'
			 */

		unsigned short int backup[4][4];
		int i;
		int j;

		//Fazendo backup e aproveitando o laXo para
		//tirar da matriz do jogo que X o contrXrio de 'put_in_matrix()'
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				backup[i][j] = this->matrix[i][j];

				//Se x + i ou y + i  X negativo, ainda estX fora da matriz do jogo
				if (((this->x + i) < 0) || ((this->y + j) < 0))
					continue;
				//Se x + i ou y + i X maior do que o limite, tambXm estX fora da matriz
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
			// Criar uma cXpia das coordenadas
			i = this->x;
			j = this->y;

			// Dar um reset()
			this->reset();

			//Atualizar as coordenadas  e o estado reseted
			this->x = i;
			this->y = j;
			this->reseted = false;
		}//if
		
		//Se nXo estiver
		else
		{
		/* Rotacionar a matriz original 
		 * Fazemos com as formulas:
		 * x' = x * cos(theta) - y * sin(theta)
		 * y' = x * sin(theta) + y * cos(theta)
		 * Com theta = 90X (pi/2):
		 * x' = -y
		 * y' = x
		 */
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
			{
				this->matrix[i][j] = backup[3-j][i];
			}//for
		}//else

		//Verificar se hX colisXes usando 'put_in_matrix(false)'
		bool flag = this->put_in_matrix(false);
		if (!flag)
		//Se houver
		{
			//Copiar da matriz-cXpia para a original (desfazendo a rotaXXo)
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
				{
					this->matrix[i][j] = backup[i][j];
				}//for

			//Recolocar na matriz
			//(sem forXar. Tecnicamente, o espaXo foi completamente esvaziado,
			//entXo mesmo sem forXar a funXXo deve ter sucesso, caso contrXrio hX um erro indeterminado [buffer overflow???])
			if (!this->put_in_matrix(false)) return false;

			//Retornar 'false'
			return false;
		}//if

		//Se nXo houver
		else
		{
			//JX colocou usando 'put_in_matrix(false)'
			//Atualizar o estado atual
			//Se jX chegou ao limite, volta pro inicial
			if (this->state == this->max_states)
				this->state = 1;
			//Se ainda nXo chegou, incrementa
			else
				this->state = this->state + 1;

			//Retornar 'true'
			return true;
		}
	}//bool Tetramino::rotate()

}//namespace
