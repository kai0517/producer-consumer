#include "message.h"
#include <iostream>

Message::Message(int idx, int param)
    : m_param(param)
    , m_idx(idx)
{}

Message::~Message()
{}

Message::Message(Message const& m)
    : m_param(m.m_param)
    , m_idx(m.m_idx)
{}

Message& Message::operator=(Message const& m)
{
    m_param = m.m_param;
    m_idx   = m.m_idx;
    return *this;
}

void Message::Process()
{
    std::cout << "Message "      << m_idx 
              << ": Parameter: " << m_param 
              << std::endl;
}
