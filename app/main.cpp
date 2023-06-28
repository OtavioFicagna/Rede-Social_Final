#include <iostream>
#include <fstream>
#include "dao.cpp"


void register_user(std::unordered_map<std::string, Users> &map_users) {
    std::string email;
    std::cout << "Digite o email do usuário: ";
    std::cin >> email;

    if (map_users.find(email) != map_users.end()) {
        std::cout << "Já existe um usuário cadastrado com esse email.\n";
        return;
    }

    Users user;
    std::string aux;
    user.setEmail(email);

    std::cout << "Digite o nome do usuário: ";
    std::cin.ignore();
    std::getline(std::cin, aux);
    user.setName(aux);

    std::cout << "Digite a data de nascimento do usuário: ";
    std::getline(std::cin, aux);
    user.setBirthDate(aux);
    

    std::cout << "Digite o número de número de telefone do usuário: ";
    std::cin >> aux;
    user.setPhNumber(aux);
    
    std::cout << "Digite a cidade do usuário: ";
    std::cin.ignore();
    std::getline(std::cin, aux);
    user.setCity(aux);

    std::unordered_set<std::string> seguindo;
    user.setSeguindo(seguindo);
    std::unordered_set<std::string> seguidores;
    user.setSeguidores(seguidores);

    map_users[email] = user;

    bool i = save_user(user);
    if(!i)
    {
       std::cout << "Erro no banco de dados\n";
       return;
    }
    std::cout << "Usuário cadastrado com sucesso.\n";
}

void follow_user(std::unordered_map<std::string, Users> &map_users) {
    std::string emailSeguidor, emailSeguido;
    std::cout << "Digite o email do seguidor: ";
    std::cin >> emailSeguidor;
    std::cout << "Digite o email do usuário a ser seguido: ";
    std::cin >> emailSeguido;

    if (map_users.find(emailSeguidor) == map_users.end() ||
        map_users.find(emailSeguido) == map_users.end()) {
        std::cout << "Um ou ambos os usuários não existem.\n";
        return;
    }

    if(emailSeguido == emailSeguidor)
    {
        std::cout << "Usuário seguidor é igual ao usuário seguido\n";
        return;
    }

    if (map_users[emailSeguidor].getSeguindo().find(emailSeguido) != map_users[emailSeguidor].getSeguindo().end()) {
        std::cout << emailSeguidor << " já está seguindo " << emailSeguido << ".\n";
        return;
    }

    bool i = save_follow(emailSeguido, emailSeguidor);
    if(!i)
    {
       std::cout << "Erro no banco de dados\n";
       return;
    }

    map_users[emailSeguidor].insertSeguindo(emailSeguido);
    map_users[emailSeguido].insertSeguidor(emailSeguidor);

    std::cout << "Seguidor cadastrado com sucesso.\n";

    std::cout << emailSeguidor << " começou a seguir " << emailSeguido << ".\n";
}

void unfollow_user(std::unordered_map<std::string, Users> &map_users) {
    std::string emailSeguidor, emailSeguido;
    std::cout << "Digite o email do seguidor: ";
    std::cin >> emailSeguidor;
    std::cout << "Digite o email do usuário a ser deixado de seguir: ";
    std::cin >> emailSeguido;

    if (map_users.find(emailSeguidor) == map_users.end() ||
        map_users.find(emailSeguido) == map_users.end()) {
        std::cout << "Um ou ambos os usuários não existem.\n";
        return;
    }

    if (map_users[emailSeguidor].getSeguindo().find(emailSeguido) == map_users[emailSeguidor].getSeguindo().end()) {
        std::cout << emailSeguidor << " não está seguindo " << emailSeguido << ".\n";
        return;
    }

    bool i = remove_follow(emailSeguido, emailSeguidor);
    if(!i)
    {
       std::cout << "Erro ao remover do banco de dados\n";
       return;
    }

    map_users[emailSeguidor].removeSeguindo(emailSeguido);
    map_users[emailSeguido].removeSeguidor(emailSeguidor);

    std::cout << emailSeguidor << " deixou de seguir " << emailSeguido << ".\n";
}

void list_users(std::unordered_map<std::string, Users>& map_users) {
    std::cout << "Lista de usuários:\n";
    for (const auto& par : map_users) {
        Users usuario = par.second;
        std::cout << "Email: " << usuario.getEmail() << "\n";
        std::cout << "Nome: " << usuario.getName() << "\n";
        std::cout << "Número de pessoas seguidas: " << usuario.getSeguindo().size() << "\n";
        std::cout << "Número de seguidores: " << usuario.getSeguidores().size() << "\n";
        std::cout << "-----\n";
    }
}

