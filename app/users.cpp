#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Users
{
    private:

        std::string email;
        std::string name;
        std::string birthDate;
        std::string phNumber;
        std::string city;
        std::unordered_set<std::string> seguindo;
        std::unordered_set<std::string> seguidores;

    public:

        //Constructors
        Users()
        {

        }
        Users(std::string e, std::string n, std::string b,
            std::string p, std::string c, std::unordered_set<std::string> seguindo,
            std::unordered_set<std::string> seguidores)
        {
            email = e;
            name = n;
            birthDate = b;
            phNumber = p;
            city = c;
            this->seguindo = seguindo;
            this->seguidores = seguidores;
        }
        //Getters and Setters
        void setEmail(std::string email)
        {
            this->email = email;
        }
        
        std::string getEmail()
        {
            return email;
        }

        void setName(std::string name)
        {
            this->name = name;
        }
        
        std::string getName()
        {
            return name;
        }

        void setBirthDate(std::string birthDate)
        {
            this->birthDate = birthDate;
        }
        
        std::string getBirthDate()
        {
            return birthDate;
        }

        void setPhNumber(std::string phNumber)
        {
            this->phNumber = phNumber;
        }
        
        std::string getPhNumber()
        {
            return phNumber;
        }

        void setCity(std::string city)
        {
            this->city = city;
        }
        
        std::string getCity()
        {
            return city;
        }

        void setSeguindo(std::unordered_set<std::string> seguindo)
        {
            this->seguindo = seguindo;
        }
        
        std::unordered_set<std::string> getSeguindo()
        {
            return seguindo;
        }
        
        void setSeguidores(std::unordered_set<std::string> seguidores)
        {
            this->seguidores = seguidores;
        }
        
        std::unordered_set<std::string> getSeguidores()
        {
            return seguidores;
        }

        void insertSeguindo(std::string email)
        {
            seguindo.insert(email);
        }

        void insertSeguidor(std::string email)
        {
            seguidores.insert(email);
        }

        void removeSeguindo(std::string email)
        {
            seguindo.erase(email);
        }

        void removeSeguidor(std::string email)
        {
            seguidores.erase(email);
        }

};