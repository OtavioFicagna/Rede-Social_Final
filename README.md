# Projeto Rede Social Simples Implementada com Grafos - Estutura de Dados II
Este projeto consiste em uma implementação básica de uma rede social utilizando estruturas de grafos. A rede social permite que usúarios sejam criados e sejam linkados por seus e-mails, tendo essas informações de forma persistente.

# Funcionalidades
Cadastro de usuários: Pode ser criado os usuários, informando e-mail, nome, telefone, cidade e data de nascimento;
Seguir usuários: permite cada usuário seguir outro com o link sendo o email fornecido;
Listar usuários: lista todos os usuários cadastrados na rede;
Consultar dados de usuário: consulta os dados de um usuário em específico;
Excluir usuário: excluí o usuário desejado;
Verificar caminho entre usuários: verifica o caminho mais curto entre dois usuários que se seguem;
Exportar rede: exporta para um arquivo do tipo (.dot);
Exibir informações da rede: exibe informações específicas da rede.

# Dependencias
Precisa das bibliotecas do sqlite3;
Compilador g++.

# Utilização
Pós rodar compilar o código utilizando o parâmetro -lsqlite3
**exemplo**
    g++ main.cpp -o main -lsqlite3

Via terminal, utilizando as opções fornecidas, você gerencia sua rede-social.

# Banco Teste
O programa vai com um banco padrão "db.db", contendo dados teste, segue abaixo o script utilizado:

    DELETE FROM USER;
    DELETE FROM FOLLOWERS;

    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email0@gmail.com', 'teste0', '08/04/2004', '(54)98165655','Passo Fundo');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email1@gmail.com', 'teste1', '02/09/2003', '(54)981529335','Marau');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email2@gmail.com', 'teste2', '22/10/2003', '(54)981525656','Saldanha Marinho');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email3@gmail.com', 'teste3', '25/11/2004', '(54)981522332','Santa Barbara');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email4@gmail.com', 'teste4', '25/12/2005', '(54)981522332','Passo Fundo');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email5@gmail.com', 'teste5', '27/06/2005', '(54)981522332','Passo Fundo');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email6@gmail.com', 'teste6', '01/12/2002', '(54)981565665','Soledade');
    INSERT INTO USER(EMAIL, NAME, BIRTH_DATE, PH_NUMBER, CITY) VALUES ('email7@gmail.com', 'teste7', '10/11/2002', '(54)965646320','Xangrila');

    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email1@gmail.com', 'email0@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email0@gmail.com', 'email1@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email2@gmail.com', 'email1@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email1@gmail.com', 'email2@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email3@gmail.com', 'email2@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email2@gmail.com', 'email3@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email4@gmail.com', 'email3@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email3@gmail.com', 'email4@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email5@gmail.com', 'email4@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email4@gmail.com', 'email5@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email6@gmail.com', 'email5@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email5@gmail.com', 'email6@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email7@gmail.com', 'email6@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email6@gmail.com', 'email7@gmail.com');
    INSERT INTO FOLLOWERS(USER_EMAIL, FOLLOWER) VALUES('email0@gmail.com', 'email7@gmail.com');

# Autores
Otavio Ficagna - 195749
Carlos Eduardo Rosa Batista - 193570
Luiz Henrique Fischer - 192915