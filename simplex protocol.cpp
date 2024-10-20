#include <iostream>
using namespace std;

struct packet
{
    char data[1000];
};


struct frame
{

    packet info;
};




void to_physical_layer(frame *s)
{
    cout<<"Delivering packet to physical layer\n\n";
}

void from_physical_layer(frame *r)
{
    cout<<"Fetching packet from physical layer\n\n";
}
void from_network_layer(packet *buffer)
{
    cout<<"Fetching packet from network layer\n\n";
}
void to_network_layer(packet *buffer)
{
    cout<<"Delivering packet to network layer\n\n";
}

void sender(void)
{
    frame s;
    packet buffer;
      for (int i = 1; i <= 2; ++i) {

        from_network_layer(&buffer);
        s.info=buffer;
        to_physical_layer(&s);
      }
}

void receiver(void)
{
    frame r;
    packet buffer;
    //event_type event;
        for (int i = 1; i <= 2; ++i) {
        //wait_for_event(&event);
        from_physical_layer(&r);

        to_network_layer(&r.info);

}
}

main()
{
    sender();
    receiver();
}