void consult_user(std::unordered_map<std::string, Users>& map_users) {
    std::string email;
    std::cout << "Digite o email do usuário: ";
    std::cin >> email;

    if (map_users.find(email) == map_users.end()) {
        std::cout << "Usuário não encontrado.\n";
        return;
    }

    Users usuario = map_users[email];

    std::cout << "Dados do usuário:\n";
    std::cout << "Email: " << usuario.getEmail() << "\n";
    std::cout << "Nome: " << usuario.getName() << "\n";
    std::cout << "Data de Nascimento: " << usuario.getBirthDate() << "\n";
    std::cout << "Número de telefone: " << usuario.getPhNumber() << "\n";
    std::cout << "Cidade: " << usuario.getCity() << "\n";

    std::cout << "Usuários que este usuário segue:\n";
    for (const std::string& emailSeguido : usuario.getSeguindo()) {
        std::cout << emailSeguido << "\n";
    }
}

void remove_user(std::unordered_map<std::string, Users>& map_users) {
    std::string email;
    std::cout << "Digite o email do usuário a ser excluído: ";
    std::cin >> email;

    if (map_users.find(email) == map_users.end()) {
        std::cout << "Usuário não encontrado.\n";
        return;
    }

    Users usuario = map_users[email];

    std::cout << "Dados do usuário:\n";
    std::cout << "Email: " << usuario.getEmail() << "\n";
    std::cout << "Nome: " << usuario.getName() << "\n";
    std::cout << "Data de Nascimento: " << usuario.getBirthDate() << "\n";
    std::cout << "Número de telefone: " << usuario.getPhNumber() << "\n";
    std::cout << "Cidade: " << usuario.getCity() << "\n";

    std::cout << "Tem certeza que deseja excluir este usuário? (S/N): ";
    char confirmacao;
    std::cin >> confirmacao;

    if (confirmacao == 'S' || confirmacao == 's') {
        for (const std::string& emailSeguidor : usuario.getSeguidores()) {
            map_users[emailSeguidor].removeSeguindo(email);
        }

        for (const std::string& emailSeguido : usuario.getSeguindo()) {
            map_users[emailSeguido].removeSeguidor(email);
        }
  
        bool i = delete_user(email);
        if(!i)
        {
            std::cout << "Erro ao remover do banco de dados\n";
            return;
        }
        
        map_users.erase(email);

        std::cout << "Usuário excluído com sucesso.\n";
    } else {
        std::cout << "Exclusão cancelada.\n";
    }
}

void find_path(std::unordered_map<std::string, Users>& map_users) {
    std::string email1, email2;
    std::cout << "Digite o email do primeiro usuário: ";
    std::cin >> email1;
    std::cout << "Digite o email do segundo usuário: ";
    std::cin >> email2;

    if (map_users.find(email1) == map_users.end() ||
        map_users.find(email2) == map_users.end()) {
        std::cout << "Um ou ambos os usuários não existem.\n";
        return;
    }

    std::unordered_set<std::string> visitados;
    std::unordered_map<std::string, std::string> caminho;
    std::vector<std::string> fila;
    bool encontrouCaminho = false;

    fila.push_back(email1);
    visitados.insert(email1);

    while (!fila.empty()) {
        std::string emailAtual = fila.front();
        fila.erase(fila.begin());

        if (emailAtual == email2) {
            encontrouCaminho = true;
            break;
        }

        for (const std::string& emailSeguido : map_users[emailAtual].getSeguindo()) {
            if (visitados.find(emailSeguido) == visitados.end()) {
                fila.push_back(emailSeguido);
                visitados.insert(emailSeguido);
                caminho[emailSeguido] = emailAtual;
            }
        }
    }

    if (encontrouCaminho) {
        std::cout << "Caminho entre " << email1 << " e " << email2 << ":\n";
        std::vector<std::string> caminhoInvertido;
        std::string emailAtual = email2;
        while (emailAtual != email1) {
            caminhoInvertido.push_back(emailAtual);
            emailAtual = caminho[emailAtual];
        }
        caminhoInvertido.push_back(email1);

        for (int i = caminhoInvertido.size() - 1; i >= 0; --i) {
            std::cout << caminhoInvertido[i] << "\n";
        }
    } else {
        std::cout << "Não há caminho entre " << email1 << " e " << email2 << ".\n";
    }
}

