#include "../Header/Parser.h"

// Função que converte uma string para um array de char

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

std::vector<float> Parser::parseNumbers(const char* fileName)
{
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

    return values;
}

Parser Parser::parseEnemyTexture(const char* fileName)
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

    int linhas = values.size()/14.0;
    returnParser.linhas = linhas;

    arquivo.close();

    for(int i=0; i<linhas; i++)
    {
        returnParser.numberOfEnemies.push_back(values[0+14*i]);
        returnParser.type.push_back(values[1+14*i]);
        returnParser.typeMove.push_back(values[2+14*i]);
        returnParser.numberOfShots.push_back(values[3+14*i]);
        returnParser.typeTiroManager.push_back(values[4+14*i]);
        returnParser.vx.push_back(values[5+14*i]);
        returnParser.vy.push_back(values[6+14*i]);
        returnParser.midpointConstantX.push_back(values[7+14*i]);
        returnParser.iXSignal.push_back(values[8+14*i]);
        returnParser.multiplyerX.push_back(values[9+14*i]);
        returnParser.midpointConstantY.push_back(values[10+14*i]);
        returnParser.iYSignal.push_back(values[11+14*i]);
        returnParser.multiplyerY.push_back(values[12+14*i]);
        returnParser.textureId.push_back(values[13+14*i]);
    }

    return returnParser;
}

Parser Parser::parseEnemyTextureResize(const char* fileName)
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

    int linhas = values.size()/15.0;
    returnParser.linhas = linhas;

    arquivo.close();

    for(int i=0; i<linhas; i++)
    {
        returnParser.numberOfEnemies.push_back(values[0+15*i]);
        returnParser.type.push_back(values[1+15*i]);
        returnParser.typeMove.push_back(values[2+15*i]);
        returnParser.numberOfShots.push_back(values[3+15*i]);
        returnParser.typeTiroManager.push_back(values[4+15*i]);
        returnParser.vx.push_back(values[5+15*i]);
        returnParser.vy.push_back(values[6+15*i]);
        returnParser.midpointConstantX.push_back(values[7+15*i]);
        returnParser.iXSignal.push_back(values[8+15*i]);
        returnParser.multiplyerX.push_back(values[9+15*i]);
        returnParser.midpointConstantY.push_back(values[10+15*i]);
        returnParser.iYSignal.push_back(values[11+15*i]);
        returnParser.multiplyerY.push_back(values[12+15*i]);
        returnParser.textureId.push_back(values[13+15*i]);
        returnParser.resize.push_back(values[14+15*i]);
    }

    return returnParser;
}