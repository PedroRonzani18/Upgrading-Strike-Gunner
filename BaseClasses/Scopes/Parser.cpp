#include "../Header/Parser.h"

// Função que converte uma string para um array de char
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

Parser Parser::parseEnemy(const char* fileName)
{
    Parser returnParser;

    std::fstream arquivo;
    std::string linha;
    std::string temp;
    float found;
    std::stringstream ss;
    std::vector<float> values;
    
    arquivo.open(fileName,std::fstream::in);

    if(arquivo.is_open())
    {
        while(getline(arquivo,linha))
        {
            ss.clear(); ss.str("");
            ss << linha;

            while(!ss.eof())
            {
                ss >> temp;

                if(std::stringstream(temp) >> found)
                    values.push_back(found);
                                
                temp = "";
            }
        }
    }

    int linhas = values.size()/13.0;
    returnParser.linhas = linhas;

    arquivo.close();

    for(int i=0; i<linhas; i++)
    {
        returnParser.numberOfEnemies.push_back(values[0+13*i]);
        returnParser.type.push_back(values[1+13*i]);
        returnParser.typeMove.push_back(values[2+13*i]);
        returnParser.numberOfShots.push_back(values[3+13*i]);
        returnParser.typeTiroManager.push_back(values[4+13*i]);
        returnParser.vx.push_back(values[5+13*i]);
        returnParser.vy.push_back(values[6+13*i]);
        returnParser.midpointConstantX.push_back(values[7+13*i]);
        returnParser.iXSignal.push_back(values[8+13*i]);
        returnParser.multiplyerX.push_back(values[9+13*i]);
        returnParser.midpointConstantY.push_back(values[10+13*i]);
        returnParser.iYSignal.push_back(values[11+13*i]);
        returnParser.multiplyerY.push_back(values[12+13*i]);
    }

    return returnParser;
}