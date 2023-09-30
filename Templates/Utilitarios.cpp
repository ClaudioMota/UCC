#include <ctype.h>
#include <string.h>
#include <Utilitarios.h>

char* trim(char* entrada, int tamanho)
{
  char* saida = new char[tamanho+1];
  int i = 0, j = 0;
  for(i = 0; i < tamanho; i++)
  {
    if(!isspace(entrada[i]))
    {
      saida[j++] = entrada[i];
    }
  }
  saida[j] = 0;
  return saida;
}

char* to_string(char* str, int tam = 0)
{
  int i;
  if(tam == 0) tam = strlen(str);
  char* retorno = new char [tam+1];
  for(i = 0; i < tam; i++)
  {
    retorno[i] = str[i];
  }
  retorno[tam] = '\0';
  return retorno;
}

char* to_string(char c)
{
  char* retorno = new char[2];
  retorno[0] = c;
  retorno[1] = '\0';
  return retorno;
}

char* to_ASCII_string(char* str, int tam = 0)
{
  int i,j = 0;
  if(tam == 0) tam = strlen(str);
  char* retorno = new char [tam+1];
  for(i = 0; i < tam; i++)
  {
    if(str[i] == '\\')
    { i++;
      switch(str[i])
      {
        case 'n': retorno[j] = 10; break;
        case 't': retorno[j] = 9; break;
        case 'r': retorno[j] = 13; break;
        default: retorno[j] = str[i];
      }
      j++;
    }else
    { if(str[i] != 'n' && str[i] != 'r')
      {
        retorno[j] = str[i];
        j++;
      }
    }
  }
  retorno[j] = '\0';
  return retorno;
}
