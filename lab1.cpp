#include <iostream>
#include <cstring> // for strcpy
using namespace std;

struct packet {
    char data[1000]; // Packet holds data
};

struct frame {
    packet info; // Frame holds a packet
};

void to_physical_layer(frame *s) {
    cout << "Delivering packet to physical layer: " << s->info.data << endl;
}

void from_physical_layer(frame *r) {
    cout << "Fetching packet from physical layer\n";
}

void from_network_layer(packet *buffer, int packet_num) {
    cout << "Fetching packet " << packet_num << " from network layer\n";
    // Create a sample packet with numbered data
    string data = "Packet data " + to_string(packet_num);
    strcpy(buffer->data, data.c_str()); // Copy data into the packet
}

void to_network_layer(packet *buffer) {
    cout << "Delivering packet to network layer: " << buffer->data << endl;
}

void sender(void) {
    frame s;
    packet buffer;

    for (int i = 1; i <= 4; ++i) {
        from_network_layer(&buffer, i);  // Fetch each packet from the network layer
        s.info = buffer;                 // Place the packet into the frame
        to_physical_layer(&s);           // Send the frame to the physical layer
    }
}

void receiver(void) {
    frame r;

    for (int i = 1; i <= 4; ++i) {
        from_physical_layer(&r);        // Fetch the frame from the physical layer
        to_network_layer(&r.info);      // Deliver the packet to the network layer
    }
}

int main() {
    sender();  // Sender transmits packets
    receiver();  // Receiver processes the packets
    return 0;
}
