#include "../incs/bot.hpp"



std::string I_To_S(int num)
{
    std::stringstream ss;
    ss << num;
    return (ss.str());
}

Bot::Bot(const std::string& name, int port, const std::string password, const std::string& ip) : 
    _Name(name), 
    _Port(port),
    _Password(password),
    _Ip(ip)
{   
	return;
}

Bot::~Bot()
{
	return;
}

int	Bot::Start_Bot()
{

    _Bot_Socket = socket(AF_INET6, SOCK_STREAM, 0);
    if (_Bot_Socket < 0) {
        log(ERROR_SOCKET);
        return ERROR;
    }

    log("Socket -> " + I_To_S(_Bot_Socket));

    memset(&_Bot_Address, 0, sizeof(_Bot_Address));
    _Bot_Address.sin6_family = AF_INET6;
    _Bot_Address.sin6_addr = in6addr_any; 
    _Bot_Address.sin6_port = htons(_Port);

    int yes = 1;
    if (setsockopt(_Bot_Socket, SOL_SOCKET, SO_REUSEADDR, &(yes), sizeof(int)) == -1) {
        log(ERROR_CONF_SOCKET);
        return ERROR;
    }

    // Se connecter au serveur IRC
    if (connect(_Bot_Socket, (struct sockaddr*)&_Bot_Address, sizeof(_Bot_Address)) < 0) {
        log(ERROR_CONNECTION);
        return ERROR;
    }

    log("Connected and ready !");

    // Envoyer les commandes USER et NICK pour s'identifier
    std::string user_cmd = "USER " + _Name + " 0 * :" + _Name + "\r\n";
    std::string nick_cmd = "NICK " + _Name + "\r\n";
    std::string pass_cmd = "PASS " + _Password + "\r\n";
    send(_Bot_Socket, user_cmd.c_str(), user_cmd.length(), 0);
    send(_Bot_Socket, nick_cmd.c_str(), nick_cmd.length(), 0);
    send(_Bot_Socket, pass_cmd.c_str(), pass_cmd.length(), 0);

    //Attend le message de bienvenu

    // Rejoindre le canal #bot
    std::string join_cmd = "JOIN #bot\r\n";
    send(_Bot_Socket, join_cmd.c_str(), join_cmd.length(), 0);

    return GOOD;
}

bool contains(const std::string& input, const std::string &needle) {
    std::string::size_type pos = input.find(needle);
    return pos != std::string::npos;
}

int	Bot::Run()
{
    while (1) 
    {

        // Lire la réponse du serveur IRC
        char buffer[BUFFER_SIZE];
        int bytes_received = recv(_Bot_Socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) 
        {
            log(ERROR_RECEIVE);
            break;
        }

        buffer[bytes_received - 1] = '\0';
        std::string response(buffer);
        // log(buffer);

        // Traiter la réponse du serveur
        if (contains(buffer, "PING")) 
        {
            // Répondre au ping du serveur avec un pong
            std::string pong_cmd = "PRIVMSG #bot :PONG\r\n";
            send(_Bot_Socket, pong_cmd.c_str(), pong_cmd.length(), 0);
            log("Pong!");
        } 

        // Traiter la réponse du serveur
        if (contains(buffer, "PONG"))
        {
            std::string ping_cmd = "PRIVMSG #bot :PING\r\n";
            send(_Bot_Socket, ping_cmd.c_str(), ping_cmd.length(), 0);
            log("Ping!");
        } 

        if (contains(buffer, "quoi"))
        {
            std::string ping_cmd = "PRIVMSG #bot :feur\r\n";
            send(_Bot_Socket, ping_cmd.c_str(), ping_cmd.length(), 0);
            log("Ping!");
        } 
    }

    return GOOD;
}

int	Bot::Stop_Bot()
{
    close(_Bot_Socket);
    return GOOD;
}

void	Bot::log(std::string const &logMsg)	const {
	std::cout << "\033[38;5;160m";
	std::cout << "Bot : " << logMsg << std::endl;
	std::cout << "\033[m";
}