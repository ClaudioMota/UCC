struct No
{
	Token* token;
	Producao* producao;

	Producao::No::No(Token* token)
	{
	 this->token = token;
	 producao = NULL;
	}
	
	Producao::No::No(Producao* prod)
	{
		token = null;
		producao = prod;
	}

	Producao::No::~No
	{
	 if(token) delete token;
	 if(producao) delete producao;
	}	 
};

int estado0(int* pilhaEstados, ParteProducao* pilhaObjetos, int pos, Token* token)
{
	if(token == NULL)
	{
		return ERRO;
	}
	
	switch(token->tipo)
	{
		case Token::ponto_virgula:
			pilhaObjetos[pos] = new ParteProducao();
			pos++;
			pilhaEstados[pos] = 5;
		break;
		
		case Token::identificador:
			Producao* reducao = new Comando();
			
			for(int i = 0; i < 5; i++)
			{
				reducao->add(pilhaObjetos[pos - 5 + i -1]);
			}
			
			pos -= 5;
			pilhaObjetos[pos] = reducao;
			pos++;
			
			pilhaEstados[pos] = 12;
		break;
		
		...
		
		default:
			return ERRO;
		
	}
}

AnalizadorSintatico::AnalizadorSintatico()
{
  producaoFinal = NULL;
  analizadores[0] = estado0;
}

Producao* AnalizadorSintatico::getProducaoFinal()
{
	return producaoFinal;
}

std::string AnalizadorSintatico::getUltimoErro()
{
	return "";
}

int AnalizadorSintatico::analizar(Token* tokens)
{
  int pos = 0;
  int pilhaEstados[1000];
  ParteProducao* pilhaObjetos[1000];

  while(pos >= 0)
  {
	if(!token->ignorado())
	  resultado = analizadores[pilhaEstados[pos]](pilhaEstados,pilhaObjetos,pos,token);
	token = token->proximo;

	if(resultado == ERRO || resultado == ACEITO)
	{
	  return resultado;
	}
  }
}