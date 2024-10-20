#include<bits/stdc++.h>
using namespace std;


#define MAX_SEQ 1
#define MAX_PKT 1024
#define TOTAL_FRAMES 5


enum event_type{frame_arrival, timeout};
typedef unsigned int seq_n;

struct packet{
unsigned char data[MAX_PKT];
};

struct frame{

packet info;
seq_n ack;
seq_n seq;

};
void inc(seq_n *num)
{
    *num=(*num+1)%(MAX_SEQ+1);
}
void from_network_layer(packet *p){
cout<<"Fatch packet"<<endl;

}

void to_network_layer(packet *p){
cout<<"Deliver packet"<<endl;

}

void from_physical_layer(frame *r)
{
    r->seq=0;
    r->ack=1;
}

void to_physical_layer(frame *s)
{
    cout<<"Transmit frame"<<endl;
}

void wait_for_event(event_type *event)
{
    *event=frame_arrival;
}
void start_timer(seq_n k)
{
    cout<<"start timer :"<<k<<endl;
}
void stop_timer(seq_n k)
{
    cout<<"stop timer :"<<k<<endl;
}

void protocol()
{
    seq_n next_frametosend=0;
    seq_n expected_frame=0;
    packet buffer;
    frame r,s;
    event_type event;

    for(int i=0;i<TOTAL_FRAMES;i++)
    {
        from_network_layer(&buffer);
        s.info=buffer;
        s.seq=next_frametosend;
        s.ack=1-expected_frame;

        cout<<"Send frame:"<<s.seq<<"  Ack:"<<s.ack<<endl;
        to_physical_layer(&s);
        start_timer(s.seq);

        wait_for_event(&event);

        if(event==frame_arrival)
        {
            from_physical_layer(&r);
            cout<<"received frame:"<<r.seq<<"Ack:"<<r.ack<<endl;

            if(r.seq==expected_frame)
            {
                to_network_layer(&r.info);
                inc(&expected_frame);
            }

            if(r.ack==next_frametosend)
            {
                stop_timer(r.ack);
                inc(&next_frametosend);
            }
        }
    }
    cout<<"All frame send and ack"<<endl;
}

int main() {
    protocol();  // Start the 1-bit sliding window protocol
    return 0;
}
