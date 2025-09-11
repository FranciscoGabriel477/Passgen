#include <iostream>
#include <vector>
#include <algorithm> 
#include <random>    
#include <chrono>   
#include <string>
#include <cstring>
#include <stdexcept>
/**
 * @brief Embaralha um vetor usando um gerador de números aleatórios.
 * 
 * @tparam T Tipo dos elementos do vetor.
 * @param vec Vetor a ser embaralhado.
 */
template<typename T>
void embaralhar(std::vector<T>& vec) {
    static std::mt19937 rng(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    std::shuffle(vec.begin(), vec.end(), rng);
}
/**
 * @brief Valida os argumentos da linha de comando.
 * 
 * Esta função analisa os argumentos passados ao programa, determinando o tamanho
 * da senha, os grupos de caracteres que devem ser utilizados e se a força da senha
 * deve ser exibida. Também exibe a ajuda, se solicitado.
 * 
 * @param argc Número de argumentos.
 * @param argv Vetor de argumentos.
 * @param tamanho Ponteiro para armazenar o tamanho da senha.
 * @param grupos Vetor para armazenar os grupos de caracteres selecionados.
 * @return int Código de status:
 *         - 0: sucesso,
 *         - 1: grupo inválido,
 *         - 2: '--len' sem valor numérico,
 *         - 3: tamanho inválido,
 *         - 4: exibir força da senha,
 *         - 5: ajuda exibida.
 */
int validar(int argc, char* argv[], int *tamanho,std::vector<char>& grupos){ 
    bool verforca=false; //variável que vai indicar se a força precisará ser exibida
    for(int i=1;i<argc;i++){// loop para verificar todos argumentos
        if(strcmp(argv[i], "--len")==0){//verifica se o usuário solicitou um tamanho
            try {
                *tamanho= std::stoi(argv[i+1]); //converter o valor passado para inteiro
            } catch (std::invalid_argument& e) {
                return 2;//caso o valor passado não seja um inteiro encerra a aplicação e informa o problema ao usuário
            }
            i++;
            if(*tamanho<=0){//caso o usuário tenha fornecido um valor abaixo ou igual a zero encerra a aplicação e informa ao usuário
                return 3;
            }
        }
        else{
        switch(argv[i][1]){//verifica os grupos solicitados pelo usuário
                case 'l': 
                grupos.push_back('l'); 
                break;
                case 'u': 
                grupos.push_back('u'); 
                break;
                case 'd': 
                grupos.push_back('d'); 
                break;
                case 'o': 
                grupos.push_back('o'); 
                break;
                case 'p': 
                grupos.push_back('p'); 
                break;
                case 'q': 
                grupos.push_back('q'); 
                break;
                case 's': 
                grupos.push_back('s'); 
                break;
                case 'm': 
                grupos.push_back('m'); 
                break;
                case 'b':
                grupos.push_back('b'); 
                break;
                case 'a':
                grupos={'l', 'u', 'd', 'o', 'p', 'q', 's', 'm', 'b'};
                break;
                case '-':
                break;
                case 't':
                verforca=true;
                break;
                case 'h'://caso o usuário tenha pedido as orientações elas são mostradas e o programa é encerrado
                std::cout << "Este programa gera senhas de tamanho específico com base na seleção de grupos de caracteres.\n\n";
                std::cout << "Uso: passgen [<opções>]\n";
                std::cout << "  --len n Tamanho da senha (padrão é 7).\n";
                std::cout << "  -l, Adiciona letras em [a-z].\n";
                std::cout << "  -u, Adiciona letras em [A-Z].\n";
                std::cout << "  -d, Adiciona números em [0-9].\n";
                std::cout << "  -o, Adiciona símbolos em [#$%&@^`~].\n";
                std::cout << "  -p, Adiciona pontuação em [.,;:].\n";
                std::cout << "  -q, Adiciona aspas em [\"'].\n";
                std::cout << "  -s, Adiciona barras e similares em [\\/|_-].\n";
                std::cout << "  -m, Adiciona operadores matemáticos em [*+!?=].\n";
                std::cout << "  -b, Adiciona colchetes e parênteses em [{}[]()].\n";
                std::cout << "  -a, Adiciona caracteres de todos os grupos acima.\n";
                std::cout << "  -t, Mostra a classificação da força da senha.\n";
                std::cout << "  -h, Mostra esta tela de ajuda.\n";
                return 5;
                break;
                default://caso o usuário tenha pedido um grupo inválido encerra a aplicação e informa ao usuário
                return 1;
                break;
        }
    }
        if (strcmp(argv[i], "-a") == 0){//caso o usuário solicite todos os grupos
            grupos = {'l','u','d','o','p','q','s','m','b'};
        }
    }
    if(verforca){//verifica se o usuário solicitou a força
    return 4;
    }
    return 0;
}
/**
 * @brief Função principal do gerador de senhas.
 * 
 * Lê argumentos da linha de comando, valida as opções, gera uma senha com os grupos solicitados
 * e, se solicitado, exibe a força da senha.
 * 
 * @param argc Número de argumentos.
 * @param argv Vetor de argumentos.
 * @return int Código de saída.
 */
int main(int argc, char* argv[]){
    std::cout<<"Bem-vindo ao passgen v 1.0, © DIMAp 2025\n";
    int tamanho=7;
    bool verforca=false;
    std::vector<char>grupos;
    switch(validar(argc,argv,&tamanho,grupos)){//avalia a função 'validar' caso algum problema tenha sido indentifica ele é especificamente informado
        case 1:
        std::cout<<"Grupo desconhecido";
        exit(0);
        break;
        case 2:
        std::cout<<"Uso do'--len' sem fornecer tamanho";
        exit(0);
        break;
        case 3:
        std::cout<<"Tamanho inválido";
        exit(0);
        break;
        case 4:
        verforca=true;
        break;
        case 5:
        exit(0);
        break;
    }
    if(grupos.size()==0){//caso o usuário não forneca grupos a senha só possuirá letras minúsculas
        grupos = {'l'};
    }
    std::vector<char> u;
    std::vector<char> l; 
    std::vector<char> d;
    std::vector<char> o = { '#', '$', '%', '&', '@', '^', '`', '~' };
    std::vector<char> p = { '.', ',', ';', ':' };                     
    std::vector<char> q = { '"', '\'' };                              
    std::vector<char> s = { '\\', '/', '|', '_', '-' };              
    std::vector<char> m = { '*', '+', '!', '?', '=' };               
    std::vector<char> b = { '{', '}', '[', ']', '(', ')' };
    for (char c = 'A'; c <= 'Z'; ++c) {
        u.push_back(c);
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        l.push_back(c);
    }
    for (char c = '0'; c <= '9'; ++c) {
        d.push_back(c);
    }
    std::vector<char>senha;
    if(tamanho<grupos.size()){//caso o usuário tenha pedido mais grupos do que o tamanho da senha
        tamanho=grupos.size();
    }
    for(int i=0;i<grupos.size();i++){//garante que tenha pelo menos um elemento de cada grupo
        switch(grupos[i]){//o preenchimento funciona da seguinte forma: o vetor do respectivo ao grupo é embaralhado e em seguida é retirado o primeiiro elemento dele
            case 'l':
            embaralhar(l);
            senha.push_back(l[0]);
            break;
            case 'u':
            embaralhar(u);
            senha.push_back(u[0]);
            break;
            case 'd':
            embaralhar(d);
            senha.push_back(d[0]);
            break;
            case 'o':
            embaralhar(o);
            senha.push_back(o[0]);
            break;
            case 'p':
            embaralhar(p);
            senha.push_back(p[0]);
            break;
            case 's':
            embaralhar(s);
            senha.push_back(s[0]);
            break;
            case 'm':
            embaralhar(m);
            senha.push_back(m[0]);
            break;
            case 'b':
            embaralhar(b);
            senha.push_back(b[0]);
            break;
            default:
            break;
        }
    }
    for(int i=grupos.size();i<tamanho;i++){//preenche o restante da senha
        embaralhar(grupos);
        switch(grupos[0]){// o funcionamento é similar ao anterior porém, agora o vetor que contém os grupos também é embaralhado
            case 'l':
            embaralhar(l);
            senha.push_back(l[0]);
            break;
            case 'u':
            embaralhar(u);
            senha.push_back(u[0]);
            break;
            case 'd':
            embaralhar(d);
            senha.push_back(d[0]);
            break;
            case 'o':
            embaralhar(o);
            senha.push_back(o[0]);
            break;
            case 'p':
            embaralhar(p);
            senha.push_back(p[0]);
            break;
            case 's':
            embaralhar(s);
            senha.push_back(s[0]);
            break;
            case 'm':
            embaralhar(m);
            senha.push_back(m[0]);
            break;
            case 'b':
            embaralhar(b);
            senha.push_back(b[0]);
            break;
            default:
            break;
        }
    }
    embaralhar(senha);
    std::cout<<"Senha: ";
    for(int i=0;i<tamanho;i++){//imprime a senha
        std::cout<<senha[i];
    }
    if(verforca){//verifica a força da senha
        std::cout<<'\n';
        std::cout<<"Força da senha:";
        if(tamanho<4){
            std::cout<<"Muito fraca";
        }
        else if(tamanho<5){
            std::cout<<"Muito fraca";
        }
        else if(tamanho<10){
            std::cout<<"Fraca";
        }
        else if(tamanho<15|| grupos.size()<3){
            std::cout<<"Média";
        }
        else if(tamanho<20|| grupos.size()<4 ){
            std::cout<<"Forte";
        }else if(tamanho<30|| grupos.size()<5 ){
            std::cout<<"Muito Forte";
        }
        else{
            std::cout<<"Excelente";
        }
    }
    return 0;
}