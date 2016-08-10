#pragma once 

class Message
{
public:
    Message(int idx, int param);
    ~Message();

    // copy and assignment
    Message(Message const& m);
    Message& operator=(Message const& m);

    void Process();

private:
    int m_param;
    int m_idx;
};
