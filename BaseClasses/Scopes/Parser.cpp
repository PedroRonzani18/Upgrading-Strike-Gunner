#include "../Header/Parser.h"

// Função que converte uma string para um array de char

Parser::Parser()
{
    numberOfEnemies.resize(0);
    type.resize(0);
    typeMove.resize(0);
    numberOfShots.resize(0);
    typeTiroManager.resize(0);
    vx.resize(0);
    vy.resize(0);
    midpointConstantX.resize(0);
    iXSignal.resize(0);
    multiplyerX.resize(0);
    midpointConstantY.resize(0);
    iYSignal.resize(0);
    multiplyerY.resize(0);
     textureId.resize(0);
    resize.resize(0);
}

std::string Parser::arrayToString(const char* arr)
{
    //std::string str = "";
//
    //for(int i=0; i<sizeof(arr)-1; i++)
    //    str += arr[i];
//
    //return str;
    return "";
}

char* Parser::stringToArray(std::string str)
{
    int t = str.length() + 1;
    char* arr = (char *)malloc(t * sizeof(char));

    for(int i=0; i<t; i++)
        arr[i] = str[i];

    return arr;
}

std::vector<const char*> Parser::parsePath(const char* fileName)
{
    std::vector<const char*> returnVector;

    std::fstream arquivo;
    std::string linha, path = "";
    std::stringstream ss;
    
    arquivo.open(fileName,std::fstream::in);

    if(arquivo.is_open())
    {
        while(getline(arquivo,linha))
        {
            ss.clear();
		    ss.str(linha);
		    ss >> path;

            returnVector.push_back(stringToArray(path));
            //std::cout << "Dentro: " << returnVector.back() << std::endl;
        }
    }
    else std::cout << "Erro na abertura do arquivo." << std::endl;

    arquivo.close();

    return returnVector;
}

Parser Parser::parseGeneral(const char* fileName)
{
    Parser returnParser;

    std::fstream arquivo;
    std::string linha;
    std::string temp;
    float found;
    std::stringstream ss;
    
    arquivo.open(fileName,std::fstream::in);

    if(arquivo.is_open())
    {
        while(getline(arquivo,linha))
        {
            float valor;
            ss.clear(); ss.str("");
            ss << linha;

            while(!ss.eof())
            {
                ss >> temp;

                if(std::stringstream(temp) >> found)
                    valor = found;
                                
                temp = "";
            }

            std::string titulo = linha.substr(0,linha.find(":"));

            //std::cout << "Titulo: " << titulo << "  Valor: " << valor << std::endl;

                 if(titulo == "Quantidade de inimigos") returnParser.numberOfEnemies.push_back(valor);
            else if(titulo == "Type") returnParser.type.push_back(valor);
            else if(titulo == "TypeMove") returnParser.typeMove.push_back(valor);
            else if(titulo == "NumberOfShots") returnParser.numberOfShots.push_back(valor);
            else if(titulo == "TypeTiroManager") returnParser.typeTiroManager.push_back(valor);
            else if(titulo == "Velocidade X") returnParser.vx.push_back(valor);
            else if(titulo == "Velocidade Y") returnParser.vy.push_back(valor);
            else if(titulo == "Constante Midpoint x") returnParser.midpointConstantX.push_back(valor);
            else if(titulo == "Sinal'ix'") returnParser.iXSignal.push_back(valor);
            else if(titulo == "Multiplicador ix") returnParser.multiplyerX.push_back(valor);
            else if(titulo == "Constante Midpoint Y") returnParser.midpointConstantY.push_back(valor);
            else if(titulo == "Sinal'iy'") returnParser.iYSignal.push_back(valor);
            else if(titulo == "Multiplicador iy") returnParser.multiplyerY.push_back(valor);
            else if(titulo == "TextureId") returnParser.textureId.push_back((GLuint)valor);
            else if(titulo == "Resize") returnParser.resize.push_back(valor);
            else if(titulo == "CurrentProjectileDamage") returnParser.currentProjectileDamage.push_back(valor);
            else if(titulo == "BossTime") returnParser.bossTime = valor;
            else if(titulo == "MinX") returnParser.minX.push_back(valor);
            else if(titulo == "MaxX") returnParser.maxX.push_back(valor);
            else if(titulo == "MinY") returnParser.minY.push_back(valor);
            else if(titulo == "MaxY") returnParser.maxY.push_back(valor);
        }
    }

    else std::cout << "Erro de abertura" << std::endl;
    returnParser.linhas = returnParser.numberOfEnemies.size();
    //std::cout << std::endl;
    arquivo.close();

    return returnParser;
}