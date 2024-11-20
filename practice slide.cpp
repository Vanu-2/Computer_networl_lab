#include<bits/stdc++.h>
using namespace std;

#define MAX_PKT 1024
#define TOTAL_FRAMES 8
#define WINDOW_SIZE 2


typedef int seq_num;

enum event_type{frame_arrival,timeout};

struct packet{
char data[MAX_PKT];
};

struct frame{
packet info;
seq_num seq;
seq_num ack;
};

void from_network_layer(packet &p,int seq)
{
    cout<<"Fatch packet"<<seq<<" from network layer"<<endl;
}

void to_network_layer(packet &p,int seq)
{
    cout<<"delivery packet"<<seq<<" from network layer"<<endl;
}

void to_physical_layer(frame &f)
{
    cout<<"send frame"<<f.seq<<endl;
}
void from_physical_layer(frame &f,seq_num &ack)
{
    cout<<"received frame and send ack"<<f.seq<<endl;
    ack=f.seq;
}

void start_timer(frame &f)
{
    cout<<"start timer for frame "<<f.seq<<endl;
}
void stop_timer(frame &f)
{
    cout<<"stop timer for frame "<<f.seq<<endl;
}

void wait_for_event(event_type &event)
{
    event=frame_arrival;
}

void p()
{
    int window_start=0;
    int next_frame=0;
    int previous_ack=-1;
    event_type event;

    frame far[TOTAL_FRAMES];
    packet par[TOTAL_FRAMES];

    for(int i=0;i<TOTAL_FRAMES;i++)
    {
        from_network_layer(par[i],i);
        far[i].info=par[i];
        far[i].seq=i;
        far[i].ack=-1;
    }

    while(previous_ack<(TOTAL_FRAMES-1))
    {
        cout<<"Current Window: ";
        for(int i=window_start;i<window_start+(WINDOW_SIZE)&& i<TOTAL_FRAMES;i++)
        {
            cout<<far[i].seq<<" ";
        }
        cout<<endl;

        for(int i=window_start;i<(window_start+WINDOW_SIZE) && i<TOTAL_FRAMES;i++)
        {
            if(far[i].seq>=next_frame)
            {
                to_physical_layer(far[i]);
                start_timer(far[i]);
                next_frame++;
            }
        }

        if(window_start<TOTAL_FRAMES)
        {
            wait_for_event(event);
            if(event==frame_arrival)
            {
                seq_num ack=-1;
                from_physical_layer(far[window_start],ack);
                stop_timer(far[window_start]);
                to_network_layer(far[window_start].info,far[window_start].seq);
                previous_ack=ack;
                window_start=previous_ack+1;
            }
        }

    }
}

int main()
{
    p();
}
