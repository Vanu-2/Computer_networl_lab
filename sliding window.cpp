#include<bits/stdc++.h>
using namespace std;

#define MAX_PKT 1024
#define TOTAL_FRAMES 3

enum event_type{frame_arrival,timeout};
typedef unsigned int s_n;

struct packet{
    char data[MAX_PKT];

};

struct frame{

s_n seq;
s_n ack;
packet info;
};

void wait_for_event(event_type &event)
{
    event=frame_arrival;
}

void from_network(packet &p)
{
    cout<<"Fatching packet"<<endl;
}
void to_network(packet &p)
{
    cout<<"delivery packet"<<endl;
}
void to_physical(frame &s)
{
    cout<<"send frame of seq no:"<<s.seq<<" from receiving ack:"<<s.ack<<endl;
}

void from_physical(frame &r)
{
    static s_n expected_frame=0;
    r.seq=expected_frame;
    r.ack=expected_frame;

    cout<<"received frame of seq:"<<r.seq<<" replay ack :"<<r.ack<<endl;
    expected_frame=(expected_frame+1)%2;
}

void start_timer(s_n seq)
{
    cout<<"start timer for frame sequence:"<<seq<<endl;
}
void stop_timer(s_n seq)
{
    cout<<"stop timer for frame sequence:"<<seq<<endl;
}


void protocol()
{

    s_n next_frame=0;
    s_n frame_expected=0;
    packet buffer;
    frame r,s;
    event_type event;

    for(int i=0;i<TOTAL_FRAMES;i++){

       from_network(buffer);
       s.info=buffer;
       s.seq=next_frame;
       s.ack=1-(frame_expected);

      to_physical(s);
      start_timer(s.seq);

      wait_for_event(event);

      if(event==frame_arrival)
      {
          from_physical(r);
          if(r.seq==frame_expected)
          {
              to_network(r.info);
              frame_expected=(frame_expected+1)%2;
          }
          if(r.ack==next_frame)
          {
              stop_timer(next_frame);
              next_frame=(next_frame+1)%2;
          }
      }

    }

    cout<<"All frames are ack"<<endl;


}

int main()
{
    protocol();
}
