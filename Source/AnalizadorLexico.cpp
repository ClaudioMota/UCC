#include <AnalizadorLexico.h>

MaquinaToken tokenDesconhecido((char*)"token desconhecido", NULL, 0, NULL);

Lista<Token>* AnalizadorLexico::getTokensList(MaquinaToken* maquinas, FILE* arquivo)
{
  int POSICAO_INICIAL_CURSORS = 1;
  int ESPACO_TAB = 2;

  int tamanhoArquivo;

  fseek(arquivo, 0, SEEK_END);
  tamanhoArquivo = ftell(arquivo);
  fseek(arquivo, 0, SEEK_SET);

  if(!tamanhoArquivo) return NULL;

  char* textoArquivo = new char[tamanhoArquivo+1];
  textoArquivo[tamanhoArquivo] = '\0';

  fread(textoArquivo, sizeof(char), tamanhoArquivo, arquivo);

  int posicaoArquivo = 0, posicaoAceita = 0, posicaoInicio = 0, linhaInicio, colunaInicio;
  linhaInicio = colunaInicio = POSICAO_INICIAL_CURSORS;

  unsigned char entrada;

  Lista<Token>* retorno = NULL;
  Lista<Token>* ultimo = NULL;

  //Reinicia as leitoras de token
  MaquinaToken* maquinaApta = NULL;
  MaquinaToken* aux = maquinas;
  while(aux)
  {
    aux->reiniciar();
    aux = aux->getProxima();
  }

  while(posicaoArquivo <= tamanhoArquivo)
  {
    entrada = (unsigned char)textoArquivo[posicaoArquivo];

    bool hasLife = false;
    aux = maquinas;

    while(aux)
    {
      if(aux->isAlive())
      {
        aux->operar(entrada);
        if(aux->isAlive())
        {
          hasLife = true;

          if(aux->finalizada())
          { posicaoAceita = posicaoArquivo;
            maquinaApta = aux;
          }
        }
      }
      aux = aux->getProxima();
    }

    if(!hasLife || !textoArquivo[posicaoArquivo])
    {
      Token* token = new Token;
      token->linha = linhaInicio;
      token->coluna = colunaInicio;
      Lista<Token>* next = new Lista<Token>(token, NULL);

      if(maquinaApta)
      {
        token->tipo = maquinaApta;
        token->ignorado = (maquinaApta->getNome()[0] == '*');
        token->tamanho = posicaoAceita -posicaoInicio +1;
        token->conteudo = to_string(textoArquivo + posicaoInicio, token->tamanho);
        for(int p = posicaoInicio; p <= posicaoAceita; p++)
        {
          if(textoArquivo[p] == '\n')
          {
            linhaInicio++;
            colunaInicio = POSICAO_INICIAL_CURSORS;
          }else
          { if(textoArquivo[p] == '\t')
            {
              colunaInicio += ESPACO_TAB;
            }else
            {
              colunaInicio++;
            }
          }
        }

        posicaoInicio = posicaoAceita+1;
      }else
      {
        token->ignorado = false;
        token->tipo = &tokenDesconhecido;
        token->tamanho = 1;
        token->conteudo = to_string(textoArquivo + posicaoInicio, 1);
        if(textoArquivo[posicaoInicio] == '\n')
        {
          linhaInicio++;
          colunaInicio = POSICAO_INICIAL_CURSORS;
        }else
        { if(textoArquivo[posicaoInicio] == '\t')
          {
            colunaInicio += ESPACO_TAB;
          }else
          {
            colunaInicio++;
          }
        }

        posicaoInicio++;
        posicaoArquivo = posicaoInicio;
      }

      if(ultimo)
      {
        ultimo->proximo = next;
        ultimo = next;
      }else
      {
        retorno = next;
        ultimo = retorno;
      }

      maquinaApta = NULL;
      aux = maquinas;
      while(aux)
      { aux->reiniciar();
        aux = aux->getProxima();
      }

      if(!textoArquivo[posicaoArquivo])
      { break;}
    }else
    {
      posicaoArquivo++;
    }
  }

  delete [] textoArquivo;

  return retorno;
}
