#include "../incs/Irc.hpp"
#include "../incs/Server.hpp"
#include "../incs/Client.hpp"

/* Channel deal with methods */ // private for now

// void	Server::Try_Add_New_Channel(std::string const &name, Client &chop) {
// 	try {
// 		t_mapChannel::iterator	it;
// 		it = _Chan_List.find(name);
// 		if (it != _Chan_List.end())
// 			throw Channel::ErrorMsgException("this Channel already exists");
// 		_Chan_List[name] = Channel(name, chop);
// 	} catch(Channel::ErrorMsgException &e) {
// 		log(std::string(EVENT_CHANNEL_CREATION_FAILED) + e.what());
// 		//std::cout << EVENT_CHANNEL_CREATION_FAILED << e.what() << std::endl;
// 		// [+] envoyer un message retour au client qui a mal fait son /join
// 	}
// }



// void	Server::Rm_Channel(std::string const &name) {
// 	t_mapChannel::iterator	it;
	
// 	it = _Chan_List.find(name);
// 	if (it != _Chan_List.end()) {
// 		_Chan_List.erase(it);
// 		log("Deleting channel : " + name);
// 	}
// }