void export_network(std::unordered_map<std::string, Users>& map_users) {
    std::string formato;
    std::cout << "Exportando rede.dot";

    std::ofstream arquivo("rede.dot");
    if (arquivo.is_open()) {
        arquivo << "digraph RedeSocial {\n";

        for (const auto& par : map_users) {
            Users usuario = par.second;
            arquivo << "  " << usuario.getEmail() << " [label=\"" << usuario.getName() << "\"];\n";
            for (const std::string& emailSeguido : usuario.getSeguindo()) {
                arquivo << "  " << usuario.getEmail() << " -> " << emailSeguido << ";\n";
            }
        }

        arquivo << "}\n";

        arquivo.close();
        std::cout << "Rede exportada com sucesso.\n";
    } else {
        std::cout << "Falha ao exportar a rede.\n";
    }
}

void show_networkInformation(std::unordered_map<std::string, Users>& map_users) {
    int numUsuarios = map_users.size();
    int numConexoes = 0;
    int grauMedioEntrada = 0;
    int grauMedioSaida = 0;
    int diametroGrafo = 0;
    int usuarioMaiorNumSeguidores = 0;
    std::string nome;

    for (const auto& par : map_users) {
        Users usuario = par.second;
        numConexoes += usuario.getSeguindo().size();
        grauMedioSaida += usuario.getSeguindo().size();
        grauMedioEntrada += usuario.getSeguidores().size();
        if (usuario.getSeguidores().size() > usuarioMaiorNumSeguidores) {
            usuarioMaiorNumSeguidores = usuario.getSeguidores().size();
            nome = usuario.getName();
        }
    }

    if (numUsuarios > 0) {
        grauMedioEntrada /= numUsuarios;
        grauMedioSaida /= numUsuarios;
    }

    std::cout << "Informações da Rede:\n";
    std::cout << "Quantidade de usuários cadastrados: " << numUsuarios << "\n";
    std::cout << "Grau médio de entrada: " << grauMedioEntrada << "\n";
    std::cout << "Grau médio de saída: " << grauMedioSaida << "\n";
    std::cout << "Diâmetro do grafo: " << diametroGrafo << "\n";
    std::cout << "Usuário com maior número de seguidores: " << nome 
                                                            << " com "
                                                            << usuarioMaiorNumSeguidores 
                                                            << " seguidores\n";
}

int main()
{
    if(!initDb())
    {
       std::cout << "Erro ao iniciar o banco de dados, o programa será encerrado!\n";
       return 1;
    }
    

    std::unordered_map<std::string, Users> map_users;
    if(!load_data(map_users))
    {
       std::cout << "Erro ao carregar os dados, o programa será encerrado!\n";
       return 1;
    }
    if(!load_links(map_users))
    {
       std::cout << "Erro ao carregar os dados, o programa será encerrado!\n";
       return 1;
    }

    int opcao;
    do {
        std::cout << "----------- Menu -----------\n";
        std::cout << "1. Cadastrar usuário\n";
        std::cout << "2. Seguir usuário\n";
        std::cout << "3. Deixar de seguir usuário\n";
        std::cout << "4. Listar usuários\n";
        std::cout << "5. Consultar dados de usuário\n";
        std::cout << "6. Excluir usuário\n";
        std::cout << "7. Verificar caminho entre usuários\n";
        std::cout << "8. Exportar rede\n";
        std::cout << "9. Exibir informações da rede\n";
        std::cout << "0. Sair\n";
        std::cout << "Digite a opção desejada: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                register_user(map_users);
                break;
            case 2:
                follow_user(map_users);
                break;
            case 3:
                unfollow_user(map_users);
                break;
            case 4:
                list_users(map_users);
                break;
            case 5:
                consult_user(map_users);
                break;
            case 6:
                remove_user(map_users);
                break;
            case 7:
                find_path(map_users);
                break;
            case 8:
                export_network(map_users);
                break;
            case 9:
                show_networkInformation(map_users);
                break;
            case 0:
                std::cout << "Saindo do programa.\n";
                break;
            default:
                std::cout << "Opção inválida. Tente novamente.\n";
                break;
        }

        std::cout << "\n";
    } while (opcao != 0);
    
    return 0;

}
