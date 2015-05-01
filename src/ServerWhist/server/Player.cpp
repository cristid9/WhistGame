#include "Player.h"

namespace WhistGame
{

Player::Player(boost::asio::ip::tcp::socket *sock)
{
    socketPlayer = sock;
}

Player::~Player()
{

}

void Player::SetName(std::string newName)
{
    name = newName;
}

std::string Player::GetName()
{
    return name;
}

boost::asio::ip::tcp::socket* Player::GetSocket()
{
    return socketPlayer;
}

}

