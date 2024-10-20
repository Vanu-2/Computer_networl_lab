#include<stdio.h>
using namespace std;




void wait_for_event(event_type *event)
{

}
void to_physical_layer(frame *s)
{

}

void from_physical_layer(frame *r)
{

}
void from_network_layer(packet *buffer)
{

}
void to_network_layer(packet *buffer)
{

}

void sender(void)
{
    frame s;
    packet buffer;
     event_type_event;

    while(true)
    {
        from_network_layer(&buffer);
        s.info=buffer;
        to_physical_layer(&s);
        wait_for_event(&event);
    }
}

void receiver(void)
{
    frame r;
    packet buffer;
    event_type event;
    while(true)
    {
        wait_for_event(&event);
        from_physical_layer(&r);

        to_network_layer(&r.info);
    }
}

main()
{
    sender();
    receiver();
}

